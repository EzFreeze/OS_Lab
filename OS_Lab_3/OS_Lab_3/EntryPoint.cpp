#include <iostream>
#include <vector>
#include <stdexcept>

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

vector<int> gRequest;



void init()
{

}

class HDD
{
public:
	/************************************************************************/
	/*                           /������ � �����/                           */
	/************************************************************************/
	virtual void Request(
		int nCyl	/*����� ��������*/,
		int nGol	/*����� �������*/,
		int nSec	/*����� �������*/,
		bool oType	/*��� ��������(0 - ������, 1 - ������)*/) = 0;
	/************************************************************************/

private:
	vector<int> pRequest;
};


class FIFO:HDD
{
public:
	virtual void Request(int nCyl, int nGol, int nSec, bool oType)
	{

	}
private:

};


void main()
{
	FIFO* pFIFO = new FIFO();

}