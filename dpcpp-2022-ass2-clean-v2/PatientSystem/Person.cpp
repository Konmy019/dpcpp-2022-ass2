#include "Person.h"

Person::Person() 
{ }

Person::Person(const std::string& firstName, const std::string& lastName, std::tm birthday) :
	_firstName(firstName),
	_lastName(lastName),
	_birthday(birthday)
{
}
