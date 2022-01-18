import serial
import sys
import matplotlib.pyplot as plt

plt.ion()
xVal = 0
xVals = []
inputs = []
temps = []
targets = []
plt.show()
h1, = plt.plot(xVals, inputs)
h2, = plt.plot(xVals, temps)
h3, = plt.plot(xVals, targets)

ser = serial.Serial()
ser.baudrate = 115200
ser.port = 'COM3'
ser.open()
f = open("data.csv",'w')
while True:
    try:
        stri = ser.readline().decode("utf-8")[:-2]

        s = stri.split(",")
        xVals.append(xVal)
        inputs.append(float(s[0]))
        temps.append(float(s[1]))
        targets.append(float(s[2]))
        xVal += 1

        h1.set_xdata(xVals)
        h1.set_ydata(inputs)
        h2.set_xdata(xVals)
        h2.set_ydata(temps)
        h3.set_xdata(xVals)
        h3.set_ydata(targets)

        ax = plt.gca()
        ax.relim()
        ax.autoscale_view()
        plt.draw()
        plt.pause(1e-17)

        print(stri, file=f)
        print(stri)
    except:
        print(sys.exc_info()[0], end=' ')
        plt.close()
        f.close()
        ser.close()
        break
print("Done!")
