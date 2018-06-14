#This python script plots control parameter and position trajectories for realizations of the same control protocol
#
#Steven Large
#June 12th 2018

import os
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np


def ImportTrajectoryData(Path,Filename):

	CompleteName = os.path.join(Path,Filename)

	file1 = open(CompleteName,'r')
	TempData = file1.readlines()
	file1.close()

	Time = []
	Data = []

	for index in range(len(TempData)):
		Parsed = TempData[index].split()

		if(eval(Parsed[0]) < 0.005):
			break
		else:
			Time.append(eval(Parsed[0]))
			Data.append(eval(Parsed[1]))

	return Time,Data


ProtocolDurations = [0.5,1,2,4,8,16,32,64,128,256,512]

CPName_Base = "CPTraj_T"
PosName_Base = "PosTraj_T"

ReadPath = "TrajData"
WritePath = "Plots"

sns.set(style='darkgrid',palette='muted',color_codes=True)

CPName_1 = CPName_Base + "0.500000_"
CPName_2 = CPName_Base + "1.000000_"
CPName_3 = CPName_Base + "2.000000_"
CPName_4 = CPName_Base + "4.000000_"
CPName_5 = CPName_Base + "8.000000_"
CPName_6 = CPName_Base + "16.000000_"
CPName_7 = CPName_Base + "32.000000_"
CPName_8 = CPName_Base + "64.000000_"
CPName_9 = CPName_Base + "128.000000_"
CPName_10 = CPName_Base + "256.000000_"
CPName_11 = CPName_Base + "512.000000_"

PosName_1 = PosName_Base + "0.500000_"
PosName_2 = PosName_Base + "1.000000_"
PosName_3 = PosName_Base + "2.000000_"
PosName_4 = PosName_Base + "4.000000_"
PosName_5 = PosName_Base + "8.000000_"
PosName_6 = PosName_Base + "16.000000_"
PosName_7 = PosName_Base + "32.000000_"
PosName_8 = PosName_Base + "64.000000_"
PosName_9 = PosName_Base + "128.000000_"
PosName_10 = PosName_Base + "256.000000_"
PosName_11 = PosName_Base + "512.000000_"


fig,ax = plt.subplots(2,5,sharey=True)

for index in range(10):

	Filename_CP_1 = CPName_1 + str(index) + ".dat"
	Filename_CP_2 = CPName_2 + str(index) + ".dat"
	Filename_CP_3 = CPName_3 + str(index) + ".dat"
	Filename_CP_4 = CPName_4 + str(index) + ".dat"
	Filename_CP_5 = CPName_5 + str(index) + ".dat"
	Filename_CP_6 = CPName_6 + str(index) + ".dat"
	Filename_CP_7 = CPName_7 + str(index) + ".dat"
	Filename_CP_8 = CPName_8 + str(index) + ".dat"
	Filename_CP_9 = CPName_9 + str(index) + ".dat"
	Filename_CP_10 = CPName_10 + str(index) + ".dat"
	Filename_CP_11 = CPName_11 + str(index) + ".dat"

	Filename_Pos_1 = PosName_1 + str(index) + ".dat"
	Filename_Pos_2 = PosName_2 + str(index) + ".dat"
	Filename_Pos_3 = PosName_3 + str(index) + ".dat"
	Filename_Pos_4 = PosName_4 + str(index) + ".dat"
	Filename_Pos_5 = PosName_5 + str(index) + ".dat"
	Filename_Pos_6 = PosName_6 + str(index) + ".dat"
	Filename_Pos_7 = PosName_7 + str(index) + ".dat"
	Filename_Pos_8 = PosName_8 + str(index) + ".dat"
	Filename_Pos_9 = PosName_9 + str(index) + ".dat"
	Filename_Pos_10 = PosName_10 + str(index) + ".dat"
	Filename_Pos_11 = PosName_11 + str(index) + ".dat"

	CPTime_1,CPData_1 = ImportTrajectoryData(ReadPath,Filename_CP_1)
	CPTime_2,CPData_2 = ImportTrajectoryData(ReadPath,Filename_CP_2)
	CPTime_3,CPData_3 = ImportTrajectoryData(ReadPath,Filename_CP_3)
	CPTime_4,CPData_4 = ImportTrajectoryData(ReadPath,Filename_CP_4)
	CPTime_5,CPData_5 = ImportTrajectoryData(ReadPath,Filename_CP_5)
	CPTime_6,CPData_6 = ImportTrajectoryData(ReadPath,Filename_CP_6)
	CPTime_7,CPData_7 = ImportTrajectoryData(ReadPath,Filename_CP_7)
	CPTime_8,CPData_8 = ImportTrajectoryData(ReadPath,Filename_CP_8)
	CPTime_9,CPData_9 = ImportTrajectoryData(ReadPath,Filename_CP_9)
	CPTime_10,CPData_10 = ImportTrajectoryData(ReadPath,Filename_CP_10)
	CPTime_11,CPData_11 = ImportTrajectoryData(ReadPath,Filename_CP_11)

	PosTime_1,PosData_1 = ImportTrajectoryData(ReadPath,Filename_Pos_1)
	PosTime_2,PosData_2 = ImportTrajectoryData(ReadPath,Filename_Pos_2)
	PosTime_3,PosData_3 = ImportTrajectoryData(ReadPath,Filename_Pos_3)
	PosTime_4,PosData_4 = ImportTrajectoryData(ReadPath,Filename_Pos_4)
	PosTime_5,PosData_5 = ImportTrajectoryData(ReadPath,Filename_Pos_5)
	PosTime_6,PosData_6 = ImportTrajectoryData(ReadPath,Filename_Pos_6)
	PosTime_7,PosData_7 = ImportTrajectoryData(ReadPath,Filename_Pos_7)
	PosTime_8,PosData_8 = ImportTrajectoryData(ReadPath,Filename_Pos_8)
	PosTime_9,PosData_9 = ImportTrajectoryData(ReadPath,Filename_Pos_9)
	PosTime_10,PosData_10 = ImportTrajectoryData(ReadPath,Filename_Pos_10)
	PosTime_11,PosData_11 = ImportTrajectoryData(ReadPath,Filename_Pos_11)

	ax[0,0].plot(CPTime_2,CPData_2,'k',linewidth=2.5,alpha=0.5)
	ax[0,1].plot(CPTime_3,CPData_3,'k',linewidth=2.5,alpha=0.5)
	ax[0,2].plot(CPTime_4,CPData_4,'k',linewidth=2.5,alpha=0.5)
	ax[0,3].plot(CPTime_5,CPData_5,'k',linewidth=2.5,alpha=0.5)
	ax[0,4].plot(CPTime_6,CPData_6,'k',linewidth=2.5,alpha=0.5)
	ax[1,0].plot(CPTime_7,CPData_7,'k',linewidth=2.5,alpha=0.5)
	ax[1,1].plot(CPTime_8,CPData_8,'k',linewidth=2.5,alpha=0.5)
	ax[1,2].plot(CPTime_9,CPData_9,'k',linewidth=2.5,alpha=0.5)
	ax[1,3].plot(CPTime_10,CPData_10,'k',linewidth=2.5,alpha=0.5)
	ax[1,4].plot(CPTime_11,CPData_11,'k',linewidth=2.5,alpha=0.5)

	ax[0,0].plot(PosTime_2,PosData_2,linewidth=2.5,alpha=0.5)
	ax[0,1].plot(PosTime_3,PosData_3,linewidth=2.5,alpha=0.5)
	ax[0,2].plot(PosTime_4,PosData_4,linewidth=2.5,alpha=0.5)
	ax[0,3].plot(PosTime_5,PosData_5,linewidth=2.5,alpha=0.5)
	ax[0,4].plot(PosTime_6,PosData_6,linewidth=2.5,alpha=0.5)
	ax[1,0].plot(PosTime_7,PosData_7,linewidth=2.5,alpha=0.5)
	ax[1,1].plot(PosTime_8,PosData_8,linewidth=2.5,alpha=0.5)
	ax[1,2].plot(PosTime_9,PosData_9,linewidth=2.5,alpha=0.5)
	ax[1,3].plot(PosTime_10,PosData_10,linewidth=2.5,alpha=0.5)
	ax[1,4].plot(PosTime_11,PosData_11,linewidth=2.5,alpha=0.5)


ax[0,0].set_title(r"$\tau = 1$",fontsize=15)
ax[0,1].set_title(r"$\tau = 2$",fontsize=15)
ax[0,2].set_title(r"$\tau = 4$",fontsize=15)
ax[0,3].set_title(r"$\tau = 8$",fontsize=15)
ax[0,4].set_title(r"$\tau = 16$",fontsize=15)

ax[1,0].set_title(r"$\tau = 32$",fontsize=15)
ax[1,1].set_title(r"$\tau = 64$",fontsize=15)
ax[1,2].set_title(r"$\tau = 128$",fontsize=15)
ax[1,3].set_title(r"$\tau = 256$",fontsize=15)
ax[1,4].set_title(r"$\tau = 512$",fontsize=15)

ax[1,0].set_xlabel(r"Protocol duration $\tau$",fontsize=16)
ax[1,0].set_ylabel(r"Mean excess work $\langle W_{\rm ex}\rangle_{\Lambda}$",fontsize=16)


plt.show()
plt.close()		



