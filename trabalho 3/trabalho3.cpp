/*********************************************************************************************************************************************

Trabalho 3 - Arquivo Invertido

Autor: Antonio Galvao Martins Neto - a2557908
Curso: Bachalerado em Sistemas de Informacao
Materia: Estrutura de dados 1 - ICSF - S73
Periodo: 2
Data: 01/12/2023

**********************************************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

#define TAM_LISTA 150000

using namespace std;

struct Node
{
    string palavra;
    char letra;
    int posicao_palavra = 0;
    int posicao_letra = 0;
    int numero_letras = 0;
};

struct Lista
{
    struct Node lista_palavras[TAM_LISTA];
    int tamanho = 0;

    string paragrafo;
};

struct Ocorrencia
{
    int indice;
    int posicao_letra;
};

struct Arquivo_Invertido
{
    int numeroPalavras = 0;

    vector<string> palavras;
    vector<vector<Ocorrencia>> ocorrencias;

    void adicionarPalavra(string& conteudoPalavra, int indice, int posicao_letra)
    {
        for (size_t i = 0; i < palavras.size(); ++i)
        {
            if (palavras[i] == conteudoPalavra)
            {
                ocorrencias[i].push_back({indice, posicao_letra});
                return;
            }
        }

        palavras.push_back(conteudoPalavra);
        ocorrencias.push_back({{indice, posicao_letra}});
    }

    void procura_palavra(string& palavra)
    {
        int totalOcorrencias = 0;

        for (size_t i = 0; i < palavras.size(); i++)
        {
            if (palavras[i] == palavra)
            {
                totalOcorrencias += ocorrencias[i].size();
            }
        }

        if(totalOcorrencias > 0)
            cout << "A palavra '" << palavra << "' ocorre " << totalOcorrencias << " vezes no arquivo invertido." << endl;
        else
            cout << "A palavra '" << palavra << "' nao foi encontrada no arquivo invertido." << endl;
    }

    void exibeArquivoInvertido(bool ler_letra)
    {
        for (size_t i = 0; i < palavras.size(); i++)
        {
            cout << palavras[i] << " : ";
            for (size_t j = 0; j < ocorrencias[i].size(); j++)
            {
                if(ler_letra)
                    cout << ocorrencias[i][j].posicao_letra;
                else
                    cout << ocorrencias[i][j].indice + 1;

                if (j < ocorrencias[i].size() - 1)
                {
                    cout << ", ";
                }
            }

            cout << endl;
        }

    }
};

void apaga_tudo()
{
    system("cls");
}

void debug(string palavra)
{
    cout << palavra << endl;
    system("pause");
}

string converter_minusculo(string palavra)
{
    int i = 0;

    while(palavra[i] != '\0')
    {
        if(palavra[i] >= 'A' && palavra[i] <= 'Z')
            palavra[i] = palavra[i] + 32;
        i++;
    }

    return palavra;
}

string ver_letras(string palavra)
{
    int tamanho = palavra.size();
    string palavra_modificada;
    bool entrou = false;

    if(palavra == "- ")
        return palavra;

    if(palavra[tamanho-1] >= 33 && palavra[tamanho-1] <= 63)
    {
        palavra_modificada = palavra.substr(0, palavra.size() - 1);
        entrou = true;
    }

    if(entrou)
        return palavra_modificada;

    else
        return palavra;
}

void ler_historia(Lista* lista)
{
    int i = 0, pos_letra = 1;
    string nome_arquivo = " ";
    string nome_arquivo2 = "Historia2.txt";
    string palavra_lida, linha;

    ifstream arquivo2(nome_arquivo2);

    while(nome_arquivo == " ")
    {
        apaga_tudo();

        cout << "Digite o nome do arquivo que deseja acessar: ";
        cin >> nome_arquivo;

        ifstream arquivo(nome_arquivo);

        if(arquivo.is_open())
        {
            while(arquivo >> palavra_lida)
            {
                if(palavra_lida == "- ")
                    break;

                palavra_lida = converter_minusculo(palavra_lida);
                lista->lista_palavras[i].palavra = palavra_lida;
                lista->lista_palavras[i].palavra = ver_letras(lista->lista_palavras[i].palavra);
                lista->lista_palavras[i].posicao_palavra = i;
                lista->lista_palavras[i].posicao_letra = pos_letra;
                lista->lista_palavras[i].numero_letras += palavra_lida.size();
                lista->tamanho++;

                ///soma a quantidade de caracteres mais 1 do espaco
                pos_letra += palavra_lida.size() + 1;

                i++;
            }

            arquivo.close();
        }
        else
        {
            cout << "Nao foi possivel abrir o arquivo de texto 1";
            nome_arquivo = " ";
        }
    }

    if(arquivo2.is_open())
    {
        while(getline(arquivo2, linha))
            lista->paragrafo += linha += '\n';

        arquivo2.close();
    }
    else
    {
        cout << "nao foi possivel abrir o arquivo de texto 2";
    }
}

Lista* gera_lista()
{
    Lista* lista = new Lista;

    if(lista != nullptr)
        lista->tamanho = 0;

    return lista;
}

void mostra_palavras(Lista* lista)
{
    cout << lista->paragrafo << endl;
}

bool verifica_pontuacao(string palavra)
{
    int i = 0;
    bool parar = true;
    while(palavra[i] != '\0')
    {
        if(palavra[i] == 33 || palavra[i] == 46 || palavra[i] == 58 || palavra[i] == 63)
            parar = false;

        i++;
    }

    return parar;
}

void busca_sequencial(Lista* lista)
{
    string palavra, frase[40];

    cout << "Digite a palavra que voce deseja procurar: ";
    cin >> palavra;

    int i, cont_palavras = 0, posicao_palavra[40], posicao_letra[40];

    for(i = 0; i < lista->tamanho; i++)
    {
        if(palavra == lista->lista_palavras[i].palavra)
        {
            posicao_palavra[cont_palavras] = i;
            posicao_letra[cont_palavras] = lista->lista_palavras[i].posicao_letra;

            if(i < 3)
            {
                for(int j = i; j < i + 6; j++)
                    frase[cont_palavras] += lista->lista_palavras[j].palavra += ' ';
            }
            else if(i > 977)
            {
                for(int j = i - 6; j < i; j++)
                    frase[cont_palavras] += lista->lista_palavras[j].palavra += ' ';
            }
            else
            {
                for(int j = i - 3; j < i + 3; j++)
                    frase[cont_palavras] += lista->lista_palavras[j].palavra += ' ';
            }

            cont_palavras++;
        }
    }

    cout << "Posicao da Palavra: " << posicao_palavra[0];
    for(i = 1; i < cont_palavras; i++)
        cout << ", " << posicao_palavra[i];

    cout << endl << "Posicao Arquivo Invertido: " << posicao_letra[0];
    for(i = 1; i < cont_palavras; i++)
        cout << ", " << posicao_letra[i];

    cout << endl << "Frases: " << frase[0] << endl;
    for(i = 1; i < cont_palavras; i++)
        cout << "\t" << frase[i] << endl;

    cout << "Ocorrencias: " << cont_palavras << endl << endl;
}

///implementar nas ferias
void busca_binaria(Lista* lista)
{

}

void busca_arvore_trie(Lista* lista)
{

}

void menu_procura(Lista* lista)
{
    Arquivo_Invertido* invertido;
    string palavra;
    int decisao = 0;

    while(decisao != 4)
    {
        apaga_tudo();

        cout << "1 - Busca Sequencial" << endl;
        cout << "2 - Busca Binaria" << endl;
        cout << "3 - Arvore Trie" << endl;
        cout << "4 - Sair" << endl;

        cout << "Escolha a sua opcao: ";
        cin >> decisao;

        switch(decisao)
        {
        case 1:
            apaga_tudo();
            busca_sequencial(lista);
            cout << endl;
            system("pause");
            apaga_tudo();
            break;

        case 2:
            apaga_tudo();
            busca_binaria(lista);
            cout << endl;
            system("pause");
            apaga_tudo();
            break;

        case 3:
            apaga_tudo();
            busca_arvore_trie(lista);
            cout << endl;
            system("pause");
            apaga_tudo();
            break;

        case 4:
            cout << endl;
            break;

        default:
            apaga_tudo();
            cout << "Valor invalido" << endl <<endl;
            system("pause");
            break;
        }
    }
}

void inverte_arquivo(Lista* lista)
{
    Arquivo_Invertido arquivo_invertido;

    for(int i = 0; i < lista->tamanho; i++)
        arquivo_invertido.adicionarPalavra(lista->lista_palavras[i].palavra, i, lista->lista_palavras[i].posicao_letra);

    int decisao;
    bool letra;

    do
    {
        apaga_tudo();
        cout << "deseja ver o arquivo invertido por letra ou por palavra?" << endl <<
             "1 - Letra" << endl <<
             "2 - Palavra" << endl;
        cin >> decisao;
    }
    while(decisao != 1 && decisao != 2);

    apaga_tudo();

    if(decisao == 1)
        letra = true;
    else
        letra = false;

    arquivo_invertido.exibeArquivoInvertido(letra);
}

void procura_proxima_ocorencia(Lista* lista)
{
    string palavra, frase[40];

    cout << "Digite a palavra que voce deseja procurar: ";
    cin >> palavra;

    int i, cont_palavras = 0, posicao_palavra[40], posicao_letra[40];

    for(i = 0; i < lista->tamanho; i++)
    {
        if(palavra == lista->lista_palavras[i].palavra)
        {
            posicao_palavra[cont_palavras] = i+1;
            posicao_letra[cont_palavras] = lista->lista_palavras[i].posicao_letra;

            if(i < 3)
            {
                for(int j = i; j < i + 6; j++)
                    frase[cont_palavras] += lista->lista_palavras[j].palavra += ' ';
            }
            else if(i > 977)
            {
                for(int j = i - 6; j < i; j++)
                    frase[cont_palavras] += lista->lista_palavras[j].palavra += ' ';
            }
            else
            {
                for(int j = i - 3; j < i + 3; j++)
                    frase[cont_palavras] += lista->lista_palavras[j].palavra += ' ';
            }

            cont_palavras++;
        }
    }

    cout << "Posicao da Palavra: " << posicao_palavra[0];
    for(i = 1; i < cont_palavras; i++)
        cout << ", " << posicao_palavra[i];

    cout << endl << "Posicao Arquivo Invertido: " << posicao_letra[0];
    for(i = 1; i < cont_palavras; i++)
        cout << ", " << posicao_letra[i];

    cout << endl << "Frases: " << frase[0] << endl;
    for(i = 1; i < cont_palavras; i++)
        cout << "\t" << frase[i] << endl;
}

void menu(Lista* lista)
{
    ler_historia(lista);

    int decisao = 0;

    while(decisao != 6)
    {
        apaga_tudo();
        cout << "1 - Ler novo arquivo de texto" << endl;
        cout << "2 - Apresentar arquivo invertido" << endl;
        cout << "3 - Procurar palavra" << endl;
        cout << "4 - Procurar a proxima ocorrencia da palavra" << endl;
        cout << "5 - Imprimir arquivo de texto" << endl;
        cout << "6 - Sair" << endl;

        cout << "digite sua opcao: ";
        cin >> decisao;

        switch(decisao)
        {
        case 1:
            apaga_tudo();
            ler_historia(lista);
            cout << endl;
            system("pause");
            break;

        case 2:
            apaga_tudo();
            inverte_arquivo(lista);
            cout << endl;
            system("pause");
            break;

        case 3:
            apaga_tudo();
            menu_procura(lista);
            cout << endl;
            system("pause");
            break;

        case 4:
            apaga_tudo();
            procura_proxima_ocorencia(lista);
            cout << endl;
            system("pause");
            break;

        case 5:
            apaga_tudo();
            mostra_palavras(lista);
            cout << endl;
            system("pause");
            break;

        case 6:
            break;

        default:
            apaga_tudo();
            cout << "Valor invalido" << endl <<endl;
            system("pause");
            break;
        }
        cout << endl;
    }
}

int main()
{
    Lista* lista = gera_lista();

    menu(lista);

    delete lista;

    return 0;
}
