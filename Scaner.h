
/*Author: Luis Alvear*/

#ifndef _SCANNER_H_
#define _SCANER_H_
#define max 30
extern char tokenlen[max];

//Token types
typedef enum {
	write,
	read,
	id,
	add,
	mult,
	sub,
	division,
	eof,
	lparen,
	rparen,
	assign,
	number
}token;

//Struct that holds values and nums for tokens
typedef struct
{
	token type;
	union
	{
		char values[100];
		int num;
	}value;


}mytype;

extern mytype parsenum;
extern mytype scan();

#endif 