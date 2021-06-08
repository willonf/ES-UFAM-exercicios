#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "stdbool.h"
#include "TorreDeHanoi.h"

int moverDisco(Pino **pinos, int pinoOrigem, int pinoDestino);
void imprimir(Pino **pinos, int numPinos, int numDiscos);
Pino **criarPinos(int n);
void jogar();

int main()
{

    int m, n;
    int p1, p2;
    int pino = 0;

    // Leitura da quantidade n de pinos
    while (true)
    {
        printf("Insira a quantidade de pinos: [3..5] ");
        scanf("%d", &n);
        if (n < 3 || n > 5)
        {
            printf("Entrada invalida\n");
            continue;
        }
        else
        {
            break;
        }
    }

    // Leitura da quantidade m de discos
    while (true)
    {
        printf("Insira a quantidade de discos: [3..5] ");
        scanf("%d", &m);
        if (m < 3 || m > 5)
        {
            printf("Entrada invalida\n");
            continue;
        }
        else
        {
            break;
        }
    }

    // Criação do vetor de pinos
    Pino **vetorPinos = criarPinos(n);

    // n pinos
    // m discos

    // Inserção dos discos nos pinos
    int tam = m;
    Disco **vetorDiscos = (Disco **)malloc(m * sizeof(Disco *));
    for (int i = 0; i < m; i++)
    {
        vetorDiscos[i] = criarDisco(tam);
        push(vetorPinos[0], vetorDiscos[i]);
        tam--;
    }

    for (int i = 1; i < n; i++)
    {
        Disco **vetorDiscos2 = (Disco **)malloc(m * sizeof(Disco *));
        for (int j = 0; j < m; j++)
        {
            vetorDiscos2[j] = criarDisco(0);
            push(vetorPinos[i], vetorDiscos2[j]);
        }
    }
    imprimir(vetorPinos, n, m);

    // Início do jogo (chamada da função Jogar)
    // jogar(vetorPinos, n, m);
}

Pino **criarPinos(int n)
{
    Pino **novoPino = (Pino **)malloc(n * sizeof(Pino *));
    for (int i = 0; i < n; i++)
    {
        novoPino[i] = criarPino();
    }
    return novoPino;
}

int moverDisco(Pino **pinos, int pinoOrigem, int pinoDestino)
{
    //pop do topo origem + push no topo destino
    // Validar quantidade de discos no disco do destino
    // Validar tamanho do disco no topo da origem e tam do disco do destino

    Disco *aux;
    bool condicao1 = pinos[pinoOrigem]->numDiscos > 0;
    bool condicao2 = pinos[pinoDestino]->numDiscos >= 0 && pinos[pinoDestino]->numDiscos < 3;

    if (condicao1 && condicao2)
    {
        aux = pop(pinos[pinoOrigem]);
        push(pinos[pinoDestino], aux);
        return 1;
    }
    return 0;
}

int pegaEspacos(Pino *pino, int numPinos, int numDiscos)
{
    int espacos = 0;

    if (pino->topo)
    {
        for (Disco *aux = pino->topo; aux != NULL; aux = aux->next)
        {
            espacos = aux->tamDisco;
        }
        return espacos;
    }
    else
    {
        return numDiscos;
    }
}

int pegaTamDisco(Pino *pino, int numPinos, int numDiscos)
{
    int tamDisco;

    if (pino->topo)
    {
        for (Disco *aux = pino->topo; aux != NULL; aux = aux->next)
        {
            tamDisco = aux->tamDisco;
        }
        return tamDisco;
    }
    else
    {
        return numDiscos;
    }
}

void imprimir(Pino **pinos, int numPinos, int numDiscos)
{
    char underline = '_';
    char traco = '|';
    char espaco = ' ';
    int pinoAtual = 0;
    for (int i = 0; i < numPinos; i++)
    {
        Disco *aux = pinos[i]->topo;
        int tamDisco = aux->tamDisco;
        for (int j = 0; j < numDiscos; j++)
        {
            printf("Pino %d - Tam disco %d = %d\n", i, j, tamDisco);
        }
         aux = aux->next;
    }
    // for (int i = 0; i < numPinos; i++)
    // {
    //     int espacos = pegaEspacos(pinos[i], numPinos, numDiscos) + 1;
    //     Disco *aux = pinos[i]->topo;
    //     int tamDisco = aux->tamDisco;
    //     for (int j = 0; j < numDiscos; j++)
    //     {
    //         //impressão do disco
    //         for (int j = 0; j < espacos - tamDisco; j++)
    //         {
    //             printf("%c", espaco);
    //         }
    //         for (int j = 0; j < tamDisco; j++)
    //         {
    //             printf("%c", underline);
    //         }
    //         printf("%c", traco);
    //         //impressão do disco
    //         for (int j = 0; j < tamDisco; j++)
    //         {
    //             printf("%c", underline);
    //         }
    //         printf("\n");
    //     }
    //     // Impressão da base
    //     for (int k = 0; k < espacos; k++)
    //     {
    //         printf("%c", underline);
    //     }

    //     printf("%c", traco);
    //     for (int k = 0; k < espacos; k++)
    //     {
    //         printf("%c", underline);
    //     }
    //     printf("\n%*d\n", espacos + 1, i + 1);
    //     printf("\n");
    //     aux = aux->next;
    // }
    // }
}

void jogar(Pino **pinos, int numPinos, int numDiscos)
{
    int pinoOrigem, pinoDestino;
    int jogadas = 0;
    int cond;
    while (true)
    {
        imprimir(pinos, numPinos, numDiscos);

        while (true)
        {
            printf("Insira os pinos de origem e de destino: ");
            scanf("%d%d", &pinoOrigem, &pinoDestino);
            //Problema a partir daqui
            cond = moverDisco(pinos, pinoOrigem - 1, pinoDestino - 1);
            if (cond)
            {
                jogadas++;
                break;
            }
            else
            {
                printf("Movimento invalido\n");
                imprimir(pinos, numPinos, numDiscos);
            }
        }
        printf("\n");
        for (int i = 0; i < numPinos; i++)
        {
            if (pinos[i]->numDiscos == 3)
            {
                printf("PARABENS VOCE CONSEGUIU\n");
                printf("TOTAL DE JOGADAS: %d", jogadas);
                break;
            }
        }
    }
}
