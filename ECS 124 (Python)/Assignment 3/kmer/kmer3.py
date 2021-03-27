# Program kmer3.py
# Extension of kmer2.py
# This finds all the overlapping k-mers of the input string. It builds
# an associative array (a hash) where each key is one distinct k-mer in the string,
# and the associated value is the last starting position where that
# k-mer is found. For example, if the input is ACACTCA and k is 2, then
# one key is AC with  value 2; another key is CA with value 5;
# another key is CT with value 3; and one key is TC with value 4.
string = input('Input the string:')
num_k = int(input('What length k-mer?'))

kmer = {} # this initializes an empty hash called kmer.
for i in range(0,(len(string)-num_k+1)):
    print(string[i:(i+num_k)] + ',' + str(i))
    kmer[string[i:(i+num_k)]] = i # hash the key string[i:(i+num_k)] into the hash called kmer, and set the value there to i.

for i in range(len(kmer)):
    print("The last occurrence of string " + str(list(kmer.keys())[i]) + ' is in position ' + str(list(kmer.values())[i]))