#include <iostream>
#include <vector>
#define MEM_SIZE 10
using namespace std;
struct mem_block;
vector<mem_block> memory;

struct mem_block
{
	bool	lock;
	void*	data;
};

void ClearMemory()
{
	for (size_t i = 0; i < memory.size(); i++)
	{
		memory[i].data = nullptr;
		memory[i].lock = false;
	}
}


void main()
{
	memory.reserve(MEM_SIZE);



}