#include "PointClastering.h"

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