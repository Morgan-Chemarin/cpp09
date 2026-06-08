/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:19:28 by mchemari          #+#    #+#             */
/*   Updated: 2026/06/08 11:08:10 by dev              ###   ########.fr       */
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
	if (!parseInput(ac, av))
        return;
    fordJohnsonVector(0, _vect.size(), 1);

    std::cout << "Vecteur trié : ";
    for (size_t i = 0; i < _vect.size(); ++i) {
        std::cout << _vect[i] << " ";
    }
    std::cout << std::endl;
}

static bool valid_number(std::string arg)
{
	if (arg.empty())
		return false;
	for (size_t i = 0; i < arg.size(); i++)
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
		if (check_of > INT_MAX || check_of < 0)
		{
			std::cout << "Error : bad input : " << arg << std::endl;
			return false;
		}
		_vect.push_back(static_cast<int>(check_of));
	}
	return true;
}

void PmergeMe::sortVector()
{
	//! FORD-JOHNSON ALGO
	// 
	// size impair on vire le dernier
	if (_vect.size() % 2 == 1)
	{
		int impair = _vect.back(); // stocke dans la class ?
		_vect.pop_back();
		(void)impair;
	}
	// on met tout en paire
	std::vector<std::pair<int, int> > pairs;
	for (size_t i = 0; i < _vect.size(); i = i + 2)
	{
		pairs.push_back(std::make_pair(_vect[i], _vect[i + 1]));
	}
	// on met sur chaque paire individuelle le nombre le plus grand a droite 
	// on trie ces pairs par rapport au plus grand ou plus petit (merge sorting / recursif)
	// on separe en deux list (main / pend) mais on met deja le plus petit de pend dans main je crois
	// avec jacosthal on insert pend dans main

	std::cout << "--- Contenu de pairs ---" << std::endl;
	for (std::vector<std::pair<int, int> >::const_iterator it = pairs.begin(); it != pairs.end(); ++it)
	{
		std::cout << "[ " << it->first << " , " << it->second << " ] ";
	}
	std::cout << std::endl << "------------------------" << std::endl;
}


// vector deque