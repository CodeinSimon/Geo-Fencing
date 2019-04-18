//
// Created by Simon Nie on 2018/12/28.
//

#ifndef INC_16307130133_KDTREE_H
#define INC_16307130133_KDTREE_H
// A C++ program to demonstrate delete in K D tree
#include <vector>
#include <iostream>
#include <unordered_map>

const int k = 2;
extern std::vector<int> hit_ids;
// A structure to represent node of kd tree
struct Node {
    int id;
    double min[k];
    double max[k];
    bool isDeleted;
    double point[k]; // To store k dimensional point
    Node *left, *right;
};

// A method to create a node of K D tree
Node* newNode(double arr[], int& id);

// Inserts a new node and returns root of modified tree
// The parameter depth is used to decide axis of comparison
Node *insertRec(Node *(&root), double point[], int& id, unsigned depth);

// Function to insert a new point with given point in
// KD Tree and return new root. It mainly uses above recursive
// function "insertRec()"
Node *Insert(Node *(&root), double point[], int& id);

// Function to delete a given point 'point[]' from tree with root
// as 'root'. depth is current depth and passed as 0 initially.
// Returns root of the modified tree.
Node* deleteNodeRec(Node *(&root), double point[], int& id, int depth);

// Function to delete a given point from K D Tree with 'root'
Node *Delete(Node *(&root), double point[], int& id);

void searchRangeRec(Node *(&root), double min[], double max[], int depth);

void Search(Node *(&root), double min[], double max[]);

#endif //INC_16307130133_KDTREE_H


