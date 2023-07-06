#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_STRING 100

typedef struct
{
    int dia, mes, ano;
} DataCriacao;

typedef struct
{
    int id;
    char nome_time[MAX_STRING];
    char pais_time[MAX_STRING];
    DataCriacao data;
    int num_jogadores;
} Time;

int main()
{
    setlocale(LC_ALL, "Portuguese");

    printf("Olá!");

    system("pause");
    return 0;
}