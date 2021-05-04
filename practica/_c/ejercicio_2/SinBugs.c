#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define Dim 6

int main()
{
	float arr[Dim];

	arr[0] = 2;
	arr[1] = 4;
	arr[2] = 6;
	arr[3] = 8;
	arr[4] = 10.1;
	arr[5] = 12;

	for(int j = 0; j < 6; ++j)
		printf("%.3g \n", arr[j]);

	return 0;
}
