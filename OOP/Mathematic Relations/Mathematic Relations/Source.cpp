#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include "BinaryRelation.h"
#include "KnowledgeBase.h"

using std::cout;

int main() {
	//BinaryRelation examples
	BinaryRelation<int,const char*> test1;
	test1.addRelation(5, "five");
	test1.addRelation(5, "funf");
	test1.addRelation(6, "six");
	test1.addRelation(7, "seven");
	test1.addRelation(8, "eight");
	test1.addRelation(9, "nine");
	test1.addRelation(10, "ten");

	BinaryRelation<int, const char*> test2;
	test2.addRelation(15, "fifteen");
	test2.addRelation(5, "five");

	BinaryRelation<const char*, const char*> test3;
	test3.addRelation("five", "pet");
	test3.addRelation("funf", "pett");
	test3.addRelation("six", "6");
	test3.addRelation("two", "dve");
	test3.addRelation("three", "tri");

	cout << "test1= " << test1; //print test1
	cout << "test2= " << test2; //print test2
	cout << "test3= " << test3; //print test3
	cout << "test1+test= " << test1 + test2; // print test1 + test2
	cout << "test1^test2= " << (test1 ^ test2); // print test1 ^ test2
	cout << "test1*test3= " << test1 * test3; // print test1 * test3
	cout << "test1= " << test1; // print test1
	cout << "!test1= " << !test1; //print !test1

	if (test1(5, "five")) {
		cout << "test1 relation contain (5,\"five\")\n"; //check ()operator
	}
	if (!test1(17, "seventeen")) {
		cout << "test1 relation doesn't contain (17,\"seventeen\")\n"; //check ()operator
	}

	//check injection method
	if (test1.injection()) {
		cout << "test1 is injectable function\n"; 
	}
	else {
		cout << "test1 is not an injectable function\n";
	}

	//check function method
	if (test1.function()) {
		cout << "test1 is a partial function\n";
	}
	else {
		cout << "test1 is not a partial function\n";
	}

	std::vector<int> firstParamArray;
	std::vector<const char*> secondParamArray;

	firstParamArray = test1.dom();
	secondParamArray = test1.ran();

	//Show .dom() functionality
	cout << "test1.dom()=";
	for (int i = 0; i < firstParamArray.size(); i++)
	{
		cout << firstParamArray[i] << " ";
	}
	cout << std::endl;

	//Show .ran() functionality
	cout << "test1.ran()=";
	for (int i = 0; i < secondParamArray.size(); i++)
	{
		cout << secondParamArray[i] << " ";
	}
	cout << std::endl;

	//Show (U u) functionality
	firstParamArray = test1("five");
	cout << "test1(\"five\")=";
	for (int i = 0; i < firstParamArray.size(); i++)
	{
		cout << firstParamArray[i] << " ";
	}
	cout << std::endl;

	//Show [T t] functionality
	secondParamArray = test1[5];
	cout << "test1[5]=";
	for (int i = 0; i < secondParamArray.size(); i++)
	{
		cout << secondParamArray[i] << " ";
	}
	cout << std::endl;
	cout << std::endl;

	//Show KnowledgeBase logic
	BinaryRelation<int, const char*> test4;
	test4.addRelation(10, "ten");
	test4.addRelation(16, "sixteen");

	KnowledgeBase<int, const char*> knowledge1;
	knowledge1.addMember("firstMember", test1);
	knowledge1.addMember("secondMember", BinaryRelation<int, const char*>());

	test4.addRelation(5, "five");
	KnowledgeBase<int, const char*> knowledge2;
	knowledge2.addMember("firstMember", test2);
	knowledge2.addMember("secondMember", test4);
	knowledge2.addMember("thirdMember", BinaryRelation<int, const char*>());


	cout << "knowledge1:\n" << knowledge1;
	cout << "knowledge2:\n" << knowledge2;

	cout << std::endl;
	cout << "knowledge2.addRelation(20 ,\"twenty\")\n";
	knowledge2.addRelation(20, "twenty");
	cout << "knowledge2:\n" << knowledge2;
	
	cout << std::endl;
	cout << "knowledge1+knowledge2:\n" << knowledge1+knowledge2 << std::endl; 
	cout << "knowledge1^knowledge2:\n" << (knowledge1 ^ knowledge2) << std::endl;
	cout << "knowledge1:\n" << knowledge1 << std::endl;
	cout << "!knowledge1:\n" << !knowledge1;

	cout << std::endl;
	BinaryRelation<int, const char*> test5;
	test5 = knowledge1.kb("firstMember");
	cout << "Print relation with name: firstMember in knowledge1:\n" << test5;
	test5 = knowledge1.kb("fifthMember");
	cout << "Print relation with name: fifthMember in knowledge1:\n" << test5;

	cout << std::endl;
	cout << "knowledge1.injection():\n";
	knowledge1.injection();
	cout << "knowledge1.function():\n";
	knowledge1.function();


	cout << std::endl;
	//Show (U u) functionality
	firstParamArray = knowledge1("five");
	cout << "knowledge1(\"five\")=";
	for (int i = 0; i < firstParamArray.size(); i++)
	{
		cout << firstParamArray[i] << " ";
	}
	cout << std::endl;

	//Show [T t] functionality
	secondParamArray = knowledge1[5];
	cout << "knowledge1[5]=";
	for (int i = 0; i < secondParamArray.size(); i++)
	{
		cout << secondParamArray[i] << " ";
	}
	cout << std::endl;

	return 0;
}