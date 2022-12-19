﻿#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <fstream>
using namespace std;

double PCFreq = 0.0; // PC內的電磁頻率
__int64 CounterStart = 0;

// 計時開始
void StartTime()
{
    LARGE_INTEGER li;  // 帶符號的 64 位整數。
    if (!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart) / 1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
// 取得經過的時間
double GetTime()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - CounterStart) / PCFreq;
}
// 印出計算後的時間
void Print_Time(int i, double TimeAdd) {
    fstream outfile;
    outfile.open("C:\\Users\\MSI GP65\\Desktop\\Sroting 資料\\Sort - CostTime\\Time - C_Array-Bubble_sort.txt", ios::app);
    if (TimeAdd < 1000)
    {
        outfile << "排序" << i << "筆資料所花費時間: "
            << TimeAdd << "毫秒\n"
            << endl;
        outfile.close();
    }
    else
    {
        outfile << "排序" << i << "筆資料所花費時間: "
            << TimeAdd / 1000.0 << "秒\n"
            << endl;
        outfile.close();
    }
}

// 排序用 (氣泡排序法)
template <class TypeA>
void Bubble_sort(TypeA* pData, int nSize)
{
    StartTime();
    for (int i = 0; i < nSize - 1; i++) {
        for (int j = 0; j < nSize - i - 1; j++) {
            if (pData[j] > pData[j + 1]) {
                TypeA temp = pData[j];
                pData[j] = pData[j + 1];
                pData[j + 1] = temp;
            }
        }
    }
    double TimeAdd = GetTime();
    Print_Time(nSize, TimeAdd);
    //return *pData;
}

// 印出排序後的陣列
template <class TypeA>
TypeA Print(TypeA* pDate, int nSize)
{
    cout << "資料: ";
    for (int i = 0; i < nSize; i++) {
        cout << pDate[i] / 10000.0 << " ";
    }
    cout << endl;
    return 1;
}

// 產生亂數
template <class TypeA>
void Produce_random(TypeA* pData, int nSize, char TypeKey)
{
    srand(time(NULL));
    switch (TypeKey) {
    case 'I':
        for (int i = 0; i < nSize; i++)
        {
            pData[i] = rand() % nSize + 1;
        }
        break;
    case 'F':
        for (int i = 0; i < nSize; i++) {
            /* 產生 [0, 1) 的浮點數亂數 */
            pData[i] = (float)rand() / (RAND_MAX + 1.0);
            // 常數 RAND_MAX 是 rand 函式可傳回的最大值。
        }
        break;
    case 'D':
        for (int i = 0; i < nSize; i++) {
            /* 產生 [0, 1) 的浮點數亂數 */
            pData[i] = (double)rand() / (RAND_MAX + 1.0);
            // 常數 RAND_MAX 是 rand 函式可傳回的最大值。
        }
        break;
    default:
        cout << "型別不在搜尋範圍內!" << endl;
        break;
    }

    //return *pData;
}

// 產生字串亂數
template <class TypeA>
void Produce_Str_random(TypeA* pData, int nSize)
{
    srand(time(NULL));
    for (int i = 0; i < nSize; i++)
    {
        string temp = {};
        for (int j = 0; j < 6; j++)
        {
            // 0~25的亂數加上 97 就會剛好落在97~122之間，換算成ACSII碼就是小寫a~z
            temp += (char)(rand() % 26) + (97);
        }
        pData[i] = (string)temp;
    }
    //return *pData;
}

int main()
{
    cout << "-----------------冒泡排序法-----------------\n" << endl;

    // (int)整數型態
    cout << "\n# (int)整數型態---------------\n" << endl;
    for (int i = 10; i <= 60; i += 10)
    {
        int* DATA_Array = new int[i];
        Produce_random(DATA_Array, i, 'I');
        Bubble_sort(DATA_Array, i);

        delete[]DATA_Array;
    }

    for (int i = 100000; i <= 600000; i += 100000)
    {
        int* DATA_Array = new int[i];
        Produce_random(DATA_Array, i, 'I');
        Bubble_sort(DATA_Array, i);

        delete[]DATA_Array;
    }

    // (long int)長整數型態
    cout << "\n# (long int)長整數型態---------------\n" << endl;
    for (int i = 10; i <= 60; i += 10)
    {
        long int* DATA_Array = new long int[i];
        Produce_random<long int>(DATA_Array, i, 'I');
        Bubble_sort<long int>(DATA_Array, i);

        delete[]DATA_Array;
    }

    for (int i = 100000; i <= 600000; i += 100000)
    {
        long int* DATA_Array = new long int[i];
        Produce_random<long int>(DATA_Array, i, 'I');
        Bubble_sort<long int>(DATA_Array, i);

        delete[]DATA_Array;
    }

    // (float)浮點數型態
    cout << "\n# (float)浮點數型態---------------\n" << endl;
    for (int i = 10; i <= 60; i += 10)
    {
        float* DATA_Array = new float[i];
        Produce_random<float>(DATA_Array, i, 'F');
        Bubble_sort<float>(DATA_Array, i);

        delete[]DATA_Array;
    }

    for (int i = 100000; i <= 600000; i += 100000)
    {
        float* DATA_Array = new float[i];
        Produce_random<float>(DATA_Array, i, 'F');
        Bubble_sort<float>(DATA_Array, i);

        delete[]DATA_Array;
    }

    // (double)雙倍精度浮點數型態
    cout << "\n# (double)雙倍精度浮點數型態---------------\n" << endl;
    for (int i = 10; i <= 60; i += 10) {
        double* DATA_Array = new double[i];
        Produce_random<double>(DATA_Array, i, 'D');
        Bubble_sort<double>(DATA_Array, i);

        delete[]DATA_Array;
    }

    for (int i = 100000; i <= 600000; i += 100000)
    {
        double* DATA_Array = new double[i];
        Produce_random<double>(DATA_Array, i, 'D');
        Bubble_sort<double>(DATA_Array, i);

        delete[]DATA_Array;
    }

    // (string)字串型態，6個字母
    cout << "\n# (string)字串型態，6個字母---------------\n" << endl;
    for (int i = 10; i <= 60; i += 10)
    {
        string* DATA_Array = new string[i];
        Produce_Str_random<string>(DATA_Array, i);
        Bubble_sort<string>(DATA_Array, i);

        delete[] DATA_Array;
    }

    for (int i = 100000; i <= 500000; i += 100000)
    {
        string* DATA_Array = new string[i];
        Produce_Str_random<string>(DATA_Array, i);
        Bubble_sort<string>(DATA_Array, i);

        delete[]DATA_Array;
    }

    return 0;
}