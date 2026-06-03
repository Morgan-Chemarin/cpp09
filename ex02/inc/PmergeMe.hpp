/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:19:24 by mchemari          #+#    #+#             */
/*   Updated: 2026/06/03 16:18:59 by mchemari         ###   ########.fr       */
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
        void sortVector();
};

#endif