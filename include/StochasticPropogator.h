/* This is a header file for the Stochastic Control Nonequilbrium simulations pertaining to protocol propogation */

double ConstantDriver(double ProtDuration, double MeanDistance, int InnerIter, int OuterIter, double MeanVel, double VelVar);
double Driver(double ProtDuration, double MeanDistance, int InnerIter, int OuterIter, double VelVar, double MeanVel, double * OptVel, double * CPVals, int PeriodLength);

double Langevin(double * time, double * position, double * velocity, double * CP, double * OptVel, double * CPVals, int ArrayLength);
void LangevinEquil(double * time, double * position, double * velocity, double * CP, double * OptVel, double * CPVals);
int FindTargetIndex(double CP, double * CPVals, int ArraySize);

double ConstantLangevin(double * time, double * position, double * velocity, double * CP, double RandVel);
void ConstantLangevinEquil(double * time, double * position, double * velocity, double * CP, double RandVel);
double ForceParticleSin(double position, double CP);
double CalcWork(double position, double CPOld, double CPNew);


