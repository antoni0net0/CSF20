#include <iostream>

using namespace std;

int main()
{
    int vetor[] = { 64, 25, 12, 22, 11, 28, 34, 65, 3 };
    int n = sizeof(vetor) / sizeof(vetor[0]);

    int i, j, posicao_numero;

    for (i = 0; i < n - 1; i++)
    {
        posicao_numero = i;
        for (j = i + 1; j < n; j++)
        {
            if (vetor[j] < vetor[posicao_numero])
                posicao_numero = j;
        }

        if (posicao_numero != i)
            swap(vetor[posicao_numero], vetor[i]);
    }

    for (i = 0; i < n; i++)
        cout << vetor[i] << " ";

    return 0;
}
