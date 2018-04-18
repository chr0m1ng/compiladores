#ifndef _SAIDAS_H //Carregar somente uma vez na memória
#define _SAIDAS_H

/*
*---------------------------------------------------------------------
*   INCLUDE FILES
*---------------------------------------------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "tokens.h"
#include "simbolos.h"
#include "erroLexico.h"

/*
*-----------------------------------------------------------------------
*   Signatures
*-----------------------------------------------------------------------
*/

void salvarArquivoTks (char *, int, int);
void salvarArquivoTabSimb (char *, int);

/*
*-----------------------------------------------------------------------
*   FUNCTIONS
*-----------------------------------------------------------------------
*/

void salvarArquivoTks (char *nomeArq, int tamMaiorLex, int totalErros)
{
    int i;
    int linhaAtual = -1;
    tSimbolo *simbAtual = NULL;
    char *nomeArqTk = (char *) malloc((strlen(nomeArq) + 5) * sizeof(char));
    if(nomeArqTk == NULL)
    {
        printf("Erro ao salvar arquivo de tokens\n");
        exit(-1);
    }
    int subTotalTkOcor[41] = {0};
    int totalTkOcor = 0;

    strcpy(nomeArqTk, nomeArq);
    strcat(nomeArqTk, ".tok");

    FILE *arq = fopen(nomeArqTk, "w");
    if(arq == NULL)
    {
        printf("Erro ao salvar arquivo de tokens\n");
        exit(-1);
    }
    
    fprintf(arq, "LISTA DE TOKENS RECONHECIDOS EM \"%s\"\n\n", nomeArqTk);
    fprintf(arq, "+-----+-----+-----+------------------+");
    for(i = 0; i < tamMaiorLex + 2; i++)
        fprintf(arq, "-");
    fprintf(arq, "+----------------+\n");

    fprintf(arq, "| LIN | COL | COD | %-16s | %-*s |  POS TAB SIMB  |\n", "TOKEN", tamMaiorLex, "LEXEMA");
    fprintf(arq, "+-----+-----+-----+------------------+");
    for(i = 0; i < tamMaiorLex + 2; i++)
        fprintf(arq, "-");
    fprintf(arq, "+----------------+\n");
    for(i = 0; i < tabela_tkEncontrados.tamAtual; i++)
    {
        
        subTotalTkOcor[tabela_tkEncontrados.tab[i].tk]++;

        if(tabela_tkEncontrados.tab[i].lin == linhaAtual)
            fprintf(arq,"|     |");
        else
        {
            fprintf(arq,"| %3d |", tabela_tkEncontrados.tab[i].lin);
            linhaAtual = tabela_tkEncontrados.tab[i].lin;
        }
        fprintf(arq," %3d | %3d | %-16s ", tabela_tkEncontrados.tab[i].col, tabela_tkEncontrados.tab[i].tk, tokenGetText(tabela_tkEncontrados.tab[i].tk));
        if(tabela_tkEncontrados.tab[i].hashTabSimb == -1)
            fprintf(arq, "| %-*s |                |\n", tamMaiorLex, " ");
        else
        {
            simbAtual = getSimbNaTab(tabela_tkEncontrados.tab[i].hashTabSimb, tabela_tkEncontrados.tab[i].posTabSimb);

            fprintf(arq, "| %-*s |      %4d      |\n", tamMaiorLex, simbAtual->lex_char, tabela_tkEncontrados.tab[i].hashTabSimb);
        }
    }
    fprintf(arq, "+-----+-----+-----+------------------+");
    for(i = 0; i < tamMaiorLex + 2; i++)
        fprintf(arq, "-");
    fprintf(arq, "+----------------+\n\n\n");


    fprintf(arq, "RESUMO\n\n");
    fprintf(arq, "+-----+------------------+------+\n");
    fprintf(arq, "| COD | TOKEN            | USOS |\n");
    fprintf(arq, "+-----+------------------+------+\n");
    for (i = 0; i < 41; i++)
    {
        fprintf(arq, "| %3d | %-16s | %4d |\n", i, tokenGetText(i), subTotalTkOcor[i]);
        totalTkOcor += subTotalTkOcor[i];
    }
    fprintf(arq, "+-----+------------------+------+\n");
    fprintf(arq, "|   X | TOTAL            | %4d |\n", totalTkOcor);
    fprintf(arq, "+-----+------------------+------+\n\n");

    fprintf(arq, "TOTAL DE ERROS: %d\n\n", totalErros);

    free(nomeArqTk);
    fclose(arq);
}

void salvarArquivoTabSimb (char *nomeArq, int tamMaiorLex)
{
    int  i;
    int maiorEspOcor = (maiorQtdeOcorSimb * 10) < 30 ? 30 : maiorQtdeOcorSimb * 10;
    tSimbolo *simbAtual = NULL;
    char *nomeArqTk = (char *) malloc((strlen(nomeArq) + 5) * sizeof(char));
    if(nomeArqTk == NULL)
    {
        printf("Erro ao salvar arquivo de tabela de simbolos\n");
        exit(-1);
    }
    int subTotalTkOcor[41] = {0};
    int totalTkOcor = 0;

    strcpy(nomeArqTk, nomeArq);
    strcat(nomeArqTk, ".tbl");

    FILE *arq = fopen(nomeArqTk, "w");
    if(arq == NULL)
    {
        printf("Erro ao salvar arquivo de tabela de simbolos\n");
        exit(-1);
    }



    fprintf(arq, "TABELA DE SIMBOLOS - \"%s\"\n\n", nomeArq);

    fprintf(arq, "+-----+------------------+");
    for (i = 0; i < tamMaiorLex + 2; i++)
        fprintf(arq, "-");
    fprintf(arq, "+");
    for (i = 0; i < maiorEspOcor + 1; i++)
        fprintf(arq, "-");
    fprintf(arq, "+\n");
    fprintf(arq,"| POS | %-16s | %-*s | %-*s|\n", "TOKEN", tamMaiorLex, "LEXEMA", maiorEspOcor, "POS NA ENTRADA (linha,coluna)");
    fprintf(arq, "+-----+------------------+");
    for (i = 0; i < tamMaiorLex + 2; i++)
        fprintf(arq, "-");
    fprintf(arq, "+");
    for (i = 0; i < maiorEspOcor + 1; i++)
        fprintf(arq, "-");
    fprintf(arq, "+\n");



}


#endif