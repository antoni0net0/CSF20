#include <iostream>

using namespace std;

int main()
{
    int lista_inicial[] = { 12, 11, 13, 5, 6 };
    int n = sizeof(lista_inicial) / sizeof(lista_inicial[0]);

    int i, chave, j;
    for (i = 1; i < n; i++)
    {
        chave = lista_inicial[i];
        j = i - 1;

        while (j >= 0 && lista_inicial[j] > chave)
        {
            lista_inicial[j + 1] = lista_inicial[j];
            j--;
        }
        lista_inicial[j + 1] = chave;
    }

    for (i = 0; i < n; i++)
        cout << lista_inicial[i] << " ";
    cout << endl;

    return 0;
}
