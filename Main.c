/* Syntactical specification.
Program-> stmt_list
Stmt_list-> stmt stmt_list | e
Stmt-> id :=expr | read id a | write expr| term term_tail
Expr-> term term_tail
Term_tail-> add_op term term_tail | e
Term -> factor fact_tail
Fact_tail-> mult_op fact fact_tail | e
Factor-> (expr)| id| number
Add_op -> +
Subst_op-> -
Mult_op -> *
Div_op-> /

Lexical Specification
Assign->=
Plus->+
Minus-> -
Times-> *
div->/
lparen->(
rparen->)
id-> letter (letter|digit)*
	except READ and WRITE
number-> digit digit * | digit * (.digit|digit .)digit*
digit-> 0|1|2|3|4|5|6|7|8|9

*/

//Author: Luis Alvear
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include"Scaner.h"

#include "string.h"
#include "parser.h"

void parse();

int main(int argc, char* argv[])
{
	
	/*
	A usage example:
	'READ A'
	<enter>
	Enter value: 12
	<enter>
	'READ B'
	<enter>
	Enter value: 3
	<enter>
	'B = ( 1 + A ) * 2'
	<enter>
	'COUT B'
	<enter>
	<ctrl^z>
	Total is: 26
	*/

	/*Usage menu, please read carefully*/

	printf("USAGE:\n");
	printf("-Type 'READ' followed by an identifier to input a value.\n");
	printf("-Type 'COUT' followed by the identifier to output its value.\n");
	printf("-You can assigng values with the '=' operator\n");
	printf("-Enter spaces in between numbers/identifiers and operators such as: COUT ( 2 * 3 ) + 1 and not COUT (2*3)+1\n");
	printf("-Apply the rule above also for assignment of identifiers.\n");
	printf("-The program is using getchar so enter control^z to quit program and see last output in the buffer\n\n");

	parse();

	return 0;
}

