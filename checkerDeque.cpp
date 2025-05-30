#include <iostream>
#include <string>
#include <limits>
#include "headers/Deque.h"


using namespace std;


template <typename T>
void testDeque() {
    Deque<T> deque;
    cout << "Testing Deque" << "\n";
    
    while (true) {
        cout << "\nOperations:\n"
                  << "1. push_front\n"
                  << "2. push_back\n"
                  << "3. pop_front\n"
                  << "4. pop_back\n"
                  << "5. get_front\n"
                  << "6. get_back\n"
                  << "7. get_size\n"
                  << "8. Exit\n"
                  << "Choose operation: ";
        
        int choice;
        cin >>  choice;
        
        try {
            switch (choice) {
                case 1: {
                    T value;
                    cout << "Enter value: ";
                    cin >>  value;
                    deque.push_front(value);
                    cout << "Value pushed to front\n";
                    break;
                }
                case 2: {
                    T value;
                    cout << "Enter value: ";
                    cin >>  value;
                    deque.push_back(value);
                    cout << "Value pushed to back\n";
                    break;
                }
                case 3:
                    deque.pop_front();
                    cout << "Front element popped\n";
                    break;
                case 4:
                    deque.pop_back();
                    cout << "Back element popped\n";
                    break;
                case 5:
                    cout << "Front element: " << deque.get_front() << "\n";
                    break;
                case 6:
                    cout << "Back element: " << deque.get_back() << "\n";
                    break;
                case 7:
                    cout << "Size: " << deque.get_size() << "\n";
                    break;
                case 8:
                    return;
                default:
                    cout << "Invalid choice\n";
            }
        } catch (const std::exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }
}

template <typename T>
void testStack() {
    Stack<T> stack;
    cout << "Testing Stack" << "\n";
    
    while (true) {
        cout << "\nOperations:\n"
                  << "1. push\n"
                  << "2. pop\n"
                  << "3. top\n"
                  << "4. size\n"
                  << "5. is_empty\n"
                  << "6. Exit\n"
                  << "Choose operation: ";
        
        int choice;
        cin >>  choice;
        
        try {
            switch (choice) {
                case 1: {
                    T value;
                    cout << "Enter value: ";
                    cin >>  value;
                    stack.push(value);
                    cout << "Value pushed\n";
                    break;
                }
                case 2:
                    stack.pop();
                    cout << "Element popped\n";
                    break;
                case 3:
                    cout << "Top element: " << stack.top() << "\n";
                    break;
                case 4:
                    cout << "Size: " << stack.size() << "\n";
                    break;
                case 5:
                    cout << "Is empty: " << (stack.is_empty() ? "true" : "false") << "\n";
                    break;
                case 6:
                    return;
                default:
                    cout << "Invalid choice\n";
            }
        } catch (const std::exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }
}

template <typename T>
void testQueue() {
    Queue<T> queue;
    cout << "Testing Queue" << "\n";
    
    while (true) {
        cout << "\nOperations:\n"
                  << "1. push\n"
                  << "2. pop\n"
                  << "3. front\n"
                  << "4. back\n"
                  << "5. size\n"
                  << "6. is_empty\n"
                  << "7. Exit\n"
                  << "Choose operation: ";
        
        int choice;
        cin >>  choice;
        
        try {
            switch (choice) {
                case 1: {
                    T value;
                    cout << "Enter value: ";
                    cin >>  value;
                    queue.push(value);
                    cout << "Value pushed\n";
                    break;
                }
                case 2:
                    queue.pop();
                    cout << "Element popped\n";
                    break;
                case 3:
                    cout << "Front element: " << queue.front() << "\n";
                    break;
                case 4:
                    cout << "Back element: " << queue.back() << "\n";
                    break;
                case 5:
                    cout << "Size: " << queue.size() << "\n";
                    break;
                case 6:
                    cout << "Is empty: " << (queue.is_empty() ? "true" : "false") << "\n";
                    break;
                case 7:
                    return;
                default:
                    cout << "Invalid choice\n";
            }
        } catch (const std::exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }
}

template <typename T>
void testPriorityQueue() {
    PriorityQueue<T> pq;
    cout << "Testing PriorityQueue" << "\n";
    
    while (true) {
        cout << "\nOperations:\n"
                  << "1. push\n"
                  << "2. pop\n"
                  << "3. top\n"
                  << "4. topPriority\n"
                  << "5. topPair\n"
                  << "6. size\n"
                  << "7. is_empty\n"
                  << "8. Exit\n"
                  << "Choose operation: ";
        
        int choice;
        cin >>  choice;
        
        try {
            switch (choice) {
                case 1: {
                    T value;
                    int priority;
                    cout << "Enter value: ";
                    cin >>  value;
                    cout << "Enter priority: ";
                    cin >>  priority;
                    pq.push(value, priority);
                    cout << "Value pushed with priority " << priority << "\n";
                    break;
                }
                case 2:
                    pq.pop();
                    cout << "Top element popped\n";
                    break;
                case 3:
                    cout << "Top element: " << pq.top() << "\n";
                    break;
                case 4:
                    cout << "Top priority: " << pq.topPriority() << "\n";
                    break;
                case 5: {
                    auto pair = pq.topPair();
                    cout << "Top pair: (" << pair.first << ", " << pair.second << ")\n";
                    break;
                }
                case 6:
                    cout << "Size: " << pq.size() << "\n";
                    break;
                case 7:
                    cout << "Is empty: " << (pq.empty() ? "true" : "false") << "\n";
                    break;
                case 8:
                    return;
                default:
                    cout << "Invalid choice\n";
            }
        } catch (const std::exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    while (true) {
        cout << "\nMain Menu:\n"
                  << "1. Test Deque\n"
                  << "2. Test Stack\n"
                  << "3. Test Queue\n"
                  << "4. Test PriorityQueue\n"
                  << "5. Exit\n"
                  << "Choose option: ";
        
        int mainChoice;
        cin >>  mainChoice;
        
        if (mainChoice == 5) break;
        
        cout << "\nChoose data type:\n"
                  << "1. int\n"
                  << "2. double\n"
                  << "3. string\n"
                  << "Choose type: ";
        
        int typeChoice;
        cin >>  typeChoice;
        
        clearInputBuffer();
        
        try {
            switch (mainChoice) {
                case 1:
                    if (typeChoice == 1) testDeque<int>();
                    else if (typeChoice == 2) testDeque<double>();
                    else if (typeChoice == 3) testDeque<std::string>();
                    else cout << "Invalid type choice\n";
                    break;
                case 2:
                    if (typeChoice == 1) testStack<int>();
                    else if (typeChoice == 2) testStack<double>();
                    else if (typeChoice == 3) testStack<std::string>();
                    else cout << "Invalid type choice\n";
                    break;
                case 3:
                    if (typeChoice == 1) testQueue<int>();
                    else if (typeChoice == 2) testQueue<double>();
                    else if (typeChoice == 3) testQueue<std::string>();
                    else cout << "Invalid type choice\n";
                    break;
                case 4:
                    if (typeChoice == 1) testPriorityQueue<int>();
                    else if (typeChoice == 2) testPriorityQueue<double>();
                    else if (typeChoice == 3) testPriorityQueue<std::string>();
                    else cout << "Invalid type choice\n";
                    break;
                default:
                    cout << "Invalid main choice\n";
            }
        } catch (const std::exception& e) {
            cout << "Exception: " << e.what() << "\n";
        }
    }
    
    return 0;
}