#pragma once
#include <vector>
#include <algorithm>
#include <ranges>
#include <random>
#include <list>
#include <fstream>
#include <string>
#include <iostream>

struct Point
{
	int x;
	int y;
};

template <typename T>
class IDifference
{
public:
	//virtual double Difference(T one, T two) = 0;
	virtual double operator()(T one, T two) = 0;
};

template <typename T>
class ICreateObject
{
public:
	virtual T operator()(std::string stringObject) = 0;
};

template <typename T>
class Clusterizer
{
	std::vector<T> objects;
	IDifference<T>* difference;
	ICreateObject<T>* creator;

	std::string RemoveSpaces(std::string str);

	//double Distance(Point left, Point Right);
	T Centroid(std::list<T> cluster);

	int Random(int topBound);
public:

	Clusterizer(IDifference<T>* difference, ICreateObject creator)
		: difference{ difference },
		  creator{ creator } {}

	std::vector<T> Objects();

	//void LoadPoints(std::string fileName);
	void LoadObjects(std::string fileName);

	std::vector<std::list<T>> Clustering(int clustersCount);
};

template <typename T>
std::string Clusterizer<T>::RemoveSpaces(std::string str)
{
	std::string result = "";
	bool isString = false;
	for (auto sym : str)
	{
		if (sym == '"' && !isString)
			isString = true;
		if (sym == '"' && isString)
			isString = false;
		if (sym != ' ')
			result.append(1, sym);
		if (sym == ' ' && isString)
			result.append(1, sym);
	}
		
	return result;
}

template <typename T>
int Clusterizer<T>::Random(int topBound)
{
	static std::random_device device;
	static std::mt19937_64 generator;
	static std::uniform_int_distribution distr(0, topBound);

	return distr(generator);
}

template <typename T>
std::vector<T> Clusterizer<T>::Objects()
{
	return object;
}

template <typename T>
void Clusterizer<T>::LoadObjects(std::string fileName)
{
	std::ifstream objectsFile(fileName, std::ios::in);
	std::string objectLine;

	while (std::getline(objectsFile, objectLine))
	{
		objectLine = RemoveSpaces(objectLine);
		T object = creator(objectLine);
		objects.push_back(object);

		
	}
}

template <typename T>
T Clusterizer<T>::Centroid(std::list<T> cluster)
{
	double minDifferenceAll = std::numeric_limits<double>::max();
	T centroid;

	for (auto current = cluster.begin(); current != cluster.end(); current++)
	{
		double currentDifferenceAll{};
		for (auto point = cluster.begin(); point != cluster.end(); point++)
			currentDifferenceAll += difference(*current, *point);
		if (currentDifferenceAll < minDifferenceAll)
		{
			minDifferenceAll = currentDifferenceAll;
			centroid = *current;
		}
	}
	return centroid;
}


template <typename T>
std::vector<std::list<T>> Clusterizer<T>::Clustering(int clustersCount)
{
	// creating empty clusters
	std::vector<std::list<T>> clusters(clustersCount);

	// random coising clusters for points
	for (auto o = objects.begin(); o != objects.end(); o++)
		clusters[Random(clustersCount - 1)].push_back(*o);

	std::vector<T> centroids(clustersCount);

	bool isModified;

	do {
		// find centroids
		for (int cl{}; cl < clustersCount; cl++)
			centroids[cl] = Centroid(clusters[cl]);

		isModified = false;

		std::vector<std::list<T>> clustersNew(clustersCount);

		for (int cl{}; cl < clustersCount; cl++)
		{
			for (auto it = clusters[cl].begin(); it != clusters[cl].end(); it++)
			{
				double minDiffirence = std::numeric_limits<double>::max();
				int clusterNew;

				for (int cnt{}; cnt < centroids.size(); cnt++)
				{
					double currentDifference = difference(*it, centroids[cnt]);
					if (currentDifference < minDiffirence)
					{
						minDiffirence = currentDifference;
						clusterNew = cnt;
					}
				}
				if (clusterNew != cl)
					isModified = true;
				clustersNew[clusterNew].push_back(*it);
			}
		}
		clusters = clustersNew;
	} while (isModified);
	return clusters;
}