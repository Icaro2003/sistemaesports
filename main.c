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
    char apelido[TAMANHO_MAXIMO];
    char pais_jogador[TAMANHO_MAXIMO];
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
void cadastrarJogador();
void alterarJogador();

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int opcao;

    do
    {
        printf("1 - Cadastrar um time\n");
        printf("2 - Alterar informações de um time\n");
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
        case 3:
            cadastrarJogador();
            break;
        case 4:
            alterarJogador();
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
    // inicia a biblioteca rand que cria números aleatórios
    srand(time(NULL));
    // cria o arquivo_time.txt e define seu modo(w - escrita; a - atualizar)
    FILE *arquivo_time = fopen("arquivo_time.txt", "w");
    Times time_esport;

    if (arquivo_time != NULL)
    {
        time_esport.id_time = rand() % 10000000;                // escolhe o número aleatório de 1 a 10000000
        fprintf(arquivo_time, "IP: %d\n", time_esport.id_time); // escreve no arquivo txt o ID do time

        printf("Nome do time: ");
        fgets(time_esport.nome_time, sizeof(time_esport.nome_time), stdin);
        fprintf(arquivo_time, "Nome: %s", time_esport.nome_time); // escreve no arquivo txt o nome do time

        printf("Pa?s de origem do time: ");
        fgets(time_esport.pais_time, sizeof(time_esport.pais_time), stdin);
        fprintf(arquivo_time, "País de origem: %s", time_esport.pais_time); // escreve no arquivo txt o país do time

        printf("Data de criação do time\n");

        printf("Dia: ");
        scanf("%d", &time_esport.data_criacao.dia);

        getchar();

        printf("Mês: ");
        scanf("%d", &time_esport.data_criacao.mes);

        getchar();

        printf("Ano: ");
        scanf("%d", &time_esport.data_criacao.ano);

        fprintf(arquivo_time, "Data de criação: %d / %d / %d\n", time_esport.data_criacao.dia, time_esport.data_criacao.mes, time_esport.data_criacao.ano); // escreve no arquivo txt a data de criação do time

        getchar();

        printf("Número de jogadores: ");
        scanf("%d", &time_esport.num_jogadores);
        fprintf(arquivo_time, "Número de jogadores: %d\n", time_esport.num_jogadores); // escreve no arquivo txt o número de jogadores
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
    // criação do arquivo_time.txt e modo de leitura(r)
    FILE *arquivo_time = fopen("arquivo_time.txt", "r");
    // criação do arquivo temporário que vai salvar as informações para serem alteradas
    FILE *arquivo_time_temp = fopen("arquivo_time_temp.txt", "w");
    Times time_esport;
    int id_time;

    printf("Informe o ID do time: ");
    scanf("%d", &id_time);

    getchar();

    if (arquivo_time != NULL && arquivo_time_temp != NULL)
    {
        // variável que confirma se o time existe
        int time_existente = 0;
        // string de conteúdo que será usada nas verificações
        char linha[TAMANHO_MAXIMO];
        // variável que marcará a posição do arquivo de texto(início ou fim)
        int posicao_arquivo = 0;

        // laço de repetição com a variável linha(conte), onde será feita a leitura do arquivo_time, através da função fgets
        while (fgets(linha, sizeof(linha), arquivo_time) != NULL)
        {
            // faz a verificação do ip em comparação com o informado pelo usuário
            if (sscanf(linha, "IP: %d", &time_esport.id_time) == 1 && time_esport.id_time == id_time)
            {
                time_existente = 1;
                printf("\nNovo nome do time: ");
                fgets(time_esport.nome_time, sizeof(time_esport.nome_time), stdin);

                printf("Novo país de origem do time: ");
                fgets(time_esport.pais_time, sizeof(time_esport.pais_time), stdin);

                printf("Nova data de criação do time\n");
                printf("Dia: ");
                scanf("%d", &time_esport.data_criacao.dia);
                getchar();

                printf("Mês: ");
                scanf("%d", &time_esport.data_criacao.mes);
                getchar();

                printf("Ano: ");
                scanf("%d", &time_esport.data_criacao.ano);

                printf("Novo n?mero de jogadores: ");
                scanf("%d", &time_esport.num_jogadores);

                // função retora para posição correta do arquivo_time.txt
                fseek(arquivo_time, posicao_arquivo, SEEK_SET);

                // Escreve os novos valores informados pelo usuário no arquivo temporário
                fprintf(arquivo_time_temp, "ID: %d\n", time_esport.id_time);
                fprintf(arquivo_time_temp, "Nome: %s", time_esport.nome_time);
                fprintf(arquivo_time_temp, "País de origem: %s", time_esport.pais_time);
                fprintf(arquivo_time_temp, "Data de criação: %d / %d / %d\n", time_esport.data_criacao.dia, time_esport.data_criacao.mes, time_esport.data_criacao.ano);
                fprintf(arquivo_time_temp, "Número de jogadores: %d\n", time_esport.num_jogadores);

                system("cls");
                printf("TIME ALTERADO COM SUCESSO\n");
                break;
            }
            else
            {
                fprintf(arquivo_time_temp, "%s", linha);
            }
            // A variável recebe a função ftell, que retorna a posição que o arquivo se encontra
            posicao_arquivo = ftell(arquivo_time);
        }

        // fecha os arquivos criados e limpa-os da memória
        fclose(arquivo_time);
        fclose(arquivo_time_temp);
        free(arquivo_time);
        free(arquivo_time_temp);

        // verificação se o time foi cadastrado
        if (time_existente)
        {
            // remove o arquivo_time.txt já criado e renomeia o temporário para substituit o original
            remove("arquivo_time.txt");
            rename("arquivo_time_temp.txt", "arquivo_time.txt");
        }
        else
        {
            // se o time não tiver sido cadastrado o arquivo temporário já é removido.
            remove("arquivo_time_temp.txt");
            printf("Time não encontrado!\n");
        }
    }
    else
    {
        printf("ERRO NA ABERTURA DO ARQUIVO!\n");
    }

    system("pause");
}

void cadastrarJogador()
{
    system("cls");
    srand(time(NULL));
    FILE *arquivo_jogador = fopen("arquivo_jogador.txt", "w");
    Jogadores jogador;

    if (arquivo_jogador != NULL)
    {
        jogador.id_jogador = rand() % 10000000;
        fprintf(arquivo_jogador, "IP: %d\n", jogador.id_jogador);

        printf("Nome do jogador: ");
        fgets(jogador.nome_jogador, sizeof(jogador.nome_jogador), stdin);
        fprintf(arquivo_jogador, "Nome: %s", jogador.nome_jogador);

        printf("Apelido do jogador: ");
        fgets(jogador.apelido, sizeof(jogador.apelido), stdin);
        fprintf(arquivo_jogador, "Apelido: %s", jogador.apelido);

        printf("Pa?s de origem do jogador: ");
        fgets(jogador.pais_jogador, sizeof(jogador.pais_jogador), stdin);
        fprintf(arquivo_jogador, "País de origem: %s", jogador.pais_jogador);

        printf("Idade do jogador: ");
        scanf("%d", &jogador.idade);
        fprintf(arquivo_jogador, "Idade: %d\n", jogador.idade);

        getchar();

        printf("Posição do jogador: ");
        fgets(jogador.posicao, sizeof(jogador.posicao), stdin);
        fprintf(arquivo_jogador, "Posição de jogo: %s", jogador.posicao);
    }
    else
    {
        printf("ERRO NO CADASTRO DE JOGADOR!\n");
    }

    system("cls");
    printf("JOGADOR CADASTRADO COM SUCESSO\n");

    fclose(arquivo_jogador);
    free(arquivo_jogador);

    system("pause");
}

void alterarJogador()
{
    system("cls");
    FILE *arquivo_jogador = fopen("arquivo_jogador.txt", "r");
    FILE *arquivo_jogador_temp = fopen("arquivo_jogador_temp.txt", "w");
    Jogadores jogador;
    int id_jogador;

    printf("Informe o ID do jogador: ");
    scanf("%d", &id_jogador);

    getchar();

    if (arquivo_jogador != NULL && arquivo_jogador_temp != NULL)
    {
        int jogador_existente = 0;
        char linha[TAMANHO_MAXIMO];
        int posicao_arquivo = 0;

        while (fgets(linha, sizeof(linha), arquivo_jogador) != NULL)
        {
            if (sscanf(linha, "IP: %d", &jogador.id_jogador) == 1 && jogador.id_jogador == id_jogador)
            {
                jogador_existente = 1;
                printf("\nNovo nome do jogador: ");
                fgets(jogador.nome_jogador, sizeof(jogador.nome_jogador), stdin);

                printf("Novo apelido do jogador: ");
                fgets(jogador.apelido, sizeof(jogador.apelido), stdin);

                printf("Novo país de origem do time: ");
                fgets(jogador.pais_jogador, sizeof(jogador.pais_jogador), stdin);

                printf("Nova idade do jogador: ");
                scanf("%d", &jogador.idade);

                getchar();

                printf("Nova posição do jogador: ");
                fgets(jogador.posicao, sizeof(jogador.posicao), stdin);

                fseek(arquivo_jogador, posicao_arquivo, SEEK_SET);

                fprintf(arquivo_jogador_temp, "ID: %d\n", jogador.id_jogador);
                fprintf(arquivo_jogador_temp, "Nome: %s", jogador.nome_jogador);
                fprintf(arquivo_jogador_temp, "Apelido: %s\n", jogador.apelido);
                fprintf(arquivo_jogador_temp, "País de origem: %s", jogador.pais_jogador);
                fprintf(arquivo_jogador_temp, "Posição: %s", jogador.posicao);

                system("cls");
                printf("JOGADOR ALTERADO COM SUCESSO\n");
                break;
            }
            else
            {
                fprintf(arquivo_jogador_temp, "%s", linha);
            }

            posicao_arquivo = ftell(arquivo_jogador);
        }

        fclose(arquivo_jogador);
        fclose(arquivo_jogador_temp);
        free(arquivo_jogador);
        free(arquivo_jogador_temp);

        if (jogador_existente)
        {
            remove("arquivo_jogador.txt");
            rename("arquivo_jogador_temp.txt", "arquivo_jogador.txt");
        }
        else
        {
            remove("arquivo_jogador_temp.txt");
            printf("Jogador não encontrado!\n");
        }
    }
    else
    {
        printf("ERRO NA ABERTURA DO ARQUIVO!\n");
    }

    system("pause");
}