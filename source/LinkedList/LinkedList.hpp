#pragma once

#include <iostream>
#include "Node.hpp"
#include "../../Exception.hpp"

using namespace std;

template<class T>
class LinkedList {
private:
    Node<T> *head;
    Node<T> *tail;

public:
    LinkedList(T *items, int size);

    LinkedList();

    LinkedList(const LinkedList<T> &list);

    T GetFirst();

    T GetLast();

    T Get(int index);

    LinkedList<T> *GetSubList(int start_index, int end_index);

    int GetLength();

    void Prepend(T item);

    void Append(T item);

    void InsertAt(T item, int index);

    void RemoveAt(const int index);

    void Remove(T value);

    void RemoveAll(T value);

    LinkedList<T> *Concat(LinkedList<T> *list);
};

template<class T>
LinkedList<T>::LinkedList(T *items, int size) {
    if (size < 1) {
        throw new Exception;
    }

    Node<T> *tmp = new Node<T>(items[0]);

    head = tmp;

    for (int i = 1; i < size; ++i) {
        Node<T> *cur = new Node<T>(items[i]);
        tmp->next = cur;

        tmp = cur;
    }

    tail = tmp;
}

template<class T>
LinkedList<T>::LinkedList() {
    this->head = NULL;
    this->tail = NULL;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &list) {
    if (!list.head) {
        throw new Exception;
    }

    Node<T> *src = list.head;
    Node<T> *tmp = new Node<T>(*(src->value));

    head = tmp;
    src = src->next;

    while (src) {
        tmp->next = new Node<T>(*(src->value));
        tmp = tmp->next;

        src = src->next;
    }

    tail = tmp;
}

template<class T>
T LinkedList<T>::GetFirst() {
    if (!this->head) {
        throw new Exception;
    }
    return *(this->head->value);
}

template<class T>
T LinkedList<T>::GetLast() {
    if (!this->tail) {
        throw new Exception;
    }
    return *(this->tail->value);
}

template<class T>
T LinkedList<T>::Get(int index) {
    if (index < 0 || index >= this->GetLength()) {
        throw new Exception;
    }

    if (!head) {
        throw new Exception;
    }

    int cur_index = 0;

    Node<T> *cur = this->head;
    while (cur) {
        if (index == cur_index) {
            return *(cur->value);
        }

        cur = cur->next;
        cur_index++;
    }

    return 0;
}

template<class T>
LinkedList<T> *LinkedList<T>::GetSubList(int start_index, int end_index) {
    if (!head) {
        throw new Exception;
    }

    if (start_index > end_index || start_index < 0) {
        throw new Exception;
    }

    LinkedList<T> *subList = new LinkedList<T>();

    int cur_index = 0;
    Node<T> *cur = this->head;

    while (cur_index != start_index) {
        cur = cur->next;
        cur_index++;
    }

    while (cur_index < end_index) {
        subList->Append(*(cur->value));
        cur = cur->next;
        cur_index++;
    }

    return subList;
}

template<class T>
int LinkedList<T>::GetLength() {
    if (!head) {
        throw new Exception;
    }

    int len = 0;
    Node<T> *cur = this->head;

    while (cur) {
        cur = cur->next;
        len++;
    }

    return len;
}

template<class T>
void LinkedList<T>::Prepend(T item) {
    Node<T> *node = new Node<T>(item);

    if (!head) {
        head = node;
        tail = node;

        return;
    }

    node->next = this->head;
    this->head = node;
}

template<class T>
void LinkedList<T>::Append(T item) {
    Node<T> *node = new Node<T>(item);

    if (!head) {
        head = node;
        tail = node;

        return;
    }

    tail->next = node;
    this->tail = node;
}

template<class T>
void LinkedList<T>::InsertAt(T item, int index) {
    if (index < 0 || index > this->GetLength()) {
        throw new Exception;
    }

    if (index == 0 || !head) {
        this->Prepend(item);
        return;
    }

    if (index == this->GetLength()) {
        this->Append(item);
        return;
    }

    int cur_index = 0;
    Node<T> *node = new Node<T>(item);
    Node<T> *cur = this->head;

    while (cur_index != index - 1) {
        cur = cur->next;
        cur_index++;
    }

    node->next = cur->next;
    cur->next = node;

    return;
}

template<class T>
void LinkedList<T>::RemoveAt(const int index) {
    if (index < 0 || index >= this->GetLength() || !head) {
        throw new Exception;
    }

    if (this->GetLength() == 1) {
        this->head = NULL;
        this->tail = NULL;

        return;
    }

    if (index == 0) {
        this->head = this->head->next;
        return;
    }

    if (index == this->GetLength() - 1) {
        Node<T> *cur = this->head;

        while (cur->next->next) {
            cur = cur->next;
        }

        cur->next = NULL;
        this->tail = cur;

        return;
    }

    int cur_index = 0;
    Node<T> *cur = this->head;

    while (cur_index != index - 1) {
        cur = cur->next;
        cur_index++;
    }

    cur->next = cur->next->next;
}

template<class T>
void LinkedList<T>::Remove(T value) {
    Node<T> *cur = this->head->next;
    Node<T> *prev = this->head;

    if (*(prev->value) == value) {
        if (this->GetLength() == 1) {
            this->head = NULL;
            this->tail = NULL;
            return;
        }

        this->head = cur;
        return;
    }

    while (cur) {
        if (*(cur->value) == value) {
            prev->next = cur->next;
            if (!cur->next) {
                this->tail = prev;
            }

            return;
        }

        cur = cur->next;
        prev = prev->next;
    }
}

template<class T>
void LinkedList<T>::RemoveAll(T value) {
    Node<T> *cur = this->head->next;
    Node<T> *prev = this->head;

    while (*(prev->value) == value) {
        if (this->GetLength() == 1) {
            this->head = NULL;
            this->tail = NULL;
            return;
        }

        this->head = cur;
        cur = cur->next;
        prev = prev->next;
    }

    while (cur) {
        if (*(cur->value) == value) {
            prev->next = cur->next;
            if (!cur->next) {
                this->tail = prev;
            }

        }

        cur = cur->next;
        if (prev->next != cur) {
            prev = prev->next;
        }
    }
}

template<class T>
LinkedList<T> *LinkedList<T>::Concat(LinkedList<T> *list) {
    LinkedList<T> *newList = new LinkedList(*this);

    Node<T> *cur = list->head;
    while (cur) {
        newList->Append(*(cur->value));
        cur = cur->next;
    }

    return newList;
}
