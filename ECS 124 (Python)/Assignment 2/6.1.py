## Nhi Vo 912796677
## Lab 2 Exercise 6.1. Needleman Algorithm

f = open("exer6.1.txt", "w")
f.write("\t \t Lab 2 exercise 2: Needleman Algorithm to find maximum alignment value\n\n\n")

string1 = "ACTGACCCGTTAAACCGGTTAGTCAAAGAT"
string2 = "ACCCATGCAAAACCCACGTGACCCAGTACT"


line1 = "string1 = "+string1+"\nstring2 = "+string2+ "\n"
f.write(line1)


charlist_string1 = list(string1)
charlist_string2 = list(string2)
print("The lengths of the two strings are " + str(len(string1)) + ", " + str(len(string2)) + "\n")

match = 1
mismatch = 0
indel = 0

line2 = "Match = 1, mismatch = 0, indel = 0\n\n"
f.write(line2)


nrow = len(string1) + 1
ncol = len(string2) + 1

V = [[0] * ncol for i in range(nrow)]

for i in range(nrow):
        V[i][0] = i*indel
        print("V[" + str(i) + "][0] has value " + str(V[i][0]) + "\n")

for i in range(ncol):
        V[0][i] = i*indel
        print("V[0][" + str(i) + "] has value " + str(V[0][i]) + "\n")

for i in range(1,nrow):
        for j in range(1,ncol):
                current_max_value = V[i-1][j] + indel
                if current_max_value < (V[i][j-1] + indel):
                        current_max_value = V[i][j-1] + indel
                if charlist_string1[i - 1] == charlist_string2[j - 1]: 
                        if current_max_value < (V[i-1][j-1] + match):
                                current_max_value = V[i-1][j-1] + match
                else:
                        if current_max_value < (V[i-1][j-1] + mismatch):
                                current_max_value = V[i-1][j-1] + mismatch
                V[i][j] = current_max_value
                print("V[" + str(i) + "][" + str(j) + "] has value " + str(V[i][j]) + "\n")
		
print("The LCS of the two strings is " + str(V[nrow-1][ncol-1]) + "\n")
f.write("The LCS value of the two strings is " + str(V[nrow-1][ncol-1]) + "\n\n\n")

lenstr1 = len(string1)
lenstr2 = len(string2)
maxval = V[i][j]
lcsrev = []

while lenstr1>0 and lenstr2>0:
        if string1[lenstr1-1] == string2[lenstr2-1]:
                lcsrev.append(string1[lenstr1-1])
                lenstr1 = lenstr1 - 1
                lenstr2 = lenstr2 - 1
                l = "Match in "+ string1 + "[" + str(lenstr1-1) + "]\n"
                print(l)
                f.write(l)
        elif V[lenstr1-1][lenstr2] > V[lenstr1][lenstr2-1]:
                l1="No match in " + string1 +  "["+ str(lenstr1-1) + "]\n"
                print(l1)
                f.write(l1)
                lenstr1 = lenstr1 - 1
        else:
                lenstr2 = lenstr2 - 1
                l1="No match in " + string1 + "[" + str(lenstr1-1) + "]\n"
                print(l1)
                f.write(l1)
lsc = ""
length = V[i][j]
for i in lcsrev[::-1]:
        lsc = lsc + i

line = "\n\nThe LCS for two strings of length 30 is: " + lsc + "\n"
print(line)
f.write(line)

f.close()
