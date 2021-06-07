#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#define N 8 // Initial array size

template<typename T>
class DynamicArray {
    T* array;
    int current_size;
    int array_size;

public:
    DynamicArray() : array(new T[N]) , current_size(0) , array_size(N) {}
    ~DynamicArray() {
        delete [] array;
    }
    T& operator[](int n)
    {
       return array[n];
    }
    T* reallocTheArray (T* old_array, int current , int new_size)
    {
        T* new_array = new T[new_size];
        for (int i = 0; i < current; ++i) {
            new_array[i] = old_array[i];
        }
        delete [] old_array;
        array_size = new_size;
        return new_array;
    }
    void push (T& data) {
        array[current_size] = data;
        current_size++;
        if ( current_size == array_size ) array = reallocTheArray(array,current_size,2*array_size);
    }
    void pop() {
        current_size--;
        if ( 4*current_size == array_size && current_size!=0 )
            array = reallocTheArray(array,current_size,(array_size/2));
    }
    int get_current_size(){
        return current_size;
    }
};

#endif //DYNAMIC_ARRAY_H
