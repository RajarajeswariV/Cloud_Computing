/*

============================================================================
 Name        : CPUFinal.c
 Author      : Rajarajeswari Vaidyanathan
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style

============================================================================
 */

//Standard libraries

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>


int no_of_threads;
long cpu_iteration = 100000000;
int rc;
char choice;

struct time_zone {
  int tz_minuteseast; /* east of GMT */
  int tz_dsttime;     /* set if daylight saving time in affect */
};

struct time_array
{
	long start_time_arr, end_time_arr;
};

struct time1_array
{
	long start_arr, end_arr;
};
struct time_array gigaflops[100];
struct time1_array gigaiops[100];

//Start time and end time is declared in structure Timeval globally.
struct timeval start_time, end_time, start, end;

//time zones is declared in structure time_zone globally so all functions can use it.
struct time_zone *tzone1, *tzone2;

//*************** Function GFLOPS being called *****************************************************

void *gflops(void *id)
 {
	struct timeval start_time, end_time;
	long threadid;
	threadid = (long)id;
	long int i = 0;
	double a = 37.5, b = 47.5, c = 55.5, d = 77.5, e = 99.3;

//Get the start time before starting the below for loop
	gettimeofday(&start_time, NULL);

	for(i=0; i < 100000000; i++)
	{
		a*b*c;c*d*e;c*c*c;d*c*a*b;a+b;
		b+c;c-a;c*c*a*a*b;
		a-b;d-c;e-a;a*c;c*b;d-c;
		a/b;c/d;b/a;c*b;b*b;a*c;
		a+b;c+d;a*b;c*d;
		a-b;e-d;a+e;a+b;a+c;a+d;b+d;
		a+c;d/e;a*b*c*d*e;
		b*c;d*e;a*b*c*c*d*c*d*a;

	}

//Get the end time after ending the loop/operation.
	gettimeofday(&end_time, NULL);

	gigaflops[threadid].start_time_arr=(start_time.tv_sec)*1000000 + start_time.tv_usec;

	gigaflops[threadid].end_time_arr=(end_time.tv_sec)*1000000 + end_time.tv_usec;

	pthread_exit(NULL);
 }
// End of function gflops and the control is returned back to the main function.

//Function - performance_gflops is being called via main to display the performance calculated.

void *performance_gflops(void *id)
 {
	long threadid;
	threadid = (long)id;

	int i,j;

	long sgflop,egflop;

	sgflop = gigaflops[threadid].start_time_arr;

	egflop = gigaflops[threadid].end_time_arr;

// Start time and end times are stored in an array to calculate the Lowest Start time and Highest end time of the CPU.

	for(i=1;i<no_of_threads;i++)
	{
		if(gigaflops[i].start_time_arr < sgflop)
	   		sgflop = gigaflops[i].start_time_arr;
	}

	printf("CPU's lowest startime is %ld microsec\n",sgflop);

	for(j=0; j<no_of_threads;j++)
	{
		if(gigaflops[j].end_time_arr > egflop)
		  	egflop = gigaflops[j].end_time_arr;
	}

	printf("CPU's highest endtime is %ld microsec\n",egflop);

	double dgflop =((double)(egflop - sgflop))/1000000.0;

	printf("Total time for GFLOPS (HighestEndTime - Loweststarttime) : %lf seconds \n",dgflop);

	double ggflop = (double)cpu_iteration;
	double hgflop = (ggflop * no_of_threads) /(dgflop);
	printf(" \nFinally the processor speed to perform GFLOPS operations : %lf seconds \n \n", hgflop / cpu_iteration);
	pthread_exit(NULL);
 }

//*************************** GIOPS FUNCTION BEING CALLED **************************

void *giops(void *id)
 {
	struct timeval start, end;
	long threadid1;
	threadid1 = (long) id;
	long int i = 0;
	int a = 37567, b = 4742, c = 55232, d = 7722, e = 929;


//Get the start time before starting the below for loop
	gettimeofday(&start, NULL);

	for(i=0; i < 100000000; i++)
	{
		a*b*c;c*d*e;c*c*c;d*c*a*b;a+b;
		b+c;c-a;c*c*a*a*b;
		a-b;d-c;e-a;a*c;c*b;d-c;
		a/b;c/d;b/a;c*b;b*b;a*c;
		a+b;c+d;a*b;c*d;
		a-b;e-d;a+e;a+b;a+c;a+d;b+d;
		a+c;d/e;a*b*c*d*e;
		b*c;d*e;a*b*c*c*d*c*d*a;
	}

//Get the end time after ending the loop/operation.
	gettimeofday(&end, NULL);

	gigaiops[threadid1].start_arr=(start.tv_sec)*1000000 + start.tv_usec;
	gigaiops[threadid1].end_arr=(end.tv_sec)*1000000 + end.tv_usec;

	pthread_exit(NULL);
 }
//End of function giops and the control is returned back to the main function.

//Function - performance_giops is being called via main to display the performance calculated.

void *performance_giops(void *id)
 {
	long threadid;
	threadid = (long)id;

	int x,y;

	long sgiop,egiop;

	sgiop = gigaiops[threadid].start_arr;
	egiop = gigaiops[threadid].end_arr;

	for(x=1;x<no_of_threads;x++)
	{
		if(gigaiops[x].start_arr < sgiop)
			sgiop = gigaiops[x].start_arr;
	}

	printf("\nCPU's lowest startime is %ld microsec\n",sgiop);

// Start time and end times are stored in an array to calculate the Lowest Start time and Highest end time of the CPU.
	for(y=0; y<no_of_threads;y++)
	{
		if(gigaiops[y].end_arr > egiop)
		  	egiop = gigaiops[y].end_arr;
	}

	printf("CPU's highest endtime is %ld microsec\n",egiop);

	double diop = ((double)(egiop-sgiop))/1000000;

	printf("Total time for IOPS (HighestEndTime - Loweststarttime) : %lf seconds \n",diop);

	double giop = (double)cpu_iteration;
	double hiop = (giop * no_of_threads) / (diop);
	printf("\nFinally, The Processor speed to perform GIOPS operations : %lf seconds \n \n",hiop / cpu_iteration);

	pthread_exit(NULL);
 }

//Main function is started from below. Program starts from here
int main(int argc, char *argv[])
{
	do
	{
        	printf("Program execution begins here... \n \nPlease note : The number of threads should be less than or equal to 8. \n \n");
  				printf("Enter the number of threads to be performed : ");

				fflush(stdout);
				scanf("%d",&no_of_threads);
				fflush(stdout);
				long t;

			if (no_of_threads > 8)
			{
				printf("\n This program can handle maximum of 8 threads as per the requirement. Please retry again \n");
				break;
			}
//Number of threads is already passed at the begining of the program
// ****** Calculating GFLOPS ***************
				printf("\n************************************** Calculating GFLOPS **************************************\n");
				pthread_t threads[no_of_threads];
				void *status;
				int rc;

				gettimeofday(&start_time, NULL);

				printf("**********Threads are created for gflop with respect to the number of threads inputted : %d **********\n \n",no_of_threads);

				for(t=0; t < no_of_threads; t++)
				{
					rc = pthread_create(&threads[t], NULL, gflops, (void*)t);
					if (rc)
					{
						printf("ERROR; return code from pthread_create() is %d\n", rc);
						exit(-1);
					}
				}

				for(t=0;t<no_of_threads;t++)
				{
					pthread_join(threads[t],&status);
				}

// End time is calculated after performing gflops function.
				gettimeofday(&end_time, NULL);

//Creating the thread to do the performance evaluation and display
				pthread_t fpthreads[no_of_threads];

				for(t=0; t < 1; t++)
				{
					rc = pthread_create(&fpthreads[t], NULL, performance_gflops, (void *)t);

					if (rc){

						printf("ERROR; return code from pthread_create() for Performance evaluation is %d\n", rc);
						exit(-1);
					}
				}

				for(t = 0;t < no_of_threads; t++)
				{
					pthread_join(fpthreads[t],&status);
				}

//Number of threads is already passed at the beginning of the program
// ****** Calculating GIOPS *****************************
				printf("\n************************************* Calculating GIOPS *********************************************\n");
				pthread_t ithreads[no_of_threads];

				gettimeofday(&start, NULL);

				printf("*********** Threads are created for giop with respect to the number of threads inputted : %d ***************\n \n",no_of_threads);
				for(t=0; t < no_of_threads; t++)
				{
					rc = pthread_create(&ithreads[t], NULL, giops, (void*)t);
					if (rc)
					{
						printf("ERROR; return code from pthread_create() is %d\n", rc);
						exit(-1);
					}
				}

				for(t=0;t<no_of_threads;t++)
				{
					pthread_join(ithreads[t],&status);
				}

// End time is calculated after performing giops function.
				gettimeofday(&end, NULL);

//Creating the thread to do the performance evaluation and display
				pthread_t ipthreads[no_of_threads];

				for(t=0; t < 1; t++)
				{
					rc = pthread_create(&ipthreads[t], NULL, performance_giops, (void *)t);

					if (rc)
					{
						printf("ERROR; return code from pthread_create() for Performance evaluation - IOPS is %d\n", rc);
						exit(-1);
					}
				}

				for(t = 0;t < no_of_threads; t++)
				{
					pthread_join(ipthreads[t],&status);
				}

				fflush(stdout);
				printf("Do you wish to execute the program for any other number of threads ?? (Y/N) \n");
				fflush(stdout);
				scanf(" %c", &choice);
				fflush(stdout);

	}

  	while (choice == 'y' || choice == 'Y'); //Performing the main function in a loop until the user wants to exit the program.
  	return 0;


  	pthread_exit(NULL);
  	exit(0);
}
