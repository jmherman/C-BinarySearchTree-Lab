/* Author: Josh Herman
 * FileName: node.h
 * This file is the node class used in the Binary Search Tree
 * This file has both delcarations and implemenations for all functions
 */
#ifndef NODE_H
#define NODE_H

#include <iostream>

template<class T> class BinarySearchTree;
template<class T> class Position;

template<class T>
class Node{
    Node(); //default constructor
    Node(const T&); // copy constructor
    virtual ~Node<T>() {} // destructor
    void setItem(const T&);
    T getItem() const {return item;}
    Node<T>& operator= (const Node<T>& );
    friend class BinarySearchTree<T>;
    friend class Position<T>;
	friend void findAlbum(BinarySearchTree<Album>& tree);
    friend void deleteAlbum(BinarySearchTree<Album>& tree);
    friend void addAlbum(BinarySearchTree<Album>& tree);
private:
    Node<T>* leftPtr;
    Node<T>* rightPtr;
    Node<T>* parentPtr;
    T item;
};

/* default constructor
 * sets all pointers to NULL
 */
template<class T>
Node<T>::Node(){
    leftPtr = NULL;
    rightPtr = NULL;
    parentPtr = NULL;
}

/* copy constructor
 * Parameter: inputItem - the item to set the next node to
 * sets all pointers to NULL &  sets the item to the inputItem
 */
template<class T>
Node<T>::Node(const T& inputItem){
    leftPtr = NULL;
    rightPtr = NULL;
    parentPtr = NULL;
    this -> item = inputItem;
}

/* setItem: this function sets the item of the node
 * Parameter: inputItem - the item to set
 * Pre-condition: the node has been initialized
 * Post-condition: the item of the node has been set
 */
template<class T>
void Node<T>::setItem(const T& inputItem){
    this -> item = inputItem;
}

/* operator= sets the item of the node equal to parameter, all pointers to NULL
 * parameter: the node to copy the item from
 * Post-condition: the item is set to the inputNode's item, and the pointers have been set to NULL
 */
template<class T>
Node<T>& Node<T>::operator= (const Node<T>& inputNode){
    this -> item = inputNode -> item;
    leftPtr = NULL;
    rightPtr = NULL;
    parentPtr = NULL;
}
#endif