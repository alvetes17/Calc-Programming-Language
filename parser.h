//Author: Luis Alvear

#define MAX 30

//Function prototypes
extern mytype scan();
extern void parse();
extern void program();
extern void stmt();
extern void stmt_list();
extern int match(token);
extern int expr();
extern int term_tail(int);
extern int factor();
extern int add_op();
extern int mult_op();
extern int term();
extern int factor_tail(int);
extern int input();
extern void Storage(int value, char name[MAX]);
