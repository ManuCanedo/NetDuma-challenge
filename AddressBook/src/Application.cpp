#include "Application.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>


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
	std::cin.get();

	do
	{
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
	} while (!Person::ValidateEmail(email));
	do
	{
		std::cout << "Enter a telephone: ";
		std::getline(std::cin, telephone);
	} while (!Person::ValidateTelephone(telephone));
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
	int query = 0;
	std::string keyword;

	std::cout << "\n";
	std::cin.get();
	std::cout << "Enter the keyword: \n";
	std::getline(std::cin, keyword);

	std::cout << "\n";
	std::cout << "What search do you want to perform?\n\n";
	std::cout << "1.- Name\n";
	std::cout << "2.- Last Name\n";
	std::cout << "3.- Email\n";
	std::cout << "4.- Telephone\n";
	std::cout << "5.- Town\n";
	std::cout << "6.- Country\n";
	std::cout << "7.- Back to Menu\n" << std::endl;

	std::cout << "Option: ";
	std::cin >> query;

	Person* p = nullptr;

	switch (query)
	{
	case 1:
		p = Find(QueryType::NAME, keyword);
		break;
	case 2:
		p = Find(QueryType::SURNAME, keyword);
		break;
	case 3:
		p = Find(QueryType::EMAIL, keyword);
		break;
	case 4:
		p = Find(QueryType::TELEPHONE, keyword);
		break;
	case 5:
		p = Find(QueryType::TOWN, keyword);
		break;
	case 6:
		p = Find(QueryType::COUNTRY, keyword);
		break;
	case 7:
		return;
	default:
		std::cout << "\nNot a valid option!" << std::endl;
		break;
	}

	if (p != nullptr)
	{
		Remove(*p);
		std::cout << "Person has been removed!\n" << std::endl;
	}
	else
		std::cout << "Person has not been found!\n" << std::endl;
}

void Application::DisplayFind()
{
	int query = 0;
	std::string keyword;

	std::cin.get();
	std::cout << "Enter the keyword: \n";
	std::getline(std::cin, keyword);

	std::cout << "\n";
	std::cout << "What search do you want to perform?\n\n";
	std::cout << "1.- Name\n";
	std::cout << "2.- Last Name\n";
	std::cout << "3.- Email\n";
	std::cout << "4.- Telephone\n";
	std::cout << "5.- Town\n";
	std::cout << "6.- Country\n";
	std::cout << "7.- Back to Menu\n" << std::endl;

	std::cout << "Option: ";
	std::cin >> query;

	Person* p = nullptr;

	switch (query)
	{
	case 1:
		p = Find(QueryType::NAME, keyword);
		break;
	case 2:
		p = Find(QueryType::SURNAME, keyword);
		break;
	case 3:
		p = Find(QueryType::EMAIL, keyword);
		break;
	case 4:
		p = Find(QueryType::TELEPHONE, keyword);
		break;
	case 5:
		p = Find(QueryType::TOWN, keyword);
		break;
	case 6:
		p = Find(QueryType::COUNTRY, keyword);
		break;
	case 7:
		return;
	default:
		std::cout << "\nNot a valid option!" << std::endl;
		break;
	}

	if (p != nullptr)
		std::cout << "Person has been found!\n" << std::endl;
	else
		std::cout << "Person has not been found!\n" << std::endl;
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

bool Application::Remove(const Person& p)
{
	name->erase(p.firstName);
	surname->erase(p.otherNames);
	email->erase(p.email);
	telephone->erase(p.telephone);
	town->erase(p.address.find("Town")->second);
	country->erase(p.address.find("Country")->second);
	data->remove(p);

	return true;
}

Person* Application::Find(QueryType query, const std::string& value)
{
	Person* p = nullptr;
	QueryMap::iterator it;

	switch (query)
	{
	case QueryType::NAME:
		it = name->find(value);
		if (it != name->end())
			p = it->second;
		break;
	case QueryType::SURNAME:
		it = surname->find(value);
		if (it != surname->end())
			p = it->second;
		break;
	case QueryType::EMAIL:
		it = email->find(value);
		if (it != email->end())
			p = it->second;
		break;
	case QueryType::TELEPHONE:
		it = telephone->find(value);
		if (it != telephone->end())
			p = it->second;
		break;
	case QueryType::TOWN:
		it = town->find(value);
		if (it != town->end())
			p = it->second;
		break;
	case QueryType::COUNTRY:
		auto it = country->find(value);
		if (it != country->end())
			p = it->second;
		break;
	}

	return p;
}

void Application::LoadData()
{
	std::string line;
	std::ifstream myfile("save.txt");
	std::vector<std::string> fields(7);

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			std::stringstream ss(line);
			for (auto& f : fields)
				std::getline(ss, f, '*');
			Add({ fields[0], fields[1] , fields[2], fields[3], {fields[4],fields[5],fields[6]} });
		}
		myfile.close();
	}
	else 
		std::cout << "Unable to open file";
}

void Application::SaveData()
{
	std::ofstream file("save.txt");
	std::copy(data->begin(), data->end(), std::ostream_iterator<Person>(file, "\n"));
}

// ENTRY POINT
int main()
{
	Application app;
	app.Run();

	return 0;
}
