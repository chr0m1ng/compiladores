/* ------------------------------------------------------------- */
/*                     ARQUIVO: main.c                           */
/* ------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../Header/transicoes.h"

int main(int argc, char *argv[]){
    char simbolo = 'k';
    printf("%u\n", tabela_transicao[20][charToAlfabeto(&simbolo)]);
    return 0;
}