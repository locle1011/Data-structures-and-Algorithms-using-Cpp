#ifndef TREE_ITEM_H
#define TREE_ITEM_H

enum TraversalType
{
    IN,
    PRE,
    POST,
    LEVELS
};

template <typename T>
struct Node
{
    T data;
    int count;
    int height;
    Node *left;
    Node *right;

    Node(const T &data) : data(data), count(0), height(1), left(nullptr), right(nullptr) {}
    Node(const T &data, const int &count, const int &height) : data(data), count(count), height(height), left(nullptr), right(nullptr) {}
};

#endif // !TREE_ITEM_H