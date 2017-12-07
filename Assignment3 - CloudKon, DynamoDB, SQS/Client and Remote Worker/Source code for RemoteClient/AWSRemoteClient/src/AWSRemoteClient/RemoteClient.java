package AWSRemoteClient;

import java.util.ArrayList;
import java.util.concurrent.ConcurrentLinkedQueue;

import com.amazonaws.AmazonClientException;
import com.amazonaws.auth.AWSCredentials;
import com.amazonaws.auth.profile.ProfileCredentialsProvider;
import com.amazonaws.regions.Region;
import com.amazonaws.regions.Regions;
import com.amazonaws.services.sqs.AmazonSQS;
import com.amazonaws.services.sqs.AmazonSQSClient;
import com.amazonaws.services.sqs.model.SendMessageRequest;

public class RemoteClient {

	public static void main(String[] args) throws Exception 
	{

		String RemoteTaskQueueName = "RemoteTasksQueue";
		AWSCredentials credentials = null;

		ConcurrentLinkedQueue<String> taskQueue = new ConcurrentLinkedQueue<String>();
		ManageInputFile manageInputFile = new ManageInputFile();

		if(args.length != 3) 
		{
			System.out.println("USAGE: Client <number of tasks to be written to input file> <sleep task in the format : 'sleep <milliseconds>'> <workload input file>");
			System.exit(1);
		}

		//Getting command line arguments from the user programmatically.

		Integer noOfTasks = Integer.parseInt(args[0]);
		Integer sleepTime = Integer.parseInt(args[1]);
		String fileName = args[2];

		manageInputFile.generateInputFile(fileName, noOfTasks, sleepTime); //Create the input file with respect to number of tasks and sleep time.
		System.out.println("Input file created successfully " + fileName);
	
		ArrayList<String> fileData = manageInputFile.readInputFile(fileName); //Reading the Input file.
		
		// Getting credentials to Amazon AWS server.
		
		System.out.println("Connecting to AMAZON AWS SQS server to push the messages from the input file ...................\n");
		System.out.println("Please wait .... Trying to connect to AWS SQS using the credentials provided....");
		
		try 
		{
			credentials = new ProfileCredentialsProvider("default").getCredentials();
		} catch (Exception e) 
		{
			throw new AmazonClientException(
					"Cannot load the credentials from the credential profiles file. " +
							"Please make sure that your credentials file is at the correct " +
							"location (C:\\Users\\ravi\\.aws\\credentials), and is in valid format.",
							e);
		}
		
		//Setting the regions for sqs.
		
		AmazonSQS sqs = new AmazonSQSClient(credentials);
		Region usEast1 = Region.getRegion(Regions.US_EAST_1);
		sqs.setRegion(usEast1);
		System.out.println("**********************************************************");
		System.out.println("Connected Successfully to Amazon AWS SQS Region");
		System.out.println("***********************************************************\n");
		
		//Preparing the Task Queue from the input file to be pushed to SQS.
		
		prepareTaskQueue(fileData, taskQueue); 
		
		long startTimemilli = System.currentTimeMillis();
		
		try
		{
			String RemoteTaskQueueUrl = sqs.getQueueUrl(RemoteTaskQueueName).getQueueUrl();
						
			for (String task : taskQueue){
				sqs.sendMessage(new SendMessageRequest(RemoteTaskQueueUrl, task));
			}
			
			System.out.println(" ******** Loaded all the Input messages successfully in the format <taskid> <Sleeptime (in ms)> in the SQS Queue. ********* ");
			
		}
		catch (Exception ex) 
		{
			String RemoteTaskQueueUrl = sqs.getQueueUrl(RemoteTaskQueueName).getQueueUrl();
			System.out.println("RemoteTaskQueue URL is :" + RemoteTaskQueueUrl);
			System.out.println("Exception thrown while loading the data to SQS queue.");
		}
		long stopTimemilli = System.currentTimeMillis();
		System.out.println("\n*******************************************************************************************************************************");
		System.out.println("\n     HENCE TIME TAKEN TO PUSH ALL INPUT MESSAGES TO SQS QUEUE IS (in msecs) = " + (stopTimemilli - startTimemilli)+ " msecs        ");
		System.out.println("\n********************************************************************************************************************************");
	}
	
	//TaskQueue preparation method being called.
	
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

