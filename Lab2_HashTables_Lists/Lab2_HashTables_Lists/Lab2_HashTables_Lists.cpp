#include <iostream>
using namespace std;


class SList
{
public:
	class Item
	{
	public:
		Item* next;
		char* line;
		Item(const char* string) // создание заданной строки
		{
			int i, length = strlen(string);
			line = new char[length + 1];
			for (i = 0; i < length; i++) line[i] = string[i];
			line[i] = '\0';
			next = nullptr;
		}
		Item(int length) // создание случайной строки по заданной длине
		{
			int i;
			line = new char[length + 1];
			for (i = 0; i < length; i++) line[i] = rand() % 26 + 0x61;
			line[i] = '\0';
			next = nullptr;
		}
		void PrintLine()
		{
			cout << " ";
			for (int i = 0; line[i] != '\0'; i++) cout << line[i];
		}
		~Item()
		{
			delete[] line;
		}
	};
	Item* begin;
	SList()
	{
		begin = nullptr;
	}
	~SList()
	{
		Item* p;
		while (begin != nullptr)
		{
			p = begin; begin = begin->next;
			delete p;
		}
	}
	void RandList(int g) // создание случайного списка по заданному количеству элементов
	{
		int length = 0;
		while (g != 0) // g - количество элементов в списке
		{
			length = (rand() % 20 + 2); // количество элементов в строке списка
			Item* p, * current = new Item(length);
			if (!begin) begin = current;
			else
			{
				for (p = begin; p->next; )
					p = p->next;
				p->next = current;
			}
			g--;
		}
	}
	void PushBack(const char* string) // добавление заданной строки
	{
		Item* p, * current = new Item(string);
		if (!begin) begin = current;
		else
		{
			for (p = begin; p->next; )
				p = p->next;
			p->next = current;
		}
	}
	void PrintList(int i)
	{	
		Item* p = begin;
		if (p == nullptr) ;
		else
		{
			cout << "\n LIST #" << i << ":";
			while (p != nullptr)
			{
				p->PrintLine();
				p = p->next;
			}
		}
	}
	bool Check(const char* string, int& unique, int& comparisons) // проверка на вхождение заданной строки в список
	{
		bool result = false;
		Item* p = begin;
		while ((p != nullptr) && (result != true))
		{
			result = (strcmp(string, p->line) != 0) ? false : true;
			p = p->next;
			comparisons++;
		}
		if (!result) unique++;
		return result;
	}
	void JoinList(SList& list) // присоединение заданного списка
	{
		if (!list.begin) return;
		if (!begin) begin = list.begin;
		else
		{
			Item* p = begin;
			while (p->next != nullptr) p = p->next;
			p->next = list.begin;
		}
		list.begin = nullptr;
	}
};
class HashTable
{
	SList* Table;
	int q = 0;
public:
	HashTable(int N)
	{
		int Simple[] = { 1009, 10007, 20011, 30011, 40009, 50021, 60013, 70001, 80021, 90001, 100003 };
		for (int i = 0; i < (sizeof(Simple) / sizeof(Simple[0])); i++)
		{
			if (N <= Simple[i])
			{
				q = Simple[i];
				break;
			}
		}
		Table = new SList[q];
	}
	~HashTable()
	{
		delete[] Table;
	}
	int Hash(const char* str) // вычисление значения хеш-функции
	{
		int Y, length = strlen(str);
		Y = str[0];
		for (int i = 1; i < length; i++)
		{
			Y = (Y * 31 + str[i]) % q;
		}
		return Y;
		/*for (int i = 1; i <= length; i++)
		{
			Y = (Y % q * 31) + str[i];
		}
		Y = Y % q;
		return Y;*/
	}
	void AddString(const char* str, int& unique, int& comparisons) // добавление УНИКАЛЬНОЙ строки в хеш-таблицу
	{
		int y = Hash(str);
		if (!Table[y].Check(str, unique, comparisons)) Table[y].PushBack(str);
	}
	void JoinAllLists(SList& Common) // слияние всех списков хеш-балицы в заданный список
	{
		for (int i = 0; i < q; i++) Common.JoinList(Table[i]);
	}
	void PrintTable()
	{
		int t = q;
		int i = 0;
		for (; t != 0; t--)
		{
			Table[i].PrintList(i);
			i++;
		}
	}
};
int main()
{
	//N - количество строк (N<=100.000)
	//G - количество символов в строке
    //q - количество списков (1.000<=q<=100.000)
	srand(time(NULL));
	int N = 0, G = 0, Q = 0; 
	cout << "\n Strings: "; cin >> N;
	cout << "\n Characters: "; cin >> G;

	char** Mass = new char* [N];
	for (int i = 0; i < N; ++i) 
	{
		Mass[i] = new char[G+1];
		int g = 0;
		for (; g < G; g++) Mass[i][g] = rand() % 26 + 0x61;
		Mass[i][g] = '\0';
	}

	HashTable table(N);
	int unique = 0, comparisons = 0;

	for (int i = 0; i < N; i++)
	{
		table.AddString(Mass[i], unique, comparisons);
	}

	SList list;
	table.JoinAllLists(list);

	cout << "\n\n Unique: " << unique << endl;
	cout << "\n Comparisons: " << comparisons << endl;
	
	for (int i = 0; i < N; ++i) delete[] Mass[i];
	delete[] Mass;
}
