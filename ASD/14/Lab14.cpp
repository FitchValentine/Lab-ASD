#include <iostream>
#include <fstream>
#include <string>
#include<vector>

// Код реализует алгоритм Рабина-Карпа для поиска всех вхождений подстроки (шаблона) в строке (тексте). 
int hash(std::string& pattern, std::string& substr, int& prevHash, char prevSymbol) // Эта функция вычисляет хеш подстроки pattern или пересчитывает хеш при добавлении нового символа в substr.
																					//Используется формула Рабина - Карпа для вычисления хеша.
{
	int n = pattern.size();
	int b = 101; //const
	int h = 0;

	if (substr == "")
	{
		prevHash = 0;

		for (int i = 0; i < n; i++)
		{
			int c = pattern[i];
			h += c * pow(b,  n- i - 1);
		}

		prevHash = h;
	}
	else
	{
		h = (prevHash - prevSymbol * pow(b, n - 1)) * b + pattern[n - 1]; // Формула пересчета хеша для новой строки и ее сохарнение для дальнейшего поиска
		prevHash = h;
	}

	return h;
}

bool check(std::string& substr, std::string& pattern) //Проверяет, совпадает ли подстрока substr с образцом pattern.
{
	bool result = true;

	for (int i = 0; i < pattern.size(); i++)
	{
		if (pattern[i] != substr[i])
		{
			result = false;
		}
	}

	return result;
}

int rab_carp(std::string& text,std::string &pattern) // Это основная функция, реализующая алгоритм Рабина-Карпа для поиска подстроки pattern в тексте text.
													//Проходит по всем подстрокам текста длины pattern.size() и сравнивает их хеши с хешем pattern.
													//Если хеши совпадают, выполняется дополнительная проверка посимвольно.
{
	int count = 0;
	int n = pattern.size();
	int prevHash = 0;
	std::string substr = "";

	int h = hash(pattern,substr,prevHash,text[0]);
	prevHash = 0;


	for (int i = 0; i < text.size()-n; i++)
	{
		char s = text[0];
		std::string temp = text.substr(i, n);
		std::string help = "";		

		if (i != 0)
		{
			s = text[i - 1];
			help = "1";			
		}	

		if (hash(temp,help,prevHash,s) == h) // Если совпадают хеши, то уже сравниваем посимвольно
		{
			if (check(temp, pattern))
			{
				count++;
			}
		}
	}

	return count;
}

void getData(std::string& data, std::ifstream& file) // Читает данные из файла в строку
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

void main()
{
	std::ifstream file;
	file.open("text_dm.txt");

	std::string text = "";
	getData(text, file);

	setlocale(LC_ALL, "rus");

	std::cout << "Введите строку для поиска: ";

	std::string pattern;
	std::cin >> pattern;


	std::cout << rab_carp(text, pattern) << std::endl; //Выведение кол-во вхождений
}