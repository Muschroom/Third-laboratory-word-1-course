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

    bool operator> (const Person& other){
        return id > other.id;
    }

    bool operator< (const Person& other){
        return id < other.id;
    }

    bool operator==(const Person& other){
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

    int getMoney(){
        return money;
    }
    ~Student() = default;
};

class Teacher: public Person{
private:
    int numberOfPublications;
public:
    Teacher(int age, int id, int number, std::string name): Person(age, id, name), numberOfPublications(number){};
    Teacher() = default;

    int getNumberOfPublications(){
        return numberOfPublications;
    }

    ~Teacher() = default;
};

void Print(Person& other){
    std::cout <<"Age: " << other.getAge() <<"\n";
    std::cout <<"Id: " << other.getId() <<"\n";
    std::cout <<"Name: "<<other.getName() <<"\n";
}
