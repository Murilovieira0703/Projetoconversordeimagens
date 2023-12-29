#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "con.h"

int main(int argc, char *argv[]){
    //primero verificamos se o usuario precisa de ajuda
    if(argc < 2){
        //teste para ver se ele nao inseriu nenhuma funcao, portanto enviamos o helper
        helper();
        return 1;
    }

    //veremos se o usuario chamou o helper
    if(strcmp(argv[1], "--help") == 0){
        //usuario chamou
        helper();
        return 0;
    }

    if(strcmp(argv[2], "create") == 0){
        if(testaNome(argv[1]) == 0){
            if(testaPGM(argv[3]) == 0){
                Lista Lista = criarLista(argv[1], argv[3]);
            }
        }
    }

    if(strcmp(argv[2], "read") == 0){
        if(testaNome(argv[1]) == 0){
            imprimirListaOrdenada(argv[1]);
        }
    }

    if(strcmp(argv[2], "add") == 0){
        if(testaNome(argv[1]) == 0){
            if(testaPGM(argv[3]) == 0){
                adicionarArquivo(argv[1], argv[3]);
            }
        }
    }
    
    if(strcmp(argv[2], "remove") == 0){
        if(testaNome(argv[1]) == 0){
            if(testaPGM(argv[3]) == 0){
                removerArquivo(argv[1], argv[3]);
            }
        }
    }

    if(strcmp(argv[2], "limiar") == 0){
        if(testaNome(argv[1]) == 0){
            // Converte a string para um inteiro usando strtol
            char *endptr;
            long numero = strtol(argv[3], &endptr, 10);
            limiarizarLista(argv[1], numero);
        }
    }

    if(strcmp(argv[2], "inverter") == 0){
        if(testaNome(argv[1]) == 0){
            inverterLista(argv[1]);
        }
    }

    if(strcmp(argv[2], "espelharv") == 0){
        if(testaNome(argv[1]) == 0){
            espelharVerticalLista(argv[1]);
        }
    }

    if(strcmp(argv[2], "espelharh") == 0){
        if(testaNome(argv[1]) == 0){
            //este r esta sendo passado, pois pensei mal e achei que espelhar pela direita ou pela esquerda seriam espelhamentos diferentes, e ficou muito dificil para corrigir depois, peço perdão!!
            espelharHorizontalLista(argv[1], "r");
        }
    }

    //sempre relembrar sobre o help
    printf("Se precisar de ajuda digite --help na linha de comando \n");
    return 0;
}