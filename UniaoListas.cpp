/*********************************************************************************************************************************************

Trabalho 1 - Listas

Autor: Antonio Galvao Martins Neto - a2557908
Curso: Bachalerado em Sistemas de Informacao
Materia: Estrutura de dados 1 - ICSF - S73
Periodo: 2
Data: 07/09/2023

**********************************************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define TAM_LISTA 15000000

using namespace std;

typedef struct node Node_encadeado;
typedef struct lista Lista_encadeada;

///para a lista encadeada
struct node
{
    string nome, rg;
    Node_encadeado* elemento_posterior;
};

struct lista
{
    int tamanho;
    Node_encadeado* primeiro;
    Node_encadeado* fim;
};

///para a lista sequencial
struct Node_sequencial
{
    string nome, rg;
};

struct Lista_sequencial
{
    struct Node_sequencial pessoa[TAM_LISTA];
    int tamanho = 0;
};

///aloca para a lista encadeada
Lista_encadeada* gera_lista()
{
    Lista_encadeada* listaa = new Lista_encadeada ;

    listaa->primeiro = NULL;
    listaa->fim = NULL;
    listaa->tamanho = 0;

    return listaa;
}

Node_encadeado* alocaNode()
{
    Node_encadeado* exemplo = new Node_encadeado;

    if(exemplo != NULL)
    {
        exemplo->nome = "";
        exemplo->rg = "";
        exemplo->elemento_posterior = NULL;
    }

    return exemplo;
}

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

void exibe_iteracoes(string nome, string rg, int posicao, double tempo_encadeada, int comparacoes, int copias)
{
    cout << endl;

    cout << "Nome: " << nome << endl;
    cout << "RG: " << rg << endl;
    cout << "Posicao na lista: " << posicao << endl;
    cout << "Tempo de execucao: " << tempo_encadeada << endl;
    cout << "C(n): " << comparacoes << endl;
    cout << "M(n): " << copias << endl;

    cout << endl;
}

void salva_nova_lista_encadeada(Lista_encadeada* listaa)
{
    ///so eh necessario um tipo de lista aqui, ja que esta salvando apenas um arquivo na biblioteca
    Node_encadeado* maluco = listaa->primeiro;

    string nome_desejado;
    cout << "Digite o nome do arquivo que voce quer salvar: " << endl << "ex: 'nome'.txt :" << endl;
    cin >> nome_desejado;

    ofstream daniel (nome_desejado);
    if (daniel.is_open())
    {
        while(maluco != NULL)
        {
            daniel << maluco->nome << ", ";
            daniel << maluco->rg << endl;
            maluco = maluco->elemento_posterior;
        }
        daniel.close();
    }
    else cout << "Unable to open file";
}


void preenche_lista(Lista_encadeada* listaa, Lista_sequencial* lista_inicial)
{
    double tempo_encadeada = 0.0;
    int num_comparacoes_encadeada = 0, num_copias_encadeadas = 0;

    string nome_seq, rg_seq;
    int i = 0;
    double tempo_sequencial = 0.0;
    int num_comparacoes_sequencial = 0, num_copias_sequencial = 0;

    string nome_arquivo = " ";
    string nome, rg;

    ///le arquivo e implementa as listas
    while(nome_arquivo == " ")
    {
        cout << "Digite o nome do arquivo a ser lido: " << endl << "ex: fulano.txt" << endl;
        cin >> nome_arquivo;
        clock_t begin = clock();

        ifstream myfile(nome_arquivo);
        ifstream arquivo(nome_arquivo);

        num_comparacoes_encadeada++;
        if (myfile.is_open())
        {
            ///lista encadeada
            while (getline(myfile, nome, ',') && getline(myfile, rg))
            {
                num_comparacoes_encadeada++;
                Node_encadeado* dados = alocaNode();

                num_comparacoes_encadeada++;
                if (dados != NULL)
                {
                    dados->nome = nome;
                    dados->rg = rg;
                    dados->elemento_posterior = NULL;

                    num_copias_encadeadas += 3;
                    num_comparacoes_encadeada++;
                    if (listaa->primeiro == NULL)
                    {
                        listaa->primeiro = dados;
                        num_copias_encadeadas++;
                    }
                    else
                    {
                        listaa->fim->elemento_posterior = dados;
                        num_comparacoes_encadeada++;
                        num_copias_encadeadas++;
                    }

                    listaa->fim = dados;
                    listaa->tamanho++;
                    num_copias_encadeadas++;
                }
            }
            clock_t end = clock();
            tempo_encadeada += (double)(end - begin) / CLOCKS_PER_SEC;

            ///lista sequencial
            clock_t begina = clock();

            while(getline(arquivo, nome_seq, ',') && getline(arquivo, rg_seq))
            {
                num_comparacoes_sequencial++;
                lista_inicial->pessoa[i].nome = nome_seq;
                lista_inicial->pessoa[i].rg = rg_seq;
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
            num_comparacoes_encadeada++;
        }
    }


    cout << "Lista preenchida ;)" << endl;
    cout << endl << "Lista encadeada: ";
    exibe_iteracoes("-", "-", listaa->tamanho, tempo_encadeada, num_comparacoes_encadeada, num_copias_encadeadas);
    cout << endl << "Lista sequencial: ";
    exibe_iteracoes("-", "-", lista_inicial->tamanho, tempo_sequencial, num_comparacoes_sequencial, num_copias_sequencial);
}

void imprime_lista(Lista_encadeada* listaa)
{
    ///noa eh necessario usar as duas listas aqui porque eu so estou imprimindo na tela
    Node_encadeado* i = listaa->primeiro;
    for(i = listaa->primeiro; i != NULL; i = i->elemento_posterior)
    {
        cout << i->nome << ' ' << i->rg << endl;
    }
}


void insere_inicio(Lista_encadeada* listaa, Lista_sequencial* lista_inicial)
{
    string nome_inserido, rg_inserido;

    cout << "digite o nome: ";
    cin >> nome_inserido;
    cout << "digite o rg: ";
    cin >> rg_inserido;

    double tempo_encadeada = 0.0;
    int num_comparacoes_encadeada = 0, num_copias_encadeadas = 0;

    int i = lista_inicial->tamanho;
    double tempo_sequencial = 0.0;
    int num_comparacoes_sequencial = 0, num_copias_sequencial = 0;

    ///lista encadeada
    clock_t begin = clock();

    Node_encadeado* dados = alocaNode();

    num_comparacoes_encadeada++;
    if (dados != NULL)
    {
        dados->nome = nome_inserido;
        dados->rg = rg_inserido;

        num_comparacoes_encadeada++;
        if (listaa->primeiro == NULL)
        {
            listaa->fim = dados;
            num_copias_encadeadas++;
        }
        else
        {
            dados->elemento_posterior = listaa->primeiro;
            num_copias_encadeadas++;
            num_comparacoes_encadeada++;
        }

        listaa->primeiro = dados;
        num_copias_encadeadas++;

    }

    listaa->tamanho++;

    clock_t end = clock();
    tempo_encadeada += (double)(end - begin) / CLOCKS_PER_SEC;

    cout << endl << "Lista encadeada: ";
    exibe_iteracoes(nome_inserido, rg_inserido, 1, tempo_encadeada, num_comparacoes_encadeada, num_copias_encadeadas);

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

void insere_final(Lista_encadeada* listaa, Lista_sequencial* lista_inicial)
{
    string nome_inserido, rg_inserido;

    cout << "digite o nome: ";
    cin >> nome_inserido;
    cout << "digite o rg: ";
    cin >> rg_inserido;

    ///lista encadeada
    double tempo_encadeada = 0.0;
    int num_comparacoes_encadeada = 0, num_copias_encadeadas = 0;

    clock_t begin = clock();

    Node_encadeado* dados = alocaNode();

    num_comparacoes_encadeada++;
    if (dados != NULL)
    {
        dados->nome = nome_inserido;
        dados->rg = rg_inserido;
        dados->elemento_posterior = NULL;
        num_copias_encadeadas += 3;

        num_comparacoes_encadeada++;
        if(listaa->primeiro == NULL)
        {
            listaa->primeiro = dados;
            num_copias_encadeadas++;
        }

        else
        {
            listaa->fim->elemento_posterior = dados;
            num_copias_encadeadas++;
            num_comparacoes_encadeada++;
        }

        listaa->fim = dados;
        num_copias_encadeadas++;
    }
    listaa->tamanho++;
    clock_t end = clock();
    tempo_encadeada += (double)(end - begin) / CLOCKS_PER_SEC;
    cout << endl << "Lista encadeada: ";
    exibe_iteracoes(nome_inserido, rg_inserido, listaa->tamanho, tempo_encadeada, num_comparacoes_encadeada, num_copias_encadeadas);

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
    cout << "Lista sequencial: ";
    exibe_iteracoes(nome_inserido, rg_inserido, lista_inicial->tamanho, tempo_sequencial, num_comparacoes_sequencial, num_copias_sequencial);
}

void insere_onde_quiser(Lista_encadeada* listaa, Lista_sequencial* lista_inicial)
{
    string nome_inserido, rg_inserido;
    int posicao;

    cout << "digite o nome: ";
    cin >> nome_inserido;
    cout << "digite o rg: ";
    cin >> rg_inserido;

    cout << "digite a posicao: ";
    cin >> posicao;

    ///lista encadeada
    double tempo_encadeada = 0.0;
    int num_comparacoes_encadeada = 0, num_copias_encadeadas = 0;

    clock_t begin = clock();

    Node_encadeado* dados = alocaNode();

    num_comparacoes_encadeada++;
    if (dados != NULL)
    {
        dados->nome = nome_inserido;
        dados->rg = rg_inserido;

        num_copias_encadeadas += 2;

        num_comparacoes_encadeada++;
        if (posicao == 1)
        {
            dados->elemento_posterior = listaa->primeiro;
            listaa->primeiro = dados;
            num_copias_encadeadas += 2;

            num_comparacoes_encadeada++;
            if(listaa->primeiro == NULL)
            {
                listaa->fim = dados;
                num_copias_encadeadas++;
            }
        }
        else if (posicao == listaa->tamanho)
        {
            dados->elemento_posterior = NULL;
            listaa->fim->elemento_posterior = dados;
            listaa->fim = dados;

            num_copias_encadeadas += 3;
            num_comparacoes_encadeada++;
        }


        else
        {
            Node_encadeado* anterior = listaa->primeiro;
            for (int i = 0; i < posicao - 2; i++)
            {
                num_comparacoes_encadeada++;
                anterior = anterior->elemento_posterior;
                num_copias_encadeadas++;
            }

            dados->elemento_posterior = anterior->elemento_posterior;
            anterior->elemento_posterior = dados;

            num_comparacoes_encadeada += 2;
            num_copias_encadeadas += 3;
        }
    }
    listaa->tamanho++;

    clock_t end = clock();
    tempo_encadeada += (double)(end - begin) / CLOCKS_PER_SEC;
    cout << endl << "Lista encadeada: ";
    exibe_iteracoes(nome_inserido, rg_inserido, posicao, tempo_encadeada, num_comparacoes_encadeada, num_copias_encadeadas);

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
    cout << "Lista sequencial: ";
    exibe_iteracoes(nome_inserido, rg_inserido, posicao, tempo_sequencial, num_comparacoes_sequencial, num_copias_sequencial);

}

void retira_inicio(Lista_encadeada* listaa, Lista_sequencial* lista_inicial)
{
    string nome_retirado, rg_retirado;
    ///lista encadeada
    double tempo_encadeada = 0.0;
    int num_comparacoes_encadeada = 0, num_copias_encadeadas = 0;

    clock_t begin = clock();

    num_comparacoes_encadeada++;
    if(listaa->primeiro != NULL)
    {
        nome_retirado = listaa->primeiro->nome;
        rg_retirado = listaa->primeiro->rg;

        Node_encadeado* teste = listaa->primeiro;

        listaa->primeiro = listaa->primeiro->elemento_posterior;

        num_copias_encadeadas += 4;

        delete teste;
        listaa->tamanho--;
    }

    clock_t end = clock();
    tempo_encadeada += (double)(end - begin) / CLOCKS_PER_SEC;
    cout << "Lista encadeada: ";
    exibe_iteracoes(nome_retirado, rg_retirado, 1, tempo_encadeada, num_comparacoes_encadeada, num_copias_encadeadas);

    ///lista sequencial
    string nome, rg ;
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
    lista_inicial->pessoa[lista_inicial->tamanho - 1].rg = "";

    lista_inicial->tamanho--;

    clock_t enda = clock();
    tempo_sequencial += (double)(enda - begina) / CLOCKS_PER_SEC;
    cout << "Lista sequencial ";
    exibe_iteracoes(nome, rg, 1, tempo_sequencial, num_comparacoes_sequencial, num_copias_sequencial);
}

void retira_final(Lista_encadeada* listaa, Lista_sequencial* lista_inicial)
{
    string nome_retirado, rg_retirado;

    ///lista encadeada
    double tempo_encadeada = 0.0;
    int num_comparacoes_encadeada = 0, num_copias_encadeadas = 0;

    clock_t begin = clock();

    if(listaa->primeiro != NULL)
    {
        num_comparacoes_encadeada++;

        Node_encadeado* teste = listaa->primeiro;
        Node_encadeado* anterior = NULL;

        num_copias_encadeadas += 2;

        while(teste->elemento_posterior != NULL)
        {
            num_comparacoes_encadeada++;
            anterior = teste;
            teste = teste->elemento_posterior;

            num_copias_encadeadas += 2;
        }

        num_comparacoes_encadeada++;
        if(anterior != NULL)
        {
            listaa->fim = anterior->elemento_posterior;

            nome_retirado = listaa->fim->nome;
            rg_retirado = listaa->fim->rg;

            num_copias_encadeadas += 4;
        }
        else
        {
            listaa->primeiro = NULL;
            listaa->fim = NULL;

            num_copias_encadeadas += 2;
            num_comparacoes_encadeada++;
        }

        delete teste;
        listaa->tamanho--;
    }

    clock_t end = clock();
    tempo_encadeada += (double)(end - begin) / CLOCKS_PER_SEC;
    cout << "Lista encadeada: ";
    exibe_iteracoes(nome_retirado, rg_retirado, listaa->tamanho + 1, tempo_encadeada, num_comparacoes_encadeada, num_copias_encadeadas);


    ///lista sequencial
    string nome, rg;
    double tempo_sequencial = 0.0;
    int num_comparacoes_sequencial = 0, num_copias_sequencial = 0;

    clock_t begina = clock();

    nome = lista_inicial->pessoa[lista_inicial->tamanho - 1].nome;
    rg = lista_inicial->pessoa[lista_inicial->tamanho - 1].rg;

    lista_inicial->pessoa[lista_inicial->tamanho - 1].nome = "";
    lista_inicial->pessoa[lista_inicial->tamanho - 1].rg = "";

    num_copias_sequencial += 4;

    lista_inicial->tamanho--;

    clock_t enda = clock();
    tempo_sequencial += (double)(enda - begina) / CLOCKS_PER_SEC;

    cout << "Lista sequencial: ";
    exibe_iteracoes(nome, rg, lista_inicial->tamanho + 1, tempo_sequencial, num_comparacoes_sequencial, num_copias_sequencial);
}

void retira_onde_quiser(Lista_encadeada* listaa, Lista_sequencial* lista_inicial)
{
    ///lista encadeada
    string nome_retirado, rg_retirado;
    double tempo_encadeada = 0.0;
    int num_comparacoes_encadeada = 0, num_copias_encadeadas = 0;

    clock_t begin = clock();

    int posicao, i;

    cout << "Que linha deseja retirar? ";
    cin >> posicao;

    Node_encadeado* anterior = NULL;
    Node_encadeado* atual = listaa->primeiro;
    num_copias_encadeadas += 2;

    for(i = 0; i < posicao - 1 && atual != NULL; i++)
    {
        num_comparacoes_encadeada++;
        anterior = atual;
        atual = atual->elemento_posterior;
        num_copias_encadeadas += 2;
    }

    num_comparacoes_encadeada++;
    if(atual != NULL)
    {
        nome_retirado = atual->nome;
        rg_retirado = atual->rg;
        num_copias_encadeadas++;

        num_comparacoes_encadeada++;
        if(anterior != NULL)
        {
            anterior->elemento_posterior = atual->elemento_posterior;
            num_copias_encadeadas++;
        }
        else
        {
            listaa->primeiro = listaa->primeiro->elemento_posterior;
            num_copias_encadeadas++;
        }
    }
    else
    {
        num_comparacoes_encadeada++;
        listaa->primeiro = atual->elemento_posterior;
        num_copias_encadeadas++;

        num_comparacoes_encadeada++;
        if(atual == listaa->fim)
        {
            listaa->fim = NULL;
            num_copias_encadeadas++;
        }
    }
    delete atual;
    listaa->tamanho--;

    clock_t end = clock();
    tempo_encadeada += (double)(end - begin) / CLOCKS_PER_SEC;
    cout << endl << "Lista encadeada: ";
    exibe_iteracoes(nome_retirado, rg_retirado, posicao, tempo_encadeada, num_comparacoes_encadeada, num_copias_encadeadas);


    ///lista sequencial
    double tempo_sequencial = 0.0;
    int num_comparacoes_sequencial = 0, num_copias_sequencial = 0;
    string nome, rg;

    nome = lista_inicial->pessoa[posicao - 1].nome;
    rg = lista_inicial->pessoa[posicao - 1].rg;
    num_copias_sequencial += 2;

    clock_t begina = clock();

    for(i = posicao - 1; i < lista_inicial->tamanho ; i++)
    {
        num_comparacoes_sequencial++;
        lista_inicial->pessoa[i].nome = lista_inicial->pessoa[i + 1].nome;
        lista_inicial->pessoa[i].rg = lista_inicial->pessoa[i + 1].rg;

        num_copias_sequencial += 2;
    }

    lista_inicial->pessoa[lista_inicial->tamanho - 1].nome = "";
    lista_inicial->pessoa[lista_inicial->tamanho - 1].rg = "";

    num_copias_sequencial += 2;

    lista_inicial->tamanho--;

    clock_t enda = clock();
    tempo_sequencial += (double)(enda - begina) / CLOCKS_PER_SEC;
    cout << "Lista sequencial: ";
    exibe_iteracoes(nome, rg, posicao, tempo_sequencial, num_comparacoes_sequencial, num_copias_sequencial);
}

void procura_lista(Lista_encadeada* listaa, Lista_sequencial* lista_inicial)
{
    ///lista encadeada
    string valor_procurado, nome;
    int flag = 1, posicao = 0;

    double tempo_encadeada = 0.0;
    int num_comparacoes_encadeada = 0, num_copias_encadeadas = 0;

    Node_encadeado* teste = listaa->primeiro;
    num_copias_encadeadas++;

    cout << "Digite o valor que deseja procurar: ";
    cin >> valor_procurado;

    clock_t begin = clock();

    while(teste != NULL && flag != 0)
    {
        num_comparacoes_encadeada++;
        if(teste->rg == valor_procurado)
        {
            cout << "nome encontrado: " << teste->nome << endl << endl;
            nome = teste->nome;
            flag = 0;
            num_copias_encadeadas++;

            clock_t end = clock();
            tempo_encadeada += (double)(end - begin) / CLOCKS_PER_SEC;
            cout << "Lista encadeada: ";
            exibe_iteracoes(nome, valor_procurado, posicao + 1, tempo_encadeada, num_comparacoes_encadeada, num_copias_encadeadas);
        }
        teste = teste->elemento_posterior;
        num_copias_encadeadas++;
        posicao++;
    }

    ///lista sequencial
    double tempo_sequencial = 0.0;
    int i = 0, num_comparacoes_sequencial = 0, num_copias_sequencial = 0;
    flag = 0;

    clock_t begina = clock();

    cout << begina << endl << endl;

    while(i < lista_inicial->tamanho && flag != 1)
    {
        num_comparacoes_sequencial += 2;

        if(lista_inicial->pessoa[i].rg == valor_procurado)
        {
            clock_t enda = clock();
            tempo_sequencial += (double)(enda - begina) / CLOCKS_PER_SEC;

            nome = lista_inicial->pessoa[i].nome;

            num_copias_sequencial += 2;
            cout << "Lista sequencial: ";
            exibe_iteracoes(nome, valor_procurado, i + 1, tempo_sequencial, num_comparacoes_sequencial, num_copias_sequencial);

            flag = 1;
        }

        i++;
    }

}


void menuInicial(Lista_encadeada* listaa, Lista_sequencial* lista_inicial)
{

    int opcaoinicial = 0;

    preenche_lista(listaa, lista_inicial);

    string nome_arquivo;

    while(opcaoinicial != 12)
    {
        cout << "\tTRABALHO 1 - LISTAS " << endl << endl;
        cout << "1 - Inserir no incio" << endl;
        cout << "2 - Inserir no final" << endl;
        cout << "3 - Inserir onde quiser" << endl;
        cout << "4 - Retirar do inicio" << endl;
        cout << "5 - Retirar do final" << endl;
        cout << "6 - Retirar onde quiser" << endl;
        cout << "7 - Procurar na lista" << endl;
        cout << "8 - Imprimir lista" << endl;
        cout << "9 - Ler nova lista" << endl;
        cout << "10 - Salvar nova lista" << endl;
        cout << "11 - Dados" << endl;
        cout << "12 - Sair" << endl;

        cout << "Escolha sua opcao: ";
        cin >> opcaoinicial;

        switch(opcaoinicial)
        {
        case 1:
            apagaTudo();
            insere_inicio(listaa, lista_inicial);
            system("pause");
            apagaTudo();
            break;

        case 2:
            apagaTudo();
            insere_final(listaa, lista_inicial);
            system("pause");
            apagaTudo();
            break;

        case 3:
            apagaTudo();
            insere_onde_quiser(listaa, lista_inicial);
            system("pause");
            apagaTudo();
            break;

        case 4:
            apagaTudo();
            retira_inicio(listaa, lista_inicial);
            system("pause");
            apagaTudo();
            break;

        case 5:
            apagaTudo();
            retira_final(listaa, lista_inicial);
            system("pause");
            apagaTudo();
            break;

        case 6:
            apagaTudo();
            retira_onde_quiser(listaa, lista_inicial);
            system("pause");
            apagaTudo();
            break;

        case 7:
            apagaTudo();
            procura_lista(listaa, lista_inicial);
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
            preenche_lista(listaa, lista_inicial);
            apagaTudo();
            system("pause");
            break;

        case 10:
            apagaTudo();
            salva_nova_lista_encadeada(listaa);
            system("pause");
            apagaTudo();
            break;

        case 11:
            apagaTudo();
            cout << "Desenvolvido por: Antonio Galvao Martins Neto" << endl;
            cout << "Desenvolvido no dia: 09/09/2023" << endl << endl;
            system("pause");
            apagaTudo();
            break;

        case 12:
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
    ///inicializa lista encadeada
    Lista_encadeada* listaa;
    listaa = gera_lista();

    ///inicializa lista sequencial
    Lista_sequencial* lista_inicial;
    lista_inicial = gera_lista_sequencial();

    menuInicial(listaa, lista_inicial);

    delete listaa;
    delete lista_inicial;

    return 0;
}
