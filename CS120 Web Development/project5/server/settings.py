# settings.py
DOMAIN = {
    'people':{
        'schema': {
            'name': {
                'type': 'string',
                'minlength': 1,
                'maxlength': 10,
            },
        },
    },
    'books':{
        'schema': {
            'name': {
                'type': 'string',
                'minlength': 1,
                'maxlength': 30,
            },
            'author': {
                'type': 'string',
                'minlength': 1,
                'maxlength': 30,
            },
            'publisher': {
                'type': 'string',
                'minlength': 1,
                'maxlength': 30,
            },
            'published': {
                'type': 'integer',
            },
        },
    },
    }
RESOURCE_METHODS = ['GET', 'POST']
ITEM_METHODS = ['GET', 'PATCH', 'PUT', 'DELETE']
X_DOMAINS = '*'
