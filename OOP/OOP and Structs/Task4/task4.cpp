#include <iostream>
using namespace std;
const int MaxStudentName = 30;
const int MaxStudents = 100;
const int MaxGrades = 3;

struct Grade {
	char subject[MaxStudentName];
	double grade;
};

struct Student {
	char name[MaxStudentName];
	int facultyNumber;
	Grade grades[MaxGrades];
};

void inputStudent(Student& student) {
	cout << "name: ";
	cin >> student.name;
	cout << endl << "faceulty number: ";
	cin >> student.facultyNumber;
	cout << endl;
	for (int i = 0; i < MaxGrades; i++)
	{
		cout << "Subject: ";
		cin >> student.grades[i].subject;
		cout << endl << "grade: ";
		cin >> student.grades[i].grade;
		cout << endl;
	}
}

void outputStudent(Student student) {
	cout << "Name: " << student.name << " with faculty number: " << student.facultyNumber << endl;
	for (int i = 0; i < MaxGrades; i++)
	{
		cout << "Subject: " << student.grades[i].subject <<endl;
		cout<<"Grade: "<< student.grades[i].grade << endl;
	}
}

void biggerGrade(Student students[], int length, double grade) {
	int count = 0;
	char subjects[3][MaxGrades];

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < MaxGrades; j++)
		{
			if (students[i].grades[j].grade >= grade) {
				strcpy_s(subjects[count], students[i].grades[j].subject);
				count++;
			}
		}

		cout << students[i].name<<" -> ";
		if (count == 0) {
			cout << "No such subjects";
		}
		else {
			for (int t = 0; t < count; t++)
			{
				cout << subjects[t] << ", ";
			}
		}

		count = 0;
	}
}

int main() {	
	Student students[MaxStudents];
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		inputStudent(students[i]);
	}

	biggerGrade(students, n, 4.50);

	return 0;
}