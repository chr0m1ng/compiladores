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

#define TAM_TAB_SIMB 127 

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
    // tPos * ocorTail;
    struct ttSimbolo * prox; 
} tSimbolo;

tSimbolo ** tabela_simbolos;
int maiorQtdeOcorSimb = 0;

/*
*-----------------------------------------------------------------------
*   SIGNATURES
*-----------------------------------------------------------------------
*/

int hash (char *);
void alocarTabSimb (void);
void alocarOcorNoSimb (tSimbolo *, int, int);
void liberarOcorNoSimb(tSimbolo *);
tSimbolo * isSimbNaTab (char *, int *, int *);
int addSimbNaTab (tToken, char *, int, int);
tSimbolo * getSimbNaTab (int, int);
void liberarTabSimb (void);

/*
*-----------------------------------------------------------------------
*   FUNCTIONS
*-----------------------------------------------------------------------
*/

/* Cria hash com shift e compressão MAD do lexema para posicionar simbolo na tabela */
int hash (char *lex)
{
    int i;
    unsigned int lex_hash = 0;
    size_t lex_size = strlen(lex);

    for(i = 0; i < lex_size; i++)
    {
        lex_hash += lex[i];
        lex_hash <<= 3;
    }

    return ((lex_hash * 3) + 2) % TAM_TAB_SIMB;
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
void alocarOcorNoSimb (tSimbolo *simb, int lin, int col)
{
    tPos *novaPos, *aux;
    int i = 1;
    novaPos = (tPos *) malloc(sizeof(tPos));

    novaPos->lin = lin;
    novaPos->col = col;

    novaPos->prox = NULL;
    if(simb->ocor == NULL)
    {
        simb->ocor = novaPos;
        if(maiorQtdeOcorSimb == 0)
            maiorQtdeOcorSimb = i;
    }
    else
    {
        aux = simb->ocor;
        while(aux->prox != NULL)
        {
            aux = aux->prox;
            i++;
        }
        aux->prox = novaPos;
        i++;
        if(maiorQtdeOcorSimb < i)
            maiorQtdeOcorSimb = i;
    }
}

/* Verifica se lexema já esta instalado na tabela de simbolos. Caso SIM retorna o simbolo e seta variavel 
pos com a localização, caso NÃO retorna o ultimo simbolo da lista, seta pos como -1 e seta pos do ultimo simbolo */
tSimbolo * isSimbNaTab (char *lex, int *pos, int *posUltimoSimbolo)
{   
    *pos = 0;
    *posUltimoSimbolo = 0;
    int posHash = hash(lex);
    tSimbolo *aux = NULL;
    aux = tabela_simbolos[posHash];
    while(aux != NULL)
    {
        if(!strcmp(aux->lex_char, lex))
            return aux;
        if(aux->prox == NULL)
        {
            *posUltimoSimbolo = *pos;
            *pos = -1;
            return aux;
        }
        aux = aux->prox;
        *pos++;
    }
    if(*pos == 0)
        *pos = -1;
    return NULL;
}

/* retorna simbolo da tabela de simbolos dada a posição dele. Caso posição incorreta retorna NULL */
tSimbolo * getSimbNaTab (int posHash, int pos)
{   
    int i;
    tSimbolo *aux = NULL;
    aux = tabela_simbolos[posHash];
    for(i = 0; aux != NULL; i++)
    {
        if(i == pos)
            return aux;
        aux = aux->prox;
    }
    return NULL;
}

/* Instala um simbolo na tabela de simbolos. Caso já exista o simbolo, 
adiciona somente uma nova ocorrencia. caso seja um novo simbolo retorna pos na tabela de simbolo, caso contrario retorna -1 */
int addSimbNaTab (tToken tk, char * lex, int lin, int col)
{
    tSimbolo * novoSimb;
    int posUltimoSimbolo;
    int posHash = hash(lex);
    int pos = 0;
    tSimbolo * ultimoSimbolo = isSimbNaTab(lex, &pos, &posUltimoSimbolo);

    if(pos != -1)
    {
        alocarOcorNoSimb (ultimoSimbolo, lin, col);
        return -1;
    }
    else
    {
        pos = 0;
        novoSimb = (tSimbolo *) malloc(sizeof(tSimbolo));
        novoSimb->lex_char = (char *) malloc(sizeof(char));

        strcpy(novoSimb->lex_char, lex);

        if(tk == TK_INT)
            novoSimb->lex_int = atoi(lex);
        else if(tk == TK_DEC)
            novoSimb->lex_dec = atof(lex);

        alocarOcorNoSimb(novoSimb, lin, col);
        novoSimb->prox = NULL;
        
        // printf("pos ultimo simbolo: %d\n", posUltimoSimbolo);
        
        if(ultimoSimbolo == NULL)
        {
            tabela_simbolos[posHash] = novoSimb;
            return 0;   
        }

        ultimoSimbolo->prox = novoSimb; 
        return ++posUltimoSimbolo;
    }
}

/* Libera espaço alocado para as ocorrencias em um simbolo */
void liberarOcorNoSimb (tSimbolo * simb)
{
    tPos *aux1, *aux2;
    aux1 = simb->ocor;

    while(aux1 != NULL)
    {
        aux2 = aux1;
        aux1 = aux1->prox;
        free(aux2);
    }
}

/* Libera espaço alocado para a tabela de simbolos */
void liberarTabSimb (void)
{
    int i;    
    tSimbolo *aux1, *aux2;

    for(i = 0; i < TAM_TAB_SIMB; i++)
    {
        aux1 = tabela_simbolos[i];
        while(aux1 != NULL)
        {
            liberarOcorNoSimb(aux1);
            aux2 = aux1;
            aux1 = aux1->prox;
            free(aux2);
        }
    }

    free(tabela_simbolos);
}

#endif
