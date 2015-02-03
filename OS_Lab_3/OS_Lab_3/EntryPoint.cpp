#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;
/************************************************************************/
/*                           »сходные данные                            */
/************************************************************************/
const int	cCyl	= 500;	/*количество цилиндров */
const int	cGol	= 4;	/*количество поверхностей */
const int	cSec	= 16;	/*количество секторов */
const int	vSpeed	= 1000	/*об/мин */;
const float tJump	= .5f;	/*врем€ перехода с дорожки на соседнюю дорожку */
/************************************************************************/

vector<int> gRequest;



void init()
{

}

class HDD
{
public:
	/************************************************************************/
	/*                           /«апрос к диску/                           */
	/************************************************************************/
	virtual void Request(
		int nCyl	/*номер цилиндра*/,
		int nGol	/*номер головки*/,
		int nSec	/*номер сектора*/,
		bool oType	/*тип операции(0 - чтение, 1 - запись)*/) = 0;
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