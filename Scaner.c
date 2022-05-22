/*Author: Luis Alvear*/

#include <stdio.h>
#include "stdlib.h"
#include <ctype.h>
#include"Scaner.h"
#include "string.h"

mytype parsenum;

mytype scan()
{
	
	char tokenlen[max]; //Holds the token length
	int i = 0;
	static int c; //Holds the characters
	c = getchar();

	if (c == EOF)
	{
		//Return EOF
		mytype parseeof;
		parseeof.type = eof;
		return parseeof; 
	}

	/*If input is an alphanumeric character it will loop 
	until there is no more entries.  */
	if (isalpha(c))
	{
		do
		{
			tokenlen[i] = c;
			i++;

			if (i >= max)
			{
				printf("You exceeded token length");
				exit(0);
			}
			c = getchar();
		} while (isalpha(c) || isdigit(c));
		tokenlen[i] = '\0';

		if (!strcmp(tokenlen, "READ"))
		{
			//Return read
			mytype parseread;
			parseread.type = read;
			return parseread;
		}
		else if (!strcmp(tokenlen, "COUT"))
		{
			//Return write
			mytype parsewrite;
			parsewrite.type = write;
			return parsewrite;
		}
		else
		{
			//Return identifier
			mytype parseid;
			parseid.type = id;

			for (int i = 0; i < max; i++)
			{
				parseid.value.values[i] = tokenlen[i];
			}
			return parseid;
		}
	}

	else if (isdigit(c))
	{
		/*If input is a digit it will loop and convert
		each digit into a type, to be returned*/
		int x = 0;
		i = 0;
		do {
			tokenlen[i] = c;
			parsenum.value.values[i] = tokenlen[i];
			i++;
			c = getchar();

		} while (isdigit(c));

		tokenlen[i] = '\0';
		parsenum.value.values[i] = '\0';

		parsenum.value.num = atoi(parsenum.value.values);
		parsenum.type = number;
		return parsenum;

	}

	/*Returning operators*/
	else if (c == '*')
	{
		
		mytype parsemult;
		c = getchar();
		parsemult.type = mult;
		return parsemult;
	}
	else if (c == '/')
	{
		mytype parsedivision;
		c = getchar();
		parsedivision.type = division;
		return parsedivision;
	}
	else if (c == '-')
	{
		mytype parsesub;
		c = getchar();
		parsesub.type = sub;
		return parsesub;
	}
	else if (c == '+')
	{
		mytype parseadd;
		c = getchar();
		parseadd.type = add;
		return parseadd;
	}
	else if (c == '(')
	{
		mytype parselparen;
		c = getchar();
		parselparen.type = lparen;
		return parselparen;
	}
	else if (c == ')')
	{
		mytype parserparen;
		c = getchar();
		parserparen.type = rparen;
		return parserparen;
	}
	else if (c == '=')
	{
		mytype parseassign;
		c = getchar();
		parseassign.type = assign;
		return parseassign;
	}

	else
		printf("This is my program!!");

	//exit(0);

}



