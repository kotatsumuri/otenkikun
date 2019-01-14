import serial,time

def write_data(ser,status):
    #print(hex(status))
    ser.write(chr(status).encode())
    #time.sleep(1);
