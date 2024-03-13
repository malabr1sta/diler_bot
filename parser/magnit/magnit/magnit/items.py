import scrapy


class MagnitItem(scrapy.Item):
    net_store = scrapy.Field()
    city = scrapy.Field()
    address = scrapy.Field()
    name = scrapy.Field()
    regular_price = scrapy.Field()
    prom_price = scrapy.Field()
    discount = scrapy.Field()
    link_to_image = scrapy.Field()
