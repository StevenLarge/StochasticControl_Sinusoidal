/* This C++ file contains the Protocol read/write routines */

//#include "/Users/stevelarge/Research/DiscreteControl/LinkedCode_CPP/lib/DiscreteControl.h" 			//This is the Discrete control header file, containing function prototypes

#include "include/ReadWrite.h"

#include <fstream>
#include <iostream>
#include <random>
#include <cmath>
#include <string>
#include <ctime>

using namespace std;


void ReadParameters(double * dt, double * mass, double * DampingVal, double * beta, double * TrapStrength, double * A, double * CPDist){

	std::ifstream ReadFile;

	ReadFile.open("Parameters.dat");

	ReadFile >> *DampingVal;
	ReadFile >> *dt;
	ReadFile >> *beta;
	ReadFile >> *TrapStrength;
	ReadFile >> *mass;
	ReadFile >> *A;
	ReadFile >> *CPDist;

	ReadFile.close();

}

void ReadVelocityVariance(double * VelVar){

	std::ifstream ReadFile;

	ReadFile.open("Parameters.dat");

	double Dummy;

	ReadFile >> Dummy;
	ReadFile >> Dummy;
	ReadFile >> Dummy;
	ReadFile >> Dummy;
	ReadFile >> Dummy;
	ReadFile >> Dummy;
	ReadFile >> Dummy;
	ReadFile >> *VelVar;

	ReadFile.close();

}


void ReadCPDist(double * CPDist){

	std::ifstream ReadFile;

	double Dummy;

	ReadFile.open("Parameters.dat");

	ReadFile >> Dummy;
	ReadFile >> Dummy;
	ReadFile >> Dummy;
	ReadFile >> Dummy;
	ReadFile >> Dummy;
	ReadFile >> Dummy;

	ReadFile >> *CPDist;

}


void WriteWorkData(string WriteName, double * ProtocolDuration, double * WorkVals, int NumberDurations){

	std::ofstream WriteFile;

	WriteFile.open(WriteName);

	//for(int k = 0 ; k < NumberDurations ; k ++){
	//	WriteFile << std::to_string(ProtocolDuration[k]) << "\t" << std::to_string(WorkVals[k]) << "\n";
	//}

	WriteFile.close();

}

void WriteFrictionData(string WriteName, double * CPVals, double * Friction, double * OptVel, int ArraySize){

	std::ofstream WriteFile;

	WriteFile.open(WriteName);

	//for(int k = 0 ; k < ArraySize ; k++){
	//	WriteFile << std::to_string(CPVals[k]) << "\t" << std::to_string(Friction[k]) << "\t" << std::to_string(OptVel[k]) << "\n";
	//}

	WriteFile.close();

}

void WriteRandomProtocol(string WriteName, double * OptVel, double * CPVals, int ArrayLength){

	std::ofstream WriteFile;

	WriteFile.open(WriteName);

	//for(int k = 0 ; k < ArrayLength ; k++){
	//	WriteFile << std::to_string(CPVals[k]) << "\t" << std::to_string(OptVel[k]) << "\n";
	//}

	WriteFile.close();
}


