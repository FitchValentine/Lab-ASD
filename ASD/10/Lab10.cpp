#include <iostream>
#include <vector>
#include <fstream>
#include <string>
typedef std::vector<std::vector<int>> graph;
//Код реализует поиск эйлерова цикла в графе.
int fillMatrix(graph& matrix, std::ifstream& file,int n) // Функция заполняет матрицу смежности графа на основе данных из файла.В файле предполагается, что рёбра представлены цифрами, где '0' означает отсутствие ребра, а другие цифры (1-9) представляют веса рёбер.
{
	if (file.is_open())
	{
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


int countingTops(std::ifstream& file) // Функция считает количество вершин в графе на основе первой строки файла.
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

bool hasOddDegree(graph& matrix) // Функция проверяет, имеют ли все вершины четную степень. Это важно для определения возможности существования эйлерова цикла.
{
	bool result = true;

	for (int i = 0; i < matrix.size(); i++)
	{
		int cnt = 0;

		for (int j = 0; j < matrix[i].size(); j++)
		{
			if (matrix[i][j] == 1)
			{
				cnt++;
			}
		}

		if (cnt % 2 == 1)
		{
			result = false;
		}
	}

	return result;
}


void clean(std::vector<int>& v) // Функция для обнуления значений вектора.
{
	for (auto& e : v)
	{
		e = 0;
	}
}


bool isAllUsed(std::vector<bool>& tops) // Проверяет, все ли вершины были использованы.
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


void dfs(graph& matrix, int s, int n,std::vector<bool>&used,std::vector<int>&d) // Это функция для обхода графа в глубину. Она используется для проверки наличия эйлерова цикла.
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


bool isExist(std::vector<std::pair<int, int>>& usedEdges, std::pair<int, int> edge) //  Проверяет, существует ли ребро в заданном векторе рёбер.
{
	bool result = false;

	for (auto pair : usedEdges)
	{
		if (pair == edge || (pair.first == edge.second && pair.second == edge.first))
		{
			result = true;
		}
	}

	return result;
}


void eulearDfs(graph& matrix, int s, std::vector<std::pair<int, int>>& usedEdges, std::vector<std::pair<int, int>>& distEdges) // Обычный DFS для поиска эйлерова цикла. Он записывает вершины и рёбра.
{
	for (int i = 0; i < matrix[s].size(); i++)
	{
		std::pair <int, int> edge(s, i);

		if (matrix[s][i] != 0 && !isExist(usedEdges, edge))
		{
			distEdges.push_back(edge);
			usedEdges.push_back(edge);
			eulearDfs(matrix, i, usedEdges, distEdges);
		}
	}
}


bool checkComponents(graph& matrix, int n, std::vector<bool>& used, std::vector<int>&d) // Нужно, чтобы было либо ток 1 компонента, либо 2,  но вторая не имела путей (т.е. просто вершина)
{
	std::vector<std::vector<int>> allWays;
	bool result = true;
	int cnt = 0;
	
	while (!isAllUsed(used))
	{
		for (int i = 0; i < used.size(); i++)
		{
			if (used[i] == false)
			{
				clean(d); //Заново заполняем нулями массив расстояний, тк заполяянем новую компоненту
				dfs(matrix, i, n, used, d);
				
				std::vector<int> temp; //Строим компоненты, исходя из полученный расстояний.
	
				for (int i = 0; i < d.size(); i++)
				{
					if (d[i] != 0)
					{
						temp.push_back(i);
					}
				}
	
				allWays.push_back(temp);
			}			
		}
	}

	for (auto& way : allWays)
	{
		if (way.size() != 0)
		{
			cnt++;
		}
	}

	if (cnt >1)
	{
		result = false;
	}

	return result;
}


bool checkForEulearPath(graph& matrix, int n, std::vector<bool>& used, std::vector<int>& d) // Проверяет, является ли граф эйлеровым.
{
	return checkComponents(matrix, n, used, d) && hasOddDegree(matrix);
}



void eulearLoop(graph& matrix, int n, std::vector<bool>& used, std::vector<int>& d) // Нахождение эйлерова цикла
{
	if (checkForEulearPath(matrix, n, used, d))
	{
		std::vector<std::pair<int, int>> distEdges;
		std::vector<std::pair<int, int>> usedEdges;

		eulearDfs(matrix, 0, usedEdges, distEdges);

		for (auto edge : distEdges)
		{
			std::cout << edge.first << "\t" << edge.second << std::endl;
		}
	}
	else
	{
		std::cout << "Не эйлеровый граф! Цикла не сущесвует!" << std::endl;
	}
}

void main()
{
	setlocale(LC_ALL, "rus");
	std::ifstream file;
	file.open("simplegraph.txt"); // Для демонстарции работы на НЕ эйлеровом графе, поменять название файла на doublegraph.txt рисунок для него соответсвенно graph_image
	int n = countingTops(file); //кол-во вершин в графе
	file.close();
	file.open("simplegraph.txt"); // Для демонстарции работы на НЕ эйлеровом графе, поменять название файла на doublegraph.txt рисунок для него соответсвенно graph_image
	graph matrix(n, std::vector<int>(n));
	fillMatrix(matrix, file,n);  //Заполнение матрицы смежности
	std::vector<bool> used(n);
	std::vector<int> d(n);
	eulearLoop(matrix, n, used, d);
}