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

	string WriteName = "WorkData/WorkTrend.dat";
	string WriteNameFriction = "WorkData/Friction.dat";

	double dX = 0.005;
	//int PeriodLength = int(2.0*3.14159/dX);
	int PeriodLength = int(1.0/dX);

	double * OptVel;
	double * CPVals;
	double * Friction;
	OptVel = new double [PeriodLength];
	CPVals = new double [PeriodLength];
	Friction = new double [PeriodLength];

	int OuterIterations = 10000;// 20000;
	int InnerIterations = 1;
	//double VelVar = 1;
	double VelVar;
	double * VelVarPtr = &VelVar;
	ReadVelocityVariance(VelVarPtr);

	cout << "Velocity Variance --> " << std::to_string(VelVar) << "\n";

	//double ProtocolDuration [] = {4,8,16,32,64,128,256,512};//,1024};//,2048};
	//double ProtocolDuration [] = {0.031,0.063,0.125,0.25,0.5,1.0,2.0,4.0};
	//double ProtocolDuration [] = {1,4,16};
	//int NumDurations = 8;
	//int NumDurations = 11;//11;//12;
	//int NumDurations = 3;

	//double ProtocolDuration [] = {1};
	//int NumDurations = 1;

	double MeanVel;

	double CPDist;
	double * CPDistPtr = &CPDist;	
	//double CPDist = 2*3.14159;
	ReadCPDist(CPDistPtr);

	//double * WorkArray;
	//WorkArray = new double [NumDurations];

	double ProtocolWork;
	double ProtocolDuration = ReadProtocolDuration();

	cout << "Protocol Duration --> " << std::to_string(ProtocolDuration) << "\n";

	ZulkowskiFriction(OptVel,CPVals,Friction,dX,PeriodLength); 				//Calculate the friction over a period and the optimal velocity for a 1 second protocol

	//WriteFrictionData(WriteNameFriction,CPVals,Friction,OptVel,PeriodLength);

	//for(int k = 0 ; k < NumDurations ; k++){

	MeanVel = CPDist/ProtocolDuration;

	ProtocolWork = Driver(ProtocolDuration,CPDist,OuterIterations,InnerIterations,VelVar,MeanVel,OptVel,CPVals,PeriodLength);

		//WorkArray[k] = Driver(ProtocolDuration[k],CPDist,OuterIterations,InnerIterations,VelVar,MeanVel,OptVel,CPVals,PeriodLength); 	
		//WorkArray[k] = ConstantDriver(ProtocolDuration[k],OuterIterations,InnerIterations,MeanVel,VelVar); 					//Driver for a constant velocity protocol

	cout << "\t\t-----\n";


	WriteSingleWorkData(WriteName,ProtocolDuration,ProtocolWork);
	
	//WriteWorkData(WriteName,ProtocolDuration,WorkArray,NumDurations);

}


