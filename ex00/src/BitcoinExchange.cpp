/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 13:55:47 by mchemari          #+#    #+#             */
/*   Updated: 2026/05/26 16:30:43 by mchemari         ###   ########.fr       */
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

void BitcoinExchange::processInput(const std::string &filename)
{
	// recup chaque ligne, check et sortir de _data
	
	(void)filename;
}



// scores.insert(std::make_pair("Bob", 21));
// scores.find("Charlie")


// std::map<std::string, float>::const_iterator it = _data.begin();
// while (it != _data.end())
// {
// 	std::cout << "Key = " << it->first << " / Value = " << it->second << std::endl;
// 	it++;
// }