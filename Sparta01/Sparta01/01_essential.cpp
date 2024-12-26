#include <iostream>
using namespace std;

void sort(int arr[], int size, int choice) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (choice == 1)
            {
                if (arr[i] > arr[j]) {
                    int temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
            else if (choice == 2)
            {
                if (arr[i] < arr[j]) {
                    int temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }

        }
    }
}

void printarr(int arr[], size_t size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
}
int main() {
    int num[5];
    cout << "숫자 다섯개를 입력해 주세요: ";
    cin >> num[0] >> num[1] >> num[2] >> num[3] >> num[4];
    sort(num, 5, 2);

    cout << "정렬된 숫자: ";
    printarr(num, 5);
    return 0;
}
