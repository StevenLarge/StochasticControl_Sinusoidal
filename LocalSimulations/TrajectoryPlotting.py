#This python script plots CP and trajectory data for the periodic potential driving protocols
#
#Steven Large
#June 6th 2018

import os
import numpy as np
from math import *
import matplotlib.pyplot as plt
import seaborn as sns


def ReadTrajData(Path,Filename):

	CompleteName = os.path.join(Path,Filename)

	file1 = open(CompleteName,'r')
	TempData = file1.readlines()
	file1.close()

	Time = []
	CP = []
	Position = []

	for index in range(len(TempData)):
		Parsed = TempData[index].split()

		Time.append(eval(Parsed[0]))
		CP.append(eval(Parsed[1]))
		Position.append(eval(Parsed[2]))

	return Time,CP,Position


ReadPath = "TrajData"

Filename_Eq1 = "Traj_Equil_Vel2.000000_0.dat"
Filename_Eq2 = "Traj_Equil_Vel2.000000_1.dat"
Filename_Eq3 = "Traj_Equil_Vel2.000000_2.dat"
Filename_Eq4 = "Traj_Equil_Vel2.000000_3.dat"
Filename_Eq5 = "Traj_Equil_Vel2.000000_4.dat"

Filename_Dyn1 = "Traj_Dynamic_Vel2.000000_0.dat"
Filename_Dyn2 = "Traj_Dynamic_Vel2.000000_1.dat"
Filename_Dyn3 = "Traj_Dynamic_Vel2.000000_2.dat"
Filename_Dyn4 = "Traj_Dynamic_Vel2.000000_3.dat"
Filename_Dyn5 = "Traj_Dynamic_Vel2.000000_4.dat"


Time_Eq1,CP_Eq1,Position_Eq1 = ReadTrajData(ReadPath,Filename_Eq1)
Time_Eq2,CP_Eq2,Position_Eq2 = ReadTrajData(ReadPath,Filename_Eq2)
Time_Eq3,CP_Eq3,Position_Eq3 = ReadTrajData(ReadPath,Filename_Eq3)
Time_Eq4,CP_Eq4,Position_Eq4 = ReadTrajData(ReadPath,Filename_Eq4)
Time_Eq5,CP_Eq5,Position_Eq5 = ReadTrajData(ReadPath,Filename_Eq5)

Time_Dyn1,CP_Dyn1,Position_Dyn1 = ReadTrajData(ReadPath,Filename_Dyn1)
Time_Dyn2,CP_Dyn2,Position_Dyn2 = ReadTrajData(ReadPath,Filename_Dyn2)
Time_Dyn3,CP_Dyn3,Position_Dyn3 = ReadTrajData(ReadPath,Filename_Dyn3)
Time_Dyn4,CP_Dyn4,Position_Dyn4 = ReadTrajData(ReadPath,Filename_Dyn4)
Time_Dyn5,CP_Dyn5,Position_Dyn5 = ReadTrajData(ReadPath,Filename_Dyn5)


sns.set(style="darkgrid",palette="muted",color_codes=True)

fig,ax = plt.subplots(2,2)

ax[0,0].plot(Time_Eq1,CP_Eq1,linewidth=1.5,alpha=0.6,label="1")
ax[0,0].plot(Time_Eq2,CP_Eq2,linewidth=1.5,alpha=0.6,label="2")
ax[0,0].plot(Time_Eq3,CP_Eq3,linewidth=1.5,alpha=0.6,label="3")
ax[0,0].plot(Time_Eq4,CP_Eq4,linewidth=1.5,alpha=0.6,label="4")
ax[0,0].plot(Time_Eq5,CP_Eq5,linewidth=1.5,alpha=0.6,label="5")

ax[1,0].plot(Time_Eq1,Position_Eq1,linewidth=1.5,alpha=0.6,label="1")
ax[1,0].plot(Time_Eq2,Position_Eq2,linewidth=1.5,alpha=0.6,label="2")
ax[1,0].plot(Time_Eq3,Position_Eq3,linewidth=1.5,alpha=0.6,label="3")
ax[1,0].plot(Time_Eq4,Position_Eq4,linewidth=1.5,alpha=0.6,label="4")
ax[1,0].plot(Time_Eq5,Position_Eq5,linewidth=1.5,alpha=0.6,label="5")


ax[0,1].plot(Time_Dyn1,CP_Dyn1,linewidth=1.5,alpha=0.6,label="1")
ax[0,1].plot(Time_Dyn2,CP_Dyn2,linewidth=1.5,alpha=0.6,label="2")
ax[0,1].plot(Time_Dyn3,CP_Dyn3,linewidth=1.5,alpha=0.6,label="3")
ax[0,1].plot(Time_Dyn4,CP_Dyn4,linewidth=1.5,alpha=0.6,label="4")
ax[0,1].plot(Time_Dyn5,CP_Dyn5,linewidth=1.5,alpha=0.6,label="5")

ax[1,1].plot(Time_Dyn1,Position_Dyn1,linewidth=1.5,alpha=0.6,label="1")
ax[1,1].plot(Time_Dyn2,Position_Dyn2,linewidth=1.5,alpha=0.6,label="2")
ax[1,1].plot(Time_Dyn3,Position_Dyn3,linewidth=1.5,alpha=0.6,label="3")
ax[1,1].plot(Time_Dyn4,Position_Dyn4,linewidth=1.5,alpha=0.6,label="4")
ax[1,1].plot(Time_Dyn5,Position_Dyn5,linewidth=1.5,alpha=0.6,label="5")

ax[0,0].legend(loc='upper left')
ax[0,1].legend(loc='upper left')
ax[1,0].legend(loc='upper left')
ax[1,1].legend(loc='upper left')

plt.show()
plt.close()



