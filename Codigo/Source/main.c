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
#include "../Header/lexema.h"
#include "../Header/erroLexico.h"
#include "../Header/saidas.h"


tLexema lexema_atual;

int main(int argc, char *argv[])
{

    int pos = 0;

    alocarTabSimb();
    alocarTabelaTkEncontrados();

    pos = addSimbNaTab(TK_FIM_PROGRAMA, "adeshow", 0, 1);
    addTkTabelaEncontrados(TK_FIM_PROGRAMA, 0, 1, hash("adeshow"), pos);

    pos = addSimbNaTab(TK_IDEN, "teste", 0, 3);
    addTkTabelaEncontrados(TK_IDEN, 0, 3, hash("teste"), pos);
    
    pos = addSimbNaTab(TK_DEC, "2.3", 1, 3);
    addTkTabelaEncontrados(TK_DEC, 1, 3, hash("2.3"), pos);

    addTkTabelaEncontrados(TK_ATRIB, 2, 3, -1, -1);

    salvarArquivoTabSimb("teste.ptg", 7);

    liberarTabelaTkEncontrados();
    liberarTabSimb();



    return 0;
}