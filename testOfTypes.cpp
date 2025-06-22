#include <iostream>
#include "headers/Deque.h"
#include "headers/Matrix.h"
#include "TYPES.h"

using namespace std;

void Hello(){
    cout << "Hello\n";
}

void Bye(){
    cout << "Bye\n";
}

int main(){
    //проверка основных операций для дека(стек, очередь аналогично проверяется)
    //будет проверен тип Student, Teacher проверяется аналогично, также будет проверена работа с функциями

    cout << "ПРОВЕРКА DEQUE\n";
    //проверка работы с Student
    Person* a = new Student(10, 4, 1000, "A");
    Person* b = new Student(12, 5, 1000, "B");
    Person c;

    //проверка размера
    Deque<Person> * deq = new Deque<Person>();
    deq->push_front(*a);
    deq->push_back(*b);
    cout << deq->get_size() << "\n";

    //проверка get_front, get_back
    c = deq->get_front();
    Print(c);
    c = deq->get_back();
    Print(c);

    //проверка pop back, front 
    deq->pop_front();
    c = deq->get_back();
    Print(c);
    deq->push_front(*a);
    
    deq->pop_back();
    c = deq->get_front();
    Print(c);
    
    //возможность удаления из пустого дека + добавление в пустой дек
    try{
        deq->pop_back();
        deq->pop_back();
    }
    catch( const std::exception &e){
        cout << e.what() << "\n";
    }
    deq->push_back(*a);
    c = deq->get_front();
    Print(c);

    cout <<"\n";
    delete a, b, deq;

    //проверка работы с функциями

    Deque<void(*)()> * dequ = new Deque<void(*)()>();
    void (*hi)() = &Hello;
    void (*bye)() = &Bye;
    void (*fic)();
    //проверка размера

    dequ->push_front(hi);
    dequ->push_back(bye);
    cout << dequ->get_size() << "\n";

    //проверка get_front, get_back
    fic = dequ->get_front();
    fic();
    fic = dequ->get_back();
    fic();

    //проверка pop back, front 
    dequ->pop_front();
    fic = dequ->get_back();
    fic();
    dequ->push_front(hi);
    
    dequ->pop_back();
    fic = dequ->get_front();
    fic();
    
    //возможность удаления из пустого дека + добавление в пустой дек
    try{
        dequ->pop_back();
        dequ->pop_back();
    }
    catch( const std::exception &e){
        cout << e.what() << "\n";
    }
    dequ->push_back(hi);
    fic = dequ->get_front();
    fic();
    delete dequ, bye, hi, fic;

    cout << "\n";


    cout << "ПРОВЕРКА PRIORITY QUEUE\n";
    //проверка приоритентной очереди c Student

    PriorityQueue<Student> *pr = new PriorityQueue<Student>();

    Student *a1 = new Student(1, 2, 1000, "A");
    Student *a2 = new Student(2, 10, 1000, "B");
    Student a3;
    //проверка размера
    pr->push(*a1, 1);
    pr->push(*a2, 2);
    cout << pr->size() <<"\n";

    //проверка top, toppriority
    cout << pr->topPriority() << "\n";
    a3 = pr->top();
    Print(a3);

    //проверка pop

    pr->pop();
    cout << pr->topPriority() << "\n";
    pr->pop();
    try{
        pr->pop();
    }
    catch(const std::exception &e){
        cout << e.what() << "\n";
    }
    pr->push(*a1, 10);
    cout << pr->topPriority() << "\n";
    a3 = pr->top();
    Print(a3);

    cout << "\n";

    delete pr, a1, a2;
    //проверка работы с функциями


    PriorityQueue<void(*)()> *p = new PriorityQueue<void(*)()>();

    void (*HI)() = &Hello;
    void (*BYE)() = &Bye;
    void (*fi)();

    //проверка push, size
    p->push(HI, 1);
    p->push(BYE, 3);
    cout << p->size() << "\n";

    // проверка top, toppriority
    cout << p->topPriority() << "\n";
    fi = p->top();
    fi();


    //проверка pop

    p->pop();
    cout << p->topPriority() << "\n";
    p->pop();
    try{
        p->pop();
    }
    catch(const std::exception &e){
        cout << e.what() << "\n";
    }
    p->push(BYE, 8);

    cout << p->topPriority() << "\n";
    fi = p->top();
    fi();

    delete p, fi, HI, BYE;
}
