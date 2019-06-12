#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include<math.h>
using namespace std;

class ShannonFano
{

private:

    vector<int> probabilities;
    int total;

    int* content;
    string* code;


public:




    ShannonFano()// можно изменить что бы принимал на вход количесво элементов
    {
        total = 0; //
    }


    void fillCodes(int total, int* begin, int* end)
    {
        int* med = begin;
        int* next = begin + 1;
        int left_sum = *begin;

        while(fabs(left_sum + *next - (total - left_sum - *next)) < fabs(left_sum - (total - left_sum)))
        {
            left_sum += *next;
            med = next;
            ++next;
        }




        int i = ((int)(begin - content));
        while(i < med + 1 - content)// задаем цифорки слева
        {
            code[i] += '0';
            ++i;
        }

        while(i < end + 1 - content) // и справа
        {
            code[i] += '1';
            ++i;
        }




        /// теперь рекрусивно
        if(med - begin > 0)
            fillCodes(left_sum, begin, med);


        if(end - med > 1)
        {
            //total = total - left_sum;
            //med++;
            fillCodes(total - left_sum, med + 1, end);
        }
    }

    void build()
    {
        long n = (long)(probabilities.size());
        code = new string[n];
        content = probabilities.data();
        fillCodes(total, content, content + n - 1);


    }

    void addChance (int chance)
    {
        probabilities.push_back(chance);
        total += chance;
    }

    string get (int i)
    {
        return code[i];
    }
};



int main() {

	int n;
    ShannonFano * shf = new ShannonFano();
 
    fstream fin;
        fin.open("input.txt",ios::in);
        if(fin.is_open()) {
            fin >> n;
            for (int i = 0; i < n; i++) {
                int x;
                fin >> x;
				shf->addChance (x);
            }
            fin.close();
       
        shf->build();
        fstream fout;
        fout.open("output.txt",ios::out);
            for (int i = 0; i < n; i++){
                fout <<shf->get(i) << (i==n-1?"":" ");
                }
        fout.close();
        delete shf;
            
        }
        return 0;		
}



















/* int median(int begin, int end)
   {
       long left_sum = 0;
       for (int j = begin; j < end - 1; ++j) {
           left_sum += probabilities[j];
       }

       long right_sum = probabilities[end];
       int med = end;
       do
       {
           int d = left_sum - right_sum;
           med--;
           left_sum -= probabilities[med]; right_sum += probabilities[med];
       }
       while(fabs(left_sum - right_sum) < d);
       return med;
   }*/





