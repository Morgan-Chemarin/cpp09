/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 13:55:47 by mchemari          #+#    #+#             */
/*   Updated: 2026/05/26 16:49:19 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>

BitcoinExchange::BitcoinExchange()
{
	std::ifstream file("data.csv");
	std::string	str;
	char **endptr = NULL;
	std::string date;
	float value;

	if (!file.is_open())
	{
		// error no file open
		return;
	}
	std::getline(file, str);
	while (std::getline(file, str))
	{
		size_t pos = str.find(',');
		if (pos != std::string::npos)
		{
			date = str.substr(0, pos);
			value = static_cast<float>(std::strtod((str.substr(pos + 1)).c_str(), endptr));
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

static void check_input_date(std::string str)
{
	size_t pos = str.find('|');
	if (pos == std::string::npos)
	{
		std::cout << "Bad input => |." << std::endl;
		return;
	}

	// soit split date / valeur

	//! DATE
	// following format: Year-Month-Day
	// day 1-31 selon le mois
	// month 1-12
	// years ?? > 2026 ?
	// bisextile

	//! VALUE
	// loat or a positive integer, between 0 and 1000
}

void BitcoinExchange::processInput(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	std::string	str;
	
	if (!file.is_open())
	{
		// error no file open
		return;
	}
	std::getline(file, str); // check == "date | value"
	while (std::getline(file, str))
	{
		check_input_date(str); // return value
		
	}
	file.close();
}


// scores.insert(std::make_pair("Bob", 21));
// scores.find("Charlie")


