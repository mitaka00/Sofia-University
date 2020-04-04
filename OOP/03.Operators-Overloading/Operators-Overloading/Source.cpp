#include <iostream>
#include "Virus.h"
using namespace std;
int main() {
	Virus firstVirus(5, "korona");
	Virus secondVirus(2, "grip");

	cout << (firstVirus < secondVirus);

	return 0;
}