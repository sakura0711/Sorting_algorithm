#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <array>
#include <algorithm>
#include <iomanip>
#include <string>
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
inline double GetTime()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - CounterStart) / PCFreq;
}
// 印出計算後的時間
void Print_Time(double TimeAdd, int i, string TypeKeys) {
    fstream outfile;
    outfile.open("C:\\Users\\MSI GP65\\Desktop\\Sroting 資料\\Sort - CostTime\\Time - STD_Array-Selection_sort.txt", ios::app);
    if (TimeAdd < 1000)
    {
        outfile << "\n"
            << "(" << TypeKeys << ")"
            << "排序" << i << "筆資料所花費時間: "
            << TimeAdd << " 毫秒";
        outfile.close();
    }
    else if (TimeAdd < 60000)
    {
        outfile << "\n"
            << "(" << TypeKeys << ")"
            << "排序" << i << "筆資料所花費時間: "
            << TimeAdd / 1000.0 << " 秒";
        outfile.close();
    }
    else
    {
        outfile << "\n"
            << "(" << TypeKeys << ")"
            << "排序" << i << "筆資料所花費時間: "
            << TimeAdd / (1000.0 * 60) << " 分";
        outfile.close();
    }
}

// 排序用 (排序法STD_array)
template<typename T, size_t nSize>
void Selection_sort(array<T, nSize>* pData, string TypeKeys) noexcept
{
    float Percent = nSize / 100;
    double TimeAdd = 0.0; //儲存排序時間
    int min_index;
    T* index = pData->data();
    for (int i = 0; i < nSize; i = i + 1)
    {
        min_index = i;
        StartTime();
        for (int j = i + 1; j < nSize; j = j + 1)
        {
            if (index[min_index] > index[j])
            {
                min_index = j;
            }
        }
        T temp = index[min_index];
        index[min_index] = index[i];
        index[i] = temp;

        TimeAdd += GetTime();
        /*if (nSize >= 100000) {
            cout << "\r" << "Complate: "
                << fixed << setprecision(2) << ((i / Percent) + 0.001) << "%";
        }*/
    }
    Print_Time(TimeAdd, nSize, TypeKeys);
}

// 印出排序後的陣列(STD_array)
template <typename T, size_t nSize>
void Print(array<T, nSize>* pData)
{
    T* index = pData->data();

    //while 迴圈為取得資料位數，利於用setw()排版
    int Digits, SizeTemp = nSize;
    while (SizeTemp >= 10) {
        SizeTemp /= 10;
        Digits++;
    }

    cout << "資料: ";
    for (int i = 0; i < nSize; i++) {
        cout << setw(Digits) << index[i] << " ";
        if (i % 20 == 0 && i > 20) { cout << endl; }
    }
    cout << endl;
}

// 產生亂數(STD_array)
template<typename T, size_t nSize>
void Produce_random(array<T, nSize>* pData, char TypeKey) noexcept
{
    srand(time(NULL));
    T* index = pData->data(); // 將指標指向pData 的第一個元素位置
    switch (TypeKey) {
    case 'I':
        for (int i = 0; i < nSize; i++)
        {
            index[i] = rand() % nSize + 1;
        }
        break;
    case 'F':
        for (int i = 0; i < nSize; i++) {
            /* 產生 [0, 1) 的浮點數亂數 */
            index[i] = (float)rand() / (RAND_MAX + 1.0);
            // 常數 RAND_MAX 是 rand 函式可傳回的最大值。
        }
        break;
    case 'D':
        for (int i = 0; i < nSize; i++) {
            /* 產生 [0, 1) 的浮點數亂數 */
            index[i] = (double)rand() / (RAND_MAX + 1.0);
            // 常數 RAND_MAX 是 rand 函式可傳回的最大值。
        }
        break;
    default:
        cout << "型別不在搜尋範圍內!" << endl;
        break;
    }
}

// 產生字串亂數(STD_array)
template<typename T, size_t nSize>
void Produce_Str_random(array<T, nSize>* pData)
{
    srand(time(NULL));
    T* index = pData->data(); // 將指標指向pData 的第一個元素位置
    for (int i = 0; i < nSize; i++)
    {
        string StringTemp;
        for (int j = 0; j < 6; j++)
        {
            // 0~25的亂數加上 97 就會剛好落在97~122之間，換算成ACSII碼就是小寫a~z
            StringTemp += (char)(rand() % 26) + (97);
        }
        index[i] = StringTemp;
    }
}

int main()
{
    cout << "-----------------插入排序法-----------------\n" << endl;

    cout << "10筆資料>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
#pragma region 10筆資料(各類型)

    array<int, 10>* IntData10 = new array<int, 10>;
    Produce_random(IntData10, 'I');
    Selection_sort(IntData10, "Int");
    delete IntData10;

    array<long int, 10>* LongintData10 = new array<long int, 10>;
    Produce_random(LongintData10, 'I');
    Selection_sort(LongintData10, "Long int");
    delete LongintData10;

    array<float, 10>* FloatData10 = new array<float, 10>;
    Produce_random(FloatData10, 'I');
    Selection_sort(FloatData10, "Float");
    delete FloatData10;

    array<double, 10>* DoubleData10 = new array<double, 10>;
    Produce_random(DoubleData10, 'I');
    Selection_sort(DoubleData10, "Double");
    delete DoubleData10;

    array<string, 10>* StringData10 = new array<string, 10>;
    Produce_Str_random(StringData10);
    Selection_sort(StringData10, "String");
    delete StringData10;

#pragma endregion 

    cout << "20筆資料>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
#pragma region 20筆資料(各類型)

    array<int, 20>* IntData20 = new array<int, 20>;
    Produce_random(IntData20, 'I');
    Selection_sort(IntData20, "Int");
    delete IntData20;

    array<long int, 20>* LongintData20 = new array<long int, 20>;
    Produce_random(LongintData20, 'I');
    Selection_sort(LongintData20, "Long int");
    delete LongintData20;

    array<float, 20>* FloatData20 = new array<float, 20>;
    Produce_random(FloatData20, 'I');
    Selection_sort(FloatData20, "Float");
    delete FloatData20;

    array<double, 20>* DoubleData20 = new array<double, 20>;
    Produce_random(DoubleData20, 'I');
    Selection_sort(DoubleData20, "Double");
    delete DoubleData20;

    array<string, 20>* StringData20 = new array<string, 20>;
    Produce_Str_random(StringData20);
    Selection_sort(StringData20, "String");
    delete StringData20;

#pragma endregion 

    cout << "30筆資料>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
#pragma region 30筆資料(各類型)

    array<int, 30>* IntData30 = new array<int, 30>;
    Produce_random(IntData30, 'I');
    Selection_sort(IntData30, "Int");
    delete IntData30;

    array<long int, 30>* LongintData30 = new array<long int, 30>;
    Produce_random(LongintData30, 'I');
    Selection_sort(LongintData30, "Long int");
    delete LongintData30;

    array<float, 30>* FloatData30 = new array<float, 30>;
    Produce_random(FloatData30, 'I');
    Selection_sort(FloatData30, "Float");
    delete FloatData30;

    array<double, 30>* DoubleData30 = new array<double, 30>;
    Produce_random(DoubleData30, 'I');
    Selection_sort(DoubleData30, "Double");
    delete DoubleData30;

    array<string, 30>* StringData30 = new array<string, 30>;
    Produce_Str_random(StringData30);
    Selection_sort(StringData30, "String");
    delete StringData30;

#pragma endregion 

    cout << "40筆資料>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
#pragma region 40筆資料(各類型)

    array<int, 40>* IntData40 = new array<int, 40>;
    Produce_random(IntData40, 'I');
    Selection_sort(IntData40, "Int");
    delete IntData40;

    array<long int, 40>* LongintData40 = new array<long int, 40>;
    Produce_random(LongintData40, 'I');
    Selection_sort(LongintData40, "Long int");
    delete LongintData40;

    array<float, 40>* FloatData40 = new array<float, 40>;
    Produce_random(FloatData40, 'I');
    Selection_sort(FloatData40, "Float");
    delete FloatData40;

    array<double, 40>* DoubleData40 = new array<double, 40>;
    Produce_random(DoubleData40, 'I');
    Selection_sort(DoubleData40, "Double");
    delete DoubleData40;

    array<string, 40>* StringData40 = new array<string, 40>;
    Produce_Str_random(StringData40);
    Selection_sort(StringData40, "String");
    delete StringData40;

#pragma endregion 

    cout << "50筆資料>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
#pragma region 50筆資料(各類型)

    array<int, 50>* IntData50 = new array<int, 50>;
    Produce_random(IntData50, 'I');
    Selection_sort(IntData50, "Int");
    delete IntData50;

    array<long int, 50>* LongintData50 = new array<long int, 50>;
    Produce_random(LongintData50, 'I');
    Selection_sort(LongintData50, "Long int");
    delete LongintData50;

    array<float, 50>* FloatData50 = new array<float, 50>;
    Produce_random(FloatData50, 'I');
    Selection_sort(FloatData50, "Float");
    delete FloatData50;

    array<double, 50>* DoubleData50 = new array<double, 50>;
    Produce_random(DoubleData50, 'I');
    Selection_sort(DoubleData50, "Double");
    delete DoubleData50;

    array<string, 50>* StringData50 = new array<string, 50>;
    Produce_Str_random(StringData50);
    Selection_sort(StringData50, "String");
    delete StringData50;

#pragma endregion 

    cout << "60筆資料>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
#pragma region 60筆資料(各類型)

    array<int, 60>* IntData60 = new array<int, 60>;
    Produce_random(IntData60, 'I');
    Selection_sort(IntData60, "Int");
    delete IntData60;

    array<long int, 60>* LongintData60 = new array<long int, 60>;
    Produce_random(LongintData60, 'I');
    Selection_sort(LongintData60, "Long int");
    delete LongintData60;

    array<float, 60>* FloatData60 = new array<float, 60>;
    Produce_random(FloatData60, 'I');
    Selection_sort(FloatData60, "Float");
    delete FloatData60;

    array<double, 60>* DoubleData60 = new array<double, 60>;
    Produce_random(DoubleData60, 'I');
    Selection_sort(DoubleData60, "Double");
    delete DoubleData60;

    array<string, 60>* StringData60 = new array<string, 60>;
    Produce_Str_random(StringData60);
    Selection_sort(StringData60, "String");
    delete StringData60;

#pragma endregion 

    cout << "10萬筆資料>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
#pragma region 10萬筆資料(各類型)

    array<int, 100000>* IntData_1HT = new array<int, 100000>;
    Produce_random(IntData_1HT, 'I');
    Selection_sort(IntData_1HT, "Int");
    delete IntData_1HT;

    array<long int, 100000>* LongintData_1HT = new array<long int, 100000>;
    Produce_random(LongintData_1HT, 'I');
    Selection_sort(LongintData_1HT, "Long int");
    delete LongintData_1HT;

    array<float, 100000>* FloatData_1HT = new array<float, 100000>;
    Produce_random(FloatData_1HT, 'I');
    Selection_sort(FloatData_1HT, "Float");
    delete FloatData_1HT;

    array<double, 100000>* DoubleData_1HT = new array<double, 100000>;
    Produce_random(DoubleData_1HT, 'I');
    Selection_sort(DoubleData_1HT, "Double");
    delete DoubleData_1HT;

    array<string, 100000>* StringData_1HT = new array<string, 100000>;
    Produce_Str_random(StringData_1HT);
    Selection_sort(StringData_1HT, "String");
    delete StringData_1HT;

#pragma endregion 

    cout << "20萬筆資料>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
#pragma region 20萬筆資料(各類型)

    array<int, 200000>* IntData_2HT = new array<int, 200000>;
    Produce_random(IntData_2HT, 'I');
    Selection_sort(IntData_2HT, "Int");
    delete IntData_2HT;

    array<long int, 200000>* LongintData_2HT = new array<long int, 200000>;
    Produce_random(LongintData_2HT, 'I');
    Selection_sort(LongintData_2HT, "Long int");
    delete LongintData_2HT;

    array<float, 200000>* FloatData_2HT = new array<float, 200000>;
    Produce_random(FloatData_2HT, 'I');
    Selection_sort(FloatData_2HT, "Float");
    delete FloatData_2HT;

    array<double, 200000>* DoubleData_2HT = new array<double, 200000>;
    Produce_random(DoubleData_2HT, 'I');
    Selection_sort(DoubleData_2HT, "Double");
    delete DoubleData_2HT;

    array<string, 200000>* StringData_2HT = new array<string, 200000>;
    Produce_Str_random(StringData_2HT);
    Selection_sort(StringData_2HT, "String");
    delete StringData_2HT;

#pragma endregion 

    cout << "30萬筆資料>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
#pragma region 30萬筆資料(各類型)

    array<int, 300000>* IntData_3HT = new array<int, 300000>;
    Produce_random(IntData_3HT, 'I');
    Selection_sort(IntData_3HT, "Int");
    delete IntData_3HT;

    array<long int, 300000>* LongintData_3HT = new array<long int, 300000>;
    Produce_random(LongintData_3HT, 'I');
    Selection_sort(LongintData_3HT, "Long int");
    delete LongintData_3HT;

    array<float, 300000>* FloatData_3HT = new array<float, 300000>;
    Produce_random(FloatData_3HT, 'I');
    Selection_sort(FloatData_3HT, "Float");
    delete FloatData_3HT;

    array<double, 300000>* DoubleData_3HT = new array<double, 300000>;
    Produce_random(DoubleData_3HT, 'I');
    Selection_sort(DoubleData_3HT, "Double");
    delete DoubleData_3HT;

    array<string, 300000>* StringData_3HT = new array<string, 300000>;
    Produce_Str_random(StringData_3HT);
    Selection_sort(StringData_3HT, "String");
    delete StringData_3HT;

#pragma endregion

    cout << "40萬筆資料>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
#pragma region 40萬筆資料(各類型)

    array<int, 400000>* IntData_4HT = new array<int, 400000>;
    Produce_random(IntData_4HT, 'I');
    Selection_sort(IntData_4HT, "Int");
    delete IntData_4HT;

    array<long int, 400000>* LongintData_4HT = new array<long int, 400000>;
    Produce_random(LongintData_4HT, 'I');
    Selection_sort(LongintData_4HT, "Long int");
    delete LongintData_4HT;

    array<float, 400000>* FloatData_4HT = new array<float, 400000>;
    Produce_random(FloatData_4HT, 'I');
    Selection_sort(FloatData_4HT, "Float");
    delete FloatData_4HT;

    array<double, 400000>* DoubleData_4HT = new array<double, 400000>;
    Produce_random(DoubleData_4HT, 'I');
    Selection_sort(DoubleData_4HT, "Double");
    delete DoubleData_4HT;

    array<string, 400000>* StringData_4HT = new array<string, 400000>;
    Produce_Str_random(StringData_4HT);
    Selection_sort(StringData_4HT, "String");
    delete StringData_4HT;

#pragma endregion

    cout << "50萬筆資料>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
#pragma region 50萬筆資料(各類型)

    array<int, 500000>* IntData_5HT = new array<int, 500000>;
    Produce_random(IntData_5HT, 'I');
    Selection_sort(IntData_5HT, "Int");
    delete IntData_5HT;

    array<long int, 500000>* LongintData_5HT = new array<long int, 500000>;
    Produce_random(LongintData_5HT, 'I');
    Selection_sort(LongintData_5HT, "Long int");
    delete LongintData_5HT;

    array<float, 500000>* FloatData_5HT = new array<float, 500000>;
    Produce_random(FloatData_5HT, 'I');
    Selection_sort(FloatData_5HT, "Float");
    delete FloatData_5HT;

    array<double, 500000>* DoubleData_5HT = new array<double, 500000>;
    Produce_random(DoubleData_5HT, 'I');
    Selection_sort(DoubleData_5HT, "Double");
    delete DoubleData_5HT;

    array<string, 500000>* StringData_5HT = new array<string, 500000>;
    Produce_Str_random(StringData_5HT);
    Selection_sort(StringData_5HT, "String");
    delete StringData_5HT;

#pragma endregion

    return 0;
}