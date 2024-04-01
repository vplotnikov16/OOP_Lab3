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

    ListNode<Type> *getPNode(const int index) {
        int i = 0;
        ListNode<Type> *current = nullptr;
        if (index > size / 2) {
            current = tail;
            while (i != size - index - 1) {
                current = current->prev;
                i++;
            }
        } else {
            current = head;
            while (i != index) {
                current = current->next;
                i++;
            }
        }
        return current;
    }

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

    void push_front(Type value) {
        ListNode<Type> *node = new ListNode<Type>(value);
        if (size == 0) head = tail = node;
        else {
            node->next = head;
            head->prev = node;
            head = node;
        }
        size++;
    }

    Type &operator[](const int index) {
        return getObject(index);
    }

    Type getObject(int index, bool deleteObject = false) {
        int i = 0;
        ListNode<Type> *current = getPNode(index);
        if (deleteObject) {
            if (current->prev != nullptr) current->prev->next = current->next;
            else head = current->next;

            if (current->next != nullptr) current->next->prev = current->prev;
            else tail = current->prev;

            Type copiedData = Type(current->data);
            delete current;
            size--;
            return copiedData;
        }
        return current->data;
    }

    void insert(const int index, Type data) {
        ListNode<Type> *newNode = new ListNode<Type>(data);
        if (index == 0) {
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        } else if (index == size) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        } else if (0 < index < size) {
            ListNode<Type> *oldNode = getPNode(index);
            oldNode->prev->next = newNode;
            newNode->prev = oldNode->prev;
            newNode->next = oldNode;
            oldNode->prev = newNode;
        } else {
            // Ошибка
        }
        size++;
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
    list.push_front(4);
    list.push_back(-9);
    list.push_back(11);
    cout << list.getObject(3, true) << endl;
    list.print();
    list.insert(2, 10);
    list.print();
    return 0;
}
