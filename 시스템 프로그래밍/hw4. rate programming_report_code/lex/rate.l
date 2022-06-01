%{
    int alpha[26];
    extern FILE* yyin;
    extern FILE* yyout;
%}



%%
[a-z]   {alpha[yytext[0]-'a']++;} 
[A-Z]   {alpha[yytext[0]-'A']++;}
[^a-z^A-Z]   ;

%%

main()
{
    int i, sum=0;
    double rate[26];
    yyin = fopen("the_gold_bug.txt", "r");
    yylex();
    for(i=0; i<26; i++)
        sum += alpha[i];

    for(i=0; i<26; i++)
    {
        rate[i] = (double)alpha[i]/(double)sum;
        printf("%c : %.3lf \n", i+'a', rate[i]*100);
    }
    yyout = fopen("the_gold_bug.res1", "w");
    for(i=0; i<26; i++)
        fprintf(yyout, "%c : %.3lf%% \n", i+'a', rate[i]*100);

    fclose(yyin);
    fclose(yyout);
}

yywrap()
{
}
