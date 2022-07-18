#include "bst.h"
#include <iostream>

//-----DISPLAY-----
void BST::displayEntries()
{
    displayingEntries(root);
}

void BST::displayingEntries(Node* currentNode)
{
    if (isLeaf(currentNode->leftChild)) {
        return;
    }
    displayingEntries(currentNode->leftChild);
    std::cout << currentNode->key << " " << currentNode->item << std::endl;
    displayingEntries(currentNode->rightChild);
}

void BST::displayTree()
{
    displayingTree(root);
}

void BST::displayingTree(Node* currentNode, int counter, int left) // displays the tree with visual aid to emphasize node hierarchy/level. Does not represent left/right node allocation, just the hierarchy/level.
{
    if (isLeaf(currentNode->leftChild)) {
        for (int i = 0; i < counter; i++)
        {
            std::cout << " - ";
        }
        std::cout << "*" << "\n";
        counter -= 1;

        return;
    }

    for (int i = 0; i < counter; i++)
    {
        std::cout << " - ";
    }
    counter += 1;

    std::cout << currentNode->key << " " << currentNode->item << "\n";
    displayingTree(currentNode->leftChild, counter, 1);
    displayingTree(currentNode->rightChild, counter, 0);

    counter -= 1;
}


//-----LOOKUP-----//
BST::ItemType* BST::lookup(KeyType soughtKey)
{
    ItemType* itemName = searching(soughtKey, root);
    return itemName;
}

BST::ItemType* BST::searching(KeyType soughtKey, Node* currentNode)
{
    if (isLeaf(currentNode->leftChild)) // if the left-child of a current node is a leaf - return a null-pointer.
    {
        return nullptr;
    }
    else if (currentNode->key == soughtKey) // if the key matches our search - return the item.
    {
        return &currentNode->item;
    }
    else if (soughtKey < currentNode->key) // if the key is less than the current node key, begin recursion calls to traverse left/right children to find the key.
    {
        return searching(soughtKey, currentNode->leftChild);
    }
    else
    {
        return searching(soughtKey, currentNode->rightChild);
    }
}


//-----INSERT-----//
void BST::insert(KeyType newKey, ItemType newItem) {
    inserting(newKey, newItem, root);
}

void BST::inserting(KeyType key, ItemType item, Node* currentNode) { // function to insert a node based on it's key value.
    if (isLeaf(currentNode->leftChild)) { // if the current node, left child is a leaf, this inserts the key and the item.
        *currentNode = Node(key, item);
        return;
    }
    else if (key == currentNode->key) { // if the keys match, insert the item.
        currentNode->item = item;
        return;
    }
    else if (key < currentNode->key) { // if the key is less than that of the current key, inserts into the left child, if else (greater) inserts into the right child.
        inserting(key, item, currentNode->leftChild); 
    }
    else {
        inserting(key, item, currentNode->rightChild);
    }
}


//-----REMOVING-----//
void BST::remove(KeyType key)
{
    removing(key, root);
}

void BST::removing(KeyType key, Node* currentNode)
{
    if (isLeaf(currentNode)) { // if the current node is a leaf, return.
        return;
    }
    else if (key < currentNode->key) { // if the key is less than the currentNode key, removes the left child.
        removing(key, currentNode->leftChild);
    }
    else if (key > currentNode->key) { // conversely, if greater, removes the right child.
        removing(key, currentNode->rightChild);
    }
    else {
        if (isLeaf(currentNode->leftChild->leftChild) && isLeaf(currentNode->rightChild->rightChild)) { // This code removes/deletes a node as both children are leaves.
            *currentNode = Node();
        }
        else if (currentNode->leftChild->key == NULL && currentNode->leftChild->item == "") {
            // This will delete the node that has a populated right child, however, the left child is a leaf.
            delete currentNode->leftChild;
            Node* temp = currentNode->rightChild;
            *currentNode = Node(currentNode->rightChild->key, currentNode->rightChild->item);
            delete temp;
        }
        else if (currentNode->rightChild->key == NULL && currentNode->rightChild->item == "") {
            // Conversely, deletes the node that has a populated left child, the right child being a leaf.
            delete currentNode->rightChild;
            Node* temp = currentNode->leftChild;
            *currentNode = Node(currentNode->leftChild->key, currentNode->leftChild->item);
            delete temp;
        }
        else { // This handles two-children of a node to be removed.
            Node* temp = minNode(currentNode->rightChild);
            currentNode->key = temp->key;
            currentNode->item = temp->item;

            removing(temp->key, currentNode->rightChild);
        }
    }
}


BST::Node* BST::minNode(Node* currentNode) // This handles two-children of a node to be removed.
{
    while (currentNode->leftChild && currentNode->leftChild->leftChild) {
        currentNode = currentNode->leftChild;
    }
    return currentNode;
}


void BST::removeIf(std::function<bool(KeyType)> condition)
{
    removingIf(condition, root);
}

void BST::removingIf(std::function<bool(KeyType)> result, Node* currentNode) // first paramter is the result of a higher-order function.
{
    if (isLeaf(currentNode->leftChild)) {
        return;
    }
    removingIf(result, currentNode->leftChild);
    removingIf(result, currentNode->rightChild);
    if (result(currentNode->key)) {
        remove(currentNode->key);
    }

}

//-----HIGHER ORDER FUNCTIONS (results used as paramters in the above functions) -----//

bool BST::isEven(KeyType currentKey) {
    return !isOdd(currentKey); // recycles the below functon (inverted) to check for an even key.
}
bool BST::isOdd(KeyType currentKey) {
    return (currentKey % 2); // checks if the key is odd based on the modulas calcuation.
}
bool BST::isNegative(KeyType currentKey) {
    return (currentKey < 0); // checks to see if the key is negative based on the value being less than 0.
}

//-----DESTRUCTOR-----//

BST::~BST()
{
    deepDelete(root);
}

void BST::deepDelete(Node* current)
{
    if (isLeaf(current->leftChild))
    {
        return;
    }
    deepDelete(current->leftChild); // recurisely calls deep-delete on the left-child.
    deepDelete(current->rightChild); // performs the same recursive call, conversely, on the right-child.
    delete current; // performs the deletion of the node via the delete keyword.
}