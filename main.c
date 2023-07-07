#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#define TAMANHO_MAXIMO 100

typedef struct
{
    int dia, mes, ano;
} Data;
typedef struct
{
    int hora, minuto;
} Horario;

typedef struct
{
    int id_time;
    char nome_time[TAMANHO_MAXIMO];
    char pais_time[TAMANHO_MAXIMO];
    Data data_criacao;
    int num_jogadores;
} Times;

typedef struct
{
    int id_jogador;
    char nome_jogador[TAMANHO_MAXIMO];
    char apelido;
    int idade;
    char posicao[TAMANHO_MAXIMO];
    float salario;
} Jogadores;

typedef struct
{
    int id_partida;
    int id_time_casa;
    int id_time_visitante;
    Data data;
    Horario hora;
    int placar_final_time_casa;
    int placar_final_time_visitante;
    char destaque_individual_partida[TAMANHO_MAXIMO];
} Partidas;

void cadastrarTime();
void alterarTime();

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int opcao;

    do
    {
        printf("1 - Cadastrar um time\n");
        printf("2 - Alterar informações de um time\n");
        printf("3 - Exibe informação da função\n");
        printf("3 - Cadastrar um jogador\n");
        printf("4 - Alterar informações de um jogador\n");
        printf("5 - Registrar uma partida\n");
        printf("6 - Buscar partidas por time\n");
        printf("7 - Buscar partidas por período\n");
        printf("8 - Listar todos os times\n");
        printf("9 - Listar todos os jogadores\n");
        printf("10 - Calcular média de idade dos jogadores\n");
        printf("11 - Preço total do time\n");
        printf("12 - Sair do programa\n");

        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);

        getchar();

        switch (opcao)
        {
        case 1:
            cadastrarTime();
            break;
        case 2:
            alterarTime();
            break;
        case 12:
            printf("Saindo do sistema...\n");
            break;
        default:
            printf("Opção inválida!\n");
            break;
        }
    } while (opcao != 12);

    system("pause");
    return 0;
}

void cadastrarTime()
{
    system("cls");
    srand(time(NULL));
    FILE *arquivo_time = fopen("./arquivos/arquivo_time.txt", "a");
    Times time_esport;

    if (arquivo_time != NULL)
    {
        time_esport.id_time = rand() % 10000000;
        fprintf(arquivo_time, "IP: %d\n", time_esport.id_time);

        printf("Informe o nome do time: ");
        fgets(time_esport.nome_time, sizeof(time_esport.nome_time), stdin);
        fprintf(arquivo_time, "Nome: %s", time_esport.nome_time);

        printf("País de origem do time: ");
        fgets(time_esport.pais_time, sizeof(time_esport.pais_time), stdin);
        fprintf(arquivo_time, "País de origem: %s", time_esport.pais_time);

        printf("Data de criação do time\n");

        printf("Dia: ");
        scanf("%d", &time_esport.data_criacao.dia);

        getchar();

        printf("Mês: ");
        scanf("%d", &time_esport.data_criacao.mes);

        getchar();

        printf("Ano: ");
        scanf("%d", &time_esport.data_criacao.ano);

        fprintf(arquivo_time, "Data de criação: %d / %d / %d\n", time_esport.data_criacao.dia, time_esport.data_criacao.mes, time_esport.data_criacao.ano);

        getchar();

        printf("Número de jogadores: ");
        scanf("%d", &time_esport.num_jogadores);
        fprintf(arquivo_time, "Número de jogadores: %d\n", time_esport.num_jogadores);
    }
    else
    {
        printf("ERRO NO CADASTRO DE TIME!\n");
    }

    system("cls");
    printf("TIME CADASTRADO COM SUCESSO\n");

    fclose(arquivo_time);
    free(arquivo_time);

    system("pause");
}

void alterarTime()
{
    system("cls");
    FILE *arquivo_time = fopen("./arquivos/arquivo_time.txt", "r");
    FILE *arquivo_time_temp = fopen("./arquivos/arquivo_time_temp.txt", "w");
    Times time_esport;
    int id_time;

    printf("Informe o ID do time que deseja alterar: ");
    scanf("%d", &id_time);

    getchar();

    if (arquivo_time != NULL && arquivo_time_temp != NULL)
    {
        int time_existente = 0;
        char linha[TAMANHO_MAXIMO];
        int posicao_arquivo = 0;

        while (fgets(linha, sizeof(linha), arquivo_time) != NULL)
        {
            if (sscanf(linha, "IP: %d", &time_esport.id_time) == 1 && time_esport.id_time == id_time)
            {
                time_existente = 1;
                printf("\nInforme o novo nome do time: ");
                fgets(time_esport.nome_time, sizeof(time_esport.nome_time), stdin);

                printf("Informe o novo país de origem do time: ");
                fgets(time_esport.pais_time, sizeof(time_esport.pais_time), stdin);

                printf("Informe a nova data de criação do time\n");
                printf("Dia: ");
                scanf("%d", &time_esport.data_criacao.dia);
                getchar();

                printf("Mês: ");
                scanf("%d", &time_esport.data_criacao.mes);
                getchar();

                printf("Ano: ");
                scanf("%d", &time_esport.data_criacao.ano);

                printf("Informe o novo número de jogadores: ");
                scanf("%d", &time_esport.num_jogadores);

                fseek(arquivo_time, posicao_arquivo, SEEK_SET);

                fprintf(arquivo_time_temp, "IP: %d\n", time_esport.id_time);
                fprintf(arquivo_time_temp, "Nome: %s", time_esport.nome_time);
                fprintf(arquivo_time_temp, "País de origem: %s", time_esport.pais_time);
                fprintf(arquivo_time_temp, "Data de criação: %d / %d / %d\n", time_esport.data_criacao.dia, time_esport.data_criacao.mes, time_esport.data_criacao.ano);
                fprintf(arquivo_time_temp, "Número de jogadores: %d\n", time_esport.num_jogadores);

                printf("TIME ALTERADO COM SUCESSO\n");
                break;
            }
            else
            {
                fprintf(arquivo_time_temp, "%s", linha);
            }

            posicao_arquivo = ftell(arquivo_time);
        }

        fclose(arquivo_time);
        fclose(arquivo_time_temp);
        free(arquivo_time);
        free(arquivo_time_temp);

        if (time_existente)
        {
            remove("./arquivos/arquivo_time.txt");
            rename("./arquivos/arquivo_time_temp.txt", "./arquivos/arquivo_time.txt");
        }
        else
        {
            remove("./arquivos/arquivo_time_temp.txt");
            printf("Time não encontrado!\n");
        }
    }
    else
    {
        printf("ERRO NA ABERTURA DO ARQUIVO!\n");
    }

    system("pause");
}