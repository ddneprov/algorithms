#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

//Можно создавать любое количество любых вспомогательных классов, структур и методов для решения задачи.

//Функция для построения кучи
//Ответ должен лежать в массиве ages

void create (int *ages, int n, int i)
{
    int left_ch;// левое дитя
    int right_ch; // правое дитя

    int max;
    int parent = i;

    while(true)
    {
        left_ch = (parent + 1) * 2 - 1;
        right_ch = (parent + 1) * 2;

        if(left_ch >= n)
            break;

        if (right_ch < n && ages[right_ch] > ages[left_ch]) // поиск  наибольшего
            max = right_ch;
        else
            max = left_ch;

        if(ages[parent] >= ages[max])
            break;

        swap(ages[parent], ages[max]);
        parent = max;
    }
}





void heapBuild(int *ages, int n)
{
    for(int i = n / 2 - 1 /* родитель нижнего ребенка*/; i >= 0; --i)
        create(ages, n, i);


    for(int i = n - 1; i >= 0 ; --i)
    {
        swap(ages[0], ages[i]);
        create(ages, i, 0);
    }

}






















//Не удалять и не изменять метод main без крайней необходимости.
//Необходимо добавить комментарии, если все же пришлось изменить метод main.
int main()
{
    //Объект для работы с файлами
    ReadWriter rw;

    int *brr = nullptr;
    int n;

    //Ввод из файла
    n = rw.readInt();

    brr = new int[n];
    rw.readArray(brr, n);

    //Запуск построения кучи, ответ в том же массиве (brr)
    heapBuild(brr, n);

    //Запись в файл
    rw.writeArray(brr, n);

    //освобождаем память
    delete[] brr;

    return 0;
}
