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

    void push_back(Type value) {
        ListNode<Type> *node = new ListNode<Type>(value);
        if (size == 0) head = tail = node;
        else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        size++;
    }

    Type &operator[](const int index) {
        int i = 0;
        if (index > size / 2) {
            ListNode<Type> *current = tail;
            while (i != size - index - 1) {
                current = current->prev;
                i++;
            }
            return current->data;
        } else {
            ListNode<Type> *current = head;
            while (i != index) {
                current = current->next;
                i++;
            }
            return current->data;
        }
    }

    void print(bool reversed = false) const {
        if (!reversed) {
            ListNode<Type> *current = head;
            while (current != nullptr) {
                std::cout << current->data << " ";
                current = current->next;
            }
        } else {
            ListNode<Type> *current = tail;
            while (current != nullptr) {
                cout << current->data << " ";
                current = current->prev;
            }
        }
        std::cout << std::endl;
    }
};

int main() {
    List<int> list;
    list.push_back(0);
    list.push_back(4);
    list.push_back(-9);
    cout << list.getSize() << endl;
    list.push_back(11);
    cout << list[3] << endl;
    list.print();
    list.print(true);
    return 0;
}
