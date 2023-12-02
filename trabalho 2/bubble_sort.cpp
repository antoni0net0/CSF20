#include <iostream>

using namespace std;

int main()
{
    int lista_inicial[] = {11, 25, 34, 90, 22, 64, 12 };

    int n = sizeof(lista_inicial) / sizeof(lista_inicial[0]);

    int i, j, cont = 0;
    bool trocado;
    for (i = 0; i < n - 1; i++)
    {
        trocado = false;
        for (j = 0; j < n - 1; j++)
        {
            if (lista_inicial[j] > lista_inicial[j + 1])
            {
                swap(lista_inicial[j], lista_inicial[j + 1]);
                trocado = true;
            }

            cont++;
        }

        if (trocado == false)
            break;
    }


    for (i = 0; i < n; i++)
        cout << lista_inicial[i] << " ";
    cout << endl << cont;

    return 0;
}
