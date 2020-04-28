import serial
from pymongo import MongoClient
import json
from google.cloud import datastore
import sys
import time

datastore_client = datastore.Client.from_service_account_json('gc.json')

with open('credentials.json', 'r') as f:
    creds = json.load(f)

mongostr = creds["mongostr"]
client = MongoClient(mongostr)

db = client["plantr"]

kind = 'readings'


def put_readings(name, plantType, temp, humid, light, moist, imgurl):
    

    t = str(int(time.time()))
    user_key = datastore_client.key(kind, name + "-" + t)

    user = datastore.Entity(key = user_key)
    user['name'] = name
    user['type'] = plantType
    user['temp'] = temp
    user['humid'] = humid
    user['light'] = light
    user['moist'] = moist
    user['lastupdate'] = t
    user['pic'] = imgurl

    datastore_client.put(user)

    print('Saved to google cloud -- {}: {} {}'.format(user.key.name, user['name'], user['pic']))

    payload = {}

    payload ["name"] = name
    payload['type'] = plantType
    payload['temp'] = temp
    payload['humid'] = humid
    payload['light'] = light
    payload['moist'] = moist
    payload['lastupdate'] = t
    payload['pic'] = imgurl


    print ("payload ready")
    print (payload)
    result=db.readings.insert_one(payload)
    print (result)



# ser = serial.Serial('/dev/ttyACM0', 115200)

ser = serial.Serial('COM30', 115200)


# ser2 = serial.Serial('/dev/ttyACM1', 115200)

print ("connected to: " + ser.portstr)
# print ("connected to: " + ser2.portstr)


while True:
    line = ser.readline()
    print("read a line")
    line = line.strip()
    line=line.decode()
    if line.startswith("#"):
        line = line[2:]
    if line.endswith("#"):
        line = line[:-2]
        print (line)
        words = line.split(":")
        light = float(words[1])
        temp = float(words[2])
        humid = float(words[3])
        moist = float(words[4])
        print (light)
        print (temp)
        print (humid)
        print (moist)

        put_readings('plot1', 'fittonia', temp, humid, light, moist, 'https://storage.googleapis.com/plantsx/plot1default.jpg')

        put_readings('plot2', 'peperomia', temp, humid, light, moist, 'https://storage.googleapis.com/plantsx/plot2default.jpg')


    else:
        continue
        
    print(line)




ser.close()
