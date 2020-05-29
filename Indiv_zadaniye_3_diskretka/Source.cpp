#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//кол-во вершин
int n;

// создание динам. матрицы
int** make_matr()
{
    int **a = new int* [n];
    for (int i = 0; i < n; i++)
    {
        a[i] = new int[n];
    }
    return a;
}

// вывод матрицы
void vivod(int** a)
{
    cout << endl << "Введённая матрица:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << a[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

//вывод файла с результатом работы программы
void show(string name_file)
{
    ifstream gin(name_file);
    string s;
    while (!gin.eof())
    {
        getline(gin, s);
        cout << s << endl;
    }
    gin.close();
}

//функция Флойда
void Floyd(int** a)
{
    int i, j, k;
    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (a[i][k] + a[k][j] < a[i][j]) 
                {
                    a[i][j] = a[i][k] + a[k][j];
                }
            }
        }
    }
}

int main()
{
    //ставим русский язык и приятный цвет
    setlocale(LC_ALL, "ru");
    system("color 0E");

    //запрашиваем имя файла и открываем поток для ввода
    cout << "Введите название файла, в котором хранится граф (без .txt): ";
    string name_file; 
    getline(cin, name_file);

    if (name_file == "f")
    {
        name_file += ".txt";
        ifstream fin(name_file);

        //создаём матрицу смежности, заполняем данными из файла и выводим
        fin >> n;


        //вершины есть

        int** a = make_matr();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                fin >> a[i][j];
            }
        }
        fin.close();
        vivod(a);

        bool empty = 1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (a[i][j] != 1000)
                    empty = 0;
            }
        }

        //ребер нет
        if (empty == 1)
        {
            system("color 0C");
            cout << endl << "Граф без рёбер, жестоко, но я этого ждал" << endl;
        }

        else
        {

            //вызываем Флойда
            Floyd(a);

            //поиск эксцентриситетов
            int* maxi = new int[n];
            for (int i = 0; i < n; i++)
            {
                int max = -1000;
                for (int j = 0; j < n; j++)
                {
                    if (a[i][j] > max && a[i][j] != 1000)  //&& a[i][j]!=1000 это важно, чтобы не заносилось "отсутствие ребра"
                    {
                        max = a[i][j];
                    }
                }
                maxi[i] = max;
            }

            //выводим экссцентриситеты
            cout << "Эксцентриситеты" << endl << endl;
            for (int i = 0; i < n; i++)
            {
                cout << maxi[i] << " ";
            }
            cout << endl << endl;

            //ищем радиус
            int rad = 1001;
            for (int i = 0; i < n; i++)
            {
                if (maxi[i] < rad && maxi[i] != -1000)
                {
                    rad = maxi[i];
                }
            }

            //ищем диаметр
            int diam = -1001;
            for (int i = 0; i < n; i++)
            {
                if (maxi[i] > diam)
                {
                    diam = maxi[i];
                }
            }

            //*вывод результатов должен производиться в файл*
            ofstream gout("g.txt");
            gout << "Полученные данные о графе : " << endl << endl;
            gout << "Радиус графа = " << rad << endl;
            gout << "Диаметр графа = " << diam;
            gout.close();
            show("g.txt");

        }
    }
    //неправильное имя файла
    else
    {
        system("color 0C");
        cout << endl << "Неправильное имя файла! ";
    }
    cout << endl << endl;
    system("pause");
}