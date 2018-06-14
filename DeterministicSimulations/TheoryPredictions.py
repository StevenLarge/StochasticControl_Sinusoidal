#This python script generates the theoretical predictions for the deterministic protocol simulations
#
#Steven Large
#June 12th 2018

import os
from math import *
import numpy as np

def ReadFrictionData(Path,Filename):

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




