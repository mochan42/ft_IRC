/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replyLib.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmollenh <fmollenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:28:57 by fmollenh          #+#    #+#             */
/*   Updated: 2023/04/20 11:50:09 by fmollenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/User.hpp"


//		*!* VERITY MESSAGES  *!*
//		-----------------------

const char *User::RPY_welcomeToServer(void)
{
	_replyMessage = this->getNickName() + " welcome to " + _server->getServerName();
	return (_replyMessage.c_str());
}

//		*!* ERROR MESSAGES  *!*
//		-----------------------

const char *User::RPY_ERR_commandNotfound(std::string command)
{
	_replyMessage = ":" + _server->getServerName() + " " + this->getNickName() + " " + command + " : Unkown command";
	return (_replyMessage.c_str());
}