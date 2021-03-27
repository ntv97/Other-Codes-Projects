# Program kmer1.py
# #Here we try to find all the k-mers of a string. It
# only finds non-overlapping ones, but later it will
# be modified to find the overlapping ones as well.
# dg
string = input('Input the string:')
num_k = int(input('What length k-mer?'))
for i in range(0,len(string),num_k):
    if (i+num_k) <= len(string):
        print(string[i:(i+num_k)])
