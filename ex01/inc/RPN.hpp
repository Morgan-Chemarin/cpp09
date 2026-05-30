/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 16:08:49 by mchemari          #+#    #+#             */
/*   Updated: 2026/05/30 17:37:35 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>
#include <iostream>

class RPN
{
	public:
		RPN();
		RPN(std::string str);
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();

		void calculate();
	private:
		std::string _input;
		std::stack<int> _stack;
};

#endif