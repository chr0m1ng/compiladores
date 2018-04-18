#ifndef _TOKENS_H //Carregar somente uma vez na memória
#define _TOKENS_H

/*
*---------------------------------------------------------------------
*   INCLUDE FILES
*---------------------------------------------------------------------
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*
*-----------------------------------------------------------------------
*   Macros
*-----------------------------------------------------------------------
*/

#define TOTAL_TOKENS 23
#define TAM_LIM_INI_LIST_TK 50

/*
*-----------------------------------------------------------------------
*   Data types and global variables
*-----------------------------------------------------------------------
*/

//Tipo Tokens
typedef enum 
{ 
    TK_EOF, //0
    TK_IDEN, //1
    TK_INT, //2
    TK_DEC, //3
    TK_CADEIA, //4
    TK_VIRG, //5
    TK_PT_VIRG, //6
    TK_DOIS_PTS, //7
    TK_ABRE_PAR, //8
    TK_FECHA_PAR, //9
    TK_MENOR, //10
    TK_MENOR_IGUAL, //11
    TK_MAIOR, //12
    TK_MAIOR_IGUAL, //13
    TK_DIFERENTE, //14
    TK_IGUAL, //15
    TK_INCR, //16
    TK_DECR, //17
    TK_ATRIB, //18
    TK_MAIS, //19
    TK_MENOS, //20
    TK_VEZES, //21    
    TK_DIVIDIDO, //22
    TK_NAO, //23
    TK_E, //24
    TK_OU, //25
    TK_PROGRAMA, //26
    TK_FIM_PROGRAMA, //27
    TK_INTEIRO, //28
    TK_DECIMAL, //29
    TK_CASO, //30
    TK_ENTAO, //31
    TK_SENAO, //32
    TK_FIM_CASO, //33
    TK_PARA, //34
    TK_DE, //35
    TK_ATE, //36
    TK_PASSO, //37
    TK_FIM_PARA, //38
    TK_ENTRADA, //39
    TK_SAIDA //40
} tToken;

//Tipo token encontrado
typedef struct
{
    tToken tk;
    int lin;
    int col;
    int hashTabSimb;
    int posTabSimb;
} tTokenEncontrado;

//Tipo tabela de tokens encontrados
typedef struct
{
    tTokenEncontrado *tab;    
    int tamAtual;
    size_t tamLimite;
} tTabTokenEncontrados;


//tabela de Tokens Encontrados
tTabTokenEncontrados tabela_tkEncontrados;

/*
*-----------------------------------------------------------------------
*   Signatures
*-----------------------------------------------------------------------
*/

char * tokenGetText (tToken);
void alocarTabelaTkEncontrados (void);
void addTkTabelaEncontrados (tToken, int, int, int, int);
void liberarTabelaTkEncontrados (void);

/*
*-----------------------------------------------------------------------
*   Functions
*-----------------------------------------------------------------------
*/

/* Recebe um token enum e retorna o texto desse token */
char * tokenGetText(tToken tk)
{
    char * tokensText[] = {
        "TK_EOF", //0
        "TK_IDEN", //1
        "TK_INT", //2
        "TK_DEC", //3
        "TK_CADEIA", //4
        "TK_VIRG", //5
        "TK_PT_VIRG", //6
        "TK_DOIS_PTS", //7
        "TK_ABRE_PAR", //8
        "TK_FECHA_PAR", //9
        "TK_MENOR", //10
        "TK_MENOR_IGUAL", //11
        "TK_MAIOR", //12
        "TK_MAIOR_IGUAL", //13
        "TK_DIFERENTE", //14
        "TK_IGUAL", //15
        "TK_INCR", //16
        "TK_DECR", //17
        "TK_ATRIB", //18
        "TK_MAIS", //19
        "TK_MENOS", //20
        "TK_VEZES", //21    
        "TK_DIVIDIDO", //22
        "TK_NAO", //23
        "TK_E", //24
        "TK_OU", //25
        "TK_PROGRAMA", //26
        "TK_FIM_PROGRAMA", //27
        "TK_INTEIRO", //28
        "TK_DECIMAL", //29
        "TK_CASO", //30
        "TK_ENTAO", //31
        "TK_SENAO", //32
        "TK_FIM_CASO", //33
        "TK_PARA", //34
        "TK_DE", //35
        "TK_ATE", //36
        "TK_PASSO", //37
        "TK_FIM_PARA", //38
        "TK_ENTRADA", //39
        "TK_SAIDA" //40
    };
    
    return tokensText[tk];
}

/* Aloca tabela de tokens encontrados */
void alocarTabelaTkEncontrados (void) 
{
    tabela_tkEncontrados.tamLimite = TAM_LIM_INI_LIST_TK;
    tabela_tkEncontrados.tamAtual = 0;
    tabela_tkEncontrados.tab = (tTokenEncontrado *) malloc(TAM_LIM_INI_LIST_TK * sizeof(tTokenEncontrado));
    if(tabela_tkEncontrados.tab == NULL)
    {
        printf("Erro ao alocar espaco para a tabela de tokens encontrados");
        exit(-1);
    }
}

/* Adiciona novo token encontrado na tabela de tokens encontrados, caso já esteja cheia, realoca mais espaço */
void addTkTabelaEncontrados (tToken tk, int lin, int col, int hash, int pos)
{
    if(tabela_tkEncontrados.tamAtual + 1 == tabela_tkEncontrados.tamLimite)
    {
        tabela_tkEncontrados.tamLimite *= 2;
        tabela_tkEncontrados.tab = (tTokenEncontrado *) realloc(tabela_tkEncontrados.tab, tabela_tkEncontrados.tamLimite * sizeof(tTokenEncontrado));
        if(tabela_tkEncontrados.tab == NULL)
        {
            printf("Erro ao realocar espaco para a tabela de tokens encontrados");
            exit(-1);
        }
    }
    tabela_tkEncontrados.tab[tabela_tkEncontrados.tamAtual].tk = tk;
    tabela_tkEncontrados.tab[tabela_tkEncontrados.tamAtual].lin = lin;
    tabela_tkEncontrados.tab[tabela_tkEncontrados.tamAtual].col = col;
    tabela_tkEncontrados.tab[tabela_tkEncontrados.tamAtual].hashTabSimb = hash;
    tabela_tkEncontrados.tab[tabela_tkEncontrados.tamAtual].posTabSimb = pos;
    tabela_tkEncontrados.tamAtual++;
}

/* Libera a tabela de tokens encontrados da memória */
void liberarTabelaTkEncontrados (void)
{
    free(tabela_tkEncontrados.tab);
}

#endif