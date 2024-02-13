#include <iostream> 
#include <fstream>  
#include <cstring> 
#include <string> 
#include  <iomanip> 
#pragma warning(disable : 4996) 
#define _CRT_SECURE_NO_WARNINGS 
using namespace std; 

struct person // Определение структуры person 
{
    char F[30]; // Фамилия 
    char I[10]; // Имя 
    char O[10]; // Отчество 
    int TSUM; // Потраченная сумма денег 
    int SUM; // Выделенная сумма денег 
    int RSUM; // Выделенная сумма денег с учётом процента 
    int SUMD; // Сумма премии или долга 
};

void SLTE(person worker[], int count, int PRC) // Функция для расчета суммы с учетом процента и суммы премии или долга 
{
    for (int i = 0; i < count; i++) // Цикл по всем работникам 
    {
        worker[i].RSUM = worker[i].SUM + worker[i].SUM * PRC / 100; // Расчет выделенной суммы денег с учетом процента 
        worker[i].SUMD = worker[i].RSUM - worker[i].TSUM; // Расчет суммы премии или долга 
    }
}

void qsort(person worker[], int first, int last) // Функция быстрой сортировки 
{
    int i = first, j = last; 
    int x = worker[(first + last) / 2].SUM; // Определение опорного элемента 
    while (i <= j) // Пока индексы не сойдутся 
    {
        while (worker[i].SUM < x) // Поиск элемента большего, чем опорный 
            ++i;
        while (x < worker[j].SUM) // Поиск элемента меньшего, чем опорный 
            --j;
        if (i <= j) // Если индексы не сомкнулись 
        {
            swap(worker[i], worker[j]); // Обмен элементами 
            i++;  j--; // Сдвиг индексов 
        }
    }
    if (first < j)    qsort(worker, first, j); // Рекурсивный вызов для левой части 
    if (i < last)    qsort(worker, i, last); // Рекурсивный вызов для правой части 
}

void charqsort(person worker[], int first, int last) // Функция сортировки по алфавиту 
{
    for (int i = first; i < last - 1; i++) // Цикл по всем работникам 
        for (int j = i + 1; j < last; j++) // Цикл по всем работникам, начиная с i+1 
            if (strcmp(worker[i].F, worker[j].F) > 0) // Если фамилия i-го работника больше, чем j-го 
            {
                swap(worker[i], worker[j]); // Обмен элементами 
            }
}

void bsearch(person worker[], int first, int last, char* a) // Функция поиска работника по фамилии 
{
    int k = 0; // Флаг нахождения работника 
    for (int i = first; i < last; i++) // Цикл по всем работникам 
        if (strcmp(worker[i].F, a) == 0) // Если фамилия совпадает с искомой 
        {
            cout << setw(20) << worker[i].F << " " << worker[i].I << " " << worker[i].O << setw(20) << worker[i].SUM << setw(15) << worker[i].TSUM << setw(15) << worker[i].RSUM << setw(20) << worker[i].SUMD << endl;
            k = 1; // Установка флага нахождения работника 
        }
    if (k == 0) // Если работник не найден 
        cout << "Работника с такой фамилией нет" << endl; // Вывод сообщения об отсутствии работника 
}

void vvod(ifstream& in, person worker[], int count) // Функция ввода данных из файла 
{
    for (int i = 0; i < count; i++) // Цикл по всем работникам 
    {
        in >> worker[i].F; // Ввод фамилии 
        in >> worker[i].I; // Ввод имени 
        in >> worker[i].O; // Ввод отчества 
        in >> worker[i].TSUM; // Ввод потраченной суммы денег 
        in >> worker[i].SUM; // Ввод выделенной суммы денег 
    }
    in.close(); // Закрытие файла 
}

int main() 
{
    setlocale(LC_ALL, "rus"); 
    int count = 0, ALLSUM, PRC, OSUM = 0, OTSUM = 0, ORSUM = 0, OSUMD = 0, OSTATOK, PREMIYA = 0;  
    person worker[20]; 

    ifstream in;
ofstream out, fout; 
in.open("Spisok.txt"); // Открытие файла для чтения 
out.open("SSpisok.txt", ios::app); // Открытие файла для записи 

// Проверка файла 
if (!in.is_open()) // Если файл не открыт 
{
    cout << "Ошибка" << endl; 
    return 0; 
}

// Подсчёт количества сотрудников 
char str[50]; 
while (!in.eof()) // Пока не достигнут конец файла 
{
    in.getline(str, 50, '\n'); // Чтение строки из файла 
    count++; // Увеличение счетчика 
}
count = count - 2; // Уменьшение счетчика на 2 (первые две строки - не данные о работниках) 
in.seekg(0); // Возврат к началу файла 

in >> ALLSUM; // Чтение общей суммы 
in >> PRC; // Чтение процента 
vvod(in, worker, count); // Вызов функции ввода данных из файла 
qsort(worker, 0, count - 1); // Вызов функции быстрой сортировки 

for (int i = 0; i < count; i++) // Цикл по всем работникам 
{
    OSUM += worker[i].SUM; // Подсчет общей выделенной суммы 
}

for (int i = 0; i < count; i++) // Цикл по всем работникам 
{
    OTSUM += worker[i].TSUM; // Подсчет общей потраченной суммы 
}

SLTE(worker, count, PRC); // Вызов функции для расчета суммы с учетом процента и суммы премии или долга

for (int i = 0; i < count; i++) // Цикл по всем работникам   
{
    ORSUM += worker[i].RSUM; // Подсчет общей выделенной суммы с учетом процента
    for (int i = 0; i < count; i++) // Цикл по всем работникам   
    {
        if (worker[i].SUMD < 0); // Если сумма премии или долга отрицательна            OSUMD -= worker[i].SUMD; // Увеличение общей суммы долга
    }
    OSTATOK = ALLSUM - ORSUM + OSUMD; // Расчет остатка
    // Далее идет основная часть программы, где происходит взаимодействие с пользователем и вывод информации.}
}
