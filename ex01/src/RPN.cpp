/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 16:08:47 by mchemari          #+#    #+#             */
/*   Updated: 2026/05/30 18:28:12 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(): _input("")
{
}

RPN::RPN(std::string str): _input(str)
{
	
}

RPN::RPN(const RPN& other)
{
	_input = other._input;
	_stack = other._stack;
}

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
	{
		_input = other._input;
		_stack = other._stack;
	}
	return *this;
}

RPN::~RPN()
{
	
}

static bool isSymb(char c)
{
	return (c == '*' || c == '/' || c == '+' || c == '-');
}

void RPN::calculate()
{
	int result = 0;
	for (size_t i = 0; i < _input.size(); i++)
	{
		if (_input[i] == ' ')
			i++;
		if (isdigit(_input[i]))
			_stack.push(_input[i] - '0');
		else if (isSymb(_input[i]))
		{
			if (_stack.size() < 2)
			{
				std::cout << "Error: too many operators" << std::endl;
				return;
			}
			else if (_stack.size() > 2)
			{
				std::cout << "Error: not enough operators" << std::endl;
				return;
			}

			if (!result)
				result = _stack.top();
			_stack.pop(); // 1 element after
			result  = result * _stack.top();
			_stack.pop(); // 0 element after
			_stack.push(result); // 1 element after
		}
		else
		{
			std::cout << "Error: invalid character" << std::endl;
			return;
		}
	}
	if (_stack.size() == 1)
        std::cout << _stack.top() << std::endl;
	else
		std::cout << result << std::endl;
}