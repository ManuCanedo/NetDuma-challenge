#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>

struct Person
{
	std::string firstName{ "Unknown" };
	std::string otherNames{ "Mr. Smith" };
	std::string email{ "" };
	std::string telephone{ "" };
	std::map<std::string, std::string> address{};

	Person(std::string& firstName, std::string& otherNames, std::string& email, std::string& telephone, std::vector<std::string>&& address)
	{
		SetFirstName(firstName);
		SetOtherNames(otherNames);
		SetEmail(email);
		SetTelephone(telephone);
		SetAddress(address);
	}

	bool SetFirstName(const std::string& firstName)
	{
		if (ValidateName(firstName))
		{
			this->firstName = firstName;
			return true;
		}
		else
			return false;
	}

	bool SetOtherNames(const std::string& otherNames)
	{
		if (ValidateName(otherNames))
		{
			this->otherNames = otherNames;
			return true;
		}
		else
			return false;
	}

	bool SetEmail(const std::string& email)
	{
		if (ValidateEmail(email))
		{
			this->email = email;
			return true;
		}
		else
			return false;
	}

	bool SetTelephone(const std::string& telephone)
	{
		if (ValidateTelephone(telephone))
		{
			this->telephone = telephone;
			return true;
		}
		else
			return false;
	}

	// Not very scalable
	bool SetAddress(const std::vector<std::string>& address)
	{
		if (ValidateName(address[0]))
			this->address["Street"] = address[0];
		else
			return false;

		if (ValidateName(address[1]))
			this->address["Town"] = address[1];
		else
			return false;

		if (ValidateName(address[2]))
			this->address["Country"] = address[2];
		else
			return false;

		return true;
	}

	static bool ValidateName(const std::string& name)
	{
		if (false)
		{
			std::cout << "Text field - Format incorrect";
			return false;
		}
		return true;
	}

	static bool ValidateEmail(const std::string& email)
	{
		if (false)
		{
			std::cout << "Email field - Format incorrect";
			return false;
		}
		return true;
	}

	static bool ValidateTelephone(const std::string& telephone)
	{
		if (false)
		{
			std::cout << "Telephone field - Format incorrect";
			return false;
		}
		return true;
	}

	bool operator==(const Person& p) const
	{
		return firstName == p.firstName && otherNames == p.otherNames && email == p.email
			&& telephone == p.telephone && address.find("Street")->second == p.address.find("Street")->second
			&& address.find("Town")->second == p.address.find("Town")->second
			&& address.find("Country")->second == p.address.find("Country")->second;
	}

	bool operator!=(const Person& other) const
	{
		return !(*this == other);
	}

	friend std::ostream& operator<<(std::ostream& os, const Person& p)
	{
		os << "Name: " << p.firstName << ". Last Name: " << p.otherNames << ". Email: " << p.email << ". Telephone: " << p.telephone;
		//<< ". Street: " << os << p.address.find("Street")->second << ". Town: " << p.address.find("Town")->second << ". Country: " << p.address.find("Country")->second;
		return os;
	}
};
