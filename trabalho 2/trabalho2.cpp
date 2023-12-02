/*********************************************************************************************************************************************

Trabalho 2 - Ordenacao das Listas

Autor: Antonio Galvao Martins Neto - a2557908
Curso: Bachalerado em Sistemas de Informacao
Materia: Estrutura de dados 1 - ICSF - S73
Periodo: 2
Data: 07/09/2023

**********************************************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define TAM_LISTA 15000000

using namespace std;

///para a lista sequencial
struct Node_sequencial
{
    string nome;
    int rg;
};

struct Lista_sequencial
{
    struct Node_sequencial pessoa[TAM_LISTA];
    int tamanho = 0;
};

///aloca para a lista sequencial
Lista_sequencial* gera_lista_sequencial()
{
    Lista_sequencial* lista = new Lista_sequencial;

    if(lista != NULL)
        lista->tamanho = 0;

    return lista;
}

void apagaTudo()
{
    system("cls");
}

void exibe_iteracoes(string nome, int rg, int posicao, double tempo, int comparacoes, int copias)
{
    cout << endl;

    cout << "Nome: " << nome << endl;
    cout << "RG: " << rg << endl;
    cout << "Posicao na lista: " << posicao << endl;
    cout << "Tempo de execucao: " << tempo << endl;
    cout << "C(n): " << comparacoes << endl;
    cout << "M(n): " << copias << endl;

    cout << endl;
}

void preenche_lista(Lista_sequencial* lista_inicial)
{
    string nome_seq, rg_seq;
    int i = 0;
    double tempo_sequencial = 0.0;
    int num_comparacoes_sequencial = 0, num_copias_sequencial = 0;

    string nome_arquivo = " ";
    ///le arquivo e implementa as listas
    while(nome_arquivo == " ")
    {
        cout << "Digite o nome do arquivo a ser lido: " << endl << "ex: fulano.txt" << endl;
        cin >> nome_arquivo;
        clock_t begin = clock();

        ifstream myfile(nome_arquivo);
        ifstream arquivo(nome_arquivo);

        if (myfile.is_open())
        {
            ///lista sequencial
            clock_t begina = clock();

            while(getline(arquivo, nome_seq, ',') && getline(arquivo, rg_seq))
            {
                num_comparacoes_sequencial++;
                lista_inicial->pessoa[i].nome = nome_seq;
                lista_inicial->pessoa[i].rg = stoi(rg_seq);
                lista_inicial->tamanho++;
                i++;
                num_copias_sequencial += 2;
            }
            clock_t endo = clock();
            tempo_sequencial += (double)(endo - begina) / CLOCKS_PER_SEC;

        }
        else
        {
            apagaTudo();
            cout << "Arquivo nao encontrado" << endl << endl;
            nome_arquivo = " ";
        }
    }


    cout << "Lista preenchida ;)" << endl;
    cout << endl << "Lista sequencial: ";
    exibe_iteracoes("-", 0, lista_inicial->tamanho, tempo_sequencial, num_comparacoes_sequencial, num_copias_sequencial);
}

void imprime_lista(Lista_sequencial* listaa)
{
    ///noa eh necessario usar as duas listas aqui porque eu so estou imprimindo na tela
    int i;
    for(i = 0; i < listaa->tamanho; i++)
        cout << listaa->pessoa[i].nome << "\t\t" << listaa->pessoa[i].rg << endl;
}

void salva_nova_lista(Lista_sequencial* listaa)
{
    cout << "Digite o valor que deseja procurar: ";
    //cin >> valor_procurado;
}

void insere_inicio(Lista_sequencial* lista_inicial)
{
    string nome_inserido;
    int rg_inserido;

    cout << "digite o nome: ";
    cin >> nome_inserido;
    cout << "digite o rg: ";
    cin >> rg_inserido;

    int i = lista_inicial->tamanho;
    double tempo_sequencial = 0.0;
    int num_comparacoes_sequencial = 0, num_copias_sequencial = 0;

    ///lista sequencial
    clock_t begina = clock();

    while(i > 0)
    {
        num_comparacoes_sequencial++;
        lista_inicial->pessoa[i].nome = lista_inicial->pessoa[i - 1].nome;
        lista_inicial->pessoa[i].rg = lista_inicial->pessoa[i - 1].rg;
        i--;

        num_copias_sequencial += 2;
    }

    lista_inicial->pessoa[0].nome = nome_inserido;
    lista_inicial->pessoa[0].rg = rg_inserido;
    lista_inicial->tamanho++;

    num_copias_sequencial += 2;

    clock_t enda = clock();
    tempo_sequencial += (double)(enda - begina) / CLOCKS_PER_SEC;

    cout << endl << "Lista sequencial: ";
    exibe_iteracoes(nome_inserido, rg_inserido, 1, tempo_sequencial, num_comparacoes_sequencial, num_copias_sequencial);
}

void insere_final(Lista_sequencial* lista_inicial)
{
    string nome_inserido;
    int rg_inserido;

    cout << "digite o nome: ";
    cin >> nome_inserido;
    cout << "digite o rg: ";
    cin >> rg_inserido;

    ///lista sequencial
    int i = 0;
    double tempo_sequencial = 0.0;
    int num_comparacoes_sequencial = 0, num_copias_sequencial = 0;

    clock_t begina = clock();

    lista_inicial->pessoa[lista_inicial->tamanho].nome = nome_inserido;
    lista_inicial->pessoa[lista_inicial->tamanho].rg = rg_inserido;

    num_copias_sequencial += 2;

    lista_inicial->tamanho++;

    clock_t enda = clock();
    tempo_sequencial += (double)(enda - begina) / CLOCKS_PER_SEC;
    cout << endl << "Lista sequencial: ";
    exibe_iteracoes(nome_inserido, rg_inserido, lista_inicial->tamanho, tempo_sequencial, num_comparacoes_sequencial, num_copias_sequencial);
}

void insere_onde_quiser(Lista_sequencial* lista_inicial)
{
    string nome_inserido;
    int rg_inserido;
    int posicao;

    cout << "digite o nome: ";
    cin >> nome_inserido;
    cout << "digite o rg: ";
    cin >> rg_inserido;

    cout << "digite a posicao: ";
    cin >> posicao;

    ///lista sequencial
    int i = 0;
    double tempo_sequencial = 0.0;
    int num_comparacoes_sequencial = 0, num_copias_sequencial = 0;

    clock_t begina = clock();

    for(i = lista_inicial->tamanho; i > posicao ; i--)
    {
        num_comparacoes_sequencial++;
        lista_inicial->pessoa[i + 1].nome = lista_inicial->pessoa[i].nome;
        lista_inicial->pessoa[i + 1].rg = lista_inicial->pessoa[i].rg;

        num_copias_sequencial += 2;
    }

    lista_inicial->pessoa[posicao - 1].nome = nome_inserido;
    lista_inicial->pessoa[posicao - 1].rg = rg_inserido;
    lista_inicial->tamanho++;

    num_copias_sequencial += 2;

    clock_t enda = clock();
    tempo_sequencial += (double)(enda - begina) / CLOCKS_PER_SEC;
    cout << endl << "Lista sequencial: ";
    exibe_iteracoes(nome_inserido, rg_inserido, posicao, tempo_sequencial, num_comparacoes_sequencial, num_copias_sequencial);

}

void insere(Lista_sequencial* lista_inicial)
{
    int decisao = 0;

    while(decisao != 4)
    {
        apagaTudo();

        cout << "1 - Inicio" << endl;
        cout << "2 - Fim" << endl;
        cout << "3 - Onde quiser" << endl;
        cout << "4 - Sair" << endl;

        cout << "Escolha a sua opcao: ";
        cin >> decisao;

        switch(decisao)
        {
        case 1:
            apagaTudo();
            insere_inicio(lista_inicial);
            system("pause");
            apagaTudo();
            break;

        case 2:
            apagaTudo();
            insere_final(lista_inicial);
            system("pause");
            apagaTudo();
            break;

        case 3:
            apagaTudo();
            insere_onde_quiser(lista_inicial);
            system("pause");
            apagaTudo();
            break;

        case 4:
            cout << endl;
            break;

        default:
            apagaTudo();
            cout << "Valor invalido" << endl << endl;
            system("pause");
            break;
        }
    }
}

void retira_inicio(Lista_sequencial* lista_inicial)
{
    string nome_inserido;
    int rg_inserido;

    ///lista sequencial
    string nome;
    int rg;
    int i;
    double tempo_sequencial = 0.0;
    int num_comparacoes_sequencial = 0, num_copias_sequencial = 0;

    clock_t begina = clock();

    nome = lista_inicial->pessoa[0].nome;
    rg = lista_inicial->pessoa[0].rg;

    for(i = 0; i < lista_inicial->tamanho - 1; i++)
    {
        num_comparacoes_sequencial++;
        lista_inicial->pessoa[i].nome = lista_inicial->pessoa[i + 1].nome;
        lista_inicial->pessoa[i].rg = lista_inicial->pessoa[i + 1].rg;

        num_copias_sequencial += 2;
    }

    lista_inicial->pessoa[lista_inicial->tamanho - 1].nome = "";
    lista_inicial->pessoa[lista_inicial->tamanho - 1].rg = 0;

    lista_inicial->tamanho--;

    clock_t enda = clock();
    tempo_sequencial += (double)(enda - begina) / CLOCKS_PER_SEC;
    cout << "Lista sequencial ";
    exibe_iteracoes(nome, rg, 1, tempo_sequencial, num_comparacoes_sequencial, num_copias_sequencial);
}

void retira_final(Lista_sequencial* lista_inicial)
{
    string nome_inserido;
    int rg_inserido;

    ///lista sequencial
    string nome;
    int rg;
    double tempo_sequencial = 0.0;
    int num_comparacoes_sequencial = 0, num_copias_sequencial = 0;

    clock_t begina = clock();

    nome = lista_inicial->pessoa[lista_inicial->tamanho - 1].nome;
    rg = lista_inicial->pessoa[lista_inicial->tamanho - 1].rg;

    lista_inicial->pessoa[lista_inicial->tamanho - 1].nome = "";
    lista_inicial->pessoa[lista_inicial->tamanho - 1].rg = 0;

    num_copias_sequencial += 4;

    lista_inicial->tamanho--;

    clock_t enda = clock();
    tempo_sequencial += (double)(enda - begina) / CLOCKS_PER_SEC;

    cout << "Lista sequencial: ";
    exibe_iteracoes(nome, rg, lista_inicial->tamanho + 1, tempo_sequencial, num_comparacoes_sequencial, num_copias_sequencial);
}

void retira_onde_quiser(Lista_sequencial* lista_inicial)
{
    string nome_inserido;
    int rg_inserido;
    int posicao;

    cout << "digite a posicao: ";
    cin >> posicao;

    ///lista sequencial
    double tempo_sequencial = 0.0;
    int num_comparacoes_sequencial = 0, num_copias_sequencial = 0;
    string nome;
    int rg;

    nome = lista_inicial->pessoa[posicao - 1].nome;
    rg = lista_inicial->pessoa[posicao - 1].rg;
    num_copias_sequencial += 2;

    clock_t begina = clock();

    int i;
    for(i = posicao - 1; i < lista_inicial->tamanho ; i++)
    {
        num_comparacoes_sequencial++;
        lista_inicial->pessoa[i].nome = lista_inicial->pessoa[i + 1].nome;
        lista_inicial->pessoa[i].rg = lista_inicial->pessoa[i + 1].rg;

        num_copias_sequencial += 2;
    }

    lista_inicial->pessoa[lista_inicial->tamanho - 1].nome = "";
    lista_inicial->pessoa[lista_inicial->tamanho - 1].rg = 0;

    num_copias_sequencial += 2;

    lista_inicial->tamanho--;

    clock_t enda = clock();
    tempo_sequencial += (double)(enda - begina) / CLOCKS_PER_SEC;
    cout << endl << "Lista sequencial: ";
    exibe_iteracoes(nome, rg, posicao, tempo_sequencial, num_comparacoes_sequencial, num_copias_sequencial);
}

void retira(Lista_sequencial* lista_inicial)
{
    int decisao = 0;

    while(decisao != 4)
    {
        apagaTudo();

        cout << "1 - Inicio" << endl;
        cout << "2 - Fim" << endl;
        cout << "3 - Onde quiser" << endl;
        cout << "4 - Sair" << endl;

        cout << "Escolha a sua opcao: ";
        cin >> decisao;

        switch(decisao)
        {
        case 1:
            apagaTudo();
            retira_inicio(lista_inicial);
            system("pause");
            apagaTudo();
            break;

        case 2:
            apagaTudo();
            retira_final(lista_inicial);
            system("pause");
            apagaTudo();
            break;

        case 3:
            apagaTudo();
            retira_onde_quiser(lista_inicial);
            system("pause");
            apagaTudo();
            break;

        case 4:
            cout << endl;
            break;

        default:
            apagaTudo();
            cout << "Valor invalido" << endl << endl;
            system("pause");
            break;
        }
    }
}

void busca_sequencial(Lista_sequencial* lista_inicial)
{
    ///lista sequencial
    double tempo_sequencial = 0.0;
    int num_comparacoes_sequencial = 0, num_copias_sequencial = 0;

    int i = 0;

    int valor_procurado;
    string nome;
    bool achou = false;

    cout << "Digite o valor que deseja procurar: ";
    cin >> valor_procurado;


    clock_t begin = clock();
    while(i < lista_inicial->tamanho && !achou)
    {
        if(lista_inicial->pessoa[i].rg == valor_procurado)
        {
            clock_t end = clock();
            tempo_sequencial += (double)(end - begin) / CLOCKS_PER_SEC;

            nome = lista_inicial->pessoa[i].nome;
            achou = true;

            num_copias_sequencial += 2;
            cout << "Lista sequencial: ";
            exibe_iteracoes(nome, valor_procurado, i + 1, tempo_sequencial, num_comparacoes_sequencial, num_copias_sequencial);
        }

        i++;

        num_comparacoes_sequencial += 2;
        num_copias_sequencial++;
    }
}

void busca_binaria(Lista_sequencial* lista_inicial)
{
    double tempo_binario = 0.0;
    int num_comparacoes_binario = 0, num_copias_binario = 0;

    int valor_procurado;
    string nome;
    int flag = 1;

    cout << "Digite o valor que deseja procurar: ";
    cin >> valor_procurado;

    clock_t begina = clock();

    int inicio = 0;
    int fim = lista_inicial->tamanho - 1;
    int parametro = fim - inicio;
    int posicao = lista_inicial->tamanho/2 + parametro%2 + inicio;
    bool achou = false;

    num_copias_binario += 2;

    while(!achou && parametro > 1)
    {
        if(valor_procurado == lista_inicial->pessoa[posicao].rg)
            achou = true;
        else
        {
            if(valor_procurado < lista_inicial->pessoa[posicao].rg)
            {
                fim = posicao;

                num_copias_binario ++;
            }

            else
            {
                inicio = posicao;

                num_copias_binario ++;
                num_comparacoes_binario++;
            }

            num_comparacoes_binario += 2;
        }

        parametro = fim - inicio;
        posicao = parametro/2 + parametro%2 + inicio;

        num_comparacoes_binario += 2;
        num_copias_binario += 2;
    }

    clock_t enda = clock();
    tempo_binario += (double)(enda - begina) / CLOCKS_PER_SEC;
    exibe_iteracoes(lista_inicial->pessoa[posicao].nome, valor_procurado, posicao + 1, tempo_binario, num_comparacoes_binario, num_copias_binario);
}


void procura_lista(Lista_sequencial* lista_inicial)
{
    ///lista sequencial
    double tempo_sequencial = 0.0;
    int num_comparacoes_sequencial = 0, num_copias_sequencial = 0;

    int decisao = 0;

    while(decisao != 3)
    {
        cout << "1 - Busca sequencial" << endl;
        cout << "2 - Busca binaria" << endl;
        cout << "3 - Sair" << endl;

        cout << "digite a sua opcao: ";
        cin >> decisao;

        switch(decisao)
        {
        case 1:
            apagaTudo();
            busca_sequencial(lista_inicial);
            system("pause");
            break;

        case 2:
            apagaTudo();
            busca_binaria(lista_inicial);
            system("pause");
            break;

        case 3:
            cout << endl;
            break;

        default:
            apagaTudo();
            cout << "Valor invalido";
            system("pause");
            break;
        }

        apagaTudo();

    }

}

void insertion_sort(Lista_sequencial* lista_inicial)
{
    double tempo_insertion = 0.0;
    int num_comparacoes_insertion = 0, num_copias_insertion = 0;

    clock_t begin = clock();
    int n = lista_inicial->tamanho;
    int i, chave, j, teste;

    ///insertion sort
    for (i = 1; i < n; i++)
    {
        chave = lista_inicial->pessoa[i].rg;;
        j = i - 1;

        while (j >= 0 && lista_inicial->pessoa[j].rg > chave)
        {
            swap(lista_inicial->pessoa[j + 1], lista_inicial->pessoa[j]);
            j--;

            num_copias_insertion += 4;
            num_comparacoes_insertion++;
        }

        lista_inicial->pessoa[j + 1].rg = chave;

        num_copias_insertion += 3;
        num_comparacoes_insertion++;
    }

    clock_t end = clock();
    tempo_insertion += (double)(end - begin) / CLOCKS_PER_SEC;
    exibe_iteracoes("Insertion Sort", 0, 0, tempo_insertion, num_comparacoes_insertion, num_copias_insertion);

}

void selection_sort(Lista_sequencial* lista_inicial)
{
    double tempo_selection = 0.0;
    int num_comparacoes_selection = 0, num_copias_selection = 0;

    clock_t begin = clock();
    int n = lista_inicial->tamanho;
    int i, j, teste;

    ///selection sort
    int posicao_numero;
    for (i = 0; i < n - 1; i++)
    {
        posicao_numero = i;

        num_copias_selection++;
        for (j = i + 1; j < n; j++)
        {
            if (lista_inicial->pessoa[j].rg < lista_inicial->pessoa[posicao_numero].rg)
            {
                posicao_numero = j;
                num_copias_selection++;
            }

            num_comparacoes_selection += 2;
        }

        if (posicao_numero != i)
        {
            swap(lista_inicial->pessoa[posicao_numero], lista_inicial->pessoa[i]);
            num_copias_selection += 3;
        }

        num_comparacoes_selection += 2;
    }
    clock_t end = clock();
    tempo_selection += (double)(end - begin) / CLOCKS_PER_SEC;
    exibe_iteracoes("Selection sort", 0, 0, tempo_selection, num_comparacoes_selection, num_copias_selection);
}

void bubble_sort(Lista_sequencial* lista_inicial)
{
    double tempo_bubble = 0.0;
    int num_comparacoes_bubble = 0, num_copias_bubble = 0;

    clock_t begin = clock();
    int n = lista_inicial->tamanho;
    int i, j, teste;

    ///bubble sort
    bool trocado;
    for (i = 0; i < n - 1; i++)
    {
        trocado = false;
        for (j = 0; j < n - 1; j++)
        {
            if (lista_inicial->pessoa[j].rg > lista_inicial->pessoa[j + 1].rg)
            {
                swap(lista_inicial->pessoa[j], lista_inicial->pessoa[j + 1]);
                trocado = true;

                num_copias_bubble += 4;
            }
            num_comparacoes_bubble += 2;
        }
        if (!trocado)
            break;

        num_copias_bubble++;
        num_comparacoes_bubble += 2;
    }
    clock_t end = clock();
    tempo_bubble += (double)(end - begin) / CLOCKS_PER_SEC;
    exibe_iteracoes("Bubble sort", 0, 0, tempo_bubble, num_comparacoes_bubble, num_copias_bubble);

}

void shell_sort(Lista_sequencial* lista_inicial)
{
    double tempo_shell = 0.0;
    int num_comparacoes_shell = 0, num_copias_shell = 0;

    clock_t begin = clock();
    int n = lista_inicial->tamanho;
    int i, j, teste;

    ///shell sort
    int intervalo, valor;
    for (intervalo = n/2; intervalo > 0; intervalo /= 2)
    {
        for (i = intervalo; i < n; i += 1)
        {
            valor = lista_inicial->pessoa[i].rg;
            for (j = i; j >= intervalo && lista_inicial->pessoa[j - intervalo].rg > valor; j -= intervalo)
            {
                swap(lista_inicial->pessoa[j], lista_inicial->pessoa[j - intervalo]);

                num_comparacoes_shell++;
                num_copias_shell += 3;
            }

            lista_inicial->pessoa[j].rg = valor;

            num_comparacoes_shell++;
            num_copias_shell += 2;
        }

        num_comparacoes_shell++;
    }

    clock_t end = clock();
    tempo_shell += (double)(end - begin) / CLOCKS_PER_SEC;
    exibe_iteracoes("Shell sort", 0, 0, tempo_shell, num_comparacoes_shell, num_copias_shell);

}

double tempo_quick = 0.0;
int num_comparacoes_quick = 0, num_copias_quick = 0;

int particao_qs(Lista_sequencial* lista_inicial, int comeco, int fim)
{
    clock_t begin = clock();

    int i = comeco, j;
    num_copias_quick++;

    for(j = comeco; j < fim; j++)
    {
        if(lista_inicial->pessoa[j].rg <= lista_inicial->pessoa[fim].rg)
        {
            swap(lista_inicial->pessoa[i++], lista_inicial->pessoa[j]);
            num_copias_quick += 3;
        }
        num_comparacoes_quick += 2;
    }
    swap(lista_inicial->pessoa[i], lista_inicial->pessoa[fim]);
    num_copias_quick += 3;

    clock_t end = clock();
    tempo_quick += (double)(end - begin) / CLOCKS_PER_SEC;

    return i;
}

void quick_sort(Lista_sequencial* lista_inicial, int comeco, int fim)
{
    clock_t begin = clock();

    if(comeco >= fim)
        return;

    int pivo = particao_qs(lista_inicial, comeco, fim);

    quick_sort(lista_inicial, comeco, pivo-1);
    quick_sort(lista_inicial, pivo+1, fim);

    clock_t end = clock();
    tempo_quick += (double)(end - begin) / CLOCKS_PER_SEC;
}

double tempo_merge = 0.0;
int num_comparacoes_merge = 0, num_copias_merge = 0;

void mescla(Lista_sequencial* lista_inicial, int esquerda, int meio, int direita)
{
    clock_t begin = clock();

    int i, j, k;
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    num_copias_merge += 2;

    Node_sequencial* Listaesquerda = new Node_sequencial[n1];
    Node_sequencial* Listadireita = new Node_sequencial[n2];

    for(i = 0; i < n1; i++)
    {
        Listaesquerda[i] = lista_inicial->pessoa[esquerda + i];

        num_copias_merge++;
        num_comparacoes_merge++;
    }

    for(j = 0; j < n2; j++)
    {
        Listadireita[j] = lista_inicial->pessoa[meio + 1 + j];

        num_copias_merge++;
        num_comparacoes_merge++;
    }

    i = 0, j = 0, k = esquerda;
    num_copias_merge += 3;

    while(i < n1 && j < n2)
    {
        if(Listaesquerda[i].rg <= Listadireita[j].rg)
        {
            lista_inicial->pessoa[k] = Listaesquerda[i];
            i++;

            num_copias_merge += 2;
        }
        else
        {
            lista_inicial->pessoa[k] = Listadireita[j];
            j++;

            num_comparacoes_merge++;
            num_copias_merge += 2;
        }

        k++;

        num_comparacoes_merge += 2;
        num_copias_merge++;
    }

    while(i < n1)
    {
        lista_inicial->pessoa[k] = Listaesquerda[i];
        i++;
        k++;

        num_comparacoes_merge++;
        num_copias_merge += 3;
    }

    while(j < n2)
    {
        lista_inicial->pessoa[k] = Listadireita[j];
        j++;
        k++;

        num_comparacoes_merge++;
        num_copias_merge += 3;
    }

    delete[] Listaesquerda;
    delete[] Listadireita;

    clock_t end = clock();
    tempo_merge += (double)(end - begin) / CLOCKS_PER_SEC;
}

void merge_sort(Lista_sequencial* lista_inicial, int esquerda, int direita)
{
    clock_t begin = clock();

    if(esquerda < direita)
    {
        int meio = esquerda + (direita - esquerda) / 2;

        num_copias_merge++;

        merge_sort(lista_inicial, esquerda, meio);
        merge_sort(lista_inicial, meio+1, direita);

        mescla(lista_inicial, esquerda, meio, direita);
    }

    num_comparacoes_merge++;

    clock_t end = clock();
    tempo_merge += (double)(end - begin) / CLOCKS_PER_SEC;
}

void ordena_lista(Lista_sequencial* lista_inicial)
{
    clock_t begin = clock();
    int n = lista_inicial->tamanho;
    int i, j, teste;

    int decisao = 0;

    while(decisao != 7)
    {
        apagaTudo();
        cout << "1 - Insertion sort" << endl;
        cout << "2 - Selection sort" << endl;
        cout << "3 - Bubble sort" << endl;
        cout << "4 - Shell sort" << endl;
        cout << "5 - Quick sort" << endl;
        cout << "6 - Merge sort" << endl;
        cout << "7 - Sair" << endl;

        cout << "digite sua opcao: ";
        cin >> decisao;

        switch(decisao)
        {
        case 1:
            apagaTudo();
            insertion_sort(lista_inicial);
            system("pause");
            break;
        case 2:
            apagaTudo();
            selection_sort(lista_inicial);
            system("pause");
            break;
        case 3:
            apagaTudo();
            bubble_sort(lista_inicial);
            system("pause");
            break;
        case 4:
            apagaTudo();
            shell_sort(lista_inicial);
            system("pause");
            break;
        case 5:
            apagaTudo();
            quick_sort(lista_inicial, 0, n-1);
            exibe_iteracoes("Quick sort", 0, 0, tempo_quick/16.6, num_comparacoes_quick, num_copias_quick);
            system("pause");
            break;
        case 6:
            apagaTudo();
            merge_sort(lista_inicial, 0, n-1);
            exibe_iteracoes("Merge sort", 0, 0, tempo_merge/13.8, num_comparacoes_merge, num_copias_merge);
            system("pause");
            break;
        case 7:
            break;

        default:
            apagaTudo();
            cout << "Valor invalido";
            system("pause");
            break;
        }
        cout << endl;
    }
}

void menuInicial(Lista_sequencial* lista_inicial)
{

    int opcaoinicial = 0;

    preenche_lista(lista_inicial);

    system("pause");
    apagaTudo();

    string nome_arquivo;

    while(opcaoinicial != 9)
    {
        cout << "\tTRABALHO 1 - LISTAS " << endl << endl;
        cout << "1 - Inserir" << endl;
        cout << "2 - Retirar" << endl;
        cout << "3 - Procurar na lista" << endl;
        cout << "4 - Imprimir lista" << endl;
        cout << "5 - Ler nova lista" << endl;
        cout << "6 - Salvar nova lista" << endl;
        cout << "7 - Dados" << endl;
        cout << "8 - Ordena a lista" << endl;
        cout << "9 - Sair" << endl;

        cout << "Escolha sua opcao: ";
        cin >> opcaoinicial;

        switch(opcaoinicial)
        {
        case 1:
            apagaTudo();
            insere(lista_inicial);
            system("pause");
            apagaTudo();
            break;

        case 2:
            apagaTudo();
            retira(lista_inicial);
            system("pause");
            apagaTudo();
            break;

        case 3:
            apagaTudo();
            procura_lista(lista_inicial);
            system("pause");
            apagaTudo();
            break;

        case 4:
            apagaTudo();
            imprime_lista(lista_inicial);
            cout << endl;
            system("pause");
            apagaTudo();
            break;

        case 5:
            apagaTudo();
            preenche_lista(lista_inicial);
            apagaTudo();
            system("pause");
            break;

        case 6:
            apagaTudo();
            salva_nova_lista(lista_inicial);
            system("pause");
            apagaTudo();
            break;

        case 7:
            apagaTudo();
            cout << "Desenvolvido por: Antonio Galvao Martins Neto" << endl;
            cout << "Desenvolvido no dia: 09/09/2023" << endl << endl;
            system("pause");
            apagaTudo();
            break;

        case 8:
            apagaTudo();
            ordena_lista(lista_inicial);
            system("pause");
            apagaTudo();
            break;

        case 9:
            apagaTudo();
            cout << "Fim do programa" << endl;
            exit(0);
            break;

        default:
            cout << "Opcao invalida, por favor escolha uma das opcoes\n\n";
            system("pause");
            apagaTudo();
            break;
        }
    }
}

int main()
{
    ///inicializa lista sequencial
    Lista_sequencial* lista_inicial;
    lista_inicial = gera_lista_sequencial();

    menuInicial(lista_inicial);

    delete lista_inicial;

    return 0;
}
