## prog4.py
## Nhi Vo
## November 12, 2017


#1:

def sumOfOdds(number):
    """ Takes one argument, an integer greater than or equal to 1 and return the result
of adding the odd integers between 1 and the input value. """
    if number%2 == 0:
        number = number - 1
    value = 0
    for i in range(1,number+1, 2):
        value += i 
    return value


#2:

def countChar(single,string):
    """ Takes two arguments, a single character and a string of arbitary length,
and returs the number of times the character appears in the string. """
    count = 0
    for i in string:
       if i == single:
                count = count +1
    return count

#3:

def countDiffs(string1,string2):
    """ Takes in two strings of the same length and count the number of times the
strings have different characters in the same location. """
    count = 0
    for i in range(len(string1)):
        if (string1[i] != string2[i]):
            count = count + 1
    return count

#4:

def avgSumOfSquares(listofnum):
    """ Compute the average of the sum of squares of all the values and return that value """
    if listofnum == []:
        pass
    else:
        total = 0
        for i in listofnum:
            square = i**2
            total += square
        total = total/len(listofnum)
        return total

#5:

key = [["a",".-"],["b","-..."],["c","-.-."],["d","-.."], ["e","."],["f","..-."],["g","--."],["h","...."], ["i",".."],["j",".---"],["k","-.-"],["l",".-.."], ["m","--"],["n","-."],["o","---"],["p",".--."], ["q","--.-"],["r",".-."],["s","..."],["t","-"], ["u","..-"],["v","...-"],["w",".--"],["x","-..-"], ["y","-.--"],["z","--.."]]
test1 = "the quick brown fox jumped over the lazy dog"
test2 = "i do not like green eggs and ham"
test3 = "help! i've fallen and I can't get up"
test4 = ""
    
def translate(msg, key):
    """ Expects two argument, the first is a message to be translated into a coded
message. The second is a list of lists serving as the key to be used to conver the
original string to its Morse Code equivalent. The function returns a new string
created by replacing every character in the message with its counterpart. """
    message = ''
    space = ' '
    notchar= "***"
    for char in msg:
        status = False
        for letter in key:
            if char == letter[0]:
                message = message + letter[1] + space
                status = True
        if status == False:
                if char == ' ':
                    message = message + '  '
                else:
                    message = message + notchar + space
    return message
        
        
        
