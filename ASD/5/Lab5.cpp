#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <string>
// Этот код находит сильносвязные компоненты в ориентированном графе с помощью алгоритма Косарайю. Каждая компонента связности формируется с использованием глубокого поиска в глубину (DFS).
typedef std::vector<std::vector<int>> graph; // Для удобства

int fillMatrix(graph& matrix, std::ifstream& file, int n) // : Функция заполняет матрицу смежности графа на основе данных из файла. Принимает вектор матрицы, файл и количество вершин.
{
	if (file.is_open())
	{
		file.seekg(0); // Вернул указаетль на начало файла.
		std::string line;
		int i = 0;

		while (std::getline(file, line)) // заполение матрицы смежности
		{
			int k = 0;
			for (int j = 0; j < line.size(); j++)
			{
				if (line.at(j) != '-')
				{
					matrix[i][k] = line.at(j) - 48;
					k++;
				}
				else
				{
					matrix[i][k] = -(line.at(j+1) - 48);
					j++;
					k++;
				}				
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


bool isAllUsed(std::vector<bool>& tops) // : Функция проверяет, все ли вершины графа были использованы.
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

bool isEmpty(std::vector<int>& d) //  Функция проверяет, пуст ли вектор d.
{
	bool result = true;
	for (const auto& c : d)
	{
		if (c != 0)
		{
			result = false;
		}
	}

	return  result;
}


bool isExist(std::vector<int>& d, int value) // Функция проверяет, существует ли элемент value в векторе d.
{
	int result = false;

	for (const auto& c : d)
	{
		if (c == value)
		{
			result = true;
		}
	}

	return result;
}

bool isNotInComp(std::vector<std::vector<int>>& d, int value) // Функция проверяет, не находится ли элемент value в компоненте.
{
	int result = true;

	for (int i = 0; i < d.size(); i++)
	{
		for (int j = 0; j < d[i].size(); j++)
		{
			if (d[i][j] == value)
			{
				result = false;
			}
		}
	}

	return result;
}

void dfs1(graph& matrix, int s,std::vector<bool>&used,std::vector<int>&components,std::vector<std::vector<int>>& allcomp) //  Функция реализует глубокий поиск в глубину (DFS) для поиска компонент сильной связности.
{
	used[s] = true;
	
	if (!isExist(components, s))
	{
		components.push_back(s);
	}	
	
	for (int i = 0; i < matrix[s].size(); i++)
	{
		if (matrix[s][i]==1 && used[i] == false)
		{
			dfs1(matrix, i, used, components, allcomp);	
		}
	}
}

void dfs(graph& matrix, int v, std::vector<bool>& used, std::vector<int>&order) // Функция реализует глубокий поиск в глубину (DFS) для поиска времени обработки вершины.
{
	used[v] = true;

	for (int i = 0; i < matrix[v].size(); i++)
	{
		if (matrix[v][i] == 1 && used[i] == false)
		{
			dfs(matrix, i, used,order);			
		}
	}

	if (!isExist(order, v))
	{
		order.push_back(v); //задом на перед
	}
}


int countingTops(std::ifstream& file) //  Функция подсчитывает количество вершин в графе на основе данных из файла.
{
	if (file.is_open())
	{
		std::string line;
		std::getline(file, line);
		int cnt = 0;

		for (const auto& c : line)
		{
			if (c == '0' || c == '1')
			{
				cnt++;
			}
		}

		return cnt;
	}
	else
	{
		std::cout << "Error open file!" << std::endl;
		return -1;
	}
}

void print(std::vector<int>& v)
{
	for (const auto c : v)
	{
		std::cout << c << "\t";
	}

	std::cout << "\n";
}


void clean(std::vector<bool>& v) // Функция очищает вектор, устанавливая все значения в false.
{
	for (auto e : v)
	{
		e = false;
	}
}

void reverseGraph(graph& matrix)
{
	for (int i = 0;i<matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			matrix[i][j] = -matrix[i][j];
		}
	}
}

void main()
{

	std::ifstream file;
	file.open("graph.txt");
	int n = countingTops(file); //кол-во вершин в графе
	graph matrix(n, std::vector<int>(n)); // Создание матрицы смежности размера n x n и заполнение нулями.
	fillMatrix(matrix, file, n);  //ЗЗаполнение матрицы смежности на основе данных из файла.
	graph matrix1 = matrix; // Создание копии матрицы.
	reverseGraph(matrix1); //Инвертирование графа.
	std::vector<bool> used(n); // посещенные
	std::vector<int> order; // Еще не обработали 

	std::vector<std::vector<int>> result;


	for (int i = 0; i < used.size(); i++)
	{
		if (used[i] == false)
		{
			dfs(matrix1, i, used, order); //Находим время обработки вершины в обратном графе
		}		
	}

	clean(used);

	for (int i = order.size()-1; i > 0; i--)
	{
		std::vector<int> components;

		if (used[order[i]] == false)
		{
			dfs1(matrix, order[i], used, components, result); // Проходим граф, но уже в заднном порядке с помощью dfs (вроде бы)
		}
		
		if (!components.empty())
		{
			result.push_back(components);
		}
	}
	
	for (auto &v : result)
	{
		print(v);
	}	
}