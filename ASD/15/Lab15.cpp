#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <string>

typedef std::vector<std::vector<int>> graph;

int fillMatrix(graph& matrix, std::ifstream& file,int n) // ��������� ������� ��������� matrix �� ����� � ������.
														//��������� graph& matrix - ������� ���������, std::ifstream& file - ���� � �������, int n - ���������� ������.
{
	if (file.is_open())
	{
		file.seekg(0); // ������ ��������� �� ������ �����.
		std::string line;
		int i = 0;

		while (std::getline(file, line)) // ��������� ������� ���������
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


int countingTops(std::ifstream& file) // ������� ���������� ������ � ����� �� �����.
									//��������� std::ifstream& file - ���� � �������.
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


bool isNear(graph& matrix, std::vector <std::pair<int,int>> &colorTops, int t, int cnt) // ���������, ���� �� ����� ������� � ������������ ������.
																						//��������� graph& matrix - ������� ���������, std::vector<std::pair<int, int>>& colorTops - ������� � �� �������, int t - ������� �������, int cnt - ������� ����.
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


bool isAllChecked(graph& matrix, std::vector <std::pair<int, int>>& powerTops) // ���������, ��� �� ����� � ����� ���� ���������.
																			//��������� graph& matrix - ������� ���������, std::vector<std::pair<int, int>>& powerTops - ������� � �� ���������.
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


int color(graph& matrix) // ������� ��������� ����� (�������� ������� ���� � ������ ����� ������ �� �������� ������
{
	std::vector<std::pair<int, int>> powerTops; //�������, �������

	for (int i = 0; i < matrix.size(); i++) // ���������� ������� ������-��������
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

	bool swapped = false; // ���������� ��������� ������ �� �� �������� (���-�� ����� ��������� �� ������)
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
	std::vector<std::pair<int, int>> colorTops; // �������, ����

	colorTops.push_back({ powerTops[0].first, cnt });

	while (!powerTops.empty()) // ���� ����� ������� ����� ������( ��� ��������  ������ � ����� �� ������), �� ������, ����� ������ ���� (�� ���� �������� ������� cnt)
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

	return cnt-1; // �������� �������, �� ����� ���������� ��������� ������������� �� 1 �������
}

void main()
{/*������� ����������� ������� ������.

������� ����������� �� �������� ��������.

���������� ������� � ������� �������� ��������. ������ ������� ������������� ����������� ��������� ����, ������� ��� �� ������������ ����� �� �������.

���� ��� ������ ������� ��� ����� ����, ��� �������� ����� ����.

����������� ��� ���� ������.

������������ �������� �����, ������������ ��������, ������������ ����� ����������� ���������� ������, ����������� ��� ���������� ��������� �����.*/
	
	std::ifstream file;
	file.open("simplegraph.txt");
	int n = countingTops(file); //���-�� ������ � �����
	graph matrix(n, std::vector<int>(n));
	fillMatrix(matrix, file,n);  //���������� ������� ���������

	std::cout << color(matrix) << std::endl; // ����� ������������� ���-�� ������ ��� ��������� �����
}