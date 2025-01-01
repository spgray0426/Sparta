#include <iostream>
using namespace std;

template<typename T>
class SimpleVector
{
    T* data;
    int currentCapacity;
    int currentSize = 0;
public:
    SimpleVector(int size = 10) : data(new T[size]), currentCapacity(size){}

    void push_back(const T& value)
    {
        if (currentSize < currentCapacity)
        {
            data[currentSize] = value;
            currentSize++;
        }
    }

    void pop_back()
    {
        if (currentSize > 0)
        {
            data[--currentSize] =T();
        }
    }

    int size() const
    {
        return currentSize;
    }

    int capacity() const
    {
        return currentCapacity;
    }
    
    
    T& operator[](int index)
    {
        return data[index];
    }
    ~SimpleVector()
    {
        delete[] data;
    }
};
int main() {
    SimpleVector<int> sv(10);
    
    sv.push_back(1);
    sv.push_back(2);

    cout << sv.size() << endl;
    cout << sv.capacity() << endl;

    sv.pop_back();
    cout << sv.size() << endl;

    cout << sv[0] << endl;
    cout << sv[1] << endl;
    cout << sv[2] << endl;
    return 0;
}
