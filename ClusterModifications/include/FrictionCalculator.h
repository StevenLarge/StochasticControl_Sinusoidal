/* This is the header file for the friction calculation routines */

void ZulkowskiFriction(double * OptVel, double * CPVals, double * Friction, double dX, int PeriodLength);

double GeneralizedFriction(double CP, int Range, double XMin, double dX, double TrapStrength, double A, double beta);

double Energy(double position, double CPVal, double TrapStrength, double A);
