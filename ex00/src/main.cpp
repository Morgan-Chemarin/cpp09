/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemari <mchemari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 13:55:45 by mchemari          #+#    #+#             */
/*   Updated: 2026/05/26 16:31:52 by mchemari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 1)
	{
		std::cout << "Error: could not open file." << std::endl;
		return 0;
	}
	BitcoinExchange btc;
	btc.processInput(av[1]);
	
}

// lowerbound on map