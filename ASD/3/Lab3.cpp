#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <string>

//Этот код ищет все компоненты связности в графе и выводит вершины каждой компоненты. Каждая компонента связности формируется с использованием обхода в ширину (BFS).
typedef std::vector<std::vector<int>> graph; //  Определение псевдонима типа graph для двумерного вектора std::vector<std::vector<int>>, который представляет матрицу смежности графа.

int fillMatrix(graph& matrix, std::ifstream& file, int n) // Функция заполняет матрицу смежности графа на основе данных из файла. Принимает вектор матрицы, файл и количество вершин.
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

std::vector<int> bfs(graph& matrix, int s, int n,std::vector<bool>& used) // Функция реализует обход в ширину (BFS) в графе, начиная с вершины s. Принимает матрицу смежности, вершину начала обхода, количество вершин и вектор, отмечающий использованные вершины.
{
	std::queue<int> q;
	std::vector<int> d(n);
	d[s] = 0;
	q.push(s);
	used[s] = true;

	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		for (int i = 0; i < matrix[v].size(); i++)
		{
			auto test = matrix[v][i];
			auto test1 = used[i];
			if (matrix[v][i] != 0 && used[i] == false)
			{
				d[i] = d[v] + 1;
				used[i] = true;
				q.push(i);
			}
		}
	}

	std::vector<int> result;
	result.push_back(s);

	for (int i = 0; i < d.size(); i++)
	{
		if (d[i] != 0)
		{
			result.push_back(i);
		}
	}

	return result;
}


int countingTops(std::ifstream& file) // Кол-во вершин
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

bool isAllUsed(std::vector<bool>& tops)
{
	bool result = true;

	for (const auto t : tops)
	{
		if (t == false)
		{
			result = false;
		}
	}

	return result;
}

void print(std::vector<int> v)
{
	for (const auto c : v)
	{
		std::cout << c << "\t";
	}

	std::cout << "\n";
}

void main()
{

	std::ifstream file;
	file.open("doublegraph.txt");
	int n = countingTops(file); //кол-во вершин в графе
	graph matrix(n, std::vector<int>(n));
	fillMatrix(matrix, file, n);  //Заполнение матрицы смежности
	std::vector<bool>used(n);
	std::vector<std::vector<int>> allWays;

	while (!isAllUsed(used)) //Делаем bfs, пока все вершины не будут просмотрены (закончился  1 bfs = 1 компонента)
	{
		for (int i = 0; i < used.size(); i++) // Перебор всех вершин графа.
		{
			if (used[i] == false)
			{
				allWays.push_back(bfs(matrix, i, n,used));
			}
		}
	}

	for (const auto& arr : allWays) // Цикл для вывода компонент связности.
	{
		print(arr);
	}
}