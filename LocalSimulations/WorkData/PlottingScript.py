#This python script plots the series of numerical data compared to the corresponding theory curves
#as a function of the equilibration time and the number of iterations
#
#Steven Large
#May 28th 2018

import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

def ReadWorkData(Filename):

	file1 = open(Filename,'r')
	TempData = file1.readlines()
	file1.close()

	Times = []
	Work = []

	for index in range(len(TempData)):
		Parsed = TempData[index].split()

		Times.append(eval(Parsed[0]))
		Work.append(eval(Parsed[1]))

	return Times,Work


def ReadTheoryData(Path,Filename):

	CompleteName = os.path.join(Path,Filename)

	file1 = open(CompleteName,'r')
	TempData = file1.readlines()
	file1.close()

	Times = []
	Work = []

	for index in range(len(TempData)):
		Parsed = TempData[index].split()

		Times.append(eval(Parsed[0]))
		Work.append(eval(Parsed[3]))

	return Times,Work


Filename_Eq0_Iter1000_A1 = "WorkTrend_Eq0_Iter1000_CP4_A1.dat"
Filename_Eq10_Iter1000_A1 = "WorkTrend_Eq10_Iter1000_CP4_A1.dat"
Filename_Eq100_Iter1000_A1 = "WorkTrend_Eq100_Iter1000_CP4_A1.dat"
Filename_Eq500_Iter1000_A1 = "WorkTrend_Eq500_Iter1000_CP4_A1.dat"

Filename_Eq0_Iter2000_A1 = "WorkTrend_Eq0_Iter2000_CP4_A1.dat"
Filename_Eq10_Iter2000_A1 = "WorkTrend_Eq10_Iter2000_CP4_A1.dat"
Filename_Eq100_Iter2000_A1 = "WorkTrend_Eq100_Iter2000_CP4_A1.dat"
Filename_Eq500_Iter2000_A1 = "WorkTrend_Eq500_Iter2000_CP4_A1.dat"

Filename_Eq0_Iter5000_A1 = "WorkTrend_Eq0_Iter5000_CP4_A1.dat"
Filename_Eq10_Iter5000_A1 = "WorkTrend_Eq10_Iter5000_CP4_A1.dat"
Filename_Eq100_Iter5000_A1 = "WorkTrend_Eq100_Iter5000_CP4_A1.dat"
Filename_Eq500_Iter5000_A1 = "WorkTrend_Eq500_Iter5000_CP4_A1.dat"



Filename_Eq0_Iter1000_A2 = "WorkTrend_Eq0_Iter1000_CP4_A2.dat"
Filename_Eq10_Iter1000_A2 = "WorkTrend_Eq10_Iter1000_CP4_A2.dat"
Filename_Eq100_Iter1000_A2 = "WorkTrend_Eq100_Iter1000_CP4_A2.dat"
Filename_Eq500_Iter1000_A2 = "WorkTrend_Eq500_Iter1000_CP4_A2.dat"

Filename_Eq0_Iter2000_A2 = "WorkTrend_Eq0_Iter2000_CP4_A2.dat"
Filename_Eq10_Iter2000_A2 = "WorkTrend_Eq10_Iter2000_CP4_A2.dat"
Filename_Eq100_Iter2000_A2 = "WorkTrend_Eq100_Iter2000_CP4_A2.dat"
Filename_Eq500_Iter2000_A2 = "WorkTrend_Eq500_Iter2000_CP4_A2.dat"

Filename_Eq0_Iter5000_A2 = "WorkTrend_Eq0_Iter5000_CP4_A2.dat"
Filename_Eq10_Iter5000_A2 = "WorkTrend_Eq10_Iter5000_CP4_A2.dat"
Filename_Eq100_Iter5000_A2 = "WorkTrend_Eq100_Iter5000_CP4_A2.dat"
Filename_Eq500_Iter5000_A2 = "WorkTrend_Eq500_Iter5000_CP4_A2.dat"

TheoryPath = "/Users/stevelarge/Research/StochasticControl/Sinusoidal_CPP/ClusterData/WorkData_May27_Full/"

TheoryName_1 = "TheoryWork_A1_V1_CP2.dat"
TheoryName_2 = "TheoryWork_A2_V1_CP2.dat"


TimeTheory_1,WorkTheory_1 = ReadTheoryData(TheoryPath,TheoryName_1)
TimeTheory_2,WorkTheory_2 = ReadTheoryData(TheoryPath,TheoryName_2)


Time_Sim_0_1000_1, Work_Sim_0_1000_1 = ReadWorkData(Filename_Eq0_Iter1000_A1)
Time_Sim_10_1000_1, Work_Sim_10_1000_1 = ReadWorkData(Filename_Eq10_Iter1000_A1)
Time_Sim_100_1000_1, Work_Sim_100_1000_1 = ReadWorkData(Filename_Eq100_Iter1000_A1)
Time_Sim_500_1000_1, Work_Sim_500_1000_1 = ReadWorkData(Filename_Eq500_Iter1000_A1)

Time_Sim_0_2000_1, Work_Sim_0_2000_1 = ReadWorkData(Filename_Eq0_Iter2000_A1)
Time_Sim_10_2000_1, Work_Sim_10_2000_1 = ReadWorkData(Filename_Eq10_Iter2000_A1)
Time_Sim_100_2000_1, Work_Sim_100_2000_1 = ReadWorkData(Filename_Eq100_Iter2000_A1)
Time_Sim_500_2000_1, Work_Sim_500_2000_1 = ReadWorkData(Filename_Eq500_Iter2000_A1)

Time_Sim_0_5000_1, Work_Sim_0_5000_1 = ReadWorkData(Filename_Eq0_Iter5000_A1)
Time_Sim_10_5000_1, Work_Sim_10_5000_1 = ReadWorkData(Filename_Eq10_Iter5000_A1)
Time_Sim_100_5000_1, Work_Sim_100_5000_1 = ReadWorkData(Filename_Eq100_Iter5000_A1)
Time_Sim_500_5000_1, Work_Sim_500_5000_1 = ReadWorkData(Filename_Eq500_Iter5000_A1)



Time_Sim_0_1000_2, Work_Sim_0_1000_2 = ReadWorkData(Filename_Eq0_Iter1000_A2)
Time_Sim_10_1000_2, Work_Sim_10_1000_2 = ReadWorkData(Filename_Eq10_Iter1000_A2)
Time_Sim_100_1000_2, Work_Sim_100_1000_2 = ReadWorkData(Filename_Eq100_Iter1000_A2)
Time_Sim_500_1000_2, Work_Sim_500_1000_2 = ReadWorkData(Filename_Eq500_Iter1000_A2)

Time_Sim_0_2000_2, Work_Sim_0_2000_2 = ReadWorkData(Filename_Eq0_Iter2000_A2)
Time_Sim_10_2000_2, Work_Sim_10_2000_2 = ReadWorkData(Filename_Eq10_Iter2000_A2)
Time_Sim_100_2000_2, Work_Sim_100_2000_2 = ReadWorkData(Filename_Eq100_Iter2000_A2)
Time_Sim_500_2000_2, Work_Sim_500_2000_2 = ReadWorkData(Filename_Eq500_Iter2000_A2)

Time_Sim_0_5000_2, Work_Sim_0_5000_2 = ReadWorkData(Filename_Eq0_Iter5000_A2)
Time_Sim_10_5000_2, Work_Sim_10_5000_2 = ReadWorkData(Filename_Eq10_Iter5000_A2)
Time_Sim_100_5000_2, Work_Sim_100_5000_2 = ReadWorkData(Filename_Eq100_Iter5000_A2)
Time_Sim_500_5000_2, Work_Sim_500_5000_2 = ReadWorkData(Filename_Eq500_Iter5000_A2)


sns.set(style='darkgrid',palette="muted",color_codes=True)

fig,ax = plt.subplots(2,3,sharex=True,sharey=True)

ax[0,0].plot(TimeTheory_1,WorkTheory_1,'k',linewidth=2.5,alpha=0.5)
ax[0,1].plot(TimeTheory_1,WorkTheory_1,'k',linewidth=2.5,alpha=0.5)
ax[0,2].plot(TimeTheory_1,WorkTheory_1,'k',linewidth=2.5,alpha=0.5)

ax[0,0].plot(Time_Sim_0_1000_1,Work_Sim_0_1000_1,'ro',label="Eq = 0")
ax[0,0].plot(Time_Sim_10_1000_1,Work_Sim_10_1000_1,'go',label="Eq = 10")
ax[0,0].plot(Time_Sim_100_1000_1,Work_Sim_100_1000_1,'bo',label="Eq = 100")
ax[0,0].plot(Time_Sim_500_1000_1,Work_Sim_500_1000_1,'mo',label="Eq = 500")

ax[0,1].plot(Time_Sim_0_2000_1,Work_Sim_0_2000_1,'ro',label="Eq = 0")
ax[0,1].plot(Time_Sim_10_2000_1,Work_Sim_10_2000_1,'go',label="Eq = 10")
ax[0,1].plot(Time_Sim_100_2000_1,Work_Sim_100_2000_1,'bo',label="Eq = 100")
ax[0,1].plot(Time_Sim_500_2000_1,Work_Sim_500_2000_1,'mo',label="Eq = 500")

ax[0,2].plot(Time_Sim_0_5000_1,Work_Sim_0_5000_1,'ro',label="Eq = 0")
ax[0,2].plot(Time_Sim_10_5000_1,Work_Sim_10_5000_1,'go',label="Eq = 10")
ax[0,2].plot(Time_Sim_100_5000_1,Work_Sim_100_5000_1,'bo',label="Eq = 100")
ax[0,2].plot(Time_Sim_500_5000_1,Work_Sim_500_5000_1,'mo',label="Eq = 500")


ax[1,0].plot(TimeTheory_2,WorkTheory_2,'k',linewidth=2.5,alpha=0.5)
ax[1,1].plot(TimeTheory_2,WorkTheory_2,'k',linewidth=2.5,alpha=0.5)
ax[1,2].plot(TimeTheory_2,WorkTheory_2,'k',linewidth=2.5,alpha=0.5)

ax[1,0].plot(Time_Sim_0_1000_2,Work_Sim_0_1000_2,'ro',label="Eq = 0")
ax[1,0].plot(Time_Sim_10_1000_2,Work_Sim_10_1000_2,'go',label="Eq = 10")
ax[1,0].plot(Time_Sim_100_1000_2,Work_Sim_100_1000_2,'bo',label="Eq = 100")
ax[1,0].plot(Time_Sim_500_1000_2,Work_Sim_500_1000_2,'mo',label="Eq = 500")

ax[1,1].plot(Time_Sim_0_2000_2,Work_Sim_0_2000_2,'ro',label="Eq = 0")
ax[1,1].plot(Time_Sim_10_2000_2,Work_Sim_10_2000_2,'go',label="Eq = 10")
ax[1,1].plot(Time_Sim_100_2000_2,Work_Sim_100_2000_2,'bo',label="Eq = 100")
ax[1,1].plot(Time_Sim_500_2000_2,Work_Sim_500_2000_2,'mo',label="Eq = 500")

ax[1,2].plot(Time_Sim_0_5000_2,Work_Sim_0_5000_2,'ro',label="Eq = 0")
ax[1,2].plot(Time_Sim_10_5000_2,Work_Sim_10_5000_2,'go',label="Eq = 10")
ax[1,2].plot(Time_Sim_100_5000_2,Work_Sim_100_5000_2,'bo',label="Eq = 100")
ax[1,2].plot(Time_Sim_500_5000_2,Work_Sim_500_5000_2,'mo',label="Eq = 500")


ax[0,0].legend(loc='upper center',fontsize=12)
ax[0,1].legend(loc='upper center',fontsize=12)
ax[0,2].legend(loc='upper center',fontsize=12)

ax[1,0].legend(loc='upper center',fontsize=12)
ax[1,1].legend(loc='upper center',fontsize=12)
ax[1,2].legend(loc='upper center',fontsize=12)

ax[1,0].set_xlabel(r'Protocol duration $\tau$',fontsize=14)
ax[1,0].set_ylabel(r'Meamn excess work $\langle W_{\rm ex}\rangle_{\Lambda}$',fontsize=14)

ax[0,0].set_title(r'Iteration2 = 1000',fontsize=14)
ax[0,1].set_title(r'Iterations = 2000',fontsize=14)
ax[0,2].set_title(r'Iterations = 5000',fontsize=14)

ax[0,0].set_xscale('log')
ax[0,0].set_yscale('log')

plt.show()
plt.close()







