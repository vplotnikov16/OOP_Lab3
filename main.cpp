#include <iostream>

using namespace std;

template<typename Type>
class ListNode {
public:
    ListNode<Type> *next;
    ListNode<Type> *prev;
    Type data;

    ListNode(Type data) {
        this->data = data;
        next = nullptr;
        prev = nullptr;
    }
};

template<typename Type>
class List {
private:
    ListNode<Type> *head;
    ListNode<Type> *tail;
    int size;
public:
    List<Type>() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    };

    int getSize() {
        return size;
    }
};

int main() {
    List<int> list;
    return 0;
}
