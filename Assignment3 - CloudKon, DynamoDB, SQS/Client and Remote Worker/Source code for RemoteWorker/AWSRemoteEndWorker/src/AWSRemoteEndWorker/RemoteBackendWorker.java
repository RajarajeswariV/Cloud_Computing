package AWSRemoteEndWorker;

import java.util.ArrayList;
import java.util.List;

import com.amazonaws.auth.AWSCredentials;
import com.amazonaws.auth.profile.ProfileCredentialsProvider;
import com.amazonaws.regions.Region;
import com.amazonaws.regions.Regions;
import com.amazonaws.services.dynamodbv2.AmazonDynamoDB;
import com.amazonaws.services.dynamodbv2.AmazonDynamoDBClient;
import com.amazonaws.services.dynamodbv2.util.Tables;
import com.amazonaws.services.sqs.AmazonSQS;
import com.amazonaws.services.sqs.AmazonSQSClient;
import com.amazonaws.services.sqs.model.Message;
import com.amazonaws.services.sqs.model.ReceiveMessageRequest;
import com.amazonaws.services.sqs.model.SendMessageRequest;
import com.amazonaws.services.sqs.model.SendMessageResult;

public class RemoteBackendWorker {

	@SuppressWarnings("deprecation")
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		if(args.length != 4) 
		{
			System.out.println("USAGE: Client <number of threads> < Remote task Queue Name> <Remote Response Queue name> <Remote Dynamo DB table>");
			System.exit(1);
		}

		//Getting command line arguments from the user programmatically.

		Integer numOfThreads = Integer.parseInt(args[0]);
		String RemoteTaskQueueName = args[1];
		String RemoteResponseQueueName = args[2];
		String DynamoDBtableName = args[3];
		
		//Integer numOfThreads = 1;
		//String RemoteTaskQueueName = "RemoteTasksQueue";
		//String DynamoDBtableName = "RemoteDynamoDB";
		//String RemoteResponseQueueName = "RemoteResponseQueue";
		
		AWSCredentials credentials = null;
		
		try
		{
			//Process SQS queue to check if the queue exits.
			
			credentials = new ProfileCredentialsProvider("default").getCredentials();
			AmazonSQS sqs = new AmazonSQSClient(credentials);
			
			String remoteQueueName = sqs.getQueueUrl(RemoteTaskQueueName).getQueueUrl();
			String responseQueueName = sqs.getQueueUrl(RemoteResponseQueueName).getQueueUrl();
			
			if ((remoteQueueName != null) || (responseQueueName != null))
			{
				System.out.println("The queue " + RemoteTaskQueueName + " or " + RemoteResponseQueueName + " is exisiting"); 
			}
			
			else
			{
				System.out.println("Task Queue " + RemoteTaskQueueName + "does not exists");
				System.exit(2);
			}
			
		}catch (Exception e)
		{
			System.out.println("Task Queue " + RemoteTaskQueueName + "does not exists");
			System.exit(2);
		}
		
		// Process Dynamo DB and setting the region.
		
		try 
		{
			AmazonDynamoDB dynamoDB = new AmazonDynamoDBClient(credentials);
			Region usEast1 = Region.getRegion(Regions.US_EAST_1);
			dynamoDB.setRegion(usEast1);
						
			if (Tables.doesTableExist(dynamoDB, DynamoDBtableName))
			{
				System.out.println("DynamoDB table : " + DynamoDBtableName + " is exisiting");
			}
			
			else
			{
				System.out.println("DynamoDB table : " + DynamoDBtableName + " does not exists");
				System.exit(3);
			}
			
		} catch (Exception e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
			System.out.println("DynamoDB table : " + DynamoDBtableName + " does not exists" );
			System.exit(3);
		}
		
		ArrayList<RemoteThread> threads = new ArrayList<RemoteThread>();
		
		long startTimemilli = System.currentTimeMillis();
		
		for (int count = 0; count < numOfThreads; count++)
		{
			RemoteThread t = new RemoteThread();
			t.setQueues(RemoteTaskQueueName, RemoteResponseQueueName);
			t.setDynamoDBTableName(DynamoDBtableName);
			t.start();
			threads.add(t);
		}
		
		for(int count = 0; count < numOfThreads; count++)
		{
			RemoteThread t = threads.get(count);
			try {
				t.join();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		System.out.println("\n**********************************************************************************************************************************************");
		System.out.println("\nAll the Successfully completed tasks have being updated to DynamoDB");
		System.out.println("\nAll the Finished tasks have been removed from the TasksQueue");
		System.out.println("\nAll the Finished tasks have been updated to the Response Queue.");
		System.out.println("\n**********************************************************************************************************************************************");
		
		long stopTimemilli = System.currentTimeMillis();
		System.out.println("\n**********************************************************************************************************************************************");
		System.out.println("\n     HENCE TIME TAKEN TO PROCESS ALL THE TASKS FROM SQS QUEUE, DELETE THEM, AND UPDATE THE DYNAMO DB IS (in msecs) = " + (stopTimemilli - startTimemilli)+ " msecs        ");
		System.out.println("\n***********************************************************************************************************************************************");
	}
	
	public static SendMessageResult sendMessage(AmazonSQS sqs, String sendQueueUrl, String message) {
		return sqs.sendMessage(new SendMessageRequest(sendQueueUrl, message));
		}
	
	public static Message receiveMessage(AmazonSQS sqs, String receiveQueueUrl) 
	{	
		ReceiveMessageRequest receiveMessageRequest = new ReceiveMessageRequest(receiveQueueUrl);
		List<Message> messages = new ArrayList<Message>();
		
		int retrieveCount = 0;
		int maxPoolingCount = 100;

		while (messages.isEmpty() && retrieveCount < maxPoolingCount) 
		{
		retrieveCount++;
		messages = sqs.receiveMessage(receiveMessageRequest).getMessages();
		
			try 
			{
				if (messages.isEmpty()) 
				{
					// Then we will retry the check every 1 second.
					Thread.sleep(1000);
				} else {
					return messages.get(0);
				}
				
			} catch (InterruptedException e) 
			{
			// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		return null;
	}	
	
}
