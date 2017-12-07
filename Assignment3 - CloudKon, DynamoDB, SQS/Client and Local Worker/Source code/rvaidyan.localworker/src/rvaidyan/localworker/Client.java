package rvaidyan.localworker;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ConcurrentLinkedQueue;

public class Client {

	public static void main(String[] args) throws InterruptedException
	{
	
		ConcurrentLinkedQueue<String> taskQueue = new ConcurrentLinkedQueue<String>();
		ManageInputFile manageInputFile = new ManageInputFile();
				
		if(args.length != 4) 
		{
			System.out.println("USAGE: Client <number of tasks to be written to input file> <sleep task in the format : 'sleep <milliseconds>'> <number of threads> <workload input file>");
			System.exit(1);
		}
		
		//Getting command line arguments from the user programmatically.
		
		Integer noOfTasks = Integer.parseInt(args[0]);
		Integer sleepTime = Integer.parseInt(args[1]);
		Integer numOfThreads = Integer.parseInt(args[2]);
		String fileName = args[3];
		
	    manageInputFile.generateInputFile(fileName, noOfTasks, sleepTime);
	    
		List<Thread> workerThreads = new ArrayList<Thread>(); //Creating list for workerThreads.

		ArrayList<String> fileData = manageInputFile.readInputFile(fileName); //Reading the Input file.

		prepareTaskQueue(fileData, taskQueue); //Preparing the Task Queue.
		
		System.out.println("Number of threads entered : " + numOfThreads) ;
	
		long startTimemilli = System.currentTimeMillis();
		System.out.println("\nExecution Start time before starting the threads is : " + startTimemilli);
		System.out.println("\nALL THREADS STARTED EXECUTING CONCURRENTLY.");
		System.out.println("*************************************************************************************");
		System.out.println("**** STATISTICS OF THE THREADS EXECUTION AND THE ORDER THEY COMPLETE (in msecs) *****");
		System.out.println("**************************************************************************************");								
		for (int th = 1; th <= numOfThreads; th++)
		{
			Thread threads = new Thread(new LocalBackendWorker(taskQueue, th));
			workerThreads.add(threads);	
		}
		
		for (int i = 0; i < workerThreads.size();i++)
		{
			workerThreads.get(i).start(); //Start all threads simultaneously.
		}
		
		for (int i = 0; i < workerThreads.size();i++)
		{
			workerThreads.get(i).join(); //Wait for all threads to complete and throw the results.
		}
		
		long stopTimemilli = System.currentTimeMillis();
		System.out.println("\nExecution End time after completion of all the threads is : " + stopTimemilli);
		System.out.println("\n                 HENCE ELAPSED TIME (in msecs) = " + (stopTimemilli - startTimemilli) + " msecs        ");
		System.out.println(" \n************************* CLIENT - LOCAL WORKER ENDED SUCCESSFULLY ************************** ");

	}    
		
	public static void prepareTaskQueue(ArrayList<String> inputFileData, ConcurrentLinkedQueue<String> taskQueue)
	{
		String data;
		for(int i=0; i < inputFileData.size(); i++)
		{
			data = inputFileData.get(i).toString();
			String[] splitData = data.split(" ");
			int taskId = i+1;
			String taskData = taskId + " " + splitData[1];
			System.out.println("hello alllllll task data is " + taskData);
			taskQueue.add(taskData);
		}
	}
	
}
