#This python script merges the deterministic simulation work data for different protocol durations
#
#Steven Large
#June 11th 2018

import os

def ImportWork(Path,Filename):

	CompleteName = os.path.join(Path,Filename)

	file1 = open(CompleteName,'r')
	TempData = file1.readlines()

	Parsed = TempData[0].split()

	Time = eval(Parsed[0])
	Work = eval(Parsed[1])

	return Time,Work

def WriteWork(Path,Filename,Time,Work):

	CompleteName = os.path.join(Path,Filename)

	file1 = open(CompleteName,'w')

	for index in range(len(Time)):
		file1.write("%lf\t%lf\n" % (Time[index], Work[index]))

	file1.close()


AVals = [0,0.5,2]
Durations = [1,2,4,8,16,32,64,128,256,512]

AVals_Str = ["0","05","2"]
Durations_Str = ["1","2","4","8","16","32","64","128","256","512"]

IOPath = "ClusterData_June11"

for index1 in range(len(AVals)):

	TotalDurations = []
	TotalWork = []

	WriteName = "WorkTrend_CP1_A" + AVals_Str[index1] + "_V0.dat"

	for index2 in range(len(Durations)):

		ReadName = "WorkTrend_CP1_A" + AVals_Str[index1] + "_V0_T" + Durations_Str[index2] + ".dat"

		TempTime,TempWork = ImportWork(IOPath,ReadName)

		TotalDurations.append(TempTime)
		TotalWork.append(TempWork)

	WriteWork(IOPath,WriteName,TotalDurations,TotalWork)
	




