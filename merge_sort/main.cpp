#include "ReadWriter.h"
#include "MergeSort.h"
//iostream, fstream включены в ReadWriter.h

//Не рекомендуется добавлять собственные вспомогательные классы и методы.
//Необходимо использовать уже имеющиеся классы и методы, добавив реализацию, соответствующую описанию.
using namespace std;


void MergeSort::sort(int *arr, int length)
{
    divide_and_merge(arr, 0, length - 1);
    //merge(arr, 1, 5, 8);
}

//Метод слияния двух отсортированных секций массива в одну сортированную секцию.
void MergeSort::merge(int* arr, int first, int second, int end)
{

    int lenght = end - first;
    int mid = second - first;
    int* arr2 = new int[lenght + 1];
    for(int i = 0; i < lenght + 1; ++i)
        arr2[i] = arr[first + i];

    int part_one = 0;
    int part_two = mid + 1;

    for(int i = 0; i <= lenght; ++i)
    {
        if (part_one > mid || (part_two <= lenght && arr2[part_one] > arr2[part_two]))
        {
            arr[i + first] = arr2[ part_two++];
        }
        else
            arr[i + first] = arr2[ part_one++];
    }
    delete[] arr2;
}




//Рекурсивно разбивает массив на две части и объединяет их в пределах [ слева (включительно), справа (исключительно)]
void MergeSort::divide_and_merge(int *arr, int left, int right)
{
    // [0] [1] [2] [3] [4] [5] [6] [7]
    //  2   3   8   9   3   5   9   1

    if (left < right)
    {
        int m = (left + right) / 2;
        divide_and_merge(arr, left, m);
        divide_and_merge(arr, m + 1, right);
        merge(arr, left, m, right);
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









/* int r = right - left, m = middle - left;
  int* arr2 = new int[r + 1];
  for(int i = 0; i < r + 1; ++i)
      arr2[i] = arr[left + i];

  int p1 = 0, p2 = m + 1;
  for(int i = 0; i <= r; ++i)
      arr[i + left] = arr2[p1 > m || (p2 <= r && arr2[p1] > arr2[p2]) ? p2++ : p1++];

  delete[] arr2;
*/


/*
 * если остались элементы
 */
/*while (second!=end)
{
    arr[i] = arr[first];
    first++;
}

while (mid!=first)
{
    arr[i] = arr[second];
    second++;
}*/






/*

int lenght1 = second - first;
int lenght2 = end - second;

int *arr1 = new int[lenght1]; // создаем доп массив
int *arr2 = new int[lenght2]; // создаем доп массив

for (int j = 0; j < lenght1; j++) { // заполняем левый массив
arr1[j] = arr[j+first];
}

for (int j = 0; j < lenght2; j++) { // заполняем правый массив
arr2[j] = arr[j+second];
}


///выбираем самый короткий массив
int shortest;
if (lenght1 <= lenght2)
shortest = lenght1;
else
shortest = lenght2;


///заполняем основную часть массива
int l = 0; //заполняем основную часть массива
for (l; l < shortest; shortest++)
{
if (arr1[l] > arr2[l])
arr[first] = arr2[l];
else
arr[first] = arr1[l];
}

///дополняем если массивы разной дины
if(l==lenght1) // если первый массив меньше
{
for( int y = l; y < lenght2 ; y++)
{
arr[y] = arr2[y];
}
}
else // если второй массив меньше
{
for( int y = 0; y < lenght1 ; y++)
{
arr[y] = arr1[y];
}
}

*/
