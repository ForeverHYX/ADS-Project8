#include "include/SkipList.hpp"

// Node constructor
Node::Node(int value, int level) : value(value), forward(level + 1, nullptr) {}

// SkipList constructor
SkipList::SkipList(int maxLevel, float probability)
    : maxLevel(maxLevel), probability(probability), currentLevel(0), gen(rd()), dist(0.0f, 1.0f) {
    header = new Node(-1, maxLevel);  // Create header node with value -1
}

// Generate random level for new node
int SkipList::randomLevel() {
    int level = 0;
    while (dist(gen) < probability && level < maxLevel - 1) {
        level++;
    }
    return level;
}

// Insert a value into the skip list
void SkipList::insert(int value) {
    std::vector<Node*> update(maxLevel + 1, nullptr);  // Stores predecessors at each level
    Node* current = header;

    // Find position from highest level down
    for (int i = currentLevel; i >= 0; --i) {
        while (current->forward[i] != nullptr && current->forward[i]->value < value) {
            current = current->forward[i];
        }
        update[i] = current;  // Update predecessor at each level
    }

    current = current->forward[0];  // Move to next node at lowest level

    // If node not found, insert new node
    if (current == nullptr || current->value != value) {
        int newLevel = randomLevel();  // Generate new level for node

        if (newLevel > currentLevel) {  // Increase max level if needed
            for (int i = currentLevel + 1; i <= newLevel; ++i) {
                update[i] = header;  // Set header as predecessor for new levels
            }
            currentLevel = newLevel;  // Update skip list's max level
        }

        // Create new node
        Node* newNode = new Node(value, newLevel);

        // Update pointers at each level
        for (int i = 0; i <= newLevel; ++i) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}

// Delete a value from the skip list
void SkipList::deleteValue(int value) {
    std::vector<Node*> update(maxLevel + 1, nullptr);  // Stores predecessors at each level
    Node* current = header;

    // Find position from highest level down
    for (int i = currentLevel; i >= 0; --i) {
        while (current->forward[i] != nullptr && current->forward[i]->value < value) {
            current = current->forward[i];
        }
        update[i] = current;  // Update predecessor at each level
    }

    current = current->forward[0];  // Move to next node at lowest level

    // If node found, delete it
    if (current != nullptr && current->value == value) {
        // Update pointers at each level
        for (int i = 0; i <= currentLevel; ++i) {
            if (update[i]->forward[i] != current) {
                break;
            }
            update[i]->forward[i] = current->forward[i];
        }

        // Decrease max level if necessary
        while (currentLevel > 0 && header->forward[currentLevel] == nullptr) {
            --currentLevel;
        }

        delete current;  // Delete the node
    }
}

// Search for a value in the skip list
bool SkipList::search(int value) {
    Node* current = header;

    // Find position from highest level down
    for (int i = currentLevel; i >= 0; --i) {
        while (current->forward[i] != nullptr && current->forward[i]->value < value) {
            current = current->forward[i];
        }
    }

    current = current->forward[0];  // Move to next node at lowest level
    return current != nullptr && current->value == value;
}

// Display the structure of the skip list
void SkipList::display() {
    for (int i = currentLevel; i >= 0; --i) {
        Node* current = header->forward[i];
        std::cout << "Level " << i << ": ";
        while (current != nullptr) {
            std::cout << current->value << " -> ";
            current = current->forward[i];
        }
        std::cout << "nullptr" << std::endl;
    }
}

// Destructor to clean up memory
SkipList::~SkipList() {
    Node* current = header;
    while (current != nullptr) {
        Node* next = current->forward[0];
        delete current;
        current = next;
    }
}
