#pragma once
#include "Grapher.h"
#include <vector>
#include <list>
#include "Clusterizer.h"

struct Point
{
	int x;
	int y;
};

const int xZero = 450;
const int xMax = 1000;
const int yZero = 230;
const int yMax = 500;

class PointDiffernce : public IDifference<Point>
{
public:
    double Difference(Point one, Point two) override
    {
        return sqrt(pow(one.x - two.x, 2) + pow(one.y - two.y, 2));
    }

    double operator()(Point one, Point two) override
    {
        return sqrt(pow(one.x - two.x, 2) + pow(one.y - two.y, 2));
    }
};

class PointCreator : public ICreateObject<Point>
{
public:
    Point Create(std::string stringObject) override
    {
        auto comma = stringObject.find(',');
        auto xs = stringObject.substr(0, comma);
        auto ys = stringObject.substr(comma + 1);
        Point point{ std::stoi(xs), std::stoi(ys) };
        return point;
    }

    Point operator()(std::string stringObject) override
    {
        auto comma = stringObject.find(',');
        auto xs = stringObject.substr(0, comma);
        auto ys = stringObject.substr(comma + 1);
        Point point{ std::stoi(xs), std::stoi(ys) };
        return point;
    }
};

void ShowPoints(Grapher& grapher, std::vector<Point> points);
void ShowClusters(Grapher& grapher, std::vector<std::list<Point>> clusters);
