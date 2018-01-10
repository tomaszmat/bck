#granie na membrance piezo 

import time
import visa

C = 65
G = 98
E = 82
A = 110
F = 87
G  = 97
D = 73
H = 493
kot = [ G, E, E, F, D, D, C, E, G]
kot2= [ G, E, E, F, D, D, C, E, C]

hb = [G, G, A, G, C, H, G, G, A, G, D, C, G, G, G, E, C, H, A, F, F, E, C, D, C]

otdm = [ C,C,C,C,A,C,D,D,C,D,C,C,C,C,C,A,E,D,C,D,E,D,C,C,C,C,A,C,D,E,D,C,D,C ]
mnoznik = 20
mnoznik_hb = 30
volt_now = 10

time_d = 0.35

rm = visa.ResourceManager()
rm.list_resources()


inst = rm.open_resource('USB0::2391::1031::MY44030035::0::INSTR')

inst.write(":VOLT " + str(volt_now))
inst.write("OUTP ON")

for j in range(2):
    for i in range(9):
            inst.write("FREQ " + str(mnoznik*kot[i]))
            time.sleep(time_d)

    #time.sleep(0.5)

    for i in range(9):
            inst.write("FREQ " + str(mnoznik*kot2[i]))
            time.sleep(time_d)
'''
for i in range(30):
	inst.write("FREQ " + str(mnoznik_hb*otdm[i]))
	time.sleep(time_d)
'''
inst.write("OUTP OFF")

inst.close()
