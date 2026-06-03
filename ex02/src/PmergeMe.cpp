/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:19:28 by mchemari          #+#    #+#             */
/*   Updated: 2026/06/03 16:22:00 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	_vect = other._vect;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
		_vect = other._vect;
	return (*this);
}

PmergeMe::~PmergeMe()
{
}

void PmergeMe::process(int ac, char **av)
{
	if (parseInput(ac, av))
		return;
	sortVector();
}

static bool valid_number(std::string arg)
{
	for (size_t i = 0; i < arg.size() - 1; i++)
	{
		if (!isdigit(arg[i]))
			return false;
	}
	return true;
}

bool PmergeMe::parseInput(int ac, char **av)
{
	// ./PmergeMe 9 5 7
	for (int i = 1; i < ac; i++)
	{
		std::string arg = av[i];
		if (!valid_number(arg))
		{
			std::cout << "Error : bad input : " << arg << std::endl;
			return false;
		}
		
		long check_of = std::strtol(arg.c_str(), NULL, 10);
		if (check_of > INT_MAX)
		{
			std::cout << "Error : bad input : " << arg << std::endl;
			return false;
		}
		_vect.push_back(static_cast<int>(check_of));
	}
	return true; // ??
}

void PmergeMe::sortVector()
{
	// std::vector<std::pair<int, int> > pairs;
}

//! FORD-JOHNSON ALGO
// 
// pairing
// tri recursif
// insertion avec suite de Jacobsthal
// 






// vector deque