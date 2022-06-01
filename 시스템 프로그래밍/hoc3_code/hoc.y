%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "hoc.h"
extern	double	Pow();

Symbol* com;

int sw;

%}

%union {
	double	val;	/* actual value */
	Symbol	*sym;	/* symbol table pointer */
}

%token	<val>	NUMBER INC DEC
%token	<sym>	VAR BLTIN UNDEF CONST
%type	<val>	expr asgn 
%right	'='
%left	'+' '-' '%'
%left	'*' '/'
%left   INC DEC
%left	UNARYMINUS UNARYPLUS '_'
%right	'^'	/* exponentiation */
%%
 list:	  /* nothing */
	| list '\n'			{ sw=0; }
	| list asgn '\n'	{ sw=0; }
	| list expr '\n'	{ 		com->u.val = $2;
								printf("\t\tans = %.8g \n", com->u.val);
								sw=0;   
						}
	| list VAR '\n'		{ if(strcmp($2->name, "ans")) printf("\t\t%s = %.8g \n", $2->name, $2->u.val);
						  else 	printf("\t\tans = %.8g \n", com->u.val);
						  sw = 0;
						}
						
	| list error '\n'	{ yyerrok; sw=0; }
	| list ';'			{ sw=1; }
	| list expr ';'		{ sw=1; }
	| list VAR ';'		{ sw=1; }
	;
asgn:	  VAR '=' expr { $$=$1->u.val=$3; $1->type = VAR; sw=0;  }
	|	  CONST '=' expr { yyerror("Can't assign a value"); { sw=0; } }
	;
expr:	  NUMBER	
	| VAR { $$ = $1->u.val;}
	| CONST { $$ = $1->u.val; }
	| asgn
	| BLTIN '(' ')'	{ $$ = (*($1->u.ptr))(); }
	| BLTIN '(' expr ')'	{ $$ = (*($1->u.ptr))($3); }
	| expr '+' expr	{ $$ = $1 + $3; }
	| expr '-' expr	{ $$ = $1 - $3; }
	| expr '*' expr	{ $$ = $1 * $3; }
	| expr '/' expr	{ if($3 == 0)
					  	yyerror("devied zero");
					  $$ = $1 / $3; }
	| INC VAR 		{ $$ = ++$2->u.val; printf("\t\t%s = %.8g", $2->name, $2->u.val); }
	| VAR INC		{ printf("\t\t%s = %.8g", $1->name, $1->u.val); $$ = $1->u.val++; }
	| DEC VAR		{ $$ = --$2->u.val; printf("\t\t%s = %.8g", $2->name, $2->u.val); }
	| VAR DEC		{ printf("\t\t%s = %.8g", $1->name, $1->u.val); $$ = $1->u.val--; }
	| expr '%' expr { int count=0; double result;
					  while(1)
					  {
                         if($1 - (int)$1 == 0 && $3 - (int)$3 == 0) { result = (int)$1 % (int)$3; break; }
						 else { $1 *= 10; $3 *= 10; count++; }
					  }
					  for(; count>0; count--) result /= 10;
					  $$ = result;
                    }
	| '_' expr {
                    int number = $2; int count=2; int i;

                    for(i=2; i*i<=number; i++)
                    {
                        if(i*i == number)
                            count++;
                        else if(number % i == 0)
                            count += 2;
                    }

                    $$ = count;
               }
	| expr '^' expr	{ $$ = Pow($1, $3); }
	| '(' expr ')'	{ $$ = $2; }
	| '-' expr  %prec UNARYMINUS  { $$ = -$2; }
	| '+' expr	%prec UNARYPLUS  { $$ = $2; }  
 
	;
%%
 /* end of grammar */


char	*progname;
int	lineno = 1;

main(argc, argv)	/* hoc3 */
	char *argv[];
{
	//int arr[10][10] = {0};
	//int i; int j; int k=10000;
	//int rnd, row, col;
	progname = argv[0];
	init();
	com = install("ans", VAR, 0.0);
	printf("\n\n\t\t\t\t \033[35mH\033[0m \033[34mO\033[0m \033[32mC\033[0m\n");
	printf("\t\t\t\t\033[36mWelcome!\033[0m\n\n");
	printf("\t\t  \033[34mVersion\033[0m \033[36m3.0\033[0m   last modified \033[32m2015-10-23\033[0m\n");
	printf("\t\t\tBuild System: \033[32mLinux Mint x64\033[0m\n");
	puts("");
	printf("\t\t\t  \033[31mCopyright(C) 2015\033[0m\n");
	printf("\t\t   All rights reserved by \033[33mStudent Hong\033[0m\n");
	printf("\t\t       For information type \"\033[35mhelp\033[0m\"\n");
	puts("");
	puts("");
/*
while(k>0)
{
	 rnd = (int)(Rand()*100);

			 row = (int)(rnd/10);
			 col = (int)(rnd%10);
			arr[row][col]++;

k--;
}		
		

	for(i=0; i<10; i++)
	{
		for(j=0; j<10; j++)
			printf("%3d ", arr[i][j]);
		puts("");
}
*/
	

	yyparse();
}

 
yylex()		/* hoc3 */
{
	int c;
	
	if(sw == 0)
	{
		printf("\033[35mH\033[0m\033[34mO\033[0m\033[32mC\033[0m -> ");
		sw = 1;
	}

	while ((c=getchar()) == ' ' || c == '\t')
		;
	if (c == EOF)
		return 0;

	if(c == '+')
	{
		int tmp = getchar();
		if(tmp == '+')
			return INC;
		else
			ungetc(tmp, stdin);
	}

	if(c == '-')
	{
		int tmp = getchar();
		if(tmp == '-')
			return DEC;
		else
			ungetc(tmp, stdin);
	}
	

	if (c == '.' || isdigit(c)) {	/* number */
		ungetc(c, stdin);
		scanf("%lf", &yylval.val);
		return NUMBER;
	}


	if (isalpha(c)) {
		Symbol *s;

		char sbuf[100], *p = sbuf;
		do {
			*p++ = c;
		} while ((c=getchar()) != EOF && isalnum(c));
		ungetc(c, stdin);
		*p = '\0';

		if(!strcmp(sbuf, "help"))
		{
			system("cat help.txt | sed 's/HELP/\033[31mHELP\033[0m/g' | sed 's/graph/\033[32mgraph\033[0m/g' | sed 's/clear/\033[33mclear\033[0m/g' | sed 's/FUN/\033[31mFUN\033[0m/g'");
			puts("");
			c=getchar();
		}

		else if(!strcmp(sbuf, "clear"))
		{
			system("clear");
			c=getchar();	
		}

		else if(!strcmp(sbuf, "graph"))
		{
			int i;
			char buf[30];

			system("clear");
			printf("If you draw 'y=x', \033[36mjust type x\033[0m\n");
			printf("In case you want to draw \033[32mtwo or more graph\033[0m, ");
			printf("type like this : \033[36mx,sin(x),cos(x)\033[0m\n\n\n");
			printf("Now you can select \033[33mhow to show\033[0m the graph\n");
			printf("1. On terminal\n");
			printf("2. On ImageMagick(\033[31mneeded to install\033[0m)\n\n");
			printf("select : ");
			scanf("%d", &i);
			
			if(i == 2)
			{
				if(system("find /usr/bin/display") != 0)
					i=1;
				else
				{
					FILE *fp = fopen("graph", "w");
					fprintf(fp, "set term pngcairo size 350,262 enhanced font \'Verdana,10\'\n");
					fprintf(fp, "set output \'graph.png\'\n");
					fprintf(fp, "set title \"");
					system("clear");
					printf("Let's draw the \033[33mgraph\033[0m! \n\n");
					scanf("%s", buf);
					fprintf(fp, "%s\"\n", buf);
					fprintf(fp, "set xlab \"input\"\nset ylab \"output\"\n");
					fprintf(fp, "set key out vert right top\n");
					fprintf(fp, "plot %s", buf);
					fclose(fp);
					system("gnuplot graph");
					system("display graph.png");
					system("clear");
				
				}
			}
			
			else if(i == 1)
			{
				FILE *fp = fopen("graph_default", "w");
				fprintf(fp, "set term dumb\nplot ");
				system("clear");
				printf("Let's draw the \033[33mgraph\033[0m! \n\n");
				scanf("%s", buf);
				fprintf(fp, "%s", buf);
				fclose(fp);
				if(system("gnuplot graph_default") != 0)
					printf("Please \033[31minstall\033[0m gnuplot\n");
				else
				{
					printf("you can display the \033[33mbetter graph\033[0m by installing");
					printf(" imagemagick \n");				
				}
				
			}
			
			else
			{
				printf("\nPlease select one of above list\n\n");
				
			}

			c=getchar();
		}

		else
		{
			if ((s=lookup(sbuf)) == 0)
				s = install(sbuf, UNDEF, 0.0);
			yylval.sym = s;
			if(s->type == UNDEF)
				return VAR;
			else if(s->type == CONST)
				return CONST;
			else
				return s->type;
		}
	}

	if (c == '\n')
		lineno++;
	return c;
}
 yyerror(s)
	char *s;
{
	warning(s, (char *)0);
}

warning(s, t)
	char *s, *t;
{
	fprintf(stderr, "%s: %s", progname, s);
	if (t && *t)
		fprintf(stderr, " %s", t);
	fprintf(stderr, " near line %d\n", lineno);

	
}


