MEMORY BENCHMARK README FILE:
----------------------------

Steps for Execution:
======================

Computing throughput and Latency on the memory.

1) Execute file MEMFinal.c for Linux on the Terminal using” gcc –pthread MEMFinal.c”
 And run the output a.out file using the command “./a.out” .

2) The program will ask for how many thread to be executed for the process. 

Enter a number between 1 – 8.

3.) The program will now ask the user for how many blocksize of memory needed to be constructed.

Enter either 1 / 1KB / 1MB 

Note : 1KB = 1024 and 1 MB = 1048576 

Now Let’s consider the user entered 1 i.e. 1 thread and of block size 1024.

3) Processing starts and you have to wait for it to complete until the results are printed for you with the throughput and latency for each of the reads and writes.

4.) The program will ask the user if he/she wants to enter any other number of thread to calculate the Throughput and Latency for any other block size. 

5.) If the user enters ‘Y’, the program begins its execution and the steps from 2 to 4 are repeated for the number of threads entered by the user. If the user enters ‘N’, the program exits.

How the code works?
=====================

1.)	The below thread is created to call the function makedata where we construct the data using randNum.
‘pthread_create(&threads[t], NULL, makedata, (void*)t)’

2.)	Once the memory is constructed, the below functions are called to calculate the throughput and latency of memory.

Seqread() – This is where we try to copy a blocksize from the source file to destination file. Here the destination file is a temp file.

Then we calculate the performance by taking the difference of start and end time. 

Srperformance() – With the help of the start and end times, we here calculate the throughput and latency.
 
3.)	Time taken is calculated by = “end_time” – “start_time”. All these times are converted to microseconds in the code with the help of TIMEVAL structure.

4.)	The same process is carried for seqwrite(), ranread(), ranwrite() with the help of memcpy and strncpy and rand function is used for random read here.

5.)	All the above is being called in main function with the help of thread creation. 

Sample output:
==============

Constructing the file with random numbers..

************* CREATING THREAD TO SEQUENTIALLY READ THE FILE GENERATED******************.

Start time for Sequential read    = 1455150935.980781
End time for Sequential read       = 1455150935.981605
CPU Consumption time for SR       = 0.000824 Seconds
Throughput for Sequential read    = 611.577546
Latency for Sequential read       = 0.823975 nanoseconds

**************** CREATING THREAD TO SEQUENTIALLY WRITE INTO THE FILE GENERATED**************

Start time for sequential write  = 1455150935.981724
End time for sequential write    = 1455150935.982533
CPU Consumption time for SW      = 0.000809 Seconds
Throughput for Sequential write  = 622.933098
Latency for Sequential write     = 0.808954 nanoseconds

******************CREATING THREAD FOR RANDOMLY READING FROM THE FILE GENERATED***************

Start time for Random Read = 1455150935.982627
End time for Random Read     = 1455150935.982740
CPU Consumption time for RR  = 0.000113 Seconds
Throughput for random read   = 4459.097046
Latency for Random read      = 0.113010 nanoseconds

*****************CREATING THREAD TO RANDOMLY WRITE INTO THE FILE GENERATED***************

Start time for Random write   = 1455150935.982822 msec
End time for Random Write      = 1455150935.984179 msec
CPU Consumption time for RW    =  0.001357 Seconds
Throughput for Random Write    = 371.330288
Latency for Random write       = 1.357079 nanoseconds

Do you wish to continue with any other inputs ?n
