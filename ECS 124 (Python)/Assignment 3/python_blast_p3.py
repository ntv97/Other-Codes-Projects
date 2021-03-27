## Nhi Vo 912796677
## Python-BLAST

## READ MULTIPLE LINES


query = open('queryQ.txt', 'r')
sfile = open('pythonblastdata.txt', 'r')
Q = input("Input Q: ")   ## CHANGES: getting input

k = 4
Qkmer = {}
for i in range(0,(len(Q)-k+1)):
    if Q[i:i+k] not in Qkmer.keys():
        Qkmer[Q[i:(i+k)]] = i
S = ''
while True:  ## CHANGES: getting input
    inp = input("Input S (enter 'q' to terminate): ")
    if inp == 'q':
        break
    else:
        S = S+inp
        
Skmer = {}
pos = []
for i in range(0, (len(S)-k+1)):
    if S[i:i+k] not in  Skmer.keys():
        Skmer[S[i:i+k]] = i
##mutualpos = {}  ## CHANGES: mutual kmer in S and Q
HSP = {} ## CHANGES: HSP lengths
mutual = {} ## CHANGES all mutual kmer lengths regardless of HSP or not
for kmer in Skmer:
    L = 0
    pos = []
    if kmer in Qkmer:
        s_idx = Skmer[kmer]
        q_idx = Qkmer[kmer]
        while Q[q_idx-1] == S[s_idx-1] and q_idx<len(Q) and s_idx<len(S):
            L = L + 1
            q_idx = q_idx - 1
            s_idx = s_idx - 1
        s_idx = Skmer[kmer]
        q_idx = Qkmer[kmer]
        while q_idx<len(Q) and s_idx<len(S):
            if Q[q_idx] == S[s_idx]:
                q_idx = q_idx + 1
                s_idx = s_idx + 1
                L = L + 1
                if kmer not in mutual:  ### CHANGES: No repeats
                    print("A good HSP has been found between Q and S")
                else:
                    print("Notice: This HSP appears multiple times!")                   
                mutual[kmer] = L
            else:
                break

    if L>=7:  ## HSP dictionary contains HSP proteins w/ their lengths
        pos.append(Qkmer[kmer])  
        pos.append(q_idx)      
        pos.append(Skmer[kmer])
        pos.append(s_idx)
##        mutualpos[kmer] = tuple(pos)
        print(kmer, ":", tuple(pos))
        HSP[kmer] = L ## CHANGES: Store HSP in dictionary
print("\nHSP lengths: ") ## along with their lengths of neighboring matching characters
for elem in HSP:
    print(elem, ": ", HSP[elem])

##print("\nHSP positions of matching substrings starting at Q, ending at Q, starting at S, and ending at S: ")
##for  pos in mutualpos:
##    print(pos, ": ", mutualpos[pos])

