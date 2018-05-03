/* This is a header file for the Discrete Control Nonequilbrium simulations pertaining to protocol read-in */

#include <string>

void WriteWorkData(std::string Filename, double * ProtocolDuration, double * WorkArray, int NumberDurations);
void WriteFrictionData(std::string Filename, double * CPVals, double * Friction, double * OptVel, int ArraySize);
void WriteRandomProtocol(std::string Filename, double * OptVel, double * CPVals, int ArraySize);
