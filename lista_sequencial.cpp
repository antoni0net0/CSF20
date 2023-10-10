#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

///mudar o tamanho da lista de acordo com o arquivo que eh lido
#define TAM_LISTA 15000000

ifstream myfile ("NomeRG1K.txt");

struct Node_sequencial
{
    string nome, rg;
};

struct Lista_sequencial
{
    struct Node_sequencial pessoa[TAM_LISTA];
    int tamanho = 0;
};

Lista_sequencial* gera_lista()
{
    Lista_sequencial* lista = new Lista_sequencial;

    if(lista != NULL)
        lista->tamanho = 0;

    return lista;
}

void preenche_lista(Lista_sequencial* lista_inicial)
{
    string nome, rg;

    if(myfile.is_open())
    {
        while(getline(myfile, nome, ',') && getline(myfile, rg))
        {
            lista_inicial->pessoa[lista_inicial->tamanho].nome = nome;
            lista_inicial->pessoa[lista_inicial->tamanho].rg = rg;
            lista_inicial->tamanho++;
        }
    }

}

void exibe_iteracoes(string nome, string rg, int posicao, double tempo_sequencial, int comparacoes, int copias)
{
    cout << endl << endl;

    cout << "Nome: " << nome << endl;
    cout << "RG: " << rg << endl;
    cout << "Posicao na lista: " << posicao << endl;
    cout << "Tempo de execucao: " << tempo_sequencial << endl;
    cout << "C(n): " << comparacoes << endl;
    cout << "M(n): " << copias << endl;

    cout << endl;
}

void insere_onde_quiser(Lista_sequencial* lista_inicial)
{
    int i = 0;
    double tempo_sequencial = 0.0;
    int num_comparacoes_sequencial = 0, num_copias_sequencial = 0;
    int posicao = 1;

    string nome_inserido, rg_inserido;
    cout << "digite um nome: ";
    cin >> nome_inserido;
    cout << "digite um rg: ";
    cin >> rg_inserido;

    cout << "onde deseja posicionar o nome e o rg inserido? ";
    cin >> posicao;

    clock_t begin = clock();

    for(i = lista_inicial->tamanho; i > posicao ; i--)
    {
        lista_inicial->pessoa[i + 1].nome = lista_inicial->pessoa[i].nome;
        lista_inicial->pessoa[i + 1].rg = lista_inicial->pessoa[i].rg;

        num_copias_sequencial += 2;
    }

    lista_inicial->pessoa[posicao - 1].nome = nome_inserido;
    lista_inicial->pessoa[posicao - 1].rg = rg_inserido;
    lista_inicial->tamanho++;

    num_copias_sequencial += 2;

    clock_t end = clock();
    tempo_sequencial += (double)(end - begin) / CLOCKS_PER_SEC;

    exibe_iteracoes(nome_inserido, rg_inserido, posicao, tempo_sequencial, num_comparacoes_sequencial, num_copias_sequencial);
}

void insere_inicio(Lista_sequencial* lista_inicial)
{
    string nome_inserido, rg_inserido;
    string nome, rg;
    int i = lista_inicial->tamanho;
    double tempo_sequencial = 0.0;
    int num_comparacoes_sequencial = 0, num_copias_sequencial = 0;

    cout << "digite um nome: ";
    cin >> nome_inserido;
    cout << "digite um rg: ";
    cin >> rg_inserido;

    clock_t begin = clock();

    while(i > 0)
        {
            lista_inicial->pessoa[i].nome = lista_inicial->pessoa[i - 1].nome;
            lista_inicial->pessoa[i].rg = lista_inicial->pessoa[i - 1].rg;
            i--;

            num_copias_sequencial += 2;
        }

    lista_inicial->pessoa[0].nome = nome_inserido;
    lista_inicial->pessoa[0].rg = rg_inserido;
    lista_inicial->tamanho++;

    num_copias_sequencial += 2;

    clock_t end = clock();
    tempo_sequencial += (double)(end - begin) / CLOCKS_PER_SEC;

    exibe_iteracoes(nome_inserido, rg_inserido, 1, tempo_sequencial, num_comparacoes_sequencial, num_copias_sequencial);
}


void insere_final(Lista_sequencial* lista_inicial)
{
    int i = 0;
    double tempo_sequencial = 0.0;
    int num_comparacoes_sequencial = 0, num_copias_sequencial = 0;

    string nome_inserido, rg_inserido;
    cout << "digite um nome: ";
    cin >> nome_inserido;
    cout << "digite um rg: ";
    cin >> rg_inserido;

    clock_t begin = clock();

    lista_inicial->pessoa[lista_inicial->tamanho].nome = nome_inserido;
    lista_inicial->pessoa[lista_inicial->tamanho].rg = rg_inserido;

    num_copias_sequencial += 2;

    lista_inicial->tamanho++;

    clock_t end = clock();
    tempo_sequencial += (double)(end - begin) / CLOCKS_PER_SEC;

    exibe_iteracoes(nome_inserido, rg_inserido, lista_inicial->tamanho, tempo_sequencial, num_comparacoes_sequencial, num_copias_sequencial);
}

void retira_inicio(Lista_sequencial* lista_inicial)
{
    string vazia = "";
    string nome, rg;
    int i;
    double tempo_sequencial = 0.0;
    int num_comparacoes_sequencial = 0, num_copias_sequencial = 0;

    clock_t begin = clock();

    nome = lista_inicial->pessoa[0].nome;
    rg = lista_inicial->pessoa[0].rg;

    for(i = 0; i < lista_inicial->tamanho - 1; i++)
    {
        lista_inicial->pessoa[i].nome = lista_inicial->pessoa[i + 1].nome;
        lista_inicial->pessoa[i].rg = lista_inicial->pessoa[i + 1].rg;

        num_copias_sequencial += 2;
    }

    lista_inicial->pessoa[lista_inicial->tamanho - 1].nome = vazia;
    lista_inicial->pessoa[lista_inicial->tamanho - 1].rg = vazia;

    lista_inicial->tamanho--;

    clock_t end = clock();
    tempo_sequencial += (double)(end - begin) / CLOCKS_PER_SEC;

    exibe_iteracoes(nome, rg, 1, tempo_sequencial, num_comparacoes_sequencial, num_copias_sequencial);

}

void retira_final(Lista_sequencial* lista_inicial)
{
    string vazia = "";
    string nome, rg;
    double tempo_sequencial = 0.0;
    int num_comparacoes_sequencial = 0, num_copias_sequencial = 0;

    clock_t begin = clock();

    nome = lista_inicial->pessoa[lista_inicial->tamanho - 1].nome;
    rg = lista_inicial->pessoa[lista_inicial->tamanho - 1].rg;

    lista_inicial->pessoa[lista_inicial->tamanho - 1].nome = vazia;
    lista_inicial->pessoa[lista_inicial->tamanho - 1].rg = vazia;

    num_copias_sequencial += 4;

    lista_inicial->tamanho--;

    clock_t end = clock();
    tempo_sequencial += (double)(end - begin) / CLOCKS_PER_SEC;


    exibe_iteracoes(nome, rg, lista_inicial->tamanho + 1, tempo_sequencial, num_comparacoes_sequencial, num_copias_sequencial);
}

void retira_onde_quiser(Lista_sequencial* lista_inicial)
{
    int linha = 0;
    double tempo_sequencial = 0.0;
    int num_comparacoes_sequencial = 0, num_copias_sequencial = 0;
    int i;
    string nome, rg;
    string vazia = "";


    cout << "Que linha deseja retirar? ";
    cin >> linha;

    nome = lista_inicial->pessoa[linha - 1].nome;
    rg = lista_inicial->pessoa[linha - 1].rg;
    num_copias_sequencial += 2;

    clock_t begin = clock();

    for(i = linha - 1; i < lista_inicial->tamanho ; i++)
    {
        lista_inicial->pessoa[i].nome = lista_inicial->pessoa[i + 1].nome;
        lista_inicial->pessoa[i].rg = lista_inicial->pessoa[i + 1].rg;

        num_copias_sequencial += 2;
    }

    lista_inicial->pessoa[lista_inicial->tamanho - 1].nome = vazia;
    lista_inicial->pessoa[lista_inicial->tamanho - 1].rg = vazia;

    num_copias_sequencial += 2;

    lista_inicial->tamanho--;

    clock_t end = clock();
    tempo_sequencial += (double)(end - begin) / CLOCKS_PER_SEC;

    exibe_iteracoes(nome, rg, linha, tempo_sequencial, num_comparacoes_sequencial, num_copias_sequencial);
}

void procura_lista(Lista_sequencial* lista_inicial)
{
    string valor_procurado;
    string nome;
    double tempo_sequencial = 0.0;
    int i = 0, num_comparacoes_sequencial = 0, num_copias_sequencial = 0;
    int flag = 0;

    cout << "o que deseja procurar? " << endl;
    cin >> valor_procurado;

    clock_t begin = clock();

    while(i < lista_inicial->tamanho || flag != 0)
    {
        num_comparacoes_sequencial++;

        if(lista_inicial->pessoa[i].rg == valor_procurado)
        {
            clock_t end = clock();
            tempo_sequencial += (double)(end - begin) / CLOCKS_PER_SEC;

            nome = lista_inicial->pessoa[i].nome;

            num_copias_sequencial += 2;

            exibe_iteracoes(nome, valor_procurado, i+1, tempo_sequencial, num_comparacoes_sequencial, num_copias_sequencial);

            flag = 1;
        }

        i++;
    }

    if(flag == 0)
    {
        cout << endl << "RG nao encontrado" << endl << endl;
    }

}

void imprime_lista(Lista_sequencial* lista_inicial)
{
    int i;

    double tempo_sequencial = 0.0;
    int num_comparacoes_sequencial = 0, num_copias_sequencial = 0;

    clock_t begin = clock();

    for(i = 0; i < lista_inicial->tamanho; i++)
    {
        cout << lista_inicial->pessoa[i].nome << ' ' << lista_inicial->pessoa[i].rg << endl;
    }

    clock_t end = clock();
    tempo_sequencial += (double)(end - begin) / CLOCKS_PER_SEC;

    exibe_iteracoes("-", "-", lista_inicial->tamanho, tempo_sequencial, num_comparacoes_sequencial, num_copias_sequencial);
}

void apagaTudo()
{
    system("CLS");
}

void menuInicial(Lista_sequencial *listaa){

    int opcaoinicial;

    preenche_lista(listaa);


    while(opcaoinicial != 10){
    cout << "\tTRABALHO 1 - LISTA SEQUENCIAL " << endl << endl;
    cout << "1 - Inserir no incio" << endl;
    cout << "2 - Inserir no final" << endl;
    cout << "3 - Inserir onde quiser" << endl;
    cout << "4 - Retirar do inicio" << endl;
    cout << "5 - Retirar do final" << endl;
    cout << "6 - Retirar onde quiser" << endl;
    cout << "7 - Procurar na lista" << endl;
    cout << "8 - Imprimir lista" << endl;
    cout << "9 - Dados" << endl;
    cout << "10 - Sair" << endl;
    cout << "Escolha sua opcao: ";
    cin >> opcaoinicial;


    switch(opcaoinicial)
    {
    case 1:
        apagaTudo();
        insere_inicio(listaa);
        system("pause");
        apagaTudo();
        break;

    case 2:
        apagaTudo();
        insere_final(listaa);
        system("pause");
        apagaTudo();
        break;

    case 3:
        apagaTudo();
        insere_onde_quiser(listaa);
        system("pause");
        apagaTudo();
        break;

    case 4:
        apagaTudo();
        retira_inicio(listaa);
        system("pause");
        apagaTudo();
        break;

    case 5:
        apagaTudo();
        retira_final(listaa);
        system("pause");
        apagaTudo();
        break;

    case 6:
        apagaTudo();
        retira_onde_quiser(listaa);
        system("pause");
        apagaTudo();
        break;

    case 7:
        apagaTudo();
        procura_lista(listaa);
        system("pause");
        apagaTudo();
        break;

    case 8:
        apagaTudo();
        imprime_lista(listaa);
        cout << endl;
        system("pause");
        apagaTudo();
        break;

    case 9:
        apagaTudo();
        cout << "Desenvolvido por: Antonio Galvao Martins Neto" << endl;
        cout << "Desenvolvido no dia: 07/09/2023" << endl << endl;
        system("pause");
        apagaTudo();
        break;

    case 10:
        apagaTudo();
        cout << "Fim do programa";
        delete listaa->pessoa;
        exit(0);
        break;

    default:
        cout << "Opcao invalida, por favor escolha uma das opcoes\n\n";
        system("pause");
        apagaTudo();
        break;
    }



    }

    delete listaa;
}

int main()
{

    Lista_sequencial* lista_inicial;
    lista_inicial = gera_lista();

    menuInicial(lista_inicial);

    return 0;
}
