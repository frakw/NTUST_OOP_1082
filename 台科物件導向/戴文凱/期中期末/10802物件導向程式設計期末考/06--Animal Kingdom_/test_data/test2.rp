#include <iostream>
#include "Animal.h"
using namespace std;
int main() {

	Cat cat("Cat");
	Crow crow("Crow");
	Duck duck("Duck");
	Pig pig("Pig");
	Fox fox("Fox");

	Mammal* mammals[] = { &pig,&cat,&fox };
	Bird* birds[] = { &crow,&duck };
	for (int i = 0; i < 2; i++)
	{
		birds[i]->history();
		cout << *(birds[i]) << endl;
	}
	for (int i = 0; i < 3; i++)
	{
		mammals[i]->run();
		cout << *(mammals[i]) << endl;
	}
	return 0;
}