/*Author: Luis Alvear*/

#include<stdio.h>
#include "Scaner.h"
#include<stdlib.h>
#include<string.h>
#include"parser.h"

/*Function prototypes*/
mytype scan();
void parse();
void program();
void stmt();
void stmt_list();
int match(token);
int expr();
int term_tail(int);
int factor();
int add_op();
int mult_op();
int term();
int factor_tail(int);
int input();
void Storage(int value, char name[MAX]);

const char* arr[] = {
"COUT",
"READ",
"ID",
"ADD",
"MULT",
"SUB",
"DIVISION",
"EOF",
"LPAREN",
"RPAREN",
"ASSIGN",
"NUMBER"
};

typedef struct {
	int val;
	char name[MAX];
}myid;

//Variables that hold number and value in the sybmol table
extern myid mem[MAX];
myid mem[MAX];
static int count = 0;

//Function that throws an error and exits
void printerror(const char* str) {
	printf("%s", str);
	exit(0);
}

//FUnction that represents a sybmol table
void Storage(int value, char name[MAX])
{
	myid identifier;
	int existing;
	int i;

	if (count <= MAX)
	{
		for (int i = 0; i <= count; i++)
		{

			//Compares two variables in the memory array
			if (strcmp(name, mem[i].name) == 0)
			{
				mem[i].val = value;
			}
			else
				existing = -1;
		}

		if (existing == -1)
		{
			for (i = 0; name[i] != '\0'; i++)
			{
				identifier.name[i] = name[i];
			}
			identifier.name[i] = '\0';
			identifier.val = value;
			mem[count] = identifier;
			count++;
		}
	}
	else
	{
		perror("Exceeded max error");
	}
}

static mytype current_token;

int val = 0;

//Function to print total value
void printing(int val)
{
	printf("\nTotal: %d", val);
	printf("\n\n");
}

//Function to input values using stdin when a read token is matched
int input()
{
	int returnval;
	int myinput;

	printf("\nEnter value:");
	returnval = scanf("%d", &myinput);

	if (returnval == NULL)
	{
		printerror("Not input has been entered!");
	}
	else
		return myinput;
}

//Function that matches token and prints array
int match(token mytoken)
{

	if (current_token.type == mytoken)
	{
		printf("matched %s", arr[current_token.type]);
		printf("\n");
	}
}

/*The recursive descent parser evaluates expressions by calling the functions
based on the grammar. Check main function to see syntax evaluation*/
void parse()
{
	current_token = scan();
	program();
}

void  program()
{

	switch (current_token.type)
	{
	case id:
	case read:
	case write:
	case eof:
		printf("Calling statement_list from program\n");
		stmt_list();
		match(eof);
		printf("This is my program!:)\n");
		exit(1);
		current_token = scan();
		break;

	default:
		printerror("Error while parsing...");
	}
}

void stmt_list()
{
	switch (current_token.type)
	{
	case id:
	case read:
	case write:
		printf("Statement_list calling statement/statement_list\n");
		stmt();
		stmt_list();
		break;

	case number:
	case eof:
		return 1;

	default:
		printerror("Error while parsing...");
	}
}

void stmt()
{
	int output;
	int inputval;
	int idval;
	char temp[MAX];
	int i = 0;

	switch (current_token.type)
	{
	case id:
		match(id);

		/*Copies the values from current token into a temporary variable*/
		strncpy(temp, current_token.value.values, sizeof(temp));
		current_token = scan();
		match(assign);
		current_token = scan();
		idval = expr();

		//Calls storage function
		Storage(idval, temp);
		break;

	case read:
		match(read);
		current_token = scan();
		match(id);
		inputval = input();
		Storage(inputval, current_token.value.values);
		getchar();
		current_token = scan();
		break;

	case write:
		match(write);
		current_token = scan();
		output = expr();
		printing(output);
		break;

	default:
		printerror("Error while parsing");
	}
}

int expr()
{
	int val;
	int myresult;
	switch (current_token.type)
	{
	case id:
	case number:
	case lparen:
	{
		val = term();
		myresult = term_tail(val);
		return myresult;
	}
	break;

	default:
		printerror("Error while parsing...");
	}
}

int term_tail(int val)
{
	int x;
	int z;
	int result;
	int y;
	switch (current_token.type)
	{
	case add:
	case sub:
	{
		result = val;
		x = add_op();
		z = term();

		//If add_op returns 1 perform addition, if 2, perform substraction
		if (x == 1)
		{
			result += z;
		}
		else if (x == 2)
		{
			result -= z;
		}

		term_tail(result);
	}
	break;

	case rparen:
	case read:
	case write:
	case eof:
		return val;

	default:
		printerror("Error while parsing");
	}
}

int term()
{
	int f;
	int factort;
	switch (current_token.type)
	{
	case id:
	case number:
	case lparen:
	{
		f = factor();
		factort = factor_tail(f);
		return factort;
	}

	default:
		printerror("Error while parsing");
	}

}

int factor_tail(int val)
{
	int result;
	switch (current_token.type)
	{
	case mult:
	case division:
	{
		result = val;
		int m;
		int f;
		int x;

		m = mult_op();
		f = factor();

		//If mult op returns 2 perform multiplication
		//It it returns one return division
		if (m == 2)
		{
			result *= f;
		}
		else if (m == 1)
		{
			//Exit when division by zero
			if (f == 0)
			{
				perror("Division by zero");
				exit(0);
			}
			result /= f;
		}
		return (factor_tail(result));
	}

	case add:
	case sub:
	case rparen:
	case id:
	case read:
	case write:
	case eof:
		return val;
	default:
		printerror("Error while parsing");
	}
}

int factor()
{

	switch (current_token.type)
	{
		int result;
		int x1;

	case id:
		match(id);
		int existing;

		//Looks up in the symbol table and returns x1 in case strcmp is true
		for (int i = 0; i <= count; i++)
		{
			if (strcmp(current_token.value.values, mem[i].name) == 0)
			{
				x1 = mem[i].val;
			}
		}
		current_token = scan();
		return x1;

	case number:
		parsenum.value.num = current_token.value.num;
		val = current_token.value.num;
		match(number);
		current_token = scan();
		return val;
		break;

	case lparen:
		match(lparen);
		current_token = scan();
		result = expr();
		match(rparen);
		current_token = scan();
		return result;
		break;

	default:
		printerror("Error while parsing");
	}
}

int add_op()
{
	switch (current_token.type)
	{
	case add:
		match(add);
		current_token = scan();
		return 1;
		break;

	case sub:
		match(sub);
		current_token = scan();
		return 2;
		break;

	default:
		printerror("Error while parsing");
	}

}

int mult_op()
{
	switch (current_token.type)
	{
	case mult:
		match(mult);
		current_token = scan();
		return 2;
		break;

	case division:
		match(division);
		current_token = scan();
		return 1;
		break;

	default:
		printerror("Error while parsing");
	}
}

