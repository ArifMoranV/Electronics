import time
import serial
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation


def animate (i,datalist,va,ser,ts):
    ser.write(b'g')
    line=ser.readline().decode('utf-8').strip()
    arduino_Data_string=line.split(', ')


    #af=(arduino_Data_string).float()############lista a flotante
    #va.append(af)

    arduino_float=float(arduino_Data_string[1])
    tn=float(arduino_Data_string[0])
    ts.append(tn)
    datalist.append(arduino_float)
   
    ax.clear()
    plt.xlabel('Segundos')
    plt.tight_layout()
    plt.grid('on')  
    #print(ts)
    ##ts=np.arange(0,len(datalist),1)
    ax.plot(ts,datalist,color='black')
    ##return ts,datalist
    #plt.show()


datalist = []   
va=[]
ts=[]
fig=plt.figure(figsize=(10,7))
ax=fig.add_subplot(111)

ser=serial.Serial("COM5",baudrate=9600)
time.sleep(2)

ani=animation.FuncAnimation(fig,animate,frames=100,fargs=(datalist,va,ser,ts),interval=100)

plt.show()                                              # Keep Matplotlib plot persistent on screen until it is closed
ser.close()  