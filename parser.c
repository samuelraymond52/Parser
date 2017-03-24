/* front.c - a lexical analyzer system for simple
 arithmetic expressions */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


/* Global declarations */

/* Variables */

int charClass;
char lexeme [100];
int indexLine;
char nextChar;
char lastchar;
int lexLen;
size_t new_expression_length = 0;
int token;
int nextToken;
char endCharacter;
char * new_expression = NULL;
FILE *in_fp, *fopen();

/* Function declarations */
void addChar();
void getChar();
void getNonBlank();
int lex();
void getLine();
void addLine();
void expr();
void term();
void factor();
void error();

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define NEWLINE 2
#define UNKNOWN 99


/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
/******************************************************/


/* main driver */
i main() { 
   if ((in_fp = fopen("front.in", "r")) == NULL)
     printf("ERROR - cannot open front.in \n");
   else {
     while ((get_exression = getline(&new_expression, &new_expression_length, in_fp)) != EOF) {
       indexLine = 0;
       getChar();
       if (new_expression != NULL) {
         do {
           lex();
           expr();
         } while (nextToken != EOF);
       }
     }
   }
}



/*****************************************************/
/* lookup - a function to lookup operators and parentheses
 and return the token */
int lookup(char ch) {
  switch (ch) {
   case '(':
    addChar();
    nextToken = LEFT_PAREN;
    break;

 case ')':
    addChar();
    nextToken = RIGHT_PAREN;
    break;

 case '+':
    addChar();
    nextToken = ADD_OP;
    break;

 case '-':
    addChar();
    nextToken = SUB_OP;
    break;

 case '*':
    addChar();
    nextToken = MULT_OP;
    break;

 case '/':
    addChar();
    nextToken = DIV_OP;
    break;

  default:
     addChar();
     nextToken = EOF;
     break;
  }
  return nextToken;
}


/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar() {
  if (lexLen <= 98) {
    lexeme[lexLen++] = nextChar;
    lexeme[lexLen] = 0;
  }
  else
    printf("Error - lexeme is too long \n");
}
/*****************************************************/
/* getChar - a function to get the next character of
             input and determine its character class */

void getChar() {
  if ((nextChar = getc(in_fp)) != EOF) {
    if (isalpha(nextChar))
      charClass = LETTER;
    else if (isdigit(nextChar))
           charClass = DIGIT;
         else charClass = UNKNOWN;
   }
   else
     charClass = EOF;
}

/*****************************************************/
/* getNonBlank - a function to call getChar until it
                 returns a non-whitespace character */
void getNonBlank() {
  while (isspace(nextChar))
    getChar();
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic
         expressions */
int lex() {
  lexLen = 0;
  getNonBlank();
  switch (charClass) {
 	/* Parse identifiers */
  case LETTER:
    addChar();
    getChar();
    while (charClass == LETTER || charClass == DIGIT) {
      addChar();
      getChar();
    }
  nextToken = IDENT;
  break;
/* Parse integer literals */
  case DIGIT:
    addChar();
    getChar();
    while (charClass == DIGIT) {
      addChar();
      getChar();
    }
    nextToken = INT_LIT;
    break;
/* Parentheses and operators */
  case UNKNOWN:
    lookup(nextChar);
    etChar();
    break;
/* EOF */
  case EOF:
    nextToken = EOF;
    lexeme[0] = 'E';
    lexeme[1] = 'O';
    lexeme[2] = 'F';
    lexeme[3] = 0;
    break;
 } /* End of switch */
 printf("Next token is: %d, Next lexeme is %s\n",
         nextToken, lexeme);
 return nextToken;
} /* End of function lex */