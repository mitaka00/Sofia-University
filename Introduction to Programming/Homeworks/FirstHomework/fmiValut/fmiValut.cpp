#include <iostream>
using namespace std;
int main() {
	int input;
	cout << "number= ";
	cin >> input;

	if (input / 100000000 < 1 || input / 100000000 >= 10) {
		cout << "Invalid input"<<endl; //Проверка за 9 цифрено число
		return 0;
	}

	int cardVersion = input / 100000000;
	int specialityNum = input / 1000000 % 10;

	int identificator = input % 1000000 / 10;

	if (identificator == 0 || specialityNum == 7 || specialityNum==9) {
		cout << "Invalid card number"<<endl;
	}
	else {
		cout << "{ \"card_version\": " << cardVersion << ", \"owner_spec\": \"";
		switch (specialityNum)
		{
		case 0:
			cout << "Informatics";
			break;
		case 1:
			cout<< "Computer Sciences";
			break;
		case 2:
			cout << "Information Systems";
			break;
		case 3:
			cout << "Software Engineering";
			break;
		case 4:
			cout<< "Applied Mathematics";
			break;
		case 5:
			cout << "Mathematics";
			break;
		case 6:
			cout << "Statistics";
			break;
		case 8:
			cout << "Mathematics and Informatics";
			break;
		case 9:
			cout<< "Informatics";
			break;
		default:
			break;
		}
		cout << "\", \"owner_id\": " << identificator << " }" << endl;
	}
	return 0;
}