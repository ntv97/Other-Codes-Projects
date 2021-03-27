#this reads in the first line from testfile and tests to see if
#the line contains what looks like a dna sequence of length at least three,
#either at the start of the line, or prepended by a space or an
# = or a >.
#If it does, then it prints the sequence
#else it prints a message that the line contains no sequence.
#At the end it prints the original sequence to show that is has
#not been modified. Make a file called testfile and try the
#program out. Change the contents of testfile to try different
#conditions. The straight line | in a regular expression is
# an OR. 
import re #package for regular expression

file = 'testfile';
fp = open(file,'r')
of = open("ex5_prog2.txt", 'w')
line = fp.readline() #read the first line

pattern = re.compile('(^| |=|>)([ATCGatcg]{3,})')
match_result = pattern.match(line)
if match_result:
        print("The input line does contain what looks like a dna sequence of length at least three, and it is " + match_result.group(2) + " \n")
        of.write("The input line does contain what looks like a dna sequence of length at least three, and it is " + match_result.group(2) + " \n")
else:
        print("The input line does not contain a dna sequence\n")
        of.write("The input line does not contain a dna sequence\n")
	
print ("The input line is \n" + str(line) + "\n")
of.write("The input line is \n" + str(line) + "\n")

fp.close()
of.close()
