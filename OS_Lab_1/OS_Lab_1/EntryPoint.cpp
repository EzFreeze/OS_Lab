#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <cmath>

#ifdef _WIN32

#define STATUS __int32
#define clear system("cls");

#else
#include <stdlib.h>
#define STATUS int
#define clear system("clear");

#endif // _WIN32

#define MEM_SIZE	10
#define BLOCK_SIZE	1024
using namespace std;

STATUS error = 0;
/*
Error Code List 
0 - Успешно
1 - Нет пустых блоков
2 - Недостаточно памяти
3 - Неверный индекс блока
*/

struct mem_block
{
	bool	bLock;
	int		iChild_id;
	int		iParent_id;
};

void InitMemory(vector<mem_block> &memory)
{
	mem_block temp_block = { false, -1, -1};
	for (size_t i = 0; i < MEM_SIZE; i++)
	{
		memory.push_back(temp_block);
	}
}

void ClearMemory(vector<mem_block> &memory)
{
	for (size_t i = 0; i < memory.size(); i++)
	{
		memory[i].bLock		= false;
		memory[i].iChild_id	= -1;
		memory[i].iParent_id = -1;
	}
}

void PrintMemory(vector<mem_block> memory)
{
	for (size_t i = 0; i < memory.size(); i++)
	{
		cout<< " ID: "<< setw(3) <<(i + 1)
			<< " Lock: " << setw(5) << ((memory[i].bLock) ? "true" : "false")<<endl;
	}
	cout << "\nSTATUS: " << error << endl;
}

int GetBlockCountForAlloc(int Size)
{
	int i = 0;
	while (Size > 0)
	{
		i += 1;
		Size -= BLOCK_SIZE;
	}
	return i;
}

int GetFreeBlockCount(vector<mem_block> &memory)
{
	int iOut = 0;
	for (size_t i = 0; i < MEM_SIZE; i++)
	{
		if (memory[i].bLock == false)
		{
			iOut += 1;
		}
	}
	return iOut;
}

void AllocMemory(int iSize, vector<mem_block> &memory)
{
	if (iSize > BLOCK_SIZE)
	{
		if (GetFreeBlockCount(memory) >= GetBlockCountForAlloc(iSize))
		{
			vector<int> blocks;
			int i = 0;
			while (blocks.size() != GetBlockCountForAlloc(iSize))
			{
				if (memory[i].bLock == false){
					blocks.push_back(i);
				}
				i++; 
			}
			for (size_t i = 0; i < blocks.size(); i++)
			{
				if (i == (blocks.size()-1))
				{
					memory[blocks[i]].bLock = true;
					memory[blocks[i]].iParent_id = blocks[i - 1];
					break;
				}
				memory[blocks[i]].bLock = true;
				memory[blocks[i]].iChild_id = blocks[i + 1];
				if (i != 0)
					memory[blocks[i]].iParent_id = blocks[i - 1];
			}
		}
		else
		{error = 2;}
	}
	else
	{
		for (size_t i = 0; i < MEM_SIZE; i++)
		{
			if (memory[i].bLock == false)
			{
				memory[i].bLock = true;
				error = 0;
				return;
			}
		}
		error = 1;
	}
}

void FreeMemory(size_t Index, vector<mem_block> &memory)
{
	if (Index > 0 && Index < memory.size())
	{

		if ((memory[Index-1].iChild_id == -1) && (memory[Index-1].iParent_id == -1))
		{
			memory[Index - 1].bLock = false;
			return;
		}

		if (memory[Index-1].iParent_id == -1)
		{
			Index--;
			vector<int> chield_list;
			chield_list.push_back(Index);
			while (memory[Index].iChild_id != -1)
			{
				Index = memory[Index].iChild_id;
				chield_list.push_back(Index);
			}

			for (size_t i = 0; i < chield_list.size(); i++)
			{
				memory[chield_list[i]].bLock = false;
				memory[chield_list[i]].iChild_id = -1;
				memory[chield_list[i]].iParent_id = -1;
			}
		}

		if (memory[Index-1].iParent_id != -1)
		{
			Index--;
		}

	}
	else
	{
		error = 3;
	}
}

int main()
{
	vector<mem_block> memory;
	InitMemory(memory);
	string sBuffer;

	while (true)
	{
		//clear
		//PrintMemory(memory);
		cout << "\ncommand>";
		cin >> sBuffer;

		if (sBuffer.find("alloc") != -1)
		{
			cout << "size>";
			cin >> sBuffer;
			AllocMemory(atoi(sBuffer.c_str()),memory);
		}
		else if (sBuffer.find("free") != -1)
		{
			cout << "index>";
			cin >> sBuffer;
			FreeMemory(atoi(sBuffer.c_str()), memory);
		}
		else if (sBuffer.find("clear") != -1)
		{
			ClearMemory(memory);
		}
		else if (sBuffer.find("show") != -1)
		{
			PrintMemory(memory);
		}
	}
	return 1;
}