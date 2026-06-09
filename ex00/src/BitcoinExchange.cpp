/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 13:55:47 by mchemari          #+#    #+#             */
/*   Updated: 2026/06/09 03:53:12 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cctype>

BitcoinExchange::BitcoinExchange()
{
	std::ifstream file("data.csv");
	std::string	str;
	char *endptr;
	std::string date;
	float value;

	if (!file.is_open())
	{
		std::cout << "Error: file not open." << std::endl;
		return;
	}
	std::getline(file, str);
	while (std::getline(file, str))
	{
		size_t pos = str.find(',');
		if (pos != std::string::npos)
		{
			date = str.substr(0, pos);
			value = static_cast<float>(std::strtod((str.substr(pos + 1)).c_str(), &endptr));
			_data[date] = value;
		}
	}
	file.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	_data = other._data;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		_data = other._data;
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

static bool is_leap(int year)
{
	if ((year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)))
		return true;
	return false;
}

static bool check_valide_date(std::string date)
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
		std::cout << "Error: bad input => " << date << std::endl;
		return false;
	}

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (month < 1 || month > 12)
	{
		std::cout << "Error: bad input => " << date << std::endl;
		return false;
	}

	int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (month == 2 && is_leap(year)) {
		daysInMonth[1] = 29;
	}

	if (day > daysInMonth[month - 1] || day < 1)
	{
		std::cout << "Error: bad input => " << date << std::endl;
		return false;
	}
	if (year > 2026)
	{
		std::cout << "Error: bad input => " << date << std::endl;
		return false;
	}
	return true;
}

void BitcoinExchange::check_input(std::string str)
{
	size_t pos = str.find('|');

	if (pos == std::string::npos || pos < 1 || str[pos - 1] != ' ' || str[pos + 1] != ' ')
	{
		std::cout << "Error: bad input => " << str << std::endl;
		return;
	}

	std::string date = str.substr(0, pos - 1);
	std::string value_str = str.substr(pos + 2);

	if (!check_valide_date(date))
	{
		return ;
	}

	char *end;
	float value = std::strtof(value_str.c_str(), &end);

	if (end == value_str.c_str() || *end != '\0') {
		std::cout << "Error: bad input => " << str << std::endl;
		return;
	}

	if (value < 0)
	{
		std::cout << "Error: not a positive number." << std::endl;
		return; 
	}
	if (value > 1000)
	{
		std::cout << "Error: too large a number." << std::endl;
		return; 
	}
	
	std::map<std::string, float>::iterator it = _data.lower_bound(date);
	if (it == _data.end() || it->first != date)
	{
		if (it == _data.begin())
		{
			std::cout << "Error: no data available for dates before " << _data.begin()->first << std::endl;
			return;
		}
		it--;
	}
	std::cout << date << " => " << value << " = " << it->second * value << std::endl;
}

void BitcoinExchange::processInput(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	std::string	str;
	
	if (!file.is_open())
	{
		std::cout << "Error: file not open." << std::endl;
		return;
	}
	std::getline(file, str);
	while (std::getline(file, str))
	{
		check_input(str);
	}
	file.close();
}