/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:19:28 by mchemari          #+#    #+#             */
/*   Updated: 2026/06/08 18:52:24 by mchemari         ###   ########.fr       */
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

void PmergeMe::mergePairs(std::vector<std::pair<int, int> >& pairs, int left, int mid, int right)
{
	std::vector<std::pair<int, int> > leftPart(pairs.begin() + left, pairs.begin() + mid + 1);
	std::vector<std::pair<int, int> > rightPart(pairs.begin() + mid + 1, pairs.begin() + right + 1);

	size_t i = 0;
	size_t j = 0;
	int k = left;
	
	// superpose pile assiette
	while (i < leftPart.size() && j < rightPart.size())
	{
		if (leftPart[i].second <= rightPart[j].second)
		{
			pairs[k] = leftPart[i];
			i++;
		}
		else
		{
			pairs[k] = rightPart[j];
			j++;
		}
		k++;
	}

	// clean le morceaux non places
	while (i < leftPart.size())
	{
		pairs[k] = leftPart[i];
		k++;
		i++;
	}
	while (j < rightPart.size())
	{
		pairs[k] = rightPart[j];
		k++;
		j++;
	}
}

void PmergeMe::mergeSortPairs(std::vector<std::pair<int, int> >& pairs, int left, int right)
{
	if (left >= right)
		return;

	int mid = left + (right - left) / 2;

	mergeSortPairs(pairs, left, mid);
	mergeSortPairs(pairs, mid + 1, right);

	mergePairs(pairs, left, mid , right);
}

void PmergeMe::sortVector()
{
	//! FORD-JOHNSON ALGO
	// 
	// size impair on vire le dernier
	int straggler = -1;
	bool hasStraggler = false;
	
	if (_vect.size() % 2 == 1)
	{
		straggler = _vect.back();
		hasStraggler = true;
		_vect.pop_back();
	}
	(void)straggler;
	(void)hasStraggler;
	
	// on met tout en paire
	std::vector<std::pair<int, int> > pairs;
	for (size_t i = 0; i < _vect.size(); i = i + 2)
		pairs.push_back(std::make_pair(_vect[i], _vect[i + 1]));
	
	// on met sur chaque paire individuelle le nombre le plus grand a droite
	for (size_t i = 0; i < pairs.size(); i++)
	{
		if (pairs[i].first > pairs[i].second)
			std::swap(pairs[i].first, pairs[i].second);
	}
	
	// on trie ces pairs par rapport au plus grand ou plus petit (merge sorting / recursif)
	if (!pairs.empty())
        mergeSortPairs(pairs, 0, pairs.size() - 1);

	// on separe en deux list (main / pend) mais on met deja le plus petit de pend dans main je crois
	std::vector<int> main_chain;
	std::vector<int> pend;

	main_chain.push_back(pairs[0].first);
	for (size_t i = 0; i < pairs.size(); i++)
	{
		main_chain.push_back(pairs[i].second);
		if (i > 0)
			pend.push_back(pairs[i].first);
	}
	//? add straggler ?

	// avec jacosthal on insert pend dans main
	//! j'ai pas ça

	//? test
	std::cout << "--- main_chain ---" << std::endl;
	for (size_t i = 0; i < main_chain.size(); i++)
		std::cout << main_chain[i] << " ";
	std::cout << std::endl;

	std::cout << "--- pend ---" << std::endl;
	for (size_t i = 0; i < pend.size(); i++)
		std::cout << pend[i] << " ";
	std::cout << std::endl;
}

void PmergeMe::process(int ac, char **av)
{
	if (!parseInput(ac, av))
		return;
	sortVector();
}
