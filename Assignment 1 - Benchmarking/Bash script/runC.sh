#!usr/bin/env bash
# Script to compile and execute a c program in one step.
# compile and run the C program.
echo "CPU benchmark program starts its execution below"
echo "***************************************************"
gcc CPUFinal.c -o CPUFinal 
	watch -n free -m
	./CPUFinal
echo "Memory benchmark program starts its execution below"
echo "***************************************************"
gcc MEMFinal.c -o MEMFinal
	./MEMFinal
echo "Disk benchmark program starts its execution below"
echo "***************************************************"
gcc DISKFinal.c -o DISKFinal
	./DISKFinal