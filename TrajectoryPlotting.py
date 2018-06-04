#This python script plots the CPTraj file for establishment of periodic steady state
#
#Steven Large
#June 4th 2018

import os
import matplotlib.pyplot as plt
import seaborn as sns


Filename = "CPTraj.dat"

file1 = open(Filename,'r')
TempData = file1.readlines()
file1.close()

CPVal = []

for index in range(len(TempData)):
	CPVal.append(eval(TempData[index]))

plt.plot(CPVal)
plt.show()
plt.close()






