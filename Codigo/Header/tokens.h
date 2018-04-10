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
    int    lin;
    int    col;
    int    hashTabSimb;
} tTokenEncontrado;

//Tipo lista de tokens encontrados
typedef struct
{
    tTokenEncontrado *lista;    
    int tamanhoAtual;
    size_t tamanhoLimite;
} tListaTokenEncontrados;


//Lista de Tokens Encontrados
tListaTokenEncontrados tkEncontrados;

/*
*-----------------------------------------------------------------------
*   Signatures
*-----------------------------------------------------------------------
*/

char * tokenGetText (tToken);
void alocarListaTkEncontrados (void);
void addTkListaEncontrados (tToken, int, int, int);
void liberarListaTkEncontrados (void);

/*
*-----------------------------------------------------------------------
*   Functions
*-----------------------------------------------------------------------
*/

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

/* Aloca lista de tokens encontrados */
void alocarListaTkEncontrados (void) 
{
    tkEncontrados.tamanhoLimite = TAM_LIM_INI_LIST_TK;
    tkEncontrados.tamanhoAtual = 0;
    tkEncontrados.lista = (tTokenEncontrado *) malloc(TAM_LIM_INI_LIST_TK * sizeof(tTokenEncontrado));
    if(tkEncontrados.lista == NULL)
    {
        printf("Erro ao alocar espaco para a lista de tokens encontrados");
        exit(-1);
    }
}

/* Adiciona novo token encontrado na lista de tokens encontrados, caso já esteja cheia, realoca mais espaço */
void addTkListaEncontrados (tToken tk, int lin, int col, int hash)
{
    if(tkEncontrados.tamanhoAtual + 1 == tkEncontrados.tamanhoLimite)
    {
        tkEncontrados.tamanhoLimite *= 2;
        tkEncontrados.lista = (tTokenEncontrado *) realloc(tkEncontrados.lista, tkEncontrados.tamanhoLimite * sizeof(tTokenEncontrado));
        if(tkEncontrados.lista == NULL)
        {
            printf("Erro ao realocar espaco para a lista de tokens encontrados");
            exit(-1);
        }
    }
    tkEncontrados.lista[tkEncontrados.tamanhoAtual].tk = tk;
    tkEncontrados.lista[tkEncontrados.tamanhoAtual].lin = lin;
    tkEncontrados.lista[tkEncontrados.tamanhoAtual].col = col;
    tkEncontrados.lista[tkEncontrados.tamanhoAtual].hashTabSimb = hash;
    tkEncontrados.tamanhoAtual++;
}

/* Libera a lista de tokens encontrados da memória */
void liberarListaTkEncontrados (void)
{
    free(tkEncontrados.lista);
}

#endif