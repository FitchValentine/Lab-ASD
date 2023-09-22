#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <string>
//Этот код находит все компоненты связности в графе и выводит вершины каждой компоненты. Каждая компонента связности формируется с использованием глубокого поиска в глубину (DFS).
typedef std::vector<std::vector<int>> graph; // Для удобства

int fillMatrix(graph& matrix, std::ifstream& file, int n) //Функция заполняет матрицу смежности графа на основе данных из файла. Принимает вектор матрицы, файл и количество вершин.
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


bool isAllUsed(std::vector<bool>& tops) //Функция проверяет, все ли вершины графа были использованы.
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


void dfs(graph& matrix, int s, int n,std::vector<bool>&used,std::vector<int>&d) // : Функция реализует глубокий поиск в глубину (DFS) для поиска компонент связности.
{
	if (d.empty())
	{
		d[s]++;
		used[s] = true;
	}

	for (int i = 0; i < matrix[s].size(); i++)
	{
		if (matrix[s][i]!=0 && used[i] == false)
		{
			d[i] = d[s] + 1;
			used[i] = true;
			dfs(matrix, i, n,used,d);
		}
	}
}


int countingTops(std::ifstream& file) // Функция подсчитывает количество вершин в графе на основе данных из файла.
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

void print(std::vector<int> v)
{
	for (const auto c : v)
	{
		std::cout << c << "\t";
	}

	std::cout << "\n";
}


void clean(std::vector<int>& v)
{
	for (auto& e : v)
	{
		e = 0;
	}
}


void main()
{

	std::ifstream file;
	file.open("doublegraph.txt");
	int n = countingTops(file); //кол-во вершин в графе
	graph matrix(n, std::vector<int>(n)); //  Создание матрицы смежности размера n x n и заполнение нулями.
	fillMatrix(matrix, file, n);  //Заполнение матрицы смежности
	std::vector<bool> used(n); // Создание вектора, отмечающего использованные вершины.
	std::vector<int> d(n);

	std::vector<std::vector<int>> allWays;

	while (!isAllUsed(used)) // : Цикл, выполняющийся до тех пор, пока все вершины не будут просмотрены.
	{
		for (int i = 0; i < used.size(); i++)
		{
			if (used[i] == false)
			{
				clean(d); //Заново заполняем нулями массив расстояний, тк заполнянем новую компоненту
				dfs(matrix, i, n, used, d);
				
				std::vector<int> temp; //Строим компоненты, исходя из полученный расстояний.

				for (int i = 0; i < d.size(); i++)
				{
					if (d[i] != 0)
					{
						temp.push_back(i);
					}
				}

				allWays.push_back(temp); // Все компоненты
			}			
		}
	}
	
	for (const auto& v : allWays) // Цикл для вывода компонент связности.
	{
		print(v);
	}
	
}