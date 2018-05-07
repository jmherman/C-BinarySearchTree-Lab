/* Author: Josh Herman
 * Filename: position.h
 * This file is a iterator clas for a binary search tree
 * This file has both declarations and implementations for all functions
 */
#ifndef POSITION_H
#define POSITION_H

template<class T> class BinarySearchTree;

template<class T>
class Position{
public:
    Node<T>& operator*() { return *nodePtr;}
    Position parent() const {
        return Position<T>(this -> nodePtr -> parentPtr);
    }
    Position left() const {
        return Position<T>(nodePtr -> leftPtr);
    }
    Position right() const {
        return Position<T>(nodePtr -> rightPtr);
    }
    bool isRoot() const{
        return this->nodePtr->parentPtr->parentPtr == NULL;
    }
    bool isSuperRoot() const{
        return this->nodePtr->parentPtr == NULL;
    }
    bool isExternal() const{
        return this->nodePtr->leftPtr == NULL && this->nodePtr->rightPtr == NULL;
    }
    bool isInternal() const {return !(isExternal() ); }
    bool operator== (const Position& p){
        return this-> nodePtr == p.nodePtr;
    }
    Position parent() {
        return Position<T>(this -> nodePtr -> parentPtr);
    }
    Position& operator++();
	Position<T> operator=(const Position<T>& copyP);
    T getItem() { return nodePtr->item;}
    friend class BinarySearchTree<T>;
	friend void findAlbum(BinarySearchTree<Album>& tree);
    friend void deleteAlbum(BinarySearchTree<Album>& tree);
    friend void addAlbum(BinarySearchTree<Album>& tree);
private:
    Position(Node <T>*);
    Node<T>* nodePtr;
};

//copy constructor
template <class T>
Position<T>::Position(Node <T>* input){
    nodePtr = input;
}

/* overloaded ++ returns an iterator that points to the next node in the tree, in-order traversal.
 * Returns Position with NULL nodePtr if get to end of tree in-order.
 * Pre-condition: class T has overloaded operator<
 */
template <class T>
Position<T>& Position<T>::operator++(){
    Position w = this -> nodePtr -> rightPtr;
    if(isInternal(w) ){
        do{
            *this = w;
            w = w.leftPtr;
        } while(isInternal(w));
    } else {
        w = this.parentPtr;
        while(w -> nodePtr != NULL && this -> nodePtr = w.rightPtr){
            *this = w;
            w = w -> parentPtr;
        }
        *this = w;
    }
    return this;
}

template<class T>
Position<T> Position<T>::operator=(const Position<T>& copyP){
	this -> nodePtr = copyP -> nodePtr;
}

#endif