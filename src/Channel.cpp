/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 10:03:39 by cudoh             #+#    #+#             */
/*   Updated: 2023/04/15 19:01:30 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Channel.hpp"

Channel::Channel( std::string name, std::string topic )
: _channelCapacity(CHN_MAX_USERS),
{
    COUT << "\nCall parametric constructor : Channel" << ENDL;
	try
	{
		if (name == "" || topic == "")
			throw EmptyContentException;
		else
		{
			_channelName = name;
			_topic = topic;
    		_invitedUsers = new std::list<user *>;
    		_operators = new std::list<user *>;
    		_bannedUsers = new std::list<user *>;
    		_allUsers = new std::list<user *>;
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
	deallocPtrs(_allUsers);
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


std::list<User *>	Channel::*getListPtrInvitedUsers(void) const
{
    return (_invitedUsers);
}


std::list<User *>	Channel::*getListPtrOperators(void) const
{
    return (_operators);
}


std::list<User *>	Channel::*getListPtrBannedUsers(void) const
{
    return (_bannedUsers);
}


std::list<User *>	Channel::*getListPtrAllUsers(void) const
{
    return (_allUsers);
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
			throw EmptyContentException;
		if (list_users == NULL)
			throw NullPointerException();
		for (it = _allUsers.begin(); it != _allUsers.end(); ++it)
		{
			fd = (*it)->getFd();
			write(fd, msg.c_str(); msgLen);
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
		result = list_users.empty();
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
	
		for (it = list_users.begin(); it != list_users.end(); ++it)
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
		list_user->push_back(user);
	}
	else
	{
		throw UsrExistException;
	}
}


void	Channel::removeUserFromList(std::list<User *> *list_users, User *user)
{
	if (isUserInList(list_users, user) == true)
	{
		list_user->remove(user);
	}
	else
	{
		throw UsrNotFoundException;
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
		while (!(list_users.empty()))
		{
			list_users.pop_back();
		}
	}
	return (result);
}


void	deallocPtrs(std::list<User *> *list_users)
{
	if (emptyUserList(list_users) == CHN_TRUE)
	{
		delete list_users;
		list_users = NULL;
	}
}
