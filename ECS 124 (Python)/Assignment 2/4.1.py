## Nhi Vo
## Exercise 5.1

def DNArepeats(k):
    diction = {}
    seqDNA = "ATAGAATAGATAATAGTC"

    for i in range(len(seqDNA)-k-k+3):
        tempseq = ""
        p = i
        for j in  range(k):
            tempseq += seqDNA[p]
            p = p + 1
        if tempseq not in diction:
            diction[tempseq] = 1
        else:
            diction[tempseq] = diction[tempseq]+1

    for val in diction:
        if diction[val] > 1:
            print( val, "=", diction[val])
       
