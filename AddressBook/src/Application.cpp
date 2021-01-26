#include "Application.h"

#include <vector>
#include <iostream>

bool Application::LoadData()
{
	return false;
}

void Application::DisplayMenu()
{
	int query = 0;
	std::cout << "ADDRESS BOOK\n";
	std::cout << "\n";
	std::cout << "What do you want to do?\n";
	std::cout << "1.- Add\n";
	std::cout << "2.- Remove\n";
	std::cout << "3.- Search\n";
	std::cout << "4.- Exit\n" << std::endl;

	std::cout << "Option: ";
	std::cin >> query;

	switch (query)
	{
	case 1:
		DisplayAdd();
		break;
	case 2:
		DisplayRemove();
		break;
	case 3:
		DisplayFind();
		break;
	case 4:
		std::cout << "\nOkay bye!" << std::endl;
		bExit = true;
		break;
	default:
		std::cout << "\nNot a valid option!" << std::endl;
		break;
	}
}

void Application::DisplayAdd()
{
	std::string firstName, otherNames;
	std::string email, telephone;
	std::string street, town, country;

	do
	{
		std::cin.get();
		std::cout << "Enter a name: ";
		std::getline(std::cin, firstName);
	} while (!Person::ValidateName(firstName));
	do
	{
		std::cout << "Enter last/other names: ";
		std::getline(std::cin, otherNames);
	} while (!Person::ValidateName(otherNames));
	do
	{
		std::cout << "Enter an email: ";
		std::getline(std::cin, email);
	} while (!Person::ValidateName(email));
	do
	{
		std::cout << "Enter a telephone: ";
		std::getline(std::cin, telephone);
	} while (!Person::ValidateName(telephone));
	do
	{
		std::cout << "Enter a street: ";
		std::getline(std::cin, street);
	} while (!Person::ValidateName(street));
	do
	{
		std::cout << "Enter a town: ";
		std::getline(std::cin, town);
	} while (!Person::ValidateName(town));
	do
	{
		std::cout << "Enter a country: ";
		std::getline(std::cin, country);
	} while (!Person::ValidateName(country));
	std::cout << std::endl;

	Person p{ firstName, otherNames, email, telephone, { street, town, country } };
	Add(p);
}

void Application::DisplayRemove()
{
	std::cout << std::endl;
}

void Application::DisplayFind()
{
	std::cout << std::endl;
}

bool Application::Add(const Person& p)
{
	data->push_back(p);

	name->insert({ p.firstName, &(data->back()) });
	surname->insert({ p.otherNames, &(data->back()) });
	email->insert({ p.email, &(data->back()) });
	telephone->insert({ p.telephone, &(data->back()) });
	town->insert({ p.address.find("Town")->second, &(data->back()) });
	country->insert({ p.address.find("Country")->second, &(data->back()) });

	return true;
}

bool Application::Remove(QueryType query, const std::string& value)
{
	Person* p = Find(query, value);
	data->remove(*p);

	return true;
}

Person* Application::Find(QueryType query, const std::string& value)
{
	Person* p = nullptr;

	switch (query)
	{
	case QueryType::NAME:
		return name->find(value)->second;
		break;
	case QueryType::SURNAME:
		return surname->find(value)->second;
		break;
	case QueryType::EMAIL:
		return email->find(value)->second;
		break;
	case QueryType::TELEPHONE:
		return telephone->find(value)->second;
		break;
	case QueryType::TOWN:
		return town->find(value)->second;
		break;
	case QueryType::COUNTRY:
		return country->find(value)->second;
		break;
	}

	return nullptr;
}


// ENTRY POINT
int main()
{
	Application app;
	app.Run();

	return 0;
}
