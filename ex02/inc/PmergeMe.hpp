/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:19:24 by mchemari          #+#    #+#             */
/*   Updated: 2026/06/09 02:24:55 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <cstdlib>
#include <string>
#include <climits>
#include <algorithm>

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();

		void process(int ac, char **av);
	
	private:
		std::vector<int> _vect;
		std::deque<int> _deq;

		std::vector<int> generateJacobstahle(int size);

		bool parseInputVec(int ac, char **av);
		void mergePairsVec(std::vector<std::pair<int, int> >& pairs, int left, int mid, int right);
		void mergeSortPairsVec(std::vector<std::pair<int, int> >& pairs, int left, int right);
		void binaryInsertVec(std::vector<int>& main_chain, int value);
		void sortVector();

		bool parseInputDeq(int ac, char **av);
		void mergePairsDeq(std::deque<std::pair<int, int> >& pairs, int left, int mid, int right);
		void mergeSortPairsDeq(std::deque<std::pair<int, int> >& pairs, int left, int right);
		void binaryInsertDeq(std::deque<int>& main_chain, int value);
		void sortDeque();
};

#endif