namespace FIFO{
	size_t cRequest = 10;
	float pTime;// Время простоя
	float exTime; // Время работы
	
	std::vector<sRequest> request;
	sRequest curPost = { 1, 1, 1, 1 };

	void init(){
		srand(clock());
		for (size_t i = 0; i < cRequest; i++){
			request.push_back({
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

	void PrintVector()
	{
		for (size_t i = 0; i < request.size(); i++)
		{
			std::cout << request.at(i).nCyl << "|" << request.at(i).nGol << "|" << request.at(i).nSec << "|" << request.at(i).oType << std::endl;
		}
	}

	void FIFO(){
		init();
		try{
			while (request.size() != 0)
			{
				pTime += RandFloat(2);// время простоя
				exTime += abs(curPost.nCyl - request.back().nCyl)*tJump;//Время перехода между дорожками

				request.pop_back();//удалить элемент из массива
			}
		}
		catch (const std::out_of_range& e){
			std::cout <<"Error: "<< e.what() << std::endl;
		}
		std::cout << "Время простоя: " << pTime << std::endl;
	}
}