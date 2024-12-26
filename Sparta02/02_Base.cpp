#include <iostream>
using namespace std;

class Animal {
public: 
    virtual void makeSound() = 0; 
    virtual ~Animal() {} 
};

class Dog : public Animal {
public:
    void makeSound()  override {
        cout << "Woof Woof!" << endl;
    }
};

class Cat : public Animal {
public:
    void makeSound()  override {
        cout << "Meow Meow!" << endl;
    }
};

class Cow : public Animal {
public:
    void makeSound()  override {
        cout << "Moo Moo!" << endl;
    }
};

/*
int main(void)
{
    Animal* Animals[] = {new Dog(), new Cat(), new Cow};

    for (int i = 0; i< sizeof(Animals)/sizeof(Animals[0]); i++)
    {
        Animals[i]->makeSound();
    }
    return 0;
}
*/