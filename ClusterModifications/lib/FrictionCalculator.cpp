/* This is a C++ driver code to calculate the generalized friction for one period of a sinusoidal landscape, confined by a harmonic trap */

#include "include/FrictionCalculator.h"
#include "include/ReadWrite.h"

#include <fstream>
#include <iostream>
#include <random>
#include <cmath>
#include <string>
#include <ctime>

using namespace std;

void ZulkowskiFriction(double * OptVel, double * CPVals, double * Friction, double dX, int PeriodLength){

	double DampingVal;
	double dt;
	double beta;
	double TrapStrength;
	double A;
	double mass;
	double CPDist;

	double * DampingValPtr = &DampingVal;
	double * dtPtr = &dt;
	double * betaPtr = &beta;
	double * TrapStrengthPtr = &TrapStrength;
	double * APtr = &A;
	double * massPtr = &mass;
	double * CPDistPtr = &CPDist;

	ReadParameters(dtPtr, massPtr, DampingValPtr, betaPtr, TrapStrengthPtr, APtr, CPDistPtr);

	//cout << "Parameters:\n";
	//cout << "DampingVal ---> " << std::to_string(DampingVal) << "\n"; 	
	//cout << "dt ---> " << std::to_string(dt) << "\n"; 
	//cout << "beta ---> " << std::to_string(beta) << "\n"; 
	//cout << "TrapStrength ---> " << std::to_string(TrapStrength) << "\n"; 
	//cout << "A ---> " << std::to_string(A) << "\n"; 
	//cout << "mass ---> " << std::to_string(mass) << "\n"; 
	//cout << "CPDist ---> " << std::to_string(CPDist) << "\n";

	double CPCounter = 0.0;
	double TimeAcc = 0.0;
	double Normalization;

	double ViscoFric = -log(DampingVal)/dt;

	int Window = 10;
	double HalfWindow = double(Window)*0.5;
	double XMin;

	int Range = int(double(Window)/dX);

	for(int k = 0 ; k < PeriodLength ; k++){
		CPVals[k] = CPCounter;
		CPCounter += dX;
	}

	for(int k = 0 ; k < PeriodLength ; k++){
		XMin = CPVals[k] - HalfWindow;
		Friction[k] = ViscoFric*GeneralizedFriction(CPVals[k],Range,XMin,dX,TrapStrength,A,beta);
		OptVel[k] = (double(1))/sqrt(Friction[k]);
	}

	for(int k = 0 ; k < PeriodLength ; k++){
		TimeAcc += sqrt(Friction[k])*dX;
	}

	Normalization = (double(1))/TimeAcc;

	for(int k = 0 ; k < PeriodLength ; k++){
		OptVel[k] = OptVel[k]/Normalization;
	}
}

double GeneralizedFriction(double CPVal, int Range, double XMin, double dX, double TrapStrength, double A, double beta){

	double FrictionAcc = 0.0;

	double * EqDist;
	double * XVals;
	double * Cumul_Fw;
	double * Cumul_Rev;
	double * Cumul_Deriv;
	EqDist = new double [Range];
	XVals = new double [Range];
	Cumul_Fw = new double [Range];
	Cumul_Rev = new double [Range];
	Cumul_Deriv = new double [Range];

	double CurrX = XMin;
	double Prob;
	double NormFactor = 0;

	for(int k = 0 ; k < Range ; k++){
		Prob = exp(-beta*Energy(CurrX,CPVal,TrapStrength,A));
		NormFactor += Prob*dX;
		EqDist[k] = Prob;
		if(k!=0){
			Prob = exp(-beta*Energy(CurrX,CPVal-dX,TrapStrength,A));
			Cumul_Rev[k] = Cumul_Rev[k-1] + Prob*dX;
			Prob = exp(-beta*Energy(CurrX,CPVal+dX,TrapStrength,A));
			Cumul_Fw[k] = Cumul_Fw[k-1] + Prob*dX;
		}
		else{
			Prob = exp(-beta*Energy(CurrX,CPVal-dX,TrapStrength,A));
			Cumul_Rev[k] = Prob*dX;
			Prob = exp(-beta*Energy(CurrX,CPVal+dX,TrapStrength,A));
			Cumul_Fw[k] = Prob*dX;
		}
		CurrX += dX;
	}

	for(int k = 0 ; k < Range ; k++){
		EqDist[k] = EqDist[k]/NormFactor;
		Cumul_Fw[k] = Cumul_Fw[k]/Cumul_Fw[Range-1];
		Cumul_Rev[k] = Cumul_Rev[k]/Cumul_Rev[Range-1];
	}

	for(int k = 0 ; k < Range ; k++){
		Cumul_Deriv[k] = (Cumul_Fw[k] - Cumul_Rev[k])/(2*dX);
	}

	for(int k = 0 ; k < Range ; k++){
		FrictionAcc += (Cumul_Deriv[k]*Cumul_Deriv[k]/EqDist[k])*dX;
	}

	delete EqDist;
	delete XVals;
	delete Cumul_Fw;
	delete Cumul_Rev;
	delete Cumul_Deriv;

	return FrictionAcc;
}


double Energy(double position, double CP, double TrapStrength, double A){

	double Energy;
	Energy = 0.5*TrapStrength*(position - CP)*(position - CP) - A*cos(2.0*3.14159*position);

	return Energy;
}

