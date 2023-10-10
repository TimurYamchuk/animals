#include <iostream>
using namespace std;

class Animal {
public:
    virtual bool IsAlive() const = 0;
};

class Herbivore : public Animal {
public:
    virtual void EatGrass() = 0;
};

class Continent {
public:
    Animal* animals[100];
    int animalCount;

    Continent() : animalCount(0) {}

    void AddAnimal(Animal* animal) {
        if (animalCount < 100) {
            animals[animalCount++] = animal;
        }
    }
};

class Wildebeest : public Herbivore {
private:
    int weight;

public:
    Wildebeest() : weight(50) {}
    
    bool IsAlive() const { return true; }
    void EatGrass() { weight += 10; }
    int GetWeight() const { return weight; }
};

class Bison : public Herbivore {
private:
    int weight;

public:
    Bison() : weight(100) {}
    
    bool IsAlive() const { return true; }
    void EatGrass() { weight += 10; }
    int GetWeight() const { return weight; }
};

class Carnivore : public Animal {
public:
    virtual void Eat(Herbivore* herbivore) = 0;
};

class Lion : public Carnivore {
private:
    int power;

public:
    Lion() : power(100) {}
    
    bool IsAlive() const { return true; }
    void Eat(Herbivore* herbivore) {
        if (power >= herbivore->GetWeight()) {
            power += 10;
        } else {
            power -= 10;
        }
    }
};

class Wolf : public Carnivore {
private:
    int power;

public:
    Wolf() : power(80) {}
    
    bool IsAlive() const { return true; }
    void Eat(Herbivore* herbivore) {
        if (power >= herbivore->GetWeight()) {
            power += 10;
        } else {
            power -= 10;
        }
    }
};

class AnimalWorld {
public:
    void MealsHerbivores(Continent* continent) {
        for (int i = 0; i < continent->animalCount; i++) {
            Herbivore* herbivore = dynamic_cast<Herbivore*>(continent->animals[i]);
            if (herbivore) {
                herbivore->EatGrass();
            }
        }
    }

    void NutritionCarnivores(Continent* continent) {
        for (int i = 0; i < continent->animalCount; i++) {
            Carnivore* carnivore = dynamic_cast<Carnivore*>(continent->animals[i]);
            if (carnivore) {
                for (int j = 0; j < continent->animalCount; j++) {
                    Herbivore* herbivore = dynamic_cast<Herbivore*>(continent->animals[j]);
                    if (herbivore) {
                        carnivore->Eat(herbivore);
                    }
                }
            }
        }
    }
};

int main() {
    Continent africa;
    africa.AddAnimal(new Wildebeest());
    africa.AddAnimal(new Bison());
    africa.AddAnimal(new Lion());
    africa.AddAnimal(new Wolf());

    Continent northAmerica;
    northAmerica.AddAnimal(new Bison());
    northAmerica.AddAnimal(new Wolf());

    AnimalWorld animalWorld;

   
    animalWorld.MealsHerbivores(&africa);
    animalWorld.NutritionCarnivores(&africa);

    animalWorld.MealsHerbivores(&northAmerica);
    animalWorld.NutritionCarnivores(&northAmerica);

    return 0;
}
