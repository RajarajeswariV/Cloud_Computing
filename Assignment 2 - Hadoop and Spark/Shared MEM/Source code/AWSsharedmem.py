#!/usr/bin/python

#import all the necessary libraries for file handling, System time, Threads handling, String handling, OS for path, Queue handling.

import os,multiprocessing,sys,time,glob,string,re,json,shutil,locale,string,fileinput
from time import sleep
from multiprocessing import Queue
from collections import Counter, defaultdict
from itertools import islice
from operator import itemgetter
import operator
from glob import iglob

#Break the large file into many smaller files for sorting using the below function fsize_split.

def fsize_split(num_threads):

    fsize_array = []
    fsize_array.append(0)

    files = []
    
    file_size = os.path.getsize(input_file)  # Get the size of the input file from the OS directory with the help of "path"

    print ("File size is %d" % file_size)
    
    n = 1
    start_line = 0

    if file_size < 2000000:
        lines_split = 100 / num_threads
    elif file_size < 2000000000:
        lines_split = 10000000 / num_threads # Handles 1GB file
    elif file_size < 20000000000:
        lines_split = 100000000 / num_threads # Handles 10 GB file
    elif file_size < 200000000000:
        lines_split = 1000000000 / num_threads # Handles 100 GB file
    elif file_size < 2000000000000:
        lines_split = 10000000000 / num_threads # Handles 1000GB (1TB) file
    else:
        lines_split = 100000000000 / num_threads # Handles more than 1TB file

    print ("Lines split is : %d " % lines_split)
    
    end_line = lines_split
    
# Split the huge sized input file and create multiple file names with the splitted records.

    with open (input_file) as robj:
        while (n <= num_threads):
           
            data = [next(robj) for x in range(start_line, end_line)]
             
            with open ("./splitoutput/splitat%s_record.txt" % end_line, "a") as wobj:        
                wobj.writelines(data)
                files.append(wobj.name)

            start_line = end_line
            end_line = end_line + lines_split
            n = n + 1

# Allocate files with respect to each files that was broken down into chunks from above step.

    length = len(files)
    print ("Length of the files is %d " % length)
    splitat_record = num_threads * (length // num_threads)

    file_list1 = files[:splitat_record]
    file_list2 = files[splitat_record:]

    max_length = len(file_list1) // num_threads

    print ("Maximum length of the file is : % d" % max_length)

    file_split = [file_list1[i:i+max_length] for i in range(0, len(file_list1),max_length)]

    divider = max_length

    for i in range(len(file_list2)):
        insertat_rec = i % divider
        file_split[insertat_rec].append(file_list2[i])

    return file_split

# The below function name_file will help in creating the file name according to the ascii table which will in turn be helpful in sorting them as individual files.

def name_file(files, X):
    
    for i in files:
        
        read = open(i, "r")

        dictionary = defaultdict(list)

        list_ascii = []

        s = string.printable

        list_ascii.append(s)

        for i in read:
            dictionary[i[0]].append(i)

        for i in dictionary.values():
            a = []
            a.extend(i)
           
            strings = "".join([i for i in a])
            
            try:
                for j in range(100):

                    if (i[0][:1].islower() == True):
                        if (i[0][:1] == list_ascii[0][j]):
                            with open ("./output/%s_Small_words" % (list_ascii[0][j]), "a") as wipfile:
                                wipfile.writelines(strings)
                                
                    elif (i[0][:1].isupper() == True):
                        if (i[0][:1] == list_ascii[0][j]):
                            with open ("./output/%s_Caps_words" % (list_ascii[0][j]), "a") as wipfile:
                                wipfile.write(strings)
                                           
                    elif (i[0][:1] == list_ascii[0][j]):
                        if (i[0][:1] == '/'):
                            with open ("./output/fwdslash_words", "a") as wipfile:
                                wipfile.write(strings)
                                
                        elif (i[0][:1] == '\\'):
                            with open ("./output/bkwdslash_words", "a") as wipfile:
                                wipfile.write(strings)
                                
                        else:
                            with open ("./output/%s_words" % (list_ascii[0][j]), "a") as wipfile:
                                wipfile.write(strings)
            except OSError:

                print ("An exception has occured which implies that the program is unable to create a file name with respect to the special ascii character")

#Function sort_file is called from __main__ to sort the files that are split into various files according to the ascii characters.

def sort_merge_file(sort_list):

    quick_sort2(sort_list,0,len(sort_list)-1) # Sorting each files 

    with open('./output/Merged_Sorted_Output', 'a') as wobj:
        wobj.writelines(sort_list)

def quick_sort2(sort_list,low,high):
   if low < high:

       splitpoint = data_partition(sort_list,low,high) # Calling data_partition function to partition the data for an easy sort

       quick_sort2(sort_list,low,splitpoint-1)
       quick_sort2(sort_list,splitpoint+1,high)

# Function to get the pivot point from which the records are to be sorted on the left and right portions.

def get_pivot(sort_list,low,high):
   mid = (high + low) // 2

   pivot = high

   if sort_list[low] < sort_list[mid]:
       if sort_list[mid] < sort_list[high]:
           pivot = mid
       
   elif sort_list[low] < sort_list[high]:
       pivot = low
       
   return pivot

def data_partition(sort_list, low, high):
    
    pivotIndex = get_pivot(sort_list, low, high) # Calling get_pivot function to set the pivot point from which the records are split into halves at left and right and sorted accordingly by accessing the border point as well.

    pivotValue = sort_list[pivotIndex]

    sort_list[pivotIndex], sort_list[low] = sort_list[low], sort_list[pivotIndex]

    border = low

    for i in range(low, high+1):
        if(sort_list[i] < pivotValue):
            border += 1
            sort_list[i], sort_list[border] = sort_list[border], sort_list[i]

    sort_list[low], sort_list[border] = sort_list[border], sort_list[low]

    return border

#=========================================
#Main function of the program starts here.

if __name__ == "__main__":

# Number of threads and File name is passed as an argument along with program execution.

# All the output files are stored in a folder named "Output" in the path specified.

    try:
        num_threads = int(sys.argv[1])
        print ("The number of threads that you have entered is %d" % num_threads)
    except IndexError:
        print ("\n \n Please pass an argument along with executing the python code. Argument is taken as number of threads \n \n")
        exit()

    try:
        input_file = "./" + str(sys.argv[2])
        print ("The input file that you have entered for which the program has to run is %s" % input_file)
	print("\n")
        print("Program execution begins ------ Please wait for the output result to be shown")
    except IndexError:
        print ("\n \n Please enter the file name also along with execting the python code \n \n")
        exit()

    try:
        remove_allfiles = glob.glob(r"./output/*words")
        for i in remove_allfiles:
            os.remove(i)
    except OSError:
        print (" \n \n No more files to delete \n\n")

    try:
        newpath = r'./output'

        if os.path.exists(newpath):
            shutil.rmtree("./output")
            os.makedirs(newpath)
        else:
            os.makedirs(newpath)

    except OSError:
        print ("\n\n Program is unable to create the folder in the path specified \n\n")

    try:
        newpath = r'./splitoutput'

        if os.path.exists(newpath):
            shutil.rmtree("./splitoutput")
            os.makedirs(newpath)
        else:
            os.makedirs(newpath)

    except OSError:
        print ("\n\n Program is unable to create the folder in the path specified \n\n")
        
    threads_array = []

#Calling Fsize_split function to break the input file into chunks depending on the sizes and seek pointer.

    file_split = fsize_split(num_threads)

    for i in range(num_threads):
        name_file(file_split[i], i)

# Creating a list - sort_ascii and appending the ASCII table in ascending order.

    sort_ascii = [' ', '!', '"', '#', '$', '%', '&', "'", '(', ')', '*', '+', ',', '-', '.', 'fwdslash', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 'A_Caps', 'B_Caps', 'C_Caps', 'D_Caps', 'E_Caps', 'F_Caps', 'G_Caps', 'H_Caps', 'I_Caps', 'J_Caps', 'K_Caps', 'L_Caps', 'M_Caps', 'N_Caps', 'O_Caps', 'P_Caps', 'Q_Caps', 'R_Caps', 'S_Caps', 'T_Caps', 'U_Caps', 'V_Caps', 'W_Caps', 'X_Caps', 'Y_Caps', 'Z_Caps', '[', 'bkwdslash', ']', '^', '_', '`', 'a_Small', 'b_Small', 'c_Small', 'd_Small', 'e_Small', 'f_Small', 'g_Small', 'h_Small', 'i_Small', 'j_Small', 'k_Small', 'l_Small', 'm_Small', 'n_Small', 'o_Small', 'p_Small', 'q_Small', 'r_Small', 's_Small', 't_Small', 'u_Small', 'v_Small', 'w_Small', 'x_Small', 'y_Small', 'z_Small', '{', '|', '}', '~']

    q = multiprocessing.Queue()
    
    st = time.time() # Start time is taken before the threads could start processing.
    
    for i in sort_ascii:
        with open('./output/%s_words' % i, 'r') as robj:
            sort_list = []
    
            for line in robj:
                sort_list.append(line)
    
            t = multiprocessing.Process(target = sort_merge_file(sort_list)) #Accessing sort_merge_file function through threads which sorts the files and merges them in 1 big file.
            threads_array.append(t)

    for i in range(num_threads):
        threads_array[i].start()

    for i in range(num_threads):
        threads_array[i].join()

    et = time.time() # End time is taken after the successful completion of all the threads.

    total_time = et - st

    print ("\n The total time taken for processing the Sorting is : %f" % total_time)

# The below lines are to remove the temporary output splitted files as they are not required anymore by the program and occupies space.

    try:
        remove_allfiles = glob.glob(r"./output/*words")
        for i in remove_allfiles:
            os.remove(i)
    except OSError:
        print (" \n \n No more files to delete \n\n")

    print("The program has ended successfully")

    try:
        remove_allfiles = glob.glob(r"./splitoutput")
        for i in remove_allfiles:
            os.remove(i)
    except OSError:
        print (" \n \n No more files to delete \n\n")

    print("The program has ended successfully")

# End of the program
