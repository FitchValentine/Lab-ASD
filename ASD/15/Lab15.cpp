#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <string>

typedef std::vector<std::vector<int>> graph;

int fillMatrix(graph& matrix, std::ifstream& file,int n) // Заполняет матрицу смежности matrix из файла с графом.
														//Принимает graph& matrix - матрица смежности, std::ifstream& file - файл с данными, int n - количество вершин.
{
	if (file.is_open())
	{
		file.seekg(0); // Вернул указаетль на начало файла.
		std::string line;
		int i = 0;

		while (std::getline(file, line)) // заполение матрицы смежности
		{
			for (int j = 0; j < n; j++)
			{
				matrix[i][j] = line.at(j) - 48;
			}

			i++;
		}
	}
	else
	{
		std::cout << "Error open file!" << std::endl;
	}

	return matrix.size();
}


int countingTops(std::ifstream& file) // Считает количество вершин в графе из файла.
									//Принимает std::ifstream& file - файл с данными.
{
	if (file.is_open())
	{
		std::string line;
		std::getline(file, line);
		return line.size();
	}
	else
	{
		std::cout << "Error open file!" << std::endl;
		return -1;
	}
}


bool isNear(graph& matrix, std::vector <std::pair<int,int>> &colorTops, int t, int cnt) // Проверяет, есть ли рядом вершина с определенным цветом.
																						//Принимает graph& matrix - матрица смежности, std::vector<std::pair<int, int>>& colorTops - вершины с их цветами, int t - текущая вершина, int cnt - текущий цвет.
{
	bool result = false;

	for (int i = 0; i < colorTops.size(); i++)
	{
		int j = colorTops[i].first;

		if (matrix[t][j] != 0  && t!=j && colorTops[i].second == cnt)
		{
			result = true;
		}
	}

	return  result;
}


bool isAllChecked(graph& matrix, std::vector <std::pair<int, int>>& powerTops) // Проверяет, все ли ребра в графе были проверены.
																			//Принимает graph& matrix - матрица смежности, std::vector<std::pair<int, int>>& powerTops - вершины с их степенями.
{
	bool result = true;

	for (int i = 0; i < powerTops.size(); i++)
	{
		for (int j = 0; j < powerTops.size(); j++)
		{
			int k = powerTops[i].first;
			int g = powerTops[j].first;

			if (matrix[k][g] != 0)
			{
				result = false;
			}
		}
	}

	return result;
}


int color(graph& matrix) // ПРоцесс раскраски графа (алгоритм который дали в лекции самый первый по степеням вершин
{
	std::vector<std::pair<int, int>> powerTops; //Веришна, степень

	for (int i = 0; i < matrix.size(); i++) // Заполнение массива вершин-степеней
	{
		int power = 0;

		for (int j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[i][j] != 0)
			{
				power++;
			}
		}

		powerTops.push_back(std::pair<int, int>(i, power));
	}

	bool swapped = false; // Соритровка пузырьком вершин по их степеням (кол-во ребер исхоядщих из вершин)
	do
	{
		swapped = false;

		for (int i = 0; i < powerTops.size() - 1; i++)
		{
			if (powerTops[i].second < powerTops[i + 1].second)
			{
				std::swap(powerTops[i], powerTops[i + 1]);
				swapped = true;
			}
		}
	} while (swapped); 

	int cnt = 1;
	std::vector<std::pair<int, int>> colorTops; // Вершина, цвет

	colorTops.push_back({ powerTops[0].first, cnt });

	while (!powerTops.empty()) // Пока можем красить одним цветом( нет соседних  вершин с таким же цветом), то красим, после меняем цвет (за цвет отвечает счетчик cnt)
	{
		std::vector<std::pair<int,int>> del;

		for (int i = 0; i < powerTops.size(); i++)
		{
			if (!isNear(matrix, colorTops, powerTops[i].first,cnt))
			{
				colorTops.push_back({ powerTops[i].first,cnt });
				del.push_back(powerTops[i]);
			}
		}


		for (int i = 0; i < del.size(); i++)
		{

			powerTops.erase(std::find(powerTops.begin(), powerTops.end(), del[i]));
		}
		
		cnt++;
	}

	return cnt-1; // Вычитаем едиинцу, тк после завершения раскраски увеличивается на 1 счетчик
}

void main()
{/*Сначала вычисляются степени вершин.

Вершины сортируются по убыванию степеней.

Проходятся вершины в порядке убывания степеней. Каждой вершине присваивается минимальный доступный цвет, который еще не используется среди ее соседей.

Если все соседи вершины уже имеют цвет, она получает новый цвет.

Повторяется для всех вершин.

Максимальное значение цвета, присвоенного вершинам, представляет собой минимальное количество цветов, необходимых для правильной раскраски графа.*/
	
	std::ifstream file;
	file.open("simplegraph.txt");
	int n = countingTops(file); //кол-во вершин в графе
	graph matrix(n, std::vector<int>(n));
	fillMatrix(matrix, file,n);  //Заполнение матрицы смежности

	std::cout << color(matrix) << std::endl; // Вывод максимального кол-ва цветов для раскраски графа
}