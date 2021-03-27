# Program kmer2.py
# Extension of kmer2.py
# This finds and prints all the overlapping k-mers of the input string.
# dg
string = input('Input the string:')
num_k = int(input('What length k-mer?'))
for i in range(0,(len(string)-num_k+1)):
    print(string[i:(i+num_k)])