#include "Dictionary.h"
#include <bits/stdc++.h>
#include <algorithm>
#include <stack>
#include <map>
#include "Node.h"

using namespace std;

template <class K, class V>
int Dictionary<K, V>::height(Node<K, V>* node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

template <class K, class V>
Node<K, V>* Dictionary<K, V>::newNode(const K& key, const V& value)
{
    Node<K, V>* node = new Node<K, V>();
    node->key = key;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

template <class K, class V>
Node<K,V>*  Dictionary<K, V>::rightRotate(Node<K, V>* node)
{
    Node<K, V>* initLeft = node->left;
    Node<K, V>* leftsRight = initLeft->right;

    initLeft->right = node;
    node->left = leftsRight;

    node->height = max(height(node->left), height(node->right)) + 1;
    initLeft->height = max(height(initLeft->left), height(initLeft->right)) + 1;

    return initLeft;
}

template <class K, class V>
Node<K, V>*  Dictionary<K, V>::leftRotate(Node<K, V>* node)
{
    Node<K, V>* initRight = node->right;
    Node<K, V>* rightsLeft = initRight->left;

    initRight->left = node;
    node->right = rightsLeft;

    node->height = max(height(node->left), height(node->right)) + 1;
    initRight->height = max(height(initRight->left), height(initRight->right)) + 1;

    return initRight;
}

template <class K, class V>
int Dictionary<K, V>::getBalance(Node<K, V> *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

template <class K, class V>
Node<K, V>* Dictionary<K, V>::insert(Node<K, V>* node, const K& key, const V& value)
{
    if (node == NULL) {
        size_++;
        return newNode(key, value);
    }

    if (key < node->key)
        node->left = insert(node->left, key, value);
    else if (key > node->key)
        node->right = insert(node->right, key, value);
    else {
        node->value = value;
        return node;
    }


    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

template <class K, class V>
Node<K, V>* Dictionary<K, V>::minValueNode(Node<K, V>* node)
{
    Node<K, V>* current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

template <class K, class V>
Node<K, V>* Dictionary<K, V>::deleteNode(Node<K, V>* root, const K& key)
{
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if(key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if((root->left == NULL) || (root->right == NULL)) {
            Node<K, V> *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }

            free(temp);
        } else {
            Node<K, V>* temp = minValueNode(root->right);

            root->key = temp->key;

            root->right = deleteNode(root->right,temp->key);
        }

        size_--;
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

template <class K, class V>
void Dictionary<K, V>::preOrder(Node<K, V>* root)
{
    if(root != NULL) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

template<class K, class V>
Dictionary<K, V>::Dictionary() {
    root_ = NULL;
    size_ = 0;
}

template<class K, class V>
void Dictionary<K, V>::put(const K& key, const V& value) {
    root_ = insert(root_, key, value);
}

template<class K, class V>
void Dictionary<K, V>::remove(const K& key) {
    root_ = deleteNode(root_, key);
}

template<class K, class V>
int Dictionary<K, V>::size() const {
    return size_;
}

template<class K, class V>
V* Dictionary<K, V>::get(const K& key) {
    Node<K, V>* node = root_;
    while (node != NULL) {
        if (node->key == key) {
            return &node->value;
        }

        if (key < node->key) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    return nullptr;
}

template<class K, class V>
const V &Dictionary<K, V>::operator[](const K &key) const {
    V* value = get(key);
    if (value == nullptr) {
        if (std::is_class<V>::value) {
            put(key, V());
        } else {
            put(key, NULL);
        }

        return *get(key);
    } else {
        return *value;
    }
}

template<class K, class V>
V &Dictionary<K, V>::operator[](const K &key) {
    V* value = get(key);
    if (value == nullptr) {
        if (std::is_class<V>::value) {
            put(key, V());
        } else {
            put(key, NULL);
        }

        return *get(key);
    } else {
        return *value;
    }
}

template<class K, class V>
bool Dictionary<K, V>::contains(const K &key) {
    return get(key) != nullptr;
}

template<class K, class V>
const typename Dictionary<K, V>::Iterator Dictionary<K, V>::iterator() const {
    return Dictionary::Iterator(*this);
}

template<class K, class V>
typename Dictionary<K, V>::Iterator Dictionary<K, V>::iterator() {
    return Dictionary::Iterator(*this);
}

template<class K, class V>
Dictionary<K, V>::~Dictionary() {
}

template<class K, class V>
Dictionary<K, V>::Iterator::Iterator(Dictionary<K, V>& dictionary) {
    stackNext_ = std::stack<Node<K, V>*>();
    stackPrevious_ = std::stack<Node<K, V>*>();

    pushToLeft(dictionary.root_);
}

template<class K, class V>
const V &Dictionary<K, V>::Iterator::get() const {
    Node<K, V>* node = stackNext_.top();

    return node->value;
}

template<class K, class V>
void Dictionary<K, V>::Iterator::set(const V &value) {
    Node<K, V>* node = stackNext_.top();
    node->value = value;
}

template<class K, class V>
const K &Dictionary<K, V>::Iterator::key() const {
    Node<K, V>* node = stackNext_.top();

    return node->key;
}

template<class K, class V>
void Dictionary<K, V>::Iterator::next() {
    Node<K, V>* node = stackNext_.top();
    stackNext_.pop();
    stackPrevious_.push(node);
}

template<class K, class V>
void Dictionary<K, V>::Iterator::prev() {
    Node<K, V>* node = stackPrevious_.top();
    stackPrevious_.pop();
    stackNext_.push(node);
}

template<class K, class V>
bool Dictionary<K, V>::Iterator::hasNext() const {
    return stackNext_.size() > 1;
}

template<class K, class V>
bool Dictionary<K, V>::Iterator::hasPrev() const {
    return !stackPrevious_.empty();
}

template<class K, class V>
void Dictionary<K, V>::Iterator::pushToLeft(Node<K, V>* node) {
    if (node != nullptr) {
        pushToLeft(node->right);
        pushToLeft(node->left);

        stackNext_.push(node);
    }
}
