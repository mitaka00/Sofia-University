#include <string>
#include <vector>
#include "User.h"
#include "Admin.h"
#include "Moderator.h"
#include "Post.h"
#include "postImage.h"
#include "postLink.h"
#include "PostText.h"

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
	void showInfo() const;
	int checkUser(const string& name)const;
	

private:
	System();
	std::vector<User*> users;

	void blockUser(const std::vector<string>& token);
	void unblockUser(const std::vector<string>& token);
	void renameUser(const std::vector<string>& token);
	void createUser(const std::vector<string>& token);
	void removeUser(const std::vector<string>& token);
	void postImage(const std::vector<string>& token);
	void postText(const std::vector<string>& token);
	void postLink(const std::vector<string>& token);
	void removePost(const std::vector<string>& token);
	void viewPost(const std::vector<string>& token) const;
	void viewAllPosts(const std::vector<string>& token) const;

	//Helper functions
	void printUserInfo(const int index) const;
	void checkYoungestAndOldestInfo(int index,int& oldestIndex,int& youngestIndex) const;
	std::vector<string> split(const string& s, char delim);
};

