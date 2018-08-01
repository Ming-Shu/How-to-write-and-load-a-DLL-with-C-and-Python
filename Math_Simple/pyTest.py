from ctypes import *
import os
mydll = cdll.LoadLibrary("c:\\pythondll.dll")

mydll.sum(5,25)

mydll.mult(4,12)

mydll.sentMessage()

print(mydll.mult(3,12))

os.system("pause")
