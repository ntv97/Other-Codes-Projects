# Program kmerfirst.py
# This program finds all the overlapping k-mers of the input string. It builds
# an associative array where each key is one distinct k-mer in the string,
# and the associated value is the starting position where that
#k-mer is FIRST found.  Compare this to kmer3.py
string = input('Input the string:')
num_k = int(input('What length k-mer?'))

kmer = {} # this initializes an empty hash called kmer.
for i in range(0,(len(string)-num_k+1)):
    print(string[i:(i+num_k)] + ',' + str(i))
    if string[i:(i+num_k)] not in kmer.keys():
        kmer[string[i:(i+num_k)]] = i # hash the key string[i:(i+num_k)] into the hash called kmer, and set the value there to i.

for i in range(len(kmer)):
    print("The first occurrence of string " + str(list(kmer.keys())[i]) + ' is in position ' + str(list(kmer.values())[i]))

print(kmer)
