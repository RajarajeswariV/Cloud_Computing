/*
 ============================================================================
 Name        : MEMFinal.c
 Author      : Rajarajeswari Vaidyanathan
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <memory.h>
#include <sys/time.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>

// Structure for time interval of start and end time for seq read, seq write, ran read, ran write.
struct timeval start_time, end_time, start, end, startTime, endTime, Starttime, Endtime;

long block_size;

char content[9999999], choice; // Source file size

int counter, randNum = 0;

long n = 5284322, lc;

int no_of_threads;

double s_t, e_t, t_t;

pthread_mutex_t count_mutex;
pthread_mutex_t count_mutex1;


void makedata(long n)
{
	printf("Constructing the file with random numbers.. \n");

	int counter;

	for(counter=0; counter < n; ++counter)
	{
		randNum = 97 * (rand() / (RAND_MAX + 1.0)); //pick a Number between 0 and 97.
		randNum = randNum + 97; // ASCII code for 'a' is 97, so add 97 to the random number to get a lower case letter.
		content[counter] = (char) randNum;

	}
}

// Sequential read function is being called by main.
void *seqread(void *id)
{
	struct timeval start_time, end_time;
	long threadid;
	threadid = (long)id;
	long sr; //Sequential Read
	char temp_sr[1048577];

	gettimeofday(&start_time,NULL);
	for(sr=0; sr < lc; sr += block_size)
	{
		memcpy(temp_sr, content, block_size);
	}
	gettimeofday(&end_time,NULL);

	pthread_exit(NULL);
}
// Calculating the consumption time for seq read and throughput.
void srperformance()
{
	printf("\nStart time for Sequential read    = %lf \n",start_time.tv_sec + (start_time.tv_usec / 1000000.0));
	printf("End time for Sequential read       = %lf \n",end_time.tv_sec + (end_time.tv_usec / 1000000.0));

		s_t = start_time.tv_sec + (start_time.tv_usec / 1000000.0);
		e_t = end_time.tv_sec + (end_time.tv_usec / 1000000.0);
		t_t = e_t - s_t;

		printf("CPU Consumption time for SR       = %lf Seconds \n",t_t);

		printf("Throughput for Sequential read    = %lf \n", (n/t_t) / (1024*1024));

		printf("Latency for Sequential read       = %lf nanoseconds \n\n", (e_t - s_t) / CLOCKS_PER_SEC * 1000000);
}
//**********************Sequential write function is called by main.
void *seqwrite(void *id)
{
	struct timeval start, end;
	long threadid;
	threadid = (long)id;
	long sw; //Sequential Write
	char temp_sw[1048577];

	gettimeofday(&start,NULL);
	for(sw=0; sw < lc; sw += block_size)
	{
		strncpy(temp_sw, content, block_size);
	}
	gettimeofday(&end,NULL);

	pthread_exit(NULL);
}

// Calculating the consumption time for seq write and throughput.
void swperformance()
{
	printf("Start time for sequential write  = %lf \n",start.tv_sec + (start.tv_usec / 1000000.0));
	printf("End time for sequential write    = %lf \n",end.tv_sec + (end.tv_usec / 1000000.0));

		s_t = start.tv_sec + (start.tv_usec / 1000000.0);
		e_t = end.tv_sec + (end.tv_usec / 1000000.0);

		t_t = e_t - s_t;
		printf("CPU Consumption time for SW      = %lf Seconds \n",t_t);

		printf("Throughput for Sequential write  = %lf \n", (n/t_t) / (1024*1024));

		printf("Latency for Sequential write     = %lf nanoseconds \n\n", (e_t - s_t) / CLOCKS_PER_SEC * 1000000);
}

//*******Random read function being called by main.********

void *ranread(void *id)
{
	struct timeval startTime, endTime;
	long threadid;
	threadid = (long)id;
	long rr,v; //Random read
	char temp_rr[1048576];

	pthread_mutex_lock(&count_mutex);
	gettimeofday(&startTime, NULL);

	for(rr = 0; rr < 1; rr++)
	{
		v = rand() % 100;
		memcpy(&temp_rr[v], &content[v], block_size);

	}
	gettimeofday(&endTime, NULL);
	pthread_mutex_unlock(&count_mutex);

	pthread_exit(NULL);
}

// Calculating the consumption time for random read and throughput.

void rrperformance()
{
			printf("\nStart time for Random Read = %lf \n",startTime.tv_sec + (startTime.tv_usec / 1000000.0));
			printf("End time for Random Read     = %lf \n",endTime.tv_sec + (endTime.tv_usec / 1000000.0));

			s_t = startTime.tv_sec + (startTime.tv_usec / 1000000.0);
			e_t = endTime.tv_sec + (endTime.tv_usec / 1000000.0);
			t_t = e_t - s_t;

			printf("CPU Consumption time for RR  = %lf Seconds \n",t_t);

			printf("Throughput for random read   = %lf \n", (n/t_t) / (1024*1024));

			printf("Latency for Random read      = %lf nanoseconds \n \n", (e_t - s_t) / CLOCKS_PER_SEC * 1000000);
}

//********* Random write function being called from main.**************

void *ranwrite(void *id)
{
	struct timeval Starttime, Endtime;
	long threadid;
	threadid = (long)id;
	long rw,x; //Random Write
	char temp_rw[1048576];

	pthread_mutex_lock(&count_mutex1);

	gettimeofday(&Starttime, NULL);
	for(rw = 0; rw < 1; rw++)
	{
		x = rand() % 100;
		strncpy(&temp_rw[x], &content[x], block_size);
	}
	gettimeofday(&Endtime, NULL);

	pthread_mutex_unlock(&count_mutex1);

	pthread_exit(NULL);
}

//****************** Calculating performance & throughput for Random write.

void rwperformance()
{

		printf("\nStart time for Random write   = %lf msec\n",Starttime.tv_sec + (Starttime.tv_usec / 1000000.0));
		printf("End time for Random Write      = %lf msec\n",Endtime.tv_sec + (Endtime.tv_usec / 1000000.0));

		s_t = Starttime.tv_sec + (Starttime.tv_usec / 1000000.0);
		e_t = Endtime.tv_sec + (Endtime.tv_usec / 1000000.0);
		t_t = e_t - s_t;

		printf("CPU Consumption time for RW    =  %lf Seconds \n",t_t);

		printf("Throughput for Random Write    = %lf \n", (n/t_t) / (1024*1024));

		printf("Latency for Random write       = %lf nanoseconds \n \n", (e_t - s_t) / CLOCKS_PER_SEC * 1000000);
}

int main()
{

	long a, b, c, d, e, f, g, h;
	void *status;
	int rc;


	do
	{
		fflush(stdout);
		printf("Enter the number of threads to be processed :");
		fflush(stdout);
		scanf("%d",&no_of_threads);
		printf("Enter the size of the memory block size. 'Please note': The sizes to be entered are in 1B, 1KB, 1MB :");
		fflush(stdout);
		scanf("%ld", &block_size);
		fflush(stdout);

	//*************** Constructing the file - makedata ****************
	// ****************** Calling Makedata function to construct the file.**************
		printf("***** Calling Function - makedata to construct a file and generate random numbers in it ****** \n \n");
		makedata(n);
			lc = n/no_of_threads;

	//************** Creating threads for Sequential read of the file*****************

		pthread_t seqrthreads[no_of_threads];

		gettimeofday(&start_time,NULL);

		for(a = 0; a < no_of_threads; a++)
		{
			printf("\n************* CREATING THREAD TO SEQUENTIALLY READ THE FILE GENERATED******************. \n");
			rc = pthread_create(&seqrthreads[a],NULL, seqread, (void*)a);

			if (rc)
				{
				         printf("ERROR; return code from pthread_create() for sequential read is %d\n", rc);
				         exit(-1);
				}
		}

		for(b=0; b < no_of_threads; b++)
		{
			pthread_join(seqrthreads[b],&status);
		}

		gettimeofday(&end_time, NULL);

		srperformance(); // Calling a function to perform the throughput and CPU consumption for sequential read.

	//********************* Threads created for sequential write ***********************

			pthread_t seqwthreads[no_of_threads];

			gettimeofday(&start, NULL);

			for(c = 0; c < no_of_threads; c++)
			{
				printf("**************** CREATING THREAD TO SEQUENTIALLY WRITE INTO THE FILE GENERATED**************\n\n");
				rc = pthread_create(&seqwthreads[c],NULL, seqwrite, (void*)c);

				if (rc)
					{
					         printf("ERROR; return code from pthread_create() for sequential write is %d\n", rc);
					         exit(-1);
					}
			}

			for(d=0; d < no_of_threads; d++)
			{
				pthread_join(seqwthreads[d],&status);
			}

			gettimeofday(&end, NULL);

			swperformance(); // calling function to calculate the throughput and CPU consumption for sequential write

	//************* Creating threads for random read ****************

			pthread_t ranrthreads[no_of_threads];

			gettimeofday(&startTime,NULL);

			for(e = 0; e < no_of_threads; e++)
			{
				printf("******************CREATING THREAD FOR RANDOMLY READING FROM THE FILE GENERATED***************\n");
				rc = pthread_create(&ranrthreads[e],NULL, ranread, (void*)e);

				if (rc)
				{
			         printf("ERROR; return code from pthread_create() is %d\n", rc);
			         exit(-1);
				}
			}

			for(f = 0; f < no_of_threads; f++)
			{
				pthread_join(seqrthreads[f],&status);
			}

			gettimeofday(&endTime, NULL);

			rrperformance(); // Function call for calculating the performance & throughput for Random read.

	//************* Creating threads for random write *******************

			pthread_t ranwthreads[no_of_threads];

			gettimeofday(&Starttime,NULL);

			for(g = 0; g < no_of_threads; g++)
			{
				printf("*****************CREATING THREAD TO RANDOMLY WRITE INTO THE FILE GENERATED*************** \n");
				rc = pthread_create(&ranwthreads[g],NULL, ranwrite, (void*)g);
				if (rc)
				{
			         printf("ERROR; return code from pthread_create() for random write is %d\n", rc);
			         exit(-1);
				}
			}
			for(h = 0; h < no_of_threads; h++)
			{
				pthread_join(ranwthreads[h],&status);
			}

			gettimeofday(&Endtime, NULL);

			rwperformance(); // Function call for calculating throughput and performance for random write.
			fflush(stdout);
			printf("Do you wish to continue with any other inputs ?");
			fflush(stdout);
			scanf(" %c", &choice);
			fflush(stdout);
	}

	while (choice == 'y' || choice == 'Y');
		return 0;


pthread_exit(NULL);
exit(0);
}
