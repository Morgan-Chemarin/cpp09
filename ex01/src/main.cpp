/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 16:08:45 by mchemari          #+#    #+#             */
/*   Updated: 2026/06/03 10:31:45 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
#include <stack>

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Error : bad format ./RPN \"8 9 *\"" << std::endl;
		return 1;
	}
	RPN rpn(av[1]);
	rpn.calculate();
	return 0;
}