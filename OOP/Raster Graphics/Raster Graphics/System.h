#pragma once
#include <iostream>
#include <vector>
#include "Session.h"

class System
{
public:
	static System& i();
	System(const System&) = delete;
	void operator=(const System&) = delete;
	~System();

	void printHelp() const;

	void run();

private:
	System();

	std::vector<Session> sessions;

	void readImages(Session& currentSession);
};