#include "hoc.h"
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//static Symbol *symlist = 0;  /* symbol table: linked list */

Symbol *lookup(s)	/* find s in symbol table */
	char *s;
{
	int index;

	if(islower(s[0]))
		index = s[0]-'a';
	else
		index = s[0]-'A';

	Symbol *sp = table[index];
	
	for (sp = table[index]; sp != (Symbol *) 0; sp = sp->next)
		if (strcmp(sp->name, s) == 0)
			return sp;
	return 0;	/* 0 ==> not found */	
}
Symbol *install(s, t, d)  /* install s in symbol table */
	char *s;
	int t;
	double d;
{
	int index;
	Symbol *a;

	if(islower(s[0]))
		index = s[0]-'a';
	else
		index = s[0]-'A';

	Symbol *sp;
		
	sp = (Symbol *) malloc(sizeof(Symbol));
	sp->name = malloc(strlen(s)+1); /* +1 for '\0' */
	strcpy(sp->name, s);
	sp->type = t;
	sp->u.val = d;
	sp->next = table[index]; /* put at front of list */
	table[index] = sp;

	//puts("");
	
	//for (a = table[index]; a != (Symbol *) 0; a = a->next)
	//	printf("%s ", a->name);

	//puts("");
	
	return sp;
}


 

