
#include <iostream>
#include <vector>
#include <stdexcept>
#include <time.h>
#include <assert.h>
#include <iomanip>

using namespace std;

#include "FIFO.h"
#include "SSTF.h"

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
	bool	oType	/*тип операции (0 - чтение, 1 - запись)*/;
};

/************************************************************************/
size_t			 cRequest = 10	/*количество запросов*/;
vector<sRequest> gRequest		/*массив с запросами*/;
/************************************************************************/

void main()
{
#ifdef _WIN32
	setlocale(LC_ALL, "Russian");
#endif // _WIN32
	FIFO::FIFO();
	SSTF::SSTF();

}