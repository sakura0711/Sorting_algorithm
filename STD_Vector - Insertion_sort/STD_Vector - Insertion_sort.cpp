#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <array>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>
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
    outfile.open("C:\\Users\\MSI GP65\\source\\repos\\Data_structure - 排序法\\Sort - CostTime\\Time - STD_Vector-Insertion_sort.txt", ios::app);

    if (TimeAdd < 1000)
    {
        outfile << "\n"
            << "(" << TypeKeys << ")"
            << "排序" << i << "筆資料所花費時間: "
            << TimeAdd << " 毫秒\n";
        outfile.close();
    }
    else if (TimeAdd < 60000)
    {
        outfile << "\n"
            << "(" << TypeKeys << ")"
            << "排序" << i << "筆資料所花費時間: "
            << TimeAdd / 1000.0 << " 秒\n";
        outfile.close();
    }
    else
    {
        outfile << "\n"
            << "(" << TypeKeys << ")"
            << "排序" << i << "筆資料所花費時間: "
            << TimeAdd / (1000.0 * 60) << " 分\n";
        outfile.close();
    }
}

// 排序用 (排序法)
template<typename T>
void Insertion_sort(vector<T>& pData, string TypeKeys) noexcept
{
    int nSize = pData.size();
    float Percent = nSize / 100;
    double TimeAdd = 0.0; //儲存排序時間

    T temp;
    for (int i = 1; i < nSize; i++)
    {
        StartTime();
        temp = pData[i];
        int k;
        for (k = i -1; k >= 0 && temp < pData[k]; k--)
        {
            pData[k+1] = pData[k]; // 比前面小就跟前面的交換
        }
        pData[k+1] = temp;
        TimeAdd += GetTime();
        //if (nSize >= 100000) { cout << "\r" << "Complate: " << fixed << setprecision(2) << ((i / Percent) + 0.001) << "%"; }
    }
    Print_Time(TimeAdd, nSize, TypeKeys);
    //return 0;
}

// 印出排序後的陣列(STD_array)
template <typename T>
void Print(vector<T>& pData)
{
    //while 迴圈為取得資料位數，利於用setw()排版
    int Digits = 0, SizeTemp = pData.size;
    while (SizeTemp >= 10) {
        SizeTemp /= 10;
        Digits++;
    }

    cout << "資料: ";
    for (int i = 0; i < SizeTemp; i++) {
        cout << setw(Digits) << pData[i] << " ";
        if (i % 20 == 0 && i > 20) { cout << endl; }
    }
    cout << endl;
}

// 產生亂數(STD_array)
template<typename T>
void Produce_random(vector<T>& pData, char TypeKey) noexcept
{
    int nSize = pData.size();
    srand(time(NULL));
    switch (TypeKey) {
    case 'I':
        for (int i = 0; i < nSize; i++)
        {
            //pData.emplace_back(rand() % nSize + 1 );
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
}

// 產生字串亂數(STD_array)
template<typename T>
void Produce_Str_random(vector<T>& pData)
{
    int nSize = pData.size();
    srand(time(NULL));
    for (int i = 0; i < nSize; i++)
    {
        string StringTemp;
        for (int j = 0; j < 6; j++)
        {
            // 0~25的亂數加上 97 就會剛好落在97~122之間，換算成ACSII碼就是小寫a~z
            StringTemp += (char)(rand() % 26) + (97);
        }
        pData[i]=StringTemp;
    }
}

int main()
{
    cout << "請問要資料要單筆輸出還是全部輸出(單筆 Y / 全部 N) >";
    char printSelect = 'N'; //默認全部輸出
    cin >> printSelect;

    // Vector 宣告**********************
    vector<int> intVector;
    vector<long int> longintVector;
    vector<float> floatVector;
    vector<double> doubleVector;
    vector<string> stringVector;
    /**********************************/

    if (printSelect == 'Y')
    {
        short int typeSelect;
        int dataRecord;

        cout << "\n------請輸入要顯示的數據類型----- \n"
            << "1. int類型\n"
            << "2. long int類型\n"
            << "3. float類型\n"
            << "4. double類型\n"
            << "5. string類型\n"
            << "> ";
        cin >> typeSelect;

        cout << "要排序幾筆資料> ";
        cin >> dataRecord;

        switch (typeSelect)
        {
        case 1:
            intVector.clear();
            intVector.resize(dataRecord);

            Produce_random(intVector, 'I');
            Insertion_sort(intVector, "Int");
            break;
        case 2:
            longintVector.clear();
            longintVector.resize(dataRecord);

            Produce_random(longintVector, 'I');
            Insertion_sort(longintVector, "Long int");
            break;
        case 3:
            floatVector.clear();
            floatVector.resize(dataRecord);

            Produce_random(floatVector, 'F');
            Insertion_sort(floatVector, "Float");
            break;
        case 4:
            doubleVector.clear();
            doubleVector.resize(dataRecord);

            Produce_random(doubleVector, 'D');
            Insertion_sort(doubleVector, "Double");
            break;
        case 5:
            stringVector.clear();
            stringVector.resize(dataRecord);

            Produce_Str_random(stringVector);
            Insertion_sort(stringVector, "String");
            break;
        default:
            cout << "選項輸入錯誤~!";
            break;
        }
    }
    else if (printSelect == 'N')
    {
        int dataRecord[] = { 10, 20, 30, 40, 50, 60 , 100000, 200000, 300000, 400000, 500000 };

        // (int)整數型態
        cout << "\n# (int)整數型態---------------\n" << endl;
        for (int i = 0; i < size(dataRecord); i++)
        {
            cout << "\n" << dataRecord[i] << ' ' << endl;
            intVector.clear();
            intVector.resize(dataRecord[i]);

            Produce_random(intVector, 'I');
            //for (auto temp : intVector) { cout << temp << " "; }
            Insertion_sort(intVector, "Int");
            //for (auto temp : intVector) { cout << temp << " "; }
        }
        
        // (long int)長整數型態
        cout << "\n# (long int)長整數型態---------------\n" << endl;
        for (int i = 0; i < size(dataRecord); i++)
        {
            longintVector.clear();
            longintVector.resize(dataRecord[i]);

            Produce_random(longintVector, 'I');
            Insertion_sort(longintVector, "Long Int");
        }

        // (float)浮點數型態
        cout << "\n# (float)浮點數型態---------------\n" << endl;
        for (int i = 0; i < size(dataRecord); i++)
        {
            floatVector.clear();
            floatVector.resize(dataRecord[i]);

            Produce_random(floatVector, 'F');
            Insertion_sort(floatVector, "Float");
        }

        // (double)雙倍精度浮點數型態
        cout << "\n# (double)雙倍精度浮點數型態---------------\n" << endl;
        for (int i = 0; i < size(dataRecord); i++)
        {
            doubleVector.clear();
            doubleVector.resize(dataRecord[i]);

            Produce_random(doubleVector, 'D');
            Insertion_sort(doubleVector, "Double");
        }

        // (string)字串型態，6個字母
        cout << "\n# (string)字串型態，6個字母---------------\n" << endl;
        for (int i = 0; i < size(dataRecord); i++)
        {
            stringVector.clear();
            stringVector.resize(dataRecord[i]);

            Produce_Str_random(stringVector);
            Insertion_sort(stringVector, "String");
        }
    }
    else { cout << "請輸入正確選項! "; }
}