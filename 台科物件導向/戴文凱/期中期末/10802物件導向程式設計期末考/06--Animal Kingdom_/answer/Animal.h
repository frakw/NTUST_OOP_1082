#pragma once
#include <iostream>
#include <string>
using namespace std;

class Animal
{
public:
	Animal(string inputName)
	{
		this->name = inputName;
	}
	void setName(string inputName)
	{
		this->name = inputName;
	}
	string getName() const
	{
		return this->name;
	}

	friend ostream& operator<<(ostream& os, const Animal* animal)
	{
		return os << "My name is " + animal->getName() + ". I am a " + animal->introduced() + " of " + animal->myKind() + " and " + animal->doTrick() + ", also I make sound like \"" + animal->makeASound() + "\"";
	}
	friend ostream& operator<<(ostream& os, const Animal& animal)
	{
		return os << "My name is " + animal.getName() + ". I am a " + animal.introduced() + " of " + animal.myKind() + " and " + animal.doTrick() + ", also I make sound like \"" + animal.makeASound() + "\"";
	}
	virtual string makeASound() const { return 0; }
	virtual string doTrick() const { return 0; }
	virtual string introduced() const { return 0; }
	virtual string myKind() const { return 0; }
private:
	string name;

};


class Bird : public Animal
{
public:
	Bird(string inputName) :Animal(inputName) {}
	void history() { cout << "I'm a flying dinosaur actually. (fluttering!)" << std::endl; }
	//private:
	string doTrick() const override { return "I can fly"; }
	string myKind() const override { return "Bird"; }
};

class Mammal : public Animal
{
public:
	Mammal(string inputName) :Animal(inputName) {}
	void run() { cout << "As a mammal, I can run. (sweating...)" << std::endl; }
	//private:
	string doTrick() const override { return "I can jump"; }
	string myKind() const override { return "Mammal"; }
};

class Cat : public Mammal
{
public:
	Cat(string inputName) :Mammal(inputName) {}
	//private:
	string makeASound() const override { return "meow"; }
	string introduced() const override { return "Cat"; }
};
class Pig : public Mammal
{
public:
	Pig(string inputName) :Mammal(inputName) {}
	//private:
	string makeASound() const override { return "oink"; }
	string introduced() const override { return "Pig"; }
};
class Fox : public Mammal
{
public:
	Fox(string inputName) :Mammal(inputName) {}
	//private:
	string makeASound() const override { return "Ring-ding-ding-ding-dingeringeding!"; }
	string introduced() const override { return "Fox"; }
};

class Crow : public Bird
{
public:
	Crow(string inputName) :Bird(inputName) {}
	//private:
	string makeASound() const override { return "cah"; }
	string introduced() const override { return "Crow"; }
};
class Duck : public Bird
{
public:
	Duck(string inputName) :Bird(inputName) {}
	//private:
	string makeASound() const override { return "quack"; }
	string introduced() const override { return "Duck"; }
};