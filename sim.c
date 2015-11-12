#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

//+1 spin = true
//-1 spin = false

bool randB()
{
	bool jawn;
	if (rand() % 2 ==0)
		jawn=false;
	else
		jawn=true;
	return jawn; 
}

void printArr(bool * arr, int len)
{
	int i;
	for (i=0; i<len; i++)
	{
		printf("%d", arr[i] );
		if (i!=(len-1))
			printf(",");
	}
	printf("\n");
}

void genspconf(bool * arr, int len)
{
	int i;
	for(i=0; i<len; i++)
		arr[i] = randB();
}

double calcdE(bool * arr, int index, int len, double j, double h)
{
	//dE = -J ( arr[i+1] + arr[i-1] ) ( -2arr[i] )
	int a = arr[index] ? -2:2;
	int b;
	
	//Periodic boundary
	int indexh = (index+1)%len;
	int indexl = (index-1)%len;

	if (arr[indexh] ^ arr[indexl]) //opposite sign
		b = 0;
	else if(arr[indexh]) //same sign, positive
		b=2;
	else //same sign, negative
		b=-2;

	return (j*a*b+h*a);
}


int main(int argc, char *argv[])
{
	//argv = {rows, numItr, beta, J, H}
	int rows; 
	sscanf(argv[1], "%d", &rows);
	int numItr;	//Will eventually get rid of iterating by a set number of times
	sscanf(argv[2],"%d",&numItr);
	double beta; 
	sscanf(argv[3],"%lf",&beta);
	double J; 
	sscanf(argv[4],"%lf",&J);
	double H;
	sscanf(argv[5],"%lf",&H);
	
	srand(time(NULL));
	double E = exp(1.0);
	
	bool * spconf;
	spconf = malloc(rows * sizeof(bool));

	genspconf(spconf, rows);
	printArr(spconf, rows);

	int i;
	for(i=0; i<numItr; i++)
	{
		int rindex = rand() % (rows+1);
		double deltaE = -calcdE(spconf, rindex, rows, J, H);
		
		if(deltaE <= 0)
			spconf[rindex] = !spconf[rindex];
		else
		{
			double rval = (double)rand()/(double)RAND_MAX;
			if( pow(E, -beta*deltaE) >= rval )
				spconf[rindex] = !spconf[rindex];
		}

		printArr(spconf, rows);
	}

	return 0;
}
