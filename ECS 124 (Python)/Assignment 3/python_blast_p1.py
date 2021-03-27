## Nhi Vo 912796677
## Python-BLAST

## PRINT MESSAGE WHEN L>=7

query = open('queryQ.txt', 'r')
sfile = open('pythonblastdata.txt', 'r')
Q = query.readline()

k = 4
Qkmer = {}
for i in range(0,(len(Q)-k+1)):
    if Q[i:i+k] not in Qkmer.keys():
        Qkmer[Q[i:(i+k)]] = i
S = ''
for line in sfile:
    S = S + line.rstrip('\n')
Skmer = {}
for i in range(0, (len(S)-k+1)):
    if S[i:i+k] not in  Skmer.keys():
        Skmer[S[i:i+k]] = i
for kmer in Skmer:
    L = 0
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
                if L==7:
                    print("A good HSP has been found between Q and S: \n", kmer)
                elif L>7:
                    print("Notice: This HSP appears multiple times!")                   
            else:
                break

