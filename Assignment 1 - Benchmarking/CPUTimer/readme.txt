README FILE FOR CPUTIMER
=========================

1. Compile and execute the file CPUTimer.c
2. The Timer program runs and gives the output in another file named - CPUTimer.txt.


Output inside the CPUTimer.txt file
===================================

The program does the below.

1. Takes the start time of the CPU in seconds
2. For every one second, the arithmetic operations are performed and the CPU utilization is calculated. 
3. Once after 1 second is completed, the program takes the end time of the CPU in seconds. 
4. The above steps from 1-3 is repeated continuously for 10 minutes as per the requirement taking 600 samples of the CPU iterations. 

Thus, the CPU utilization is calculated based on the 600 samples.

Observations:
===========

For every second, and about 100000000 iterations performed, around 4 to 5 operations are executed by the CPU and its utilization for every second is approximately on an average 0.97956 secon