package AWSRemoteEndWorker;

import java.util.HashMap;
import java.util.Map;
import com.amazonaws.services.dynamodbv2.model.PutItemRequest;
import com.amazonaws.AmazonWebServiceRequest;
import com.amazonaws.auth.AWSCredentials;
import com.amazonaws.services.dynamodbv2.model.Condition;
import com.amazonaws.auth.profile.ProfileCredentialsProvider;
import com.amazonaws.regions.Region;
import com.amazonaws.regions.Regions;
import com.amazonaws.services.dynamodbv2.model.ComparisonOperator;
import com.amazonaws.services.dynamodbv2.AmazonDynamoDB;
import com.amazonaws.services.dynamodbv2.AmazonDynamoDBClient;
import com.amazonaws.services.dynamodbv2.model.AttributeValue;
import com.amazonaws.services.dynamodbv2.model.PutItemResult;
import com.amazonaws.services.dynamodbv2.model.ScanRequest;
import com.amazonaws.services.dynamodbv2.model.ScanResult;
import com.amazonaws.services.sqs.model.Message;
import com.amazonaws.services.sqs.AmazonSQS;
import com.amazonaws.services.sqs.AmazonSQSClient;
import com.amazonaws.services.sqs.model.DeleteMessageRequest;

public class RemoteThread extends Thread {
	
	AWSCredentials credentials = getcredentials();
	
	@Override
	public String toString() {
		// TODO Auto-generated method stub
		return super.toString();
	}
	
	String RemoteTaskQueueUrl;
	String RemoteResponseQueueUrl;
	String dynamoDBTableName = "RemoteDynamoDB";
	private AmazonDynamoDB dynamoDB;

	AmazonSQS sqs = new AmazonSQSClient(credentials);	
	
	public void setQueues(String RemoteTaskQueueName, String RemoteResponseQueueName)
	{
		this.RemoteTaskQueueUrl = sqs.getQueueUrl(RemoteTaskQueueName).getQueueUrl();
		this.RemoteResponseQueueUrl = sqs.getQueueUrl(RemoteResponseQueueName).getQueueUrl();
		
	}
	
	public void run() 
	{
		Message m = null;
		int id = -1;
		
		while ((m = getNextTask(sqs, RemoteTaskQueueUrl)) != null) {
		try 
		{
			String body = m.getBody();
			String[] parsed = body.split(" ");
			String jobidPart = parsed[0];
			id = Integer.parseInt(jobidPart);
			
			System.out.println("Task id read from the SQS Queue : "  + id);
			if (checkIfDuplicate(id))
			{
				continue;
			}

			int sleepTime = Integer.parseInt(parsed[1]);
			Thread.sleep(sleepTime);


			deleteAndSendTaskResponse(sqs, m, id, "SUCCESSFULLY PROCESSED");
			}catch (Exception e) {
				deleteAndSendTaskResponse(sqs, m, id, "TASK FAILED~" + e.getMessage());
			
			}
		 
		}
	}

		private void deleteAndSendTaskResponse(AmazonSQS sqs, Message m, int taskId, String responseMessage) 
		{
			updateDB(taskId, responseMessage);
			
			System.out.println("The corresponding task executed for the sleep time in the SQS Queue :  " + responseMessage);
			
			deleteMessage(sqs, RemoteTaskQueueUrl, m);
			
			RemoteBackendWorker.sendMessage(sqs, RemoteResponseQueueUrl, "taskId:" + taskId + "-Response:" + responseMessage);
			
		}
		
		//To delete the message from the SQS queue once completed processing.
		
		private void deleteMessage(AmazonSQS sqs, String RemoteResponseQueueUrl, Message message) 
		{
			String messageReceiptHandle = message.getReceiptHandle();
			sqs.deleteMessage(new DeleteMessageRequest(RemoteResponseQueueUrl, messageReceiptHandle));
			return;
		}

		//Update the DynamoDB once the process is fetched from SQS and completed successfully.
		
		private void updateDB(int taskId, String status) 
		{
			Map<String,AttributeValue> item = newItem(taskId, status);
			PutItemRequest putItemRequest = new PutItemRequest(dynamoDBTableName, item);
			PutItemResult putItemResult = dynamoDB.putItem(putItemRequest);

		}

		private static Map<String, AttributeValue> newItem(int taskId, String status) {
			// TODO Auto-generated method stub
			Map<String, AttributeValue> columnName = new HashMap<String, AttributeValue>();
			columnName.put("taskId", new AttributeValue().withN(new Integer(taskId).toString()));
			columnName.put("Status", new AttributeValue(status));
			
			return columnName;
		}
		
		//Check if there are any duplicates processed.
		
		private boolean checkIfDuplicate(int id) 
		{
			HashMap<String, Condition> scanFilter = new HashMap<String, Condition>();
			Condition condition = new Condition().withComparisonOperator(ComparisonOperator.EQ.toString())
			.withAttributeValueList(new AttributeValue().withN(new Integer(id).toString()));
			scanFilter.put("jobId", condition);
			ScanRequest scanRequest = new ScanRequest(dynamoDBTableName).withScanFilter(scanFilter);
			ScanResult scanResult = dynamoDB.scan(scanRequest);
			
			if (scanResult.getCount() > 0)
			{
				return true;
			}
			//return false;
			
		updateDB(id, "RUNNING");
		return false;
		}
		
		//Worker get the next tasks once the running task is completed.
		private Message getNextTask(AmazonSQS sqs, String RemoteTaskQueueUrl) {
		Message message = RemoteBackendWorker.receiveMessage(sqs, RemoteTaskQueueUrl);
		return message;
		}
	
	
	private AWSCredentials getcredentials() 
	{
		// TODO Auto-generated method stub
		credentials = new ProfileCredentialsProvider("default").getCredentials();
		return credentials;
	
	}

	public void setDynamoDBTableName(String dynamoDBtableName) 
	{
		// TODO Auto-generated method stub
		this.dynamoDBTableName = dynamoDBTableName;
		dynamoDB = newDynamoDBClient(credentials);
		
	}
	
	public static AmazonDynamoDB newDynamoDBClient(AWSCredentials credentials){
		AmazonDynamoDB dynamoDB = new AmazonDynamoDBClient(credentials);
		Region usEast1 = Region.getRegion(Regions.US_EAST_1);
		dynamoDB.setRegion(usEast1);
		return dynamoDB;
	}
}