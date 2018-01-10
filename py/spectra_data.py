import visa
import time
import datetime
import serial

rm = visa.ResourceManager()
rm.list_resources()

att = 1

#open connect
inst = rm.open_resource('USB0::0x1AB1::0x0960::DSA8A170200011::0::INSTR')
#inst = rm.open_resource('TCPIP0::192.168.0.70::80::SOCKET')
#ser = serial.Serial("COMx", 9600)

measures_file = open(time.strftime("measure/%d%m%Y %H%M%S.txt "),"w")
measures_file.write(inst.query("*IDN?"))
measures_file.write("START: " + time.strftime("%d.%m.%Y %H:%M:%S") + "\n")
measures_file.write("\n")



#start values
inst.write("DISPlay:WINdow:TRACe:Y:SCALe:RLEVel 20") # dBm

inst.write(":INPut:IMPedance 50")
inst.write(":UNIT:POWer DBM")

inst.write(":SENSe:FREQuency:STARt 430000000") #MHz
inst.write(":SENSe:FREQuency:STOP 440000000") #MHz

#uruchomienie markera nr 1
inst.write(":CALCulate:MARKer1:MODE POSition")

for i in range(3):
    
    inst.write(":TRACe1:MODE MAXHOLD")
    time.sleep(4)
    inst.write(":CALCulate:MARKer1:MAXimum:MAX")

    data_0 = inst.query(":CALCulate:MARKer1:Y?")
    data_0 = data_0.strip("\n");

    if att == 1:
        data_f = float(data_0)
        data_f += 19.96
    else:
         data_f = float(data_0)
        

   
    measures_file.write(str(data_f) +" " + time.strftime("%d.%m.%Y %H:%M:%S ") + "\t" + str(i+1) + "\n" )
    
    inst.write(":TRACe1:MODE WRITE")
    time.sleep(2)
    print("Pomiar nr" + str(i+1))


measures_file.write("\n")
measures_file.write("END:" + time.strftime("%d.%m.%Y %H:%M:%S "))
measures_file.close()
inst.close()

