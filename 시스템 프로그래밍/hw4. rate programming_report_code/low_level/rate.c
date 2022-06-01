#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
   int rfd, wfd, n, i;
   int cnt[26] = {0};
   int total = 0;
   double rate[26] = {0};
   char buf[10];
   char new_line[] = "%\n";
   char colon[] = " : ";
   char cur;

   rfd = open("the_gold_bug.txt", O_RDONLY);
   if(rfd == -1)
   {
       perror("Open the_gold_bug.txt");
       exit(1);
   }

   wfd = open("the_gold_bug.res1", O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0644);
   if(wfd == -1)
   {
       perror("Open the_gold_bug.res1");
       exit(1);
   }

   while((n = read(rfd, &cur, 1)) > 0)
   {
       if(isalpha(cur))
       {
           if(islower(cur))
               cnt[cur-'a']++;
           else
               cnt[cur-'A']++;
           total++;
       }
   }

   if(n == -1)
       perror("Read");

   
   for(i=0; i<26; i++)
   {
      rate[i] = ((double)cnt[i] / total) * 100;
      cur = i + 'a';
      write(wfd, &cur, 1);
      write(wfd, colon, 3);
      if(write(wfd, gcvt(rate[i], 5, buf), 5) != 5)
          perror("Write");

      write(wfd, new_line, 2);
     
   }


  close(rfd); 
  close(wfd);
   

    return 0;
}

