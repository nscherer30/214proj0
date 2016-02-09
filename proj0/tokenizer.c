/*
 * tokenizer.c
 *
 * Nicholas Scherer, nds63
 * Griffin Wood,  gbw15
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*To Do:
Need to make currentChar actually represent a char. You changed it from me accessing an index in the array each time. Also im iterating through so currentChar needs to be going one char over each time the local currIndex is going up one.
Decided we have two options: to use the tokens need to add something in main to correctly deal look at the inside of the tokens 
i think weve agreed to this one>	or currently I print out type inside getNextToken and then return the string which should be printed out in main.
Have not deleted of your functions, but I believe currently everything works without any of the helper functions. I wanted to leave them for you jsut in case you wanted to use any of them.
Do we need to deal with there being no char after a 0?
Need to add checks that malloc worked properly. In class he said we needed to do that.
Bad tokens must be printed out in hexform
Might need to fix hasnexttoken i think it might exit a char early.
*/


/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 * Input String will contain the whole input. CurrentIndex is what position the program
 * is in while iterating through the string.  delimPositions will be an array of indexes
 * that refer to the indices where a delimiter exists in the inputString.
 *
 *  This implementation uses a linked list of "Tokens" for readability, modularity, and ease of use 
 *  The inputString is the standard program argument, currIndex is how far through we are
 * through the string and inputSize is the length of the inputString.
 
 */
 
struct TokenizerT_ {
	
	char *inputString;
	int currIndex;
	int inputSize;

}; typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 * 
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char * ts ) {

	if( ts == NULL || ts[0] == '\0'){
		return 0;
	}
	
	/* Make copies of tokenizer and its properties, initialize all to 0 */
	char *inputString = 0;
	int currIndex = 0;
	int inputSize = 0;
	TokenizerT *tokenizer = 0;

	/* Allocate memory for the tokenizer and its fields */
	inputString = (char *)malloc(sizeof(ts));
	tokenizer = malloc(sizeof(TokenizerT));

	/*  Copy the string paramter to inputString variable and get inputSize */
	strcpy(inputString, ts);	
	inputSize = strlen(inputString);
	

	/* Set new tokenizer field values */
	tokenizer->inputString = inputString;
	tokenizer->currIndex = currIndex;
	tokenizer->inputSize = inputSize;
	
	/* If successful, give a tokenizer with initialized fields */
	return tokenizer;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * First, free all allocated properties/elements of the TokenizerT struct. 
 * Then free the pointer to the struct itself
 */

void TKDestroy( TokenizerT * tk ) {

	free(tk->inputString);
	free(tk);
}

int isDelimiter (char c){
	switch (c){
		case ' ':
			return 1;
			break;
		case '\t':
			return 1;
			break;
		case '\v':
			return 1;
			break;
		case '\f':
			return 1;
			break;
		case '\n':
			return 1;
			break;
		case '\r':
			return 1;
			break;
		default:
			return 0;
			break;
	}
}

int buildHex(char * currentChar){

	int counter = 0;
	while(  (*currentChar >= '0' && *currentChar <= '9')  
				    ||
		(*currentChar >= 'A' && *currentChar <= 'F')
		                              ||	 
                 	(*currentChar >= 'a' && *currentChar <= 'f')   ){
			currentChar++;
			counter++;
	}
	if(counter == 0)
		printf("bad token");
	else
		printf("hexadecimal");
	return counter;
}

int buildOct(char *string){
	
	return 0;
}

int buildFloat(char *string){
	
	return 0;
}

int buildDec(char *string){
	/*
	while(isdigit(currentChar)){
		//currIndex++;	
	}*/
	return 0;
}
/* To be implemented with all single character operators, since we use greedy algorithms,
    we will only consider single char operators and start the sequence over */
int isOp (char *currentChar){ //returns positive if opporator and negative if bad token. The number corresponds with the number 
	switch (*currentChar){
		case ' ':
			return 1;
			break;
		case '*':
			printf("indirect");
			return 1;
			break;
		case '&':
			printf("address");
			return 1;
			break;
		case '-':
			printf("minus");
			return 1;
			break;

		case '!':
			if(*(currentChar + 1) == '='){
				currentChar++;
				printf("not equals");
				return 2;
			}else{
				printf("negate");
				return 1;
			}
			break;
		case '~':
			if(*(currentChar + 1) == '-'){
				currentChar++;
				printf("dec");
				return 2;
			}
			printf("1's comp");
			return 1;
			break;

//Sizeof(cast) is put with opporators 
		case '/':
			printf("divide");
			return 1;
			break;
		case '%':
			printf("modulus");
			return 1;
			break;
		case '+':
			if(*(currentChar + 1) == '+'){
				currentChar++;
				printf("inc");
				return 2;
			}
			printf("add");
			return 1;
			break;
		case '<':
			if(*(currentChar + 1) == '='){
				currentChar++;
				printf("less or equals");
				return 2;
			}else if( *(currentChar + 1) == '<'){
				currentChar++;
				printf("shift left");
				return 2;
			}
			printf("less than");
			return 1;
			break;
		case '>':
			if( *(currentChar + 1) == '='){
				currentChar++;
				printf("greater or equals");
				return 2;
			}else if( *(currentChar + 1) == '>'){
				currentChar++;
				printf("shift right");
				return 2;
			}
			printf("greater than");
			return 1;
			break;
		case '^':
			printf("bitwise exclusive or");
			return 1;
			break;
		case '|':
			printf("bitwise or");
			return 1;
			break;

		//double char opporators 
		
		case '=':
			if( *(currentChar + 1) == '='){
				currentChar++;
				printf("equals");
				return 2;
			}else{
				printf("bad token");
				return -1;
			}
			break;

		default:
			printf("bad token");
			return -1;
			break;
	}

	return 0;
}



/* ( ) [ ]  ->
function array element structure member structure pointer
UNARY OPERATORS ---------------------------------------- RIGHT TO LEFT
* & - ! ~ ++ -- sizeof ( )
indirect address minus negate 1’s comp inc dec cast
BINARY OPERATORS --------- decreasing precedence ---------- LEFT TO RIGHT
* multiply / divide % modulus
+ add - subtract
>> shift right << shift left
< less than > greater than <= less or equal >= greater or equal
== equals != not equals
& bitwise and
^ bitwise exclusive or
| bitwise or
&& logical and || logical or
CONDITIONAL EXPRESSION ---------------------------------------- RIGHT TO LEFT
Condition ? true : false
ASSIGNMENT OPERATORS ---------------------------------------- RIGHT TO LEFT
- += -= *= /= %= >>= <<= &= ^= |= see BINARY OPERATORS
COMMA OPERATOR ---------------------------------------- LEFT TO RIGHT
, discards value of left expression */


/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * Algorithm: If first token is character/letter, then we have a word always. 
 * Word, Hex, Octal, Dec, Float
 */

int hasNextToken(TokenizerT *tk){
	
	char *inputString = tk->inputString;
	if(!tk || inputString[tk->currIndex] == '\0'){//checking if the \0 has been reached.
		return 0;
	} 
	
	return 1;

}

char *TKGetNextToken( TokenizerT * tk ) {

	/*Build current token based on inputString and iterate
	  until delimiter found, new type, or end of array.
	  The BuildFunctions will take the tokenizer parameter and the newToken
	  string as arguments and finish iterating through until no more of their type is
       found.  Each new character that is still of the same type is added
       to the newToken String.*/
	
	/* These variables are useful for easier readability and so that we keep referencing
	   the TokenizerT struct instead of making local variable copies that may differ values
	   in the functions. */
	   
	   	/* For all conditions, we use the start index which is where 'currIndex''
	  left off from the last calls or 0 if it is the first call.  So we use the substring
	  startIndex through the rest of the string and assume it will be the same type
	  unless determined otherwise */
	
	char *inputString = tk->inputString;
	char *currentChar = &inputString[tk->currIndex];
	int counter = 0;
	char *startChar = currentChar;
	char *newToken = 0;
	int newTokenSize = 0;

	//interates through until reaching the end of array and/or last index

	while(isDelimiter(*currentChar)){	
		currentChar++;
		startChar++;
	}
	
	if(isalpha(*currentChar)){//check for word

		while(isalpha(*currentChar) || isdigit(*currentChar)){
			currentChar++;
		}
		printf("word");//print substring at the end to avoid unnecessary repetition 
	
	} else if( isdigit(*currentChar)){//check for hex, octal, and decimal
		
		if(*currentChar == '0'){ //check for hex or octal, the negation checks for 0 so this is equivalent to if(currentChar == 0)
			//if true, found hex value
			if( tolower(*(currentChar + 1)) == 'x') { //
			//probably need to deal with the case that nothing comes after the x. I think thats a bad token
				currentChar+=2;//goes to the char after the x;
				currentChar += buildHex(currentChar);
				
			} else { //build octal, must be octal if it wasnt hex, unless length 1
				while( (*currentChar >= '0' && *currentChar <= '7') && (*currentChar != '\0') ){//will always go to char after the first 0
					currentChar++;
				}
				if(currentChar==startChar)
					printf("decimal");/not workiing
				else  
					printf("octal");
			}
		} else{//build decimal, must be decimal 
			while(isdigit(*currentChar)){
				currentChar++;
			}
			printf("decimal");

		}
	} else {
		counter = isOp(currentChar);
		if(counter > 0)
			currentChar+=counter;	
		else
			currentChar-=counter;
	}
	
	newTokenSize = strlen(startChar) - strlen(currentChar) + 1;
	/* Update tokenizerT's currIndex for the next tokens */
	tk->currIndex = strlen(inputString) - strlen(currentChar);//accounts for the space moved

	//creates newToken by having it point to the

	newToken = malloc(sizeof(char) * newTokenSize);
	strncpy(newToken, startChar, newTokenSize - 1);
	
	/* adds '\0' to end of array */
	newToken[newTokenSize] = '\0';
	
	return newToken;

	
}

/* Keep for guidance for now

Token *createWordToken(char *string, TokenizerT *tk){
	
	Token *newToken = NULL;
	newToken = malloc(sizeof(Token));
	int currIndex = 0;
	char currChar = string[currIndex];
	
	while((isalpha(currChar) || isdigit(currChar)) && currIndex < tk->inputSize - 1){
			currIndex++;
	}
	
	newToken->string = malloc(currIndex * sizeof(char));
	strncpy(newToken->string, string, currIndex);
	newToken->tokenType = "word";
	tk->currIndex = currIndex;
	return newToken;
} */


 /* 
 main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */


/*
 Token Examples: 1234ab is 2 tokens
			  12340b  is 2 tokens

		       12340x is 2 tokens (BE GREEDY IN CURRENT TOKEN)
			  dddddN  --> decimals and numbers

			0 8 can be bad token or two numbers
			
			01234 is definitely octal

			0x213 is hex

			0129820x123 is best interpreted as decimal and a word


	JUST SHOW EVERYTHING WITH DOCUMENTATION AND MAKE ASSUMPTIONS/RULES
	BASED ON SMALL AMBIGUITIES.  "ROOM FOR INTERPRETATION"
*/
int main(int argc, char **argv) {

	/*NO ARGUMENTS, EXIT PROGRAM*/
	if(argc == 0){
		return 0;
	}	

	TokenizerT *tokenizer = TKCreate(argv[1]);

	/* Iterates loop until end of array */
	while (hasNextToken(tokenizer)){
		
		/* Get token string, the type has already been printed */
		char *newToken = TKGetNextToken(tokenizer);
		printf(" \"%s\"\n", newToken);// this puts "" around the token when we print it out like in the examples.
			
	}
	
	TKDestroy(tokenizer);

	return 0;
}	
