import yaml
import matplotlib.pyplot as plt
import math

times = []
yaws = []
pitchs = []
rolls = []
wxs = []
wys = []
wzs = []

with open("Output.txt", "r") as text_file:
    lines = text_file.readlines();
    for line in lines:
        if "time:" in line:
            data = yaml.safe_load("{" + line + "}")
            times.append(data['time'] / 1000.0)
            yaws.append(data['yaw'])
            pitchs.append(data['pitch'])
            rolls.append(data['roll'])
            wxs.append(data['wx'])
            wys.append(data['wy'])
            wzs.append(data['wz'])

dwxs = []
dwys = []
dwzs = []
for i in range(1, len(times)):
    dwxs.append((rolls[i] - rolls[i-1]) / (times[i] - times[i-1]))
    dwys.append((pitchs[i] - pitchs[i-1]) / (times[i] - times[i-1]))
    dwzs.append((yaws[i] - yaws[i-1]) / (times[i] - times[i-1]))


plt.figure()
plt.plot(times, wxs)
plt.plot(times[1::], dwxs)
plt.legend(['omegaX','EulerRoll'])
plt.grid()

plt.figure()
plt.plot(times, wys)
plt.plot(times[1::], dwys)
plt.legend(['omegaY','EulerPitch'])
plt.grid()

plt.figure()
plt.plot(times, wzs)
plt.plot(times[1::], dwzs)
plt.legend(['omegaZ','EulerYaw'])
plt.grid()


plt.show()
