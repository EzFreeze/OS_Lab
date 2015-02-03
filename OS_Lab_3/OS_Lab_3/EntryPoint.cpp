#include <iostream>
#include <vector>
#include <stdexcept>
#include <time.h>

using namespace std;
/************************************************************************/
/*                           Исходные данные                            */
/************************************************************************/
const int	cCyl	= 500;	/*количество цилиндров */
const int	cGol	= 4;	/*количество поверхностей */
const int	cSec	= 16;	/*количество секторов */
const int	vSpeed	= 1000	/*об/мин */;
const float tJump	= .5f;	/*время перехода с дорожки на соседнюю дорожку */
/************************************************************************/

struct sRequest
{
	int		nCyl	/*номер цилиндра*/;
	int		nGol	/*номер головки*/;
	int		nSec	/*номер сектора*/;
	bool	oType	/*тип операции(0 - чтение, 1 - запись)*/;
};

/************************************************************************/
size_t			 cRequest = 10	/*количество запросов*/;
vector<sRequest> gRequest		/*массив с запросами*/;
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
	/*                           /Запрос к диску/                           */
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