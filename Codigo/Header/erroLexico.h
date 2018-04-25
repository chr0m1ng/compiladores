#ifndef _ERROLEXICO_H //Carregar somente uma vez na memória
#define _ERROLEXICO_H


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

#define TOTAL_ERROS_LEX 5
#define TAM_LIM_INI_TAB_ERR 30

/*
*-----------------------------------------------------------------------
*   Data types and global variables
*-----------------------------------------------------------------------
*/


//Tipos de Erro
typedef enum {
	ERRO_CHAR_INV = 1,	   // 1
	ERRO_COMEN_BLC_N_FECH, // 2
	ERRO_CAD_N_FECH,	   // 3
	ERRO_DEL_ESP,		   // 4
    ERRO_PT_ISO		       // 5
} tErro;

//Tipo Ocorrencia de Erros
typedef struct {
    tErro err;
    char simb;
    int lin;
    int col;
} tOcorErro;

//Tipo tabela de erros lexicos
typedef struct {
    size_t tamAtual;
    size_t tamLimite;
    tOcorErro *tab;
} tTabErroLexico;

tTabErroLexico tabela_erros_lexicos;

/*
*-----------------------------------------------------------------------
*   Signatures
*-----------------------------------------------------------------------
*/
void alocarTabErrLex (void);
char * erroGetText (tErro);
void addErrNaTab (tErro, char, int, int);
int verificaErroNaLinha(int);
void liberarTabErrLex (void);

/*
*-----------------------------------------------------------------------
*   FUNCTIONS
*-----------------------------------------------------------------------
*/

/* Aloca tabela de erros lexicos */
void alocarTabErrLex (void)
{
    tabela_erros_lexicos.tamLimite = TAM_LIM_INI_TAB_ERR;
    tabela_erros_lexicos.tamAtual = 0;
    tabela_erros_lexicos.tab = (tOcorErro *) malloc(TAM_LIM_INI_TAB_ERR * sizeof(tOcorErro));
    if(tabela_erros_lexicos.tab == NULL)
    {
        printf("Erro ao alocar espaco para a lista de tokens encontrados");
        exit(-1);
    }
}

/* Recebe um erro enum e retorna o texto desse erro */
char * erroGetText (tErro err)
{
    char * errosText[] = {
        "",
        "Caractere Invalido",
        "Comentario de Bloco Não Fechado",
        "Cadeia Não Fechada",
        "Delimitador Esperado",
        "Ponto Isolado"
    };

    return errosText[err];
}

/* Adiciona novo erro encontrado na tabela de erros lexicos, caso já esteja cheia, realoca mais espaço */
void addErrNaTab (tErro err, char simb, int lin, int col)
{
    if(tabela_erros_lexicos.tamAtual + 1 == tabela_erros_lexicos.tamLimite)
    {
        tabela_erros_lexicos.tamLimite *= 2;
        tabela_erros_lexicos.tab = (tOcorErro *) realloc(tabela_erros_lexicos.tab, tabela_erros_lexicos.tamLimite * sizeof(tOcorErro));
        if(tabela_erros_lexicos.tab == NULL)
        {
            printf("Erro ao realocar espaco para a tabela de erros lexicos");
            exit(-1);
        }
    }
    tabela_erros_lexicos.tab[tabela_erros_lexicos.tamAtual].err = err;
    tabela_erros_lexicos.tab[tabela_erros_lexicos.tamAtual].lin = lin;
    tabela_erros_lexicos.tab[tabela_erros_lexicos.tamAtual].col = col;
    tabela_erros_lexicos.tab[tabela_erros_lexicos.tamAtual].simb = simb;
    tabela_erros_lexicos.tamAtual++;
}

/* Libera espaço na memoria reservado para a tabela de erros lexicos */
void liberarTabErrLex (void)
{
    free(tabela_erros_lexicos.tab);
}

/* Verifica se tem erro na linha passada. Caso sim devolve a quantidade, caso não devolve 0 */
int verificaErroNaLinha(int linha)
{
    int qtdeErros = 0;
    int i;
    for(i = 0; i < tabela_erros_lexicos.tamAtual; i++)
    {
        if(tabela_erros_lexicos.tab[i].lin == linha)
            qtdeErros++;
        else if (tabela_erros_lexicos.tab[i].lin > linha)
            return qtdeErros;
    }
    return qtdeErros;
}


void printarErros()
{
    int i;
    printf("ERROS LEXICOS\n");
    for(i = 0; i < tabela_erros_lexicos.tamAtual; i++)
        printf("[%d] tipo = %s char = %c lin = %d col = %d\n", i,  erroGetText(tabela_erros_lexicos.tab[i].err), tabela_erros_lexicos.tab[i].simb, tabela_erros_lexicos.tab[i].lin, tabela_erros_lexicos.tab[i].col);
    printf("\n");
}

#endif