#include <vector> 
#include <iostream>

int backpack(std::vector<std::pair<int,int>>& stuff, int W) // ������� ������, ���� �� �� ��������� ���������, ���������, ��������� ���������� ������� ��������
{                                                           // (��������� ������ dp) ��� ����� ������ ����� ������ �����
    int  n = stuff.size();
    std::vector<std::vector<int>> dp(W + 1, std::vector<int>(n + 1, 0)); //��������� ��������� ������ dp �������� (W + 1) x (n + 1), ��� n - ���������� ���������.

    for (int j = 1; j <= n; j++) //����������� �� ��������� (j �� 1 �� n), � ����� �� ��������� ����� (w �� 1 �� W).
    {
        for (int w = 1; w <= W; w++) /*��� ������� ���� � ������� �������� :
            ���� ��� �������� �������� ������ ��� ����� �������� ����(weigth <= w), �� ������� ����� �������� � ������.�� ����������, ��� �������� : �������� ������� ������� � ������ ��� �������� ������ ��� ����.
            dp[w][j] = std::max(dp[w][j - 1], dp[w - weigth][j - 1] + price), ��� price - ��������� �������� ��������.
            �����(���� ��� �������� �������� ������ ���������� ���� �������), �� ������ �������� ��� ���������.
            dp[w][j] = dp[w][j - 1].*/
        {
            int weigth = stuff[j - 1].second;
            if (weigth <= w)
            {
                int price = stuff[j - 1].first;
                dp[w][j] = std::max(dp[w][j - 1], dp[w - weigth][j - 1] + price); // ��� ������� ����� ����� ��������� - ������  ����� ����� ��������� ������ 
            }                                                                     //���� ����� ������� � ����������� ��� ��� ��� ��������� ������� ��� �� �� ������������� ���������
            else
            {
                dp[w][j] = dp[w][j - 1];
            }
        }
    }
    /*���������� �������� �� ��������� ������ dp[W][n],
        ������� ������������ ��������� ��������� - ������������ ��������� ���������, 
        ������� ����� �������� � ������ ��� ������������ ����������������.*/
    return dp[W][n];
}



void main()
{
	std::vector<std::pair<int, int>> stuff = { {1,3},{6,4}, {4,5}, {7,8}, {6,9} }; // ����� ���� ��������� (���������, ���)
	int w = 13; // ���������������� �������
	std::cout << backpack(stuff, w) << std::endl;
}