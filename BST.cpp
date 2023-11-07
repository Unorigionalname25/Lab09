#include <iostream>
#include <vector>

template <typename T>
class BinarySearchTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;
    std::vector<T> elements;

    void insertRecursive(Node*& current, const T& value) {
        if (current == nullptr) {
            current = new Node(value);
            elements.push_back(value);
        } else {
            if (value < current->data) {
                insertRecursive(current->left, value);
            } else if (value > current->data) {
                insertRecursive(current->right, value);
            }
        }
    }

    bool searchRecursive(Node* current, const T& value) {
        if (current == nullptr) {
            return false;
        }
        if (value == current->data) {
            return true;
        }
        if (value < current->data) {
            return searchRecursive(current->left, value);
        } else {
            return searchRecursive(current->right, value);
        }
    }

    T findMinValue(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node->data;
    }

    Node* deleteNode(Node* current, const T& value) {
        if (current == nullptr) {
            return current;
        }

        if (value < current->data) {
            current->left = deleteNode(current->left, value);
        } else if (value > current->data) {
            current->right = deleteNode(current->right, value);
        } else {
            if (current->left == nullptr) {
                Node* temp = current->right;
                delete current;
                return temp;
            } else if (current->right == nullptr) {
                Node* temp = current->left;
                delete current;
                return temp;
            }

            current->data = findMinValue(current->right);
            current->right = deleteNode(current->right, current->data);
        }

        return current;
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(const T& value) {
        insertRecursive(root, value);
    }

    bool search(const T& value) {
        return searchRecursive(root, value);
    }

    void remove(const T& value) {
        root = deleteNode(root, value);
        // Update the elements array after deletion
        elements.clear();
        updateElements(root);
    }

    void updateElements(Node* current) {
        if (current == nullptr) {
            return;
        }
        updateElements(current->left);
        elements.push_back(current->data);
        updateElements(current->right);
    }

    void displayElements() {
        for (const T& element : elements) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
};




/*main_____________________________________________*/
int main() {
    BinarySearchTree<int> intBST;
    BinarySearchTree<char> charBST;
    BinarySearchTree<float> floatBST;
    BinarySearchTree<double> doubleBST;

    intBST.insert(5);
    intBST.insert(3);
    intBST.insert(7);
    intBST.insert(2);
    intBST.insert(4);
    intBST.insert(6);
    intBST.insert(8);

    charBST.insert('C');
    charBST.insert('A');
    charBST.insert('B');
    charBST.insert('E');
    charBST.insert('D');

    floatBST.insert(3.14f);
    floatBST.insert(2.71f);
    floatBST.insert(1.618f);

    doubleBST.insert(3.14159);
    doubleBST.insert(2.71828);

    std::cout << "Elements in intBST: ";
    intBST.displayElements();

    std::cout << "Elements in charBST: ";
    charBST.displayElements();

    std::cout << "Elements in floatBST: ";
    floatBST.displayElements();

    std::cout << "Elements in doubleBST: ";
    doubleBST.displayElements();

    int valueToSearch = 4;
    bool found = intBST.search(valueToSearch);
    if (found) {
        std::cout << valueToSearch << " is found in intBST." << std::endl;
    } else {
        std::cout << valueToSearch << " is not found in intBST." << std::endl;
    }

    int valueToDelete = 7;
    intBST.remove(valueToDelete);
    std::cout << "After deleting " << valueToDelete << ": ";
    intBST.displayElements();

    return 0;
}