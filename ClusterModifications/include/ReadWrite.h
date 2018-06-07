/* This is a header file for the Discrete Control Nonequilbrium simulations pertaining to protocol read-in */

#include <string>

void ReadParameters(double * dt, double * mass, double * DampingVal, double * beta, double * TrapStrength, double * A, double * CPDist);
void ReadCPDist(double * CPDist);
void ReadVelocityVariance(double * VelVar);

void WriteWorkData(std::string Filename, double * ProtocolDuration, double * WorkArray, int NumberDurations);
void WriteFrictionData(std::string Filename, double * CPVals, double * Friction, double * OptVel, int ArraySize);
void WriteRandomProtocol(std::string Filename, double * OptVel, double * CPVals, int ArraySize);

double ReadProtocolDuration();
void WriteSingleWorkData(std::string WriteName, double ProtocolDuration, double WorkVal);
