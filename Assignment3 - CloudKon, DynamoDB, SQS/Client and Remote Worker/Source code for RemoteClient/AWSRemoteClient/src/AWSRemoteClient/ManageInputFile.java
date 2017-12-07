package AWSRemoteClient;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

public class ManageInputFile 
{
	public void generateInputFile(String fileName, int noOfTasks, int sleepTime) 
	  {
	    try
	    {
	      File file = new File(fileName);
	      PrintWriter printWriter= new PrintWriter(file);
	            
	      //System.out.println("The task entered inside the input file is : " + task);
	      System.out.println("Number of Tasks entered inside the input file are :" + noOfTasks);
	      
	      while(noOfTasks >0){
	         printWriter.println("sleep " + sleepTime);
	         noOfTasks--;
	      }
	      printWriter.close();
	    }
	    catch (Exception e)	{
	      System.out.println(e.getStackTrace().toString());		
	    }
	  }

	 
	public ArrayList<String> readInputFile(String fileName)
	{
		      
		BufferedReader fileBufferedReader;
		ArrayList inputFileData = new ArrayList<String>();
		try 
		{
			fileBufferedReader = new BufferedReader(new FileReader(fileName));
	      
			String line = ""; 			
			int i=1;
		
			while((line = fileBufferedReader.readLine()) != null)
			{	    	 
				inputFileData.add(line);
				i++;
			}
		} catch (FileNotFoundException e) {
				System.out.println(e.getStackTrace().toString());
		} catch (IOException e) {
				System.out.println(e.getStackTrace().toString());
		}
				return inputFileData;
	}
}
