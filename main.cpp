#include <iostream>

using namespace std;

struct Bomb {
    int weight;
    char color;
    int trotylCount;

    Bomb(int weight, const char color, int trotylCount) :
            weight(weight), color(color), trotylCount(trotylCount) {}

    Bomb() {}

    string toString() {
        return "Bomb with weight: "
               + to_string(weight) + "kg ,color: "
               + color + ", trotyl count: "
               + to_string(trotylCount) + "kg.";
    }

};

struct DynamicArray {
    Bomb *array;
    const double fillIndex;
    int elementsCount = 0;
    int capacity;

    explicit DynamicArray(int baseSize, double fillIndex = 1.5) : array(new Bomb[baseSize]), fillIndex(fillIndex),
                                                                  capacity(baseSize) {}

    void expandArray() {
        capacity = (int) (capacity * fillIndex);
        Bomb *newArray = new Bomb[capacity];
        memcpy(newArray, array, size());
        delete[] array;
        array = newArray;
    }

    void insert(Bomb &bomb, int index) {
        if (index < 0 || index > elementsCount) {
            throw out_of_range("You`ve provided wrong array index");
        }
        if (capacity >= elementsCount) {
            expandArray();
        }
        if (elementsCount == 0) {
            array[0] = bomb;
            elementsCount++;
            return;
        }
        for (int i = elementsCount; i > index; i--) {
            array[i] = array[i - 1];
        }
        array[index] = bomb;
        elementsCount++;
    }

    Bomb remove(int index) {
        if (index < 0 || index >= elementsCount) {
            throw out_of_range("No element in the array under such index");
        }
        Bomb bomb;
        if (elementsCount == 1) {
            bomb = array[index];
            elementsCount = 0;
            return bomb;
        }
        bomb = array[index];
        for (int i = index; i < elementsCount - 1; i++) {
            array[i] = array[i + 1];
        }
        elementsCount--;
        return bomb;
    }

    void push_back(Bomb &bomb) {
        if (elementsCount >= capacity) {
            expandArray();
        }
        array[elementsCount++] = bomb;
    }

    Bomb pop_back() {
        if (size() > 0) {
            Bomb bomb = array[size() - 1];
            elementsCount--;
            return bomb;
        }
        throw out_of_range("Array has no elements");
    }

    Bomb get(int index) {
        if (index < 0 || index >= elementsCount) {
            throw out_of_range("Non-existent index was provided");
        }
        return array[index];
    }

    int size() {
        return elementsCount;
    }

    void print() {
        for (int i = 0; i < size(); i++) {
            cout << array[i].toString() << endl;
        }
    }

    void clear() {
        elementsCount = 0;
        capacity = 0;
        delete[] array;
        array = nullptr;
    }

    void push_front(Bomb &bomb) {
        if (elementsCount >= capacity) {
            expandArray();
        }
        memmove(&array[1], &array[0], elementsCount++);
        array[0] = bomb;
    }

    Bomb pop_front() {
        if (size() > 0) {
            Bomb result = array[0];
            memmove(&array[0], &array[1], --elementsCount);
            return result;
        }
        throw out_of_range("Array has no elements");
    }

    virtual ~DynamicArray() {
        clear();
    }
};

struct Node {
    Node *nextNode;
    Bomb bomb;

};

struct SingleLinkedList {
    Node *head;
    Node *tail;
    int nodesCount = 0;

    SingleLinkedList() : head(nullptr), tail(nullptr) {}

    void insert(Bomb &bomb, int index) {
        if (index < 0 || index > nodesCount) {
            throw out_of_range("You`ve provided wrong list index");
        }
        Node *node = new Node();
        if (nodesCount == 0) {
            head = tail = node;
            node->bomb = bomb;
            node->nextNode = nullptr;
            nodesCount++;
            return;
        } else {
            node->bomb = bomb;
            Node *current = head;
            int i = 0;
            do {
                if (i == index - 1) {
                    node->nextNode = current->nextNode;
                    current->nextNode = node;
                    nodesCount++;
                    return;
                }
                current = current->nextNode;
                i++;
            } while (i < index - 1);
        }
    }

    Bomb remove(int index) {
        if (index >= nodesCount || index < 0) {
            throw out_of_range("No element with such index in the list");
        }
        Bomb bomb;
        Node *current = head;
        Node *prev;
        if (index == 0) {
            if (head == tail) {
                bomb = head->bomb;
                delete head;
                head = nullptr;
                tail = nullptr;
                nodesCount = 0;
            } else {
                prev = head;
                head = head->nextNode;
                bomb = prev->bomb;
                delete prev;
                nodesCount--;
            }
        } else {
            int i = 0;
            do {
                if (i == index - 1) {
                    prev = current;
                    current = current->nextNode;
                    bomb = current->bomb;
                    prev->nextNode = current->nextNode;
                    delete current;
                    nodesCount--;
                    break;
                }
                current = current->nextNode;
                i++;
            } while (i < index - 1);
        }
        return bomb;
    }

    void push_front(Bomb &bomb) {
        Node *node = new Node();
        if (head == nullptr) tail = node;
        node->bomb = bomb;
        node->nextNode = head;
        head = node;
        nodesCount++;
    }

    void push_back(Bomb &bomb) {
        Node *node = new Node();
        if (head == nullptr) {
            tail = node;
            head = node;
        } else {
            tail->nextNode = node;
            tail = node;
        }
        node->bomb = bomb;
        nodesCount++;
    }

    Bomb get(int index) {
        if (index < 0 || index >= nodesCount) {
            throw out_of_range("Non-existent index was provided");
        }
        Node *nextNode = head;
        int i = 0;
        while (nextNode != nullptr) {
            if (i == index) {
                return nextNode->bomb;
            }
            nextNode = nextNode->nextNode;
            i++;
        }
        throw out_of_range("No element with this id in the list");
    }

    Bomb pop_front() {
        if (head == nullptr) {
            throw out_of_range("List has no elements");
        }
        Bomb bomb = head->bomb;
        nodesCount--;
        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
            return bomb;
        }
        Node *temp;
        temp = head;
        head = head->nextNode;
        delete temp;
        return bomb;
    }

    Bomb pop_back() {
        if (tail == nullptr) {
            throw out_of_range("List has no elements");
        }
        Bomb bomb = tail->bomb;
        nodesCount--;
        if (head == tail) {
            delete tail;
            head = nullptr;
            tail = nullptr;
            return bomb;
        }
        Node *nextNode = head;
        Node *temp;
        while (nextNode != nullptr) {
            if (nextNode->nextNode == tail) {
                temp = tail;
                tail = nextNode;
                delete temp;
            }
            nextNode = nextNode->nextNode;
        }
        return bomb;
    }

    int size() {
        return nodesCount;
    }

    void print() {
        Node *nextNode = head;
        while (nextNode != nullptr) {
            cout << nextNode->bomb.toString() << endl;
            nextNode = nextNode->nextNode;
        }
    }

    void clear() {
        if (size() == 0) {
            return;
        }
        Node *nextNode = head;
        Node *temp;
        while (nextNode != nullptr) {
            temp = nextNode;
            nextNode = nextNode->nextNode;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
    }

    virtual ~SingleLinkedList() {
        clear();
    }
};

int main() {
    SingleLinkedList *singleLinkedList = new SingleLinkedList();
    DynamicArray *dynamicArray = new DynamicArray(2, 2);
    Bomb bomb;
    bomb.color = 'c';
    bomb.weight = 100;
    bomb.trotylCount = 99;
    srand(time(NULL));
    int randNum;
    clock_t secondTime, firstTime;
    double seconds;
    firstTime = clock();
    for (int i = 0; i < 50000; i++) {
        dynamicArray->push_back(bomb);
    }
    secondTime = clock();
    seconds = (double(secondTime - firstTime)) / CLOCKS_PER_SEC;
    cout << "Count of seconds for adding 50000 elements in the end of dynamic array: " << seconds << endl;
    firstTime = clock();
    for (int i = 0; i < 50000; i++) {
        singleLinkedList->push_back(bomb);
    }
    secondTime = clock();
    seconds = (double(secondTime - firstTime)) / CLOCKS_PER_SEC;
    cout << "Count of seconds for adding 50000 elements in the end of single linked list: " << seconds << endl;
    firstTime = clock();
    for (int i = 0; i < 10000; i++) {
        dynamicArray->push_front(bomb);
    }
    secondTime = clock();
    seconds = (double(secondTime - firstTime)) / CLOCKS_PER_SEC;
    cout << "Count of seconds for adding 10000 elements in the beginning of the dynamic array: " << seconds << endl;
    firstTime = clock();
    for (int i = 0; i < 10000; i++) {
        singleLinkedList->push_front(bomb);
    }
    secondTime = clock();
    seconds = (double(secondTime - firstTime)) / CLOCKS_PER_SEC;
    cout << "Count of seconds for adding 10000 elements in the beginning of the single linked list: " << seconds
         << endl;
    firstTime = clock();
    for (int i = 0; i < 20000; i++) {
        randNum = rand() % 50000;
        dynamicArray->get(randNum);
    }
    secondTime = clock();
    seconds = (double(secondTime - firstTime)) / CLOCKS_PER_SEC;
    cout << "Count of second for getting 20000 elements under the random indexes in dynamic array: " << seconds << endl;
    firstTime = clock();
    for (int i = 0; i < 20000; i++) {
        randNum = rand() % 50000;
        singleLinkedList->get(randNum);
    }
    secondTime = clock();
    seconds = (double(secondTime - firstTime)) / CLOCKS_PER_SEC;
    cout << "Count of second for getting 20000 elements under the random indexes in single linked list: " << seconds
         << endl;
    firstTime = clock();
    for (int i = 0; i < 5000; i++) {
        dynamicArray->pop_back();
    }
    secondTime = clock();
    seconds = (double(secondTime - firstTime)) / CLOCKS_PER_SEC;
    cout << "Count of seconds for removing 5000 elements from the end of the dynamic array: " << seconds << endl;
    firstTime = clock();
    for (int i = 0; i < 5000; i++) {
        singleLinkedList->pop_back();
    }
    secondTime = clock();
    seconds = (double(secondTime - firstTime)) / CLOCKS_PER_SEC;
    cout << "Count of seconds for removing 5000 elements from the end of the single linked list: " << seconds << endl;
    firstTime = clock();
    for (int i = 0; i < 5000; i++) {
        dynamicArray->pop_front();
    }
    secondTime = clock();
    seconds = (double(secondTime - firstTime)) / CLOCKS_PER_SEC;
    cout << "Count of seconds for removing 5000 elements from the beginning of the dynamic array: " << seconds << endl;
    firstTime = clock();
    for (int i = 0; i < 5000; i++) {
        singleLinkedList->pop_front();
    }
    secondTime = clock();
    seconds = (double(secondTime - firstTime)) / CLOCKS_PER_SEC;
    cout << "Count of seconds for removing 5000 elements from the beginning of the single linked list: " << seconds
         << endl;
    firstTime = clock();
    for (int i = 0; i < 50000; i++) {
        dynamicArray->push_back(bomb);
    }
    for (int i = 0; i < 20000; i++) {
        randNum = rand() % 50000;
        dynamicArray->get(randNum);
    }
    for (int i = 0; i < 5000; i++) {
        dynamicArray->pop_back();
    }
    for (int i = 0; i < 5000; i++) {
        dynamicArray->pop_front();
    }
    for (int i = 0; i < 10000; i++) {
        dynamicArray->push_front(bomb);
    }
    secondTime = clock();
    seconds = (double(secondTime - firstTime)) / CLOCKS_PER_SEC;
    cout << "Count of seconds taken for all the operations mentioned above for a dynamic array: " << seconds << endl;
    firstTime = clock();
    for (int i = 0; i < 50000; i++) {
        singleLinkedList->push_back(bomb);
    }
    for (int i = 0; i < 20000; i++) {
        randNum = rand() % 50000;
        singleLinkedList->get(randNum);
    }
    for (int i = 0; i < 5000; i++) {
        singleLinkedList->pop_back();
    }
    for (int i = 0; i < 5000; i++) {
        singleLinkedList->pop_front();
    }
    for (int i = 0; i < 10000; i++) {
        singleLinkedList->push_front(bomb);
    }
    secondTime = clock();
    seconds = (double(secondTime - firstTime)) / CLOCKS_PER_SEC;
    cout << "Count of seconds taken for all the operations mentioned above for a single linked list: " << seconds
         << endl;
}

