/*
 ============================================================================
 Name        : CPUbkup.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#include<time.h>

struct timeval start_time, end_time;
struct tm ct, ct1, cpu_s, cpu_e;
FILE *fp;

int main(int argc, char *argv[])
{
	int i;
	int a = 5, b = 3, c = 5, d = 10, e = 4;

    fp = fopen("CPUTimer.txt","w+");
    if(fp == NULL)
    {
    	printf("Error in opening/creating the text file !!");
    	exit(1);
    }
	time_t currenttime, wantedtime;
	time_t cpu_starttime, cpu_endtime;
	int cur_min,wan_min, cur_sec, wan_sec, tot_cur_min, tot_wan_min;
	int cpu_start_sec = 0, cpu_end_sec = 0;
	currenttime = time(NULL);
	wantedtime = time(NULL) + 600;
	ct = *localtime(&currenttime);
	ct1 = * localtime(&wantedtime);
	cur_min = ct.tm_min;
	cur_sec = ct.tm_sec;
	wan_sec = ct1.tm_sec;
	wan_min = ct1.tm_min;
	tot_cur_min = (cur_min * 60) + cur_sec;
	tot_wan_min = (wan_min * 60) + wan_sec;

	cpu_starttime = time(NULL);
	cpu_s = *localtime(&cpu_starttime);
	cpu_start_sec = cpu_s.tm_sec;

	fprintf(fp, "\nTHIS OUTPUT PRINTS INSTRUCTIONS IN INTERVAL OF 1 SECOND TAKEN BY THE CPU. \n");
	fprintf(fp, "*************************************************************************** \n \n");
do
 {
	if(cpu_start_sec != 0)
	{
		fprintf(fp,"\nCPU's START TIME IS : %d \n", cpu_start_sec);
		fprintf(fp, "**************************");
	}/*
	else if(cpu_start_sec == 0)
	{
		fprintf(fp,"\nStart sec of the cpu is : %d \n", cpu_start_sec);
	}*/
	do
	{
		cpu_starttime = time(NULL);
		cpu_endtime = time(NULL) + 1;
		cpu_s = *localtime(&cpu_starttime);
		cpu_e = * localtime(&cpu_endtime);
		cpu_start_sec = cpu_s.tm_sec;
		cpu_end_sec = cpu_e.tm_sec;

		gettimeofday(&start_time, NULL);

			//printf("\nstartime is %ld sec %ld microsec\n",start_time.tv_sec,start_time.tv_usec);
			fprintf(fp,"\nStartime before the operations is %ld sec %ld microsec\n",start_time.tv_sec,start_time.tv_usec);
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

				fprintf(fp,"Endtime after the operations %ld sec %ld microsec\n",end_time.tv_sec,end_time.tv_usec);

				long diff  = (end_time.tv_sec-start_time.tv_sec)*1000000 + (end_time.tv_usec-start_time.tv_usec);
				fprintf(fp,"CPU Utilization time is : %lf\n",(double)diff/1000000);
				cpu_starttime = time(NULL);
				cpu_s = *localtime(&cpu_starttime);
				cpu_start_sec = cpu_s.tm_sec;

	 }

	while(cpu_start_sec < cpu_end_sec);
	fprintf(fp,"\nCPU's END TIME IS : %d\n", cpu_end_sec);
	fprintf(fp, "************************ \n \n");
	fprintf(fp,"PRINTING INSTRUCTIONS FOR THE NEXT INTERVAL OF SECONDS \n");
	fprintf(fp, "****************************************************** \n \n");

		currenttime = time(NULL);
		ct = *localtime(&currenttime);
		cur_min = ct.tm_min;
		cur_sec = ct.tm_sec;
		tot_cur_min = (cur_min *60) + cur_sec;
 }
while (tot_cur_min < tot_wan_min);

fprintf(fp,"\nTHIS PROGRAM RAN FOR 10 MINUTES AND THUS EXITING OUT.......\n");
fprintf(fp, "PLEASE CLOSE THIS FILE..\n \n");
fclose(fp);
exit(0);
}
