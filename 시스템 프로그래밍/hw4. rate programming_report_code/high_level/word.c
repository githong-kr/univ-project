#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

int main()
{
    List myList;
    int n, i=0;
    char buffer[20];
    
    FILE *rfp, *wfp;

    Init(&myList);

    if((rfp = fopen("the_gold_bug.txt", "r")) == NULL)
    {
        perror("fopen : the_gold_bug.txt");
        exit(1);
    }

    if((wfp = fopen("the_gold_bug.res2", "w")) == NULL)
    {
        perror("fopen : the_gold_bug.res2");
        exit(1);
    }

    while((n = fgetc(rfp)) != EOF)
    {
        if(isalpha(n))
        {
            if(islower(n))
                buffer[i++] = n;
            else
                buffer[i++] = n+32;
        }
        else
        {
            buffer[i] = '\0';
            if(buffer[0] != '\0')
            {
                if(Seek(&myList, buffer))
                    Insert(&myList, buffer);
                i=0;
                buffer[i] = '\0';
            }
        }
    }

    myList.cur = myList.head->rLink;

    while(myList.cur != NULL)
    {
        fprintf(wfp, "%s : %d\n", myList.cur->name, myList.cur->count);
        myList.cur = myList.cur->rLink;
    }



    fclose(rfp);
    fclose(wfp);

    return 0;
}



























