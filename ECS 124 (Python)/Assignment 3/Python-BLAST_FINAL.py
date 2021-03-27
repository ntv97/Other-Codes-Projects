## Nhi Vo 912796677
## Python-BLAST

## database string is also in the query string in multiple locations,
## then a search should be made from each occurrence of the k-mer in the
## query string


## For each Kmer, we match all the characters to the left with position A and
## all the characters to the right with position C and we store all the
## matching characters as keys and beginning and end positions as values

##query = open('queryQ.txt', 'r')
sfile = open('pythonblastdata.txt', 'r')
Q = input("Input Q: ")
k = int(input("Enter k: "))
Qkmer = {}
for i in range(0,(len(Q)-k+1)):
    if Q[i:i+k] not in Qkmer.keys():
        Qkmer[Q[i:(i+k)]] = [i]
    else:
        Qkmer[Q[i:(i+k)]].append(i)
S = ''
while True:
    inp = input("Input S (enter 'q' to terminate): ")
    if inp == 'q':
        break
    else:
        S = S+inp
L = int(input("Enter threshold: "))
Skmer = {}
pos = []
for i in range(0, (len(S)-k+1)):
    if S[i:i+k] not in  Skmer.keys():
        Skmer[S[i:(i+k)]] = [i]
    else:
        Skmer[S[i:i+k]].append(i)
HSPpos = {}  ## mutual kmer in S and Q
HSP = {} ## HSP with beginning pos of first matching chat in Q and S and ending pos of last matching char in Q, S
mutual = {}
HSPlen = {}

longest_l = 0
for kmer in Skmer:
    length = 0
    pos = []
    if kmer in Qkmer:
        q_idx = Qkmer[kmer]
        s_idx = Skmer[kmer]
        #print(q_idx, s_idx)
        for i in q_idx:
            for j in s_idx:
                beg_q = i
                beg_s = j
                while beg_q>0 and beg_s>0 and Q[beg_q-1] == S[beg_s-1]:
                        beg_q = beg_q - 1
                        beg_s = beg_s - 1
                        length = length + 1
                q = "Q: "     ## the beginning of the matching characters to 
                q = q + str(beg_q)  ## the left of S and Q
                s = "S: "           ## and I stores these values and 
                s = s + str(beg_s)   ## its ending postions in a dictionary
                beg_q = i
                beg_s = j
                while beg_q<len(Q) and beg_s<len(S):
                    if Q[beg_q] == S[beg_s]:
                        beg_q = beg_q + 1
                        beg_s = beg_s + 1
                        length = length + 1
                    else:
                        q = q + "," + str(beg_q)   ## ending matching char position
                        s = s + "," + str(beg_s)
                        pos.append([q,s])
                        if kmer not in HSP:
                            mutual[kmer] = pos
                        else:
                            mutual[kmer].append(pos)
                        break
        if L > longest_l:
            longest_l = L
        if length >= L:
            if kmer not in HSP:
                HSP[kmer] = tuple(pos)
                print("A good HSP has been found between Q and S: ", kmer, '\n')
                print(HSP[kmer])
                HSPlen[kmer] = L
            else:
                if HSPlen[kmer] < length:
                    HSPlen[kmer] = length
                HSP[kmer].append(pos)
                print("Notice: This HSP appears multiple times!\n\n")
            
#print(HSP)
print("\nThe matching strings with length at least L are: ")
for elem in HSPlen:
    print(elem, ": ", HSPlen[elem])
print("\nLongest length with k =",k," and L =", L, "is: \n", longest_l)
