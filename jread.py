import json

def read(jsonfile,s):
    r=open(jsonfile,"r")
    dic=json.load(r)
    return str(dic[str(s)])
