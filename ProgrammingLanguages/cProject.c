//
//  program.c
//  BlakeLaFuente341P1
//
//  Created by Blake LaFuente on 10/11/16.
//  Copyright © 2016 Blake LaFuente. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

double compute_pi(int n);
double compute_sqrt(double x);
int is_prime(int n);
void display_primes(int n);
void process_scores();
double compute_tax(int income, char *status, char state);
int quadratic();
int factorial();
void file_count();
void file_sort();
void file_student();

//reads in an integer, n
//computes an estimation of pi based off the infinite
//series: pi = 4(1-1/3+1/5-1/7+1/9-1/11...etc)
//returns estimation of pi, answer
double compute_pi(int n)
{
    double answer = 0.0;
    double denominator =  1;
    for(int x = 0; x < n; x++)
    {
        if (x % 2 == 0)
        {
            answer = answer + (1.0/denominator);
        }
        else
        {
            answer = answer - (1.0/denominator);
        }
        denominator  = denominator + 2.0;
    }
    answer = answer * 4.0;
    return answer;
}

//reads a double, x
//computes an estimation of the square root
//of x based of the formula next=0.5*(last+x/last)
//run through a loop ten times.
//returns estimation, next
double compute_sqrt (double x)
{
    if(x < 0)
    {
        return -1;
    }
    double last = 1;
    double next = 1;
    for(int i = 1; i <= 10; i++)
    {
        last = next;
        next = 0.5 * (last + x/last);
    }
    return next;
}

//reads an integer, n
//determines if n is a prime number by testing if n is
//less than or equal to 1, an even number greater than 2,
//and looking for mod == 0 for all integers less than half n.
//returns 1 if prime, 0 if not prime
int is_prime(int n)
{
    if (n <= 1)
    {
        return 0;
    }
    if (n > 2  && n % 2 == 0)
    {
        return 0;
    }
    for(int i = 3; i < n / 2; i += 2)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

//This function is called if int n is prime.
//displays all prime numbers starting at 2 up to n.
void display_primes(int n)
{
    printf("The primes of %d are:", n);
    for(int count = 2; count < n; count++)
    {
        int prime = is_prime(count);
        if(prime == 1)
        {
            printf(" %d", count);
        }
    }
}

//This function inputs string names and int scores from the user.
//As each score is entered, the function will keep track of the student names 
//and scores of the highest and lowest scores. It will also compute the average.
//They are displayed when the user enters 'q' or 'Q' to finish.
void process_scores()
{
    int max = 0, min = 0, total = 0, size = 0, score, average;
    char max_name[50];
    char min_name[50];
    printf("Enter student names and scores.\nPress 'q' or 'Q' to finish.\n");
    while(1)
    {
        char name[50];
        scanf("%s", name);
        if(name[0]=='q' || name[0]=='Q')
        {
            break;
        }
        else
        {
            scanf("%d", &score);
            if (total == 0)
            {
                max = score;
                strcpy(max_name, name);
            }
            if(score > max)
            {
                max = score;
                strcpy(max_name, name);
            }
            if(total == 0)
            {
                min = score;
                strcpy(min_name, name);
            }
            if (score < min)
            {
                min = score;
                strcpy(min_name, name);
            }
            total += score;
            size ++;
            
        }
    }
    average = (total/size);
    printf("Average Score: %d\nMinimum Score: %d\nMaximum Score: %d\n", average, min, max);
    printf("Student with minimum score: %s\n", min_name);
    printf("Student with maximum score: %s", max_name);
}

//The percentage of inputted income that is tax is determined
//by whether the person is in-state or out of state, married or single,
//and whether their income is above a certain amount. The income is
//multiplied by this percentage and returned. If an input is incorrect,
//-1 is returned.
double compute_tax(int income, char *status, char state)
{
    double tax;
    if((state == 'i' || state == 'I'))
    {
        if(strcmp(status, "single")==0)
        {
            if(income < 30000 && income >= 0)
            {
                tax = income *0.2;
                return tax;
            }
            else if(income >= 30000)
            {
                tax = income * 0.25;
                return tax;
            }
            else
            {
                return -1;
            }
        }
        else if(strcmp(status, "married")==0)
        {
            if(income >=0 && income < 50000)
            {
                tax = income * 0.1;
                return tax;
            }
            else if(income >= 50000)
            {
                tax = income * 0.15;
                return tax;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            return -1;
        }
    }
    else if((state == 'o' || state == 'O'))
    {
        
        if(strcmp(status, "single")==0)
        {
            if(income < 30000)
            {
                tax = income *0.17;
                return tax;
            }
            else if(income >= 30000)
            {
                tax = income * 0.22;
                return tax;
            }
            else
            {
                return -1;
            }
        }
        else if(strcmp(status, "married")==0)
        {
            if(income >=0 && income < 50000)
            {
                tax = income * 0.7;
                return tax;
            }
            else if(income >= 50000)
            {
                tax = income * 0.12;
                return tax;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
    
}

//The inputs are the variables of the quadratic equation. If solutions are
//found, 1 is returned. Else 0 is returned.
int quadratic(double a, double b, double c, double *solution1, double *solution2)
{
    if(b*b - 4*a*c >= 0)
    {
        *solution1 = (-b + compute_sqrt(b*b - 4*a*c));
        *solution2 = (-b - compute_sqrt(b*b- 4*a*c));
        return 1;
    }
    else
    {
        return 0;
    }
}

//Recursive function that returns all numbers between 1 and the 
//input n multiplied by each other.
int factorial(int n)
{
    if (n > 1)
        return n * factorial(n-1);
    else
        return 1;
}

//Opens a file and reads in all of the characters.
//For each char, the integer, characters, is incremented.
//For each \n character, the integer, lines, is incremented.
//File is closed.
void file_count(char *file, int *characters, int *lines)
{
    FILE *fp;
    char read;
    fp = fopen(file, "r");
    if(fp == NULL)
    {
        printf("File does not exist\n");
    }
    else{
        do{
            read = getc(fp);
            *characters = *characters + 1;
            if (read == '\n')
            {
                *lines = *lines + 1;
            }
        } while(read != EOF);
    }
    fclose(fp);
}

//Variables temp, hold, and flip are used to temporarily hold
//variables during sorting. Dynamically allocated arrays are 
//created for int id, char grade, and double gpa. The file, infile,
//is opened. The first line is an integer, size, that lists the number
//students listed. The arrays are then filled from reading the file.
//Then the arrays are sorted based off id into ascending order. Every 
//time the ids are switched, so are the grades and gpas. Then an 
//output file is created and filled with the sorted arrays. 
//Arrays are freed and file is closed.
void file_sort(char *infile, char *outfile)
{
    int size, temp;
    char hold;
    double flip;
    FILE *fp;
    
    int *id = (int*)malloc(size * sizeof(int));
    char *grade = (char*)malloc(size * sizeof(char));
    double *gpa = (double*)malloc(size * sizeof(double));
    
    fp = fopen(infile, "r");
    fscanf(fp, "%d", &size);
    for(int count = 0; count < size; count++)
    {
        fscanf(fp, "%d", &id[count]);
      fscanf(fp, " %c", &grade[count]);
       fscanf(fp, " %lf", &gpa[count]);
    }
    
    fclose(fp);
    
    for(int i = 0; i < (size - 1); i++)
    {
        for(int j = i + 1; j < size; j++)
        {
            if(id[i] > id[j])
            {
                temp = id[i];
                id[i] = id[j];
                id[j] = temp;
         
                hold = grade[i];
                grade[i] = grade[j];
                grade[j] = hold;
          
                flip = gpa[i];
                gpa[i] = gpa[j];
                gpa[j] = flip;
            }
        }
    }
    
    FILE *f = fopen(outfile, "w");
    
    for(int spot = 0; spot < size; spot++)
    {
        fprintf(f, "%d ", id[spot]);
        fprintf(f, "%c ", grade[spot]);
    fprintf(f, "%lf\n", gpa[spot]);
    }
    
    free(id);
    free(grade);
    free(gpa);
    fclose(f);
}

//File is opened. A struct called student is created containing
//a string: name, an int: age, and a double: gpa. A dynamically allocated
//array of student structs is created. The number of students,int size is 
//is scanned from the first line of the file. Then the struct array is filled
//from the rest of the file. The average gpa is calculated and printed. The 
//names of students with at least a 2.0 are printed. Then all of the names
//are printed in alphabetical order. The memory is freed and file is closed.
void file_student(char *infile)
{
    FILE* file = fopen(infile, "r");
    int size;
    char temp[50];
    double average;
    
    struct student
    {
        char name[100];
		int age; 
        double gpa;
    };
    
    fscanf(file, "%d", &size);
    struct student *records = malloc(size * sizeof(struct student));

    for(int count = 0; count < size; count ++)
    {
        fscanf(file, "%s", records[count].name);
        fscanf(file, " %d", &records[count].age);
        fscanf(file, " %lf\n", &records[count].gpa);
        average += records[count].gpa;
    }
    
    average = average/size;
    printf("The average gpa is %lf.\n", average);
    printf("Students whose gpa is at least 2:\n");
    for(int i = 0; i < size; i++)
    {
        if(records[i].gpa >= 2)
        {
            printf("%s\n",records[i].name);
        }
    }
    
    for(int i = 0; i < (size - 1); i++)
    {
        for(int j = i + 1; j < size; j++)
        {
            if(strcmp(records[i].name, records[j].name) > 0)
            {
                strcpy(temp, records[i].name);
                strcpy(records[i].name, records[j].name);
                strcpy(records[j].name, temp);
            }
        }
    }
    
    printf("Students in alphabetical order:\n");
    for(int i = 0; i < size; i++)
    {
        printf("%s\n", records[i].name);
    }
    free(records);
	fclose(file);
}


int main() {
    int choice;        					//used for switch statement
    double answer;						//used for case 1 and 2 answers
	double enter;						//used for case 2 user input
	int input;							//used for case 1 and 3 user inputs
    int income;							//used for case 5 user input
    double tax;							//used for case 5 answer
    char status[10], state;				//used for case 5 input
    double a, b, c, solution1, solution2; //used for case 6, quadratic variables
    int has_solutions;					//boolean for case 6
    int n, solve;						//Variables for case 7
    char file[100];						//file name
    int characters = 0, lines = 0;		//Variables for case 8
    char infile[100];					//file name for input file
    char outfile[100];					//file name for output file
    
    while(choice != 11)
    {						//prints menu every loop
        printf("     Menu\n----------------\n1-computing pi\n2-computing square root\n");
        printf("3-displaying primes\n4-processing grades\n5-computing tax\n6-solving ");
        printf("quadratic\n7-computing factorial\n8-counting file\n9-sorting file\n");
        printf("10-student file\n11-quit\n\nEnter option:");
        
        scanf("%d", &choice);   //User input for menu
        
        switch(choice){
                
                
            case 1 :
                //computation of pi
                printf("How many terms of pi?\n");
                scanf("%d", &input);
                answer = compute_pi(input);
                printf("%lf \n", answer);
                break;
                
            case 2:
                //computation of square root
                printf("What number would you like to find the square root of? \n");
                scanf("%lf", &enter);
                answer = compute_sqrt(enter);
                if (answer == -1)
                {
                    printf("Input was a negative number\n");
                    break;
                }
                printf("%lf \n", answer);
                break;
                               
            case 3:
                //Determines if prime and displays primes
                printf("What number would you like to display the primes of?\n");
                scanf("%d", &input);
                int prime = is_prime(input);
                if (prime == 1)
                {
                    display_primes(input);
                    printf("\n");
                }
                else
                {
                    printf("Your input was not a prime number\n");
                }
                break;
                                
            case 4:
                //processes scores
                process_scores();
                printf("\n");
                break;
                
                
            case 5:               
                //Determines tax amount
                printf("Enter Income: ");
                scanf("%d",&income);
                printf("Is the tax payer:\n1.single\n2.married\n");
				printf("Enter 'single' or 'married': ");
                scanf("%s", status);
                printf("Is the tax payer a:\n1.in-state resident\n");
				printf("2.out-of-state resident\nEnter 'i' or 'o': ");
                scanf("\n%c", &state);
                tax = compute_tax(income, status, state);
                
                if(tax == -1)
                {
                    printf("At least one input was invalid.\n");
                }
                else
                {
                    printf("The tax amount is $%lf.\n", tax);
                }
                break;                
                
            case 6:
				//Determines solutions for quadratic equation
                printf("Quadratic Equation: ax^2+bx+c=0\nEnter value for a:\n");
                scanf("%lf",&a);
                printf("Enter value for b:\n");
                scanf("%lf",&b);
                printf("Enter value for c:\n");
                scanf("%lf",&c);
                has_solutions = quadratic(a, b, c, &solution1, &solution2);
                if(has_solutions == 0)
                {
                    printf("There are no solutions\n");
                }
                else
                {
                    printf("Solution 1: %lf\nSolution 2: %lf\n", solution1, solution2);
                }
                break;
                
                
            case 7:              
                //Determines factorials of integer input
                printf("What number would you like the factorial of?\n");
                scanf("%d", &n);
                solve = factorial(n);
                printf("The factorial of %d is %d\n", n, solve);
                break;
                
            case 8:                
                //Counts lines and characters in a file
                printf("Enter file name:\n");
                scanf("%s", file);
                file_count(file, &characters, &lines);
                printf("Number of characters: %d\n", characters);
				printf("Number of lines: %d\n", lines);
                break;
                
            case 9:                
				//Reads input file. Creates sorted output file.
                printf("What is the name of your input file?\n");
                scanf("%s", infile);
                printf("What is the name of your output file?\n");
                scanf("%s", outfile);
                file_sort(infile, outfile);
                printf("Output file %s created.\n", outfile);
                break;
                
            case 10:
                //Computes and prints student data from file
                printf("What is the name of your input file?");
                scanf("%s", infile);
                file_student(infile);
                break;
                
            case 11:
                
                printf("Goodbye!\n");
                break;               
                
            default:
                
                printf("That was an invalid choice. Try again:\n");
                
        }
    }
    
    return 0;
}

