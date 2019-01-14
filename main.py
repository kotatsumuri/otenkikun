#!/anaconda3/bin/python3
import time
from datetime import datetime, timezone, timedelta
import wthr,wdata,jread
import serial
import os

ser=0
for file in os.listdir('/dev'):
    if "cu.usb" in file:
        ser=serial.Serial('/dev/'+str(file),115200)
time.sleep(1.5)

info_name=['place','hour','minute','light','now']
info=[]
for i in info_name:
    info.append(jread.read('info.json',str(i)))
status=wthr.get_weather(str(info[0]))
wdata.write_data(ser,status)

wdata.write_data(ser,0x40)

now =time.time()
JST = timezone(timedelta(hours=+9), 'JST')
loc = datetime.fromtimestamp(now,JST)

start_second=loc.hour*3600+loc.minute*60+loc.second

p_info=''
p_info=str(info[0])

p=0
p=int(info[4])

while True:

    now =time.time()
    JST = timezone(timedelta(hours=+9), 'JST')
    loc = datetime.fromtimestamp(now,JST)

    r=ser.readline()

    if (loc.second)%2==0:
        p_info=str(info[0])
        p=int(info[4])
        for i in range(5):
            info[i]=jread.read('info.json',str(info_name[i]))
    if (loc.hour==5 or loc.hour==11 or loc.hour==17) and loc.minute==0 and loc.second==30:
        status=wthr.get_weather(str(info[0]))
        wdata.write_data(ser,status)

    now_second=loc.hour*3600+loc.minute*60+loc.second
    light_second=int(info[1])*3600+int(info[2])*60
    s_second=light_second-600
    f_second=light_second+600

    if p_info!=str(info[0]):
        status=wthr.get_weather(str(info[0]))
        wdata.write_data(ser,status)
        wdata.write_data(ser,0x40)
        start_second=loc.hour*3600+loc.minute*60+loc.second
    elif p!=int(info[4]) and int(info[3])==0 :
        start_second=now_second-61


    if s_second<0:
        s_second=24*3600+s_second

    if f_second>24*3600:
        f_second=s_second-24*3600

    if now_second>s_second and now_second<f_second or r==b'0\r\n' or (p!=int(info[4]) and int(info[3])==1):
        wdata.write_data(ser,0x40)
        start_second=loc.hour*3600+loc.minute*60+loc.second
    if abs(now_second-start_second)>60 :
        wdata.write_data(ser,0x80)
ser.close()
