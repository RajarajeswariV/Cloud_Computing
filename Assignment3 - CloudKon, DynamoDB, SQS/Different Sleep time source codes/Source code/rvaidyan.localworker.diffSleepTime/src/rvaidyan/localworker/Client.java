package rvaidyan.localworker;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ConcurrentLinkedQueue;

public class Client {

	public static void main(String[] args) throws InterruptedException
	{
	
		ConcurrentLinkedQueue<String> taskQueue = new ConcurrentLinkedQueue<String>();
		ManageInputFile manageInputFile = new ManageInputFile();
				
		if(args.length != 2) 
		{
			System.out.println("USAGE: Client <number of threads> <workload input file>");
			System.exit(1);
		}
		
		//Getting command line arguments from the user programmatically.
		
		Integer numOfThreads = Integer.parseInt(args[0]);
		String fileName = args[1];
		
		List<Thread> workerThreads = new ArrayList<Thread>(); //Creating list for workerThreads.

		ArrayList<String> fileData = manageInputFile.readInputFile(fileName); //Reading the Input file.

		prepareTaskQueue(fileData, taskQueue); //Preparing the Task Queue.
		
		System.out.println("Number of threads entered : " + numOfThreads) ;
	
		long startTimemilli = System.currentTimeMillis();
		System.out.println("Execution Start time before starting the threads is : " + startTimemilli);
		System.out.println("All threads started executing concurrently.");
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
		System.out.println("Execution End time after completion of all the threads is : " + stopTimemilli);
		System.out.println("\n********* HENCE ELAPSED TIME (in msecs) = " + (stopTimemilli - startTimemilli) + " msecs **********");
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
			taskQueue.add(taskData);
		}
	}
}
