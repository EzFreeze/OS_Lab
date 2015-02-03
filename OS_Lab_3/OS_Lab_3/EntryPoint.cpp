#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

vector<int> gRequest;

void init()
{

}

class FIFO
{
public:
	FIFO(vector<int> iRequest)
	{
		pRequest = iRequest;
	}

	//
	void PrintResult()
	{
		for (size_t i = 0; i < pRequest.size(); i++)
		{
			cout << pRequest.at(i) << endl;
		}
	}

protected:

private:
	vector<int> pRequest;
};

void main()
{

	FIFO* pFIFO = new FIFO(gRequest);
	pFIFO->PrintResult();

}