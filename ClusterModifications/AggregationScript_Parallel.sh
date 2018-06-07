#!/usr/bin/env python

import os

def AggregateDurations(ProtocolDuration_Str,VelVar,AVals,CPDist):

	Time = []
	Work = []

	for index5 in range(len(ProtocolDuration_Str)):
		Filename = "AggregateData/WorkTrend_CP" + str(CPDist) + "_A" + AVals + "_V" + VelVar + "_T" + ProtocolDuration_Str[index5] + ".dat"

		file1 = open(Filename,'r')
		Data = readlines()
		file1.close()
		Parsed = Data[0].split()
		Time.append(eval(Parsed[0]))
		Work.append(eval(Parsed[1]))

	WriteName = "AggregateData/WorkTrendAgg_CP" + str(CPDist) + "_A" + AVals + "_V" + VelVar + ".dat"

	file2 = open(WriteName,'w')
	for index6 in range(len(Time)):
		file2.write("%lf\t%lf\n" % (Time[index6], Work[index6]))
	file2.close()


AVals = [0.5,1,2]
AVals_Str = ["05","1","2"]

CPDist = [3.14,6.28,12.56]

VelVar = [0.25,1,4,16]
VelVar_Str = ["025","1","4","16"]

ProtocolDuration = [4,8,16,32,64,128,256,512]
ProtocolDuration_Str = ["4","8","16","32","64","128","256","512"]

if(os.path.exists("AggregateData")==False):
	os.mkdir("AggregateData")

MissingFiles = []

for index1 in range(len(CPDist)):
	for index2 in range(len(AVals)):
		for index3 in range(len(VelVar)):
			for index4 in range(len(ProtocolDuration)):

				TargetFileWork = "CPDist_" + str(index1+1) + "/A_" + AVals_Str[index2] + "/Var_" + VelVar_Str[index3] + "/T_" + ProtocolDuration_Str[index4] + "/WorkData/WorkTrend.dat"

				if(os.path.exists(TargetFileWork)==False):
					MissingFiles.append(TargetFileWork)
				else:
					CopyCommand =  "cp " + TargetFileWork + " AggregateData"
					RenameCommand = "mv AggregateData/WorkTrend.dat AggregateData/WorkTrend_CP" + str(index1+1) + "_A" + AVals_Str[index2] + "_V" + VelVar_Str[index3] + "_T" + ProtocolDuration_Str[index4] + ".dat"
					os.system(CopyCommand)
					os.system(RenameCommand)

			AggregateDurations(ProtocolDuration_Str,VelVar_Str[index3],AVals_Str[index2],(index1+1))


os.system("echo Missing Files:")

for index in range(len(MissingFiles)):
	os.system("echo " + MissingFiles[index])

os.system("echo")
os.system("echo")
os.system("echo -- Aggregation Finished --")
os.system("echo")
os.system("echo")


