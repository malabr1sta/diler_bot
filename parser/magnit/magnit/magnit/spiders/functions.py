from typing import List, Dict, Any


def get_category_id(childrens: List[Dict[str, Any]],
                    category_list: List) -> None:

    for children in childrens:
        item = children.get('children')
        if not item:
            category_list.append(children.get('id', 0))
            continue
        get_category_id(item, category_list)


def get_store(stores: List[Dict[str, Any]], address: str):

    for store in stores:
        if store.get('address') == address:
            return {
                    'city': store.get('city'),
                    'id': store.get('id'),
                    'code': store.get('code')
                    }
