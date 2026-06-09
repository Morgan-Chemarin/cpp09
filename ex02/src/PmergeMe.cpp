/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:19:28 by mchemari          #+#    #+#             */
/*   Updated: 2026/06/09 16:51:04 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	_vect = other._vect;
	_deq = other._deq;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_vect = other._vect;
		_deq = other._deq;
	}
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

std::vector<int> PmergeMe::generateJacobstahle(int size)
{
	std::vector<int> jacob;
	std::vector<int> sequence;
	
	sequence.push_back(0);
	sequence.push_back(1);

	while (sequence.back() < size)
	{
		int next = sequence[sequence.size() - 1]  + sequence[sequence.size() - 2] * 2;
		sequence.push_back(next);
	}
	
	for (size_t i = 1; i < sequence.size(); i++)
	{
		int upper = sequence[i];
		int lower = sequence[i - 1];
		
		for (int j = upper; j > lower; j--)
		{
			if (j < size && std::find(jacob.begin(), jacob.end(), j) == jacob.end())
				jacob.push_back(j);
		}
	}

	for (int i = 0; i < size; i++)
	{
		if (std::find(jacob.begin(), jacob.end(), i) == jacob.end())
			jacob.push_back(i);
	}
	
	return jacob;
}

//! ---------------------
//! SORT VECTOR CONTAINER
//! ---------------------

bool PmergeMe::parseInputVec(int ac, char **av)
{
	for (int i = 1; i < ac; i++)
	{
		std::string arg = av[i];
		if (!valid_number(arg))
		{
			std::cerr << "Error : bad input : " << arg << std::endl;
			return false;
		}
		
		long check_of = std::strtol(arg.c_str(), NULL, 10);
		if (check_of > INT_MAX || check_of < 0)
		{
			std::cerr << "Error : bad input : " << arg << std::endl;
			return false;
		}
		_vect.push_back(static_cast<int>(check_of));
	}
	return true;
}

void PmergeMe::mergePairsVec(std::vector<std::pair<int, int> >& pairs, int left, int mid, int right)
{
	std::vector<std::pair<int, int> > leftPart(pairs.begin() + left, pairs.begin() + mid + 1);
	std::vector<std::pair<int, int> > rightPart(pairs.begin() + mid + 1, pairs.begin() + right + 1);

	size_t i = 0;
	size_t j = 0;
	int k = left;
	
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

void PmergeMe::mergeSortPairsVec(std::vector<std::pair<int, int> >& pairs, int left, int right)
{
	if (left >= right)
		return;

	int mid = left + (right - left) / 2;

	mergeSortPairsVec(pairs, left, mid);
	mergeSortPairsVec(pairs, mid + 1, right);

	mergePairsVec(pairs, left, mid , right);
}

void PmergeMe::binaryInsertVec(std::vector<int>& main_chain, int value)
{
	std::vector<int>::iterator pos = std::lower_bound(main_chain.begin(), main_chain.end(), value);
	main_chain.insert(pos, value);
}

void PmergeMe::sortVector()
{
	int straggler = -1;
	bool hasStraggler = false;
	
	if (_vect.size() % 2 == 1)
	{
		straggler = _vect.back();
		hasStraggler = true;
		_vect.pop_back();
	}
	
	if (_vect.empty())
	{
		if (hasStraggler)
			_vect.push_back(straggler);
		return;
	}
	
	std::vector<std::pair<int, int> > pairs;
	for (size_t i = 0; i < _vect.size(); i = i + 2)
		pairs.push_back(std::make_pair(_vect[i], _vect[i + 1]));

	for (size_t i = 0; i < pairs.size(); i++)
	{
		if (pairs[i].first > pairs[i].second)
			std::swap(pairs[i].first, pairs[i].second);
	}
	
	if (!pairs.empty())
		mergeSortPairsVec(pairs, 0, pairs.size() - 1);

	std::vector<int> main_chain;
	std::vector<int> pend;

	if (!pairs.empty())
		main_chain.push_back(pairs[0].first);
	for (size_t i = 0; i < pairs.size(); i++)
	{
		main_chain.push_back(pairs[i].second);
		if (i > 0)
			pend.push_back(pairs[i].first);
	}

	std::vector<int> jacob_order = generateJacobstahle(pend.size());
	
	for (size_t i = 0; i < jacob_order.size(); i++)
	{
		int index = jacob_order[i];
		if (index < static_cast<int>(pend.size()))
		{
			binaryInsertVec(main_chain, pend[index]);
		}
	}

	if (hasStraggler)
		binaryInsertVec(main_chain, straggler);
	
	_vect = main_chain;
}

//! --------------------
//! SORT DEQUE CONTAINER
//! --------------------

bool PmergeMe::parseInputDeq(int ac, char **av)
{
	for (int i = 1; i < ac; i++)
	{
		std::string arg = av[i];
		if (!valid_number(arg))
			return false;
		long check_of = std::strtol(arg.c_str(), NULL, 10);
		if (check_of > INT_MAX || check_of < 0)
			return false;
		_deq.push_back(static_cast<int>(check_of));
	}
	return true;
}

void PmergeMe::mergePairsDeq(std::deque<std::pair<int, int> >& pairs, int left, int mid, int right)
{
	std::deque<std::pair<int, int> > leftPart(pairs.begin() + left, pairs.begin() + mid + 1);
	std::deque<std::pair<int, int> > rightPart(pairs.begin() + mid + 1, pairs.begin() + right + 1);

	size_t i = 0;
	size_t j = 0;
	int k = left;
	
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

void PmergeMe::mergeSortPairsDeq(std::deque<std::pair<int, int> >& pairs, int left, int right)
{
	if (left >= right)
		return;

	int mid = left + (right - left) / 2;

	mergeSortPairsDeq(pairs, left, mid);
	mergeSortPairsDeq(pairs, mid + 1, right);

	mergePairsDeq(pairs, left, mid , right);
}

void PmergeMe::binaryInsertDeq(std::deque<int>& main_chain, int value)
{
	std::deque<int>::iterator pos = std::lower_bound(main_chain.begin(), main_chain.end(), value);
	main_chain.insert(pos, value);
}

void PmergeMe::sortDeque()
{
	int straggler = -1;
	bool hasStraggler = false;
	
	if (_deq.size() % 2 == 1)
	{
		straggler = _deq.back();
		hasStraggler = true;
		_deq.pop_back();
	}
	
	if (_deq.empty())
	{
		if (hasStraggler)
			_deq.push_back(straggler);
		return;
	}
	
	std::deque<std::pair<int, int> > pairs;
	for (size_t i = 0; i < _deq.size(); i = i + 2)
		pairs.push_back(std::make_pair(_deq[i], _deq[i + 1]));

	for (size_t i = 0; i < pairs.size(); i++)
	{
		if (pairs[i].first > pairs[i].second)
			std::swap(pairs[i].first, pairs[i].second);
	}
	
	if (!pairs.empty())
		mergeSortPairsDeq(pairs, 0, pairs.size() - 1);

	std::deque<int> main_chain;
	std::deque<int> pend;

	if (!pairs.empty())
		main_chain.push_back(pairs[0].first);
	for (size_t i = 0; i < pairs.size(); i++)
	{
		main_chain.push_back(pairs[i].second);
		if (i > 0)
			pend.push_back(pairs[i].first);
	}

	std::vector<int> jacob_order = generateJacobstahle(pend.size());
	
	for (size_t i = 0; i < jacob_order.size(); i++)
	{
		int index = jacob_order[i];
		if (index < static_cast<int>(pend.size()))
		{
			binaryInsertDeq(main_chain, pend[index]);
		}
	}

	if (hasStraggler)
		binaryInsertDeq(main_chain, straggler);
	
	_deq = main_chain;
}

void PmergeMe::process(int ac, char **av)
{
	clock_t start_vec = clock();
	if (!parseInputVec(ac, av))
	{
		return;
	}
	sortVector();
	clock_t end_vec = clock();

	clock_t start_deq = clock();
	if (!parseInputDeq(ac, av))
	{
		return;
	}
	sortDeque();
	clock_t end_deq = clock();

	std::cout << "Before: ";
	for (int i = 1; i < ac; i++)
		std::cout << av[i] << " ";
	std::cout << std::endl;

	std::cout << "After:  ";
	for (size_t i = 0; i < _vect.size(); i++)
		std::cout << _vect[i] << " ";
	std::cout << std::endl;

	double time_vec = static_cast<double>(end_vec - start_vec) / CLOCKS_PER_SEC * 1000000;
	double time_deq = static_cast<double>(end_deq - start_deq) / CLOCKS_PER_SEC * 1000000;

	std::cout << "Time to process a range of " << _vect.size() << " elements with std::vector : " << time_vec << " us" << std::endl;
	std::cout << "Time to process a range of " << _deq.size() << " elements with std::deque  : " << time_deq << " us" << std::endl;
}
