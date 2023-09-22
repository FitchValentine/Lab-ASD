#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
//  ��� ��������� �������� ��������-����� ��� ������ ���������� ����� �� ������ ������� �� ���� ��������� ������ �� ���������� �����. 
typedef std::vector<std::vector<int>> graph;

int to_int(std::string str) // ������� �������� ������ � ������ � ������������� ��������.
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


void fillMatrix(graph& matrix, std::ifstream& file, int n) //  ������� ��� ���������� ������� ��������� ����� �� ������ �����.
{
	if (file.is_open())
	{
		std::string line;
		int  k = 0;

		while (std::getline(file, line)) // ��������� ������� ���������
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


int countingTops(std::ifstream& file) // ������� ��� �������� ���������� ������ � �����, ���������� �� ����� ����� � �����.
{
	int tops = 0;

	if (file.is_open())
	{
		file.seekg(0); // ������ ��������� �� ������ �����.
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


std::vector<int> BF(graph& matrix, int s) // ������������� ����� ��� ���������� �������  ( � ������� ���������) � ��� �� �����  ������� ��� ����������
{									     // ����� ���������� ������� � �������� ����� (�����  ��) xd
	std::vector<int> ways(matrix.size(),10000);

	ways[s] = 0;

	for (int k = 0; k < matrix.size(); k++)
	{
		for (int i = 0; i < matrix.size(); ++i)
		{
			for (int j = 0; j < matrix[i].size(); ++j)
			{
				if (matrix[i][j] != 0)
				{
					if (ways[j] > ways[i] + matrix[i][j])
					{
						ways[j] = ways[i] + matrix[i][j];
					}
				}
			}
		}
	}
	

	return ways;
}

void main() // �������� �������, ������� ������ ���������� ���� �� �����, �������� ������� BF ��� ������ �������, ����� ������� ���������� ���� �� ������ ������� �� ���� ���������.
{
	std::ifstream file;
	file.open("weigthed_graph.txt");
	int n = countingTops(file);//���-�� ������ � �����
	file.close();
	file.open("weigthed_graph.txt");
	graph matrix(n, std::vector<int>(n));
	fillMatrix(matrix, file, n);

	std::vector<std::vector<int>> allWays;

	for (int i = 0; i < matrix.size(); i++)
	{
		std::vector<int> ways = BF(matrix, i); // ��� ������ ������� ����������� �������� ��������-����� ��� ���������� ���������� ����� �� ��� �� ���� ��������� ������.
		allWays.push_back(ways);
	}

	for (auto way : allWays)
	{
		for (auto w : way)
		{
			std::cout << w << "\t";
		}

		std::cout << "\n";
	}


}