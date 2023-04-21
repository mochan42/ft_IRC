/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 10:03:39 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/21 11:32:56 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Channel.hpp"

Channel::Channel( std::string name, std::string topic, User* user)
: _channelCapacity(CHN_MAX_USERS),
_invitedUsers(NULL), _operators(NULL), _bannedUsers(NULL), _ordinaryUsers(NULL)
{
    COUT << "\nCall parametric constructor : Channel" << ENDL;
	try
	{
		if (name == "" || topic == "")
			throw EmptyContentException();
		else
		{
			_channelName = name;
			_topic = topic;
    		_invitedUsers = new std::list<User *>;
    		_operators = new std::list<User *>;
    		_bannedUsers = new std::list<User *>;
    		_ordinaryUsers = new std::list<User *>;
			this->addUserToList(this->_ordinaryUsers ,user);
		}
	}
	catch(const std::exception & e)
	{
		std::cerr << e.what() << '\n';
	}
}

Channel::~Channel(void)
{
    COUT << "\nCall destructor : Channel" << ENDL;
	deallocPtrs(_invitedUsers);
	deallocPtrs(_operators);
	deallocPtrs(_bannedUsers);
	deallocPtrs(_ordinaryUsers);
}

/*---------------Getters and setters--------------------------- */

std::string Channel::getChannelName(void) const
{
    return (_channelName);
}


std::string Channel::getTopic(void) const
{
    return (_topic);
}


unsigned int    Channel::getChannelCapacity(void) const
{
    return (_channelCapacity);
}


std::list<User *>	*Channel::getListPtrInvitedUsers(void) const
{
    return (_invitedUsers);
}


std::list<User *>	*Channel::getListPtrOperators(void) const
{
    return (_operators);
}


std::list<User *>	*Channel::getListPtrBannedUsers(void) const
{
    return (_bannedUsers);
}


std::list<User *>	*Channel::getListPtrOrdinaryUsers(void) const
{
    return (_ordinaryUsers);
}


void   Channel::setChannelName(std::string name)
{
    _channelName = name;
}


void   Channel::setTopic(std::string topic)
{
    _topic = topic;
}


/*----------- Methods -------------------------------------*/

void Channel::broadcastMsg(std::string msg)
{
	int msgLen = msg.size();
	int fd = 0;
	std::list<User *>::iterator it;
	

	try
	{
		if (msgLen == 0)
			throw EmptyContentException();
		if (_operators == NULL || _ordinaryUsers == NULL)
			throw NullPointerException();
		
		/* iterate over operators and ordinary user lists to send msg */
		for (it = _operators->begin(); it != _operators->end(); ++it)
		{
			fd = (*it)->getFd();
			write(fd, msg.c_str(), msgLen);
		}
		for (it = _ordinaryUsers->begin(); it != _ordinaryUsers->end(); ++it)
		{
			fd = (*it)->getFd();
			write(fd, msg.c_str(), msgLen);
		}
	}	
	catch(const std::exception & e)
	{
		std::cerr << e.what() << '\n';
	}

}


bool    Channel::isUserListEmpty(std::list<User *> *list_users)
{
	bool result = false;

	try
	{
		if (list_users == NULL)
		{
			throw NullPointerException();
		}
		result = (*list_users).empty();
	}
	catch(const std::exception & e)
	{
		std::cerr << e.what() << '\n';
	}
	return (result);
}


bool	Channel::isUserInList(std::list<User *> *list_users, User *user)
{
	std::list<User *>::iterator it;
	bool result = false;
	
	try
	{
		if (list_users == NULL || user == NULL)
		{
			throw NullPointerException();
		}
	
		for (it = list_users->begin(); it != list_users->end(); ++it)
		{
			if (*it == user)
			{
				result = true;
			}
		}
	}
	catch(const std::exception & e)
	{
		std::cerr << e.what() << '\n';
	}
	return (result);
}


void	Channel::addUserToList(std::list<User *> *list_users, User *user)
{
	if (isUserInList(list_users, user) == false)
	{
		list_users->push_back(user);
	}
	else
	{
		throw UsrExistException();
	}
}


void	Channel::removeUserFromList(std::list<User *> *list_users, User *user)
{
	if (isUserInList(list_users, user) == true)
	{
		list_users->remove(user);
	}
	else
	{
		throw UsrNotFoundException();
	}
}


void    Channel::updateUserList(std::list<User *> *list_users, User *user,
                                                      t_chn_action action)
{
    try
    {
		switch (action)
		{
		    case USR_ADD:
			{
				addUserToList(list_users, user);
				break;
			}
		    case USR_REMOVE:
			{
				removeUserFromList(list_users, user);
				break;
			}
		    default:
			{
        		throw InvalidActionException();
			}
		}
    }
	catch(const std::exception & e)
	{
		std::cerr << e.what() << '\n';
	}  
}


int	Channel::emptyUserList(std::list<User *> *list_users)
{
	int result = CHN_FALSE;
	
	if (list_users != NULL)
	{
		result = CHN_TRUE;
		while (!((*list_users).empty()))
		{
			(*list_users).pop_back();
		}
	}
	return (result);
}


void	Channel::deallocPtrs(std::list<User *> *list_users)
{
	if (emptyUserList(list_users) == CHN_TRUE)
	{
		delete list_users;
		list_users = NULL;
	}
}



User*	Channel::fetchUserPtrFromList(std::list<User *> *user_list, 
									   std::string nickname)
{
	std::list<User *>::iterator	it = user_list->begin();
	
	for (; it != user_list->end(); ++it)
	{
		if ((*it)->getNickName() == nickname)
		{
			return (*it);
		}
	}
	return (NULL);
}



User	*Channel::isUserInChannel(std::string nickname)
{
	User	*user = NULL;
	
	user = fetchUserPtrFromList(_operators, nickname);
	if (user == NULL)
	{
		user = fetchUserPtrFromList(_ordinaryUsers, nickname);
	}
	return (user);
}



int	Channel::demoteUser(std::string nickname)
{
	int rc_code = -1; // does not exist
	User *user = NULL;
	
	user = fetchUserPtrFromList(_operators, nickname);
	if (user != NULL)
	{
		rc_code = 0;
		removeUserFromList(_operators, user);
		addUserToList(_ordinaryUsers, user);
	}
	return (rc_code);
}



int	Channel::promoteUser(std::string nickname)
{
	int rc_code = -1; // does not exist
	User *user = NULL;
	
	user = fetchUserPtrFromList(_ordinaryUsers, nickname);
	if (user != NULL)
	{
		rc_code = 0;
		removeUserFromList(_ordinaryUsers, user);
		addUserToList(_operators, user);
	}
	return (rc_code);
}
