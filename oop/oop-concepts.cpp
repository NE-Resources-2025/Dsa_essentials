#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Am going to use Animal as the base class to demonstrate OOP
class Animal {
    protected:
        string name;
        int age;

    public:
    Animal(string name, int age) : name(name), age(age) {}

    virtual void makeSound() const = 0; // Pure virtual function (abstract method)

    string getName() const { return name; } //encapsulation

    int getAge() const { return age; }
};

class Dog : public Animal {
    public:
    Dog(string name, int age) : Animal (name, age) {}

    void makeSound() const override {
        cout << "Woof! Woof!" << endl;
    }
};

// Derived class: Cat (Demonstrates Inheritance and Polymorphism)
class Cat : public Animal
{
public:
    Cat(string name, int age) : Animal(name, age) {}

    void makeSound() const override
    { // Overriding makeSound method
        cout << "Meow! Meow!" << endl;
    }
};

// Out utility class is an animal shelter
class AnimalShelter {
    private:
        vector<Animal *> animals;

    public:
    void addAnimal(Animal *animal) {
        animals.push_back(animal);
    }

    void makeAllSounds() const {
        for (const auto &animal: animals) {
            cout << animal->getName() << "says: ";
            animal->makeSound();
        }
    };

    ~AnimalShelter() {
        for (auto animal: animals) {
            delete animal;
        }
    }
};

// Function to demonstrate Compile-time Polymorphism (Function Overloading)
void printInfo(const Animal &animal)
{
    cout << "Animal: " << animal.getName() << ", Age: " << animal.getAge() << endl;
}

void printInfo(const Dog &dog)
{
    cout << "Dog: " << dog.getName() << ", Age: " << dog.getAge() << endl;
}

void printInfo(const Cat &cat)
{
    cout << "Cat: " << cat.getName() << ", Age: " << cat.getAge() << endl;
}

// Main function demonstrating OOP concepts
int main() {
   // Create instances of Dog and Cat
   Dog *dog = new Dog("Buddy", 3);
   Cat *cat = new Cat("Whiskers", 2);

   // Create AnimalShelter and add animals
   AnimalShelter shelter;
   shelter.addAnimal(dog);
   shelter.addAnimal(cat);

   // Demonstrate Encapsulation and Polymorphism
   shelter.makeAllSounds();

   // Demonstrate Compile-time Polymorphism (Function Overloading)
   printInfo(*dog);
   printInfo(*cat);

   // Demonstrate Runtime Polymorphism
   Animal *animalPtr = dog;
   animalPtr->makeSound();

   animalPtr = cat;
   animalPtr->makeSound();

   return 0;
}