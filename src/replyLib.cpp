/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replyLib.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmollenh <fmollenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:28:57 by fmollenh          #+#    #+#             */
/*   Updated: 2023/04/21 16:39:00 by fmollenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/User.hpp"

//		*!* ADD PREFIX  *!*
//		-----------------------


// ":" + this->getNickName() + "!" + this->getIP() + "@" + this->_server->getServerName() + " " + 


//		*!* VERITY MESSAGES  *!*
//		-----------------------

std::string User::RPY_welcomeToServer(void)
{
	std::string	replyMessage = "\n\nWelcome to " + _server->getServerName() + "!\n\n" + "The server is still under construction by Triinu, Monine, Philipp, Chiemezie, Florian and Ferenc.\n\nThe following commands are now integrated:\n" + "/NICK\n/USER\n/PW\n/JOIN\n" + "\nHave a good time on the server.";
	return (replyMessage);
}

std::string User::RPY_newNick(std::string oldNick)
{
	std::string	replyMessage = ":" + oldNick + "!" + this->getIP() + " NICK " + this->getNickName();
	return (replyMessage);
}

std::string User::RPY_pass(bool registered)
{
	std::string	replyMessage;
	if (registered == true)
		replyMessage = "pass :successfully registered";
	else
		replyMessage = "pass :wrong password";
	return (replyMessage);
}

std::string User::RPY_joinChannel(Channel* channel)
{
	std::string	replyMessage1 = ":" + this->getNickName() + "!" + this->getIP() + " JOIN " + channel->getChannelName();
	return (replyMessage1);
}

// std::string		User::RPY_who(Channel *channel)
// {
// 	std::string	replyMessage = ":" + _server->getServerName() + " 353 " + this->getNickName() + " = " + channel->getChannelName() + ":";
// 	std::list<User *>::iterator iterOper = channel->getListPtrOperators()->begin();
// 	for (;iterOper != channel->getListPtrOperators()->end(); ++iterOper)
// 		replyMessage += "@" + (*iterOper)->getNickName() + " ";
// 	std::list<User *>::iterator iterUser = channel->getListPtrOrdinaryUsers()->begin();
// 	for (;iterOper != channel->getListPtrOrdinaryUsers()->end(); ++iterUser)
// 		replyMessage += "@" + (*iterUser)->getNickName() + " ";
// 	replyMessage.resize(replyMessage.size() - 1);
// 	sendMsgToOwnClient(replyMessage);
// }

// std::string		User::RPY_getModeCreated(Channel *channel)
// {
// 	std::string	replyMessage1 = ":" + _server->getServerName() + " 353 " + this->getNickName() + " = " + channel->getChannelName() + ":End of /NAMES list";
// 	sendMsgToOwnClient(replyMessage1);

// 	std::string	replyMessage2 = "New channel " + channel->getChannelName() + " created by you. You are operator.";
// 	sendMsgToOwnClient(replyMessage2);
// }

// std::string		User::RPY_getModeJoined(Channel *channel)
// {
// 	std::string	replyMessage = "Joined channel " + channel->getChannelName() + ". You are not an operator.";
// 	sendMsgToOwnClient(replyMessage);
// }

//		*!* ERROR MESSAGES  *!*
//		-----------------------

std::string	User::RPY_ERR_commandNotfound(std::string command)
{
	std::string prefix = ":" + this->getNickName() + "!" + this->getIP() + " ";
	std::string	replyMessage = command + " : Unkown command";
	return (replyMessage);
}
