import scrapy

from magnit.items import MagnitItem
from magnit.spiders import (
    constanst as spiders_constants,
    functions as spiders_functions
)

import json
from urllib.parse import urlencode


class ProductsSpider(scrapy.Spider):
    name = "products"

    def start_requests(self):
        yield scrapy.Request(
                callback=self.parse_store,
                url=f'{spiders_constants.URL_STORE}?{urlencode(spiders_constants.PARAMS_STORE)}',
                headers=spiders_constants.HEADERS,
        )

    def parse_store(self, response):
        data = json.loads(response.text)
        address = getattr(self, "address", None)
        store = spiders_functions.get_store(data.get('stores'), address)
        yield scrapy.Request(
                callback=self.parse_category,
                url=f'{spiders_constants.URL_CATEGORY}?StoreCode={store.get("code")}',
                headers=spiders_constants.HEADERS,
                meta={'store': store}
        )

    def parse_category(self, response):
        store = response.meta.get('store')
        data = json.loads(response.text)
        category = getattr(self, "category", None)
        category_ids = []
        for item in data:
            if item.get('name', '') == category:
                spiders_functions.get_category_id(
                        item.get('children'),
                        category_ids
                )
                break
        data = spiders_constants.PRODUCTS_DATA.copy()
        data["categoryIDs"] = category_ids
        data["storeCodes"] = [f"{store.get('code')}"]
        yield scrapy.Request(
                callback=self.parse_products,
                url=spiders_constants.URL_PRODUCTS,
                headers=spiders_constants.HEADERS,
                method='POST',
                body=json.dumps(data),
                meta={
                    'store': store,
                    'page': 1,
                    'data': data
                }
        )

    def parse_products(self, response):
        store = response.meta.get('store')
        data = json.loads(response.text)
        products = data.get("goods")
        for product in products:
            image = product.get('image')
            offers = product.get('offers')[0]
            prom_price = offers.get('oldPrice', '-')
            regular_price = offers.get('price')
            if prom_price != '-':
                regular_price, prom_price = prom_price, regular_price
            item = MagnitItem()
            item['net_store'] = 'Magnit'
            item['city'] = store.get('city')
            item['address'] = getattr(self, "address", None)
            item['name'] = product.get('name')
            item['regular_price'] = regular_price
            item['prom_price'] = prom_price
            item['discount'] = offers.get('discountPercent', '-')
            item['link_to_image'] = f'{image.get("prefixUrl")}{image.get("defaultSize")}{image.get("postfixUrl")}'
            yield item
        pagination = data.get('pagination')
        total_page = int(pagination.get('totalPages'))
        page = response.meta.get('page')
        if page < total_page:
            new_data = response.meta.get('data')
            new_data["pagination"]["number"] += 1
            yield scrapy.Request(
                callback=self.parse_products,
                url=spiders_constants.URL_PRODUCTS,
                headers=spiders_constants.HEADERS,
                method='POST',
                body=json.dumps(new_data),
                meta={
                    'store': store,
                    'page': 1,
                    'data': new_data
                }
            )
