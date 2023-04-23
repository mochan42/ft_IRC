/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replyLib.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:28:57 by fmollenh          #+#    #+#             */
/*   Updated: 2023/04/22 20:31:51 by fsemke           ###   ########.fr       */
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
	std::string	replyMessage = ":" + oldNick + "!" + _userName + "@" + _ip + " NICK " + _nickName;
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

std::string User::RPY_ChannelMsg(std::string message, Channel* channel)
{
	std::string	replyMessage = ":" + this->getNickName() + "!" + this->getNickName() + "@" + this->getIP() + " PRIVMSG " + channel->getChannelName() + " " + message;
	return (replyMessage);
}


std::string User::RPY_joinChannelBroadcast(Channel* channel)
{
	std::string	replyMessage = ":" + this->getNickName() + "!" + this->getIP() + " JOIN " + channel->getChannelName();
	return (replyMessage);
}

std::string User::RPY_joinChannel(Channel* channel)
{
	std::string	replyMessage = "Joined channel " + channel->getChannelName() + ". You are not an operator.";
	return (replyMessage);
}

std::string User::RPY_createChannel(Channel* channel)
{
	std::string	replyMessage = "New channel " + channel->getChannelName() + " created by you. You are operator.";
	return (replyMessage);
}

const char *User::RPY_inviteMessage(std::string otherNick, std::string channel)
{
	_replyMessage = ":" + _nickName + "!" + _userName + "@" + _ip + " INVITE " + otherNick + channel;
	return (_replyMessage.c_str());
}

const char *User::RPY_341_userAddedtoInviteList(std::string otherNick, std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 341 " + _nickName + " " + otherNick + " " + channel;
	return (_replyMessage.c_str());
}

const char *User::RPY_kickedMessage(std::string otherNick, std::string channel)
{
	_replyMessage = ":" + _nickName + "!" + _userName + "@" + _ip + " KICK " + channel + " " + otherNick;
	return (_replyMessage.c_str());
}

const char *User::RPY_leaveChannel(std::string channel)
{
	_replyMessage = ":" + _nickName + "!" + _userName + "@" + _ip + " PART " + channel + " :Leaving";
	return (_replyMessage.c_str());
}

const char *User::RPY_332_channelTopic(std::string channel, std::string topic)
{
	_replyMessage = ":" + _server->getServerName() + " 332 " + _nickName + " " + channel + " :" + topic;
	return (_replyMessage.c_str());
}

const char *User::RPY_newTopic(std::string channel, std::string newTopic)
{
	//>> :<Nick>!<User@IP> TOPIC <channel> :<new Topic>
	_replyMessage = ":" + _nickName + "!" + _userName + "@" + _ip + " TOPIC " + channel + " :" + newTopic;
	return (_replyMessage.c_str());
}

const char *User::RPY_352_whoUser(std::string recipientNick, std::string channel, bool op)
{
	std::string flag = " H :0 ";
	if (op)
		flag = " H@ :0 ";
	_replyMessage = ":" + _server->getServerName() + " 352 " + recipientNick + " " + channel + " " + _userName + " " +_ip + " " +_server->getServerName() + " " + _nickName + flag + _realName;
	return (_replyMessage.c_str());
}

const char *User::RPY_315_endWhoList(std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 315 " + _nickName + " " + channel + " :End of WHO list";
	return (_replyMessage.c_str());
}

//		*!* ERROR MESSAGES  *!*
//		-----------------------

std::string	User::RPY_ERR_commandNotfound(std::string command)
{
	std::string prefix = ":" + this->getNickName() + "!" + this->getIP() + " ";
	std::string	replyMessage = command + " : Unkown command";
	return (replyMessage);
}

const char *User::RPY_ERR462_alreadyRegistered()
{
	_replyMessage = ":" + _server->getServerName() + " 462 " + _nickName + " :Unauthorized command (already registered)";
	return (_replyMessage.c_str());
}

const char *User::RPY_ERR401_noSuchNickChannel(std::string nickchannel)
{
	_replyMessage = ":" + _server->getServerName() + " 401 " + _nickName + " " + nickchannel + " :No such nick/channel";
	return (_replyMessage.c_str());
}

const char *User::RPY_ERR443_alreadyOnChannel(std::string otherNick, std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 443 " + _nickName + " " + otherNick + " " + channel + " :User is already on that channel";
	return (_replyMessage.c_str());
}

const char *User::RPY_ERR476_badChannelMask(std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 476 " + _nickName + " " + channel + " :Bad Channel Mask";
	return (_replyMessage.c_str());
}

const char *User::RPY_ERR475_canNotJoinK(std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 475 " + _nickName + " " + channel + " :Cannot join channel (+k)";
	return (_replyMessage.c_str());
}

const char *User::RPY_ERR473_canNotJoinI(std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 473 " + _nickName + " " + channel + " :Cannot join channel (+i)";
	return (_replyMessage.c_str());
}

const char *User::RPY_ERR471_canNotJoinL(std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 471 " + _nickName + " " + channel + " :Cannot join channel (+l)";
	return (_replyMessage.c_str());
}

const char *User::RPY_ERR482_notChannelOp(std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 482 " + _nickName + " " + channel + " :You're not channel operator";
	return (_replyMessage.c_str());
}

const char *User::RPY_ERR441_kickNotOnChannel(std::string otherNick, std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 441 " + _nickName + " " + otherNick + " :Is not on channel " + channel;
	return (_replyMessage.c_str());
}

const char *User::RPY_ERR403_noSuchChannel(std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 403 " + _nickName + " " + channel + " :No such channel";
	return (_replyMessage.c_str());
}

const char *User::RPY_ERR442_youreNotOnThatChannel(std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 442 " + _nickName + " " + channel + " :You're not on that channel";
	return (_replyMessage.c_str());
}
