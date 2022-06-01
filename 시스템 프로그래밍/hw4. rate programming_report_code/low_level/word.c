#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
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
    int rfd, wfd, n, i=0;
    char cur, buf[20];
    char colon[] = " : ";
    char new_line = '\n';
    
    Init(&myList);

    rfd = open("the_gold_bug.txt", O_RDONLY);
    if(rfd == -1)
    {
        perror("Open the_gold_bug.txt");
        exit(1);
    }

    wfd = open("text.res2", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if(wfd == -1)
    {
        perror("Open text.res2");
        exit(1);
    }


    while((n = read(rfd, &cur, 1)) > 0)
    {
        if(isalpha(cur))
        {
            if(isupper(cur))
                cur += 32;

            buf[i] = cur;
            i++;
            
        }
        else
        {
            buf[i] = '\0';
            if(buf[0] != '\0')
                if(Seek(&myList, buf))
                    Insert(&myList, buf);
            i=0;
            buf[i] = '\0';
        }
    }

    myList.cur = myList.head;

    while(myList.cur != NULL)
    {
        int i=0;
        int j=0;
        int k=0;
        char rate[5];

        write(wfd, myList.cur->name, strlen(myList.cur->name));
        write(wfd, colon, 3);
        
        n = myList.cur->count;
        
        while(n != 0)
        {
            buf[i] = n%10 + 48;
            n /= 10;
            i++;
        }
        for(j=i-1; j>=0; j--)
            rate[j] = buf[k++];
        rate[i] = '\0';
        
        write(wfd, rate, i);

        write(wfd, &new_line, 1);

        myList.cur = myList.cur->rLink;
    }
  
    close(rfd);   
    close(wfd);

    return 0;
}



























