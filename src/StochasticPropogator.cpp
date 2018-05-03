/* This is a C++ driver code to propogate an ensemble of stochastic protocols along a sinusoidal landscape, confined by a harmonic trap */

#include "include/StochasticPropogator.h"
#include "include/ReadWrite.h"

#include <fstream>
#include <iostream>
#include <random>
#include <cmath>
#include <string>
#include <ctime>

using namespace std;


/* Global declaration of random device */

std::random_device rd;
std::mt19937 gen(rd());
std::normal_distribution<> d(0,1);
double GaussRandom;

/* Global variable declarations for Langevin integrator parameters */

double TrapStrength = 4.0;
double DampingVal = 0.25;
double beta = 1.0;
double dt = 0.1;
double mass = 1.0;
double ViscoFric = -log(DampingVal)/dt;

/* Global variables for Sinusoidal potential parameters */

double A = 4.0;


double Driver(double ProtDuration, double MeanDistance, int OuterIterations,int InnerIterations, double VelVar, double MeanVel, double * OptVel, double * CPVals, int PeriodLength){

	//std::random_device rd2;
	//std::mt19937 gen(rd2());
	//std::normal_distribution<> d2(MeanVel,VelVar);
	double RandVel;

	double WorkAcc = 0.0;
	double Equilibration = 100;

	double time;
	double position;
	double velocity;
	double CP;

	double * timePointer = &time;
	double * velocityPointer = &velocity;
	double * positionPointer = &position;
	double * CPPointer = &CP;

	double Distance;
	int ImageNumber;
	double CompleteImage;
	int ProtocolLength;
	double Normalization;

	double MINVAL;
	double TestDiff;
	int Target;
	double TimeAcc;

	string ProtocolName;

	for(int k = 0 ; k < OuterIterations ; k++){

		RandVel = abs(VelVar*d(gen) + MeanVel);

		ProtocolName = "WorkData/OptimalProtocol_A4_" + std::to_string(int(ProtDuration)) + "_" + std::to_string(int(k)) + ".dat";

		Distance = RandVel*ProtDuration;
		ImageNumber = int(Distance)/int(MeanDistance);
		CompleteImage = fmod(Distance,MeanDistance);

		//cout << "Distance --> " << std::to_string(Distance) << "\n";
		//cout << "ImageNumber --> " << std::to_string(ImageNumber) << "\n";
		//cout << "CompleteImage --> " << std::to_string(CompleteImage) << "\n";

		MINVAL = 9999;
		
		for(int p = 1 ; p < PeriodLength ; p++){
			TestDiff = abs(CPVals[p] - CompleteImage);
			if(TestDiff < MINVAL){
				Target = p;
				MINVAL = TestDiff;
			}
		}

		//cout << "Target --> " << std::to_string(Target) << "\n";
		//cout << "CPVals[Target] --> " << std::to_string(CPVals[Target]) << "\n\n";

		ProtocolLength = ImageNumber*PeriodLength + Target;

		double * OptVel_Realization;
		double * CPVals_Realization;
		OptVel_Realization = new double [ProtocolLength];
		CPVals_Realization = new double [ProtocolLength];

		for(int p = 0 ; p < ProtocolLength ; p ++){
			OptVel_Realization[p] = OptVel[p%PeriodLength];
			CPVals_Realization[p] = CPVals[p%PeriodLength] + (int(p)/int(PeriodLength))*CPVals[PeriodLength-1];
		}

		//TimeAcc = ImageNumber + (CompleteImage/double(PeriodLength));
		TimeAcc = 0.0;

		for(int p = 0 ; p < ProtocolLength ; p ++){
			TimeAcc += 0.01/OptVel_Realization[p];
		}

		Normalization = double(ProtDuration)/TimeAcc;

		for(int p = 0 ; p < ProtocolLength ; p++){
			OptVel_Realization[p] = OptVel_Realization[p]/Normalization;
		}

		WriteRandomProtocol(ProtocolName,OptVel_Realization,CPVals_Realization,ProtocolLength);

		/*
		for(int j = 0 ; j < InnerIterations ; j++){

			time = 0;
			position = -ViscoFric*RandVel/TrapStrength;
			velocity = 0;
			CP = 0;

			while(time < Equilibration){
				//ConstantLangevinEquil(timePointer,positionPointer,velocityPointer,CPPointer,RandVel);
				LangevinEquil(timePointer,positionPointer,velocityPointer,CPPointer,OptVel_Realization,CPVals_Realization);
			}

			time = 0;

			while(time < ProtDuration){
				//WorkAcc += ConstantLangevin(timePointer,positionPointer,velocityPointer,CPPointer,RandVel);
				WorkAcc += Langevin(timePointer,positionPointer,velocityPointer,CPPointer,OptVel_Realization,CPVals_Realization,ProtocolLength);
			}

		}*/

		WorkAcc = WorkAcc/double(InnerIterations);

		//delete OptVel_Realization;
		//delete CPVals_Realization;

	}

	return WorkAcc/double(OuterIterations);
}


int FindTargetIndex(double CP, double * CPVals, int ArrayLength){

	double MINVAL = 9999;
	double TestDiff;
	int Target;

	for(int k = 0 ; k < ArrayLength ; k++){
		TestDiff = abs(CP - CPVals[k]);
		if(TestDiff < MINVAL){
			Target = k;
		}
	}

	return Target;
}

double Langevin(double * time, double * position, double * velocity, double * CP, double * OptVel_Realization, double * CPVals_Realization, int ArrayLength){

	GaussRandom = d(gen);

	*velocity = sqrt(DampingVal)*(*velocity) + sqrt((1-DampingVal)/(beta*mass))*GaussRandom;
	*velocity = *velocity + 0.5*dt*ForceParticleSin(*position,*CP)/mass;
	*position = *position + 0.5*dt*(*velocity);

	*time += dt;
	double NewCP = *CP + OptVel_Realization[FindTargetIndex(*CP,CPVals_Realization,ArrayLength)]*dt;
	double WorkStep = CalcWork(*position,*CP,NewCP);

	*CP = NewCP;

	GaussRandom = d(gen);

	*position = *position + 0.5*dt*(*velocity);
	*velocity = *velocity + 0.5*dt*ForceParticleSin(*position,*CP)/mass;
	*velocity = sqrt(DampingVal)*(*velocity) + sqrt((1-DampingVal)/(beta*mass))*GaussRandom;

	return WorkStep;
}

void LangevinEquil(double * time, double * position, double * velocity, double * CP, double * OptVel_Realization, double * CPVals_Realization){

	GaussRandom = d(gen);

	*velocity = sqrt(DampingVal)*(*velocity) + sqrt((1-DampingVal)/(beta*mass))*GaussRandom;
	*velocity = *velocity + 0.5*dt*ForceParticleSin(*position,*CP)/mass;
	*position = *position + 0.5*dt*(*velocity);

	*time += dt;
	double OldCP = *CP;
	double NewCP = *CP + OptVel_Realization[0]*dt;
	*CP = NewCP;

	GaussRandom = d(gen);

	*position = *position + 0.5*dt*(*velocity);
	*velocity = *velocity + 0.5*dt*ForceParticleSin(*position,*CP)/mass;
	*velocity = sqrt(DampingVal)*(*velocity) + sqrt((1-DampingVal)/(beta*mass))*GaussRandom;

	*CP = OldCP;
	*position = *position - (NewCP - OldCP); 		//Reset the position so that after equilibration the system average position
}



/* Constane velocity protocol propogation routines */


double ConstantDriver(double ProtDuration,int OuterIterations,int InnerIterations,double MeanVel,double VelVar){

	std::random_device rd3;
	std::mt19937 gen(rd3());
	std::normal_distribution<> d3(MeanVel,VelVar);
	double RandVel;

	double WorkAcc = 0.0;
	double Equilibration = 100;

	double time;
	double position;
	double velocity;
	double CP;

	double * timePointer = &time;
	double * velocityPointer = &velocity;
	double * positionPointer = &position;
	double * CPPointer = &CP;

	for(int k = 0 ; k < OuterIterations ; k++){

		RandVel = d3(gen);

		for(int j = 0 ; j < InnerIterations ; j++){

			time = 0;
			position = -ViscoFric*RandVel/TrapStrength;
			velocity = 0;
			CP = 0;

			while(time < Equilibration){
				ConstantLangevinEquil(timePointer,positionPointer,velocityPointer,CPPointer,RandVel);
			}

			time = 0;

			while(time < ProtDuration){
				WorkAcc += ConstantLangevin(timePointer,positionPointer,velocityPointer,CPPointer,RandVel);
			}

		}

		WorkAcc = WorkAcc/double(InnerIterations);

	}

	return WorkAcc/double(OuterIterations);
}



double ConstantLangevin(double * time, double * position, double * velocity, double * CP, double RandVel){

	GaussRandom = d(gen);

	*velocity = sqrt(DampingVal)*(*velocity) + sqrt((1-DampingVal)/(beta*mass))*GaussRandom;
	*velocity = *velocity + 0.5*dt*ForceParticleSin(*position,*CP)/mass;
	*position = *position + 0.5*dt*(*velocity);

	*time += dt;
	double NewCP = *CP + RandVel*dt;
	double WorkStep = CalcWork(*position,*CP,NewCP);

	*CP = NewCP;

	GaussRandom = d(gen);

	*position = *position + 0.5*dt*(*velocity);
	*velocity = *velocity + 0.5*dt*ForceParticleSin(*position,*CP)/mass;
	*velocity = sqrt(DampingVal)*(*velocity) + sqrt((1-DampingVal)/(beta*mass))*GaussRandom;

	return WorkStep;
}

void ConstantLangevinEquil(double * time, double * position, double * velocity, double * CP, double RandVel){

	GaussRandom = d(gen);

	*velocity = sqrt(DampingVal)*(*velocity) + sqrt((1-DampingVal)/(beta*mass))*GaussRandom;
	*velocity = *velocity + 0.5*dt*ForceParticleSin(*position,*CP)/mass;
	*position = *position + 0.5*dt*(*velocity);

	*CP += RandVel*dt;

	*time += dt;

	GaussRandom = d(gen);

	*position = *position + 0.5*dt*(*velocity);
	*velocity = *velocity + 0.5*dt*ForceParticleSin(*position,*CP)/mass;
	*velocity = sqrt(DampingVal)*(*velocity) + sqrt((1-DampingVal)/(beta*mass))*GaussRandom;

}


double ForceParticleSin(double position, double CP){

	double Force;
	Force = -TrapStrength*(position - CP) + A*sin(position);
	return Force;
}

double CalcWork(double position, double CPOld, double CPNew){

	double EnergyBefore;
	double EnergyAfter;
	double Work;

	EnergyBefore = 0.5*TrapStrength*(position - CPOld)*(position - CPOld) - A*cos(position);
	EnergyAfter = 0.5*TrapStrength*(position - CPNew)*(position - CPNew) - A*cos(position);

	Work = EnergyAfter - EnergyBefore;

	return Work;
}

