#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    FILE *rfp, *wfp;
    int n;
    int alpha[26] = {0};
    double total = 0;

    if((rfp = fopen("the_gold_bug.txt", "r")) == NULL)
    {
        perror("fopen : the_gold_bug.txt");
        exit(1);
    }

    if((wfp = fopen("the_gold_bug.res1", "w")) == NULL)
    {
        perror("fopen : the_gold_bug.res1");
        exit(1);
    }

    while((n = fgetc(rfp)) != EOF)
    {
        if(isalpha(n))
        {
            if(islower(n))
                alpha[n-'a']++;
            else
                alpha[n-'A']++;

            total++;
        }
    }


    for(n=0; n<26; n++)
        fprintf(wfp, "%c : %.3lf%%  \n", n+'a', ((double)alpha[n]/total)*100);


    return 0;
}

