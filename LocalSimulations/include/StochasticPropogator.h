/* This is a header file for the Stochastic Control Nonequilbrium simulations pertaining to protocol propogation */

double ConstantDriver(double ProtDuration, double MeanDistance, int InnerIter, int OuterIter, double MeanVel, double VelVar);
double Driver(double ProtDuration, double MeanDistance, int InnerIter, int OuterIter, double VelVar, double MeanVel, double * OptVel, double * CPVals, int PeriodLength);


double Langevin(double * time, double * position, double * velocity, double * CP, double * OptVel_Realization, double * CPVals_Realization, int ArrayLength, double dt, double A, double beta, double DampingVal, double mass, double TrapStrength);
void LangevinEquil(double * time, double * position, double * velocity, double * CP, double * OptVel_Realization, double * CPVals_Realization, double dt, double A, double beta, double DampingVal, double mass, double TrapStrength);
void LangevinEquil_NESS(double * time, double * position, double * velocity, double * CP, double * OptVel_Realization, double * CPVals_Realization, double dt, double A, double beta, double DampingVal, double mass, double TrapStrength, int ArrayLength);
void LangevinEquil_MeanVel(double * time, double * position, double * velocity, double * CP, double MeanVel, double * CPVals_Realization, double dt, double A, double beta, double DampingVal, double mass, double TrapStrength);
double ForceParticleSin(double position, double CP, double TrapStrength, double A);
double CalcWork(double position, double CPOld, double CPNew, double TrapStrength, double A);

//double Langevin(double * time, double * position, double * velocity, double * CP, double * OptVel, double * CPVals, int ArrayLength);
//void LangevinEquil(double * time, double * position, double * velocity, double * CP, double * OptVel, double * CPVals);
int FindTargetIndex(double CP, double * CPVals, int ArraySize);

//double ConstantLangevin(double * time, double * position, double * velocity, double * CP, double RandVel);
//void ConstantLangevinEquil(double * time, double * position, double * velocity, double * CP, double RandVel);

double ConstantLangevin(double * time, double * position, double * velocity, double * CP, double RandVel, double dt, double mass, double beta, double DampingVal, double TrapStrength, double A);
void ConstantLangevinEquil(double * time, double * position, double * velocity, double * CP, double RandVel, double dt, double mass, double beta, double DampingVal, double TrapStrength, double A);


//double ForceParticleSin(double position, double CP);
//double CalcWork(double position, double CPOld, double CPNew);


