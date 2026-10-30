#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "Grapher.h"
#include "Clusterizer.h"

const int xZero = 450;
const int xMax = 1000;
const int yZero = 230;
const int yMax = 500;


void CoordinateGrid(Grapher& grapher);
void ShowPoints(Grapher& grapher, std::vector<Point> points);
void ShowClusters(Grapher& grapher, std::vector<std::list<Point>> clusters);

int main()
{
    Grapher grapher;
    Clusterizer<Point> clusterizer(
        [](Point left, Point right) 
        {
            return sqrt(pow(left.x - right.x, 2) + pow(left.y - right.y, 2))
        },
        [](std::string str) 
        {
            auto comma = str.find(',');
            auto xs = str.substr(0, comma);
            auto ys = str.substr(comma + 1);
            Point point{ std::stoi(xs), std::stoi(ys) };
            return point;
        });

    clusterizer.LoadPoints("points.dat");
    auto clusters = clusterizer.Clustering(4);

    CoordinateGrid(grapher);

    ShowPoints(grapher, clusterizer.Points());
    int key = _getch();

    ShowClusters(grapher, clusters);
    key = _getch();
    
}

void CoordinateGrid(Grapher& grapher)
{
    grapher.Line(xZero, 0, xZero, yMax);
    grapher.Line(0, yZero, xMax, yZero);
}

void ShowPoints(Grapher& grapher, std::vector<Point> points)
{
    grapher.SetPen(RGB(255, 255, 255));
    for (auto point : points)
        grapher.Circle(point.x + xZero, point.y + yZero, 3);    
}

void ShowClusters(Grapher& grapher, std::vector<std::list<Point>> clusters)
{
    COLORREF colors[]
    { RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255),
      RGB(255, 255, 0), RGB(255, 0, 255), RGB(0, 255, 255) };

    int color{};

    for (auto cluster : clusters)
    {
        grapher.SetPen(colors[color++]);
        for (auto point : cluster)
            grapher.Circle(point.x + xZero, point.y + yZero, 3);
    }

}
