/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev <dev@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:19:24 by mchemari          #+#    #+#             */
/*   Updated: 2026/06/08 14:20:34 by dev              ###   ########.fr       */
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

        bool parseInput(int ac, char **av);
		void mergeSortPairs(std::vector<std::pair<int, int> >& pairs, int left, int right);
		void sortVector();
};

#endif