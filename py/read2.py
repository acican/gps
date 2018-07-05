#!/usr/bin/env python
import time
import serial
import sys
import math
import urllib
import http.client

id = 'pi-SIM'
server = 'gps.cican.ro:5055'
period = 1

ser = serial.Serial(
    port='/dev/ttyUSB0',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
)
counter=0

conn = http.client.HTTPConnection(server)


def send(conn, lat, lon):
    params = (('id', id), ('timestamp', int(time.time())), ('lat', lat), ('lon', lon))
    conn.request('GET', '?' + urllib.parse.urlencode(params))
    conn.getresponse().read()
    
def convertDegMinToDecDeg (degMin):
    min = 0.0;
    decDeg = 0.0;
    
    min, degMin = math.modf(degMin)
    decDeg = degMin + (min*100/60)
    
    return decDeg
    

while 1:
    x=ser.readline()
    print(x)
    if (len(x)>50):
        lat = float(x.decode().split(",")[1])/100
        lon = float(x.decode().split(",")[2])/100
        
        latD = convertDegMinToDecDeg (lat)
        lonD = convertDegMinToDecDeg (lon)
        
        send(conn, latD, lonD)    
    time.sleep(period)
    
    
    