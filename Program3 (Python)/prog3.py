## prog3.py
## Nhi Vo
## October 29, 2017


# Problem 1

def sumOfEvens(int):
    """ Takes an integer greater or equal to 1 and returns the result of adding
even integers between 1 and the value of the given argument. """
    if int%2 == 0:
        counter = 0
        while int >= 1:
            counter = counter + int
            int = int - 2
        return counter
    else:
        counter = 0
        int = int - 1
        while int >= 1:
            counter = counter + int
            int = int - 2
        return counter

# Problem 2

def productOfPowersOf10(exp1,exp2):
    """ Compute and return the product of all powers of 10 from 10**exp1 to 10**exp2 """
    counter = 1
    while exp1<=exp2:
        counter = counter*10**exp1 
        exp1 = exp1 + 1
    return counter

# Problem 3

def printHashtags(nonneg):
    """ Expects a nonnegative integer and prints a row of hashtags. """
    if nonneg == 0:  ## If 0 is entered print blank
        print(" ")
    else:
        hashtag = '#'  ## If a number is entered, return the number of hashtags in accordance
        number = nonneg -1
        while number>0:
            number = number - 1
            hashtag = hashtag + '#'
        print(hashtag)

# Problem 4

def printTriangle(nonneg):
    """ Expects a nonnegative integer and prints a right triangle. """
    if nonneg == 0:
        pass
    else:
        while nonneg>0:
            str(printHashtags(nonneg)) ## Call on the function in problem 3
            nonneg = nonneg - 1

# Problem 5:
def allButMax():
    """ Ask user to enter a series of numbers greater than or equal to zero one at a time.
The user types end to indicate that there are no more number. The function prints the sum
and returns the sum. """
    value = 0
    max = 0
    number = 0
    while True:
        number = input("Enter the next number: ")
        if number != 'end':  ## If user types in a number as a string,
            if max<=float(number):  ## determine the max value of all the value entered
                max = float(number)
            value = value + float(number)  ## The sum of all values including the max number.
            sum = value - max  ## The sum of values excluding the max number.

        else:
            if value == 0:   ## If 'end' is entered as the first input, return and print 0
                sum = 0
                print("The sum of all values except for the maximum value is: ", sum)
                return sum
            else:  ## If numbers as strings are entered before end. print and return its sum
                print('The sum of all values except for the maximum value is: ', sum)
                return sum
                

## Problem 6:

def avgSumOfSquares():
    """ Ask user to enter a series of number one at a time. 'End' indicates that
there are no more numbers. The function computers the average of the sum of squares
of all values entered. """
    count = 1
    sum = 0
    while count != -1:
        number = input("Enter the next number: ")

        if number != 'end':
            square = (float(number))**2  ## Takes the square of the user input
            sum = sum + square  ## Takes the sum of squares
            avg = float(sum/count) ## Takes the average of squares
            count = count +1

        else:
            if count == 1:   ## If end is entered before other values print the following:
                print("No numbers were entered.")
                break
            else:
                print("The average of the sum of the squares is: ", avg)  ## If end is entered following some number(s), print and return
                return avg
            
                   


    


