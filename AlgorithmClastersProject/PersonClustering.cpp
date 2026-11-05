#include "PersonClustering.h"

Person::Person(std::string name, int year, int month, int day)
	: name{ name },
    birthDate{
        std::chrono::year(year),
        std::chrono::month(month),
        std::chrono::day(day) }{}

int Person::Age() const
{
    std::chrono::year_month_day currentDate =
        std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now());
    int currentYear = static_cast<int>(currentDate.year());
    int birthYear = static_cast<int>(birthDate.year());
    return currentYear - birthYear;
}
