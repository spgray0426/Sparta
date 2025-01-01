#include <iostream>
#include <algorithm>
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
        if (currentSize >= currentCapacity)
        {
            resize(currentCapacity + 5);
        }
        
        data[currentSize] = value;
        currentSize++;
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

    void sortData()
    {
        std::sort(data, data + currentSize);
    }
    
    ~SimpleVector()
    {
        delete[] data;
    }

private:
    void resize(int newCapacity)
    {
        if (newCapacity > currentCapacity)
        {
            T* newData = new T[newCapacity];
            for (int i = 0; i < currentSize; i++)
            {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            currentCapacity = newCapacity;
        }
    }
    
};
/*
int main() {
    SimpleVector<int> sv(3);
    
    sv.push_back(7);
    sv.push_back(2);

    cout << sv.size() << endl;
    cout << sv.capacity() << endl;

    sv.pop_back();
    cout << sv.size() << endl;

    sv.push_back(3);
    sv.push_back(6);
    sv.push_back(5);
    sv.push_back(4);

    cout << "sv : [";
    for (int i = 0; i < sv.size(); i++)
    {
        cout << sv[i];
    }
    cout << "]" << endl;
    
    cout << sv.size() << endl;
    cout << sv.capacity() << endl;

    sv.sortData();

    cout << "sv : [";
    for (int i = 0; i < sv.size(); i++)
    {
        cout << sv[i];
    }
    cout << "]" << endl;
    return 0;
}
*/