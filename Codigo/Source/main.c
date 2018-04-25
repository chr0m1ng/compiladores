/*
*---------------------------------------------------------------------
*   INCLUDE FILES
*---------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <wctype.h>

#include "../Header/analisadorLexico.h"


tLexema lexema_atual;

int main(int argc, char *argv[])
{
    inicializarAnalisadorLexico("teste.ptg");
    tToken tkAtual;
    
    tkAtual = obterProxToken();
    while(tkAtual != TK_EOF)
        tkAtual = obterProxToken();

    finalizarAnalisadorLexico();

    return 0;
}