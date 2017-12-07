package rvaidyan.localworker;

public class TaskNode {
	
	int taskId;
	int milliseconds;
	String command = "";

	public TaskNode( int taskId, String milliseconds, String command ){
		this.taskId = taskId;
		this.milliseconds = Integer.parseInt( milliseconds );
		this.command = command;
	}

}
