#pragma once
#include <string>
#include <iostream>
class Person{
private:
    int age;
    int id;
    std::string name;
public:
    Person(int age, int id, std::string name): age(age), id(id), name(name){}
    Person() = default;

    int getId() const{
        return id;
    }

    int getAge() const{
        return age;
    }

    std::string getName() const{
        return name;
    }

    bool operator> (const Person& other) const{
        if(id > other.id) return id > other.id;
        if(age > other.age) return age > other.age;
        return name > other.name;
    }

    bool operator< (const Person& other) const{
        if(id < other.id) return id < other.id;
        if(age < other.age) return age < other.age;
        return name < other.name;
    }

    bool operator==(const Person& other) const{
        return id == other.id && age == other.age && name == other.name;
    }
    
    ~Person() = default;
};


class Student: public Person{
private:
    int money;
public:
    Student(int age, int id, int money, std::string name): Person(age, id, name), money(money){}
    Student() = default;

    int getMoney() const{
        return money;
    }

    bool operator<(const Student & other) const{
        return Person::operator<(other) && money < other.getMoney();
    }

    bool operator>(const Student & other) const{
        return Person::operator>(other) && money > other.getMoney();
    }

    bool operator==(const Student & other) const{
        return Person::operator==(other) && money == other.getMoney();
    }

    ~Student() = default;
};

class Teacher: public Person{
private:
    int numberOfPublications;
public:
    Teacher(int age, int id, int number, std::string name): Person(age, id, name), numberOfPublications(number){};
    Teacher() = default;

    int getNumberOfPublications() const{
        return numberOfPublications;
    }

     bool operator<(const Teacher & other) const{
        return Person::operator<(other) && numberOfPublications < other.getNumberOfPublications();
    }

    bool operator>(const Teacher & other) const{
        return Person::operator>(other) && numberOfPublications > other.getNumberOfPublications();
    }

    bool operator==(const Teacher & other) const{
        return Person::operator==(other) && numberOfPublications == other.getNumberOfPublications();
    }

    ~Teacher() = default;
};

void Print(Person& other){
    std::cout <<"Age: " << other.getAge() <<"\n";
    std::cout <<"Id: " << other.getId() <<"\n";
    std::cout <<"Name: "<<other.getName() <<"\n";
}
