#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
//Код реализует алгоритм Дейкстры для поиска кратчайших путей от заданной вершины до всех остальных вершин во взвешенном графе.
typedef std::vector<std::vector<int>> graph;

int to_int(std::string str) // Функция, которая преобразует строку в число. Она конвертирует строку с числом (возможно, двузначным) в целочисленное значение.
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


void fillMatrix(graph& matrix, std::ifstream& file, int n) // Функция, заполняющая матрицу смежности графа на основе файла. Она считывает строки из файла, разбивает числа и заполняет соответствующие ячейки матрицы смежности.
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


int countingTops(std::ifstream& file)  // Функция, подсчитывающая количество вершин в графе. Она читает строки из файла и для каждой строки считает, что она представляет собой новую вершину.
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

bool isAllChecked(std::vector<bool> used) // Функция, которая проверяет, все ли вершины уже были обработаны (посещены).
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

void dijstra(graph& matrix, int s, std::vector<int>& d, std::vector<bool> &used) //  Основная функция, реализующая алгоритм Дейкстры для поиска кратчайших путей от заданной вершины до всех остальных.
{                                                                               // Она находит вершину с наименьшим текущим расстоянием и обновляет расстояния до соседних вершин.
	int minValue = 10000;
	int c = s; //Текущая обрабатываемая верщина
	d[s] = 0;
	
	for (int i = 0; i < d.size(); i++) // Ставим очень  большое расстояние для всех вершин (так как ищем min)
	{
		if (used[i] == false && d[i] < minValue)
		{
			c = i;
			minValue = d[i];
		}
	}

	for (int i = 0; i < matrix[c].size(); i++) //Выбираем лучший вариант для min расстояния
	{
		if (matrix[c][i] != 0 && d[i] > d[c] + matrix[c][i])
		{
			d[i] = d[c] + matrix[c][i];			
		}
	}

	used[c] = true;
}


void main() // Функция, запускающая алгоритм Дейкстры и выводящая результаты. Она открывает файл с взвешенным графом, создает матрицу смежности, запускает алгоритм Дейкстры, а затем выводит найденные кратчайшие расстояния от выбранной вершины до всех остальных вершин.
{
	std::ifstream file;
	file.open("weigthed_graph.txt");
	int n = countingTops(file);//кол-во вершин в графе
	file.close();
	file.open("weigthed_graph.txt");
	graph matrix(n, std::vector<int>(n));
	fillMatrix(matrix, file, n);
	std::vector<bool> used(n);
	std::vector<int> d(n);

	for (int i = 0; i < d.size(); i++)
	{
		d[i] = 10000;
	}
	int s = 0; //Расстояние от текущей вершины

	while (!isAllChecked(used)) // Пока не посетили все вершины
	{
		dijstra(matrix, s, d, used); //Ищем для выбранной вершины min расстояние, при желании можно  пробегаться циклом по веришнам и записывать расстояния в двумерный массив
	}

	for (auto dist : d)
	{
		std::cout << dist << std::endl;
	}
}