
#include <iostream>
#include <vector>
#include <stdexcept>
#include <time.h>
#include <assert.h>
#include <iomanip>
#include <fstream>

#define deff(a,b)				abs(a-b)
#define check_time(a,b)			if(a > b) break;
/************************************************************************/
/*                           Исходные данные                            */
/************************************************************************/
const int cCyl		= 500;/*количество цилиндров */
const int cGol		= 4;/*количество поверхностей */
const int cSec		= 16;/*количество секторов */
const float vSpeed	= 1000.0f/60.0f	/*об/сек */;
const float tJump	= .5f;/*время перехода с дорожки на соседнюю дорожку */
/************************************************************************/
const int cReq		= 100000;/*общее количество запросов*/
const int tMax		= 3600;
/************************************************************************/



struct sRequest{
	int		nCyl	/*номер цилиндра*/;
	int		nGol	/*номер головки*/;
	int		nSec	/*номер сектора*/;
	bool	oType	/*тип операции (0 - чтение, 1 - запись)*/;
};

std::vector<sRequest> ReqList /*список запросов*/;
std::fstream GisLog;


void InitReqList()
{
	for (size_t i = 0; i < cReq; i++){
		ReqList.push_back({
			(0 + rand() % cCyl),
			(0 + rand() % cGol),
			(0 + rand() % cSec),
			((rand() % 2) ? true : false) 
		});
	}
}

float RandFloat(float max){
	return ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * max);
}

void PrintResult(float minTime, float maxTime, float avrTime, 
	float avrTime2, int max_leght, float eTime)
{
	std::cout
		<< "Минимальное время обслуживания: " << minTime << std::endl
		<< "Максимальное время обслуживания: " << maxTime << std::endl
		<< "Среднее	время обслуживания: " << avrTime << std::endl
		<< "Среднеквадратическое отклонение от среднего: " << avrTime2 << std::endl
		<< "Количество обработанных запросов: " << max_leght << std::endl
		<< "Время простоя: " << eTime << std::endl;
}



void FIFO(){
	std::cout << " - FIFO - " << std::endl;
	std::vector<sRequest>	FIFO_ReqList	= ReqList;
	std::vector<float>		ExTimeArray;
	sRequest				CurPos = { 1, 1, 1, 1 };
	float					exTime = .0f;
	float					gExTime = .0f;
	float					eTime = .0f;
	/************************************************************************/

	while (FIFO_ReqList.size()){
		exTime = (deff(CurPos.nCyl, FIFO_ReqList.back().nCyl)*tJump) / 1000; /*Время выполнения запроса (в секундах)*/
		CurPos = FIFO_ReqList.back();
		eTime += RandFloat(0.02f);
		
		if (FIFO_ReqList.back().oType == 1)
		{ exTime += (1/vSpeed)*2;} 
		else
		{ exTime += (1/vSpeed);}

		GisLog.open(L"FIFO.log", std::ios_base::app);
		GisLog << exTime << std::endl;
		GisLog.close();

		gExTime += exTime + eTime;
		ExTimeArray.push_back(exTime);
		check_time(gExTime, tMax);
		FIFO_ReqList.pop_back();
	}

	/************************************************************************/
	/*                      Среднее время выполнения                        */
	/************************************************************************/
	float t = .0f; /*Среднее время выполнений запроса*/
	for (size_t i = 0; i < ExTimeArray.size(); i++){
		t += ExTimeArray.at(i);
	}
	t /= ExTimeArray.size();

	/************************************************************************/
	/*                      Среднеквадратическое отклонение                 */
	/************************************************************************/
	float t2 = .0f;/*Среднеквадратическое отклонение*/
	for (size_t i = 0; i < ExTimeArray.size(); i++){
		t2 += pow((ExTimeArray.at(i) - t), 2);
	}
	t2 = sqrt(t2 / ExTimeArray.size());

	/************************************************************************/
	/*                       Минимальное время выполнения                   */
	/************************************************************************/

	float min = ExTimeArray.at(0);
	for (size_t i = 0; i < ExTimeArray.size(); i++){
		if (min > ExTimeArray.at(i)){
			min = ExTimeArray.at(i);
		}
	}

	/************************************************************************/
	/*                       Максимальное время выполнения                  */
	/************************************************************************/

	float max = ExTimeArray.at(0);
	for (size_t i = 0; i < ExTimeArray.size(); i++){
		if (max < ExTimeArray.at(i)){
			max = ExTimeArray.at(i);
		}
	}

	PrintResult(min, max, t, t2, ExTimeArray.size(), eTime);
}


void SSTF()
{
	std::cout << " - SSTF - " << std::endl;
	std::vector<sRequest>	SSTF_ReqList = ReqList;
	std::vector<float>		ExTimeArray;
	sRequest				CurPos = { 1, 1, 1, 1 };
	float					exTime = .0f;
	float					gExTime = .0f;
	float					eTime = .0f;
	/************************************************************************/

	while (SSTF_ReqList.size()){
		int temp = cCyl;
		size_t index; 
		for (size_t i = 0; i < SSTF_ReqList.size(); i++){
			if (deff(CurPos.nCyl,SSTF_ReqList.at(i).nCyl) < temp){
				temp = deff(CurPos.nCyl, SSTF_ReqList.at(i).nCyl);
				index = i;}}
		eTime += RandFloat(0.02f);
		exTime = (deff(CurPos.nCyl, SSTF_ReqList.at(index).nCyl)*tJump) / 1000;
		CurPos = SSTF_ReqList.at(index);
		
		if (SSTF_ReqList.at(index).oType == 1)
		{exTime += (1 / vSpeed) * 2;}
		else
		{exTime += (1 / vSpeed);}
		
		GisLog.open(L"SSTF.log", std::ios_base::app);
		GisLog << exTime << std::endl;
		GisLog.close();

		gExTime += exTime + eTime;
		ExTimeArray.push_back(exTime);

		check_time(gExTime, tMax);

		SSTF_ReqList.erase(SSTF_ReqList.begin() + index);
	}

	/************************************************************************/
	/*                      Среднее время выполнения                        */
	/************************************************************************/
	float t = .0f; /*Среднее время выполнений запроса*/
	for (size_t i = 0; i < ExTimeArray.size(); i++){
		t += ExTimeArray.at(i);
	}
	t /= ExTimeArray.size();

	/************************************************************************/
	/*                      Среднеквадратическое отклонение                 */
	/************************************************************************/
	float t2 = .0f;/*Среднеквадратическое отклонение*/
	for (size_t i = 0; i < ExTimeArray.size(); i++){
		t2 += pow((ExTimeArray.at(i) - t), 2);
	}
	t2 = sqrt(t2 / ExTimeArray.size());

	/************************************************************************/
	/*                       Минимальное время выполнения                   */
	/************************************************************************/

	float min = ExTimeArray.at(0);
	for (size_t i = 0; i < ExTimeArray.size(); i++){
		if (min > ExTimeArray.at(i)){
			min = ExTimeArray.at(i);
		}
	}

	/************************************************************************/
	/*                       Максимальное время выполнения                  */
	/************************************************************************/

	float max = ExTimeArray.at(0);
	for (size_t i = 0; i < ExTimeArray.size(); i++){
		if (max < ExTimeArray.at(i)){
			max = ExTimeArray.at(i);
		}
	}
	PrintResult(min, max, t, t2, ExTimeArray.size() , eTime);
}

void main(){
#ifdef _WIN32
	setlocale(LC_ALL, "Russian");
#endif // _WIN32
	InitReqList();
	FIFO();
	SSTF();
}