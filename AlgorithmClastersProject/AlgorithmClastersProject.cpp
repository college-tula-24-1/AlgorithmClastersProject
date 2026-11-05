#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <functional>
#include <chrono>

#include "Grapher.h"
#include "Clusterizer.h"
//#include "PointClastering.h"
#include "PersonClustering.h"

//const int xZero = 450;
//const int xMax = 1000;
//const int yZero = 230;
//const int yMax = 500;

void CoordinateGrid(Grapher& grapher);
void CoordinateAges(Grapher& grapher);

void PointClusteringExample();

void ShowPersons(Grapher& grapher, std::vector<Person> persons);
void ShowPersonsClusters(Grapher& grapher, std::vector<std::list<Person>> clusters);

int main()
{
    //PointClusteringExample();
    Grapher grapher;

    Clusterizer<Person> clusterizer(new PersonDiffernce(), new PersonCreator());
    clusterizer.LoadObjects("persons.txt");

    CoordinateAges(grapher);
    ShowPersons(grapher, clusterizer.Objects());

    auto clusters = clusterizer.Clustering(2);
    int key = _getch();

    ShowPersonsClusters(grapher, clusters);
    key = _getch();
}

void CoordinateGrid(Grapher& grapher)
{
    grapher.Line(xZero, 0, xZero, yMax);
    grapher.Line(0, yZero, xMax, yZero);
}

void CoordinateAges(Grapher& grapher)
{
    //grapher.Line(xZero, 0, xZero, yMax);
    grapher.Line(0, yZero, xMax, yZero);

    for (int y{}; y < 7; y++)
    {
        grapher.Line(xZero + (y * 10 * oneYear), yZero + 10, xZero  + (y * 10 * oneYear), yZero - 10);
    }
}

void PointClusteringExample()
{

    //Grapher grapher;

    //Clusterizer<Point> clusterizer(new PointDiffernce(), new PointCreator());

    //clusterizer.LoadObjects("points.dat");
    //auto clusters = clusterizer.Clustering(4);

    //CoordinateGrid(grapher);

    //ShowPoints(grapher, clusterizer.Objects());
    //int key = _getch();

    //ShowClusters(grapher, clusters);
    //key = _getch();
}

void ShowPersons(Grapher& grapher, std::vector<Person> persons)
{
    grapher.SetPen(RGB(157, 204, 159), 5);

    for (auto p : persons)
    {
        grapher.Line(xZero + (p.Age() * oneYear), yZero - 20, xZero + (p.Age() * oneYear), yZero - 120);
    }
}

void ShowPersonsClusters(Grapher& grapher, std::vector<std::list<Person>> clusters)
{
    COLORREF colors[]
    { RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255),
      RGB(255, 255, 0), RGB(255, 0, 255), RGB(0, 255, 255) };

    int color{};

    for (auto cluster : clusters)
    {
        grapher.SetPen(colors[color++], 5);
        for (auto p : cluster)
            grapher.Line(xZero + (p.Age() * oneYear), yZero - 20, xZero + (p.Age() * oneYear), yZero - 120);
    }

}


