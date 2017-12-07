/*
 ============================================================================
 Name        : DISKFinal.c
 Author      : Rajarajeswari Vaidyanathan
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <memory.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#define KB 1024
#define BYTE 1
#define MB (1024 * 1024)

// Structure for time interval of start and end time for seq read, seq write, ran read, ran write.
struct timeval start_time, end_time, start, end, startTime, endTime, Starttime, Endtime;

long block_size;

struct time_array
{
	long start_time_arr, end_time_arr;
};

struct time_array seqwr[30]; //Array for sequential write
struct time_array seqrd[30]; //Array for sequential read
struct time_array ranwr[30]; //Array for random write
struct time_array ranrd[30]; //Array for random read

int counter, r = 0;

int no_of_threads;

double s_t, e_t, t_t;

char choice;

FILE *fp;

char buffer[BYTE];

void makedata(long n)
{
	printf("Constructing the file with random numbers of that block size.. . \n");

	int i, j;

	char a = r;

	for(i = 0; i < BYTE; i++)
	{
		fp = fopen("DiskFile.txt", "w+");
		if(fp == NULL)
		{
			printf("Error in opening/creating the text file !!");
			exit(1);
		}
		else
		{
			for(j=0; j < block_size; j++)
			{
				fputc(a, fp);
			}
		}
	}
}

//**********************Sequential write function is called by main.

void *seqwrite(void *id)
{
	long threadid;
	threadid = (long)id;

	struct timeval start, end;

	long sw; //Sequential Write

	int i,j;

	double ssw, esw, tsw;

	gettimeofday(&start,NULL);

	for(sw=0; sw < block_size ; sw++)
	{
		fwrite(&buffer[0], 1, BYTE, fp);
	}

	gettimeofday(&end,NULL);

	seqwr[threadid].start_time_arr=(start.tv_sec)*1000000 + start.tv_usec;
	seqwr[threadid].end_time_arr=(end.tv_sec)*1000000 + end.tv_usec;

// Calculating the consumption time for seq write and throughput.

	s_t = start.tv_sec + (start.tv_usec / 1000000.0);
	e_t = end.tv_sec + (end.tv_usec / 1000000.0);

	t_t = e_t - s_t ;

	ssw = seqwr[threadid].start_time_arr;
	esw = seqwr[threadid].end_time_arr;

	for(i=1;i<no_of_threads;i++)
	{
		if(seqwr[i].start_time_arr < ssw)
			ssw = seqwr[i].start_time_arr;
	}

	printf("CPU's lowest startime is %lf microsec\n",ssw);

	for(j=0; j<no_of_threads;j++)
	{
		if(seqwr[j].end_time_arr > esw)
			esw = seqwr[j].end_time_arr;
	}

	printf("\nCPU's highest endtime is %lf microsec\n",esw);

	tsw = esw - ssw; // Calculating the CPU time taken to complete instructions.

	printf("Throughput for Sequential write speed = %lf Mb/seconds \n", (((block_size / t_t) * 1000)) / (1024*1024));

	printf("Latency for Sequential write          = %lf \n \n", (1) / (block_size * t_t));

	pthread_exit(NULL);

}

// *********************Sequential read function is being called by main.
void *seqread(void* id)
{
		long threadid;
		threadid = (long)id;

		struct timeval start, end;

		long sr; //Sequential read

		int i,j;

		double ssr, esr, tsr; // Start and end times for sequential read.

		gettimeofday(&start,NULL);
		for(sr=0; sr < block_size ; sr++)
		{
			fread(&buffer[0], BYTE, 1, fp);
		}

		gettimeofday(&end,NULL);

		seqrd[threadid].start_time_arr=(start.tv_sec)*1000000 + start.tv_usec;
		seqrd[threadid].end_time_arr=(end.tv_sec)*1000000 + end.tv_usec;

// Calculating the consumption time for seq read and throughput.
		s_t = start.tv_sec + (start.tv_usec / 1000000.0);
		e_t = end.tv_sec + (end.tv_usec / 1000000.0);

		t_t = e_t - s_t;

		ssr = seqrd[threadid].start_time_arr;
		esr = seqrd[threadid].end_time_arr;

		for(i=1;i<no_of_threads;i++)
		{
			if(seqrd[i].start_time_arr < ssr)
				ssr = seqrd[i].start_time_arr;
		}

		printf("CPU's lowest startime is %lf microsec\n",ssr);

		for(j=0; j<no_of_threads;j++)
		{
			if(seqrd[j].end_time_arr > esr)
				esr = seqrd[j].end_time_arr;
		}

		printf("\nCPU's highest endtime is %lf microsec\n",esr);

		tsr =(esr - ssr);

		printf("Throughput for Sequential read speed = %lf MB/seconds \n", (((block_size / t_t) * 1000)) / (1024*1024));

		printf("Latency for Sequential read          = %lf \n \n", (1) / (block_size * t_t));

		pthread_exit(NULL);
}


//*********** Random write function being called here from main **************

void *ranwrite(void* id)
{
		long threadid;
		threadid = (long)id;

		struct timeval start, end;

		long rw; //Random write

		int i,j;

		double srw, erw, trw; //Start Random Write and End Random write time

		gettimeofday(&start,NULL);

		for(rw = 0; rw < block_size ; rw++)
		{
			int r = rand()%block_size;
			fseek(fp, r, SEEK_SET);
			fwrite(buffer, 7899, BYTE, fp);
		}

		gettimeofday(&end,NULL);

		ranwr[threadid].start_time_arr=(start.tv_sec)*1000000 + start.tv_usec;
		ranwr[threadid].end_time_arr=(end.tv_sec)*1000000 + end.tv_usec;

// Calculating the consumption time for seq write and throughput.

		s_t = start.tv_sec + (start.tv_usec / 1000000.0);
		e_t = end.tv_sec + (end.tv_usec / 1000000.0);

		t_t = e_t - s_t;

		srw = ranwr[threadid].start_time_arr;
		erw = ranwr[threadid].end_time_arr;

		for(i=1;i<no_of_threads;i++)
		{
			if(ranwr[i].start_time_arr < srw)
				srw = ranwr[i].start_time_arr;
		}

		printf("CPU's lowest startime is %lf microsec\n",srw);

		for(j=0; j<no_of_threads;j++)
		{
			if(ranwr[j].end_time_arr > erw)
				erw = ranwr[j].end_time_arr;
		}

		printf("\nCPU's highest endtime is %lf microsec\n",erw);

		trw = (erw - srw);

		printf("Throughput for Random write speed = %lf MB/seconds \n", (((block_size / t_t) * 1000)) / (1024*1024));

		printf("Latency for Random write          = %lf \n \n", (1) / (block_size * t_t));

		pthread_exit(NULL);
}


//********* Random read function being called from main.**************

void *ranread(void* id)
{
		long threadid;
		threadid = (long)id;

		struct timeval start, end;

		long rr; //Random write

		int i,j;

		double srr, err, trr; //Start Random Read and End Random Read time

		gettimeofday(&start,NULL);

		for(rr = 0; rr < block_size ; rr++)
		{
			int r = rand()%KB;
			fseek(fp,r,SEEK_SET);
		}

		gettimeofday(&end,NULL);

		ranrd[threadid].start_time_arr=(start.tv_sec)*1000000 + start.tv_usec;
		ranrd[threadid].end_time_arr=(end.tv_sec)*1000000 + end.tv_usec;

// Calculating the consumption time for seq write and throughput.

		s_t = start.tv_sec + (start.tv_usec / 1000000.0);
		e_t = end.tv_sec + (end.tv_usec / 1000000.0);

		t_t = e_t - s_t;

		srr = ranrd[threadid].start_time_arr;
		err = ranrd[threadid].end_time_arr;

		for(i=1;i<no_of_threads;i++)
		{
			if(ranrd[i].start_time_arr < srr)
				srr = ranrd[i].start_time_arr;
		}

		printf("CPU's lowest startime is %lf microsec\n",srr);

		for(j=0; j<no_of_threads;j++)
		{
			if(ranrd[j].end_time_arr > err)
				err = ranrd[j].end_time_arr;
		}

		printf("\nCPU's highest endtime is %lf microsec\n",err);

		trr =(err - srr);

		printf("Throughput for Random read speed = %lf Mb/seconds \n", (((block_size / t_t) * 1000)) / (1024*1024));

		printf("Latency for Random read          = %lf \n \n", ((1) / (block_size * t_t)));

		pthread_exit(NULL);
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
		long n = 528403;

// ****************** Calling Makedata function to construct the file.**************

		printf("***** Calling Function - makedata() to construct a file and generate random numbers in it ****** \n \n");
		makedata(n);

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


// ***************************Creating thread for sequential read ********************

			pthread_t seqrthreads[no_of_threads];

			gettimeofday(&start, NULL);

			for(a = 0; a < no_of_threads; a++)
			{
				printf("**************** CREATING THREAD TO SEQUENTIALLY READ INTO THE FILE GENERATED**************\n\n");
				rc = pthread_create(&seqrthreads[a],NULL, seqread, (void*)a);

				if (rc)
				{
			         printf("ERROR; return code from pthread_create() for sequential read is %d\n", rc);
			         exit(-1);
				}
			}

			for(b = 0; b < no_of_threads; b++)
			{
				pthread_join(seqrthreads[b],&status);
			}

			gettimeofday(&end, NULL);

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

//************* Creating threads for random Read****************

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

		fclose(fp); //Closing the file appropriately.

		fflush(stdout);
		printf("Do you wish to continue with any other inputs ? Reply with 'Y' or 'N'");
		fflush(stdout);
		scanf(" %c", &choice);
		fflush(stdout);
	}

	while (choice == 'y' || choice == 'Y');
	return 0;

pthread_exit(NULL);
exit(0);
}
