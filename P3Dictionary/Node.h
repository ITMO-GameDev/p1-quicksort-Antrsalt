#ifndef P3DICTIONARY_NODE_H
#define P3DICTIONARY_NODE_H

template <class K, class V>
class Node {
    public:
        K key;
        V value;
        Node<K, V>* left;
        Node<K, V>* right;
        int height;
};

#endif //P3DICTIONARY_NODE_H
