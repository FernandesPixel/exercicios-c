#include <stdio.h>
#include <stdlib.h>

char tabuleiro[3][3];
char jog1;
char jog2;
char sinalX = 'X';
char sinalO = 'O';
char sinalVazio = '#';




int jogada_usuario(int lin, int col, char jog)
{
    if(lin>3 || col>3)
    {
        //jogada inválida
        return 1;
    }else if(tabuleiro[lin][col]==sinalVazio){
        tabuleiro[lin][col]=jog;
        return 0;
    }else{
        //posicao ocupada
        return 2;
    }
}


//precisa passar o sinal? A função defineSinalJogador já define um sinal para o computador
void jogada_computador(char jog, int nivel)
{
    switch(nivel)
    {
    case 0:
        printf("Nivel basico");
        //jogada_computador_basic();
        break;
    case 1:
        printf("Nivel intermediario");
        //jogada_computador_interm();
        break;
    case 2:
        printf("Nivel avançado");
        //jogada_computador_avanc();
        break;
    default:
        printf("Jogada inválida");
    }
}

int menu()
{
    int opc;
    printf("--- JOGO DA VELHA --- \n");
    printf("1 - Player X Maquina \n");
    printf("2 - Player X Player \n");
    scanf("%d",&opc);

    //fazer loop para verifica opc
    while(opc!=1 || opc!=2)
    {
        switch(opc)
        {
        case 1:
            return 1;
            break;
        case 2:
            return 2;
            break;
        default:
            printf("Jogada inválida. Escolha [1] ou [2]");
        }
    }
    return 1;
}

void escolha_simb(char *jog1, char *jog2)
{
    *jog1 = sinalX;
    *jog2 = sinalO;
}


int verifica_sinal(char jog)
{
    if(jog == 'O' || jog == 'X')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


void inicializa_velha()
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            tabuleiro[i][j] = sinalVazio;
        }
    }
}

int verifica_ganhador(char jog)
{
    //verifica as linhas XXX || OOO
    for(int i=0; i<3; i++)
    {
        if(tabuleiro[i][0] == jog && tabuleiro[i][1] == jog && tabuleiro[i][2] == jog)
        {
            return 1;
        }
    }

    //verifica as colunas
    for(int i=0; i<3; i++)
    {
        if(tabuleiro[0][i] == jog && tabuleiro[1][i] == jog && tabuleiro[2][i] == jog)
        {
            return 1;
        }
    }

    //verifica as diagonais
    if(tabuleiro[0][0] == jog && tabuleiro[1][1] ==jog && tabuleiro[2][2] ==jog)
    {
        return 1;
    }
    else if(tabuleiro[0][2] == jog && tabuleiro[1][1]==jog && tabuleiro[2][0]==jog)
    {
        return 1;
    }
    return 0;
}

void imprime_velha()
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            printf("%c",tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void main()
{
    inicializa_velha();
    imprime_velha();

    //mostra menu
    int tipoJogo =  menu();

    //Player X Maquina
    if(tipoJogo == 1)
    {
        //define nivel de dificuldade
        int nivel=0;
        while(!(nivel==1 || nivel==2 || nivel==3))
        {
            printf("-- Escolha o nível --\n");
            printf("1 - Basico\n");
            printf("2 - Intermediario\n");
            printf("3 - Avancado\n");
            scanf(" %d",&nivel);
        }


        //fazer a parte de escolha e verificaçao de sinal
        int sinal_valido = 0;
        while(sinal_valido!=1)
        {
            char sinal;
            printf("Escolha seu sinal [%c] ou [%c] \n",sinalX,sinalO);
            scanf(" %c",&sinal);

            //verificando sinal
            sinal = toupper(sinal);
            sinal_valido = verifica_sinal(sinal);

            if(sinal_valido!=1)
            {
                printf("Sinal inválido.\n");
            }
            else
            {
                //define quem é X e O
                if(sinal==sinalX)  //jog1 = X
                {
                    escolha_simb(&jog1,&jog2);
                }
                else   //jog1 = O
                {
                    escolha_simb(&jog2,&jog1);
                }
            }
        }
        printf("Jogador 1: %c \n",jog1);
        printf("Jogador 2: %c \n",jog2);


    }
    //Player X Player
    else
    {
        //fazer a parte de escolha e verificaçao de sinal
        int sinal_valido = 0;
        while(sinal_valido!=1)
        {
            char sinal;
            printf("Escolha seu sinal [%c] ou [%c] \n",sinalX,sinalO);
            scanf(" %c",&sinal);

            //verificando sinal
            sinal = toupper(sinal);
            sinal_valido = verifica_sinal(sinal);

            if(sinal_valido!=1)
            {
                printf("Sinal inválido.\n");
            }
            else
            {
                //define quem é X e O
                if(sinal==sinalX)  //jog1 = X
                {
                    escolha_simb(&jog1,&jog2);
                }
                else   //jog1 = O
                {
                    escolha_simb(&jog2,&jog1);
                }
            }
        }
        printf("Jogador 1: %c \n",jog1);
        printf("Jogador 2: %c \n",jog2);

        //Jogadas
        int turno = 1;
        char jog;
        imprime_velha();
        while(verifica_ganhador(jog)!=1)
        {
            //verifica a vez dos jogadores
            if(turno%2 == 0)
            {
                jog=jog2;
            }
            else
            {
                jog=jog1;
            }

            printf("-- Vez do Jogador %c --\n",jog);
            int jogadaValida = -1;
            while(jogadaValida!=0)
            {
                printf("Digite a linha e a coluna:\n");
                int lin, col;
                scanf(" %d %d",&lin,&col);
                printf("Lin: %d, Col: %d, Jog: %c \n",lin,col,jog);
                jogadaValida=jogada_usuario(lin,col,jog);
                if(jogadaValida==1){
                    printf("Jogada invalida\n");
                }else if(jogadaValida==2){
                    printf("Posica ocupada.\n");
                }
            }
            turno++;
            imprime_velha();
        }
        printf("--- JOGADOR %c GANHOU ---\n",jog);
    }




}
