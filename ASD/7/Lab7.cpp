#include <iostream>
#include <fstream>
#include <vector>
#include <string>
// код реализует алгоритм Прима для поиска минимального остовного дерева во взвешенном графе.
typedef std::vector<std::vector<int>> graph;

int to_int(std::string str) //Функция, которая преобразует строку в число. Это используется для конвертации строковых представлений чисел (возможно, двузначных) в целочисленное значение.
{
	int result = 0;
	if (str.size() == 2)
	{
		result = (str[0] - 48) * 10 + str[1] - 48;
	}
	else if (str.size() == 1)
	{
		result = str[0] - 48;
	}

	return result;
}


void fillMatrix(graph& matrix, std::ifstream& file, int n) // Функция, которая заполняет матрицу смежности графа на основе файла. Она считывает строку из файла, разбивает числа и заполняет соответствующие ячейки матрицы смежности.
{
	if (file.is_open())
	{
		std::string line;
		int  k = 0;

		while (std::getline(file, line)) // заполение матрицы смежности
		{
			int cnt = 0;

			for (int i = 0; i < n - 1; i++)
			{
				int g = 0;

				if (line[i] == ' ')
				{
					for (int j = i + 1; j < line.size(); j++)
					{
						if (line[j] == ' ')
						{
							std::string test = line.substr(i + 1, j - i - 1);
							matrix[k][g] = to_int(line.substr(i + 1, j - i - 1));
							i = j;
							g++;
						}
					}
				}
			}

			k++;
		}
	}
	else
	{
		std::cout << "Error open file!" << std::endl;
	}
}


int countingTops(std::ifstream& file) // Функция, которая подсчитывает количество вершин в графе. Она читает строки из файла и для каждой строки считает, что она представляет собой новую вершину.
{
	int tops = 0;

	if (file.is_open())
	{
		file.seekg(0); // Вернул указаетль на начало файла.
		std::string line;

		while (std::getline(file, line))
		{
			tops++;
		}
	}
	else
	{
		std::cout << "Error open file!" << std::endl;
	}

	return tops;
}


bool isExist(std::vector<std::vector<int>> woods, int value) // Функция, которая проверяет, существует ли вершина в данном остовном дереве.
{
	bool result = false;

	for (const auto wood : woods)
	{		
		for (int i = 0; i < 2; i++)
		{
			if (wood[i] == value)
			{
				result = true;
			}
		}
	}

	return result;
}


bool isAllChecked(std::vector<bool> used) //  Функция, которая проверяет, все ли вершины были уже просмотрены.
{
	bool result = true;

	for (auto c : used)
	{
		if (c == false)
		{
			result = false;
		}
	}

	return result;
}

void prim(graph& matrix, std::vector<std::vector<int>>& woods, std::vector<int>& components, std::vector<bool> &used) //Основная функция, реализующая алгоритм Прима для поиска минимального остовного дерева.
{																					                                  //Она проходит по компонентам связности графа и находит рёбра с минимальным весом, добавляя их в остовное дерево.
	bool isCanContinue = false;
	
	int k = 0;
	int g = 0;

	for (int i = 0; i < components.size();)
	{
		int minValue = 1000000;

		for (int j = 0; j < matrix[i].size();j++)
		{
			int z = i;

			if (matrix[z][j] != 0 && matrix[z][j] < minValue && !(isExist(woods, j) && isExist(woods,z)))
			{
				minValue = matrix[z][j];
				k = z;
				g = j;
				isCanContinue = true;
			}
			if (isExist(woods, j))
			{
				used[z] = true;
				used[j] = true;
			}
		}

		if (isCanContinue)
		{
			woods.push_back({ k,g,minValue });
			isCanContinue = false;
			used[k] = true;
			used[g] = true;
			i = g;
		}
		else
		{
			i++;
		}
	}
}


void main() // Функция, запускающая алгоритм Прима и выводящая результаты. Она открывает файл с графом, создает матрицу смежности, запускает алгоритм Прима, а затем выводит найденные рёбра остовного дерева.
{
	std::ifstream file;
	file.open("graph.txt");
	int n = countingTops(file);//кол-во вершин в графе
	file.close();
	file.open("graph.txt");
	graph matrix(n, std::vector<int>(n));
	fillMatrix(matrix, file, n);
	std::vector<bool> used(n);
	std::vector<std::vector<int>> woods; //spaning woods
	std::vector<int> components = { 0,1,2,3,4,5,6,7,8,9 }; //Списко компонент связанности

	while (!isAllChecked(used)) // Пока не посетили все вершины 
	{
		for (int i = 0; i < used.size(); i++)
		{
		    prim(matrix, woods, components, used);
		}
	}

	for (int i = 0; i < woods.size(); i++)
	{
		for (int j = 0; j < woods[i].size(); j++)
		{
			std::cout << woods[i][j] << "\t";
		}

		std::cout << "\n";
	}
}