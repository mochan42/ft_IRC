#include <../inc/user.hpp>

int main()
{
    User user1(5, 5159024057);
	std::string command = "PRIVMSG";
	std::vector<std::string> args;
	args.push_back("channel1");
	args.push_back(":Message");
	user1.executeCommand(command, args);
    return (0);
}