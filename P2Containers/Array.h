#ifndef P2CONTAINERS_ARRAY_H
#define P2CONTAINERS_ARRAY_H

template <typename T>
class Array {
    class Iterator
    {
        friend class Array<T>;

        public:
            Iterator(Array<T>& arr);
            const T& get() const;
            void set(const T& value);
            void insert(const T& value);
            void remove();
            void next();
            void prev();
            void toIndex(int index);
            bool hasNext() const;
            bool hasPrev() const;
        private:
            Array<T>& array_;
            int index_;
    };

public:
    Array();
    Array(int capacity);
    ~Array();
    void insert(const T& value);
    void insert(int index, const T& value);
    void remove(int index);
    int size();
    int capacity();
    const T& operator[](int index) const;
    T& operator[](int index);
    Iterator iterator();
    const Iterator iterator() const;

protected:
    T* array_;
    int size_;
    int capacity_;
    void extend();
};


#endif //P2CONTAINERS_ARRAY_H
