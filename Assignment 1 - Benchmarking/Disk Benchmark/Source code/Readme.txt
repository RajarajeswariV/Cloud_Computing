DISK BENCHMARK README FILE:
============================

The folder consists of all the .c source files and the respective command line arguments syntax are mentioned below.

The file DISKFinal has the code to measure the throughput and Latency of disk. A file is opened, sequentially or randomly read/written and then the time taken is calculated.
 
Steps for Execution:
=====================
Computing throughput and Latency on the Disk.

1) Execute file DISKFinal.c for Linux on the Terminal using” gcc –pthread DISKFinal.c”
 And run the output a.out file using the command “./a.out” .

2) The program will ask for how many thread to be executed for the process. 

Enter a number between 1 – 8.

3.) The program will now ask the user for how many blocksize of the file needed to be constructed.

Enter either 1 / 1KB / 1MB 

Note : 1KB = 1024 and 1 MB = 1024*1024 

Now Let’s consider the user entered 1 i.e. 1 thread and of block size 1024.

3) Processing starts and you have to wait for it to complete until the results are printed for you with the throughput and latency for each of the reads and writes.

4.) The program will ask the user if he/she wants to enter any other number of thread to calculate the Throughput and Latency for any other block size. 

5.) If the user enters ‘Y’, the program begins its execution and the steps from 2 to 4 are repeated for the number of threads entered by the user. If the user enters ‘N’, the program exits.

How the code works?
========================

1.)	The below thread is created to call the function makedata where we construct the data using fputc.

2.)	Once the file is constructed, the below functions are called to calculate the throughput and latency of memory.

Seqread() – This is where we try to copy a blocksize from the source file to destination file. Here the destination file is a temp file.

Then we calculate the performance by taking the difference of start and end time. 

With the help of the start and end times, we here calculate the throughput and latency.
 
3.)	Time taken is calculated by = “end_time” – “start_time”. All these times are converted to microseconds in the code with the help of TIMEVAL structure.

4.)	The same process is carried for seqwrite(), ranread(), ranwrite() with the help of fwrite and fread and rand function is used for random read here.

5.)	All the above is being called in main function with the help of thread creation. 


Sample output:
===============

CPU Consumption time for SR           = 0.002476 Seconds
threadid is 0
******** Lowest start time and Highest end time of CPU are calculated

CPU's lowest startime is 1455152333455748.000000 microsec

CPU's highest endtime is 1455152333458224.000000 microsec

The Difference between the lowest start time and highest end time is calculated below *******

The Difference in the above timings in seconds is : 2476.000000
Throughput for Sequential read speed = 2.535400 Mb/seconds
Latency for Sequential read          = 0.394415

*****************CREATING THREAD TO RANDOMLY WRITE INTO THE FILE GENERATED***************
Start time for random write  = 1455152333.458552
End time for random write    = 1455152333.461763
CPU Consumption time for RW           = 0.003211 Seconds
threadid is 0
******** Lowest start time and Highest end time of CPU are calculated

CPU's lowest startime is 1455152333458552.000000 microsec

CPU's highest endtime is 1455152333461763.000000 microsec

The Difference between the lowest start time and highest end time is calculated below *******

The Difference in the above timings in seconds is : 3211.000000
Throughput for Random write speed = 3.288086 Mb/seconds
Latency for Random write          = 0.304128

******************CREATING THREAD FOR RANDOMLY READING FROM THE FILE GENERATED***************
Start time for random read  = 1455152333.462094
End time for random read    = 1455152333.462496
CPU Consumption time for RR           = 0.000402 Seconds
threadid is 0
******** Lowest start time and Highest end time of CPU are calculated

CPU's lowest startime is 1455152333462094.000000 microsec

CPU's highest endtime is 1455152333462496.000000 microsec

The Difference between the lowest start time and highest end time is calculated below *******

The Difference in the above timings in seconds is : 402.000000
Throughput for Random read speed = 0.411621 Mb/seconds
Latency for Random read          = 2.429419
