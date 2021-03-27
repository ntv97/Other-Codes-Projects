# Program kmer4.py
# Extension of kmer3.py
# This finds all the overlapping k-mers of the input string. It builds
# an associative array (a hash) where each key is one distinct k-mer in the string,
# and the associated value is the list of the all starting positions where that
# k-mer is found. For example, if the input is ACACTCA and k is 2, then
# one key is AC with value [0,2]; another key is CA with value [1,5];
# another key is CT with value [3]; and one key is TC with value [4].

string = input('Input the string:')
num_k = int(input('What length k-mer?'))

kmer = {} # this initializes an empty hash called kmer.
for i in range(0,(len(string)-num_k+1)):
    print(string[i:(i+num_k)] + ',' + str(i))
    if string[i:(i+num_k)] not in kmer.keys():
        kmer[string[i:(i+num_k)]] = [i] # hash the key string[i:(i+num_k)] into the hash called kmer, and set the value there to i.
    else:
        kmer[string[i:(i+num_k)]].append(i)

for i in range(len(kmer)):
    print("The occurrences of string " + str(list(kmer.keys())[i]) + ' is in position ' + str(list(kmer.values())[i]))
