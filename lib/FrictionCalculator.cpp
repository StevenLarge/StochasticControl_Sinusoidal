/* This is a C++ driver code to calculate the generalized friction for one period of a sinusoidal landscape, confined by a harmonic trap */

#include "include/FrictionCalculator.h"

#include <fstream>
#include <iostream>
#include <random>
#include <cmath>
#include <string>
#include <ctime>

using namespace std;

double DampingVal_2 = 0.25;
double dt_2 = 0.1;
double beta_2 = 1.0;
double TrapStrength_2 = 4.0;
double A_2 = 8.0;

void ZulkowskiFriction(double * OptVel, double * CPVals, double * Friction, double dX, int PeriodLength){

	//double DampingVal = 0.25;
	//double dt = 0.1;

	double CPCounter = 0.0;
	double TimeAcc = 0.0;
	double Normalization;

	double ViscoFric = -log(DampingVal_2)/dt_2;

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
		Friction[k] = ViscoFric*GeneralizedFriction(CPVals[k],Range,XMin,dX);
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

double GeneralizedFriction(double CPVal, int Range, double XMin, double dX){

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
		Prob = exp(-beta_2*Energy(CurrX,CPVal));
		NormFactor += Prob*dX;
		EqDist[k] = Prob;
		if(k!=0){
			Prob = exp(-beta_2*Energy(CurrX,CPVal-dX));
			Cumul_Rev[k] = Cumul_Rev[k-1] + Prob*dX;
			Prob = exp(-beta_2*Energy(CurrX,CPVal+dX));
			Cumul_Fw[k] = Cumul_Fw[k-1] + Prob*dX;
		}
		else{
			Prob = exp(-beta_2*Energy(CurrX,CPVal-dX));
			Cumul_Rev[k] = Prob*dX;
			Prob = exp(-beta_2*Energy(CurrX,CPVal+dX));
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

	return FrictionAcc;
}


double Energy(double position, double CP){

	double Energy;
	Energy = 0.5*TrapStrength_2*(position - CP)*(position - CP) -A_2*cos(position);

	return Energy;
}

