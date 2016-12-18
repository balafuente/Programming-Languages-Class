#Blake LaFuente
#COSC 341 Assignment 9
#Python Project

#value of pi returned based on term in infinite series
def compute_pi(n):
    answer = 0.0
    denominator = 1
    for k in range(0,n):
        if k % 2 == 0:   #Even terms are added
            answer = answer + (1.0/denominator)
        else:  #odd terms are subtracted
            answer = answer - (1.0/denominator)
        denominator = denominator + 2.0 #denominator increases by 2 each term
    answer = answer * 4.0
    return answer

#computes square root based off relation equation
def compute_sqrt(x):
    if x < 0:
        return -1
    last = 1.0
    next = 1.0
    for k in range(1,10): #runs through relation equation ten times
        last = next
        next = 0.5*(last + x/last)
    return next

#checks if number is divisble by preceding terms
def is_prime(n):
    if n <= 1: #negatives and zero aren't prime
        return 0
    if n > 2 and n % 2 == 0:  #even numbers other than 2 aren't prime
        return 0
    k = 3
    while k < (n/2):   #checks if divisible by odd numbers less than half n
        if n % k == 0:
            return 0
        k += 2
    return 1    #else is prime

#checks if preceding numbers are prime and displays those that are
def display_primes(n):
    print "The primes of %d are: " % n
    for x in range(n +1):
        if is_prime(x) == 1:
            print x

#returns data based on input scores
def process_scores():
    max = 0
    min = 0
    total = 0
    size = 0

    while(1): #only breaks when user inputs 'q' or 'Q'
        print "Enter student name and score:\nPress 'q' or 'Q' to finish."
        line = raw_input()
        if len(line) == 1 and line == "q" or line == "Q":
            break
        else:   #takes an input line, first part is name, second is score
            line = line.split()
            if(total == 0): #if first entry, make it max
                max = int(line[1])
                max_name = line[0]
            if int(line[1]) > max: #if entry score is greater than max,
                max = int(line[1]) #make it max
                max_name = line[0]
            if total == 0: #if first entry, make it min
                min = int(line[1])
                min_name = line[0]
            if int(line[1]) < min:  #if entry score is less than min
                min = int(line[1])  #make it min
                min_name = line[0]
            total += int(line[1]) #add score to total
            size = size+1      #add one to size
    average = (total/size);   #compute average
    #print data
    print "Average Score: %d" %average
    print "Minimum Score: %d" %min
    print "Maximum Score: %d" %max
    print "Student with minimum score: %s" %min_name
    print "Student with maximum score: %s" %max_name

#computes tax by multiplying income by the rate
#with the corresponding inputs
def compute_tax(income, status, state):
    if state is 'i' or state is 'I':
        if status == "single":
            if income < 30000 and income >= 0:
                tax = income *0.2
                return tax
            elif income >= 30000:
                tax = income * 0.25
                return tax
            else:
                return -1
        elif status == "married":
            if income >=0 and income < 50000:
                tax = income * 0.1
                return tax
            elif income >= 50000:
                tax = income * 0.15
                return tax
            else:
                return -1
        else:
            return -1
    elif state is 'o' or state is 'O':
        if status == "single":
            if income < 30000:
                tax = income *0.17
                return tax
            elif income >= 30000:
                tax = income * 0.22
                return tax
            else:
                return -1
        elif status == "married":
            if income >=0 and income < 50000:
                tax = income * 0.07
                return tax
            elif income >= 50000:
                tax = income * 0.12
                return tax
            else:
                return -1
        else:
            return -1
    else:
        return -1


#solves quadratic equation based on inputs
def solve_quadratic(a, b, c):
    if b*b - 4*a*c >= 0:  #checks if inputs have solutions
        #computes solutions
        solution1 = (-b + compute_sqrt(b*b - 4*a*c))
        solution2 = (-b - compute_sqrt(b*b - 4*a*c))
        return [solution1, solution2]
    else:
        return [0,0]

#sorts list based on selection sort
def sort(my_list):
    for i in range( len( my_list ) ):
        least = i
        for k in range( i + 1 , len( my_list ) ):
            if my_list[k] < my_list[least]:
                least = k

        swap( my_list, least, i )
    return my_list

#swaps values
def swap( A, x, y ):
  tmp = A[x]
  A[x] = A[y]
  A[y] = tmp

#uses input names to create username and password
def id_password(first, last):
    username = first[0]
    username += last
    password = first[0]
    password += first[len(first)-1]
    password += last[0:3]
    password += str(len(first))
    password += str(len(last))
    return username, password


#sorts file based off student ID's
def file_sort(infile, outfile):
    #opens files
    infile = open(infile, 'r')
    outfile = open(outfile, 'w')
    total_students = int(infile.readline())
    k = 0
    #creates lists for data
    idnum = []
    name = []
    gpa = []
    #splits each line into separate data
    #puts data into corresponding list
    for k in range(0, total_students):
        line = infile.readline()
        line = line.strip()
        line = line.split()
        idnum.append(int(line[0]))
        name.append(line[1])
        gpa.append(line[2])

    #sorts and swaps data based off student ID's
    for i in range(0, total_students-1):
        for j in range(i+1, total_students):
            if idnum[i] > idnum[j]:
                temp = idnum[i];
                idnum[i] = idnum[j];
                idnum[j] = temp;

                hold = name[i];
                name[i] = name[j];
                name[j] = hold;

                flip = gpa[i];
                gpa[i] = gpa[j];
                gpa[j] = flip;
    #writes sorted data to otuput file
    for p in range(0, total_students):
        outfile.write(str(idnum[p]) + " " + name[p] + " " + gpa[p] + "\n")
    infile.close()   #closes files
    outfile.close()

def main():
    choice = 0
    #prints menu
    while choice != 11:
        print "      Menu"
        print "1. Compute Pi"
        print "2. Compute Square Root"
        print "3. Check if Prime"
        print "4. Display Primes"
        print "5. Process Scores"
        print "6. Compute Tax"
        print "7. Solve Quadratic Equation"
        print "8. Sort List"
        print "9. ID & Password"
        print "10. File Sort"
        print "11. Quit"

        #takes menu choice from user
        choice = input("\nEnter Number: ")

        if choice == 1:
            #user inputs number to compute pi
            number = input("Enter number to compute pi with: ")
            pi = compute_pi(number)
            print "The answer is %f" %pi

        if choice == 2:
            #inputs number to square root
            number = input("Enter number to square root: ")
            answer = compute_sqrt(number)
            print "The square root of %d is %f" %(number, answer)

        if choice == 3:
            #user inputs number to test
            number = input("What number do you want to test if prime: ")
            if is_prime(number) == 0:
                print "%d is not a prime number" %number
            else:
                print "%d is a prime number" %number

        if choice == 4:
            #user inputs number to display preceding primes
            number = input("Enter number to display primes of: ")
            display_primes(number)

        if choice == 5:
            process_scores()

        if choice == 6:
            #user inputs tax information
            income = input("Enter your income: ")
            status = raw_input("single or married:  ")
            state = raw_input("In-state or out-of-state (Enter 'i' or 'o'):")
            tax = compute_tax(income, status, state)
            if tax == -1:
                print "There was an error with one of your inputs"
            else:
                print "The amount you are taxed is $%d" %tax

        if choice == 7:
            #user inputs quadratic coefficients
            print "Quadratic equation is ax^2 + bx + c = 0"
            a = input("Enter value for a: ")
            b = input("Enter value for b: ")
            c = input("Enter value for c: ")
            solutions = solve_quadratic(a,b,c)
            solution1 = solutions[0]
            solution2 = solutions[1]
            if solution1 == 0:
                print "Those inputs have no solution"
            else:
                print "Solution 1 is %f" %solution1
                print "Solution 2 is %f" %solution2

        if choice == 8:
            #user inputs list of ints on single line
            print "Enter list of numbers on a single line separated by a single space"
            string_input = raw_input()
            input_list = string_input.split() #splits the input string on spaces
            # process string elements in the list and make them integers
            input_list = [int(a) for a in input_list]
            input_list = sort(input_list)
            print "Sorted List: "
            print(input_list)

        if choice == 9:
            #user inputs first and last name
            fname = raw_input("Enter first name: ")
            lname = raw_input("Enter last name: ")
            fname = fname.upper()
            lname = lname.upper()
            username, password = id_password(fname, lname)
            print "The username is %s" %username
            print "The password is %s" %password

        if choice == 10:
            #user inputs input and output file names
            infile = raw_input("Enter name of input file: ")
            outfile = raw_input("Enter name of output file: ")
            file_sort(infile, outfile)
            print "Output file successfully created."

        if choice == 11:
            #causes loop to break
            print "Goodbye!"

#begins program
main()
