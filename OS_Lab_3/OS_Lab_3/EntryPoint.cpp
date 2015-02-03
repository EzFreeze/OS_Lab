#include <iostream>
#include <vector>
#include <stdexcept>
#include <time.h>
#include <assert.h>

using namespace std;
/************************************************************************/
/*                           �������� ������                            */
/************************************************************************/
const int	cCyl	= 500;	/*���������� ��������� */
const int	cGol	= 4;	/*���������� ������������ */
const int	cSec	= 16;	/*���������� �������� */
const int	vSpeed	= 1000	/*��/��� */;
const float tJump	= .5f;	/*����� �������� � ������� �� �������� ������� */
/************************************************************************/

struct sRequest
{
	int		nCyl	/*����� ��������*/;
	int		nGol	/*����� �������*/;
	int		nSec	/*����� �������*/;
	bool	oType	/*��� �������� (0 - ������, 1 - ������)*/;
};

/************************************************************************/
size_t			 cRequest = 10	/*���������� ��������*/;
vector<sRequest> gRequest		/*������ � ���������*/;
/************************************************************************/

void init()
{
	srand(clock());

	for (size_t i = 0; i < cRequest; i++)
	{
		gRequest.push_back(
		{ 
			(0 + rand() % cCyl),
			(0 + rand() % cGol),
			(0 + rand() % cSec),
			((0 + rand() % 2) ? true: false) 
		});
	}
}

void PrintRequests()
{
	cout << "/************************************************************************/" << endl;
	cout << "/*                           /������� � �����/                          */" << endl;
	cout << "/************************************************************************/" << endl;

	for (size_t i = 0; i < gRequest.size(); i++)
	{
		cout << "Cyl = " << gRequest.at(i).nCyl << "\t   Gol = " << gRequest.at(i).nGol << "\t   Sec = " << gRequest.at(i).nSec << "\t   Type = " << gRequest.at(i).oType << endl;
	}

	cout << "/************************************************************************/" << endl;
}

class HDD
{
public:
	/************************************************************************/
	/*                           /������ � �����/                           */
	/************************************************************************/
	virtual void Request(sRequest dRequest) = 0;
	/************************************************************************/
private:
	vector<int> pRequest;
};


class FIFO:HDD
{
public:	
	virtual void Request(sRequest dRequest)
	{

	}
private:

};


void main()
{
#ifdef _WIN32
	setlocale(LC_ALL, "Russian");
#endif // _WIN32

	init();
	FIFO* pFIFO = new FIFO();
	PrintRequests();
}