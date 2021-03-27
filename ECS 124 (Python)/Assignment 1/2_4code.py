## Lab 1
## Nhi Vo
## October 9, 2018

## 2_4:


## a:
def C_to_F():
    s1 = "The entered Celcius is: \n"
    x = input("Celcius to Fahrenheit: ")
    s2 = "which converts to:"
    print(s2)
    try:
        x_s = int(x)
    except:
        x_s = float(x_s)
        x_s = float(x_s * (9/5) + 32.0)
    else:
        x_s = float(x_s*(9/5)+32.0)
    x_s = str(x_s)
    s3 = ("\nFahrenheit")
    print(x_s, s3)
    lines = s1 + x + "\n" + s2 + "\n" + x_s + s3 + "\n"
    f.write(lines)
    return x_s
    
## b:
def hypotenuse():
    from math import sqrt
    print("Enter two legs of triangle one at a time: ")
    a = int(input())
    b = int(input())
    c = a*a + b*b
    c = sqrt(c)
    c_s = str(c)
    print("Hypotenuse = ", c_s)
    s1 = "The two legs entered are: \n"
    s2 = str(a) + " and " + str(b) + "\n" + "Hypotenuse = \n" + c_s
    f.write( s1 + s2)
    return c

## c:
def toUpp():
    print("Enter string to be convert to uppercase: ")
    text = input()
    text_U = text.upper()
    line = s1 = "Entered line: \n\"" + text + "\"" +  "\nconverted to uppercase: \n\"" + text_U + "\"\n"
    print(line)
    f.write(line)
    return text_U

## d:
def toUpp_File():
    fl = input("Enter filename: ")
    inp = open(fl, "r")
    text = inp.read()
    text_U = text.upper()
    s1 = "Line from file \"" + fl + "\" : \n\"" + text + "\"" +  "\nconverted to uppercase: \n\"" + text_U + "\"\n"
    print(s1)
    f.write(s1)
    return text_U

## e:
def palindrome():
    text = input("Check to see if palindrome: ")
    s1 = "Text entered: \n\"" + text + "\"" + "\n"
    print(s1)
    f.write(s1)
    text = text.upper()
    palin = True
    stop = int(len(text)/2)
    rev = len(text)-1
    for i in range(stop):
        if text[i] != text[rev-i]:
            palin = False
    if palin == True:
        s2 = "is a palindrome\n"
    else:
        s2 = "is not a palindrome\n"
    print(s2)
    f.write(s2)
    return palin

## f:
def sm_lg():
    print("Enter three values one at a time (hit enter each time): ")
    a = input()
    b = input()
    c = input()
    line = "The three original entered values: \n" + str(a) + " " + str(b) + " " + str(c) + "\n"
    f.write(line)
    try:
        a = int(a)
    except:
        a = float(a)
    try:
        b = int(b)
    except:
        b = float(b)
    try:
        c = int(c)
    except:
        c = float(c)
    sm = a;
    lg = a;
    if b<sm:
        sm = b
    if c<sm:
        sm = c
    if b>lg:
        lg = b
    if c>lg:
        lg = c
    line2 = "The smallest and largest in respective order: \n" + str(sm) + " " + str(lg) + "\n"
    print("Smallest: ", sm, "\nLargest: ", lg)
    f.write(line2)

## g:
def U_I():
    
    print("Enter the first interval in the following format '(x,y)': ")
    num1 = input()
    print("Enter the first interval in the following format '(x,y)': ")
    num2 = input()
    i = 0
    x1 = ''
    y1 = ''
    s1 = "The two entered intervals are: \n" + num1 + " and " + num2
    f.write(s1)
    while num1[i] == ' ' or num1[i] == '(':
        i = i + 1
    while num1[i] != ',':
        x1 = x1 + num1[i]
        i = i + 1

    i = i + 1
    while num1[i] != ')' :
        y1 = y1 + num1[i]
        i = i + 1

    x1 = int(x1)
    y1 = int(y1)

    j = 0
    x2 = ''
    y2 = ''
    while num2[j] == ' ' or num2[j] == '(':
        j = j + 1
    while num2[j] != ',':
        x2 = x2 + num2[j]
        j = j + 1

    j = j + 1
    while num2[j] != ')' :
        y2 = y2 + num2[j]
        j = j + 1

    x2 = int(x2)
    y2 = int(y2)

    xU = min(x1,x2)
    yU = max(y1,y2)
    xI = max(x1,x2)
    yI = min(y1,y2)
    U = "Union: ("+str(xU)+","+str(yU)+")"
    In = "Intersection: ("+str(xI)+","+str(yI)+")"
    line = U + "\n" + In + "\n"
    print(line)
    f.write(line)

## h:
def sum_I():
    print("Enter an interval in the following format '(x,y)': ")
    num = input()
    i = 0
    x1 = ''
    y1 = ''
    s1 = "The entered interval: \n" + num + "\n"
    f.write(s1)
    while num[i] == ' ' or num[i] == '(':
        i = i + 1
    while num[i] != ',':
        x1 = x1 + num[i]
        i = i + 1

    i = i + 1
    while num[i] != ')' :
        y1 = y1 + num[i]
        i = i + 1

    x1 = int(x1)
    y1 = int(y1)
    total = x1 + y1
    s2 = "its sum: \n" + str(total) + "\n"
    print(s2)
    f.write(s2)
    return total

## i:
def seq_of_int():
    nums = []
    size = 0
    total = 0
    nums_s = "[ "
    print("Enter a sequence of numbers terminated by 0 one at a time (hit enter each time):\n")
    while (True):
        temp = int(input())
        nums.append(temp)
        nums_s = nums_s + str(temp) + " "
        size = size + 1
        if temp == 0:
            break
    largest = nums[0]
    s1 = "Sequence of integers entered: \n" + nums_s + "]"
    print(s1)
    f.write(s1)
    for elem in range(size):
        total = total + nums[elem]
        if nums[elem] > largest:
            largest = nums[elem]
    avg = float(total/size)
    s2 = "\nTotal: "+ str(total) + "\n" + "Mean: " + str(avg) + "\n" + "Largest: " + str(largest) + "\n"
    print(s2)
    f.write(s2)
        
## j:
def dec_seq():
    print("Enter a sequence of numbers terminated by 0 one at a time (hit enter each time): \n")
    nums = []
    size = 0
    nums_s = "[ "
    while (True):
        temp = int(input())
        nums.append(temp)
        size = size + 1
        y = str(temp)
        nums_s = nums_s + y + " "
        if temp == 0:
            break;
    s1 = "Sequence of integers entered: \n" + nums_s + "]" + "\n"
    f.write(s1)
    nums.sort()
    num_dec = "[ "
    for i in range(size-1, -1, -1):
        num_dec = num_dec + str(nums[i]) + " "
    num_dec = num_dec + "]"
    s2 = "Sequence in decreasing order: \n" + num_dec
    print(s2)
    print(s2)
    f.write(s2)

f = open("2_4output.txt", "w")
f.write("2_4output             Nhi Vo     912796677     \n\n\n")
f.write("a)\n")
print("a)\n")
C_to_F()
f.write("b)\n")
print("\nb)\n")
hypotenuse()
f.write("c)\n")
print("\nc)\n")
toUpp()
f.write("d)\n")
print("\nd)\n")
toUpp_File()
f.write("e)\n")
print("\ne)\n")
palindrome()
f.write("f)\n")
print("\nf)\n")
sm_lg()
f.write("g)\n")
print("\ng)\n")
U_I()
f.write("h)\n")
print("\nh)\n")
sum_I()
f.write("i)\n")
print("\ni)\n")
seq_of_int()
f.write("j.)\n")
print("\nj)\n")
dec_seq()

f.close()
