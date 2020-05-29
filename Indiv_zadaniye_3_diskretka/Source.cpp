#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//���-�� ������
int n;

// �������� �����. �������
int** make_matr()
{
    int **a = new int* [n];
    for (int i = 0; i < n; i++)
    {
        a[i] = new int[n];
    }
    return a;
}

// ����� �������
void vivod(int** a)
{
    cout << endl << "�������� �������:" << endl;
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

//����� ����� � ����������� ������ ���������
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

//������� ������
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
    //������ ������� ���� � �������� ����
    setlocale(LC_ALL, "ru");
    system("color 0E");

    //����������� ��� ����� � ��������� ����� ��� �����
    cout << "������� �������� �����, � ������� �������� ���� (��� .txt): ";
    string name_file; 
    getline(cin, name_file);

    if (name_file == "f")
    {
        name_file += ".txt";
        ifstream fin(name_file);

        //������ ������� ���������, ��������� ������� �� ����� � �������
        fin >> n;


        //������� ����

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

        //����� ���
        if (empty == 1)
        {
            system("color 0C");
            cout << endl << "���� ��� ����, �������, �� � ����� ����" << endl;
        }

        else
        {

            //�������� ������
            Floyd(a);

            //����� ����������������
            int* maxi = new int[n];
            for (int i = 0; i < n; i++)
            {
                int max = -1000;
                for (int j = 0; j < n; j++)
                {
                    if (a[i][j] > max && a[i][j] != 1000)  //&& a[i][j]!=1000 ��� �����, ����� �� ���������� "���������� �����"
                    {
                        max = a[i][j];
                    }
                }
                maxi[i] = max;
            }

            //������� ����������������
            cout << "���������������" << endl << endl;
            for (int i = 0; i < n; i++)
            {
                cout << maxi[i] << " ";
            }
            cout << endl << endl;

            //���� ������
            int rad = 1001;
            for (int i = 0; i < n; i++)
            {
                if (maxi[i] < rad && maxi[i] != -1000)
                {
                    rad = maxi[i];
                }
            }

            //���� �������
            int diam = -1001;
            for (int i = 0; i < n; i++)
            {
                if (maxi[i] > diam)
                {
                    diam = maxi[i];
                }
            }

            //*����� ����������� ������ ������������� � ����*
            ofstream gout("g.txt");
            gout << "���������� ������ � ����� : " << endl << endl;
            gout << "������ ����� = " << rad << endl;
            gout << "������� ����� = " << diam;
            gout.close();
            show("g.txt");

        }
    }
    //������������ ��� �����
    else
    {
        system("color 0C");
        cout << endl << "������������ ��� �����! ";
    }
    cout << endl << endl;
    system("pause");
}