#!/usr/bin/env python

import os

def WriteParameterFile(AVal,CPDist,Var,Filename):

	file1 = open('Parameters.dat','w')

	file1.write('0.87055\n')
	file1.write('0.01\n')
	file1.write('1.0\n')
	file1.write('4.0\n')
	file1.write('1.0\n')
	file1.write('%lf\n' % AVal)
	file1.write('%lf\n' % CPDist)
	file1.write('%lf\n' % Var)
	file1.write('%s\n' % Filename) 


#AVals = [0,0.25,0.5,1,2]
AVals = [1]
#CPDist = [1,4,16]
CPDist = [1,4]
Var = [0.036,0.144,0.577,2.308]

for index1 in range(len(AVals)):

	for index2 in range(len(CPDist)):

		for index3 in range(len(Var)):

			os.system("echo Running File")

			WriteName = "WorkTrend3_CP" + str(index2+1) + "_A" + str(AVals[index1]) + "_V" + str(Var[index3]) + ".dat"

			WriteParameterFile(AVals[index1],CPDist[index2],Var[index3],WriteName)

			os.system('make clean')
			os.system('make clean_ex')
			os.system('make')
			os.system('./StochControl.exe')


os.system('echo')
os.system('echo')
os.system('echo ----- Finished Calculations -----')
os.system('echo')
os.system('echo')



