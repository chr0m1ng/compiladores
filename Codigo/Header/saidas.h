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
#include "analisadorLexico.h"

/*
*-----------------------------------------------------------------------
*   Signatures
*-----------------------------------------------------------------------
*/

void salvarArquivoTks (char *);
void salvarArquivoTabSimb (char *);
void salvarArquivoErr (char *);

/*
*-----------------------------------------------------------------------
*   FUNCTIONS
*-----------------------------------------------------------------------
*/

void salvarArquivoTks (char *nomeArq)
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

    fprintf(arq, "TOTAL DE ERROS: %lu\n\n", tabela_erros_lexicos.tamAtual);

    free(nomeArqTk);
    fclose(arq);
}

void salvarArquivoTabSimb (char *nomeArq)
{
    int  i;
    int j;
    int qtdeOcorAtual = 0;
    int maiorEspOcor = (maiorQtdeOcorSimb * 10) < 30 ? 30 : maiorQtdeOcorSimb * 10;
    tSimbolo *simbAtual = NULL;
    tPos *ocorAtual = NULL;
    char *nomeArqTab = (char *) malloc((strlen(nomeArq) + 5) * sizeof(char));
    if(nomeArqTab == NULL)
    {
        printf("Erro ao salvar arquivo de tabela de simbolos\n");
        exit(-1);
    }

    strcpy(nomeArqTab, nomeArq);
    strcat(nomeArqTab, ".tbl");

    FILE *arq = fopen(nomeArqTab, "w");
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

    for (i = 0; i < TAM_TAB_SIMB; i++)
    {
        simbAtual = tabela_simbolos[i];
        while(simbAtual != NULL)
        {
            fprintf(arq, "| %3d | %-16s | %-*s | ", i, tokenGetText(simbAtual->tk), tamMaiorLex, simbAtual->lex_char);
            ocorAtual = simbAtual->ocor;
            while(ocorAtual != NULL)
            {
                fprintf(arq, "(%3d,%3d) ", ocorAtual->lin, ocorAtual->col);
                ocorAtual = ocorAtual->prox;
                qtdeOcorAtual++;
            }
            for(j = 0; j < (maiorEspOcor - (qtdeOcorAtual * 10)); j++)
                fprintf(arq, " ");
            fprintf(arq, "|\n");
            simbAtual = simbAtual->prox;
            qtdeOcorAtual = 0;
        }
    }
    fprintf(arq, "+-----+------------------+");
    for (i = 0; i < tamMaiorLex + 2; i++)
        fprintf(arq, "-");
    fprintf(arq, "+");
    for (i = 0; i < maiorEspOcor + 1; i++)
        fprintf(arq, "-");
    fprintf(arq, "+\n");

    free(nomeArqTab);
    fclose(arq);

}

void salvarArquivoErr (char *nomeArq)
{
    int i;
    int errosLidos = 0;
    int qtdeErrosNaLinha = 0;
    int nmrLinhaAtual = 1;
    size_t tamLinhaAtual = 0;
    char simbAtual;
    char *nomeArqErr = (char *) malloc((strlen(nomeArq) + 5) * sizeof(char));
    if(nomeArqErr == NULL)
    {
        printf("Erro ao salvar arquivo de erro\n");
        exit(-1);
    }

    strcpy(nomeArqErr, nomeArq);
    strcat(nomeArqErr, ".err");

    FILE *arqOut = fopen(nomeArqErr, "w");
    FILE *arqIn = fopen(nomeArq, "r");
    if(arqOut == NULL || arqIn == NULL)
    {
        printf("Erro ao salvar arquivo de erro\n");
        exit(-1);
    }

    fprintf(arqOut, "LISTA DE ERROS LEXICOS EM \"%s\"\n\n", nomeArq);

    while(!feof(arqIn))
    {
        simbAtual = fgetc(arqIn);
        if(simbAtual != EOF)
        {
            fprintf(arqOut, "[%4d] ", nmrLinhaAtual);
            tamLinhaAtual++;
            
            while(simbAtual != '\n' && simbAtual != EOF)
            {
                fprintf(arqOut, "%c", simbAtual);
                simbAtual = fgetc(arqIn);
                tamLinhaAtual++;
            }

            qtdeErrosNaLinha = verificaErroNaLinha(nmrLinhaAtual);

            if(qtdeErrosNaLinha == 1)
            {
                fprintf(arqOut, "\n%6s", "");
                for (i = 0; i < tabela_erros_lexicos.tab[errosLidos].col; i++)
                    fprintf(arqOut, "-");
                fprintf(arqOut, "-^\n");
                fprintf(arqOut, "%4sErro lexico na linha %d coluna %d: %s '%c'", "", tabela_erros_lexicos.tab[errosLidos].lin, tabela_erros_lexicos.tab[errosLidos].col, erroGetText(tabela_erros_lexicos.tab[errosLidos].err), tabela_erros_lexicos.tab[errosLidos].simb);
                errosLidos++;
            }
            else if (qtdeErrosNaLinha > 1)
            {
                fprintf(arqOut, "\n%6s", "");
                for (i = 0; i < tabela_erros_lexicos.tab[errosLidos].col; i++)
                    fprintf(arqOut, "-");
                fprintf(arqOut, "-^\n");
                fprintf(arqOut, "%4sErro lexico na linha %d coluna %d: %s '%c'", "", tabela_erros_lexicos.tab[errosLidos].lin, tabela_erros_lexicos.tab[errosLidos].col, erroGetText(tabela_erros_lexicos.tab[errosLidos].err), tabela_erros_lexicos.tab[errosLidos].simb);
                errosLidos++;
                for(i = 0; i < qtdeErrosNaLinha; i++)
                {
                    fseek(arqIn, -tamLinhaAtual, SEEK_CUR);
                    simbAtual = fgetc(arqIn);
                    fprintf(arqOut, "\n[%4d] ", nmrLinhaAtual);
                    while(simbAtual != '\n' && simbAtual != EOF)
                    {
                        fprintf(arqOut, "%c", simbAtual);
                        simbAtual = fgetc(arqIn);
                    }
                    fprintf(arqOut, "\n%6s", "");
                    for (i = 0; i < tabela_erros_lexicos.tab[errosLidos].col; i++)
                        fprintf(arqOut, "-");
                    fprintf(arqOut, "-^\n");
                    fprintf(arqOut, "%4sErro lexico na linha %d coluna %d: %s '%c'", "", tabela_erros_lexicos.tab[errosLidos].lin, tabela_erros_lexicos.tab[errosLidos].col, erroGetText(tabela_erros_lexicos.tab[errosLidos].err), tabela_erros_lexicos.tab[errosLidos].simb);
                    errosLidos++;
                }
            }
            
            fprintf(arqOut, "\n");
            nmrLinhaAtual++;
            tamLinhaAtual = 0;
        }
    }

    fprintf(arqOut, "\nTOTAL DE ERROS: %lu\n", tabela_erros_lexicos.tamAtual);
    free(nomeArqErr);
    fclose(arqIn);
    fclose(arqOut);

}

#endif