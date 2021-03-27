## 2_5code
## Nhi Vo
## October 9, 2018


## calculate area, perimeter, length of diagnoal

class Rectangle:

    def __init__(self, height, length):
        self.height = height
        self.length = length

    def area(self):
        return self.height*self.length

    def perimeter(self):
        return (self.height*2) + (self.length*2)

    def diagonal(self):
        from math import sqrt
        leg1 = self.height*self.height
        leg2 = self.length*self.length
        diag = leg1 + leg2
        return sqrt(diag)

    
class Square(Rectangle):

    def __init__(self, side):
        self.side = side

    def area(self):
        return self.side*self.side

    def perimeter(self):
        return self.side*4

    def diagonal(self):
        from math import sqrt
        diag = (self.side *self.side)
        diag = sqrt(diag + diag)
        return(diag)           

f = open("2_5output.txt", "w")
f.write("2_5output             Nhi Vo     912796677     \n\n\n")
rec_obj1 = Rectangle(3,4)
rec_obj2 = Rectangle(5, 2)

rec_area1 = rec_obj1.area()
rec_perim1 = rec_obj1.perimeter()
rec_diag1 = rec_obj2.diagonal()

line1 = "Rectangle object 1 has height of: " + str(rec_obj1.height) + " and a length of: " + str(rec_obj1.length) + "\n"
print(line1)
f.write(line1)
line2 = "Rectangle object 2 has height of: " + str(rec_obj2.height) + " and a length of: " + str(rec_obj2.length) + "\n\n"
print(line2)
f.write(line2)

line3 = "Rectangle object 1 has: \nArea = " + str(rec_area1) + "\nPerimeter = " + str(rec_perim1) + "\nDiagonal = " + str(rec_diag1) + "\n\n"
print(line3)
f.write(line3)

rec_area2 = rec_obj2.area()
rec_perim2 = rec_obj2.perimeter()
rec_diag2 = rec_obj2.diagonal()

line4 = "Rectangle object 2 has: \nArea = " + str(rec_area2) + "\nPerimeter = " + str(rec_perim2) + "\nDiagonal = " + str(rec_diag2) + "\n\n\n"
print(line4)
f.write(line4)

sq_obj1 = Square(2)
sq_obj2 = Square(6)

sq_area1 = sq_obj1.area()
sq_perim1 = sq_obj1.perimeter()
sq_diag1 = sq_obj1.diagonal()

line1 = "Square object 1 has side of: " + str(sq_obj1.side) + "\n"
print(line1)
f.write(line1)
line2 = "Square object 2 has side of: " + str(sq_obj2.side) + "\n\n"
print(line2)
f.write(line2)

line3 = "Square object 1 has: \nArea = " + str(sq_area1) + "\nPerimeter = " + str(sq_perim1) + "\nDiagonal = " + str(sq_diag1) + "\n\n"
print(line3)
f.write(line3)

sq_area2 = sq_obj2.area()
sq_perim2 = sq_obj2.perimeter()
sq_diag2 = sq_obj2.diagonal()

line4 = "Square object 2 has: \nArea = " + str(sq_area2) + "\nPerimeter = " + str(sq_perim2) + "\nDiagonal = " + str(sq_diag2) + "\n\n\n"
print(line4)
f.write(line4)

f.close()
