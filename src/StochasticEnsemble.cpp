/* This is a C++ driver code to propogate an ensemble of stochastic protocols along a sinusoidal landscape, confined by a harmonic trap */

#include <fstream>
#include <iostream>
#include <random>
#include <cmath>
#include <string>
#include <ctime>

#include "include/FrictionCalculator.h"
#include "include/StochasticPropogator.h"
#include "include/ReadWrite.h"

using namespace std;


int main(){

	string WriteName = "WorkData/ConstantVelocityWork_k4_A2.dat";
	string WriteNameFriction = "WorkData/Friction_k4_A4.dat";

	double dX = 0.01;
	int PeriodLength = int(2.0*3.14159/dX);

	double * OptVel;
	double * CPVals;
	double * Friction;
	OptVel = new double [PeriodLength];
	CPVals = new double [PeriodLength];
	Friction = new double [PeriodLength];

	int OuterIterations = 10;
	int InnerIterations = 1;
	double VelVar = 1;
	//double ProtocolDuration [] = {1,2,4,8,16,32,64,128,256,512,1024,2048};
	double ProtocolDuration [] = {1,4,16};
	//int NumDurations = 12;
	int NumDurations = 3;

	double MeanVel;
	double CPDist = 2*3.14159;

	double * WorkArray;
	WorkArray = new double [NumDurations];

	ZulkowskiFriction(OptVel,CPVals,Friction,dX,PeriodLength); 				//Calculate the friction over a period and the optimal velocity for a 1 second protocol

	WriteFrictionData(WriteNameFriction,CPVals,Friction,OptVel,PeriodLength);

	for(int k = 0 ; k < NumDurations ; k++){

		MeanVel = CPDist/ProtocolDuration[k];

		WorkArray[k] = Driver(ProtocolDuration[k],CPDist,OuterIterations,InnerIterations,VelVar,MeanVel,OptVel,CPVals,PeriodLength); 	
		//WorkArray[k] = ConstantDriver(ProtocolDuration[k],OuterIterations,InnerIterations,MeanVel,VelVar); 					//Driver for a constant velocity protocol

		cout << "\t\t-----\n";

	}

	//WriteWorkData(WriteName,ProtocolDuration,WorkArray,NumDurations);

}


