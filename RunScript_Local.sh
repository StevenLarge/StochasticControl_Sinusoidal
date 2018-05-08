#!/bin/bash
#Shell script to run stochastic ensemble propogators for different A values

echo
echo "   ----   "
echo "Running A0"
echo "   ----   "
./StochControl_A0.exe

echo
echo "   ----   "
echo "Running A1"
echo "   ----   "
./StochControl_A1.exe

echo
echo "   ----   "
echo "Running A2"
echo "   ----   "
./StochControl_A2.exe

echo
echo "   ----   "
echo "Running A4"
echo "   ----   "
./StochControl_A4.exe


echo 
echo " ----- Finished Calculations -----"
echo

