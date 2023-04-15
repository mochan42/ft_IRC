/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:10:05 by pmeising          #+#    #+#             */
/*   Updated: 2023/04/15 12:14:29 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

Server::Server()
{
}

Server::~Server()
{
	// Need to delete all allocated memory here.
}


// ########################################### MEMBERFUNCTIONS ########################################
void	Server::readErrorCodes(std::map<t_err, std::string>& errors)
{
	std::ifstream	input;

	try
	{
		input.open(this->_errorFile);
		if (input.fail())
			throw ErrorInternal();
		else
		{
			/*std::ifstream	infile(infilePath);
			checkFileCanBeOpened(infile);
			std::string	line;
			std::getline(infile, line);
			while(getline(infile, line))
			{
				size_t	pos = line.find(",");
				if (pos == std::string::npos)
				{
					std::cout << "Error: delimiter not found in line \"" << line << "\"" << std::endl;
					continue;
				}
				std::string	date = line.substr(0, pos);
				std::string	numericValue = line.substr(pos + 1);
				float btcNumericValueInt = static_cast<float>(atof(numericValue.c_str()));
				this->_btcExchangeRate.insert(std::pair<std::string, float > (date, btcNumericValueInt));
			}
			infile.close(); */
		}
	}
	catch(const std::exception& e)
		std::cerr << "Internal error:" << e.what() << this->_errorFile << " coudln't be opened.\n";
	
	
		
}