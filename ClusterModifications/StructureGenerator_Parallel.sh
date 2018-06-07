#!/usr/bin/env python

import os
#import numpy as np

def ParameterFile(A,CPDist,VelVar,ProtocolDuration):

	file1 = open("Parameters.dat",'w')
	file1.write("0.87055\n")
	file1.write("0.01\n")	    
	file1.write("1.0\n") 						#beta
	file1.write("4.0\n") 						#Trap Strength
	file1.write("1.0\n")	 					#mass

	file1.write("%lf\n" % A) 					#A
	file1.write("%lf\n" % CPDist)				#CPDist
	file1.write("%lf\n" % VelVar)				#Velocity Variance
	file1.write("%lf\n" % ProtocolDuration)		#Protocol duration

	file1.close()


def ParameterFile_Fast(A,CPDist,VelVar):

        file1 = open("Parameters.dat",'w')
        #file1.write("0.87055\n")
        file1.write("0.933033\n")
        #file1.write("0.01\n")
        file1.write("0.005\n")
        file1.write("1.0\n")
        file1.write("4.0\n")
        file1.write("1.0\n")

        file1.write("%lf\n" % A)
        file1.write("%lf\n" % CPDist)
        file1.write("%lf\n" % VelVar)

        file1.close()

        
def GenerateSlurmFile(Duration):

	file1 = open("SlurmSubmission.sh",'w')

	file1.write("#!/bin/bash\n")
	file1.write("#SBATCH --account=rrg-dsivak\n")
	file1.write("#SBATCH --time=20:00:00\n")

	NameCommand = "#SBATCH --job-name=Long_T" + Duration + "\n"

	file1.write(NameCommand)
	file1.write("\n./StochControl.exe\n")



AVals = [0.5,1,2]
AVals_Str = ["05","1","2"]

#AVals = [2,4]
#AVals_Str = ["2","4"]

#CPDist = [np.pi,2*np.pi,4*np.pi]
CPDist = [1,4,16]
#CPDist = [16]

#VelVar = [0.25,1,4,16]
VelVar = [0.036,0.144,0.577,2.308]
VelVar_Str = ["025","1","4","16"]

ProtocolDuration = [4,8,16,32,64,128,256,512]
ProtocolDuration_Str = ["4","8","16","32","64","128","256","512"]

for index1 in range(len(CPDist)):

	DirName1 = "CPDist_" + str(index1+1)

	if(os.path.exists(DirName1)==False):
		os.mkdir(DirName1)

	os.chdir(DirName1)


	for index2 in range(len(AVals)):

		DirName2 = "A_" + AVals_Str[index2]

		if(os.path.exists(DirName2)==False):
			os.mkdir(DirName2)

		os.chdir(DirName2)


		for index3 in range(len(VelVar)):

			DirName3 = "Var_" + VelVar_Str[index3]

			if(os.path.exists(DirName3)==False):
				os.mkdir(DirName3)

			os.chdir(DirName3)

			for index4 in range(len(ProtocolDuration)):

				DirName4 = "T_" + ProtocolDuration_Str[index4]

				if(os.path.exists(DirName4)==False):
					os.mkdir(DirName4)

				os.chdir(DirName4)

				ParameterFile(AVals[index2],CPDist[index1],VelVar[index3],ProtocolDuration[index4])
				GenerateSlurmFile(ProtocolDuration_Str[index4])

				if(os.path.exists("WorkData")==False):
					os.mkdir("WorkData")

				os.chdir("..")
			
			os.chdir("..")
		
		os.chdir("..")
	
	os.chdir("..")


os.system("echo")
os.system("echo")
os.system("echo ----- Finished Generating Parameter Files")
os.system("echo")
os.system("echo")

for index1 in range(len(CPDist)):
	for index2 in range(len(AVals)):
		for index3 in range(len(VelVar)):
			for index4 in range(len(ProtocolDuration)):

				TargetPath = "CPDist_" + str(index1+1) + "/" + "A_" + AVals_Str[index2] + "/Var_" + VelVar_Str[index3] + "/T_" + ProtocolDuration_Str[index4]
				
				CopyCommandSrc = "cp -r src " + TargetPath
				CopyCommandLib = "cp -r lib " + TargetPath
				CopyCommandInc = "cp -r include " + TargetPath
				CopyCommandMake = "cp Makefile " + TargetPath

				os.system(CopyCommandSrc)
				os.system(CopyCommandLib)
				os.system(CopyCommandInc)
				os.system(CopyCommandMake)
        
				DirName1 = "CPDist_" + str(index1+1)
				DirName2 = "A_" + AVals_Str[index2]
				DirName3 = "Var_" + VelVar_Str[index3]
				DirName4 = "T_" + ProtocolDuration_Str[index4]
				os.chdir(DirName1)
				os.chdir(DirName2)
				os.chdir(DirName3)
				os.chdir(DirName4)
				os.system("make clean")
				os.system("make")
				#os.system("sbatch SlurmSubmission.sh")
				os.chdir("..")
				os.chdir("..")
				os.chdir("..")
				os.chdir("..")


os.system("echo")
os.system("echo")
os.system("echo ----- Finished Submitting Jobs")
os.system("echo")
os.system("echo")



