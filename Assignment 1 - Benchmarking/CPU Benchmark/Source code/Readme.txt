CPU BENCHMARK - README:
======================

The folder consists of all the .c source files and the respective command line arguments syntax are mentioned below.

The file CPUFinal has the code to measure the CPU speed in terms of GFLOPS. Addition, Subtraction, Multiplication is being used as the operations performed on the CPU and the time taken to execute these instructions are recorded. 

Steps for Execution:
===================
Computing FLOPS and IOPS of the machine

1) Execute file CPUFinal.c for Linux on the Terminal using” gcc –pthread CPUFinal.c”
 And run the output a.out file using the command “./a.out” .

2) The program will ask for how many thread to be executed for the process. This program has a capacity to handle threads less than or equal to 8.

Enter a number between 1 – 8.

Now Let’s consider the user entered 1 i.e. 1 thread.

3) Processing starts and you have to wait for it to complete since both the computing of IOPS of the machine and the GFLOPS of the machine will be done and the results printed.

4.) The program will ask the user if he/she wants to enter any other number of thread to calculate the CPU performance. 

5.) If the user enters ‘Y’, the program begins its execution and the steps from 2 to 4 are repeated for the number of threads entered by the user. If the user enters ‘N’, the program exits.


How the code works?
====================

1.)	The below thread is created to call the function gflops.
‘pthread_create(&threads[t], NULL, gflops, (void*)t)’

2.)	Once the function gflops is called, we get the start time of the CPU and perform some arithmetic operations in a for loop for ‘n’ times. Once after the operations performed, we take the end_time of the CPU.

3.)	By doing so, we get the time taken by the CPU to perform the operations ‘n’ times. 

4.)	Time taken is calculated by = “end_time” – “start_time”. All these times are converted to microseconds in the code with the help of TIMEVAL structure.

5.)	Once after getting the CPU’s time, we call another function named – “performance_gflops()” where we take the lowest start time and the highest end time taken by the CPU to perform all the operations. Thread created for the same is shown below.
‘pthread_create(&ithreads[t], NULL, performance_gflops, (void*)t);

6.)	This gives the actual time taken to perform floating point operations per seconds for the number of threads the user entered.

7.)	Similarly, GIOPS is calculated in the same way with the help of 2 functions being called from main as a thread as below.
‘pthread_create(&ithreads[t], NULL, giops, (void*)t)’.
pthread_create(&ipthreads[t], NULL, performance_giops, (void*)t);

Sample output:
==============

Calculating GFLOPS:
CPU's lowest startime is 1455150704108678 microsec

CPU's highest endtime is 1455150706595036 microsec

The Difference between the lowest start time and highest end time is calculated below *******

The Difference in the above timings in seconds is : 2486358
time difference in microseconds is : 2.486358

The total gflops for 1 threads in seconds is : 4.021947

Calculating GIOPS:

CPU's lowest startime is 1455150706595610 microsec

CPU's highest endtime is 1455150709049562 microsec

The Difference between the lowest start time and highest end time is calculated below *******

The Difference in the above timings in seconds is : 2453952
time difference in microseconds is : 2.453952

The total giops for 1 threads in seconds is : 4.075059
