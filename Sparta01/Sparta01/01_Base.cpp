#include <iostream>
using namespace std;

int sum(int num[], size_t size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += num[i];
    }
    return sum;
}

int avg(int sum, size_t size)
{
    return sum / size;
}
/*
int main() {
    int num[5];
    cout << "숫자 다섯개를 입력해 주세요";
    cin >> num[0] >> num[1] >> num[2] >> num[3] >> num[4];

    cout << "합계 :";
    cout << sum(num, sizeof(num) / sizeof(int)) << endl;

    cout << "평균 :";
    cout << avg(sum(num, sizeof(num) / sizeof(int)), sizeof(num) / sizeof(int)) << endl;
    return 0;
}
*/