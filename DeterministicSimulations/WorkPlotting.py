#This python script plots the theoretical prediction for the excess work for a harmonic trap and for a sinusoidal potential
#
#Steven Large
#June 11th 2018

import os
import matplotlib.pyplot as plt
import seaborn as sns
from math import *

def ImportFrictionData(Path,Filename):

	CompleteName = os.path.join(Path,Filename)

	file1 = open(CompleteName,'r')
	TempData = file1.readlines()
	file1.close()

	CPVal = []
	Friction = []

	for index in range(len(TempData)):
		Parsed = TempData[index].split()
		CPVals.append(eval(Parsed[0]))
		Friction.append(eval(Parsed[1]))

	return CPVals,Friction


def ImportTheoryWork(Path,Filename):

	CompleteName = os.path.join(Path,Filename)

	file1 = open(CompleteName,'r')
	TempData = file1.readlines()
	file1.close()

	Time = []
	Work = []

	for index in range(len(TempData)):
		Parsed = TempData[index].split()
		Time.append(eval(Parsed[0]))
		Work.append(eval(Parsed[1]))

	return Time,Work


def ImportWorkData(Filename):

	file1 = open(Filename,'r')
	TempData = file1.readlines()
	file1.close()

	Time = []
	Work = []

	for index in range(len(TempData)):
		Parsed = TempData[index].split()

		Time.append(eval(Parsed[0]))
		Work.append(eval(Parsed[1]))

	return Time,Work


TheoryWorkPath = "/Users/stevelarge/Research/StochasticControl/Sinusoidal_CPP/ClusterData/WorkData_June8_Full/"
FrictionPath = "/Users/stevelarge/Research/StochasticControl/Sinusoidal_CPP/ClusterData/FrictionData_May11/"

AVals = ["0","05","2"]

FrictionName_A05 = "Friction_CP2_A05_V1.dat"
FrictionName_A2 = "Friction_CP2_A2_V1.dat"

TheoryName_H = "TheoryWork_H_V1_CP3.dat"
TheoryName_A05 = "TheoryWork_A05_V1_CP3.dat"
TheoryName_A2 = "TheoryWork_A2_V1_CP3.dat"

SimName_A0 = "WorkTrend_CP1_A0_V0.dat"
SimName_A05 = "WorkTrend_CP1_A05_V0.dat"
SimName_A2 = "WorkTrend_CP1_A2_V0.dat"

##CPVals_A0,Friction_A0 = ImportFrictionData(FrictionPath,FrictionName_A0)
#CPVals_A05,Friction_A05 = ImportFrictionData(FrictionPath,FrictionName_A05)
#CPVals_A2,Friction_A2 = ImportFrictionData(FrictionPath,FrictionName_A2)

TimeTheory_A0,WorkTheory_A0 = ImportTheoryWork(TheoryWorkPath,TheoryName_H)
TimeTheory_A05,WorkTheory_A05 = ImportTheoryWork(TheoryWorkPath,TheoryName_A05)
TimeTheory_A2,WorkTheory_A2 = ImportTheoryWork(TheoryWorkPath,TheoryName_A2)

TimeSim_A0,WorkSim_A0 = ImportWorkData(SimName_A0)
TimeSim_A05,WorkSim_A05 = ImportWorkData(SimName_A05)
TimeSim_A2,WorkSim_A2 = ImportWorkData(SimName_A2)

sns.set(style='darkgrid',palette='muted',color_codes=True)

fig,ax = plt.subplots(1,1)

ax.plot(TimeTheory_A2,WorkTheory_A2,'r',linewidth=2.5,alpha=0.8,label=r"Theory: $E^{\dagger} = 2$")
ax.plot(TimeTheory_A0,WorkTheory_A0,'b',linewidth=2.5,alpha=0.8,label=r"Theory: $E^{\dagger} = 0$")
ax.plot(TimeSim_A0,WorkSim_A0,'go',label=r"Simulation: $E^{\dagger} = 2$")

ax.set_xscale('log')
ax.set_yscale('log')

ax.set_xlabel(r'Protocol Duration $\tau$',fontsize=16)
ax.set_ylabel(r'Mean excess work $\langle W_{\rm ex}\rangle_{\Lambda}$',fontsize=16)

ax.legend(loc='upper right',fontsize=14)

plt.show()
plt.close()





