#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#define TAMANHO_MAXIMO 100

// Estrutura data
typedef struct
{
    int dia, mes, ano;
} Data;

// Estrura para período
typedef struct
{
    Data data_comeco;
    Data data_encerramento;
} Periodo;

// Estruta para horas
typedef struct
{
    int hora, minuto;
} Horario;

/*Estruturas obrigatórias no trabalho*/
// Estrutura de Times
typedef struct
{
    int id_time;
    char nome_time[TAMANHO_MAXIMO];
    char pais_time[TAMANHO_MAXIMO];
    Data data_criacao;
    int num_jogadores;
} Times;

// Estrutura de Jogadores
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

// Estrutura de Partidas
typedef struct
{
    int id_partida;
    int id_time_casa;
    int id_time_visitante;
    Data data_partida;
    Horario horas;
    int placar_final_time_casa;
    int placar_final_time_visitante;
    int destaque_individual_partida;
} Partidas;

// Protótipos de funções
void cadastrarTime();
void alterarTime();
void cadastrarJogador();
void alterarJogador();
void registrarPartida();
int verificarExistenciaTime(int);
int verificarExistenciaJogador(int);
void buscarTime();
void buscarPeriodo();
int compararDatas(Data, Data);
void listarTime();
void listarJogadores();
void mediaIdadeJogadores();
void salarioJogadores();

int main()
{
    // Biblioca locale.h para uso de acentos e caracteres especiais
    setlocale(LC_ALL, "Portuguese");

    // Menu e chamadas das funções necessárias no sistema
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
        case 5:
            registrarPartida();
            break;
        case 6:
            buscarTime();
            break;
        case 7:
            buscarPeriodo();
            break;
        case 8:
            listarTime();
            break;
        case 9:
            listarJogadores();
            break;
        case 10:
            mediaIdadeJogadores();
            break;
        case 11:
            salarioJogadores();
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
    // limpa a tela
    system("cls");
    // inicia a biblioteca rand que cria números aleatórios
    srand(time(NULL));
    // cria o arquivo_time.txt e define seu modo(w - escrita; a - atualizar)
    FILE *arquivo_time = fopen("arquivo_time.txt", "a");
    Times time_esport;

    if (arquivo_time != NULL)
    {
        // escolhe o número aleatório de 1 a 10000000
        time_esport.id_time = rand() % 10000000;

        // informações coletadas do usuário

        printf("Nome do time: ");
        fgets(time_esport.nome_time, sizeof(time_esport.nome_time), stdin);

        printf("País de origem do time: ");
        fgets(time_esport.pais_time, sizeof(time_esport.pais_time), stdin);

        printf("Data de criação do time\n");

        printf("Dia: ");
        scanf("%d", &time_esport.data_criacao.dia);

        getchar();

        printf("Mês: ");
        scanf("%d", &time_esport.data_criacao.mes);

        getchar();

        printf("Ano: ");
        scanf("%d", &time_esport.data_criacao.ano);

        getchar();

        printf("Número de jogadores: ");
        scanf("%d", &time_esport.num_jogadores);

        // Escreve os valores informados pelo usuário no arquivo txt
        fprintf(arquivo_time, "ID: %d\n", time_esport.id_time);
        fprintf(arquivo_time, "Nome: %s", time_esport.nome_time);
        fprintf(arquivo_time, "País de origem: %s", time_esport.pais_time);
        fprintf(arquivo_time, "Data de criação: %d / %d / %d\n", time_esport.data_criacao.dia, time_esport.data_criacao.mes, time_esport.data_criacao.ano);
        fprintf(arquivo_time, "Número de jogadores: %d\n\n", time_esport.num_jogadores);
    }
    else
    {
        printf("ERRO NO CADASTRO DE TIME!\n");
    }

    system("cls");
    printf("TIME CADASTRADO COM SUCESSO\n");

    // fecha o arquivo criado
    fclose(arquivo_time);

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
            if (sscanf(linha, "ID: %d", &time_esport.id_time) == 1 && time_esport.id_time == id_time)
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

                printf("Novo número de jogadores: ");
                scanf("%d", &time_esport.num_jogadores);

                // função retora para posição correta do arquivo_time.txt
                fseek(arquivo_time, posicao_arquivo, SEEK_SET);

                // Escreve os novos valores informados pelo usuário no arquivo temporário
                fprintf(arquivo_time_temp, "ID: %d\n", time_esport.id_time);
                fprintf(arquivo_time_temp, "Nome: %s", time_esport.nome_time);
                fprintf(arquivo_time_temp, "País de origem: %s", time_esport.pais_time);
                fprintf(arquivo_time_temp, "Data de criação: %d / %d / %d\n", time_esport.data_criacao.dia, time_esport.data_criacao.mes, time_esport.data_criacao.ano);
                fprintf(arquivo_time_temp, "Número de jogadores: %d\n\n", time_esport.num_jogadores);

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

        // fecha os arquivos criados
        fclose(arquivo_time);
        fclose(arquivo_time_temp);

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

        printf("Nome do jogador: ");
        fgets(jogador.nome_jogador, sizeof(jogador.nome_jogador), stdin);

        printf("Apelido do jogador: ");
        fgets(jogador.apelido, sizeof(jogador.apelido), stdin);

        printf("País de origem do jogador: ");
        fgets(jogador.pais_jogador, sizeof(jogador.pais_jogador), stdin);

        printf("Idade do jogador: ");
        scanf("%d", &jogador.idade);

        getchar();

        printf("Posição do jogador: ");
        fgets(jogador.posicao, sizeof(jogador.posicao), stdin);

        printf("Salário do jogador: ");
        scanf("%f", &jogador.salario);

        getchar();

        fprintf(arquivo_jogador, "ID: %d\n", jogador.id_jogador);
        fprintf(arquivo_jogador, "Nome: %s", jogador.nome_jogador);
        fprintf(arquivo_jogador, "Apelido: %s", jogador.apelido);
        fprintf(arquivo_jogador, "País de origem: %s", jogador.pais_jogador);
        fprintf(arquivo_jogador, "Idade: %d\n", jogador.idade);
        fprintf(arquivo_jogador, "Posição de jogo: %s", jogador.posicao);
        fprintf(arquivo_jogador, "Salario: %.2f\n\n", jogador.salario);
    }
    else
    {
        printf("ERRO NO CADASTRO DE JOGADOR!\n");
    }

    system("cls");
    printf("JOGADOR CADASTRADO COM SUCESSO\n");

    fclose(arquivo_jogador);

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
            if (sscanf(linha, "ID: %d", &jogador.id_jogador) == 1 && jogador.id_jogador == id_jogador)
            {
                jogador_existente = 1;
                printf("\nNovo nome do jogador: ");
                fgets(jogador.nome_jogador, sizeof(jogador.nome_jogador), stdin);

                printf("Novo apelido do jogador: ");
                fgets(jogador.apelido, sizeof(jogador.apelido), stdin);

                printf("Novo país de origem do jogador: ");
                fgets(jogador.pais_jogador, sizeof(jogador.pais_jogador), stdin);

                printf("Nova idade do jogador: ");
                scanf("%d", &jogador.idade);

                getchar();

                printf("Nova posição do jogador: ");
                fgets(jogador.posicao, sizeof(jogador.posicao), stdin);

                printf("Novo salário do jogador: ");
                scanf("%d", &jogador.salario);

                fseek(arquivo_jogador, 0, SEEK_SET);

                fprintf(arquivo_jogador_temp, "ID: %d\n", jogador.id_jogador);
                fprintf(arquivo_jogador_temp, "Nome: %s", jogador.nome_jogador);
                fprintf(arquivo_jogador_temp, "Apelido: %s", jogador.apelido);
                fprintf(arquivo_jogador_temp, "País de origem: %s", jogador.pais_jogador);
                fprintf(arquivo_jogador_temp, "Posição: %s\n", jogador.posicao);
                fprintf(arquivo_jogador, "Salario: %.2f\n\n", jogador.salario);

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

void registrarPartida()
{
    system("cls");
    srand(time(NULL));

    FILE *arquivo_partidas = fopen("arquivo_partidas.txt", "w");
    Partidas partida;

    if (arquivo_partidas != NULL)
    {
        partida.id_partida = rand() % 10000000;

        printf("ID do time da casa: ");
        scanf("%d", &partida.id_time_casa);

        if (!verificarExistenciaTime(partida.id_time_casa))
        {
            printf("ID do time da casa não encontrado!\n");
            fclose(arquivo_partidas);
            system("pause");
            return;
        }

        printf("ID do time visitante: ");
        scanf("%d", &partida.id_time_visitante);

        if (!verificarExistenciaTime(partida.id_time_visitante))
        {
            printf("ID do time visitante não encontrado!\n");
            fclose(arquivo_partidas);
            system("pause");
            return;
        }

        printf("Data da partida\n");
        printf("Dia: ");
        scanf("%d", &partida.data_partida.dia);

        getchar();

        printf("Mês: ");
        scanf("%d", &partida.data_partida.mes);

        getchar();

        printf("Ano: ");
        scanf("%d", &partida.data_partida.ano);

        getchar();

        printf("Horário da partida\n");
        printf("Horas: ");
        scanf("%d", &partida.horas.hora);

        printf("Minutos: ");
        scanf("%d", &partida.horas.minuto);

        printf("Placar final da partida\n");
        printf("Placar final time da casa: ");
        scanf("%d", &partida.placar_final_time_casa);

        printf("Placar final time visitante: ");
        scanf("%d", &partida.placar_final_time_visitante);

        printf("Destaque individual da partida: ");
        scanf("%d", &partida.destaque_individual_partida);

        if (!verificarExistenciaTime(partida.id_time_visitante))
        {
            printf("ID do destaque individual da partida não encontrado!\n");
            fclose(arquivo_partidas);
            system("pause");
            return;
        }

        fprintf(arquivo_partidas, "ID partida: %d\n", partida.id_partida);
        fprintf(arquivo_partidas, "ID time da casa: %d\n", partida.id_time_casa);
        fprintf(arquivo_partidas, "ID time visitante: %d\n", partida.id_time_visitante);
        fprintf(arquivo_partidas, "Data da partida: %d / %d / %d\n", partida.data_partida.dia, partida.data_partida.mes, partida.data_partida.ano);
        fprintf(arquivo_partidas, "Horário da partida: %d : %d\n", partida.horas.hora, partida.horas.minuto);
        fprintf(arquivo_partidas, "Placar final da partida: %d X %d\n", partida.placar_final_time_casa, partida.placar_final_time_visitante);
        fprintf(arquivo_partidas, "Destaque individual da partida: %d\n\n", partida.destaque_individual_partida);
    }
    else
    {
        printf("ERRO AO REGISTRAR PARTIDA!\n");
    }

    system("cls");
    printf("PARTIDA REGISTRADA COM SUCESSO\n");

    fclose(arquivo_partidas);

    system("pause");
}

int verificarExistenciaTime(int id_time)
{
    FILE *arquivo_time = fopen("arquivo_time.txt", "r");
    int time_existente = 0;

    if (arquivo_time != NULL)
    {
        char linha_time[TAMANHO_MAXIMO];

        while (fgets(linha_time, sizeof(linha_time), arquivo_time) != NULL)
        {
            int id_temp;

            if (sscanf(linha_time, "ID: %d", &id_temp) == 1 && id_temp == id_time)
            {
                time_existente = 1;
            }
        }

        fclose(arquivo_time);
    }

    return time_existente;
}

int verificarExistenciaJogador(int id_jogador)
{
    FILE *arquivo_jogador = fopen("arquivo_jogador.txt", "r");
    int jogador_existente = 0;

    if (arquivo_jogador != NULL)
    {
        char linha_jogador[TAMANHO_MAXIMO];

        while (fgets(linha_jogador, sizeof(linha_jogador), arquivo_jogador) != NULL)
        {
            int id_temp;

            if (sscanf(linha_jogador, "ID: %d", &id_temp) == 1 && id_temp == id_jogador)
            {
                jogador_existente = 1;
            }
        }

        fclose(arquivo_jogador);
    }

    return jogador_existente;
}

void buscarTime()
{
    FILE *arquivo_partidas = fopen("arquivo_partidas.txt", "r");
    Partidas partida;

    if (arquivo_partidas != NULL)
    {
        system("cls");

        char linha_partida[TAMANHO_MAXIMO];
        int time_existente = 0;
        int id_time;

        printf("ID do time a ser buscado: ");
        scanf("%d", &id_time);

        printf("\n");

        while (fgets(linha_partida, sizeof(linha_partida), arquivo_partidas) != NULL)
        {
            sscanf(linha_partida, "ID partida: %d", &partida.id_partida);
            sscanf(linha_partida, "ID time da casa: %d", &partida.id_time_casa);
            sscanf(linha_partida, "ID time visitante: %d", &partida.id_time_visitante);

            if (id_time == partida.id_time_casa || id_time == partida.id_time_visitante)
            {
                printf("%s", linha_partida);

                time_existente = 1;
            }
        }

        if (time_existente == 0)
        {
            printf("Partida não encontrada, segundo o id do time informado!\n");
        }
    }
    else
    {
        printf("ERRO AO BUSCAR PARTIDAS DE TIME!");
    }

    fclose(arquivo_partidas);
    system("pause");
}

void buscarPeriodo()
{
    FILE *arquivo_partidas = fopen("arquivo_partidas.txt", "r");
    Partidas partida;
    Periodo periodo;

    if (arquivo_partidas != NULL)
    {
        system("cls");

        char linha_partida[TAMANHO_MAXIMO];
        int partida_existente = 0;

        printf("Data de início do período\n");
        printf("Dia: ");
        scanf("%d", &periodo.data_comeco.dia);

        getchar();

        printf("Mês: ");
        scanf("%d", &periodo.data_comeco.mes);

        getchar();

        printf("Ano: ");
        scanf("%d", &periodo.data_comeco.ano);

        getchar();

        printf("Data de fim do período\n");
        printf("Dia: ");
        scanf("%d", &periodo.data_encerramento.dia);

        getchar();

        printf("Mês: ");
        scanf("%d", &periodo.data_encerramento.mes);

        getchar();

        printf("Ano: ");
        scanf("%d", &periodo.data_encerramento.ano);

        getchar();

        printf("\nPartidas no período de %d / %d / %d à %d / %d / %d\n",
               periodo.data_comeco.dia, periodo.data_comeco.mes, periodo.data_comeco.ano,
               periodo.data_encerramento.dia, periodo.data_encerramento.mes, periodo.data_encerramento.ano);

        while (fgets(linha_partida, sizeof(linha_partida), arquivo_partidas) != NULL)
        {
            sscanf(linha_partida, "Data da partida: %d / %d / %d",
                   &partida.data_partida.dia, &partida.data_partida.mes, &partida.data_partida.ano);

            if (compararDatas(partida.data_partida, periodo.data_comeco) >= 0 &&
                compararDatas(partida.data_partida, periodo.data_encerramento) <= 0)
            {
                printf("%s", linha_partida);
                partida_existente = 1;
            }
        }

        if (partida_existente == 0)
        {
            printf("Nenhuma partida encontrada no período especificado!\n");
        }
    }
    else
    {
        printf("ERRO AO BUSCAR PARTIDAS POR PERÍODO!\n");
    }

    fclose(arquivo_partidas);
    system("pause");
}

int compararDatas(Data data_arquivo, Data data_informada)
{
    if (data_arquivo.ano < data_informada.ano)
    {
        return -1;
    }
    else if (data_arquivo.ano > data_informada.ano)
    {
        return 1;
    }
    else
    {
        if (data_arquivo.mes < data_informada.mes)
        {
            return -1;
        }
        else if (data_arquivo.mes > data_informada.mes)
        {
            return 1;
        }
        else
        {
            if (data_arquivo.dia < data_informada.dia)
            {
                return -1;
            }
            else if (data_arquivo.dia > data_informada.dia)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
}

void listarTime()
{
    FILE *arquivo_time = fopen("arquivo_time.txt", "r");

    if (arquivo_time != NULL)
    {
        system("cls");
        char linha_time[TAMANHO_MAXIMO];

        while (fgets(linha_time, sizeof(linha_time), arquivo_time) != NULL)
        {
            printf("%s", linha_time);
        }
    }
    else
    {
        printf("NÃO EXISTEM TIMES CADASTRADOS!");
    }

    fclose(arquivo_time);
    system("pause");
}

void listarJogadores()
{
    FILE *arquivo_jogador = fopen("arquivo_jogador.txt", "r");

    if (arquivo_jogador != NULL)
    {
        system("cls");
        char linha_jogador[TAMANHO_MAXIMO];

        while (fgets(linha_jogador, sizeof(linha_jogador), arquivo_jogador) != NULL)
        {
            printf("%s", linha_jogador);
        }
    }
    else
    {
        printf("NÃO EXISTEM JOGADORES CADASTRADOS!");
    }

    fclose(arquivo_jogador);
    system("pause");
}

void mediaIdadeJogadores()
{
    FILE *arquivo_jogador = fopen("arquivo_jogador.txt", "r");

    if (arquivo_jogador != NULL)
    {
        system("cls");
        char linha_jogador[TAMANHO_MAXIMO];
        float cont = 0, soma = 0, media = 0;

        while (fgets(linha_jogador, sizeof(linha_jogador), arquivo_jogador) != NULL)
        {
            int idade;

            if (sscanf(linha_jogador, "Idade : %d", &idade) == 1)
            {
                cont++;
                soma += idade;
            }
        }

        if (cont > 0)
        {
            media = soma / cont;
            printf("Média de idade dos jogadores: %.2f\n", media);
        }
        else
        {
            printf("Não foram encontrados jogadores cadastrados!");
        }
    }
    else
    {
        printf("ERRO AO CALCULAR A MÉDIA DOS JOGADORES!");
    }

    fclose(arquivo_jogador);
    system("pause");
}

void salarioJogadores()
{
    FILE *arquivo_jogador = fopen("arquivo_jogador.txt", "r");
    // Jogadores jogador;

    if (arquivo_jogador != NULL)
    {
        system("cls");
        
        char linha_jogador[TAMANHO_MAXIMO];
        float soma = 0;
        int cont = 0;

        while (fgets(linha_jogador, sizeof(linha_jogador), arquivo_jogador) != NULL)
        {
            float salario;

            if (sscanf(linha_jogador, "Salario: %f", &salario) == 1)
            {
                cont++;
                soma += salario;
            }
        }

        if (cont > 0)
        {
            printf("A soma de salário dos jogadores: %.2f\n", soma);
        }
        else
        {
            printf("Não foram encontrados jogadores cadastrados!\n");
        }
    }
    else
    {
        printf("ERRO AO CALCULAR A MÉDIA DOS JOGADORES!");
    }

    fclose(arquivo_jogador);
    system("pause");
}