#ifndef P3DICTIONARY_DICTIONARY_H
#define P3DICTIONARY_DICTIONARY_H

#include "Node.h"
#include<stack>

template <class K, class V>
class Dictionary {
        class Iterator
        {
            friend class Dictionary<K, V>;

            public:
                Iterator(Dictionary<K, V>& dictionary);
                const K& key() const;
                const V& get() const;
                void set(const V& value);
                void next();
                void prev();
                bool hasNext() const;
                bool hasPrev() const;

            private:
                void pushToLeft(Node<K, V>* node);

                std::stack<Node<K, V>*> stackNext_;
                std::stack<Node<K, V>*> stackPrevious_;
        };

    protected:
        Node<K, V>* root_;
        int size_;

        int height(Node<K, V>* node);
        Node<K, V>* newNode(const K& key, const V& value);
        Node<K, V>* rightRotate(Node<K, V>* node);
        Node<K, V>* leftRotate(Node<K, V>* node);
        int getBalance(Node<K, V>* node);
        Node<K, V>* insert(Node<K, V>* node, const K& key, const V& value);
        Node<K, V>* minValueNode(Node<K, V>* node);
        Node<K, V>* deleteNode(Node<K, V>* root, const K& key);
        void preOrder(Node<K, V>* root);
        V* get(const K& key);

    public:
        Dictionary();
        ~Dictionary();
        void put(const K& key, const V& value);
        void remove(const K& key);
        bool contains(const K& key);
        int size() const;
        Iterator iterator();
        const Iterator iterator() const;

        const V& operator [](const K& key) const;
        V& operator [](const K& key);
};

#endif //P3DICTIONARY_DICTIONARY_H
