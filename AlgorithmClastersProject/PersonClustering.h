#pragma once

#include <vector>
#include <list>
#include <chrono>
#include <string>

#include "Clusterizer.h"
#include "Grapher.h"

const int xZero = 100;
const int xMax = 1000;
const int yZero = 420;
const int yMax = 500;

const int oneYear = 10;

class Person
{
	std::string name;
	std::chrono::year_month_day birthDate;
public:
	Person(std::string name, int year, int month, int day);
	Person() {};

	int Age() const;
};

class PersonDiffernce : public IDifference<Person>
{
public:
	double Difference(Person one, Person two) override
	{
		return abs(one.Age() - two.Age());
	}
	double operator()(Person one, Person two) override
	{
		return abs(one.Age() - two.Age());
	}
};

class PersonCreator : public ICreateObject<Person>
{
public:
	Person Create(std::string stringObject) override
	{
		auto commaOne = stringObject.find(',');
		auto name = stringObject.substr(0, commaOne);

		auto commaTwo = stringObject.find(',', commaOne + 1);
		auto year = stoi(stringObject.substr(commaOne + 1, commaTwo - commaOne - 1));

		commaOne = commaTwo;
		commaTwo = stringObject.find(',', commaOne + 1);
		auto month = stoi(stringObject.substr(commaOne + 1, commaTwo - commaOne - 1));

		auto day = stoi(stringObject.substr(commaTwo + 1));

		return Person(name, year, month, day);
	}

	Person operator()(std::string stringObject) override
	{
		auto commaOne = stringObject.find(',');
		auto name = stringObject.substr(0, commaOne);

		auto commaTwo = stringObject.find(',', commaOne + 1);
		auto year = stoi(stringObject.substr(commaOne + 1, commaTwo - commaOne - 1));

		commaOne = commaTwo;
		commaTwo = stringObject.find(',', commaOne + 1);
		auto month = stoi(stringObject.substr(commaOne + 1, commaTwo - commaOne - 1));

		auto day = stoi(stringObject.substr(commaTwo + 1));

		return Person(name, year, month, day);
	}
};