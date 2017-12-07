Requirements:
•	TeraSort is an application which sorts a file-resident dataset; it should be able to sort datasets that are larger than memory. 


•	To implement the TeraSort application in any favorite language, without MapReduce/Hadoop or Spark. 


•	TeraSort should be multi-threaded (to process large files concurrently), and should only run on 1 virtual node. 

•	You can develop your code on any machine, but performance evaluation must be done on Amazon EC2 on a “c3.large” instance. Measure the time to execute the TeraSort application on two datasets (a 1GB and 1TB dataset produced with the tool XXX) on 1 node. 

•	Vary the number of threads from 1 to 8, to find the best performance. Save the first 10 lines of output from the Shared-Memory TeraSort application, as well as the last 10 lines of output, for each dataset, in “Merged_Sorted_Output for 1GB” and “Merged_Sorted_Output for 100GB” respectively.


HOW THE PROGRAM WORKS TO MEET THE ABOVE REQUIREMENTS?:
Programming Language: Python
?	The given project requires to perform operations on a huge file (1GB, 10GB and 100GB and 1TB) which will lead to some limitations one of which is allocation of resources for a huge file. 

?	For example, our machine has maximum RAM of 8 GB, the read, write, sort operations can be well performed on a Dataset which is less than the memory. In our case, 1GB dataset can be sorted with the help of 8GB RAM available.  


?	But the problem comes when we try to handle a 100 GB file where the input file is larger in size than the memory and so the operations like read/write/sort cannot be performed unless the huge input file is split into smaller files.

?	Hence, we first split the input file into smaller chunks of files and then try sorting the smaller files on a 8 GB RAM. Once the smaller files are sorted, we then try to merge all the smaller sorted files. To avoid sorting on the merged file, I have used the below sort function to sort the files based on the ASCII characters.

Python installer v2.7 and above
==============================

Executing python code on the terminal ------> python <programname.py> <numberofthreads> <inputdataset>

HADOOP:
========
Installation and the version details are clearly specified in the prog2_report document of hadoop along with screenshots of installing the cluster. 

Spark:
=======
Installation and the version details are clearly specified in the prog2_report document of Spark along with screenshots of installing the cluster. 

