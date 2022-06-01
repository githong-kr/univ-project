%{

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
extern FILE* yyin;
extern FILE* yyout;

typedef struct _node
{
    char name[30];
    int count;
    struct _node *rLink;
} Node;

typedef struct _list
{
    Node *head;
    Node *cur;
    Node *before;
    int length;
} List;
List myList;

void Init(List *L) 
{
    L->head = (Node *)malloc(sizeof(Node));
    L->head->rLink=NULL;
    L->cur = NULL;
    L->before = NULL;
    L->length = 0;
}

void Insert(List *L, char *name)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    strcpy(new_node->name, name);
    new_node->count = 1;
    new_node->rLink = NULL;

    if(L->head->rLink == NULL)
        L->head->rLink = new_node;
    else
    {   
        L->before = L->head;
        L->cur = L->head->rLink;
        while(L->cur != NULL)
            if(strcmp(name, L->cur->name) > 0 ) 
            {
                L->before = L->cur;
                L->cur = L->cur->rLink;
            }
            else
                break;
     
        new_node->rLink = L->cur;
        L->before->rLink = new_node;
     
    }   
}
void Display(List *L) 
{
    L->cur = L->head->rLink;

    while(L->cur != NULL)
    {
        printf("%s : %d \n", L->cur->name, L->cur->count);
        L->cur = L->cur->rLink;
    }
}

int Seek(List *L, char *name)
{
    L->cur = L->head->rLink;
    while(L->cur != NULL)
    {
        if(strcmp(name, L->cur->name) == 0)
        {
            L->cur->count++;
            return 0;
        }
        L->cur = L->cur->rLink;
    }

    return 1;
}

%}


%%
[a-zA-Z]+   {   int n = strlen(yytext);
                int i;
                for(i=0; i<n; i++)
                    if(isupper(yytext[i]))
                        yytext[i] += 32;

                if(Seek(&myList, yytext))
                    Insert(&myList, yytext);
               
            }

[^a-z^A-z]* ;
`   ;
]   ;

%%


main()
{
    Init(&myList);
    yyin = fopen("the_gold_bug.txt", "r");

    yylex();

    yyout = fopen("the_gold_bug.res2", "w");

    myList.cur = myList.head->rLink;
    while(myList.cur != NULL)
    {
        fprintf(yyout, "%s : %d \n", myList.cur->name, myList.cur->count);
        myList.cur = myList.cur->rLink;
    }

    fclose(yyin);
    fclose(yyout);
}

yywrap()
{
}























