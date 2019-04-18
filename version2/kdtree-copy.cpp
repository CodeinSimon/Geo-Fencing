//
// Created by Simon Nie on 2018/12/29.
// @Copyright (c) 2018 Simon Nie. All rights reserved.

#include "KDTree.h"
std::vector<int> hit_ids;

int cnt;

Node* newNode(double arr[], int& id) {
    struct Node *temp = new Node;
    for (int i = 0; i < k; i++) {
        temp->point[i] = arr[i];
        temp->min[i] = std::min(temp->min[i], arr[i]);
        temp->max[i] = std::max(temp->max[i], arr[i]);
    }
    temp->isDeleted = false;
    temp->id = id;
    temp->left = temp->right = NULL;
    return temp;
}
// Inserts a new node and returns root of modified tree
// The parameter depth is used to decide axis of comparison
Node *insertRec(Node *(&root), double point[], int& id, unsigned depth) {
    // Tree is empty?
    if (root == NULL)
        return newNode(point, id);

    // Calculate current dimension (cd) of comparison
    unsigned cd = depth % k;

    // Compare the new point with root on current dimension 'cd'
    // and decide the left or right subtree
    if (point[cd] < (root->point[cd])) {
        // it will be insert to its left, so refresh it's min and max
        root->left = insertRec(root->left, point, id, depth + 1);
        root->min[0] = root->min[0] < point[0] ? root->min[0] : point[0];
        root->min[1] = root->min[1] < point[1] ? root->min[1] : point[1];
        root->max[0] = root->max[0] > point[0] ? root->max[0] : point[0];
        root->max[1] = root->max[1] > point[1] ? root->max[1] : point[1];

    }
    else {
        root->right = insertRec(root->right, point, id, depth + 1);
        root->min[0] = root->min[0] < point[0] ? root->min[0] : point[0];
        root->min[1] = root->min[1] < point[1] ? root->min[1] : point[1];
        root->max[0] = root->max[0] > point[0] ? root->max[0] : point[0];
        root->max[1] = root->max[1] > point[1] ? root->max[1] : point[1];
    }
    return root;
}

// Function to insert a new point with given point in
// KD Tree and return new root. It mainly uses above recursive
// function "insertRec()"
Node *Insert(Node *(&root), double point[], int& id) {
    return insertRec(root, point, id, 0);
}



inline Node *deleteNodeRec(Node *(&root), double point[], int& id, int depth) {
    // Given point is not present
    if (root == NULL)
        return NULL;

    // Find dimension of current node
    int cd = depth % k;

    // If the point to be deleted is present at root
    if (root->id == id) {
        //std::cout<<"to be deleted: "<<root->id<<std::endl;
        root->isDeleted = true;
        return root;
    }
    // 2) If current node doesn't contain point, search downward
    if (point[cd] < root->point[cd]) {
        root->left = deleteNodeRec(root->left, point, id, depth + 1);
    }
    else {
        root->right = deleteNodeRec(root->right, point, id, depth + 1);
    }
    return root;
}

// Function to delete a given point from K D Tree with 'root'
Node *Delete(Node *(&root), double point[], int& id) {
// Pass depth as 0
    return deleteNodeRec(root, point, id, 0);
}

inline void searchRangeRec(Node *(&root), double min[], double max[], int depth) {

    // Given point is not present
    if (root == NULL ||min[0] > root->max[0] || min[1] > root->max[1]
        || max[0] < root->min[0] || max[1] < root->min[1])
        return;

    // Find dimension of current node
    int cd = depth % k;

    bool isAtLeft, isAtRight, isAtMiddle;

    isAtLeft = min[cd] < root->point[cd];
    isAtRight = max[cd] > root->point[cd];
    isAtMiddle = root->point[cd ^ 1] > min[cd ^ 1] && root->point[cd ^ 1] < max[cd ^ 1];

    if (!root->isDeleted && isAtLeft && isAtRight && isAtMiddle) {
        hit_ids.push_back(root->id);
    }

    if (isAtLeft) {
        searchRangeRec(root->left, min, max, depth + 1);
    }
    if (isAtRight) {
        searchRangeRec(root->right, min, max, depth + 1);
    }
}

void Search(Node *(&root), double min[], double max[]) {
    searchRangeRec(root, min, max, 0);
}
