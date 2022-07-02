import serial
import yaml
import matplotlib.pyplot as plt

ArduinoSerial = serial.Serial("com3", 115200)
previousData = None

with open("Output.txt", "w") as text_file:
    while True:
        try:
            dataPacket = ArduinoSerial.readline()
            dataPacket = str(dataPacket, "utf-8")
            text_file.write(dataPacket)
            print(dataPacket)
            #if "time:" in dataPacket:
            #    data = yaml.safe_load("{" + dataPacket + "}")
            #    print(data)

            #    #plt.scatter(data['time'] / 1000.0, data['wz'])
            #    #if previousData is not None:
            #    #    velz = (data['yaw'] - previousData['yaw']) / ((data['time'] - previousData['time']) / 1000.0)
            #    #    plt.scatter(data['time'] / 1000.0, velz)
            #    #xlim = (data['time'] + 10) / 1000
            #    #plt.xlim((xlim - 10, xlim))
            #    #plt.pause(0.05)
            #    #previousData = data
            #else:
            #    print(dataPacket)
        except Exception as e:
            print(e)
