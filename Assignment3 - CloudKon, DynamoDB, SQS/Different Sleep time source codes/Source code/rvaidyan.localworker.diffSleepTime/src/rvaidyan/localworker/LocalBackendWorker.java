package rvaidyan.localworker;

import java.util.concurrent.ConcurrentLinkedQueue;

public class LocalBackendWorker implements Runnable {

	ConcurrentLinkedQueue<String> taskQueue;
	int threadId;
		public LocalBackendWorker(ConcurrentLinkedQueue<String> queue, int threadId){
				this.taskQueue = queue;
				this.threadId = threadId;
	   }

	@Override
	public void run() {
		// TODO Auto-generated method stub
		Thread currentThread = Thread.currentThread();
		String taskData;
		
		try 
		{
			System.out.println("Starting Thread : " + new Integer(threadId).toString());
			while( ( taskData = this.taskQueue.poll())!=null )
			{
		//execute task in task node
				String[] splitTaskData =taskData.split(" ");
				long milliseconds = Integer.parseInt(splitTaskData[1]);
				currentThread.sleep(milliseconds);
				
				System.out.println("\nI AM THREAD NO. " + new Integer(threadId).toString());
				System.out.println("******************");
				System.out.println("I am sleeping for " + splitTaskData[1]);
				System.out.println("Successfully Executed the sleep task of : " + splitTaskData[1] + " msecs" + " from the assigned task number : " + splitTaskData[0]+ " in the input file");
				System.out.println("*************************************************************************************************");
				
			}
			   
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
