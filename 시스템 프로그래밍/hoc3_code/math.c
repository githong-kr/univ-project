#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


double Pow(double a, double b)
{ 
    return pow(a, b);
}

double Log(double n)
{
    return log(n);
}
double Log10(double n)
{
    return log10(n);
}
double Exp(double n)
{
    return exp(n);
}
double Sqrt(double n)
{
    return sqrt(n);
}

double integer(double n)
{
    int a = (int) n;
    double b = (double) a;
    return b;
}

double Rand(){

	static short int i=0;
    static unsigned x;
	if(i==0)
	{
		x = time(NULL);
		i++;
	}

    x ^= x>>11;
    x ^= x<<7 & 0x9D2C5680;
    x ^= x<<15 & 0xEFC60000;
    x ^= x>>18;
    return 0.000001*((x&0x7FFFFFFF)%1000000);
}




