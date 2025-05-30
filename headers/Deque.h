#pragma once
#include "sequence/ArraySequence.h"
using namespace std;


template<typename T>
class Deque{
private:
    struct Node
    {
        T value;
        Node* before = nullptr;
        Node* after = nullptr;
    };
    
    int size = 0;
    Node* tail = nullptr;
    Node* head = nullptr;
    
    void checkSize() const{
        if(size == 0){
            throw std::logic_error("Container is empty");
        }
    }

public:
    Deque() = default;

    int get_size() const{
        return size;
    }

    const T& get_front() const{
        checkSize();
        return head->value;
    }

    const T& get_back() const{
        checkSize();
        return tail->value;
    }

    void push_front(T& value){
        if(size == 0){
            Node* node = new Node();
            node->value = value;
            tail = node;
            head = node;
            size = 1;
            return;
        }
        Node* node = new Node();
        node->value = value;
        node->before = head;
        head->after = node;
        head = node;
        size++;
    }

    void push_back(T& value){
        if(size == 0){
            Node* node = new Node();
            node->value = value;
            tail = node;
            head = node;
            size = 1;
            return;
        }
        Node* node = new Node();
        node->value = value;
        node->after = tail;
        tail->before = node;
        tail = node;
        size++;
    }

    void pop_front(){
        checkSize();
        if(size == 1){
            delete head;
            size = 0;
            return;
        }
        if(head != nullptr){
            Node* new_head = head->before;
            delete head;
            head = new_head;
            size--;
        }
    }

    void pop_back(){
        checkSize();
        if(size == 1){
            delete tail;
            size = 0;
            return;
        }
        if(tail != nullptr){
            Node* new_tail = tail->after;
            delete tail;
            tail = new_tail;
            size--;
        }
    }


    ~Deque(){
        Node* next = nullptr;
        Node* now = tail;
    
        while (now != nullptr) {
            next = now->after;
            delete now;
            now = next;
        }
    }
};


template<typename T>
class Queue{
private:
    Deque<T> * queue;
public:
    Queue(): queue(new Deque<T>()){};

    void push(T& value){
        queue->push_front(value);
    }

    const T& front() const {
        return queue->get_front();
    }

    const T& back() const {
        return queue->get_back();
    }

    int size() const {
        return queue->get_size();
    }  

    void pop(){
        return queue->pop_back();
    }

    bool is_empty() const{
        return queue->get_size() == 0;
    }

    ~Queue(){delete queue;}
};


template<typename T>
class Stack{
private:
    Deque<T> * stack;
public:
    Stack(): stack(new Deque<T>()){};

    int size() const{
        return stack->get_size();
    }

    bool is_empty() const{
        return stack->get_size() == 0;
    }

    void push(T& value){
        stack->push_front(value);
    }

    const T& top() const {
        return stack->get_front();
    }

    void pop(){
        stack->pop_front();
    }

    ~Stack(){delete stack;}
};








template <typename T>
class PriorityQueue {
private:
    ArraySequence<std::pair<T, int>>* heap;

    void Up(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if ((*heap)[parent].second >= (*heap)[index].second) {
                break;
            }

            auto temp = (*heap)[index];
            heap->Set(index, (*heap)[parent]);
            heap->Set(parent, temp);
            index = parent;
        }
    }

    void Down(int index) {
        int l, r, max_val;
        while (true) {
            l = 2 * index + 1;
            r = 2 * index + 2;
            max_val = index;

            if (l < heap->GetLength() && (*heap)[l].second > (*heap)[max_val].second)
                max_val = l;
            if (r < heap->GetLength() && (*heap)[r].second > (*heap)[max_val].second)
                max_val = r;

            if (max_val == index) break;

            auto temp = (*heap)[index];
            heap->Set(index, (*heap)[max_val]);
            heap->Set(max_val, temp);

            index = max_val;
        }
    }

    void checkEmpty() const{
        if (empty()) {
            throw std::out_of_range("PriorityQueue is empty");
        }
    }

public:
    PriorityQueue() {
        heap = new MutableArraySequence<std::pair<T, int>>();
    }

    ~PriorityQueue() {
        delete heap;
    }

    bool empty() const {
        return heap->GetLength() == 0;
    }

    int size() const {
        return heap->GetLength();
    }

    void push(T& value, int priority) {
        heap->Append(std::make_pair(value, priority));
        Up(heap->GetLength() - 1);
    }

    T top() {
        checkEmpty();
        return (*heap)[0].first;
    }

    int topPriority(){
        checkEmpty();
        return (*heap)[0].second;
    }

    void pop() {
        checkEmpty();
        if (heap->GetLength() == 1) {
            delete heap;
            heap = new MutableArraySequence<std::pair<T, int>>();
            return;
        }
        heap->Set(0, heap->Get(heap->GetLength() - 1));
        heap = heap->GetSubsequence(0, heap->GetLength() - 2);
        if (!empty()) {
            Down(0);
        }

    }

    std::pair<T, int> topPair()  {
        checkEmpty();
        return (*heap)[0];
    }

};