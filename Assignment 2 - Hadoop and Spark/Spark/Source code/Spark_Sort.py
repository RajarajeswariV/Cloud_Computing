#!/usr/bin/python

#import all the necessary libraries for file handling, System time, OS for path, Queue handling.

import sys
import string
import pyspark
from pyspark import SparkContext

def sortfunc(file_name):
    
    sc = SparkContext(appName="PythonSort")
    
    lines = sc.textFile("hdfs:////root/sys.argv") # Get the input file from the user

    sortedCount = lines.filter(lambda line: line.split(" ")) \
                  .setmap(lambda line: (int(x), 1)) \
                  .rows.sortBy(r => (lambda line: x))

if __name__ == "__main__":

    try:
        input_file = "./" + str(sys.argv[2])
        print ("The input file that you have entered for which the program has to run is %s" % input_file)
	print("\n")
        print("Program execution begins ------ Please wait for the output result to be shown")
    except IndexError:
        print ("\n \n Please enter the file name also along with execting the python code \n \n")
        exit()
        
    if len(sys.argv) != 2:
        print (sys.stderr, "Usage: sort<file>")
        exit(-1)
        
    logData = sc.textFile(logFile).cache()
    errors = logData.filter(lambda line: "ERROR" in line)
    
    sortfunc(input_file) # Calling the sort function to sort the input file

# Outputs the sorted lines

    result=sorted(SortedCount, key=debugFunction)

    sc.stop()

# End of the program
