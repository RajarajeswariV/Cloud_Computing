#!usr/bin/env bash
# Script to compile and execute a c program in one step.
# compile and run the C program.
echo "CPU benchmark program starts its execution below and runs for 10 mins"
echo "**********************************************************************"
gcc cputimer.c -o cputimer  
	./cputimer