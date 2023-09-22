#include <iostream>
#include <vector>
#include<algorithm>
typedef std::pair<int, int> point; //Здесь определен псевдоним типа point для пары целочисленных значений (x, y), представляющих координаты точек.


void sort(std::vector<point>& surface) // Пузырьковая Соритровка всех точек по x и y
{
	bool swapped = false;

	do
	{
		swapped = false;

		for (int i = 0; i < surface.size() - 1; i++)
		{
			if (surface[i].first > surface[i + 1].first)
			{
				std::swap(surface[i], surface[i + 1]);
				swapped = true;
			}
			else if (surface[i].first == surface[i + 1].first)
			{
				if (surface[i].second > surface[i + 1].second)
				{
					std::swap(surface[i], surface[i + 1]);
					swapped = true;
				}
			}
		}
	} while (swapped);
}


bool isLeftAngle(point& last, point& current, point& next) // Является ли угол между тремя точками "левым". Это используется для построения выпуклой оболочки.
{
	return ((current.first - last.first) * (next.second - current.second) - 
		(current.second - last.second) * (next.first - current.first)) >= 0;
}

std::vector<point> build(std::vector<point>& surface) //Главная функция для построения выпуклой оболочки. Сначала точки сортируются, затем создается пустой вектор для оболочки (hull). Затем происходит построение нижней и верхней части оболочки, а затем точки объединяются в один вектор, представляя выпуклую оболочку.
{	
	sort(surface);
	point left = surface.front();
	point right = surface.back();

	std::vector <point> hull = {left};
	int cnt = 0;
	for (int i = 1; surface[i]!=right; i++)
	{
		if (surface[i].second < right.second || surface[i].second < left.second) // Построение нижней части
		{
			hull.push_back(surface[i]);
			cnt++;

			while (hull.size() >= 3 && !isLeftAngle(hull[cnt - 2], hull[cnt - 1], hull[cnt]))
			{
				hull.erase(hull.end() - 2);
				cnt--;
			}				
		}		
	}

	for (int j = surface.size()-1; surface[j] != left; j--)
	{
		if (surface[j].second >= right.second || surface[j].second >= left.second) // Построение верхней части
		{
			hull.push_back(surface[j]);
			cnt++;

			while (hull.size() >= 3 && !isLeftAngle(hull[cnt - 2], hull[cnt - 1], hull[cnt]))
			{
				hull.erase(hull.end() - 2);
				cnt--;
			}
		}
	}

	if(hull.size() >= 3 && !isLeftAngle(hull[cnt - 1], hull[cnt], left)) // Исключение первой точки,  которая берется дважды
	{
		hull.erase(hull.end() - 1);
		cnt--;
	}
	
	return hull;
}


void main()    // Это точка входа в программу. Создается вектор surface, представляющий исходные точки. Затем производятся тестовые данные, и вызывается функция build для построения оболочки. Результат выводится на консоль.
{
	std::vector<point> surface = { {-3,-3}, {-3,-1}, {-3,2}, {-1,1}, {-1,4}, {3,4}, {2,2}, {5,3}, {4,1}, {1,-1}, {2,-2} };
	surface.clear();
	surface.push_back({0, 0}); //Тест №1
	surface.push_back({ 0, 100 });
	surface.push_back({ 100, 0 });
	surface.push_back({ 1, 1 });
	surface.push_back({ 0, 5 });
	surface.push_back({ 0, 10 });
	surface.push_back({ 10, 0 });
	surface.push_back({ 99, 99 });

	/*surface.push_back({ 0, 0 });  Тест №2
	surface.push_back({ 0, 100 });
	surface.push_back({ 100, 0 });
	surface.push_back({ 1, 1 });
	surface.push_back({ 0, 5 });
	surface.push_back({ 0, 10 });
	surface.push_back({ 25, 25 });
	surface.push_back({ 30, 15 });
	surface.push_back({ 15, 40 });
	surface.push_back({ 10, 0 });*/


	auto result = build(surface);

	for (const auto& point : result)
	{
		std::cout << point.first << "\t" << point.second << std::endl;
	}
}