#include <iostream>
#include <vector>
using namespace std;

int* resize(int* array, int size_old, int new_size){int* narray = new int[new_size];memcpy( narray, array, size_old * sizeof(int) );delete[] array;array=narray;return narray;}

template <class T>
class CircularArray
{
private:
    T *array;
    int capacity;
    int back, front;
    
public:
    CircularArray();
    CircularArray(int _capacity);
    virtual ~CircularArray();
    void push_front(T data);
    void push_back(T data);
    void insert(T data, int pos);
    T pop_front();
    T pop_back();
    bool is_full();
    bool is_empty();
    int size();
    void clear();
    T &operator[](int a){
        return array[(front+a)%capacity];
    };
    void sort();
    bool is_sorted();
    void reverse();
    string to_string(string sep=" ");

private:
    int next(int);
    int prev(int);
};

template <class T>
bool CircularArray<T>::is_empty()
{
    return (front==-1);
}
template <class T>
bool CircularArray<T>::is_full()
{
    return  front==next(back) || (front==0 && back==capacity-1);
}

template <class T>
void CircularArray<T>::push_back(T data){
    if (is_full()){
        array=resize(array,size(),size()+capacity);
    }
    if(back == -1 ){ front=0; back=0;}
    else back=next(back);
    array[back]=data;

}

template <class T>
void CircularArray<T>::push_front(T data){
    if(is_full()){
        array=resize(array,size(),size()+capacity);
    }
    if(front == -1 ){ front=0; back=0;}
    else front=prev(front);
    array[front]=data;
}

template <class T>
T CircularArray<T>::pop_front(){
 if (is_empty()) return 0;
 if (front==back){back=-1; front=-1;}
 else{
     if (front==size()-1) front=0;
     else front=next(front);
 }
 return array[prev(front)];
}

template <class T>
T CircularArray<T>::pop_back(){
    if (is_empty()) return 0;
    if (front==back){back=-1; front=-1;}
    else{
        if (back==0) back=size()-1;
        else back=prev(back);
    }
    return array[next(back)];
}

template <class T>
int CircularArray<T>::size() {
    if(back > front) return back - front + 1;
    else return back - front + capacity + 1;
}
template <class T>
bool CircularArray<T>::is_sorted()
{
    for(int i=0; i<size()-1; i++){
        if(array[i]>array[i+1]) return false;
    }
    return true;
}

template <class T>
void CircularArray<T>::sort()
{
    for(int i = front; i != back - 1; i = next(i)){
        int min_idx = i;
        for (int j = next(i); j != next(back); j=next(j))
            if (array[j] < array[min_idx])
                min_idx = j;

        // Swap the found minimum element with the first element
        T temp= array[min_idx];
        array[min_idx]=array[i];
        array[i]= temp;
    }
}

template <class T>
void CircularArray<T>::reverse()
{
    
    T temp;
    int begin=front;
    int end=back;
    while(begin!=end){
        temp=array[begin];
        array[begin]=array[end];
        array[end]=temp;
        begin=next(begin);
        end=prev(end);
    }

/*
    T* temp = new T[size()];
    cout<<size()<<endl;
    for(int i=front; i!=back; i=next(i)){

        temp[i]=array[size()-i];
    }
    delete [] array;
    array=temp;
*/
}


template <class T>
CircularArray<T>::CircularArray()
{
    CircularArray(0);
}


template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->array = new T[_capacity];
    this->capacity = _capacity;
    this->front = this->back = -1;
}

template <class T>
CircularArray<T>::~CircularArray()
{
    delete[] array;
}

template <class T>
int CircularArray<T>::prev(int index)
{
    return (index == 0) ? capacity - 1 : index - 1;
}

template <class T>
int CircularArray<T>::next(int index)
{
    return (index + 1) % capacity;
}

template <class T>
string CircularArray<T>::to_string(string sep)
{
    string result = ""; 
    for (int i = 0; i < size(); i++)
        result += std::to_string((*this)[i]) + sep;
    return result;
}
