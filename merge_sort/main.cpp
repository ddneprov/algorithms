#include "ReadWriter.h"
#include "MergeSort.h"
//iostream, fstream включены в ReadWriter.h

//Не рекомендуется добавлять собственные вспомогательные классы и методы.
//Необходимо использовать уже имеющиеся классы и методы, добавив реализацию, соответствующую описанию.
using namespace std;


void MergeSort::sort(int *arr, int length)
{
    divide_and_merge(arr, 0, length);
}

//Метод слияния двух отсортированных секций массива в одну сортированную секцию.
void MergeSort::merge(int* arr, int first, int second, int end)
{

}


//Рекурсивно разбивает массив на две части и объединяет их в пределах [ слева (включительно), справа (исключительно)]
void MergeSort::divide_and_merge(int *arr, int left, int right)
{
    // [0] [1] [2] [3] [4] [5] [6] [7]
    //  2   3   8   9   3   5   9   1

    ///--------------------
    //    2 3 8 9 3 5 9 1
    // 2 3 8 9       3 5 9 1




    int mid = (left + right) / 2;
    if (mid % 1 == 1)
        mid++;

    while ( left != right+1 )
    {
        divide_and_merge(arr, left, mid);
        divide_and_merge(arr, mid , right);
    }
}













int main()
{   
    ReadWriter rw;

    int *brr = nullptr;
    int length;

    //Read data from file
    length = rw.readInt();

    brr = new int[length];
    rw.readArray(brr, length);

    //Start sorting
    MergeSort s;

    s.sort(brr, length);
    
    //Write answer to file
    rw.writeArray(brr, length);

    delete[] brr;

    return 0;
}