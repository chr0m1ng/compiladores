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
    alocarTabErrLex();

    addTkTabelaEncontrados(TK_PROGRAMA, 3, 1, -1, -1);

    addTkTabelaEncontrados(TK_INTEIRO, 4, 3, -1, -1);

    addTkTabelaEncontrados(TK_DOIS_PTS, 4, 10, -1, -1);

    pos = addSimbNaTab(TK_IDEN, "n", 4, 13);
    addTkTabelaEncontrados(TK_IDEN, 4, 13, hash("n"), pos);
    
    pos = addSimbNaTab(TK_IDEN, "mero", 4, 15);
    addTkTabelaEncontrados(TK_IDEN, 4, 15, hash("mero"), pos);

    addTkTabelaEncontrados(TK_VIRG, 4, 19, -1, -1);

    pos = addSimbNaTab(TK_IDEN, "r", 4, 21);
    addTkTabelaEncontrados(TK_IDEN, 4, 21, hash("r"), pos);

    addTkTabelaEncontrados(TK_PT_VIRG, 4, 22, -1, -1);

    addTkTabelaEncontrados(TK_SAIDA, 5, 3, -1, -1);

    addTkTabelaEncontrados(TK_ABRE_PAR, 5, 9, -1, -1);

    pos = addSimbNaTab(TK_CADEIA, "Digite um nro:", 5, 10);
    addTkTabelaEncontrados(TK_CADEIA, 5, 10, hash("Digite um nro:"), pos);

    addTkTabelaEncontrados(TK_FECHA_PAR, 5, 26, -1, -1);

    addTkTabelaEncontrados(TK_PT_VIRG, 5, 27, -1, -1);

    addTkTabelaEncontrados(TK_ENTRADA, 6, 3, -1, -1);

    addTkTabelaEncontrados(TK_ABRE_PAR, 6, 11, -1, -1);

    pos = addSimbNaTab(TK_IDEN, "numero", 6, 12);
    addTkTabelaEncontrados(TK_IDEN, 6, 12, hash("numero"), pos);

    addTkTabelaEncontrados(TK_FECHA_PAR, 6, 18, -1, -1);

    addTkTabelaEncontrados(TK_PT_VIRG, 6, 19, -1, -1);

    pos = addSimbNaTab(TK_IDEN, "r", 7, 3);
    addTkTabelaEncontrados(TK_IDEN, 7, 3, hash("r"), pos);


    addTkTabelaEncontrados(TK_ATRIB, 7, 5, -1, -1);

    pos = addSimbNaTab(TK_IDEN, "raiz", 7, 8);
    addTkTabelaEncontrados(TK_IDEN, 7, 8, hash("raiz"), pos);


    addTkTabelaEncontrados(TK_ABRE_PAR, 7, 13, -1, -1);

    pos = addSimbNaTab(TK_IDEN, "n", 7, 14);
    addTkTabelaEncontrados(TK_IDEN, 7, 14, hash("n"), pos);

    pos = addSimbNaTab(TK_IDEN, "mero", 7, 15);
    addTkTabelaEncontrados(TK_IDEN, 7, 15, hash("mero"), pos);

    addTkTabelaEncontrados(TK_FECHA_PAR, 7, 20, -1, -1);

    addTkTabelaEncontrados(TK_PT_VIRG, 7, 21, -1, -1);

    addTkTabelaEncontrados(TK_SAIDA, 8, 3, -1, -1);

    addTkTabelaEncontrados(TK_ABRE_PAR, 8, 8, -1, -1);

    pos = addSimbNaTab(TK_IDEN, "r", 8, 9);
    addTkTabelaEncontrados(TK_IDEN, 8, 9, hash("r"), pos);

    addTkTabelaEncontrados(TK_FECHA_PAR, 8, 10, -1, -1);

    addTkTabelaEncontrados(TK_PT_VIRG, 8, 11, -1, -1);

    addTkTabelaEncontrados(TK_FIM_PROGRAMA, 9, 1, -1, -1);

    addTkTabelaEncontrados(TK_EOF, 10, 0, -1, -1);

    addErrNaTab(ERRO_CHAR_INV, '@', 4, 12);
    addErrNaTab(ERRO_CHAR_INV, 'ú', 4, 14);
    
    addErrNaTab(ERRO_CHAR_INV, 'ú', 7, 15);

    salvarArquivoTks("teste.ptg", 14);
    salvarArquivoTabSimb("teste.ptg", 14);
    salvarArquivoErr("teste.ptg");

    liberarTabErrLex();
    liberarTabelaTkEncontrados();
    liberarTabSimb();



    return 0;
}