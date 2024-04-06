#include <iostream>
#include <chrono>

using namespace std;

template<typename Type>
class ListNode {
public:
    ListNode<Type> *next;
    ListNode<Type> *prev;
    Type data;

    ListNode(Type data) : data(data), next(nullptr), prev(nullptr) {}
};

template<typename Type>
class List {
private:
    ListNode<Type> *head;
    ListNode<Type> *tail;
    ListNode<Type> *current;
    int _size;

public:
    List() {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
        _size = 0;
    }

    ~List() {
        clear();
    }

    void push_front(Type element) {
        ListNode<Type> *node = new ListNode<Type>(element);
        if (head == nullptr) {
            head = tail = node;
        } else {
            node->next = head;
            head->prev = node;
            head = node;
        }
        _size++;
    }

    void push_back(Type element) {
        ListNode<Type> *node = new ListNode<Type>(element);
        if (head == nullptr) {
            head = tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        _size++;
    }

    void pop_front() {
        if (head == nullptr) return;
        ListNode<Type> *temp = head;
        head = head->next;
        if (head != nullptr) head->prev = nullptr;
        else tail = nullptr;
        if (current == temp) current = head;
        delete temp;
        _size--;
    }

    void pop_back() {
        if (tail == nullptr) return;
        ListNode<Type> *temp = tail;
        tail = tail->prev;
        if (tail != nullptr) tail->next = nullptr;
        else head = nullptr;
        if (current == temp) current = nullptr;
        delete temp;
        _size--;
    }

    void first() {
        current = head;
    }

    void last() {
        current = tail;
    }

    Type get_current() {
        if (eol()) return Type();
        return current->data;
    }

    void erase() {
        if (current == nullptr) return;
        if (current == head) {
            pop_front();
        } else if (current == tail) {
            pop_back();
        } else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            ListNode<Type> *temp = current;
            current = current->next;
            delete temp;
            _size--;
        }
    }

    void insert(Type element) {
        ListNode<Type> *node = new ListNode<Type>(element);
        if (current == nullptr) { // If inserting when current is beyond the end
            push_back(element);
        } else {
            node->next = current;
            node->prev = current->prev;
            if (current->prev != nullptr) current->prev->next = node;
            current->prev = node;
            if (current == head) head = node;
            _size++;
        }
    }

    void clear() {
        while (head != nullptr) {
            pop_front();
        }
        current = nullptr;
    }

    bool eol() {
        return current == nullptr;
    }

    int size() {
        return _size;
    }

    void next() {
        if (current != nullptr) current = current->next;
    }

    void prev() {
        if (current != nullptr && current->prev != nullptr) current = current->prev;
    }
};


class Triangle {
protected:
    double a, b, c;
public:
    Triangle() {
        //printf("Triangle()\n");
        a = 3, b = 4, c = 5;
    }

    Triangle(double a, double b, double c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }

    ~Triangle() {
        //printf("~Triangle()\n");
    }

    double perimeter() {
        return a + b + c;
    }

};

class RightTriangle : public Triangle {
public:
    RightTriangle() {
        //printf("RightTriangle()\n");
        a = b = c = 3;
    }

    RightTriangle(double a) {
        //printf("RightTriangle(double a)\n");
        this->a = a;
        this->b = a;
        this->c = a;
    }

    ~RightTriangle() {
        //printf("~RightTriangle()\n");
    }

    double perimeter() {
        return 3 * a;
    }
};

void foo(int n) {
    List<Triangle *> *triangles = new List<Triangle *>;
    for (int i = 0; i < n / 2; i++) triangles->push_back(new Triangle());
    for (int i = n / 2; i < n; i++) triangles->push_back(new RightTriangle());
    delete triangles;
}

double bar(int n) {
    List<Triangle *> *triangles = new List<Triangle *>;
    for (int i = 0; i < n / 2; i++) triangles->push_back(new Triangle());
    for (int i = n / 2; i < n; i++) triangles->push_back(new RightTriangle());
    double acc = 0;
    for (triangles->first(); !triangles->eol(); triangles->next()) acc += triangles->get_current()->perimeter();
    return acc;
}

int main() {
    auto start = chrono::high_resolution_clock::now();
    foo(100);
    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> delta = finish - start;
    printf("(foo 100): %f\n", delta.count());

    start = chrono::high_resolution_clock::now();
    foo(1000);
    finish = chrono::high_resolution_clock::now();
    delta = finish - start;
    printf("(foo 1000): %f\n", delta.count());

    start = chrono::high_resolution_clock::now();
    foo(10000);
    finish = chrono::high_resolution_clock::now();
    delta = finish - start;
    printf("(foo 10000): %f\n\n", delta.count());


    start = chrono::high_resolution_clock::now();
    double acc = bar(100);
    finish = chrono::high_resolution_clock::now();
    delta = finish - start;
    printf("(bar 100) {acc = %f}: %f\n", acc, delta.count());

    start = chrono::high_resolution_clock::now();
    acc = bar(1000);
    finish = chrono::high_resolution_clock::now();
    delta = finish - start;
    printf("(bar 1000) {acc = %f}: %f\n", acc, delta.count());

    start = chrono::high_resolution_clock::now();
    acc = bar(10000);
    finish = chrono::high_resolution_clock::now();
    delta = finish - start;
    printf("(bar 10000) {acc = %f}: %f\n", acc, delta.count());

    return 0;
}
