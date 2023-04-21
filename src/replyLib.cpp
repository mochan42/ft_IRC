/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replyLib.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:28:57 by fmollenh          #+#    #+#             */
/*   Updated: 2023/04/21 14:56:16 by fsemke           ###   ########.fr       */
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
	_replyMessage = ":" + _nickName + "!" + _userName + "@" + _ip + " KICK " + channel + otherNick;
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

const char *User::RPY_352_whoUser(std::string recipientNick, std::string channel)
{
	_replyMessage = ":" + _server->getServerName() + " 352 " + recipientNick + " " + channel + " " + _userName + " " +_ip + " " +_server->getServerName() + " " + _nickName + " H :0 " + _realName;
	return (_replyMessage.c_str());
}

const char *User::RPY_315_endWhoList(std::string channel)
{
	//>> :<ServerName> 315 <ownNick> <channel> :End of WHO list
	_replyMessage = ":" + _server->getServerName() + " 315 " + _nickName + " " + channel + " :End of WHO list";
	return (_replyMessage.c_str());
}

//		*!* ERROR MESSAGES  *!*
//		-----------------------

const char *User::RPY_ERR_commandNotfound(std::string command)
{
	_replyMessage = ":" + _server->getServerName() + " " + this->getNickName() + " " + command + " :Unkown command";
	return (_replyMessage.c_str());
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