## Programming Assingment 2 - Functions and Conditionals
## Nhi Vo
## October 15, 2017


## Problem 1

def max4(a, b, c, d):
    """ Return the maximum of the four values """
    biggest = a
    
    if a>=d and a>=c and a>=b: ## If a is the largest value return a
        biggest = a
    elif b>=d and b>=c and b>=a: ## If b is the largest value return b
        biggest = b
    elif c>=a and c>=b and c>=d: ## If c is the largest value return c
        biggest = c
    elif d>=b and d>=c and d>=a: ## If d is the largest value return d
        biggest = d
    return biggest

## Problem 2

def grade(s):
    """ Returns a letter grade corresponding to a score """
    score = s

    if 90<=s<=100:  ## If score is between 90-100 print A
        grade = print("'A'") 
    elif 80<=s<=89.99:   ## If score is between 80-89 print B
        grade = print("'B'")
    elif 70<=s<=79.99:   ## If score is between 70-79 print C
        grade = print("'C'")
    elif 60<=s<=69.99:   ## If score is between 60-69 print D
        grade = print("'D'")
    elif s<60:        ## If score is between below 60 print F
        grade = print("'F'") 
    return grade

## Problem 3:

def days(m):
    """ Returns the number of days corresponding to the month """
    if m== "September" or m=="April" or m=="June" or m=="November":
        days = 30   ## If the month is September, April, June, or November, there are 30 days
        return days
    elif m== "February": ## February has 28 days
        days = 28
    else:
        days = 31 ## The rest of the months not listed have 31 days
    return days

## Problem 4:

def inchesToMeters(inch):
    """ Converts a value representing length in inches to meters """
    meters = 0.0254 ## 0.0254 meters in one inch
    inch_tometers= inch * meters ## convert from inches to meters
    return inch_tometers

## Problem 5:

def poundsToKgs(lbs):
    """ Expects a valune representing weight in inches and converts it to lbs """
    lbs_per_kg = 0.453592 ## number of kilograms per pound
    lbs_to_kg = lbs * lbs_per_kg ## converts lbs to kg
    return lbs_to_kg

## Problem 6:

def bmi(inches, pounds):
    """ Expects a subject's height in inches and a number representing the
subject's weight in pounds and returns the BMI """
    bodymassindex = poundsToKgs(pounds) / (inchesToMeters(inches))**2
    ## Computes BMI using previous two functions to convert from lbs to kg and inches to meter
    return bodymassindex

## Problem 7:
               
def bodyMassIndex():
    """ Asks user for infortmation needed to compute BMI, then displays body mass
index along with BMI category from the table """
    name = input("Please enter the subject's name: ")
    height = float(input("Please enter the subject's height in inches: "))
    weight = float(input("Please enter the subject's weight in pounds: "))
    calculatebmi = bmi(height, weight) ## takes the user's answers and computes bmi
    print(name, " has a body mass index of: ", calculatebmi)
    if calculatebmi<18.5:  ## If BMI is over 18.5 print underweight
        print(name, 'is underweight')  
    elif 18.5<=calculatebmi<26:  ## If BMI is or between 18.5 and 26 print normal weight
        print(name, 'is normal weight')
    elif 25<=calculatebmi<30:  ## If BMI is or between 25 and 30 print overweight
        print(name, 'is overweight')
    elif 30<=calculatebmi:  ## If BMI is greater than or equal to 30 print obese
        print(name, 'is obese')

## Problem 8:

def weekly_pay(wage, hour):
    """ Compute the amount of money paid to employee for the week in floating point """
    paynormal= float(wage*hour) ## Calculates pay for regular hourly wage
    pay40 = float(wage*40)  ## Used to calculate pay for employees who work overtime. Calculates pay for the first 40 hours 
    hourovertime = float(hour - 40) ## Calculates hour worked overtime
    payovertime = float((1.5*hourovertime*wage)) ## Calculate wage for overworked hours
    overtime = float(pay40 + payovertime) ## Calculates normal pay and extra work hours
    if 0<=hour<=40:  ## If employee worked 40 or less hours calculate normal pay
        return paynormal
    elif hour>40:  ## If employees work overtime, calculate normal wage for first 40 hours and special overtime pay
        return overtime
        
## Problem 9:

def single(income):
    """ Compute the tax for single households. If the person's income is $32,000 or
less they are charge 10% and if their income is over $32,000 they are 25% of the
amount of income over $32,000 plus $3,200. """
    x = income
    amountover = x-32000
    if x <= 32000:  ## If income is $3200 or less tax is 10%
        return x * .10
    else:  ## If income is over $3200 tax is the amoount over $3200 used amount over $3200 and times by 25% and add $3200
        
        return (amountover*.25)+3200


def married(income):
    """ Compute the tax for married households. If the person's income is $64,000 or
less they are charge 10% and if their income is over $64,000 they are 25% of the
amount of income over $64,000 plus $6,400. """
    x = income
    amountover = x-64000
    if x <= 64000: ## If income is $6400 or less tax is 10%
        return x * .10
    elif x > 64000:  ## If income is over $6400 tax is the amoount over $6400 used amount over $3200 and times by 25% and add $6400
        return (amountover*.25) + 6400

def taxes(status, income):
    """ Computes taxpayer's income that takes in the arguments "s" for single
and "m" for married househoulds. This function uses the previous two fuctions to
do so. """
    x = income
    if status == "s":
        return single(x)
    elif status == "m":
        return married(x)
            

def single(income):
    x=income
    amtover=x-3200
    if x<=32000:
        tax=income*.10
    elif x>3200:
        tax=3200+(amtover*.25)
    return tax
def married(income):
    x=income
    amtover=x-64000
    if x<=64000:
        tax=income*.10
    elif x>64000:
        tax=6400+(amtover*.25)
    return tax
def taxes(sm, income):
    x=sm
    y=income
    if x=="s":
        return single(y)
    elif x=="m":
        return married(y)
    
