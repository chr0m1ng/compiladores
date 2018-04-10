#ifndef _SIMBOLOS_H //Carregar somente uma vez na memória
#define _SIMBOLOS_H

/*
*---------------------------------------------------------------------
*   INCLUDE FILES
*---------------------------------------------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "tokens.h"

/*
*-----------------------------------------------------------------------
*   Macros
*-----------------------------------------------------------------------
*/

#define TAM_TAB_SIMB 255 

/*
*-----------------------------------------------------------------------
*   Data types and global variables
*-----------------------------------------------------------------------
*/

//Tipo posição no codigo
typedef struct ttPos
{
	int lin;
	int col;
    struct ttPos * prox;
} tPos;

//Tipo simbolo na tabela de simbolos
typedef struct ttSimbolo {
    tToken tk;
    char * lex_char;
    int lex_int;
    float lex_dec;

    tPos * ocor;

    struct ttSimbolo * prox; 
} tSimbolo;

tSimbolo ** tabela_simbolos;

/*
*-----------------------------------------------------------------------
*   SIGNATURES
*-----------------------------------------------------------------------
*/

int hash (char *);
void alocarTabSimb (void);
void alocarOcorNoSimb (tSimbolo *, int, int);
tSimbolo * isSimbNaTab (char *);
void addSimbNaTab (tToken, char *, int, int);
void liberarTabSimb (void);

/*
*-----------------------------------------------------------------------
*   FUNCTIONS
*-----------------------------------------------------------------------
*/

/* Cria hash do lexema para posicionar simbolo na tabela */
int hash (char *lex)
{
    return 0;
}

/* Aloca espaço para a tabela de simbolos e inicializa os ponteiros como NULL */
void alocarTabSimb (void)
{
    int i = 0;
    tabela_simbolos = (tSimbolo **) malloc(TAM_TAB_SIMB * sizeof(tSimbolo *));
    
    if(tabela_simbolos == NULL)
    {
        printf("Erro ao alocar espaco para a tabela de simbolos");
        exit(-1);
    }
    
    for(i = 0; i < TAM_TAB_SIMB; i++)
        tabela_simbolos[i] = NULL;
}

/* Aloca uma nova ocorrencia na lista de ocorrencias do simbolo  */
void alocarOcorNoSimb (tSimbolo *simb, int lin. int col)
{
    tPos *novaPos;
    novaPos = (tPos) malloc(sizeof(tPos));

    novaPos->lin = lin;
    novaPos->col = col;

    novaPos->prox = simb->ocor;
    simb->ocor = novaPos;
}

/* Verifica se lexema já esta instalado na tabela de simbolos. Caso SIM retorna o simbolo, caso NÃO retorna NULL */
tSimbolo * isSimbNaTab (char *lex)
{
    int pos = hash(lex);
    tSimbolo *aux = NULL;
    aux = tabela_simbolos[pos];
    while(aux != NULL)
    {
        if(!strcmp(aux->lex_char, lex))
            return aux;
        aux = aux->prox;
    }
    return NULL;
}

void addSimbNaTab (tToken tk, char *lex, int lin, int col)
{
    tSimbolo * novoSimb;
    int pos = hash(lex);
    novoSimb = isSimbNaTab(lex);
    if(novoSimb != NULL)
    {
        alocarOcorNoSimb(novoSimb, lin, col);
    }
    else
    {
        novoSimb = (tSimbolo) malloc(sizeof(tSimbolo));

        strcpy(novoSimb->lex_char, lex);

        if(tk == TK_INT)
            novoSimb->lex_int = atoi(lex);
        else if(tk == TK_DEC)
            novoSimb->lex_dec = atof(lex);

        alocarOcorNoSimb(novoSimb, lin, col);

        novoSimb->prox = tabela_simbolos[pos];
        tabela_simbolos[pos] = novoSimb;
    }

//FALTA TESTAR TUDO DESTE ARQUIVO

}

#endif
