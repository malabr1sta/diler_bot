HEADERS = {
    'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64; rv:122.0) Gecko/20100101 Firefox/122.0',
    'Accept': '*/*',
    'Accept-Language': 'en-US,en;q=0.5',
    'Accept-Encoding': 'gzip, deflate, br',
    'Referer': 'https://magnit.ru/',
    'x-platform-version': 'window.navigator.userAgent',
    'x-device-id': 'c234jfssc',
    'x-device-tag': 'disabled',
    'x-app-version': '0.1.0',
    'x-device-platform': 'Web',
    'x-client-name': 'magnit',
    'Origin': 'https://magnit.ru',
    'Connection': 'keep-alive',
    'Sec-Fetch-Dest': 'empty',
    'Sec-Fetch-Mode': 'cors',
    'Sec-Fetch-Site': 'same-site',
    'Content-Type': 'application/json'
}
URL_STORE = 'https://web-gateway.middle-api.magnit.ru/v1/geolocation/store'
URL_CATEGORY = 'https://web-gateway.middle-api.magnit.ru/v2/goods/categories'
URL_PRODUCTS = 'https://web-gateway.middle-api.magnit.ru/v3/goods'
PARAMS_STORE = {
    'Longitude': '44.549305338867185',
    'Latitude': '48.77240357993189',
    'Radius': '9999999999',
    'Limit': '100000000000000'
}
PRODUCTS_DATA = {
    "includeForAdults": True,
    "onlyDiscount": False,
    "pagination": {"number": 1, "size": 500},
    "order": "desc",
    "shopType": "1",
    "sortBy": "price",
    "filters": []
}
