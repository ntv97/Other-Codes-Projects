## Nhi Vo 912796677
## Lab 2 Exercise 2. Needleman Algorithm

f = open("exer2.txt", "w")
f.write("\t \t Lab 2 exercise 2: Needleman Algorithm to find maximum alignment value\n\n\n")

string1 = "AATTAGGTTGA"
string2 = "ATAATCGTTAA"

line1 = "string1 = "+string1+"\nstring2 = "+string2+ "\n"
f.write(line1)


charlist_string1 = list(string1)
charlist_string2 = list(string2)
print("The lengths of the two strings are " + str(len(string1)) + ", " + str(len(string2)) + "\n")

match = int(input("Enter the Match Value (include sign in front of integer):  "))
mismatch = int(input("Enter the Mismatch Cost (include sign in front of integer):  "))
indel = int(input("Enter the Indel Cost (include sign in front of integer):  "))

line2 = "Match = 1, mismatch = -1, indel = -2\n\n"
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
		
print("The similarity value of the two strings is " + str(V[nrow-1][ncol-1]) + "\n")
f.write("The similarity value of the two strings is " + str(V[nrow-1][ncol-1]) + "\n")
f.close()
