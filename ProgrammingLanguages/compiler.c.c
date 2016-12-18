//
//  main.c
//  compiler.c
//
//  Created by Blake LaFuente on 10/31/16.
//  Copyright © 2016 Blake LaFuente. All rights reserved.
//
//
//  main.c
//  compiler.c
//
//  Created by Blake LaFuente on 10/31/16.
//  Copyright © 2016 Blake LaFuente. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*constants for true and false*/
#define FALSE 0
#define TRUE 1

/*enumerated types for token types*/
//21 Token types
typedef enum
{
    MAIN, ID, INTLITERAL, READ, WRITE, IF, ELSE, WHILE,	
    PLUSOP, MINUSOP, MULTIPLYOP, DIVIDEOP, ASSIGNOP,
    LPAREN, RPAREN, LBRACKET, RBRACKET, COMMA, BOOLEAN, SEMICOLON, SCANEOF
} token;

/*functions declarations related to scanner*/
token scanner();
void clear_buffer();
void buffer_char(char c);
token check_reserved();
void lexical_error();

/*functions declarations related to parser*/
void parser();
void program();
void statement_list();
void statement();
void id_list();
void expression_list();
void expression();
void boolean_expr();
void term();
void add_op();
void match(token tok);
void syntax_error();

/*global variables*/
FILE *fin;		/*source file*/
token next_token;	/*next token in source file*/
char token_buffer[100]; /*token buffer*/
int token_ptr; 		/*buffer pointer*/
int line_num =  1;	/*line number in source file*/
int error = FALSE;      /*flag to indicate error*/

/****************************************************************************/


/*returns next token from source file*/
token scanner()
{
    char c; 								/*current character in source file*/
    
    clear_buffer();							/*empty token buffer*/
    
    while(TRUE)								/*loop reads and returns next tokens*/
    {
        c = getc(fin);						/*read a character from source file*/
        
        if(c == EOF)						/*end of file*/
            return SCANEOF;
        
        else if (isspace(c))				/*skip white spaces and count line number*/
        {
            if(c == '\n')
                line_num = line_num + 1;
        }
        
        else if (isalpha(c)) 				/*identifier or reversed word*/
        {
            buffer_char (c); 				/*buffer the first character*/
            c = getc (fin);
            while (isalnum(c) || c == '_')	/*read and buffer subsequent characters*/
            {
                buffer_char(c);
                c = getc(fin);
            }
            ungetc(c, fin);					/*put back the last character read*/
            return check_reserved();		/*return identifier or reserved word*/
        }
        
        /*integer literal*/
        else if (isdigit(c))
        {
            buffer_char(c);   				/*buffer the first character*/
            c = getc(fin);
            while(isdigit(c)) 				/*read and buffer subsequent characters*/
            {
                buffer_char(c);
                c = getc(fin);
            }
            ungetc(c, fin);  				/*put back the last character read*/
            return INTLITERAL;  			/*return integer literal*/
        }
        
        else if (c == '(')   				/*left parentheses*/
            return LPAREN;
        
        else if (c == ')')   				/*right parentheses*/
            return RPAREN;
        
        else if (c == '{')  				/*left bracket*/
            return LBRACKET;
        
        else if (c == '}')					/*right bracket*/
            return RBRACKET;
        
        else if (c == ',')   				/*comma*/
            return COMMA;
        
        else if (c == ';')  				/*semicolon*/
            return SEMICOLON;
        
        else if (c == '+')  				/*plus operator*/
            return PLUSOP;
        
        else if (c == '-')					/*minus operator*/
            return MINUSOP;
        
        else if(c == '*') 					/*multiplication operator*/
            return MULTIPLYOP;
        
        else if(c == '/')  					/*comment or divide operator*/
        {
            c = getc(fin);
            if(c == '/')					/*comment begins*/
            {
                do 							/*read and discard until end of line*/
                    c = getc(fin);
                while(c != '\n');
                line_num = line_num + 1;
            }
            else							/*divide operator*/
            {
                ungetc(c, fin);
                return DIVIDEOP;
            }
        }
        else if (c == '<' || c == '>')		/*boolean less than or greater tham*/
        {
            c = getc(fin);
            if(c != '=')					/*boolean less than or equal to */
            {								/*or greater than or equal to*/
                ungetc(c,fin);
            }
            return BOOLEAN;
        }
        
        else if(c == '!' || c == '=')		/*possible boolean equal to or not equal to*/
        {
            c = getc(fin);
            if(c == '=')					/* need equal sign for == or != operator*/
                return BOOLEAN;
            else							/*error due to missing equal sign*/
            {
                ungetc(c, fin);
                lexical_error();
            }
        }
        
        else if(c == ':')					/*possible assignment operator*/
        {
            c = getc(fin);
            if(c == '=')					/*assignment operator*/
                return ASSIGNOP;
            else							/*error due to missing equal sign*/
            {
                ungetc(c, fin);
                lexical_error();
            }
        }
        
        else								/*invalid character*/
            lexical_error();
    }
}

/************************************************************************/

/*clears the buffer*/
void clear_buffer()
{
    token_ptr = 0;							/*reset token pointer*/
    token_buffer[token_ptr] = '\0';			/*add null character*/
}

/********************************************************************/

/*appends the character to buffer*/
void buffer_char(char c)
{
    token_buffer[token_ptr] = c;			/*append current caracter*/
    token_ptr = token_ptr + 1;				/*move token pointer*/
    token_buffer[token_ptr] = '\0';			/*move null character*/
}

/*********************************************************************/

/*checks whether buffer is reserved word or identifier*/
token check_reserved()						/*six reserved words*/
{
    if(strcmp(token_buffer, "main") == 0)	
        return MAIN;						/*main to start program*/
    else if(strcmp (token_buffer, "read") == 0)
        return READ;						/*read statement*/
    else if(strcmp(token_buffer, "write") == 0)
        return WRITE;						/*write statement*/
    else if(strcmp(token_buffer, "if") == 0)
        return IF;							/*conditional if statement*/
    else if(strcmp(token_buffer, "while") == 0)
        return WHILE;						/*while-loop statement*/
    else if(strcmp(token_buffer, "else") == 0)	
        return ELSE;						/*else for if-else statement*/
    else									/*identifier*/
        return ID;
}

/***********************************************************************/

/*reports lexical error and sets error flags*/
void lexical_error()						/*checked with scanner()*/
{
    printf("lexical error in line %d\n", line_num);
    error = TRUE;
}

/************************************************************************/

/*parses source file*/
void parser()
{
    next_token = scanner();						/*read the first token*/
    program();									/*parse the program*/
    match(SCANEOF);								/*check end of file*/
}

/**********************************************************************/

/*parses a program*/
/* <program> --> main<lb><stmtlist><rb> */
void program()
{
    match(MAIN);								/*main*/
    match(LBRACKET);							/* { */
    statement_list();							/*list of statements*/
    match(RBRACKET);							/* } */
}
/*******************************************************************/

/*parses list of statements*/
/* <stmtlist> --> <stmt>{<stmt>} */
void statement_list()
{
    statement();								/*first statement*/
    while (TRUE)
    {
        if(next_token == ID || next_token == READ || next_token == WRITE ||
           next_token == IF || next_token == WHILE)
            statement();						/*subsequent statement*/
        else
            break;
    }
}

/*********************************************************************/

/*parses one statement*/
/* 	<stmt> --> id:=<expr>;
 <stmt> --> read(<idlist>);
 <stmt> --> write(<exprlist>);
 <stmt> --> if<lp><boolean-expr><rp>
 			<lb><stmtlist><rb>
 			[else<lb><stmtlist><rb>]
 <stmt> --> while<lp><boolean-expr><rp>
 			<lb><stmtlist><rb> */
void statement()
{
    if(next_token == ID)					/*assignment statement*/
    {
        match(ID);
        match(ASSIGNOP);
        expression();
        match(SEMICOLON);
    }
    else if (next_token == READ)			/*read statement*/
    {
        match(READ);
        match(LPAREN);
        id_list();
        match(RPAREN);
        match(SEMICOLON);
    }
    else if (next_token == WRITE)			/*write statement*/
    {
        match(WRITE);
        match(LPAREN);
        expression_list();
        match(RPAREN);
        match(SEMICOLON);
    }
    else if (next_token == IF)    			/*if statement*/
    {
        match(IF);
        match(LPAREN);
        boolean_expr();
        match(RPAREN);
        match(LBRACKET);
        statement_list();
        match(RBRACKET);
        if(next_token == ELSE)  			/*if-else statement */ 
        {
            match(LBRACKET);
            statement_list();
            match(RBRACKET);
        }
        
    }
    else if (next_token == WHILE) 			/*while statement*/
    {
        match(WHILE);
        match(LPAREN);
        boolean_expr();
        match(RPAREN);
        match(LBRACKET);
        statement_list();
        match(RBRACKET);
    }
    else									/*invalid beginning of statement*/
        syntax_error();
}

/*******************************************************************/

/*parses list of identifiers*/
/* <idlist> --> id{,id} */
void id_list()
{
    match(ID);								/*first identifier*/
    while(next_token == COMMA)
    {
        match(COMMA);
        match(ID);							/*subsequent identifiers*/
    }
}

/*******************************************************************/

/*parses list of expressions*/
/* <explist> --> <exp>{,<exp>} */
void expression_list()
{
    expression();							/*first expression*/
    while(next_token == COMMA)
    {
        match(COMMA);
        expression();						/*subsequent expressions*/
    }
}

/****************************************************************/

/*parses one expression*/
/* <exp> --> <term>{<adop><term>} */
void 	expression()
{
    term();									/*first term*/
    while(next_token == PLUSOP || next_token == MINUSOP ||
          next_token == MULTIPLYOP || next_token == DIVIDEOP)
    {
        add_op();							/*plus, minus, multiply, or divide operators*/
        term();								/*subsequent terms*/
    }
}

/*******************************************************************/
/* parses boolean -expr */
/*
 <boolean-expr> --> <term><boolean><term>
 */

void boolean_expr()
{
    term();								/*first term*/
    match(BOOLEAN);						/* > or < or <= or >= or == or != */
    term();								/*subsequent term*/
}

/******************************************************************/

/*parses one term*/
/* 	<term> --> id
 <term> --> integer
 <term> --> (<expr>)	*/

void term()
{
    if(next_token == ID)				/*identifier*/
        match(ID);
    else if(next_token == INTLITERAL) 	/*integer literal*/
        match(INTLITERAL);
    else if(next_token == LPAREN)		/*expression inside parentheses*/
    {
        match(LPAREN);
        expression();
        match(RPAREN);
    }
    else								/*invalid term*/
        syntax_error();
}

/***********************************************************************/

/*parses plus, minus, multiply, or divide operator*/
/* <adop> --> +|-|*|/ */
void add_op()
{
    if(next_token == PLUSOP || next_token == MINUSOP
    	|| next_token == MULTIPLYOP || next_token == DIVIDEOP)
        match(next_token);
    else								/*invalid operator*/
        syntax_error();	
}

/*********************************************************************/

/* checks whetherthe expected token and the actual token match,
	and also reads the next token from the source file */

void match(token tok)
{
    if(tok == next_token)				/*expected token and actual token match*/
        ;
    else
        syntax_error();					/*expected token and actual token do not match*/
    
    next_token = scanner();				/*read the next token*/
}


/***********************************************************************/

/*reports syntax error*/
void syntax_error()						/*checked with parser()*/
{
    printf("syntax error in line %d\n", line_num);
    error = TRUE;
}

/**************************************************************************/

int main()
{
    int option;							/*user input of whether to use scanner or parser*/
    error = FALSE;						/*No errors should be set at beginning*/
    token file_token;					/*token returned by scanner()*/
    char infile_name[50];				/*file name of input file*/
    char outfile_name[50];				/*file name of output file*/
    FILE *outfile;						/*output file created*/
    int count = 0;						/*Will print new line every ten tokens*/
    printf("XMicro Compiler:\n\n1. Use Scanner\n2. Use Parser\n\nEnter option number:\n");
    scanf("%d", &option);				/*scans user choice*/
    if (option == 1)					/*User chose scanner*/
    {
        printf("Enter name of the source code file:\n");
        scanf("%s", infile_name);		/*scans in input file name*/
        fin = fopen(infile_name, "r");	/*opens and reads input file*/
        printf("Enter name of output file:\n");	
        scanf("%s", outfile_name);		/*scans in output file name*/
        outfile = fopen(outfile_name, "w");	/*opens and writes to output file*/     
        while (file_token != SCANEOF)	/*reads input file until End of File token*/
        {
            file_token = scanner();		/*returns token from scanner()*/
            if(file_token == 0)			/*prints proper token name*/
            {
                fprintf(outfile, "MAIN ");
            }
            else if(file_token == 1)
            {
                fprintf(outfile, "ID ");
            }
            else if(file_token == 2)
            {
                fprintf(outfile, "INTLITERAL ");
            }
            else if(file_token == 3)
            {
                fprintf(outfile, "READ ");
            }
            else if(file_token == 4)
            {
                fprintf(outfile, "WRITE ");
            }
            else if(file_token == 5)
            {
                fprintf(outfile, "IF ");
            }
            else if(file_token == 6)
            {
                fprintf(outfile, "ELSE ");
            }
            else if(file_token == 7)
            {
                fprintf(outfile, "WHILE ");
            }
            else if(file_token == 8)
            {
                fprintf(outfile, "PLUSOP ");
            }
            else if(file_token == 9)
            {
                fprintf(outfile, "MINUSOP ");
            }
            else if(file_token == 10)
            {
                fprintf(outfile, "MULTIPLYOP ");
            }
            else if(file_token == 11)
            {
                fprintf(outfile, "DIVIDEOP ");
            }
            else if(file_token == 12)
            {
                fprintf(outfile, "ASSIGNOP ");
            }
            else if(file_token == 13)
            {
                fprintf(outfile, "LPAREN ");
            }
            else if(file_token == 14)
            {
                fprintf(outfile, "RPAREN ");
            }
            else if(file_token == 15)
            {
                fprintf(outfile, "LBRACKET ");
            }
            else if(file_token == 16)
            {
                fprintf(outfile, "RBRACKET ");
            }
            else if(file_token == 17)
            {
                fprintf(outfile, "COMMA ");
            }
            else if(file_token == 18)
            {
                fprintf(outfile, "BOOLEAN ");
            }
            else if(file_token == 19)
            {
                fprintf(outfile, "SEMICOLON ");
            }
            else if(file_token == 20)
            {
                fprintf(outfile, "SCANEOF ");
            }
            count++;
            if(count == 10)			/*prints new line every ten tokens*/
            {
                fprintf(outfile, "\n");
                count = 0;
            }
        }
         
        fclose(fin);				/*close files*/
        fclose(outfile);
        
    }
    
    if(option == 2)
    {
        error = FALSE;
        printf("Enter name of the source code file:\n");
        scanf("%s", infile_name );
        fin = fopen(infile_name, "r");
        parser();						/*checks for syntax errors*/
        if(error == FALSE)				/*prints message if there are no errors*/
        {
            printf("Parsing is successful!\n");
        }
        fclose(fin);					/*closes file*/
    }
    
    return 0;							/*end of program*/
}

/****************************************************************************/