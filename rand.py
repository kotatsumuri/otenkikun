import random
import time
import sys
while True:
    for i in range(208):
        print(chr(random.randint(33,126)),end="")
        print("\r")
    sys.stdout.flush()
    time.sleep(0.05)
