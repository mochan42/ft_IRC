#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <cstring>
# include <list>
# include <exception>
# include <unistd.h>
# include <cmath>
# include "User.hpp"

# define CHN_MAX_USERS (1024)
# define CHN_MIN_USERS (1)
# define COUT std::cout
# define ENDL std::endl
# define CHN_TRUE (1)
# define CHN_FALSE (0)
# define CHN_DEFAULT_NAME ("Unknown")
# define CHN_DEFAULT_TOPIC ("No topic is set")
# define CHN_DEFAULT_MODE (0)
# define CHN_EXCEPTION_HANDLER() 		\
	catch(const std::exception &e) 		\
	{\
		std::cerr << e.what() << '\n'; \
	}\

# define CHN__ISMODESET(mode,optCtrl) ({						\
	if ((optCtrl)) 												\
	{															\
		returnCode = (_mode == (1 << ((mode) - (1)))) ? 1 : 0;	\
		break ;													\
	}															\
	returnCode = _mode &(1 << ((mode) - (1)));					\
	break;														\
	})															\

typedef enum e_chn_action
{
	USR_ADD = 0,
	USR_REMOVE,
	/*Max*/
	MAX_ACTION
}	t_chn_action;


typedef enum e_chnOptionCtrl
{
	CHN_OPT_CTRL_NotExclusive,
	CHN_OPT_CTRL_Exclusive
}	t_chnOptionCtrl;


typedef enum e_chn_return
{
	CHN_ERR_FAILED = -127,
	CHN_ERR_InvalidNbrOfUsers,
	CHN_ERR_UserDoesNotExist,
	CHN_ERR_InvalidMode,
	CHN_ERR_SUCCESS = 0,
}	t_chn_return;

typedef enum e_chn_mode
{
	CHN_MODE_Default,
	CHN_MODE_Invite,            // _mode value = 1
	CHN_MODE_Protected,         // _mode value = 2
	CHN_MODE_CustomUserLimit, 	// _mode value = 4
	CHN_MODE_AdminSetTopic,     // _mode value = 8
	CHN_MODE_Max
}	t_chnMode;

class User;

class Channel
{
    private:
        std::string			_channelName;
        std::string			_topic;
		std::string			_password;
        unsigned int		_channelCapacity;
        std::list<User *>	*_invitedUsers;
        std::list<User *>	*_operators;
        std::list<User *>	*_ordinaryUsers;
		uint8_t				_mode;
		
		/**	
		 * ! This method call must be wrapped within try/catch. 
		 * @brief 
		 * This method adds a user to a list of users.
		 * It checks if a user is already in the list before adding user.
		 * An exception is thrown if user already exist in list of user.
		 * Hence, a user cannot be added twice in a list.
		 * @param list_users 
		 * @param user 
		 */
		void	addUserToList(std::list<User *> *list_users, User *user);
		
		/**
		 * ! This method call must be wrapped within try/catch.
		 * @brief 
		 * This method removes a user from a list of users.
		 * It checks if a user is already in the list before removing user.
		 * An exception is thrown if user is not found in list of user.
		 * Hence, a user non-existent in list of user cannot be removed.
		 * @param list_users 
		 * @param user 
		 */
		void	removeUserFromList(std::list<User *> *list_users, User *user);

    public:
    	Channel(std::string name, User *user);	// Parametric constructor
    	~Channel(void);
    
    	/* Getters and Setters */
    	std::string			getChannelName(void) const;
    	std::string			getTopic(void) const;
    	unsigned int		getChannelCapacity(void) const;
    	std::list<User *>	*getListPtrInvitedUsers(void) const;
    	std::list<User *>	*getListPtrOperators(void) const;
    	std::list<User *>	*getListPtrOrdinaryUsers(void) const;
		unsigned int		getNbrofActiveUsers(void) const;
        uint8_t             getMode(void) const;
		std::string			getPassword(void) const;
    	void				setChannelName(std::string name);
    	t_chn_return		setChannelCapacity(unsigned int);
    	void				setTopic(std::string topic);
		t_chn_return		setMode(uint8_t mode);
		void				setPassword(std::string pw);
    
    	/* Methods */
		
		bool				isModeSet(uint8_t mode, t_chnOptionCtrl optCtrl);
		
		/**
		 * @brief 
		 * This method sends messages passed to users in the a channel by
		 * iterating over all user pointers in the _allUser list using
		 * iterators which deference each user pointer and access their file
		 * descriptor to send message to them.
		 *
		 * @param msg std::string
		 */
    	// void	broadcastMsg(std::string msg_org);
		void 	broadcastMsg(std::string msg_org, std::pair<bool, User*> ownUser);



		/**
		 * @brief 
		 * This method checks if a list of users is empty.
		 * It returns true if empty.
		 * It returns false if not empty
		 * 
		 * @param list_users 
		 * @return true 
		 * @return false 
		 */
    	bool	isUserListEmpty(std::list<User *> *list_users);

		
		/**
		 * @brief 
		 * This method checks if a user already exist in a list of users
		 * It returns true if user exist in list.
		 * It returns false if user is not found in list.
		 * @param list_users 
		 * @param user 
		 * @return true 
		 * @return false 
		 */
		bool	isUserInList(std::list<User *> *list_users, User *user);




		/**
		 * @brief 
		 * This method updates the list of users which includes adding and 
		 * removing users from it.
		 * The action arg passed in specifies which update to perform.
		 * @param list_users 
		 * @param user 
		 * @param action 
		 */
    	void	updateUserList(std::list<User *> *list_users, User *user, t_chn_action action);


		/**
		 * @brief 
		 * This method removes all the users stored in a list if the list
		 * is not empty.
		 * 
		 * @param list_users 
		 * @return int 
		 */
		int		emptyUserList(std::list<User *> *list_users);


		/**
		 * @brief 
		 * This methods deallocates the memory allocated for the user list
		 * during the constructor call.
		 * 
		 * @param list_users 
		 */
		void	deallocPtrs(std::list<User *> *list_users);


		/**
		 * @brief 
		 * This methods returns the user pointer after searching a list of
		 * user with the given nickname.
		 * 
		 * @param nickname 
		 * @return User* 
		 */
		User	*fetchUserPtrFromList(std::list<User *> *user_list, \
								      std::string nickname);


		/**
		 * @brief 
		 * This methods checks if a user is in channel. The user is searched
		 * using an iterator to iterate over all users in the channel and
		 * checking for a matched with the nickname passed as argument.
		 * 
		 * @param nickname 
		 * @return User* 
		 */
		User	*isUserInChannel(std::string nickname);


		/**
		 * @brief 
		 * This method demotes a user from operator to ordinary user.
		 * First the user pointer is retrieved from operator list using 
		 * the nickname.
		 * If found, the user is removed from operator list and added to
		 * list of ordinary users.
		 * It returns 0, if successful
		 * It returns -1, on error
		 * ? Note that an exeception would be raised if user is already
		 * ? in the list during add operation
		 * 
		 * @param nickname 
		 * @return t_chn_return 
		 */
		t_chn_return	demoteUser(std::string nickname);
		 

		
		/**
		 * @brief 
		 * This method promotes a user from ordinary user to operator.
		 * First the user pointer is retrieved from operator list using 
		 * the nickname.
		 * If found, the user is removed from operator list and added to
		 * list of ordinary users.
		 * It returns 0, if successful
		 * It returns -1, on error
		 * ? Note that an exeception would be raised if user is already
		 * ? in the list during add operation
		 * 
		 * @param nickname 
		 * @return t_chn_return 
		 */
		t_chn_return	promoteUser(std::string nickname);
		
		/**
		 * @brief 
		 * This method is checking if password is equivalent 
		 * to the channel pw.
		 * Return 1 if its equivalent.
		 * Return 0 pw is wrong.
		 * 
		 * @param pw 
		 * @return bool
		 */
		bool			checkPassword(std::string pw);
		
		/**
		 * @brief 
		 * If pw is equivalent to channel pw, delete the password from the channel
		 * Return 1 if the password is removed
		 * Return 0 if pw is'nt equivalent with channel pw
		 * 
		 * @param pw
		 * @return bool
		 */
		bool			remPassword(std::string pw);


		/* Nested class for execeptions */
		 class NullPointerException : public std::exception
        {
            virtual char const *what() const throw()
            {
                return ("\nError: null pointer : channel class\n");
            }
        };

		class InvalidActionException : public std::exception
		{
			virtual char const *what() const throw()
			{
				return ("\nError! Invalid channel action : channel class\n"); 
			}
		};

		class UsrExistException : public std::exception
		{
			virtual char const *what() const throw()
			{
				return ("\nError! User already exist in channel list : channel class\n");
			}
		};

		class UsrNotFoundException : public std::exception
		{
			virtual char const *what() const throw()
			{
				return ("\nError! User is not found in channel list : channel class\n");
			}
		};

		class EmptyContentException : public std::exception
		{
			virtual char const *what() const throw()
			{
				return ("\nError! String is empty : channel class.\n");
			}
		};
		
		class InvalidNbrOfUsersException : public std::exception
		{
			virtual char const *what() const throw()
			{
				return ("\nError! Invalid number of user specified : channel class.\n");
			}
		};

		class InvalidChannelModeException : public std::exception
		{
			virtual char const *what() const throw()
			{
				return ("\nError! Invalid channel mode give : Channel class\n");
			}
		};
};

#endif
