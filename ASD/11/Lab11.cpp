#include <iostream> 
#include <string>
#include <map>
#include <fstream>

using namespace std;

struct state // ��������� ������������ ��������� ��������. � ��� �������� ����� ������� ������, ����� ������ (link) � ����������� �������� �� ��������� (��������� ���������).
{
	int len, link;
	map<char, int> next;
};


const int MAXLEN = 100000; //  ���������, ������������ ������������ ����� ������.
state st[MAXLEN * 2]; //  ������ ��������� ��������. �� ��������� sz � last ����������� � 0.
int sz, last;



void sa_init() // ������������� ��������. ������������� ��������� ��������� � ������� ������ � -1 � �������� ������.
{
	sz = last = 0;
	st[0].len = 0;
	st[0].link = -1;
	++sz;
}


void sa_extend(char c)  //���������� ������� c � �������. ��� ������� ��������� �������, �������� ����� ��������� ��� ������� ������� � �������� ������ ��� �������������.
{
	int cur = sz++;
	st[cur].len = st[last].len + 1;
	int p;
	for (p = last; p != -1 && !st[p].next.count(c); p = st[p].link)
	{
		st[p].next[c] = cur;
	}
		
	if (p == -1)
	{
		st[cur].link = 0;
	}
		
	else 
	{
		int q = st[p].next[c];
		if (st[p].len + 1 == st[q].len)
			st[cur].link = q;
		else 
		{
			int clone = sz++;
			st[clone].len = st[p].len + 1;
			st[clone].next = st[q].next;
			st[clone].link = st[q].link;
			for (; p != -1 && st[p].next[c] == q; p = st[p].link)
				st[p].next[c] = clone;
			st[q].link = st[cur].link = clone;
		}
	}

	last = cur;
}


void getData(std::string& data, std::ifstream& file) // ������� ��� ������ ������ �� ����� � ���������� �� � ������ data.
{
	if (file.is_open())
	{
		std::string line;

		while (std::getline(file, line))
		{
			data += line;
		}
	}
	else
	{
		std::cout << "File can't open!" << std::endl;
	}
}

bool find(string& text, string& pattern) // ��� ������� ��������� ����� ��������� pattern � ������ text, ��������� ����������� �������. ��� ���������� true, ���� ��������� �������, � false, ���� ���.
{
	int n = pattern.size();
	sa_init();

	for (int i = 0; i < text.size(); i++) // ������� ������ ������� ��� ����� ������ (����� ����������� ������� �������, ��  ����� ������)
	{
		sa_extend(text[i]);
	}

	int cur = 0;
	bool result = true;

	for (int i = 0; i < pattern.size(); i++) // ����� �� ������ � ���� �� ����� ������ �� �������� � ����� ���������, �� ������ �� ����������, ���� ����� �� �����, �� ��� ����
	{
		if (st[cur].next[pattern[i]])
		{
			cur = st[cur].next[pattern[i]];
		}
		else
		{
			result = false;
		}
	}

	return result;

}

void main()
{
		std::ifstream file;
	file.open("text_dm.txt");

	std::string text = "";
	getData(text, file);

	setlocale(LC_ALL, "rus");

	std::cout << "������� ������ ��� ������: ";

	std::string pattern;
	std::cin >> pattern;



	std::cout <<  find(text,pattern)<< std::endl; 

}