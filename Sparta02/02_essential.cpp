#include <iostream>
#include <cstdlib>
#include <ctime>

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

class Zoo
{
private:
    Animal* animals[10] = {nullptr,};
    int count = 0;
public:
    void addAnimal(Animal* animal)
    {
        if (count < 10)
        {
            animals[count] = animal;
            count++;
        }
    }

    void performActions()
    {
        for (int i = 0; i < count; i++)
        {
            animals[i]->makeSound();
        }
    }
    ~Zoo()
    {
        for (int i = 0; i < count; ++i) {
            delete animals[i]; // 메모리 해제
            animals[i] = nullptr;
        }
    }
};

Animal* createRandomAnimal()
{
    int random = rand() % 3;

    switch (random)
    {
    case 0:
        return new Dog;
    case 1:
        return new Cat;
    case 2:
        return new Cow;
    default:
        return nullptr;
    }
}
int main(void)
{
    srand(static_cast<unsigned int>(time(0)));
    
    Zoo* zoo = new Zoo;

    for (int i = 0; i < 10; i++)
    {
        zoo->addAnimal(createRandomAnimal());
    }

    zoo->performActions();
    
    return 0;
}
