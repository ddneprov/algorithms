#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

//Можно создавать любое количество любых вспомогательных классов, структур и методов для решения задачи.






//Необходимо реализовать алгоритм быстрой сортировки.
//В качестве опорного элемента выбирать случайный
void quickSort(int *numbers, int lBorder,  int rBorder) {
    int i = lBorder, j = rBorder;
    int x, buf;
    x = numbers[lBorder + rand() % (rBorder - lBorder + 1)]; // поменял рандом
    do {
        while (numbers[i] < x)
            i++;
        while (x < numbers[j])
            j--;
        if (i <= j) {
            swap(numbers[i], numbers[j]);
            i++;
            j--;
        }
    } while (i <= j);
    if (lBorder < j)
        quickSort(numbers, lBorder, j);
    if (rBorder > i)
        quickSort(numbers, i, rBorder);
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

    //Запуск сортировки, ответ в том же массиве (brr)
    quickSort(brr,0, n-1);

    //Запись в файл
    rw.writeArray(brr, n);

    //освобождаем память
    delete[] brr;

    return 0;
}