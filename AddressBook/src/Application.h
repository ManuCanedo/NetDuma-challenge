#pragma once

#include "DataEntry.h"

#include <memory>
#include <list>
#include <unordered_map>

enum class QueryType
{
	NAME, SURNAME, EMAIL, TELEPHONE, TOWN, COUNTRY
};

class Application
{
	using QueryMap = typename std::unordered_multimap<std::string, Person*>;

public:
	Application()
		: data(std::make_unique<std::list<Person>>()), 
		name(std::make_unique<QueryMap>()), surname(std::make_unique<QueryMap>()), email(std::make_unique<QueryMap>()), 
		telephone(std::make_unique<QueryMap>()), town(std::make_unique<QueryMap>()), country(std::make_unique<QueryMap>())
	{
		LoadData();
	}

	~Application() = default;

	void Run()
	{
		while (!bExit)
			DisplayMenu();
	}

private:
	void DisplayMenu();
	void DisplayAdd();
	void DisplayRemove();
	void DisplayFind();

	bool Add(const Person& p);
	bool Remove(QueryType query, const std::string& value);
	Person* Find(QueryType query, const std::string& value);

private:
	static bool LoadData();

private:
	bool bExit{ false };
	std::unique_ptr<std::list<Person>> data{ std::make_unique<std::list<Person>>() };

	// Concerned about memory
	std::unique_ptr<QueryMap> name{ std::make_unique<QueryMap>() };
	std::unique_ptr<QueryMap> surname{ std::make_unique<QueryMap>() };
	std::unique_ptr<QueryMap> email{ std::make_unique<QueryMap>() };
	std::unique_ptr<QueryMap> telephone{ std::make_unique<QueryMap>() };
	std::unique_ptr<QueryMap> town{ std::make_unique<QueryMap>() };
	std::unique_ptr<QueryMap> country{ std::make_unique<QueryMap>() };
};

