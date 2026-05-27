/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 13:55:47 by mchemari          #+#    #+#             */
/*   Updated: 2026/05/27 13:11:12 by dev              ###   ########.fr       */
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

static void check_input(std::string str)
{
	size_t pos = str.find('|');
	if (pos == std::string::npos)
	{
		std::cout << "Bad input => '|'." << std::endl;
		return;
	}
	if (pos == 0 || str[pos - 1] != ' ' || str[pos + 1] != ' ')
	{
		std::cout << "Bad input => ' '." << std::endl;
		return;
	}
	
	char *end;
	std::string date = str.substr(0, pos - 1);
	float value = std::strtof(str.substr(pos + 1).c_str(), &end);
	// std::cout << date << " : " << value << std::endl;
	if (*end != '\0' && !std::isspace(*end)) {
        std::cout << "Error: bad input (value) => " << str.substr(pos + 1) << std::endl;
        return;
    }

	//! DATE
	// following format: Year-Month-Day
	// day 1-31 selon le mois
	// month 1-12
	// years ?? > 2026 ?
	// bisextile
	if (check_valide_date())
	{
		// 
		return;
	}

	//! VALUE
	// loat or a positive integer, between 0 and 1000
	if (value < 0 || value > 1000)
	{
		//
		return; 
	}
	
	// trouver la bonne date où celle dessous
	// add check_input dans la class ou arg
	// btc->_data[date] * value;
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
	std::getline(file, str); // check == "date | value"
	while (std::getline(file, str))
	{
		check_input(str); // return value
		
	}
	file.close();
}


// scores.insert(std::make_pair("Bob", 21));
// scores.find("Charlie")


