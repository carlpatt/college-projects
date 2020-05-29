# settings.py
DOMAIN = {
    'people':{
        'schema': {
            'name': {
                'type': 'string',
                'minlength': 1,
                'maxlength': 10,
            },
            'job': {
                'type': 'string',
                'minlength': 1,
                'maxlength': 20,
            },
        },
    },
    'books':{},
    }
RESOURCE_METHODS = ['GET', 'POST']
ITEM_METHODS = ['GET', 'PATCH', 'PUT', 'DELETE']
X_DOMAINS = '*'
