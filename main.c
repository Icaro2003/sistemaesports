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

// Estrura para per�odo
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

/*Estruturas obrigat�rias no trabalho*/
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

// Prot�tipos de fun��es
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

    // Menu e chamadas das fun��es necess�rias no sistema
    int opcao;

    do
    {
        printf("1 - Cadastrar um time\n");
        printf("2 - Alterar informa��es de um time\n");
        printf("3 - Cadastrar um jogador\n");
        printf("4 - Alterar informa��es de um jogador\n");
        printf("5 - Registrar uma partida\n");
        printf("6 - Buscar partidas por time\n");
        printf("7 - Buscar partidas por per�odo\n");
        printf("8 - Listar todos os times\n");
        printf("9 - Listar todos os jogadores\n");
        printf("10 - Calcular m�dia de idade dos jogadores\n");
        printf("11 - Pre�o total do time\n");
        printf("12 - Sair do programa\n");

        printf("\nEscolha uma op��o: ");
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
            printf("Op��o inv�lida!\n");
            break;
        }
    } while (opcao != 12);

    system("pause");
    return 0;
}

// fun��o que permite cadastrar um novo time no sistema
void cadastrarTime()
{
    // limpa a tela
    system("cls");

    // inicia a fun��o rand que cria n�meros aleat�rios
    srand(time(NULL));

    // cria o arquivo_time.txt e define seu modo(w - escrita, a - atualizar)
    FILE *arquivo_time = fopen("arquivo_time.txt", "a");

    // defini��o de uma vari�vel para acessar a estrutura Times
    Times time_esport;

    // verifica��o se o arquivo criado existe ou n�o
    if (arquivo_time != NULL)
    {
        // escolhe o n�mero aleat�rio de 1 a 10000000 para atribuir ao id do time
        time_esport.id_time = rand() % 10000000;

        // informa��es do time solicitadas ao usu�rio
        printf("Nome do time: ");
        fgets(time_esport.nome_time, sizeof(time_esport.nome_time), stdin);

        printf("Pa�s de origem do time: ");
        fgets(time_esport.pais_time, sizeof(time_esport.pais_time), stdin);

        printf("Data de cria��o do time\n");

        printf("Dia: ");
        scanf("%d", &time_esport.data_criacao.dia);

        getchar();

        printf("M�s: ");
        scanf("%d", &time_esport.data_criacao.mes);

        getchar();

        printf("Ano: ");
        scanf("%d", &time_esport.data_criacao.ano);

        getchar();

        printf("N�mero de jogadores: ");
        scanf("%d", &time_esport.num_jogadores);

        // escreve os valores informados pelo usu�rio no arquivo txt
        fprintf(arquivo_time, "ID: %d\n", time_esport.id_time);
        fprintf(arquivo_time, "Nome: %s", time_esport.nome_time);
        fprintf(arquivo_time, "Pa�s de origem: %s", time_esport.pais_time);
        fprintf(arquivo_time, "Data de cria��o: %d / %d / %d\n", time_esport.data_criacao.dia, time_esport.data_criacao.mes, time_esport.data_criacao.ano);
        fprintf(arquivo_time, "N�mero de jogadores: %d\n\n", time_esport.num_jogadores);
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

// fun��o que permite alterar as informa��es de um time existente no sistema
void alterarTime()
{
    // limpa a tela
    system("cls");

    // vari�vel que recebe o arquivo_time.txt no modo de leitura(r)
    FILE *arquivo_time = fopen("arquivo_time.txt", "r");

    // cria��o do arquivo tempor�rio que vai salvar as informa��es para serem alteradas no modo de escrita(w)
    FILE *arquivo_time_temp = fopen("arquivo_time_temp.txt", "w");

    // defini��o de uma vari�vel para acessar a estrutura Times
    Times time_esport;

    // id solicitado ao usu�rio para informar qual time ser� alterado
    int id_time;

    printf("Informe o ID do time: ");
    scanf("%d", &id_time);

    getchar();

    // verifica��o se os arquivos criados existem ou n�o
    if (arquivo_time != NULL && arquivo_time_temp != NULL)
    {
        // vari�vel que confirma se o time existe(0 - n�o foi cadastrado, 1 - foi cadastrado)
        int time_existente = 0;

        // string de conte�do que ser� usada nas verifica��es
        char linha_time[TAMANHO_MAXIMO];

        // vari�vel que marcar� a posi��o do arquivo de texto
        int posicao_arquivo = 0;

        // la�o de repeti��o com a vari�vel linha_time, onde ser� feita a leitura conte�do do arquivo_time, atrav�s da fun��o fgets
        while (fgets(linha_time, sizeof(linha_time), arquivo_time) != NULL)
        {
            // faz a verifica��o do id em compara��o com o informado pelo usu�rio
            if (sscanf(linha_time, "ID: %d", &time_esport.id_time) == 1 && time_esport.id_time == id_time)
            {
                time_existente = 1;

                // novas informa��es do time solicitadas ao usu�rio
                printf("\nNovo nome do time: ");
                fgets(time_esport.nome_time, sizeof(time_esport.nome_time), stdin);

                printf("Novo pa�s de origem do time: ");
                fgets(time_esport.pais_time, sizeof(time_esport.pais_time), stdin);

                printf("Nova data de cria��o do time\n");
                printf("Dia: ");
                scanf("%d", &time_esport.data_criacao.dia);
                getchar();

                printf("M�s: ");
                scanf("%d", &time_esport.data_criacao.mes);
                getchar();

                printf("Ano: ");
                scanf("%d", &time_esport.data_criacao.ano);

                printf("Novo n�mero de jogadores: ");
                scanf("%d", &time_esport.num_jogadores);

                // fun��o retorna para posi��o inicial do arquivo_time.txt
                fseek(arquivo_time, posicao_arquivo, SEEK_SET);

                // escreve os novos valores informados pelo usu�rio no arquivo tempor�rio
                fprintf(arquivo_time_temp, "ID: %d\n", time_esport.id_time);
                fprintf(arquivo_time_temp, "Nome: %s", time_esport.nome_time);
                fprintf(arquivo_time_temp, "Pa�s de origem: %s", time_esport.pais_time);
                fprintf(arquivo_time_temp, "Data de cria��o: %d / %d / %d\n", time_esport.data_criacao.dia, time_esport.data_criacao.mes, time_esport.data_criacao.ano);
                fprintf(arquivo_time_temp, "N�mero de jogadores: %d\n\n", time_esport.num_jogadores);

                // limpa a tela
                system("cls");

                printf("TIME ALTERADO COM SUCESSO\n");
                break;
            }
            else
            {
                fprintf(arquivo_time_temp, "%s", linha_time);
            }
            // a vari�vel recebe a fun��o ftell, que retorna a posi��o que o cursor do arquivo se encontra
            posicao_arquivo = ftell(arquivo_time);
        }

        // fecha os arquivos criados
        fclose(arquivo_time);
        fclose(arquivo_time_temp);

        // verifica��o se o time foi cadastrado
        if (time_existente)
        {
            // se o time foi cadastado remove o arquivo_time.txt j� criado e renomeia o tempor�rio para substitui o original
            remove("arquivo_time.txt");
            rename("arquivo_time_temp.txt", "arquivo_time.txt");
        }
        else
        {
            // se o time n�o tiver sido cadastrado o arquivo tempor�rio j� � removido.
            remove("arquivo_time_temp.txt");
            printf("Time n�o encontrado!\n");
        }
    }
    else
    {
        // mensagem de erro em caso do valor de arquivo_time e arquivo_time_temp receber NULL
        printf("ERRO NA ABERTURA DO ARQUIVO!\n");
    }

    // pausa ao encerrar a fun��o
    system("pause");
}

// fun��o que permite cadastrar um jogador no sistema
void cadastrarJogador()
{
    // limpa a tela
    system("cls");

    // inicia a fun��o rand que cria n�meros aleat�rios
    srand(time(NULL));

    // cria o arquivo_jogador.txt e define seu modo(w - escrita, a - atualizar)
    FILE *arquivo_jogador = fopen("arquivo_jogador.txt", "a");

    // defini��o de uma vari�vel para acessar a estrutura Jogadores
    Jogadores jogador;

    // verifica��o se o arquivo criado existe ou n�o
    if (arquivo_jogador != NULL)
    {
        // escolhe o n�mero aleat�rio de 1 a 10000000 para atribuir ao id do jogador
        jogador.id_jogador = rand() % 10000000;

        // informa��es do jogador solicitadas ao usu�rio
        printf("Nome do jogador: ");
        fgets(jogador.nome_jogador, sizeof(jogador.nome_jogador), stdin);

        printf("Apelido do jogador: ");
        fgets(jogador.apelido, sizeof(jogador.apelido), stdin);

        printf("Pa�s de origem do jogador: ");
        fgets(jogador.pais_jogador, sizeof(jogador.pais_jogador), stdin);

        printf("Idade do jogador: ");
        scanf("%d", &jogador.idade);

        getchar();

        printf("Posi��o do jogador: ");
        fgets(jogador.posicao, sizeof(jogador.posicao), stdin);

        printf("Sal�rio do jogador: ");
        scanf("%f", &jogador.salario);

        getchar();

        // escreve os valores informados pelo usu�rio no arquivo txt
        fprintf(arquivo_jogador, "ID: %d\n", jogador.id_jogador);
        fprintf(arquivo_jogador, "Nome: %s", jogador.nome_jogador);
        fprintf(arquivo_jogador, "Apelido: %s", jogador.apelido);
        fprintf(arquivo_jogador, "Pa�s de origem: %s", jogador.pais_jogador);
        fprintf(arquivo_jogador, "Idade: %d\n", jogador.idade);
        fprintf(arquivo_jogador, "Posi��o de jogo: %s", jogador.posicao);
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

    // pausa ao encerrar a fun��o
    system("pause");
}

// fun��o que permite alterar as informa��es de um jogador existente no sistema
void alterarJogador()
{
    // limpa a tela
    system("cls");

    // vari�vel que recebe o arquivo_jogador.txt no modo de leitura(r)
    FILE *arquivo_jogador = fopen("arquivo_jogador.txt", "r");

    // cria��o do arquivo tempor�rio que vai salvar as informa��es para serem alteradas no modo de escrita(w)
    FILE *arquivo_jogador_temp = fopen("arquivo_jogador_temp.txt", "w");

    // defini��o de uma vari�vel para acessar a estrutura Jogadores
    Jogadores jogador;

    // id solicitado ao usu�rio para informar qual jogador ser� alterado
    int id_jogador;

    printf("Informe o ID do jogador: ");
    scanf("%d", &id_jogador);

    getchar();

    // verifica��o se os arquivos criados existem ou n�o
    if (arquivo_jogador != NULL && arquivo_jogador_temp != NULL)
    {
        // vari�vel que confirma se o jogador existe(0 - n�o foi cadastrado, 1 - foi cadastrado)
        int jogador_existente = 0;

        // string de conte�do que ser� usada nas verifica��es
        char linha_jogador[TAMANHO_MAXIMO];

        // vari�vel que marcar� a posi��o do arquivo de texto
        int posicao_arquivo = 0;

        // la�o de repeti��o com a vari�vel linha_jogador, onde ser� feita a leitura conte�do do arquivo_jogador, atrav�s da fun��o fgets
        while (fgets(linha_jogador, sizeof(linha_jogador), arquivo_jogador) != NULL)
        {
            // faz a verifica��o do id em compara��o com o informado pelo usu�rio
            if (sscanf(linha_jogador, "ID: %d", &jogador.id_jogador) == 1 && jogador.id_jogador == id_jogador)
            {
                jogador_existente = 1;

                // novas informa��es do jogador solicitadas ao usu�rio
                printf("\nNovo nome do jogador: ");
                fgets(jogador.nome_jogador, sizeof(jogador.nome_jogador), stdin);

                printf("Novo apelido do jogador: ");
                fgets(jogador.apelido, sizeof(jogador.apelido), stdin);

                printf("Novo pa�s de origem do jogador: ");
                fgets(jogador.pais_jogador, sizeof(jogador.pais_jogador), stdin);

                printf("Nova idade do jogador: ");
                scanf("%d", &jogador.idade);

                getchar();

                printf("Nova posi��o do jogador: ");
                fgets(jogador.posicao, sizeof(jogador.posicao), stdin);

                printf("Novo sal�rio do jogador: ");
                scanf("%d", &jogador.salario);

                // fun��o retorna para posi��o inicial do arquivo_jogador.txt
                fseek(arquivo_jogador, 0, SEEK_SET);

                // escreve os novos valores informados pelo usu�rio no arquivo tempor�rio
                fprintf(arquivo_jogador_temp, "ID: %d\n", jogador.id_jogador);
                fprintf(arquivo_jogador_temp, "Nome: %s", jogador.nome_jogador);
                fprintf(arquivo_jogador_temp, "Apelido: %s", jogador.apelido);
                fprintf(arquivo_jogador_temp, "Pa�s de origem: %s", jogador.pais_jogador);
                fprintf(arquivo_jogador_temp, "Posi��o: %s\n", jogador.posicao);
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
            // a vari�vel recebe a fun��o ftell, que retorna a posi��o que o cursor do arquivo se encontra
            posicao_arquivo = ftell(arquivo_jogador);
        }

        // fechamento dos arquivos abertos
        fclose(arquivo_jogador);
        fclose(arquivo_jogador_temp);

        // verifica��o se o time foi cadastrado
        if (jogador_existente)
        {
            // se o jogador foi cadastado remove o arquivo_jogador.txt j� criado e renomeia o tempor�rio para substitui o original
            remove("arquivo_jogador.txt");
            rename("arquivo_jogador_temp.txt", "arquivo_jogador.txt");
        }
        else
        {
            // se o jogador n�o tiver sido cadastrado o arquivo tempor�rio j� � removido
            remove("arquivo_jogador_temp.txt");
            printf("Jogador n�o encontrado!\n");
        }
    }
    else
    {
        // mensagem de erro em caso do valor de arquivo_jogador e arquivo_jogador_temp receber NULL
        printf("ERRO NA ABERTURA DO ARQUIVO!\n");
    }

    // pausa ao encerrar a fun��o
    system("pause");
}

// fun��o que permite registrar uma partida no sistema
void registrarPartida()
{
    // limpa a tela
    system("cls");

    // inicia a fun��o rand que cria n�meros aleat�rios
    srand(time(NULL));

    // cria o arquivo_partidas.txt e define seu modo(w - escrita, a - atualizar)
    FILE *arquivo_partidas = fopen("arquivo_partidas.txt", "a");

    // defini��o de uma vari�vel para acessar a estrutura Partidas
    Partidas partida;

    // verifica��o se o arquivo criado existe ou n�o
    if (arquivo_partidas != NULL)
    {
        // escolhe o n�mero aleat�rio de 1 a 10000000 para atribuir ao id da partida
        partida.id_partida = rand() % 10000000;

        // informa��es da partida solicitadas ao usu�rio
        printf("ID do time da casa: ");
        scanf("%d", &partida.id_time_casa);

        // verifica��o com chamada da fun��o verificarExistenciaTime(), para confirmar a exist�ncia do id do time da casa
        if (!verificarExistenciaTime(partida.id_time_casa))
        {
            printf("ID do time da casa n�o encontrado!\n");
            fclose(arquivo_partidas);
            system("pause");
            return;
        }

        printf("ID do time visitante: ");
        scanf("%d", &partida.id_time_visitante);

        // verifica��o com chamada da fun��o verificarExistenciaTime(), para confirmar a exist�ncia do id do time da casa
        if (!verificarExistenciaTime(partida.id_time_visitante))
        {
            printf("ID do time visitante n�o encontrado!\n");
            fclose(arquivo_partidas);
            system("pause");
            return;
        }

        printf("Data da partida\n");
        printf("Dia: ");
        scanf("%d", &partida.data_partida.dia);

        getchar();

        printf("M�s: ");
        scanf("%d", &partida.data_partida.mes);

        getchar();

        printf("Ano: ");
        scanf("%d", &partida.data_partida.ano);

        getchar();

        printf("Hor�rio da partida\n");
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

        // verifica��o com chamada da fun��o verificarExistenciaJogador(), para confirmar a exist�ncia do id do destaque individual da partida
        if (!verificarExistenciaJogador(partida.destaque_individual_partida))
        {
            printf("ID do destaque individual da partida n�o encontrado!\n");
            fclose(arquivo_partidas);
            system("pause");
            return;
        }

        // escreve os valores informados pelo usu�rio no arquivo txt
        fprintf(arquivo_partidas, "ID partida: %d\n", partida.id_partida);
        fprintf(arquivo_partidas, "ID time da casa: %d\n", partida.id_time_casa);
        fprintf(arquivo_partidas, "ID time visitante: %d\n", partida.id_time_visitante);
        fprintf(arquivo_partidas, "Data da partida: %d / %d / %d\n", partida.data_partida.dia, partida.data_partida.mes, partida.data_partida.ano);
        fprintf(arquivo_partidas, "Hor�rio da partida: %d : %d\n", partida.horas.hora, partida.horas.minuto);
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

    // pausa ao encerrar a fun��o
    system("pause");
}

// fun��o que verifica se um determinado ID de time existe no sistema
int verificarExistenciaTime(int id_time)
{
    // vari�vel que recebe o arquivo_time.txt no modo de leitura(r)
    FILE *arquivo_time = fopen("arquivo_time.txt", "r");

    // vari�vel que confirma se o time existe
    int time_existente = 0;

    // verifica��o se o arquivo existe ou n�o
    if (arquivo_time != NULL)
    {
        // string de conte�do que ser� usada nas verifica��es
        char linha_time[TAMANHO_MAXIMO];

        // la�o de repeti��o com a vari�vel linha_time, onde ser� feita a leitura conte�do do arquivo_time, atrav�s da fun��o fgets
        while (fgets(linha_time, sizeof(linha_time), arquivo_time) != NULL)
        {
            // faz a verifica��o do id em compara��o com o informado pelo usu�rio
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
        printf("ERRO AO VERIFICAR EXIST�NCIA DE TIME!");
    }
    // fechamento do arquivo aberto
    fclose(arquivo_time);

    // retorno que confirma se o time existe(0 - n�o foi cadastrado, 1 - foi cadastrado)
    return time_existente;
}

// fun��o que verifica se um determinado ID de jogador existe no sistema
int verificarExistenciaJogador(int id_jogador)
{
    // vari�vel que recebe o arquivo_jogador.txt no modo de leitura(r)
    FILE *arquivo_jogador = fopen("arquivo_jogador.txt", "r");

    // vari�vel que confirma se o jogador existe
    int jogador_existente = 0;

    // verifica��o se o arquivo existe ou n�o
    if (arquivo_jogador != NULL)
    {
        // string de conte�do que ser� usada nas verifica��es
        char linha_jogador[TAMANHO_MAXIMO];

        // la�o de repeti��o com a vari�vel linha_jogador, onde ser� feita a leitura conte�do do arquivo_jogador, atrav�s da fun��o fgets
        while (fgets(linha_jogador, sizeof(linha_jogador), arquivo_jogador) != NULL)
        {
            // faz a verifica��o do id em compara��o com o informado pelo usu�rio
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
        printf("ERRO AO VERIFICAR EXIST�NCIA DE JOGADOR!");
    }
    // fechamento do arquivo aberto
    fclose(arquivo_jogador);

    // retorno que confirma se o jogador existe(0 - n�o foi cadastrado, 1 - foi cadastrado)
    return jogador_existente;
}

// fun��o que permite buscar as partidas de um determinado time
void buscarTime()
{
    // vari�vel que recebe o arquivo_partidas.txt no modo de leitura(r)
    FILE *arquivo_partidas = fopen("arquivo_partidas.txt", "r");

    // defini��o de uma vari�vel para acessar a estrutura Partidas
    Partidas partida;

    // verifica��o se o arquivo existe ou n�o
    if (arquivo_partidas != NULL)
    {
        // limpa a tela
        system("cls");

        // string de conte�do que ser� usada nas verifica��es
        char linha_partida[TAMANHO_MAXIMO];

        // vari�vel que confirma se o time existe(0 - n�o foi cadastrado, 1 - foi cadastrado)
        int time_existente = 0;

        // id de time solicitado ao usu�rio para informar quais partidas ser�o buscadas
        int id_time;

        printf("ID do time a ser buscado: ");
        scanf("%d", &id_time);

        printf("\n");

        // la�o de repeti��o com a vari�vel linha_partida, onde ser� feita a leitura conte�do do arquivo_partida, atrav�s da fun��o fgets
        while (fgets(linha_partida, sizeof(linha_partida), arquivo_partidas) != NULL)
        {
            // leitura de ids do arquivo_partida
            sscanf(linha_partida, "ID partida: %d", &partida.id_partida);
            sscanf(linha_partida, "ID time da casa: %d", &partida.id_time_casa);
            sscanf(linha_partida, "ID time visitante: %d", &partida.id_time_visitante);

            // verifica��o se o id informado pelo usu�rio � igual aos registrados no arquivo_partidas
            if (id_time == partida.id_time_casa || id_time == partida.id_time_visitante)
            {
                // em caso de igualdade, ser�o imprimidas as informa��es das partidas presentes no arquivo_partidas
                printf("%s", linha_partida);

                time_existente = 1;
            }
        }

        // verifica��o caso o time n�o seja encontrado no arquivo, ser� exibida uma mensagem de "partida n�o encontrada"
        if (time_existente == 0)
        {
            printf("Partida n�o encontrada, segundo o id do time informado!\n");
        }
    }
    else
    {
        // mensagem de erro em caso do valor de arquivo_partida receber NULL
        printf("ERRO AO BUSCAR PARTIDAS DE TIME!");
    }

    // fechamento do arquivo aberto
    fclose(arquivo_partidas);

    // pausa ao encerrar a fun��o
    system("pause");
}

// fun��o que permite buscar as partidas que ocorreram dentro de um determinado per�odo
void buscarPeriodo()
{
    // vari�vel que recebe o arquivo_partidas.txt no modo de leitura(r)
    FILE *arquivo_partidas = fopen("arquivo_partidas.txt", "r");

    // defini��o de uma vari�vel para acessar a estrutura Partidas
    Partidas partida;

    // defini��o de uma vari�vel para acessar a estrutura Periodos
    Periodo periodo;

    // verifica��o se o arquivo existe ou n�o
    if (arquivo_partidas != NULL)
    {
        // limpa a tela
        system("cls");

        // string de conte�do que ser� usada nas verifica��es
        char linha_partida[TAMANHO_MAXIMO];

        // vari�vel que confirma se a partida existe(0 - n�o foi registrada, 1 - foi registrada)
        int partida_existente = 0;

        // Per�odo solicitado ao usu�rio(data de in�nicio / data do fim) para verifica��o de partidas que ocorrem dentro desse mesmo per�odo
        printf("Data de in�cio do per�odo\n");
        printf("Dia: ");
        scanf("%d", &periodo.data_comeco.dia);

        getchar();

        printf("M�s: ");
        scanf("%d", &periodo.data_comeco.mes);

        getchar();

        printf("Ano: ");
        scanf("%d", &periodo.data_comeco.ano);

        getchar();

        printf("Data de fim do per�odo\n");
        printf("Dia: ");
        scanf("%d", &periodo.data_encerramento.dia);

        getchar();

        printf("M�s: ");
        scanf("%d", &periodo.data_encerramento.mes);

        getchar();

        printf("Ano: ");
        scanf("%d", &periodo.data_encerramento.ano);

        getchar();

        // Impress�o das datas do per�odo
        printf("\nPartidas no per�odo de %d / %d / %d � %d / %d / %d\n",
               periodo.data_comeco.dia, periodo.data_comeco.mes, periodo.data_comeco.ano,
               periodo.data_encerramento.dia, periodo.data_encerramento.mes, periodo.data_encerramento.ano);

        // la�o de repeti��o com a vari�vel linha_partida, onde ser� feita a leitura conte�do do arquivo_partida, atrav�s da fun��o fgets
        while (fgets(linha_partida, sizeof(linha_partida), arquivo_partidas) != NULL)
        {
            // leitura de data da partida do arquivo_partida
            sscanf(linha_partida, "Data da partida: %d / %d / %d",
                   &partida.data_partida.dia, &partida.data_partida.mes, &partida.data_partida.ano);

            // verifica��o com chamada da fun��o compararDatas(), se a data do in�cio for maior ou igual a 0 e a data do fim do per�odo for menor ou igual em rela��o as datas cadastradas no arquivo_partida
            if (compararDatas(partida.data_partida, periodo.data_comeco) >= 0 &&
                compararDatas(partida.data_partida, periodo.data_encerramento) <= 0)
            {
                // caso a senten�a seja verdadeira, ser�o imprimidas as informa��es das partidas presentes no arquivo_partidas
                printf("%s", linha_partida);
                partida_existente = 1;
            }
        }

        // verifica��o n�o seja encontrada nenhuma partida durante o per�odo informado no arquivo_partidas, ser� exibida uma mensagem de "partida n�o encontrada"
        if (partida_existente == 0)
        {
            printf("Nenhuma partida encontrada no per�odo especificado!\n");
        }
    }
    else
    {
        // mensagem de erro em caso do valor de arquivo_partida receber NULL
        printf("ERRO AO BUSCAR PARTIDAS POR PER�ODO!\n");
    }

    // fechamento do arquivo aberto
    fclose(arquivo_partidas);

    // pausa ao encerramento da fun��o
    system("pause");
}

// fun��o compara duas datas(a 1� presente no arquivo e a 2� informa pelo usu�rio)
int compararDatas(Data data_arquivo, Data data_informada)
{
    // verifica��es comparando as duas datas datas(formatadas em dia, m�s e ano)
    /*
        caso a 1� seja menor que a 2�, ser� retornado -1
        caso a 1� seja maior que a 2�, ser� retornado 1
        caso a 1� seja igual a 2�, ser� retornado 0
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

// fun��o que lista todos os times cadastrados no sistema
void listarTime()
{
    // vari�vel que recebe o arquivo_time.txt no modo de leitura(r)
    FILE *arquivo_time = fopen("arquivo_time.txt", "r");

    // verifica��o se o arquivo existe ou n�o
    if (arquivo_time != NULL)
    {
        // limpa a tela
        system("cls");

        // string de conte�do
        char linha_time[TAMANHO_MAXIMO];

        // la�o de repeti��o com a vari�vel linha_time, onde ser� feita a leitura conte�do do arquivo_time, atrav�s da fun��o fgets
        while (fgets(linha_time, sizeof(linha_time), arquivo_time) != NULL)
        {
            // impress�o de todo o conte�do presente em arquivo_time
            printf("%s", linha_time);
        }
    }
    else
    {
        // mensagem de erro em caso do valor de arquivo_time receber NULL
        printf("N�O EXISTEM TIMES CADASTRADOS!");
    }

    // fechamento de arquivo aberto
    fclose(arquivo_time);

    // pausa ao encerramento da fun��o
    system("pause");
}

// fun��o que lista todos os jogadores cadastrados no sistema
void listarJogadores()
{
    // vari�vel que recebe o arquivo_jogador.txt no modo de leitura(r)
    FILE *arquivo_jogador = fopen("arquivo_jogador.txt", "r");

    // verifica��o se o arquivo existe ou n�o
    if (arquivo_jogador != NULL)
    {
        // limpa a tela
        system("cls");

        // string de conte�do
        char linha_jogador[TAMANHO_MAXIMO];

        // la�o de repeti��o com a vari�vel linha_jogador, onde ser� feita a leitura conte�do do arquivo_jogador, atrav�s da fun��o fgets
        while (fgets(linha_jogador, sizeof(linha_jogador), arquivo_jogador) != NULL)
        {
            // impress�o de todo o conte�do presente em arquivo_jogador
            printf("%s", linha_jogador);
        }
    }
    else
    {
        // mensagem de erro em caso do valor de arquivo_time receber NULL
        printf("N�O EXISTEM JOGADORES CADASTRADOS!");
    }

    // fechamento do arquivo aberto
    fclose(arquivo_jogador);

    // pausa ao encerramento da fun��o
    system("pause");
}

// fun��o que calcula a m�dia de idade dos jogadores cadastrados no sistema.
void mediaIdadeJogadores()
{
    // vari�vel que recebe o arquivo_jogador.txt no modo de leitura(r)
    FILE *arquivo_jogador = fopen("arquivo_jogador.txt", "r");

    // verifica��o se o arquivo existe ou n�o
    if (arquivo_jogador != NULL)
    {
        // limpa a tela
        system("cls");

        // string de conte�do que ser� usada nas verifica��es
        char linha_jogador[TAMANHO_MAXIMO];

        // defini��o das vari�veis de contador, soma e media para c�lculo da m�dia de idade 
        float cont = 0, soma = 0, media = 0;

        // la�o de repeti��o com a vari�vel linha_jogador, onde ser� feita a leitura conte�do do arquivo_jogador, atrav�s da fun��o fgets
        while (fgets(linha_jogador, sizeof(linha_jogador), arquivo_jogador) != NULL)
        {
            // faz a verifica��o da idade presente no arquivo_jogador
            int idade;

            if (sscanf(linha_jogador, "Idade : %d", &idade) == 1)
            {
                // contador acumulando a cada idade presente no arquivo
                cont++;

                // soma das idades presentes no arquivo
                soma += idade;
            }
        }

        // verifica��o do contador de idades, se existem jogadores cadastrados ou n�o
        if (cont > 0)
        {
            // caso tenha uma ou mais idades ser� feita a m�dia da idade dos jogadores
            media = soma / cont;
            printf("M�dia de idade dos jogadores: %.2f\n", media);
        }
        else
        {
            // caso n�o seja contada idade ser� exibida uma mensagem de "n�o foram encontrados jogadores"
            printf("N�o foram encontrados jogadores cadastrados!");
        }
    }
    else
    {
        // mensagem de erro em caso do valor de arquivo_jogador receber NULL
        printf("ERRO AO CALCULAR A M�DIA DOS JOGADORES!");
    }

    // fechamento do arquivo aberto
    fclose(arquivo_jogador);

    // pausa ao encerramento da fun��o
    system("pause");
}

// fun��o que calcula o somat�rio dos sal�rios de todos os jogadores cadastrados no sistema
void salarioJogadores()
{
    // vari�vel que recebe o arquivo_jogador.txt no modo de leitura(r)
    FILE *arquivo_jogador = fopen("arquivo_jogador.txt", "r");

    // verifica��o se o arquivo existe ou n�o
    if (arquivo_jogador != NULL)
    {
        // limpa a tela
        system("cls");

        // string de conte�do que ser� usada nas verifica��es
        char linha_jogador[TAMANHO_MAXIMO];

        // defini��o da vari�vel que ser� usada para soma dos sal�rios 
        float soma = 0;

        // defini��o de uma vari�vel que ser� usada como contador para verfica��o da exist�ncia de jogadores cadastrados
        int cont = 0;

        // la�o de repeti��o com a vari�vel linha_jogador, onde ser� feita a leitura conte�do do arquivo_jogador, atrav�s da fun��o fgets
        while (fgets(linha_jogador, sizeof(linha_jogador), arquivo_jogador) != NULL)
        {
            // faz a verifica��o do sal�rio presente no arquivo_jogador
            float salario;

            if (sscanf(linha_jogador, "Salario: %f", &salario) == 1)
            {
                // contador acumula pelo sal�rio de cada jogador presente no arquivo_jogador
                cont++;

                // soma do sal�rio de cada jogador cadastrado no arquivo_jogador
                soma += salario;
            }
        }

        // verifica��o do contador de sal�rios, se existem jogadores cadastrados ou n�o
        if (cont > 0)
        {
            // caso tenha uma ou mais sal�rios ser� exibida a soma do sal�rio dos jogadores
            printf("A soma de sal�rio dos jogadores: %.2f\n", soma);
        }
        else
        {
            // caso n�o seja contado sal�rio ser� exibida uma mensagem de "n�o foram encontrados jogadores"
            printf("N�o foram encontrados jogadores cadastrados!\n");
        }
    }
    else
    {
        // mensagem de erro em caso do valor de arquivo_jogador receber NULL
        printf("ERRO AO CALCULAR A SOMA DO SAL�RIO DOS JOGADORES!");
    }

    // fechamento do arquivo aberto
    fclose(arquivo_jogador);

    // pausa ao encerrar a fun��o
    system("pause");
}