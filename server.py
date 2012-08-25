import serial
import time

ser = serial.Serial('/dev/tty.usbserial-A1016455', 9600)



time.sleep(5)
ser.write("TweenoLCD:CLEAR")

time.sleep(2)
ser.write("Hei verden \n")

time.sleep(2)
ser.write("Hei verden \n")

time.sleep(2)
ser.write("Hei verden \n")

time.sleep(2)
ser.write("Hei verden \n")

time.sleep(5)
ser.close()