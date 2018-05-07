/* Author: Josh Herman
 * Filename: binarySearch.h
 * This file is the insides and guts of the binary search tree
 * Contains both function declarations and implementations
 */
#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H

#include <algorithm>
#include "node.h"
#include "position.h"
#include "album.h"
using namespace std;

template <class T> class Position;
const int PREORDER = 1;
const int INORDER = 2;
const int POSTORDER = 3;

template <class T>
class BinarySearchTree{
public: 
    BinarySearchTree();
    BinarySearchTree( const BinarySearchTree&);
    Node<T>* copyTree(Node<T>* p, Node<T>* n);
    //returns num nodes in tree
    int size() const { return numNodes; }
    //return true if tree empty of real nodes
    bool empty () const{return numNodes == 0;}
    //superroot rught pointer aleways points to real root node
    Position<T> root() const{
            return Position<T>(superRootPtr->rightPtr);
    }
    void traverseAndPrint(const Position<T>&p, int type) const;
    Position<T> insert(const T& item);
    int depth(const Position<T>&) const; 
    int height(const Position<T>& ) const;
    Position<T> begin() const;
    //returns NULL iterator
    Position<T> end() const { return Position<T>(); }
    Position<T> find(const T& item) const;
    bool erase(const T& p);
    bool erase(const Position<T>& p);
    void preOrderTxtFile(ostream& outTxt, const Position<T>& pos);
    void preOrderBinFile(ofstream& outBin, const Position<T>& pos);
    BinarySearchTree<T> operator=(const BinarySearchTree& tree);
    //need deleteUtility
    virtual ~BinarySearchTree() { deleteUtility(superRootPtr); }
    //returns numNodes
	int get_numNodes(){return numNodes;}
	friend void findAlbum(BinarySearchTree<Album>& tree);
    friend void deleteAlbum(BinarySearchTree<Album>& tree);
    friend void addAlbum(BinarySearchTree<Album>& tree);
private:
    Node<T>* superRootPtr;
    //number real nodes in tree, not incuding fake super
    //root and fake ends nodes 
    int numNodes;
    void preorderTraverseAndPrint(const Position<T>& ) const; //done
    void inorderTraverseAndPrint(const Position<T>& ) const; //done
    void postorderTraverseAndPrint(const Position<T>&) const; //done
    //finds item in tree starting at position
    Position<T> findUtility(const T& item, const Position<T>& p) const;
    //inserts item into tree
    Position<T> insertUtility(const T& item);
    //deletes all nodes  in the tree
    void deleteUtility(Node<T>* nodePtr);
    //erases just one node from the tree at position p 
    Position<T> eraseUtility(const Position<T>& p);
    //insert item data at position p
    void expandExternal( const T& item, Position<T>& p);
    //remove node above fake leaf node at position p
    Position<T> removeAboveExternal(const Position<T>& p);
};

/* copyTree utility function that copies one tree to this' tree
 * Paramters:
 *      p - pointer to parent in this' tree that new node's
 *          parentPtr should point to
 *      n - pointer to new node in tree to copy from
 * Returns pointer to node just allocated for this' tree or NULL
 *      (if at the end of a branch) and no new node to copy
 */
template<class T>
Node<T>* BinarySearchTree<T>::copyTree(Node<T>* p, Node<T>* n){
    if(n != NULL){
        Node<T>* newNode = new Node<T>(*n);
        newNode -> parentPtr = p;
        newNode -> leftPtr = copyTree(newNode, n -> leftPtr);
        newNode -> rightPtr = copyTree(newNode, n -> rightPtr);
        return newNode;
    }
    else {
        return NULL;
    }
}

/* erases removes a node above Position P
 * Pre-condition: position p is a valid position in tree
 * Returns true if successful
 */
template <class T>
bool BinarySearchTree<T>::erase(const T& p){
    Position<T> found = find(p);
    if(!found.isSuperRoot() && !found.isExternal()){
        eraseUtility(found);
        return true;
    }else {
        return false;
    }
}

/* removeAboveExternal: removes "left" node just above fake 
 *      leaf node pointed to by p. Decrements number of nodes in tree
 * Parameter: p - leaf node of real node to delete
 * Returns position iterator to sibling of node removed
 */
template <class T>
Position<T> BinarySearchTree<T>::removeAboveExternal(const Position<T>& p){
    Node<T>* w = p.nodePtr;
    Node<T>* v = p.nodePtr -> parentPtr;
    Node<T>* siblingPtr;
    
    if(v -> leftPtr == w){
        siblingPtr = v -> rightPtr;
    } else{
        siblingPtr = v -> leftPtr;
    }
    
    if(v == superRootPtr -> rightPtr){
        superRootPtr -> rightPtr = siblingPtr;
        siblingPtr -> parentPtr = superRootPtr;
    } else {
        Node<T>* grandParentPtr = v -> parentPtr;
        if(grandParentPtr -> leftPtr == v){
            grandParentPtr -> leftPtr = siblingPtr;
        } else {
            grandParentPtr -> rightPtr = siblingPtr;
        }
        siblingPtr -> parentPtr = grandParentPtr;
    }
    delete w;
    delete v;
    Position<T> returnFunc = Position<T>(siblingPtr);
    return returnFunc;
}

/* deleteUtility: this function deletes the whole tree
 * Parameter: nodePtr - the node to start from
 * Post-condition: the entire tree is deleted
 */
template<class T>
void BinarySearchTree<T>::deleteUtility(Node<T>* nodePtr){
    if(nodePtr != NULL){
        deleteUtility(nodePtr -> leftPtr);
        deleteUtility(nodePtr -> rightPtr);
        delete nodePtr;
    }
}

/* postorderTraverseAndPrint: this functions prints out the tree in POST ORDER
 * parameter: root - where to start
 * NOT USED IN THIS LAB
 */
template <class T>
void BinarySearchTree<T>::postorderTraverseAndPrint(const Position<T>& root) const{
    if(!root.isExternal()){
        postorderTraverseAndPrint(root.left());
        postorderTraverseAndPrint(root.right());
        cout<<root.nodePtr -> item<<" ";
    }
}

/* inorderTraverseAndPrint: this functions prints out the tree in IN ORDER
 * parameter: root - where to start
 * NOT USED IN THIS LAB
 */
template <class T>
void BinarySearchTree<T>::inorderTraverseAndPrint(const Position<T>& root) const{
    if(!root.isExternal()){
        inorderTraverseAndPrint(root.left());
        cout<<root.nodePtr -> item<<" ";
        inorderTraverseAndPrint(root.right());
    }
}

/* preorderTraverseAndPrint: this functions prints out the tree in PRE_ORDER
 * parameter: root - where to start
 * NOT USED IN THIS LAB
 */
template <class T>
void BinarySearchTree<T>::preorderTraverseAndPrint(const Position<T>& root) const{
    if(root.isExternal()){
        return;
    } else{
        cout<<root.nodePtr -> item<<endl;
        preorderTraverseAndPrint(root.left());
        preorderTraverseAndPrint(root.right());
    }
}

/* traverseAndPrint: this functions selects which print order and calls respective function
 * Parameters:
 *      p - position where to start
 *      type - the type of order to print it out
 */
template <class T>
void BinarySearchTree<T>::traverseAndPrint(const Position<T>& p, int type) const{
    if(type == PREORDER){
        preorderTraverseAndPrint(p);
    } else if(type == INORDER){
        inorderTraverseAndPrint(p);
    }else if(type == POSTORDER){
        postorderTraverseAndPrint(p);
    }
}


/*depth returns distance from root to node a parameter 
 * position
 * Parameter: position to compute depth of
 * returns depth or -1 is position is superroot
*/
template<class T>
int BinarySearchTree<T>::depth( const Position<T>&p ) const{
    if(p.isSuperRoot()) return -1;
    if(p.isRoot(*this)) return 0;
    else{
        return 1+depth(p.parent());
    }
}

/*height reutns the distance from node at parameter position to
 * the lowest leaf
 * Parameter: position to computer height of
*/
template <class T>
int BinarySearchTree<T>::height(const Position<T>& p) const {
    //if leaf
    if(p.isExternal()) return 0;
    
    int h = 0;
    //h= max of 0 and height of left subtree
    
    h = max(h, height(Position<T>(p.nodePtr->leftPtr)));
    // h = max of height of left subtree and height of right subtree
    h = max(h, height(Position<T>(p.nodePtr->rightPtr)));
    return 1 + h;
}

/* begin: returns positon iterator to first node on tree - the leftmost.
*/
template <class T>
Position<T> BinarySearchTree<T>::begin() const{
    if(numNodes > 0){
        Position<T> p = root ();
        while (p.isInternal()){
            p = p.left();
        }
        return p.parent();
    }
    else return Position<T>(superRootPtr);
}
 
/*finds a T object  in tree
 * Parameters: the object to find 
 * pre-cond: class T has overloaded operator ==
 * returns: iterator to object, superroot iterator if not found
*/
template <class T>
Position<T> BinarySearchTree<T>::find(const T& item) const {
    if(numNodes >= 0){
        Position<T> v = findUtility(item, root());
        return v;
    }
    else return Position<T>(superRootPtr);
}

/* findUtility: recursive utility find function
 * Parameters: item to look for =
 * p postion to start looking from
 * Pre-cond: classT has overloaded operator==
 *  and operator<, tree not empty of real nodes
 * returns: position iterator where found or NULL iterator
*/
template<class T>
Position<T> BinarySearchTree<T>::findUtility(const T& inputItem, const Position<T>& p) const{
    if(p.isExternal()){
        return p;
    }
    else if(p.nodePtr -> item == inputItem){
        return p;
    } else if(inputItem < p.nodePtr -> item){
        return(findUtility(inputItem, p.left()));
    } else{
        return(findUtility(inputItem, p.right()));
    }
}

/* inserts object T in the binary tree
 * Parameter: the object to insert
 * Pre-condition: class T has overloaded operator< 
 * Returns iterator to newly inserted object or superRootPtr 
 *      if item is already in tree
 */
template <class T>
Position<T> BinarySearchTree<T>::insert(const T& item){
    Position<T> p = insertUtility(item);
    return p;
}

/* insertUtility: inserts at position for new node
 * Parameters: new node to insert
 * Returns iterator to newly inserted object or to superRoot
 *      fake node if item already in tree
 */
template <class T>
Position<T> BinarySearchTree<T>::insertUtility(const T& item){
    Position<T> insertP = find(item);
    if(insertP.isExternal()){
        expandExternal(item, insertP);
    }
    return insertP;
}

/* expandExternal - inserts item by copying its data to
 *      position p and setting position's left and right ptrs
 *      to end nodes
 * Paramters:
 *      item - item to be inserted
 *      p - fake end node where item will be inserted
 * Pre-condition: p is an external node (a fake leaf)and
 *      class T has overladed = operator
 */
template <class T>
void BinarySearchTree<T>::expandExternal( const T& item, Position<T>& p){
    Node<T>* left = new Node<T>;
    Node<T>* right = new Node<T>;
    
    p.nodePtr -> leftPtr = left;
    p.nodePtr -> rightPtr = right;
    left -> parentPtr = p.nodePtr;
    right -> parentPtr = p.nodePtr;
    
    p.nodePtr -> item = item;
    numNodes++;
}

/* erase removes a node above Position p
 * Precondition: position P is a valid position in tree
 * returns true if successful
 */

template <class T>
bool BinarySearchTree<T>::erase(const Position<T>& p){
    if(!p.isSuperRoot() && !p.isExternal()){
        eraseUtility(p);
        return true;
    }
    else {
        return false;
    }
}

/* default ctor sets up an empty tree with two nodes:
 *      fake root whose right ptr points to fake end
 */
template<class T>
BinarySearchTree<T>::BinarySearchTree(){
    numNodes = 0;
    Node<T>* rights = new Node<T>();
    superRootPtr = new Node<T>();
    superRootPtr -> rightPtr = rights;
    rights -> parentPtr = superRootPtr;
}

/* copy ctor - completes a deep copy on the tree provided
 * parameter - the tree to copy over
 */
template <class T>
BinarySearchTree<T>::BinarySearchTree( const BinarySearchTree& t){
    numNodes = t.numNodes;
    superRootPtr = new Node<T>();
    
    if(t.empty()){
        superRootPtr -> rightPtr = new Node<T>();
        superRootPtr -> rightPtr -> parentPtr = superRootPtr;
    } else{
        superRootPtr -> rightPtr = copyTree(superRootPtr, superRootPtr -> rightPtr);
    }
}

/* operator=: deletes parameter tree and completes a deep copy on it
 * Parameter: the tree to copy over
 */
template <class T>
BinarySearchTree<T> BinarySearchTree<T>::operator=(const BinarySearchTree& tree){
    deleteUtility(tree.superRootPtr);
    numNodes = tree.numNodes;
    superRootPtr = new Node<T>();
    
    if(tree.empty()){
        superRootPtr -> rightPtr = new Node<T>();
        superRootPtr -> rightPtr -> parentPtr = superRootPtr;
    } else{
        superRootPtr -> rightPtr = copyTree(superRootPtr, superRootPtr -> rightPtr);
    }
}

/* eraseUtility: this function just erases one node from the tree
 * Paramter: p - the position of the tree to delete
 * Pre-condition: the node provided is a real node
 * Post-condition: the node is deleted
 * returns: the position of the fake node
 */
template <class T>
Position<T> BinarySearchTree<T>::eraseUtility(const Position<T>& p){
    Node<T>* w;
    Node<T>* u;
    if(p.left().isExternal()){
        w = p.nodePtr -> leftPtr;
    } else if(p.right().isExternal()){
        w = p.nodePtr -> rightPtr;
    } else {
        w = p.nodePtr -> rightPtr;
        do{
            w = w -> leftPtr;
        } while(w -> rightPtr != NULL && w -> leftPtr != NULL);
        u = w -> parentPtr;
        p.nodePtr -> item = u -> item;
    }
    Position<T> removes = Position<T>(w);
    removeAboveExternal(removes);
    return removes;
}

/* findAlbum: this function takes in the album name & artist name from the user
 * 		then creates a temp album with those two things and searches the tree for that album
 * 		using the normalized name
 * Paramter:
 * 		tree: the tree to search
 * Pre-condition: the tree has data in it and the nodes have their normalized names set
 * Post-condition: if the album is found, it will print out the album; otherwise it will print: no album found
 */
void findAlbum(BinarySearchTree<Album>& tree){
	Album temp;
	char tempAlbumName[MAX_NAME];
	char tempArtistName[MAX_NAME];
	cout<<"Album: ";
	cin.getline(tempAlbumName, MAX_NAME);
	cout<<"Arist: ";
	cin.getline(tempArtistName, MAX_NAME);
	
	temp.set_albumTitle(tempAlbumName);
	temp.set_artistName(tempArtistName);
	temp.setNormName();
	Position<Album> search = tree.find(temp);
	if(search == tree.superRootPtr || search.isExternal()){
		cout<<"No album found\n";
	}else{
		cout<<"Album"<<setw(20)<<setw(20)<<right<<"Artist"<<setw(20)<<"Label"<<setw(20)<<"Release Date"<<setw(10)<<"Genre\n";
		cout<<"-------------------------------------------------------------------------------------------------------------\n";
		cout<<search.nodePtr -> item<<endl;
	}
}

/* deleteAlbum: this function asks the user for a album name/artist name and searches for that album
 *      if the album is found(print error message if not found) it'll ask the user if they want to delete it
 *      function will delete the album if the user says to
 * Parameters: tree - the tree to search/delete from
 * Pre-condition: all the nodes have their normalized name set
 * Post-condition: the tree may(depending on user input) have deleted a node
 */
void deleteAlbum(BinarySearchTree<Album>& tree){
    Album temp;
    char deleteInput;
    
    char tempAlbumName[MAX_NAME];
    char tempArtistName[MAX_NAME];
    cout<<"Album: ";
    cin.getline(tempAlbumName, MAX_NAME);
    cout<<"Artist: ";
    cin.getline(tempArtistName, MAX_NAME);
    
    temp.set_albumTitle(tempAlbumName);
    temp.set_artistName(tempArtistName);
    temp.setNormName();
    Position<Album> searchDelete = tree.find(temp);
    if(searchDelete == tree.superRootPtr || searchDelete.isExternal()){ // not found
        cout<<"Album not found\n";
        return;
    } else { //found
        cout<<"Do you want to delete "<<searchDelete.nodePtr -> item.get_albumTitle()<<" by "<<searchDelete.nodePtr -> item.get_artistname()<<" (y/n)? ";
        cin>>deleteInput;
        if(deleteInput == 'y' || deleteInput == 'Y'){ //user says yes
            cout<<searchDelete.nodePtr -> item.get_albumTitle()<<" by "<<searchDelete.nodePtr -> item.get_artistname()<<" deleted.\n";
            tree.erase(searchDelete);
        } else if(deleteInput == 'n' || deleteInput == 'N'){ //user says no
            cout<<searchDelete.nodePtr -> item.get_albumTitle()<<" by "<<searchDelete.nodePtr -> item.get_artistname()<<" has not been deleted.\n";
            return;
        }
    }
    cin.get();
}

/* addAlbum: this function will ask the user for the album they want to enter
 *      if the album already exists it will print our an error message
 *      otherwise it will insert the item
 * Paramter: tree - the tree to insert the album into
 * returns nothing
 * Post-condition: the album is added to the tree(assuming the album is not already
 */
void addAlbum(BinarySearchTree<Album>& tree){
    Album temp;
    char genreTemp;
    char tempString[MAX_NAME];
    
    int trackCount = 0;
    
    cout<<"Album name: ";
    cin.getline(tempString, MAX_NAME);
    temp.set_albumTitle(tempString);
    
    cout<<"Artist: ";
    cin.getline(tempString, MAX_NAME);
    temp.set_artistName(tempString);
    temp.setNormName();
    
    Position<Album> search = tree.find(temp);
    if(search.nodePtr -> item == temp){
        cout<<search.nodePtr -> item.get_albumTitle()<<" by "<<search.nodePtr -> item.get_artistname()<<" is already in the library.\n";
        return;
    }
    cout<<"Label: ";
    cin.getline(tempString, MAX_NAME);
    temp.set_labelName(tempString);
    
    cout<<"Release Date (mm/dd/yyyy): ";
    cin.getline(tempString, MAX_NAME);
    temp.setInputDate(tempString);
    
    cout<<"Genre: ";
    cin>>genreTemp;
    temp.setGenre(genreTemp);
    
    cout<<"How many tracks (no more than "<<MAX_TRACKS<<")? ";
    cin>>trackCount;
    cin.get();

    for(int i = 0; i < trackCount; i++){
        cout<<"Track "<<i + 1<<": ";
        cin.getline(tempString, MAX_NAME);
        temp.addTrack(tempString);
    }
    
    tree.insert(temp);
}

/* preOrderTxtFile: this file will print out the tree in preorder to a file
 * Paramters:
 *      outTxt: the output file stream variable
 *      pos: the position to start
 * Pre-condition: the item in the BST must have a overloaded '<<' operator
 *      file must be opened and closed in calling function
 * Post-condition: the tree is printed out in preorder to a file
 */
template <class T>
void BinarySearchTree<T>::preOrderTxtFile(ostream& outTxt, const Position<T>& pos){
    if(pos.isExternal()){
        return;
    } else {
        outTxt<<pos.nodePtr -> item<<endl;
        preOrderTxtFile(outTxt, pos.left());
        preOrderTxtFile(outTxt, pos.right());
    }
}

/* preOrderBinFile: this function prints out the tree pre-order to a binary file
 * Parameters:
 *      outBin: the file stream variable
 *      pos: where to start in the tree
 * Pre-condition: the file is opened and closed in the calling function
 * Post-condition: the file is written to
 */
template <class T>
void BinarySearchTree<T>::preOrderBinFile(ofstream& outBin, const Position<T>& pos){
    if(pos.isExternal()){
        return;
    } else {
        pos.nodePtr -> item.writeBinAlbum(outBin);
        preOrderBinFile(outBin, pos.left());
        preOrderBinFile(outBin, pos.right());
    }
}
#endif