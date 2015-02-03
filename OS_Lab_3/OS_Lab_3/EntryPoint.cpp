#include <iostream>
#include <vector>
#include <stdexcept>
#include <time.h>

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
	bool	oType	/*��� ��������(0 - ������, 1 - ������)*/;
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
		gRequest.push_back({1,1,1,1});
	}
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
		for (size_t i = 0; i < gRequest.size(); i++)
		{
			cout << "Cyl = " << gRequest.at(i).nCyl << " Gol = " << gRequest.at(i).nGol << " Sec = " << gRequest.at(i).nSec << " Type = " << gRequest.at(i).oType << endl;
		}
	}
private:

};


void main()
{
	init();
	FIFO* pFIFO = new FIFO();
	pFIFO->Request({ 1, 1, 1, 1 });
}