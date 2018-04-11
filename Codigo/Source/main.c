/*
*---------------------------------------------------------------------
*   INCLUDE FILES
*---------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../Header/transicoes.h"
#include "../Header/tokens.h"
#include "../Header/reservadas.h"
#include "../Header/simbolos.h"



int main(int argc, char *argv[])
{
    int i;
    tPos *aux;

    alocarTabSimb();
    addSimbNaTab(TK_CADEIA, "cadeia teste", 0, 1);
    addSimbNaTab(TK_CADEIA, "cadeia teste", 2, 3);
    addSimbNaTab(TK_CADEIA, "cadeia teste", 5, 1);

    printf("%s\n", tabela_simbolos->tabela[hash("cadeia teste")]->lex_char);
    
    aux = tabela_simbolos->tabela[hash("cadeia teste")]->ocor;
    while(aux != NULL)
    {
        printf("(%d, %d) ", aux->lin, aux->col);   
        aux = aux->prox;
    }
    printf("\n");

    liberarTabSimb();

    return 0;
}