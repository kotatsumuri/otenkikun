# coding: UTF-8
import urllib.request
from bs4 import BeautifulSoup
import re
import requests



def get_weather(url):
    if url[0]=='h':
        html = urllib.request.urlopen(url)
        soup = BeautifulSoup(html, "html.parser")

        dic=soup.find_all(class_="pict")
        string=re.split('[><]',str(dic[0]))
    else:
        string=['0']*5
        string[4]=url
    print(string[4])
    array=[]

    char_pattern=['晴','雨','曇','雪','時','の']

    for c in string[4]:
        for i in char_pattern:
            if c==i:
                array.append(c)
    status=0

    for i in range(len(array)):

        for j in range(4):
            if array[i]==char_pattern[j]:
                status=status+j*pow(4,i)

        for k in range(2):
            if array[i]==char_pattern[k+4]:
                status=status+(k+1)*4


    return status
