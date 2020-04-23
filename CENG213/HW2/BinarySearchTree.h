#ifndef _BST
#define _BST
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>

using namespace std;
template <class T>
class TreeNode {
public:
    
    // DO NOT modify this part.
    
    T data;             // data stored at this node
    TreeNode<T> *left;    // reference to left subtree
    TreeNode<T> *right;   // reference to right subtree
    
    // Constructs a leaf node with the given data.
    TreeNode<T>(T val=T()) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
    
    // Constructs a branch node with the given data and links.
    TreeNode<T>(T val, TreeNode<T> *lf, TreeNode<T> *rt) {
        data = val;
        left = lf;
        right = rt;
    }
};

template <class T>
class BinarySearchTree{
public:
    // Constructor
    BinarySearchTree<T>(){
        root = nullptr;
    }
    
    //Destructor
    ~BinarySearchTree<T>(){
        deleteTree(root);
    }
    
    //Copy constructor
    BinarySearchTree<T>(const BinarySearchTree<T> & t){
        if(t.root == nullptr)
            root = nullptr;
        else make_copy(root,t.root);
    }
    
    // = operator overloading
    BinarySearchTree& operator=(const BinarySearchTree& t){
        if(this !=&t){
            deleteTree(root);
            make_copy(root,t.root);
        }
        return *this;
    }
    
    // Returns the height of this tree
    int height(){
        return(height(root));
    }
    
    // Returns the depth of a node with the given value in this tree
    int depth(T val){
        return depth(root, val, 0);
    }
    
    // Adds the given value to this BST in sorted order.
    void add(T value) {
        add(root, value);
    }
    
    // Removes the given value from this BST while remaining elements
    // stay sorted.
    void remove(T value) {
        remove(root, value);
    }
    
    // Returns if this tree contains T value val
    bool contains(T val){
        return contains(root, val);
    }
    
    // Returns the node data in this tree where val == valtree
    T& getVal(T val){
        return getVal(root, val);
    }
    
    // Returns minimum T value with respect to < operator comparison
    T getMin() {
        return getMin(root);
    }
    
    // Prints this tree in inorder with << operator
    void print(){
        printInOrder(root);
        cout << endl;
    }
    
    // Prints this tree in inorder with print() function of T
    void printVal(){
        printInOrderVal(root);
    }
    
    // Prints this tree sideways (tilted 90 degree on counter clock wise)
    void printSideways(){
        printSideways(root,"");
    }
    
    // Tests if the tree is balanced
    bool isBalanced(){
        int h= -1;
        return isBalanced(root,h);
    }
    
    // Makes the tree balanced.
    void makeItBalanced(){
        // TODO
        // Write your implementation here
        
    }
    
private:
    // Private data member:
    // the overall root of the tree. It is null for an empty tree
    TreeNode<T> *root;
    
    // Private methods
    
    // Helper method to add a new node with the given value
    void add(TreeNode<T> *&r, T value) {
        if (r == nullptr) {
            r = new TreeNode<T>(value);
        } else if (r->data > value) {
            add(r->left, value);
        } else if (r->data < value) {
            add(r->right, value);
        }
        
    }
    
    // Helper method to remove node with the given value
    void remove(TreeNode<T> *& r, T value) {
        if (r == nullptr)
            return;
        else if (r->data > value)
            remove(r->left, value);
        else if (r->data < value)
            remove(r->right , value);
        else    // r->data == value; remove this node
            if (r->left !=nullptr && r->right != nullptr) {
                // both children; replace w/ min from R
                r->data = getMin(r->right);
                remove(r->right, r->data);
            }
            else {
                TreeNode<T> * oldNode =r;  // only  R or L child
                r = (r->left != nullptr)? r->left : r->right;
                delete oldNode;
                oldNode = nullptr;
            }
    }
    
    // Helper method to delete all nodes in a tree
    void deleteTree(TreeNode<T> *&r){
        if (r == nullptr)
            return;
        deleteTree(r->left);
        deleteTree(r->right);
        delete r;
        r = nullptr;
    }
    
    // Helper method to copy r2 to r1
    void make_copy(TreeNode<T> *& r1, TreeNode<T> *r2){
        if(r2!=nullptr){
            r1=new TreeNode<T>(r2->data);
            make_copy(r1->left,r2->left);
            make_copy(r1->right,r2->right);
        }
        else r1=nullptr;
    }
    
    // Helper method to return the height of the tree
    int height(TreeNode<T> * r){
        if (r == nullptr)
            return -1;
        else return (max(height(r->left), height(r->right)) + 1);
    }
    
    // Helper method to find the depth of a given value
    int depth(TreeNode<T> * r, int val, int d){
        if (r==nullptr)
            return -1;
        if (r->data == val)
            return d;
        int ld = depth(r->left, val, d+1);
        if (ld != -1)
            return ld;
        return (depth(r->right, val, d+1));
    }
    
    // Helper method to print the nodes in inorder
    void printInOrder(TreeNode<T> * r){
        if (r!=nullptr){
            printInOrder(r->left);
            cout << r->data << " " ;
            printInOrder(r->right);
        }
    }
    
    // Helper method to print the nodes in inorder
    void printInOrderVal(TreeNode<T> * r){
        if (r!=nullptr){
            printInOrderVal(r->left);
            (r->data).print();
            printInOrderVal(r->right);
        }
    }
    
    // Helper method to print the nodes sideways
    void printSideways(TreeNode<T> *r, string str){
        if (r != nullptr){
            printSideways(r->right, str+"   ");
            cout << str << r->data <<  endl;
            printSideways(r->left, str + "   ");
        }
    }
    
    // Helper method to return if this binary search tree contains the value val
    bool contains(TreeNode<T> *r, T val){
        if (r == nullptr)
            return false;
        else {
            if (r->data == val)
                return true;
            else if (r->data > val)
                return contains(r->left,val);
            else return contains(r->right,val);
        }
    }
    
    // Helper method to return Node data
    // Given a value in T type, val, returns the value
    // of a node, r->val where r->val == val evaluates to True.
    T& getVal(TreeNode<T> *r, T& val)
    {
        if (r->data == val)
            return r->data;
        else if (r->data > val)
            return getVal(r->left,val);
        else return getVal(r->right,val);
    }
    
    // Helper method to return min value
    T getMin(TreeNode<T>* r) {
        if (r->left == nullptr) {
            return r->data;
        } else {
            return getMin(r->left);
        }
    }
    
    // Helper method to determine if this  tree is balanced
    bool isBalanced(TreeNode<T> *r, int &h){
        int lh=-1, rh=-1;
        if (r == nullptr){
            h = -1;
            return true;
        }
        bool lt, rt;
        lt = isBalanced(r->left, lh);
        rt = isBalanced(r->right,rh);
        h = max(lh,rh) + 1;
        if (lt && rt && abs(lh-rh)<2)
            return true;
        else
            return false;
    }
    
    // Helper method to make it a balanced search tree
    void makeItBalanced(TreeNode<T> *&r, vector<T> &A, int n, int &i){
        // TODO
        // Write your code here
        
    }
    
    
    // You can add your utility functions here if needed.
    

};


#endif

