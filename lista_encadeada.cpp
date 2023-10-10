#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

using namespace std;

typedef struct node Node_encadeado;
typedef struct lista Lista_encadeada;


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

void apagaTudo()
{
    system("cls");
}

void exibe_iteracoes(string nome, string rg, int posicao, double tempo_encadeada, int comparacoes, int copias)
{
    cout << endl << endl;

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


void preenche_lista(Lista_encadeada* listaa)
{
    double tempo_encadeada = 0.0;
    int num_comparacoes_encadeada = 0, num_copias_encadeadas = 0;

    string nome_arquivo = " ";
    string nome, rg;

    clock_t begin = clock();

    while(nome_arquivo == " ")
    {
        cout << "Digite o nome do arquivo a ser lido: ";
        cin >> nome_arquivo;

        ifstream myfile(nome_arquivo);

        num_comparacoes_encadeada++;
        if (myfile.is_open())
        {
            while (getline(myfile, nome, ',') && getline(myfile, rg))
            {
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
        }
        else
        {
            apagaTudo();
            cout << "Arquivo nao encontrado" << endl << endl;
            nome_arquivo = " ";
            num_comparacoes_encadeada++;
        }
    }

    clock_t end = clock();
    tempo_encadeada += (double)(end - begin) / CLOCKS_PER_SEC;

    cout << "Lista preenchida ;)" << endl;
    exibe_iteracoes("-", "-", listaa->tamanho, tempo_encadeada, num_comparacoes_encadeada, num_copias_encadeadas);
}

void imprime_lista(Lista_encadeada* listaa)
{
    double tempo_encadeada = 0.0;
    int num_comparacoes_encadeada = 0, num_copias_encadeadas = 0;

    clock_t begin = clock();

    Node_encadeado* i;
    for(i = listaa->primeiro; i != NULL; i = i->elemento_posterior)
    {
        cout << i->nome << ' ' << i->rg << endl;
        num_copias_encadeadas += 2;
        num_comparacoes_encadeada++;
    }

    clock_t end = clock();
    tempo_encadeada += (double)(end - begin) / CLOCKS_PER_SEC;

    exibe_iteracoes("-", "-", listaa->tamanho, tempo_encadeada, num_comparacoes_encadeada, num_copias_encadeadas);
}


void insere_inicio(Lista_encadeada* listaa)
{
    string nome_inserido, rg_inserido;

    cout << "digite o nome: ";
    cin >> nome_inserido;
    cout << "digite o rg: ";
    cin >> rg_inserido;

    double tempo_encadeada = 0.0;
    int num_comparacoes_encadeada = 0, num_copias_encadeadas = 0;

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

    exibe_iteracoes(nome_inserido, rg_inserido, 1, tempo_encadeada, num_comparacoes_encadeada, num_copias_encadeadas);
}

void insere_final(Lista_encadeada* listaa)
{
    string nome_inserido, rg_inserido;

    cout << "digite o nome: ";
    cin >> nome_inserido;
    cout << "digite o rg: ";
    cin >> rg_inserido;

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

    exibe_iteracoes(nome_inserido, rg_inserido, listaa->tamanho, tempo_encadeada, num_comparacoes_encadeada, num_copias_encadeadas);
}

void insere_onde_quiser(Lista_encadeada* listaa)
{
    string nome_inserido, rg_inserido;
    int posicao;

    cout << "digite o nome: ";
    cin >> nome_inserido;
    cout << "digite o rg: ";
    cin >> rg_inserido;

    cout << "digite a posicao: ";
    cin >> posicao;

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

    exibe_iteracoes(nome_inserido, rg_inserido, posicao, tempo_encadeada, num_comparacoes_encadeada, num_copias_encadeadas);
}

void retira_inicio(Lista_encadeada* listaa)
{
    string nome_retirado, rg_retirado;
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

    exibe_iteracoes(nome_retirado, rg_retirado, 1, tempo_encadeada, num_comparacoes_encadeada, num_copias_encadeadas);
}

void retira_final(Lista_encadeada* listaa)
{
    string nome_retirado, rg_retirado;
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

    exibe_iteracoes(nome_retirado, rg_retirado, listaa->tamanho + 1, tempo_encadeada, num_comparacoes_encadeada, num_copias_encadeadas);
}

void retira_onde_quiser(Lista_encadeada* listaa)
{
    string nome_retirado, rg_retirado;
    double tempo_encadeada = 0.0;
    int num_comparacoes_encadeada = 0, num_copias_encadeadas = 0;

    int posicao, i;

    cout << "Que linha deseja retirar? ";
    cin >> posicao;

    clock_t begin = clock();

    Node_encadeado* anterior = NULL;
    Node_encadeado* atual = listaa->primeiro;
    num_copias_encadeadas += 2;

    for(i = 0; i < posicao - 1 && atual != NULL; i++)
    {
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

    exibe_iteracoes(nome_retirado, rg_retirado, posicao, tempo_encadeada, num_comparacoes_encadeada, num_copias_encadeadas);
}

void procura_lista_encadeada(Lista_encadeada* listaa)
{
    string valor_procurado, nome;
    int flag = 1, posicao = 0;

    double tempo_encadeada = 0.0;
    int num_comparacoes_encadeada = 0, num_copias_encadeadas = 0;

    clock_t begin = clock();

    Node_encadeado* teste = listaa->primeiro;
    num_copias_encadeadas++;

    cout << "Digite o valor que deseja procurar: ";
    cin >> valor_procurado;

    while(teste != NULL && flag != 0)
    {
        posicao++;
        num_comparacoes_encadeada++;
        if(teste->rg == valor_procurado)
        {
            cout << "nome encontrado: " << teste->nome << endl << endl;
            nome = teste->nome;
            flag = 0;
            num_copias_encadeadas++;
        }
        teste = teste->elemento_posterior;
        num_copias_encadeadas++;

    }

    clock_t end = clock();
    tempo_encadeada += (double)(end - begin) / CLOCKS_PER_SEC;

    exibe_iteracoes(nome, valor_procurado, posicao, tempo_encadeada, num_comparacoes_encadeada, num_copias_encadeadas);

}


void menuInicial(Lista_encadeada* listaa)
{

    int opcaoinicial = 0;

    preenche_lista(listaa);

    string nome_arquivo;

    while(opcaoinicial != 12)
    {
        cout << "\tTRABALHO 1 - LISTA ENCADEADA " << endl << endl;
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
            procura_lista_encadeada(listaa);
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
            preenche_lista(listaa);
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

    Lista_encadeada* listaa;

    listaa = gera_lista();

    menuInicial(listaa);

    return 0;
}
