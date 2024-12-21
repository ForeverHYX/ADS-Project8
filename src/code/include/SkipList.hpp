#ifndef SKIPLIST_HPP
#define SKIPLIST_HPP

#include <vector>
#include <random>
#include <iostream>

class Node {
public:
    int value;
    std::vector<Node*> forward;  // Next nodes at each level

    Node(int value, int level);
};

class SkipList {
private:
    Node* header;
    int maxLevel;
    int currentLevel;
    // Random key generator
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<float> dist;

    int randomLevel();

public:
    SkipList(int maxLevel = 16, float probability = 0.5);
    ~SkipList();

    void insert(int value);
    void deleteValue(int value);
    bool search(int value);
    void display();
};

#endif
