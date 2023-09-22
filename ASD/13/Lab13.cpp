#include <iostream>
#include <vector>
#include <string>
#include <fstream>
// Этот код использует алгоритм Бойера-Мура для эффективного поиска подстроки в строке. Путем оптимизированного сдвига паттерна по тексту он находит первое вхождение паттерна и выводит индекс, 
//с которого начинается найденная подстрока. Если подстрока не найдена, выводится -1.

void getData(std::string& data, std::ifstream& file) /* Эта функция служит для чтения данных из файла и сохранения их в строку data.
Она принимает ссылку на строку data и объект ifstream, представляющий файл.
Если файл открывается успешно, она читает строки из файла и добавляет их в строку data.
Если файл не удалось открыть, выводит сообщение об ошибке. */
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

int inTable(std::vector<std::pair<char, int>>& table, char c)//Эта функция предположительно создает какую - то таблицу.
                                                             //Принимает вектор пар table(представляющий таблицу) и символ c.
															//Проверяет, есть ли символ c в таблице.Если есть, возвращает его позицию, иначе - 1.
{
	int result = -1;

	for (int i = 0 ;i < table.size();i++)
	{
		if (c == table[i].first)
		{
			result = i;
		}
	}

	return result;
}

int BM(std::string & text, std::string & pattern)	//Это функция, реализующая алгоритм Бойера - Мура для поиска подстроки pattern в строке text.
													//Алгоритм Бойера - Мура использует таблицу смещений для эффективного поиска.
													//Она возвращает индекс начала найденной подстроки в строке text или - 1, если подстрока не найдена.
{
	int result = -1;
	std::vector<std::pair<char, int>> table;

	for (int i = pattern.size() - 2; i >= 0; i--)
	{
		if (inTable(table, pattern[i])==-1)
		{
			table.push_back({ pattern[i], pattern.size() - i - 1 });
		}
	}

	if (!inTable(table, pattern[0]))
	{
		table.push_back({ pattern[0],pattern.size() - 1 });
	}

	int i = pattern.size() - 1;

	while (i < text.size())
	{
		int k = 0; 

		int j = pattern.size() - 1;
		for (; j != 0; --j)
		{
			int off = 0;

			if (text[i - k] != pattern[j])
			{
				if (j == pattern.size() - 1)
				{
					int d = inTable(table, text[i]);
					off = d != -1 ? table[d].second : pattern.size();
				}
				else
				{
					int pos = inTable(table, pattern[j]);
					off = table[pos].second;
				}

				i += off;
				break;
			}

			k++;
		}

		if (j == 0)
		{
			result = i - k + 1;
			break;
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

	std::cout << "Введите строку для поиска: ";

	std::string pattern;
	std::cin >> pattern;

	std::cout<<BM(text, pattern)<<std::endl; // введи строку в начале и посчитай, какой индекс дают, с какого начинается или выводит просто кол-во, я забыл
}

