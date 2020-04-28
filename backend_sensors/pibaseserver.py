from flask import Flask, request, redirect, session, url_for, Response, json
from flask.json import jsonify
from twilio.twiml.messaging_response import MessagingResponse
from twilio.rest import Client
import json
import os
import random
##from twilio.rest import Client
import time
import requests
from pymongo import MongoClient
from pprint import pprint
from google.cloud import datastore
import serial
import subprocess



# The session object makes use of a secret key.
SECRET_KEY = 'a secret key'
app = Flask(__name__)
app.config.from_object(__name__)



datastore_client = datastore.Client.from_service_account_json('gc.json')

with open('credentials.json', 'r') as f:
    creds = json.load(f)

mongostr = creds["mongostr"]
client = MongoClient(mongostr)

db = client["plantr"]



def getSavingsBalance(uid):
    col = db.users
    user  = col.find_one({"userid": str(uid)})
    print(user)
    oldbal = float(user["savingsbalance"])
    return oldbal



def getIoTdata():
    reading = getReading('COM12', 115200)
    ts = int(time.time())

    payload = {}

    payload ["deviceid"] = "D1"
    payload ["time"] = str(ts)
    payload ["devicetype"] = "agrisensorA"
    payload ["reading"] = reading


    print ("payload ready")
    print (payload)

    outstring = str(reading["temp"])+":"+str(reading["humid"])+":"+str(reading["light"])+":"+str(reading["water"])+":"+str(reading["soil"])
    print(outstring)

    txid = key.send([('mmRjZNRwjz3GCBfknxQpUc8SHaPgtq3Hft',0.000001,'btc')],message=outstring)
    print(txid)


    tids1 = key.get_transactions()
    tids2 = key2.get_transactions()

    print (tids1)
    print (tids2)

    result=db.readings.insert_one(payload)
    return txid


@app.route("/dummyJson", methods=['GET', 'POST'])
def dummyJson():

    print(request)

    res = request.get_json()
    print (res)

    resraw = request.get_data()
    print (resraw)

##    args = request.args
##    form = request.form
##    values = request.values

##    print (args)
##    print (form)
##    print (values)

##    sres = request.form.to_dict()
 

    status = {}
    status["server"] = "up"
    status["message"] = "some random message here"
    status["request"] = res 

    statusjson = json.dumps(status)

    print(statusjson)

    js = "<html> <body>OK THIS WoRKS</body></html>"

    resp = Response(statusjson, status=200, mimetype='application/json')
    ##resp.headers['Link'] = 'http://google.com'

    return resp


@app.route("/action", methods=['GET', 'POST'])
def action():

    print(request)

    res = request.get_json()
    print (res)

    resraw = request.get_data()
    print (resraw)

    ser = serial.Serial('/dev/ttyACM1', 115200)

    print ("connected to: " + ser.portstr)
    ser.flush()
    

    serialmsg = b''

    # args = request.args
    # form = request.form
    # values = request.values

    # print(request.args.get("type"))
    print(request.form["type"])

    if request.form["type"] == "lightoff":
        print ("lights go off")
        ser.flush()
        ser.write(b'l')
        ser.flush()
        ser.write('l')

    
    if request.form["type"] == "lighton":
        print ("lights go on")
        ser.flush()
        ser.write(b'L')
        ser.flush()
        ser.write('L')



    # print (args)
    # print (form)
    # print (values)

##    sres = request.form.to_dict()
 
    ser.close()
    status = {}
    status["server"] = "up"
    status["message"] = "some random message here"
    status["request"] = res 

    statusjson = json.dumps(status)

    print(statusjson)

    js = "<html> <body>OK THIS WoRKS</body></html>"

    resp = Response(statusjson, status=200, mimetype='application/json')
    ##resp.headers['Link'] = 'http://google.com'

    return resp




@app.route("/getData", methods=['GET', 'POST'])
def getData():

    print(request)

    subprocess.Popen("sudo python pireadings.py", shell = True)

    # res = request.get_json()
    # print (res)

    # plot = res["plot"]

    # resraw = request.get_data()
    # print (resraw)

##    args = request.args
##    form = request.form
##    values = request.values

##    print (args)
##    print (form)
##    print (values)

##    sres = request.form.to_dict()
    col = db.readings
    humids = []
    temps = []
    lights = []
    times = []
    images = []
    names = []
    moists = []
    types = []


    for x in col.find():
      print(x)
      times.append(x["lastupdate"])
      humids.append(x["humid"])
      names.append(x["name"])
      temps.append(x["temp"])
      lights.append(x["light"])
      moists.append(x["moist"])
      images.append(x["pic"])
      types.append(x["type"])

 

    status = {}
    status["server"] = "up"
    status["message"] = "some random message here"
    # status["request"] = res
    status["times"] = times
    status["humid"] = humids
    status["names"] = names
    status["temps"] = temps
    status["lights"] = lights
    status["moists"] = moists
    status["images"] = images
    status["types"] = types
    
    statusjson = json.dumps(status)

    # print(statusjson)

    js = "<html> <body>OK THIS WoRKS</body></html>"

    resp = Response(statusjson, status=200, mimetype='application/json')
    ##resp.headers['Link'] = 'http://google.com'

    return resp





@app.route("/dummy", methods=['GET', 'POST'])
def dummy():

    ##res = request.json

    js = "<html> <body>OK THIS WoRKS</body></html>"

    resp = Response(js, status=200, mimetype='text/html')
    ##resp.headers['Link'] = 'http://google.com'

    return resp


if __name__ == "__main__":
    app.run(debug=True, host = 'localhost', port = 8002)
    # app.run(debug=True, host = '52.116.36.178', port = 8001)