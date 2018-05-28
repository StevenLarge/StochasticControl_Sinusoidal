#!/usr/bin/env python

import os

VarVals = [0.036,0.144,0.577,2.308]
NewVar = ["025","1","4","16"]

AVals = [0,0.25,0.5,1,2]
NewAVals = ["0","025","05","1","2"]

AVals = [1]
NewAVals = ["1"]

CPVals = [1,2,3]
CPVals = [1,2]

for index1 in range(len(CPVals)):

	for index2 in range(len(AVals)):

		for index3 in range(len(VarVals)):

			Filename = "WorkTrend3_CP" + str(index1+1) + "_A" + str(AVals[index2]) + "_V" + str(VarVals[index3]) + ".dat"

			NewName = "WorkTrend3_CP" + str(index1+1) + "_A" + str(NewAVals[index2]) + "_V" + str(NewVar[index3]) + ".dat"

			NameCommand = "mv " + Filename + " " + NewName
			os.system(NameCommand)

