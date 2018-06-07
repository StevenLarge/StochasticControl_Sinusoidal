#!/usr/bin/env python

import os
import time

#AVals = ["0","025","05","1","2"]#,"4"]
AVals = ["05","1","2"]
Var = ["025","1","4","16"]
Durations = ["4","8","16","32","128","256","512"]

for index1 in range(3):

	CPDir = "CPDist_" + str(index1+1)
	os.chdir(CPDir)

	for index2 in range(len(AVals)):

		ADir = "A_" + AVals[index2]
		os.chdir(ADir)

		for index3 in range(len(Var)):

			VarDir = "Var_" + Var[index3]
			os.chdir(VarDir)

			for index4 in range(len(Durations)):

				TimeDir = "T_" + Durations[index4]
				os.chdir(TimeDir)

				os.system("chmod 777 Slurm*.sh")
				os.system("sbatch Slurm*.sh")
				os.system("echo Waiting...")
				time.sleep(2)

				os.chdir("..")

			os.chdir("..")

		os.chdir("..")

	os.chdir("..")







