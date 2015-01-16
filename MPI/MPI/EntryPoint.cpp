#include <iostream>
#include <mpi.h>

#ifdef _WIN32
#pragma comment(lib,"msmpi.lib")
#endif

using namespace std;


double inline fact(int n)
{
	if (n == 0)
		return 1;
	else
		return n*fact(n - 1);
}



int main(int argc, char *argv[])
{
#ifdef _WIN32
	setlocale(LC_ALL, "Russian");
#endif
	int num		/*Количество*/,
		id		/*Номер*/;
	double 
		s_time	/*Начало работы*/, 
		d_time	/*Разность начала и конца работы программы*/;

	if (int rc = MPI_Init(&argc, &argv))
	{
		cout << "Ошибка запуска, выполнение остановлено " << endl;
		MPI_Abort(MPI_COMM_WORLD, rc);
	}

	MPI_Comm_size(MPI_COMM_WORLD, &num);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	/*=============================================================*/

	/*=============================================================*/
	if (id == 0)
	{
		s_time = MPI_Wtime();
	}

	
	if (id == 0)
	{
		d_time = MPI_Wtime() - s_time;
		cout << "TIME: "<<d_time * 1000 << endl;
	}

	MPI_Finalize();
	return 0;
}