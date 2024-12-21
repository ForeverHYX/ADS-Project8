#include <iostream>
#include "include/SkipList.hpp"

int main() {
    SkipList skipList;  // Create a new SkipList instance

    // Insert elements into the skip list
    skipList.insert(3);
    skipList.insert(6);
    skipList.insert(7);
    skipList.insert(9);
    skipList.insert(12);
    skipList.insert(19);
    skipList.insert(17);
    skipList.insert(26);

    // Display the structure of the skip list
    skipList.display();

    // Search for elements in the skip list
    std::cout << "Search 6: " << (skipList.search(6) ? "Found" : "Not Found") << std::endl;
    std::cout << "Search 15: " << (skipList.search(15) ? "Found" : "Not Found") << std::endl;

    // Delete an element and display the list again
    skipList.deleteValue(6);
    skipList.display();

    // Search for the deleted element
    std::cout << "Search 6 after deletion: " << (skipList.search(6) ? "Found" : "Not Found") << std::endl;

    return 0;
}
