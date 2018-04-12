#ifndef _LEXEMA_H //Carregar somente uma vez na memória
#define _LEXEMA_H

/*
*---------------------------------------------------------------------
*   INCLUDE FILES
*---------------------------------------------------------------------
*/

#include <string.h>
#include <stdio.h>

/*
*---------------------------------------------------------------------
*   MACROS
*---------------------------------------------------------------------
*/

#define TAM_LIM_INI_LEX 30

/*
*-----------------------------------------------------------------------
*   Data types and global variables
*-----------------------------------------------------------------------
*/

//Tipo Lexema
typedef struct {
    char * lex;
    size_t tamLimite;
    size_t tamAtual;
} tLexema;

tLexema lexema_atual;

/*
*-----------------------------------------------------------------------
*   Signatures
*-----------------------------------------------------------------------
*/

void alocarLexema (void);
void addCharNoLexema (char);
void zerarLexema (void);
void liberarLexema (void);

/*
*-----------------------------------------------------------------------
*   FUNCTIONS
*-----------------------------------------------------------------------
*/

/* Aloca espaço lexema na memória */
void alocarLexema (void)
{
    lexema_atual.tamLimite = TAM_LIM_INI_LEX;
    lexema_atual.tamAtual = 0;
    lexema_atual.lex = (char *) malloc(TAM_LIM_INI_LEX * sizeof(char));
    lexema_atual.lex[0] = '\0';
    if(lexema_atual.lex == NULL)
    {
        printf("Erro ao alocar espaco para o lexema");
        exit(-1);
    }
}

/* Adiciona caractere ao lexema, caso não haja mais espaço na variavel, tenta aloca mais */
void addCharNoLexema (char c)
{
    if(lexema_atual.tamAtual + 1 == lexema_atual.tamLimite)
    {
        lexema_atual.tamLimite *= 2;
        lexema_atual.lex = (char *) realloc(lexema_atual.lex, lexema_atual.tamLimite * sizeof(char));
        if(lexema_atual.lex == NULL)
        {
            printf("Erro ao alocar espaco para o lexema");
            exit(-1);   
        }
    }
    lexema_atual.lex[lexema_atual.tamAtual] = c;
    lexema_atual.lex[lexema_atual.tamAtual + 1] = '\0';
    lexema_atual.tamAtual++;
}

/* Zera valores armazenados no lexema_atual */
void zerarLexema (void)
{
    lexema_atual.lex[0] = '\0';
    lexema_atual.tamAtual = 0;
}

/* Libera espaço alocado para o lexema na memória */
void liberarLexema (void)
{
    free(lexema_atual.lex);
}

#endif