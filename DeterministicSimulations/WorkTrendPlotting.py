#This script generates a plot of the excess work as a function of protocol duration from simulation data
#
#Steven Large
#June 12th 2018

import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns


def ImportWorkData(Path,Filename):

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

def ImportFriction(Path,Filename):

	CompleteName = os.path.join(Path,Filename)

	file1 = open(CompleteName,'r')
	TempData = file1.readlines()
	file1.close()

	CPVals = []
	Friction = []

	for index in range(len(TempData)):
		Parsed = TempData[index].split()

		CPVals.append(eval(Parsed[0]))
		Friction.append(eval(Parsed[1]))

	return CPVals,Friction

def CalcThermoLength(Friction,CPVals):

	dCP = CPVals[1]-CPVals[0]

	SqrtFric = []

	for index in range(len(Friction)):
		SqrtFric.append(np.sqrt(Friction[index]))

	MeanRootFric = np.mean(SqrtFric)

	return MeanRootFric*float(2)


TimeRange = []
CurrTime = 0.1
MaxTime = 1000

while CurrTime < MaxTime:
	TimeRange.append(CurrTime)
	CurrTime += 0.1

WorkHarm = []
WorkHarm_CP2 = []

for index in range(len(TimeRange)):
	WorkHarm.append(float(13.86)*float(4)/TimeRange[index])
	WorkHarm_CP2.append(float(13.86)*float(8)*float(8)/TimeRange[index])

FrictionName_A2 = "Friction_A2.dat"
FrictionName_A05 = "Friction_A05.dat"

ReadPath = "WorkData"
ReadName_A0 = "WorkTrend_A0.dat"
ReadName_A05 = "WorkTrend_A05.dat"
ReadName_A2 = "WorkTrend_A2.dat"
ReadName_A2_CP2 = "WorkTrend_A2_CP2.dat"
ReadName_A0_CP2 = "WorkTrend_A0_CP2.dat"

CPVals_A05,Friction_A05 = ImportFriction(ReadPath,FrictionName_A05)
CPVals_A2,Friction_A2 = ImportFriction(ReadPath,FrictionName_A2)

ThermoLength_A05 = CalcThermoLength(Friction_A05,CPVals_A05)
ThermoLength_A2 = CalcThermoLength(Friction_A2,CPVals_A2)

Work_A05 = []
Work_A2 = []
Work_A2_CP2 = []

for index in range(len(TimeRange)):

	Work_A05.append(ThermoLength_A05*ThermoLength_A05/TimeRange[index])
	Work_A2.append(ThermoLength_A2*ThermoLength_A2/TimeRange[index])
	Work_A2_CP2.append(4*4*ThermoLength_A2*ThermoLength_A2/TimeRange[index])

TimeSim_A0,WorkSim_A0 = ImportWorkData(ReadPath,ReadName_A0)
TimeSim_A05,WorkSim_A05 = ImportWorkData(ReadPath,ReadName_A05)
TimeSim_A2,WorkSim_A2 = ImportWorkData(ReadPath,ReadName_A2)
TimeSim_A2_CP2,WorkSim_A2_CP2 = ImportWorkData(ReadPath,ReadName_A2_CP2)
TimeSim_A0_CP2,WorkSim_A0_CP2 = ImportWorkData(ReadPath,ReadName_A0_CP2)

sns.set(style='darkgrid',palette='muted',color_codes=True)

fig,ax = plt.subplots(1,2,sharex=True,sharey=True)

ax[0].plot(TimeRange,WorkHarm,'b',linewidth=3.0,alpha=0.5,label=r"Theory: $E^{\dagger} = 0$")
ax[0].plot(TimeRange,Work_A2,'r',linewidth=3.0,alpha=0.5,label=r"Theory: $E^{\dagger} = 4$")
ax[0].plot(TimeSim_A0,WorkSim_A0,'bo',label=r"Simulation: $E^{\dagger} = 0$")
ax[0].plot(TimeSim_A2,WorkSim_A2,'ro',label=r"Simulation: $E^{\dagger} = 4$")

ax[1].plot(TimeRange,WorkHarm_CP2,'b',linewidth=3.0,alpha=0.5,label=r"Theory: $E^{\dagger} = 0$")
ax[1].plot(TimeRange,Work_A2_CP2,'r',linewidth=3.0,alpha=0.5,label=r"Theory: $E^{\dagger} = 4$")
ax[1].plot(TimeSim_A0_CP2,WorkSim_A0_CP2,'bo',label=r"Simulation: $E^{\dagger} = 0$")
ax[1].plot(TimeSim_A2_CP2,WorkSim_A2_CP2,'ro',label=r"Simulation: $E^{\dagger} = 4$")

ax[0].set_xscale('log')
ax[0].set_yscale('log')

ax[0].set_xlim([0.25,550])

ax[0].set_xlabel(r"Protocol duration $\tau$",fontsize=16)
ax[0].set_ylabel(r"Average excess work $\langle W_{\rm ex}\rangle_{\Lambda}$",fontsize=16)

ax[0].legend(loc='upper right',fontsize=14)

ax[0].set_title(r"$\Delta\lambda = 1$",fontsize=15)
ax[1].set_title(r"$\Delta\lambda = 4$",fontsize=15)

plt.show()
plt.close()








