#include <iostream>

class Data{
private:
    int value;

public:
    Data(int value){
        Data::value = value;
    }

    int getValue() const {
        return value;
    }

    void setValue(int value) {
        Data::value = value;
    }

    void print(){
        std::cout << value << std::endl;
    }

    bool isLessThan(Data dataOne, Data dataTwo){
        if (dataOne.getValue() < dataTwo.getValue()){
            return 1;
        }else if (dataOne.getValue() > dataTwo.getValue()){
            return -1;
        }else if (dataOne.getValue() == dataTwo.getValue()){
            return 0;
        }
    }

};

template <typename T> class Node {
private:
    T *data;
    Node<T> *leftChild;
    Node<T> *rightChild;
    Node<T> *parent;
public:

    Node(T *data) {
        Node::data = new Data(*data);

    }

    T *getData() const {
        return data;
    }

    void setData(T *data) {
        Node::data = data;
    }

    Node<T> *getLeftChild() const {
        return leftChild;
    }

    void setLeftChild(Node<T> *leftChild) {
        Node::leftChild = leftChild;
    }

    Node<T> *getRightChild() const {
        return rightChild;
    }

    void setRightChild(Node<T> *rightChild) {
        Node::rightChild = rightChild;
    }

    Node<T> *getParent() const {
        return parent;
    }

    void setParent(Node<T> *parent) {
        Node::parent = parent;
    }

    void print () {
        data->print();
    }

    int isLessThan(T *dataOne, T *dataTwo){
        int valueOne = dataOne->getValue();
        int valueTwo = dataTwo->getValue();
        if (valueOne < valueTwo){
            return 1;
        }else if (valueOne > valueTwo){
            return -1;
        }else if( valueOne == valueTwo){
            return 0;
        }
    }

};

template <typename T> class BinarySearchTree {
private:
    Node<T> *root;
    int numberOfElements;
    int height;
    int orderPos;

public:

    BinarySearchTree(T *data) {
        root = new Node<T>(data);
        root->setLeftChild(nullptr);
        root->setRightChild(nullptr);
        numberOfElements = 1;
        height = 1;
    }

    BinarySearchTree(){
        root = nullptr;
        numberOfElements = 0;
        height = 0;
    }

    virtual ~BinarySearchTree() {

    }

    void insertElement(T *data){
        if(root == nullptr){
            root = new Node<T>(data);
            return;
        }

        Node<T>* newNode = new Node<T>(data);
        newNode->setLeftChild(nullptr);
        newNode->setRightChild(nullptr);
        Node<T>* checkNode = root;
        int value;

        for(int i = 0; i <= numberOfElements; i++){
            value = isLessThan(newNode, checkNode);
            if((value == 1) && (checkNode->getLeftChild() != nullptr)){
                checkNode = checkNode->getLeftChild();
            }else if((value <= 0) && (checkNode->getRightChild() != nullptr)){
                checkNode = checkNode->getRightChild();
            }
        }

        newNode->setParent(checkNode);
        if(value == 1){
            checkNode->setLeftChild(newNode);
        }else if(value <= 0){
            checkNode->setRightChild(newNode);
        }

        numberOfElements += 1;
    }

    void deleteElement(T *data) {
        if (root == nullptr) {
            return;
        }

        Node<T> *temp = root;
        Node<T> *tempRight = root->getRightChild();
        Node<T> *tempLeft = root->getLeftChild();
        Node<T> *currTemp = root;
        bool done = false;
        bool left = false;
        bool right = false;

        if (root->getData()->getValue() == data->getValue()) {
            if (root->getLeftChild() != nullptr) {
                root = root->getLeftChild();
                while (tempLeft->getRightChild() != nullptr) {
                    tempLeft = tempLeft->getRightChild();
                }
                tempLeft->setRightChild(tempRight);
            } else {
                root = tempRight;
            }
            numberOfElements -= 1;
            return;
        }

        while (!done) {
            if (currTemp->getLeftChild() != nullptr && currTemp->getLeftChild()->getData()->getValue() == data->getValue()) {
                done = true;
                temp = currTemp->getLeftChild();
                left = true;
                break;
            }
            if (currTemp->getRightChild() != nullptr && currTemp->getRightChild()->getData()->getValue() == data->getValue()) {
                done = true;
                temp = currTemp->getRightChild();
                right = true;
                break;
            }
            if (currTemp->getLeftChild() == nullptr && currTemp->getData()->getValue() > data->getValue()){
                std::cout << "Number does not exist." << std::endl;
                return;
            }
//            if (currTemp->getRightChild() == nullptr && currTemp->getData()->getValue() < data->getValue()){
//                std::cout << "Number does not exist." << std::endl;
//                return;
//            }
            if (currTemp->getLeftChild() == nullptr && currTemp->getRightChild() == nullptr) {
                std::cout << "Number does not exist." << std::endl;
                return;
            }
            if (currTemp->getData()->getValue() > data->getValue()) {
                currTemp = currTemp->getLeftChild();
            }
            if (currTemp->getData()->getValue() < data->getValue()) {
                currTemp = currTemp->getRightChild();
            }
        }
        if(left){
            if(temp->getLeftChild() == nullptr){
                currTemp->setLeftChild(temp->getRightChild());
            }else{
                tempRight = temp->getRightChild();
                currTemp->setLeftChild(temp->getLeftChild());
                while (currTemp->getRightChild() != nullptr) {
                    currTemp = currTemp->getRightChild();
                }
                currTemp->setRightChild(tempRight);
            }
        }
        if(right){
            if(temp->getLeftChild() == nullptr){
                currTemp->setRightChild(temp->getRightChild());
            }else{
                tempRight = temp->getRightChild();
                currTemp->setRightChild(temp->getLeftChild());
                while (currTemp->getRightChild() != nullptr) {
                    currTemp = currTemp->getRightChild();
                }
                currTemp->setRightChild(tempRight);
            }
        }
        numberOfElements -= 1;
    }

    void print(){
        traversePreOrder(root);
        std::cout << std::endl;
    }

    void traversePreOrder(Node<T> *newNode){
        std::cout << newNode->getData()->getValue() << ", ";
            if(newNode->getLeftChild() != nullptr) {
                traversePreOrder(newNode->getLeftChild());
            }
            if(newNode->getRightChild() != nullptr) {
                traversePreOrder(newNode->getRightChild());
            }
    }

    void findKthElement(int k){
        if ((k < 1) || (k > numberOfElements)){
            std::cout << "Number does not exist." << std::endl;
            return;
        }
        orderPos = 0;
        findInOrder(root, k);
        orderPos = 0;
    }

    void findInOrder(Node<T> *newNode, int k){
        if (newNode == nullptr){
            return;
        }
        findInOrder(newNode->getLeftChild(), k);
        orderPos += 1;
        if (k == orderPos){
            std::cout << newNode->getData()->getValue() << std::endl;
            return;
        }
        findInOrder(newNode->getRightChild(), k);
    }

    void findSmallest() {
        Node<T>* smallestNode = root;
        if (root->getLeftChild() == nullptr){
            std::cout << smallestNode->getData()->getValue() << std::endl;
        } else {
            smallestNode = root->getLeftChild();
            while (smallestNode->getLeftChild() != nullptr) {
                smallestNode = smallestNode->getLeftChild();
            }
            std::cout << smallestNode->getData()->getValue() << std::endl;
        }
    }


    void findBiggest(){
        Node<T>* biggestNode = root;
        if(biggestNode->getRightChild() == nullptr){
            std::cout << biggestNode->getData()->getValue() << std::endl;
        }else {
            biggestNode = root->getRightChild();
            while (biggestNode->getRightChild() != nullptr) {
                biggestNode = biggestNode->getRightChild();
            }
            std::cout << biggestNode->getData()->getValue() << std::endl;
        }
    }

    void sortAscending(){
        traverseInOrder(root);
        std::cout << std::endl;
    }

    void traverseInOrder(Node<T> *newNode){
        if(newNode != nullptr){
            traverseInOrder(newNode->getLeftChild());
            std::cout << newNode->getData()->getValue() << ", ";
            traverseInOrder(newNode->getRightChild());
        }
    }

    void sortDescending(){
        traverseBackwardsInOrder(root);
        std::cout << std::endl;
    }

    void traverseBackwardsInOrder(Node<T> *newNode){
        if(newNode != nullptr){
            traverseBackwardsInOrder(newNode->getRightChild());
            std::cout << newNode->getData()->getValue() << ", ";
            traverseBackwardsInOrder(newNode->getLeftChild());
        }
    }

    Node<T> *getRoot() const {
        return root;
    }

    void setRoot(Node<T> *root) {
        BinarySearchTree::root = root;
    }

    int getNumberOfElements() const {
        return numberOfElements;
    }

    void setNumberOfElements(int numberOfElements) {
        BinarySearchTree::numberOfElements = numberOfElements;
    }

    int getHeight() const {
        return height;
    }

    void setHeight(int height) {
        BinarySearchTree::height = height;
    }

    int isLessThan(Node<T> *nodeOne, Node<T> *nodeTwo){
        int dataOne = nodeOne->getData()->getValue();
        int dataTwo = nodeTwo->getData()->getValue();
        if (dataOne < dataTwo){
            return 1;
        }else if (dataOne > dataTwo){
            return -1;
        }else if (dataOne == dataTwo){
            return 0;
        }
    }


};

int main() {
    int a[] = {10,45,23,67,89,34,12,99};
    Data* newData = new Data(a[0]);
    BinarySearchTree<Data>* newBST = new BinarySearchTree<Data>(newData);
    for(int i=1;i< (sizeof(a)/sizeof(int));i++)
    {
        newData = new Data(a[i]);
        newBST->insertElement(newData);
    }
    newBST->print();
    newBST->findSmallest();
    newBST->findBiggest();
//    newData = new Data(10);
    newData = new Data(10);
    newBST->deleteElement(newData); // delete root
    newBST->print();
    newData = new Data(45);
    newBST->deleteElement(newData); //delete with two children
    newBST->print();
    newData = new Data(12);
    newBST->deleteElement(newData); //delete with one child
    newBST->print();
    newData = new Data(10);
    newBST->deleteElement(newData); // delete a number that doesnt exist. What will you print?
    newBST->print();
    newBST->findKthElement(1); //first element
    newBST->findKthElement(newBST->getNumberOfElements()); //last element
    newBST->findKthElement(3); // some element in between
    newBST->findKthElement(7); // Edge case where item does not exist. What will you print?
    newBST->findSmallest();
    newBST->findBiggest();
    newBST->sortAscending();
    newBST->sortDescending();
    return 0;
}
