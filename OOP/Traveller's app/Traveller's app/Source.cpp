#include <iostream>
#include "System.h"
#include "Destination.h"

int main() {

	System::i().run();

	return 0;
}

	/*
	Date start, end;
	std::cout << "Started date: ";
	std::cin >> start;
	std::cout << start;
	std::cout << std::endl<<"End date: ";
	std::cin >> end;
	Destination test("ime", 5, "comment1",start,end,3);
	test.addImage("image1");
	test.addImage("image2");
}
**/