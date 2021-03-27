class MySeq:

    def __init__(self, seq, seq_type = "DNA"):
        self.seq = seq
        self.seq_type = seq_type

    def print_sequence(self):
        print("Sequence: " + self.seq)

    def get_seq_biotype (self):
        return self.seq_type

    def show_info_seq(self):
        print("Sequence: " + self.seq + " biotype: " + self.seq_type)

    def count_occurrences(self, seq_search):
        return self.seq.count(seq_search)

class ValidateSeq(MySeq):

    def __init__(self, seq):
        self.seq = seq.upper()

    def validate(self):
        condition = "ACTG"
        status = all(c in condition for c in self.seq)
        return status

f = open("2_6output.txt", "w")
f.write("2_6output             Nhi Vo     912796677     \n\n")

obj1 = ValidateSeq("AGGGGTCC")
status1 = obj1.validate()

obj2 = ValidateSeq("ACGTTTAUDVAAA")
status2 = obj2.validate()

f.write(obj1.seq)
if status1 == True:
    line1 = "\n is a DNA sequence\n"
else:
    line1 = "\n is not a DNA sequence\n"
f.write(line1)
f.write("\n")
print(obj1.seq + line1)
f.write(obj2.seq)
if status2 == True:
    line2 = "\n is a DNA sequence\n"
else:
    line2 = "\n is not a DNA sequence\n"
f.write(line2)
print(obj2.seq + line2)

f.close()

        
