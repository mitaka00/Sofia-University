#include <string>
#include <vector>
#include "User.h"
#include "Admin.h"
#include "Moderator.h"
#include "Post.h"

class System
{
	using string = std::string;
public:
	static System& i();
	System(const System&) = delete;
	void operator=(const System&) = delete;
	~System();

	void run();
	void printHelp() const;
	int checkUser(const string& name)const;

private:
	System();
	std::vector<User*> users;

	void blockUser(std::vector<string> token);
	void unblockUser(std::vector<string> token);
	void renameUser(std::vector<string> token);
	void createUser(std::vector<string> token);
	std::vector<string> split(const string& s, char delim);
};

