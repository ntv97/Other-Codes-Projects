## prog5.py
## Nhi Vo
## November 26, 2017

# Problem 1:

def printAverages(table):
    """ Takes a 2-D table and computes and print the averages of all but
the lowest score in the row """
    for nums in range(len(table)):  
        total = 0
        count = 0
        for num in table[nums]:  ## For the elements in table of row nums
            count+=1
            minval= minival(table[nums])  ## Calls on another function to calculate minimum val
            total=num+total
        avg=float((total-minval)/(count-1))  ## Calculate average of numbers excluding the lowest
        print("Average for row", nums, "is", avg)


def minival(numbers):  ## Calculate the minimum value in each row
    """ Calculate the minimum value in a list  needed for problem #1 """
    minval=numbers[0]
    for num in range(len(numbers)):
        if minval>=numbers[num]:
            minval=numbers[num]
    return minval

## Problem 2:

def addTables(table1,table2):
    """ Takes table 1(the first index) and table 2(the second index) and add the value
of each element into table3. The new table has the same dimensions as the
two tables passed as parameter. """
    table3 = []   
    for nums in range(len(table1)):    # Counts in the number of rows
        total = []
        for num in range(len(table1[0])):   # Counts in the number of columns
            result = table1[nums][num]+table2[nums][num]
            total.append(result)  # Add the result to total
        table3.append(total) # At the end of each num loop append total to table3
    return(table3)
##    import copy
##    newt1= copy.deepcopy(table1)
##    newt2 = copy.deepcopy(table2)
##    for nums in range(len(newt1)):
##        total = []
##        for num in range(len(newt1[0])):
##            result = newt1[nums][num]+newt2[nums][num]
##            #total.append(result)
##        table3.append(result)
##    return(table3)
    
    

                      
        
