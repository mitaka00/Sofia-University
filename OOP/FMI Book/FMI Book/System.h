#include <string>

class System
{
public:
	static System& i();
	System(const System&) = delete;
	void operator=(const System&) = delete;
	~System();

	void run();
	void printHelp() const;

private:
	System();
};

