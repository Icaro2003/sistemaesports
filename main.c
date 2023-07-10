#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>

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

// função que permite cadastrar um novo time no sistema
void cadastrarTime()
{
    // limpa a tela
    system("cls");

    // inicia a função rand que cria números aleatórios
    srand(time(NULL));

    // cria o arquivo_time.txt e define seu modo(w - escrita, a - atualizar)
    FILE *arquivo_time = fopen("arquivo_time.txt", "a");

    // definição de uma variável para acessar a estrutura Times
    Times time_esport;

    // verificação se o arquivo criado existe ou não
    if (arquivo_time != NULL)
    {
        // escolhe o número aleatório de 1 a 10000000 para atribuir ao id do time
        time_esport.id_time = rand() % 10000000;

        // informações do time solicitadas ao usuário
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

        // escreve os valores informados pelo usuário no arquivo txt
        fprintf(arquivo_time, "ID: %d\n", time_esport.id_time);
        fprintf(arquivo_time, "Nome: %s", time_esport.nome_time);
        fprintf(arquivo_time, "País de origem: %s", time_esport.pais_time);
        fprintf(arquivo_time, "Data de criação: %d / %d / %d\n", time_esport.data_criacao.dia, time_esport.data_criacao.mes, time_esport.data_criacao.ano);
        fprintf(arquivo_time, "Número de jogadores: %d\n\n", time_esport.num_jogadores);
    }
    else
    {
        // mensagem de erro em caso do valor de arquivo_time receber NULL
        printf("ERRO NO CADASTRO DE TIME!\n");
    }

    system("cls");
    printf("TIME CADASTRADO COM SUCESSO\n");

    // fecha o arquivo criado
    fclose(arquivo_time);

    system("pause");
}

// função que permite alterar as informações de um time existente no sistema
void alterarTime()
{
    // limpa a tela
    system("cls");

    // variável que recebe o arquivo_time.txt no modo de leitura(r)
    FILE *arquivo_time = fopen("arquivo_time.txt", "r");

    // criação do arquivo temporário que vai salvar as informações para serem alteradas no modo de escrita(w)
    FILE *arquivo_time_temp = fopen("arquivo_time_temp.txt", "w");

    // definição de uma variável para acessar a estrutura Times
    Times time_esport;

    // id solicitado ao usuário para informar qual time será alterado
    int id_time;

    printf("Informe o ID do time: ");
    scanf("%d", &id_time);

    getchar();

    // verificação se os arquivos criados existem ou não
    if (arquivo_time != NULL && arquivo_time_temp != NULL)
    {
        // variável que confirma se o time existe(0 - não foi cadastrado, 1 - foi cadastrado)
        int time_existente = 0;

        // string de conteúdo que será usada nas verificações
        char linha_time[TAMANHO_MAXIMO];

        // variável que marcará a posição do arquivo de texto
        int posicao_arquivo = 0;

        // laço de repetição com a variável linha_time, onde será feita a leitura conteúdo do arquivo_time, através da função fgets
        while (fgets(linha_time, sizeof(linha_time), arquivo_time) != NULL)
        {
            // faz a verificação do id em comparação com o informado pelo usuário
            if (sscanf(linha_time, "ID: %d", &time_esport.id_time) == 1 && time_esport.id_time == id_time)
            {
                time_existente = 1;

                // novas informações do time solicitadas ao usuário
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

                // função retorna para posição inicial do arquivo_time.txt
                fseek(arquivo_time, posicao_arquivo, SEEK_SET);

                // escreve os novos valores informados pelo usuário no arquivo temporário
                fprintf(arquivo_time_temp, "ID: %d\n", time_esport.id_time);
                fprintf(arquivo_time_temp, "Nome: %s", time_esport.nome_time);
                fprintf(arquivo_time_temp, "País de origem: %s", time_esport.pais_time);
                fprintf(arquivo_time_temp, "Data de criação: %d / %d / %d\n", time_esport.data_criacao.dia, time_esport.data_criacao.mes, time_esport.data_criacao.ano);
                fprintf(arquivo_time_temp, "Número de jogadores: %d\n\n", time_esport.num_jogadores);

                // limpa a tela
                system("cls");

                printf("TIME ALTERADO COM SUCESSO\n");
                break;
            }
            else
            {
                fprintf(arquivo_time_temp, "%s", linha_time);
            }
            // a variável recebe a função ftell, que retorna a posição que o cursor do arquivo se encontra
            posicao_arquivo = ftell(arquivo_time);
        }

        // fecha os arquivos criados
        fclose(arquivo_time);
        fclose(arquivo_time_temp);

        // verificação se o time foi cadastrado
        if (time_existente)
        {
            // se o time foi cadastado remove o arquivo_time.txt já criado e renomeia o temporário para substitui o original
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
        // mensagem de erro em caso do valor de arquivo_time e arquivo_time_temp receber NULL
        printf("ERRO NA ABERTURA DO ARQUIVO!\n");
    }

    // pausa ao encerrar a função
    system("pause");
}

// função que permite cadastrar um jogador no sistema
void cadastrarJogador()
{
    // limpa a tela
    system("cls");

    // inicia a função rand que cria números aleatórios
    srand(time(NULL));

    // cria o arquivo_jogador.txt e define seu modo(w - escrita, a - atualizar)
    FILE *arquivo_jogador = fopen("arquivo_jogador.txt", "a");

    // definição de uma variável para acessar a estrutura Jogadores
    Jogadores jogador;

    // verificação se o arquivo criado existe ou não
    if (arquivo_jogador != NULL)
    {
        // escolhe o número aleatório de 1 a 10000000 para atribuir ao id do jogador
        jogador.id_jogador = rand() % 10000000;

        // informações do jogador solicitadas ao usuário
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

        // escreve os valores informados pelo usuário no arquivo txt
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
        // mensagem de erro em caso do valor de arquivo_jogador receber NULL
        printf("ERRO NO CADASTRO DE JOGADOR!\n");
    }
    // limpa a tela
    system("cls");

    printf("JOGADOR CADASTRADO COM SUCESSO\n");

    // fecha o arquivo aberto
    fclose(arquivo_jogador);

    // pausa ao encerrar a função
    system("pause");
}

// função que permite alterar as informações de um jogador existente no sistema
void alterarJogador()
{
    // limpa a tela
    system("cls");

    // variável que recebe o arquivo_jogador.txt no modo de leitura(r)
    FILE *arquivo_jogador = fopen("arquivo_jogador.txt", "r");

    // criação do arquivo temporário que vai salvar as informações para serem alteradas no modo de escrita(w)
    FILE *arquivo_jogador_temp = fopen("arquivo_jogador_temp.txt", "w");

    // definição de uma variável para acessar a estrutura Jogadores
    Jogadores jogador;

    // id solicitado ao usuário para informar qual jogador será alterado
    int id_jogador;

    printf("Informe o ID do jogador: ");
    scanf("%d", &id_jogador);

    getchar();

    // verificação se os arquivos criados existem ou não
    if (arquivo_jogador != NULL && arquivo_jogador_temp != NULL)
    {
        // variável que confirma se o jogador existe(0 - não foi cadastrado, 1 - foi cadastrado)
        int jogador_existente = 0;

        // string de conteúdo que será usada nas verificações
        char linha_jogador[TAMANHO_MAXIMO];

        // variável que marcará a posição do arquivo de texto
        int posicao_arquivo = 0;

        // laço de repetição com a variável linha_jogador, onde será feita a leitura conteúdo do arquivo_jogador, através da função fgets
        while (fgets(linha_jogador, sizeof(linha_jogador), arquivo_jogador) != NULL)
        {
            // faz a verificação do id em comparação com o informado pelo usuário
            if (sscanf(linha_jogador, "ID: %d", &jogador.id_jogador) == 1 && jogador.id_jogador == id_jogador)
            {
                jogador_existente = 1;

                // novas informações do jogador solicitadas ao usuário
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

                // função retorna para posição inicial do arquivo_jogador.txt
                fseek(arquivo_jogador, 0, SEEK_SET);

                // escreve os novos valores informados pelo usuário no arquivo temporário
                fprintf(arquivo_jogador_temp, "ID: %d\n", jogador.id_jogador);
                fprintf(arquivo_jogador_temp, "Nome: %s", jogador.nome_jogador);
                fprintf(arquivo_jogador_temp, "Apelido: %s", jogador.apelido);
                fprintf(arquivo_jogador_temp, "País de origem: %s", jogador.pais_jogador);
                fprintf(arquivo_jogador_temp, "Posição: %s\n", jogador.posicao);
                fprintf(arquivo_jogador, "Salario: %.2f\n\n", jogador.salario);

                // limpa a tela
                system("cls");

                printf("JOGADOR ALTERADO COM SUCESSO\n");
                break;
            }
            else
            {
                fprintf(arquivo_jogador_temp, "%s", linha_jogador);
            }
            // a variável recebe a função ftell, que retorna a posição que o cursor do arquivo se encontra
            posicao_arquivo = ftell(arquivo_jogador);
        }

        // fechamento dos arquivos abertos
        fclose(arquivo_jogador);
        fclose(arquivo_jogador_temp);

        // verificação se o time foi cadastrado
        if (jogador_existente)
        {
            // se o jogador foi cadastado remove o arquivo_jogador.txt já criado e renomeia o temporário para substitui o original
            remove("arquivo_jogador.txt");
            rename("arquivo_jogador_temp.txt", "arquivo_jogador.txt");
        }
        else
        {
            // se o jogador não tiver sido cadastrado o arquivo temporário já é removido
            remove("arquivo_jogador_temp.txt");
            printf("Jogador não encontrado!\n");
        }
    }
    else
    {
        // mensagem de erro em caso do valor de arquivo_jogador e arquivo_jogador_temp receber NULL
        printf("ERRO NA ABERTURA DO ARQUIVO!\n");
    }

    // pausa ao encerrar a função
    system("pause");
}

// função que permite registrar uma partida no sistema
void registrarPartida()
{
    // limpa a tela
    system("cls");

    // inicia a função rand que cria números aleatórios
    srand(time(NULL));

    // cria o arquivo_partidas.txt e define seu modo(w - escrita, a - atualizar)
    FILE *arquivo_partidas = fopen("arquivo_partidas.txt", "a");

    // definição de uma variável para acessar a estrutura Partidas
    Partidas partida;

    // verificação se o arquivo criado existe ou não
    if (arquivo_partidas != NULL)
    {
        // escolhe o número aleatório de 1 a 10000000 para atribuir ao id da partida
        partida.id_partida = rand() % 10000000;

        // informações da partida solicitadas ao usuário
        printf("ID do time da casa: ");
        scanf("%d", &partida.id_time_casa);

        // verificação com chamada da função verificarExistenciaTime(), para confirmar a existência do id do time da casa
        if (!verificarExistenciaTime(partida.id_time_casa))
        {
            printf("ID do time da casa não encontrado!\n");
            fclose(arquivo_partidas);
            system("pause");
            return;
        }

        printf("ID do time visitante: ");
        scanf("%d", &partida.id_time_visitante);

        // verificação com chamada da função verificarExistenciaTime(), para confirmar a existência do id do time da casa
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

        // verificação com chamada da função verificarExistenciaJogador(), para confirmar a existência do id do destaque individual da partida
        if (!verificarExistenciaJogador(partida.destaque_individual_partida))
        {
            printf("ID do destaque individual da partida não encontrado!\n");
            fclose(arquivo_partidas);
            system("pause");
            return;
        }

        // escreve os valores informados pelo usuário no arquivo txt
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
        // mensagem de erro em caso do valor de arquivo_partida receber NULL
        printf("ERRO AO REGISTRAR PARTIDA!\n");
    }

    system("cls");
    printf("PARTIDA REGISTRADA COM SUCESSO\n");

    // fecha o arquivo aberto
    fclose(arquivo_partidas);

    // pausa ao encerrar a função
    system("pause");
}

// função que verifica se um determinado ID de time existe no sistema
int verificarExistenciaTime(int id_time)
{
    // variável que recebe o arquivo_time.txt no modo de leitura(r)
    FILE *arquivo_time = fopen("arquivo_time.txt", "r");

    // variável que confirma se o time existe
    int time_existente = 0;

    // verificação se o arquivo existe ou não
    if (arquivo_time != NULL)
    {
        // string de conteúdo que será usada nas verificações
        char linha_time[TAMANHO_MAXIMO];

        // laço de repetição com a variável linha_time, onde será feita a leitura conteúdo do arquivo_time, através da função fgets
        while (fgets(linha_time, sizeof(linha_time), arquivo_time) != NULL)
        {
            // faz a verificação do id em comparação com o informado pelo usuário
            int id_temp;

            if (sscanf(linha_time, "ID: %d", &id_temp) == 1 && id_temp == id_time)
            {
                time_existente = 1;
            }
        }
    }
    else
    {
        // mensagem de erro em caso do valor de arquivo_time receber NULL
        printf("ERRO AO VERIFICAR EXISTÊNCIA DE TIME!");
    }
    // fechamento do arquivo aberto
    fclose(arquivo_time);

    // retorno que confirma se o time existe(0 - não foi cadastrado, 1 - foi cadastrado)
    return time_existente;
}

// função que verifica se um determinado ID de jogador existe no sistema
int verificarExistenciaJogador(int id_jogador)
{
    // variável que recebe o arquivo_jogador.txt no modo de leitura(r)
    FILE *arquivo_jogador = fopen("arquivo_jogador.txt", "r");

    // variável que confirma se o jogador existe
    int jogador_existente = 0;

    // verificação se o arquivo existe ou não
    if (arquivo_jogador != NULL)
    {
        // string de conteúdo que será usada nas verificações
        char linha_jogador[TAMANHO_MAXIMO];

        // laço de repetição com a variável linha_jogador, onde será feita a leitura conteúdo do arquivo_jogador, através da função fgets
        while (fgets(linha_jogador, sizeof(linha_jogador), arquivo_jogador) != NULL)
        {
            // faz a verificação do id em comparação com o informado pelo usuário
            int id_temp;

            if (sscanf(linha_jogador, "ID: %d", &id_temp) == 1 && id_temp == id_jogador)
            {
                jogador_existente = 1;
            }
        }
    }
    else
    {
        // mensagem de erro em caso do valor de arquivo_jogador receber NULL
        printf("ERRO AO VERIFICAR EXISTÊNCIA DE JOGADOR!");
    }
    // fechamento do arquivo aberto
    fclose(arquivo_jogador);

    // retorno que confirma se o jogador existe(0 - não foi cadastrado, 1 - foi cadastrado)
    return jogador_existente;
}

// função que permite buscar as partidas de um determinado time
void buscarTime()
{
    // variável que recebe o arquivo_partidas.txt no modo de leitura(r)
    FILE *arquivo_partidas = fopen("arquivo_partidas.txt", "r");

    // definição de uma variável para acessar a estrutura Partidas
    Partidas partida;

    // verificação se o arquivo existe ou não
    if (arquivo_partidas != NULL)
    {
        // limpa a tela
        system("cls");

        // string de conteúdo que será usada nas verificações
        char linha_partida[TAMANHO_MAXIMO];

        // variável que confirma se o time existe(0 - não foi cadastrado, 1 - foi cadastrado)
        int time_existente = 0;

        // id de time solicitado ao usuário para informar quais partidas serão buscadas
        int id_time;

        printf("ID do time a ser buscado: ");
        scanf("%d", &id_time);

        printf("\n");

        // laço de repetição com a variável linha_partida, onde será feita a leitura conteúdo do arquivo_partida, através da função fgets
        while (fgets(linha_partida, sizeof(linha_partida), arquivo_partidas) != NULL)
        {
            // leitura de ids do arquivo_partida
            sscanf(linha_partida, "ID partida: %d", &partida.id_partida);
            sscanf(linha_partida, "ID time da casa: %d", &partida.id_time_casa);
            sscanf(linha_partida, "ID time visitante: %d", &partida.id_time_visitante);

            // verificação se o id informado pelo usuário é igual aos registrados no arquivo_partidas
            if (id_time == partida.id_time_casa || id_time == partida.id_time_visitante)
            {
                // em caso de igualdade, serão imprimidas as informações das partidas presentes no arquivo_partidas
                printf("%s", linha_partida);

                time_existente = 1;
            }
        }

        // verificação caso o time não seja encontrado no arquivo, será exibida uma mensagem de "partida não encontrada"
        if (time_existente == 0)
        {
            printf("Partida não encontrada, segundo o id do time informado!\n");
        }
    }
    else
    {
        // mensagem de erro em caso do valor de arquivo_partida receber NULL
        printf("ERRO AO BUSCAR PARTIDAS DE TIME!");
    }

    // fechamento do arquivo aberto
    fclose(arquivo_partidas);

    // pausa ao encerrar a função
    system("pause");
}

// função que permite buscar as partidas que ocorreram dentro de um determinado período
void buscarPeriodo()
{
    // variável que recebe o arquivo_partidas.txt no modo de leitura(r)
    FILE *arquivo_partidas = fopen("arquivo_partidas.txt", "r");

    // definição de uma variável para acessar a estrutura Partidas
    Partidas partida;

    // definição de uma variável para acessar a estrutura Periodos
    Periodo periodo;

    // verificação se o arquivo existe ou não
    if (arquivo_partidas != NULL)
    {
        // limpa a tela
        system("cls");

        // string de conteúdo que será usada nas verificações
        char linha_partida[TAMANHO_MAXIMO];

        // variável que confirma se a partida existe(0 - não foi registrada, 1 - foi registrada)
        int partida_existente = 0;

        // Período solicitado ao usuário(data de inínicio / data do fim) para verificação de partidas que ocorrem dentro desse mesmo período
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

        // Impressão das datas do período
        printf("\nPartidas no período de %d / %d / %d à %d / %d / %d\n",
               periodo.data_comeco.dia, periodo.data_comeco.mes, periodo.data_comeco.ano,
               periodo.data_encerramento.dia, periodo.data_encerramento.mes, periodo.data_encerramento.ano);

        // laço de repetição com a variável linha_partida, onde será feita a leitura conteúdo do arquivo_partida, através da função fgets
        while (fgets(linha_partida, sizeof(linha_partida), arquivo_partidas) != NULL)
        {
            // leitura de data da partida do arquivo_partida
            sscanf(linha_partida, "Data da partida: %d / %d / %d",
                   &partida.data_partida.dia, &partida.data_partida.mes, &partida.data_partida.ano);

            // verificação com chamada da função compararDatas(), se a data do início for maior ou igual a 0 e a data do fim do período for menor ou igual em relação as datas cadastradas no arquivo_partida
            if (compararDatas(partida.data_partida, periodo.data_comeco) >= 0 &&
                compararDatas(partida.data_partida, periodo.data_encerramento) <= 0)
            {
                // caso a sentença seja verdadeira, serão imprimidas as informações das partidas presentes no arquivo_partidas
                printf("%s", linha_partida);
                partida_existente = 1;
            }
        }

        // verificação não seja encontrada nenhuma partida durante o período informado no arquivo_partidas, será exibida uma mensagem de "partida não encontrada"
        if (partida_existente == 0)
        {
            printf("Nenhuma partida encontrada no período especificado!\n");
        }
    }
    else
    {
        // mensagem de erro em caso do valor de arquivo_partida receber NULL
        printf("ERRO AO BUSCAR PARTIDAS POR PERÍODO!\n");
    }

    // fechamento do arquivo aberto
    fclose(arquivo_partidas);

    // pausa ao encerramento da função
    system("pause");
}

// função compara duas datas(a 1ª presente no arquivo e a 2ª informa pelo usuário)
int compararDatas(Data data_arquivo, Data data_informada)
{
    // verificações comparando as duas datas datas(formatadas em dia, mês e ano)
    /*
        caso a 1ª seja menor que a 2ª, será retornado -1
        caso a 1ª seja maior que a 2ª, será retornado 1
        caso a 1ª seja igual a 2ª, será retornado 0
    */

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

// função que lista todos os times cadastrados no sistema
void listarTime()
{
    // variável que recebe o arquivo_time.txt no modo de leitura(r)
    FILE *arquivo_time = fopen("arquivo_time.txt", "r");

    // verificação se o arquivo existe ou não
    if (arquivo_time != NULL)
    {
        // limpa a tela
        system("cls");

        // string de conteúdo
        char linha_time[TAMANHO_MAXIMO];

        // laço de repetição com a variável linha_time, onde será feita a leitura conteúdo do arquivo_time, através da função fgets
        while (fgets(linha_time, sizeof(linha_time), arquivo_time) != NULL)
        {
            // impressão de todo o conteúdo presente em arquivo_time
            printf("%s", linha_time);
        }
    }
    else
    {
        // mensagem de erro em caso do valor de arquivo_time receber NULL
        printf("NÃO EXISTEM TIMES CADASTRADOS!");
    }

    // fechamento de arquivo aberto
    fclose(arquivo_time);

    // pausa ao encerramento da função
    system("pause");
}

// função que lista todos os jogadores cadastrados no sistema
void listarJogadores()
{
    // variável que recebe o arquivo_jogador.txt no modo de leitura(r)
    FILE *arquivo_jogador = fopen("arquivo_jogador.txt", "r");

    // verificação se o arquivo existe ou não
    if (arquivo_jogador != NULL)
    {
        // limpa a tela
        system("cls");

        // string de conteúdo
        char linha_jogador[TAMANHO_MAXIMO];

        // laço de repetição com a variável linha_jogador, onde será feita a leitura conteúdo do arquivo_jogador, através da função fgets
        while (fgets(linha_jogador, sizeof(linha_jogador), arquivo_jogador) != NULL)
        {
            // impressão de todo o conteúdo presente em arquivo_jogador
            printf("%s", linha_jogador);
        }
    }
    else
    {
        // mensagem de erro em caso do valor de arquivo_time receber NULL
        printf("NÃO EXISTEM JOGADORES CADASTRADOS!");
    }

    // fechamento do arquivo aberto
    fclose(arquivo_jogador);

    // pausa ao encerramento da função
    system("pause");
}

// função que calcula a média de idade dos jogadores cadastrados no sistema.
void mediaIdadeJogadores()
{
    // variável que recebe o arquivo_jogador.txt no modo de leitura(r)
    FILE *arquivo_jogador = fopen("arquivo_jogador.txt", "r");

    // verificação se o arquivo existe ou não
    if (arquivo_jogador != NULL)
    {
        // limpa a tela
        system("cls");

        // string de conteúdo que será usada nas verificações
        char linha_jogador[TAMANHO_MAXIMO];

        // definição das variáveis de contador, soma e media para cálculo da média de idade 
        float cont = 0, soma = 0, media = 0;

        // laço de repetição com a variável linha_jogador, onde será feita a leitura conteúdo do arquivo_jogador, através da função fgets
        while (fgets(linha_jogador, sizeof(linha_jogador), arquivo_jogador) != NULL)
        {
            // faz a verificação da idade presente no arquivo_jogador
            int idade;

            if (sscanf(linha_jogador, "Idade : %d", &idade) == 1)
            {
                // contador acumulando a cada idade presente no arquivo
                cont++;

                // soma das idades presentes no arquivo
                soma += idade;
            }
        }

        // verificação do contador de idades, se existem jogadores cadastrados ou não
        if (cont > 0)
        {
            // caso tenha uma ou mais idades será feita a média da idade dos jogadores
            media = soma / cont;
            printf("Média de idade dos jogadores: %.2f\n", media);
        }
        else
        {
            // caso não seja contada idade será exibida uma mensagem de "não foram encontrados jogadores"
            printf("Não foram encontrados jogadores cadastrados!");
        }
    }
    else
    {
        // mensagem de erro em caso do valor de arquivo_jogador receber NULL
        printf("ERRO AO CALCULAR A MÉDIA DOS JOGADORES!");
    }

    // fechamento do arquivo aberto
    fclose(arquivo_jogador);

    // pausa ao encerramento da função
    system("pause");
}

// função que calcula o somatório dos salários de todos os jogadores cadastrados no sistema
void salarioJogadores()
{
    // variável que recebe o arquivo_jogador.txt no modo de leitura(r)
    FILE *arquivo_jogador = fopen("arquivo_jogador.txt", "r");

    // verificação se o arquivo existe ou não
    if (arquivo_jogador != NULL)
    {
        // limpa a tela
        system("cls");

        // string de conteúdo que será usada nas verificações
        char linha_jogador[TAMANHO_MAXIMO];

        // definição da variável que será usada para soma dos salários 
        float soma = 0;

        // definição de uma variável que será usada como contador para verficação da existência de jogadores cadastrados
        int cont = 0;

        // laço de repetição com a variável linha_jogador, onde será feita a leitura conteúdo do arquivo_jogador, através da função fgets
        while (fgets(linha_jogador, sizeof(linha_jogador), arquivo_jogador) != NULL)
        {
            // faz a verificação do salário presente no arquivo_jogador
            float salario;

            if (sscanf(linha_jogador, "Salario: %f", &salario) == 1)
            {
                // contador acumula pelo salário de cada jogador presente no arquivo_jogador
                cont++;

                // soma do salário de cada jogador cadastrado no arquivo_jogador
                soma += salario;
            }
        }

        // verificação do contador de salários, se existem jogadores cadastrados ou não
        if (cont > 0)
        {
            // caso tenha uma ou mais salários será exibida a soma do salário dos jogadores
            printf("A soma de salário dos jogadores: %.2f\n", soma);
        }
        else
        {
            // caso não seja contado salário será exibida uma mensagem de "não foram encontrados jogadores"
            printf("Não foram encontrados jogadores cadastrados!\n");
        }
    }
    else
    {
        // mensagem de erro em caso do valor de arquivo_jogador receber NULL
        printf("ERRO AO CALCULAR A SOMA DO SALÁRIO DOS JOGADORES!");
    }

    // fechamento do arquivo aberto
    fclose(arquivo_jogador);

    // pausa ao encerrar a função
    system("pause");
}