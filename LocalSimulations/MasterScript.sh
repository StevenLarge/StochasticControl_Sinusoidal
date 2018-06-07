#!/usr/bin/env python

import os

def ParameterFileWrite(AVal,CPDist,VelVar,WriteName):

	file1 = open("Parameters.dat",'w')

	file1.write("0.93303\n")
	file1.write("0.005\n")
	file1.write("1.0\n")
	file1.write("4.0\n")
	file1.write("1.0\n")
	file1.write("%lf\n" % AVal)
	file1.write("%lf\n" % CPDist)
	file1.write("%lf\n" % VelVar)
	file1.write(WriteName)


#AVals = [0.5,1,2]
#AVals_Str = ["05","1","2"]

AVals = [0.5,2]
AVals_Str = ["05","2"]

CPDist = [1.0,4.0,16.0]
CPDist_Str = ["1","2","3"]

VelVar = [0.036,0.144,0.577,2.308]
VelVar_Str = ["025","1","4","16"]

for index1 in range(len(AVals)):

	for index2 in range(len(CPDist)):

		for index3 in range(len(VelVar)):

			os.system("echo ----")

			WriteName = "WorkData_June5_Short2/WorkTrend_CP" + CPDist_Str[index2] + "_A" + AVals_Str[index1] + "_V" + VelVar_Str[index3] + ".dat"
			ParameterFileWrite(AVals[index1],CPDist[index2],VelVar[index3],WriteName)

			os.system("./Stoch*.exe")



