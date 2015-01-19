#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>


void Init()
{

}

int main()
{
	double start, end;
	start = clock();
	Init();
	Sleep(100);
	end = clock();
	printf("%.4lf\n", (end - start));
	return 0;
}
