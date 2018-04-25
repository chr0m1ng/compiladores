#ifndef _RESERVADAS_H //Carregar somente uma vez na memória
#define _RESERVADAS_H

/*
*---------------------------------------------------------------------
*   INCLUDE FILES
*---------------------------------------------------------------------
*/

#include <stdio.h>
#include <string.h>
#include "tokens.h"

/*
*---------------------------------------------------------------------
*   MACROS
*---------------------------------------------------------------------
*/

#define TOTAL_PALAVRAS_RESERVADAS 17

/*
*-----------------------------------------------------------------------
*   Data types and global variables
*-----------------------------------------------------------------------
*/

char * palavras_reservadas[] = 
{
    "NAO", //23
    "E", //24
    "OU", //25
    "PROGRAMA", //26
    "FIM_PROGRAMA", //27
    "INTEIRO", //28
    "DECIMAL", //29
    "CASO", //30
    "ENTAO", //31
    "SENAO", //32
    "FIM_CASO", //33
    "PARA", //34
    "DE", //35
    "ATE", //36
    "PASSO", //37
    "FIM_PARA", //38
    "ENTRADA", //39
    "SAIDA" //40
};

/*
*-----------------------------------------------------------------------
*   Signatures
*-----------------------------------------------------------------------
*/

tToken isPalavraReservada (char *);

/*
*-----------------------------------------------------------------------
*   FUNCTIONS
*-----------------------------------------------------------------------
*/

/* Verifica se um token é uma palavra reservada ou um identificador e retorna o token */
tToken isPalavraReservada (char * lex)
{
    char lexUP[100];
    int i = 0;
    tToken tk;
    while(lex[i]) 
    {
        lexUP[i] = toupper(lex[i]);
        i++;
    }
    lexUP[i] = '\0';

    for(i = 0; i < TOTAL_PALAVRAS_RESERVADAS + 1; i++)
    {
        if(!strcmp(lexUP, palavras_reservadas[i]))
        {
            tk = i + TK_NAO;
            return tk;
        }
    }

    return TK_IDEN;
}

#endif