# run.py
from eve import Eve
app = Eve()

@app.after_request
def after_request(response):
  response.headers.set('Access-Control-Allow-Origin', '*')
  response.headers.set('Access-Control-Allow-Headers', 'Content-Type,Authorization')
  response.headers.set('Access-Control-Allow-Methods', 'HEAD,GET,PUT,POST,DELETE,OPTIONS')
  return response

app.run()
