## Nhi Vo 92796677
## 4.3

## Part a)
def findmotif(protein):
    from re import search
    motif = "Y.{2}[YFT]{1}"
    pos = search(motif, protein)
    if (pos != None):
        return pos.span()[0]
    else:
        return -1

def motif():
    seq = input("Enter protein sequence: ")
    print(findmotif(seq))


## Part b)
def proteinlist():
    seqlist = ["ABCNHI", "YFFT", "SDFSDYYYYDG" ,"ASDJYBGY", "HELLO", "YYYY"]
    reslist = []
    for seq in range (len(seqlist)):
        temp = []
        contains = findmotif(seqlist[seq])
        if contains != -1:
            temp.append(seq)
            temp.append(contains)
            reslist.append(temp)
    tuplist = tuple(reslist)
    return tuplist

## above function returns tuple with elements in the form [x,y] where x is
## position of the sequence in tuple that contains motif and y is the position in the sequence
## where the motif occurs.
