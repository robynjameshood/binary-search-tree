#include <string>
#include <functional>

class BST
{
public:
    ~BST();

    using KeyType = int; // implied key type
    using ItemType = std::string; // implied item type
    ItemType* lookup(KeyType); // lookup function definition
    void insert(KeyType, ItemType); // insertion definition
    void displayEntries();
    void remove(KeyType);
    void displayTree();
    void removeIf(std::function<bool(KeyType)>);
    static bool isEven(KeyType);
    static bool isOdd(KeyType);
    static bool isNegative(KeyType);

    BST() { // procedure for blank root node (leaf)
        root = new Node;
    }

    BST(KeyType key, ItemType item) { // procedure for populated root node
        root = new Node(key, item);
    }


private:
    struct Node { // struct definition
        KeyType key;
        ItemType item;
        Node* leftChild;
        Node* rightChild;

        Node() { // constructer for empty node (leaf)
            key = NULL;
            item = "";
            leftChild = leaf();
            rightChild = leaf();
        };

        Node(KeyType newKey, ItemType newItem) // constructer for populated node
        {
            key = newKey;
            item = newItem;
            leftChild = new Node;
            rightChild = new Node;
        };
    };

    Node* root = leaf();
    ItemType* searching(KeyType, Node*);
    Node* minNode(Node*);

    static Node* leaf() {
        return nullptr;
    }

    static bool isLeaf(Node* node)
    {
        return (node == nullptr);
    }

    void inserting(KeyType, ItemType, Node*);
    void displayingEntries(Node*);
    void displayingTree(Node* node, int = 0, int left = 2);
    void removing(KeyType, Node*);
    void removingIf(std::function<bool(KeyType)>, Node*);

    void deepDelete(Node*);
};
