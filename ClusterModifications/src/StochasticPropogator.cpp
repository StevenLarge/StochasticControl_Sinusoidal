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


double Driver(double ProtDuration, double MeanDistance, int OuterIterations,int InnerIterations, double VelVar, double MeanVel, double * OptVel, double * CPVals, int PeriodLength){

	double TrapStrength;
	double DampingVal;
	double beta;
	double dt;
	double mass;
	double A;
	double CPDist;

	double * TrapStrengthPtr = &TrapStrength;
	double * DampingValPtr = &DampingVal;
	double * betaPtr = &beta;
	double * dtPtr = &dt;
	double * massPtr = &mass;
	double * APtr = &A;
	double * CPDistPtr = &CPDist;

	ReadParameters(dtPtr, massPtr, DampingValPtr, betaPtr, TrapStrengthPtr, APtr, CPDistPtr);

	double ViscoFric = -log(DampingVal)/dt;

	double RandVel;
	double MeanProtoVel;

	double WorkAcc = 0.0;
	double Equilibration = 50/dt;
	
	int EquilCounter;
	int BreakCondition;
	int MaxCounter = 100000;

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

	string Filename;

	for(int k = 0 ; k < OuterIterations ; k++){

		RandVel = abs(sqrt(VelVar)*d(gen) + MeanVel);

		Distance = RandVel*ProtDuration;
		//ImageNumber = int(Distance/MeanDistance);
		//ImageNumber = int(Distance/(2*3.14159));
		ImageNumber = int(Distance/(1.0));
		//CompleteImage = fmod(Distance,MeanDistance);
		//CompleteImage = fmod(Distance,(2*3.14159));
		CompleteImage = fmod(Distance,1.0);

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
			TimeAcc += 0.005/OptVel_Realization[p];
		}

		Normalization = double(ProtDuration)/TimeAcc;

		for(int p = 0 ; p < ProtocolLength ; p++){
			OptVel_Realization[p] = OptVel_Realization[p]/Normalization;
		}
		
		for(int j = 0 ; j < InnerIterations ; j++){

			time = 0;
			position = 0;//-ViscoFric*RandVel/TrapStrength;
			velocity = 0;
			CP = 0;

			BreakCondition = 0;
			EquilCounter = 0;

			//while(time < Equilibration){
			while(BreakCondition == 0){
				//LangevinEquil(timePointer,positionPointer,velocityPointer,CPPointer,OptVel_Realization,CPVals_Realization,dt,A,beta,DampingVal,mass,TrapStrength);
				LangevinEquil_NESS(timePointer,positionPointer,velocityPointer,CPPointer,OptVel_Realization,CPVals_Realization,dt,A,beta,DampingVal,mass,TrapStrength,PeriodLength);
				EquilCounter += 1;

				//std::ofstream WriteFile;
				//Filename = "TrajData/Traj_Equil_Vel" + std::to_string(MeanVel) + "_" + std::to_string(k) + ".dat";
				//WriteFile.open(Filename,std::ios_base::app);
				//WriteFile << std::to_string(time) << "\t" << std::to_string(CP) << "\t" << std::to_string(position) << "\n";
				//WriteFile.close();

				if(EquilCounter > Equilibration && EquilCounter%PeriodLength == 0){
					BreakCondition = 1;
				}
				if(EquilCounter > MaxCounter){
					BreakCondition = 1;
					cout << "\t\t--- Equilibration Terminated: MaxCounter Limit Reached ---\n";
				}
			}

			time = 0;
			position = position - CP;
			CP = 0;

			while(time < ProtDuration){
				WorkAcc += Langevin(timePointer,positionPointer,velocityPointer,CPPointer,OptVel_Realization,CPVals_Realization,ProtocolLength,dt,A,beta,DampingVal,mass,TrapStrength);
			
				//std::ofstream WriteFile;
				//Filename = "TrajData/Traj_Dynamic_Vel" + std::to_string(MeanVel) + "_" + std::to_string(k) + ".dat";
				//WriteFile.open(Filename,std::ios_base::app);
				//WriteFile << std::to_string(time) << "\t" << std::to_string(CP) << "\t" << std::to_string(position) << "\n";
				//WriteFile.close();
			}

		}

		WorkAcc = WorkAcc/double(InnerIterations);

		delete OptVel_Realization;
		delete CPVals_Realization;

	}

	return WorkAcc/double(OuterIterations);
}


int FindTargetIndex(double CP, double * CPVals, int ArrayLength){

	double MINVAL = 9999;
	double TestDiff;
	int Target;

	double Image;

	Image = fmod(CP,1.0);

	for(int k = 0 ; k < ArrayLength ; k++){
		TestDiff = abs(Image - CPVals[k]);
		if(TestDiff < MINVAL){
			Target = k;
			MINVAL = TestDiff;
		}
	}

	return Target;
}

double Langevin(double * time, double * position, double * velocity, double * CP, double * OptVel_Realization, double * CPVals_Realization, int ArrayLength, double dt, double A, double beta, double DampingVal, double mass, double TrapStrength){

	GaussRandom = d(gen);

	*velocity = sqrt(DampingVal)*(*velocity) + sqrt((1-DampingVal)/(beta*mass))*GaussRandom;
	*velocity = *velocity + 0.5*dt*ForceParticleSin(*position,*CP,TrapStrength,A)/mass;
	*position = *position + 0.5*dt*(*velocity);

	*time += dt;
	double NewCP = *CP + OptVel_Realization[FindTargetIndex(*CP,CPVals_Realization,ArrayLength)]*dt;
	double WorkStep = CalcWork(*position,*CP,NewCP,TrapStrength,A);

	*CP = NewCP;

	GaussRandom = d(gen);

	*position = *position + 0.5*dt*(*velocity);
	*velocity = *velocity + 0.5*dt*ForceParticleSin(*position,*CP,TrapStrength,A)/mass;
	*velocity = sqrt(DampingVal)*(*velocity) + sqrt((1-DampingVal)/(beta*mass))*GaussRandom;

	return WorkStep;
}

void LangevinEquil(double * time, double * position, double * velocity, double * CP, double * OptVel_Realization, double * CPVals_Realization, double dt, double A, double beta, double DampingVal, double mass, double TrapStrength){

	GaussRandom = d(gen);

	*velocity = sqrt(DampingVal)*(*velocity) + sqrt((1-DampingVal)/(beta*mass))*GaussRandom;
	*velocity = *velocity + 0.5*dt*ForceParticleSin(*position,*CP,TrapStrength,A)/mass;
	*position = *position + 0.5*dt*(*velocity);

	*time += dt;
	double OldCP = *CP;
	double NewCP = *CP + OptVel_Realization[0]*dt;
	*CP = NewCP;

	GaussRandom = d(gen);

	*position = *position + 0.5*dt*(*velocity);
	*velocity = *velocity + 0.5*dt*ForceParticleSin(*position,*CP,TrapStrength,A)/mass;
	*velocity = sqrt(DampingVal)*(*velocity) + sqrt((1-DampingVal)/(beta*mass))*GaussRandom;

	*CP = OldCP;
	*position = *position - (NewCP - OldCP); 		//Reset the position so that after equilibration the system average position
}


void LangevinEquil_MeanVel(double * time, double * position, double * velocity, double * CP, double MeanVel, double * CPVals_Realization, double dt, double A, double beta, double DampingVal, double mass, double TrapStrength){

	GaussRandom = d(gen);

	*velocity = sqrt(DampingVal)*(*velocity) + sqrt((1-DampingVal)/(beta*mass))*GaussRandom;
	*velocity = *velocity + 0.5*dt*ForceParticleSin(*position,*CP,TrapStrength,A)/mass;
	*position = *position + 0.5*dt*(*velocity);

	*time += dt;
	double OldCP = *CP;
	double NewCP = *CP + MeanVel*dt;
	*CP = NewCP;

	GaussRandom = d(gen);

	*position = *position + 0.5*dt*(*velocity);
	*velocity = *velocity + 0.5*dt*ForceParticleSin(*position,*CP,TrapStrength,A)/mass;
	*velocity = sqrt(DampingVal)*(*velocity) + sqrt((1-DampingVal)/(beta*mass))*GaussRandom;

	*CP = OldCP;
	*position = *position - (NewCP - OldCP); 		//Reset the position so that after equilibration the system average position
}



void LangevinEquil_NESS(double * time, double * position, double * velocity, double * CP, double * OptVel_Realization, double * CPVals_Realization, double dt, double A, double beta, double DampingVal, double mass, double TrapStrength, int ArrayLength){

	GaussRandom = d(gen);

	*velocity = sqrt(DampingVal)*(*velocity) + sqrt((1-DampingVal)/(beta*mass))*GaussRandom;
	*velocity = *velocity + 0.5*dt*ForceParticleSin(*position,*CP,TrapStrength,A)/mass;
	*position = *position + 0.5*dt*(*velocity);

	*time += dt;
	double OldCP = *CP;
	double NewCP = *CP + OptVel_Realization[FindTargetIndex(*CP,CPVals_Realization,ArrayLength)]*dt;
	//double NewCP = *CP + OptVel_Realization[Counter%ArrayLength]*dt;
	*CP = NewCP;

	GaussRandom = d(gen);

	*position = *position + 0.5*dt*(*velocity);
	*velocity = *velocity + 0.5*dt*ForceParticleSin(*position,*CP,TrapStrength,A)/mass;
	*velocity = sqrt(DampingVal)*(*velocity) + sqrt((1-DampingVal)/(beta*mass))*GaussRandom;

	//*CP = OldCP;
	//*position = *position - (NewCP - OldCP); 		//Reset the position so that after equilibration the system average position
}


/* Constant velocity protocol propogation routines */


double ConstantDriver(double ProtDuration,int OuterIterations,int InnerIterations,double MeanVel,double VelVar){

	std::random_device rd3;
	std::mt19937 gen(rd3());
	std::normal_distribution<> d3(MeanVel,VelVar);
	double RandVel;

	double WorkAcc = 0.0;
	double Equilibration = 500;

	double TrapStrength;
	double DampingVal;
	double beta;
	double dt;
	double mass;
	double A;
	double CPDist;

	double * TrapStrengthPtr = &TrapStrength;
	double * DampingValPtr = &DampingVal;
	double * betaPtr = &beta;
	double * dtPtr = &dt;
	double * massPtr = &mass;
	double * APtr = &A;
	double * CPDistPtr = &CPDist;

	ReadParameters(dtPtr, massPtr, DampingValPtr, betaPtr, TrapStrengthPtr, APtr, CPDistPtr);

	double ViscoFric = -log(DampingVal)/dt;

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
				ConstantLangevinEquil(timePointer,positionPointer,velocityPointer,CPPointer,RandVel,dt,mass,beta,DampingVal,TrapStrength,A);
			}

			time = 0;

			while(time < ProtDuration){
				WorkAcc += ConstantLangevin(timePointer,positionPointer,velocityPointer,CPPointer,RandVel,dt,mass,beta,DampingVal,TrapStrength,A);
			}

		}

		WorkAcc = WorkAcc/double(InnerIterations);

	}

	return WorkAcc/double(OuterIterations);
}



double ConstantLangevin(double * time, double * position, double * velocity, double * CP, double RandVel, double dt, double mass, double beta, double DampingVal, double TrapStrength, double A){

	GaussRandom = d(gen);

	*velocity = sqrt(DampingVal)*(*velocity) + sqrt((1-DampingVal)/(beta*mass))*GaussRandom;
	*velocity = *velocity + 0.5*dt*ForceParticleSin(*position,*CP,TrapStrength,A)/mass;
	*position = *position + 0.5*dt*(*velocity);

	*time += dt;
	double NewCP = *CP + RandVel*dt;
	double WorkStep = CalcWork(*position,*CP,NewCP,TrapStrength,A);

	*CP = NewCP;

	GaussRandom = d(gen);

	*position = *position + 0.5*dt*(*velocity);
	*velocity = *velocity + 0.5*dt*ForceParticleSin(*position,*CP,TrapStrength,A)/mass;
	*velocity = sqrt(DampingVal)*(*velocity) + sqrt((1-DampingVal)/(beta*mass))*GaussRandom;

	return WorkStep;
}

void ConstantLangevinEquil(double * time, double * position, double * velocity, double * CP, double RandVel, double dt, double mass, double beta, double DampingVal, double TrapStrength, double A){

	GaussRandom = d(gen);

	*velocity = sqrt(DampingVal)*(*velocity) + sqrt((1-DampingVal)/(beta*mass))*GaussRandom;
	*velocity = *velocity + 0.5*dt*ForceParticleSin(*position,*CP,TrapStrength,A)/mass;
	*position = *position + 0.5*dt*(*velocity);

	*CP += RandVel*dt;

	*time += dt;

	GaussRandom = d(gen);

	*position = *position + 0.5*dt*(*velocity);
	*velocity = *velocity + 0.5*dt*ForceParticleSin(*position,*CP,TrapStrength,A)/mass;
	*velocity = sqrt(DampingVal)*(*velocity) + sqrt((1-DampingVal)/(beta*mass))*GaussRandom;

}


double ForceParticleSin(double position, double CP, double TrapStrength, double A){

	double Force;
	Force = -TrapStrength*(position - CP) + A*sin(2.0*3.14159*position);
	return Force;
}

double CalcWork(double position, double CPOld, double CPNew, double TrapStrength, double A){

	double EnergyBefore;
	double EnergyAfter;
	double Work;

	EnergyBefore = 0.5*TrapStrength*(position - CPOld)*(position - CPOld) - A*cos(2.0*3.14159*position);
	EnergyAfter = 0.5*TrapStrength*(position - CPNew)*(position - CPNew) - A*cos(2.0*3.14159*position);

	Work = EnergyAfter - EnergyBefore;

	return Work;
}

