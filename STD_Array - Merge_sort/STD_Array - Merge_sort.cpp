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
double GetTime()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - CounterStart) / PCFreq;
}
// 印出計算後的時間
void Print_Time(int i, string TypeKeys, double TimeAdd) {
    fstream outfile;
    outfile.open("C:\\Users\\MSI GP65\\Desktop\\Sroting 資料\\Sort - CostTime\\Time - STD_Array-Merge_sort.txt", ios::app);
    if (TimeAdd < 1000)
    {
        outfile << "(" << TypeKeys << ")"
            << "排序" << i << "筆資料所花費時間: "
            << TimeAdd << " 毫秒\n";
        outfile.close();
    }
    else
    {
        outfile << "(" << TypeKeys << ")"
            << "排序" << i << "筆資料所花費時間: "
            << fixed << setprecision(2)
            << TimeAdd / 1000.0 << " 秒\n";
        outfile.close();
    }
}

// 排序用 (排序法STD_array)
template<typename T, size_t nSize>
void merge(array<T, nSize>* pData, int left, int mid, int right) noexcept
{
    int subArrayOne = mid - left + 1;
    int subArrayTwo = right - mid;
    T* index = pData->data();

    // Create temp arrays
    T* leftArray = new T[subArrayOne],
        * rightArray = new T[subArrayTwo];


    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = index[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = index[mid + 1 + j];

    auto indexOfSubArrayOne
        = 0, // Initial index of first sub-array
        indexOfSubArrayTwo
        = 0; // Initial index of second sub-array
    int indexOfMergedArray
        = left; // Initial index of merged array

    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne
        && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne]
            <= rightArray[indexOfSubArrayTwo]) {
            index[indexOfMergedArray]
                = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            index[indexOfMergedArray]
                = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        index[indexOfMergedArray]
            = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        index[indexOfMergedArray]
            = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }

    delete[] leftArray;
    delete[] rightArray;
    //return temp;
}
// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
template<typename T, size_t nSize>
void mergeSort(array<T, nSize>* pData, int begin, int end, bool Fristjudge)
{
    if (Fristjudge) {
        StartTime();
    }
    //array<TypeA, nSize> temp{};
    if (begin < end) {
        int mid = begin + (end - begin) / 2;
        mergeSort(pData, begin, mid, false);
        mergeSort(pData, mid + 1, end, false);
        merge(pData, begin, mid, end);
    }
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
    cout << "-----------------冒泡排序法-----------------\n" << endl;

    cout << "10筆資料>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
#pragma region 10筆資料(各類型)

    array<int, 10>* IntData10 = new array<int, 10>;
    Produce_random(IntData10, 'I');
    mergeSort(IntData10, 0, 9, true);
    Print_Time(10, "Int",GetTime());
    delete IntData10;

    array<long int, 10>* LongintData10 = new array<long int, 10>;
    Produce_random(LongintData10, 'I');
    mergeSort(LongintData10, 0, 9, true);
    Print_Time(10, "Long int", GetTime());
    delete LongintData10;

    array<float, 10>* FloatData10 = new array<float, 10>;
    Produce_random(FloatData10, 'I');
    mergeSort(FloatData10, 0, 9, true);
    Print_Time(10, "Float", GetTime());
    delete FloatData10;

    array<double, 10>* DoubleData10 = new array<double, 10>;
    Produce_random(DoubleData10, 'I');
    mergeSort(DoubleData10, 0, 9, true);
    Print_Time(10, "Double", GetTime());
    delete DoubleData10;

    array<string, 10>* StringData10 = new array<string, 10>;
    Produce_Str_random(StringData10);
    mergeSort(StringData10, 0, 9, true);
    Print_Time(10, "String", GetTime());
    delete StringData10;

#pragma endregion 

    cout << "20筆資料>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
#pragma region 20筆資料(各類型)

    array<int, 20>* IntData20 = new array<int, 20>;
    Produce_random(IntData20, 'I');
    mergeSort(IntData20, 0, 19, true);
    Print_Time(20, "Int", GetTime());
    delete IntData20;

    array<long int, 20>* LongintData20 = new array<long int, 20>;
    Produce_random(LongintData20, 'I');
    mergeSort(LongintData20, 0, 19, true);
    Print_Time(20, "Long int", GetTime());
    delete LongintData20;

    array<float, 20>* FloatData20 = new array<float, 20>;
    mergeSort(FloatData20, 0, 19, true);
    Print_Time(20, "Float", GetTime());
    delete FloatData20;

    array<double, 20>* DoubleData20 = new array<double, 20>;
    Produce_random(DoubleData20, 'I');
    mergeSort(DoubleData20, 0, 19, true);
    Print_Time(20, "Double", GetTime());
    delete DoubleData20;

    array<string, 20>* StringData20 = new array<string, 20>;
    Produce_Str_random(StringData20);
    mergeSort(StringData20, 0, 19, true);
    Print_Time(20, "String", GetTime());
    delete StringData20;

#pragma endregion 

    cout << "30筆資料>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
#pragma region 30筆資料(各類型)

    array<int, 30>* IntData30 = new array<int, 30>;
    Produce_random(IntData30, 'I');
    mergeSort(IntData30, 0, 29, true);
    Print_Time(30, "Int", GetTime());
    delete IntData30;

    array<long int, 30>* LongintData30 = new array<long int, 30>;
    Produce_random(LongintData30, 'I');
    mergeSort(LongintData30, 0, 29, true);
    Print_Time(30, "Long int", GetTime());
    delete LongintData30;

    array<float, 30>* FloatData30 = new array<float, 30>;
    Produce_random(FloatData30, 'I');
    mergeSort(FloatData30, 0, 29, true);
    Print_Time(30, "Float", GetTime());
    delete FloatData30;

    array<double, 30>* DoubleData30 = new array<double, 30>;
    Produce_random(DoubleData30, 'I');
    mergeSort(DoubleData30, 0, 29, true);
    Print_Time(30, "Double", GetTime());
    delete DoubleData30;

    array<string, 30>* StringData30 = new array<string, 30>;
    Produce_Str_random(StringData30);
    mergeSort(StringData30, 0, 29, true);
    Print_Time(30, "String", GetTime());
    delete StringData30;

#pragma endregion 

    cout << "40筆資料>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
#pragma region 40筆資料(各類型)

    array<int, 40>* IntData40 = new array<int, 40>;
    Produce_random(IntData40, 'I');
    mergeSort(IntData40, 0, 39, true);
    Print_Time(40, "Int", GetTime());
    delete IntData40;

    array<long int, 40>* LongintData40 = new array<long int, 40>;
    Produce_random(LongintData40, 'I');
    mergeSort(LongintData40, 0, 39, true);
    Print_Time(40, "Long int", GetTime());
    delete LongintData40;

    array<float, 40>* FloatData40 = new array<float, 40>;
    Produce_random(FloatData40, 'I');
    mergeSort(FloatData40, 0, 39, true);
    Print_Time(40, "Float", GetTime());
    delete FloatData40;

    array<double, 40>* DoubleData40 = new array<double, 40>;
    Produce_random(DoubleData40, 'I');
    mergeSort(DoubleData40, 0, 39, true);
    Print_Time(40, "Double", GetTime());
    delete DoubleData40;

    array<string, 40>* StringData40 = new array<string, 40>;
    Produce_Str_random(StringData40);
    mergeSort(StringData40, 0, 39, true);
    Print_Time(40, "String", GetTime());
    delete StringData40;

#pragma endregion 

    cout << "50筆資料>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
#pragma region 50筆資料(各類型)

    array<int, 50>* IntData50 = new array<int, 50>;
    Produce_random(IntData50, 'I');
    mergeSort(IntData50, 0, 49, true);
    Print_Time(50, "Int", GetTime());
    delete IntData50;

    array<long int, 50>* LongintData50 = new array<long int, 50>;
    Produce_random(LongintData50, 'I');
    mergeSort(LongintData50, 0, 49, true);
    Print_Time(50, "Long int", GetTime());
    delete LongintData50;

    array<float, 50>* FloatData50 = new array<float, 50>;
    Produce_random(FloatData50, 'I');
    mergeSort(FloatData50, 0, 49, true);
    Print_Time(50, "Float", GetTime());
    delete FloatData50;

    array<double, 50>* DoubleData50 = new array<double, 50>;
    Produce_random(DoubleData50, 'I');
    mergeSort(DoubleData50, 0, 49, true);
    Print_Time(50, "Double", GetTime());
    delete DoubleData50;

    array<string, 50>* StringData50 = new array<string, 50>;
    Produce_Str_random(StringData50);
    mergeSort(StringData50, 0, 49, true);
    Print_Time(50, "String", GetTime());
    delete StringData50;

#pragma endregion 

    cout << "60筆資料>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
#pragma region 60筆資料(各類型)

    array<int, 60>* IntData60 = new array<int, 60>;
    Produce_random(IntData60, 'I');
    mergeSort(IntData60, 0, 59, true);
    Print_Time(60, "Int", GetTime());
    delete IntData60;

    array<long int, 60>* LongintData60 = new array<long int, 60>;
    Produce_random(LongintData60, 'I');
    mergeSort(LongintData60, 0, 59, true);
    Print_Time(60, "Long int", GetTime());
    delete LongintData60;

    array<float, 60>* FloatData60 = new array<float, 60>;
    Produce_random(FloatData60, 'I');
    mergeSort(FloatData60, 0, 59, true);
    Print_Time(60, "Float", GetTime());
    delete FloatData60;

    array<double, 60>* DoubleData60 = new array<double, 60>;
    Produce_random(DoubleData60, 'I');
    mergeSort(DoubleData60, 0, 59, true);
    Print_Time(60, "Double", GetTime());
    delete DoubleData60;

    array<string, 60>* StringData60 = new array<string, 60>;
    Produce_Str_random(StringData60);
    mergeSort(StringData60, 0, 59, true);
    Print_Time(60, "String", GetTime());
    delete StringData60;

#pragma endregion 

    cout << "10萬筆資料>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
#pragma region 10萬筆資料(各類型)

    array<int, 100000>* IntData_1HT = new array<int, 100000>;
    Produce_random(IntData_1HT, 'I');
    mergeSort(IntData_1HT, 0, 99999, true);
    Print_Time(100000, "Int", GetTime());
    delete IntData_1HT;

    array<long int, 100000>* LongintData_1HT = new array<long int, 100000>;
    Produce_random(LongintData_1HT, 'I');
    mergeSort(LongintData_1HT, 0, 99999, true);
    Print_Time(100000, "Long int", GetTime());
    delete LongintData_1HT;

    array<float, 100000>* FloatData_1HT = new array<float, 100000>;
    Produce_random(FloatData_1HT, 'I');
    mergeSort(FloatData_1HT, 0, 99999, true);
    Print_Time(100000, "Float", GetTime());
    delete FloatData_1HT;

    array<double, 100000>* DoubleData_1HT = new array<double, 100000>;
    Produce_random(DoubleData_1HT, 'I');
    mergeSort(DoubleData_1HT, 0, 99999, true);
    Print_Time(100000, "Double", GetTime());
    delete DoubleData_1HT;

    array<string, 100000>* StringData_1HT = new array<string, 100000>;
    Produce_Str_random(StringData_1HT);
    mergeSort(StringData_1HT, 0, 99999, true);
    Print_Time(100000, "String", GetTime());
    delete StringData_1HT;

#pragma endregion 

    cout << "20萬筆資料>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
#pragma region 20萬筆資料(各類型)

    array<int, 200000>* IntData_2HT = new array<int, 200000>;
    Produce_random(IntData_2HT, 'I');
    mergeSort(IntData_2HT, 0, 199999, true);
    Print_Time(200000, "Int", GetTime());
    delete IntData_2HT;

    array<long int, 200000>* LongintData_2HT = new array<long int, 200000>;
    Produce_random(LongintData_2HT, 'I');
    mergeSort(LongintData_2HT, 0, 199999, true);
    Print_Time(200000, "Long int", GetTime());
    delete LongintData_2HT;

    array<float, 200000>* FloatData_2HT = new array<float, 200000>;
    Produce_random(FloatData_2HT, 'I');
    mergeSort(FloatData_2HT, 0, 199999, true);
    Print_Time(200000, "Float", GetTime());
    delete FloatData_2HT;

    array<double, 200000>* DoubleData_2HT = new array<double, 200000>;
    Produce_random(DoubleData_2HT, 'I');
    mergeSort(DoubleData_2HT, 0, 199999, true);
    Print_Time(200000, "Double", GetTime());
    delete DoubleData_2HT;

    array<string, 200000>* StringData_2HT = new array<string, 200000>;
    Produce_Str_random(StringData_2HT);
    mergeSort(StringData_2HT, 0, 199999, true);
    Print_Time(200000, "String", GetTime());
    delete StringData_2HT;

#pragma endregion 

    cout << "30萬筆資料>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
#pragma region 30萬筆資料(各類型)

    array<int, 300000>* IntData_3HT = new array<int, 300000>;
    Produce_random(IntData_3HT, 'I');
    mergeSort(IntData_3HT, 0, 299999, true);
    Print_Time(300000, "Int", GetTime());
    delete IntData_3HT;

    array<long int, 300000>* LongintData_3HT = new array<long int, 300000>;
    Produce_random(LongintData_3HT, 'I');
    mergeSort(LongintData_3HT, 0, 299999, true);
    Print_Time(300000, "Long int", GetTime());
    delete LongintData_3HT;

    array<float, 300000>* FloatData_3HT = new array<float, 300000>;
    Produce_random(FloatData_3HT, 'I');
    mergeSort(FloatData_3HT, 0, 299999, true);
    Print_Time(300000, "Float", GetTime());
    delete FloatData_3HT;

    array<double, 300000>* DoubleData_3HT = new array<double, 300000>;
    Produce_random(DoubleData_3HT, 'I');
    mergeSort(DoubleData_3HT, 0, 299999, true);
    Print_Time(300000, "Double", GetTime());
    delete DoubleData_3HT;

    array<string, 300000>* StringData_3HT = new array<string, 300000>;
    Produce_Str_random(StringData_3HT);
    mergeSort(StringData_3HT, 0, 299999, true);
    Print_Time(300000, "String", GetTime());
    delete StringData_3HT;

#pragma endregion

    cout << "40萬筆資料>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
#pragma region 40萬筆資料(各類型)

    array<int, 400000>* IntData_4HT = new array<int, 400000>;
    Produce_random(IntData_4HT, 'I');
    mergeSort(IntData_4HT, 0, 399999, true);
    Print_Time(400000, "Int", GetTime());
    delete IntData_4HT;

    array<long int, 400000>* LongintData_4HT = new array<long int, 400000>;
    Produce_random(LongintData_4HT, 'I');
    mergeSort(LongintData_4HT, 0, 399999, true);
    Print_Time(400000, "Long int", GetTime());
    delete LongintData_4HT;

    array<float, 400000>* FloatData_4HT = new array<float, 400000>;
    Produce_random(FloatData_4HT, 'I');
    mergeSort(FloatData_4HT, 0, 399999, true);
    Print_Time(400000, "Float", GetTime());
    delete FloatData_4HT;

    array<double, 400000>* DoubleData_4HT = new array<double, 400000>;
    Produce_random(DoubleData_4HT, 'I');
    mergeSort(DoubleData_4HT, 0, 399999, true);
    Print_Time(400000, "Double", GetTime());
    delete DoubleData_4HT;

    array<string, 400000>* StringData_4HT = new array<string, 400000>;
    Produce_Str_random(StringData_4HT);
    mergeSort(StringData_4HT, 0, 399999, true);
    Print_Time(400000, "String", GetTime());
    delete StringData_4HT;

#pragma endregion

    cout << "50萬筆資料>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
#pragma region 50萬筆資料(各類型)

    array<int, 500000>* IntData_5HT = new array<int, 500000>;
    Produce_random(IntData_5HT, 'I');
    mergeSort(IntData_5HT, 0, 499999, true);
    Print_Time(500000, "Int", GetTime());
    delete IntData_5HT;

    array<long int, 500000>* LongintData_5HT = new array<long int, 500000>;
    Produce_random(LongintData_5HT, 'I');
    mergeSort(LongintData_5HT, 0, 499999, true);
    Print_Time(500000, "Long int", GetTime());
    delete LongintData_5HT;

    array<float, 500000>* FloatData_5HT = new array<float, 500000>;
    Produce_random(FloatData_5HT, 'I');
    mergeSort(FloatData_5HT, 0, 499999, true);
    Print_Time(500000, "Float", GetTime());
    delete FloatData_5HT;

    array<double, 500000>* DoubleData_5HT = new array<double, 500000>;
    Produce_random(DoubleData_5HT, 'I');
    mergeSort(DoubleData_5HT, 0, 499999, true);
    Print_Time(500000, "Double", GetTime());
    delete DoubleData_5HT;

    array<string, 500000>* StringData_5HT = new array<string, 500000>;
    Produce_Str_random(StringData_5HT);
    mergeSort(StringData_5HT, 0, 499999, true);
    Print_Time(500000, "String", GetTime());
    delete StringData_5HT;

#pragma endregion

    return 0;
}