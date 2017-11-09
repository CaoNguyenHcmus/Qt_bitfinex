import json

from websocket import create_connection
#ws = create_connection("wss://api2.bitfinex.com:3000/ws")
ws = create_connection("wss://api.bitfinex.com/ws/2")

#ws.connect("wss://api2.bitfinex.com:3000/ws")
ws.send(json.dumps({
    "event": "subscribe",
    "channel": "ticker",
    "symbol": "tEOSUSD"
}))


while True:
    result = ws.recv()
    result = json.loads(result)
    print ("Received '%s'" % result)

ws.close()