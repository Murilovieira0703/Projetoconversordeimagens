#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "con.h"

void helper(void){
    printf("Seja bem-vindo este programa foi feito para te ajudar com a manipulacao de imagens PGM \n aqui voce pode edita-las e criar listas com todas suas imagens, veja como com nossas funcoes: \n");
    printf("Aqui voce encontrara alguns detalhes sobre todas as funcoes disponiveis para seu uso. Veja tudo possivel fazer com este programa:\n1- Criar uma lista: Voce pode criar uma lista que sera salva no repositorio deste codigo e contera seus arquivos de imagem pgm\n sintaxe no console: ./'nome do arquivo compilado' 'nome da lista' create(funcao usada pra criar) 'nome da primeira imagem da lista' \n2- Adicionar imagens: esta funcao adiciona imagens em uma lista anteriormente criada\n sintaxe: ./'nome do arquivo compilado' 'nome da lista ja criada' add(funcao para adicionar) 'nome da imagem a ser adicionada' \n");
    printf("3- Remover imagens de sua lista: com esta funcao voce pode remover o nome de uma imagem anteriormente adicionad a lista \n sintaxe: ./'nome do arquivo compilado' 'nome da lista usada' remove(funcao para remover os nomes) 'nome da imagem a ser removida'\n");
    printf("4- Imprimir lista: com essa funcao todos os nome de imagens contidos em sua lista serao impressos em ordem alfabetica para visualizacao\n sintaxe: ./'nome do arquivo compilado' 'nome da lista' read(funcao usada para imprimir a lista) \n");
    printf("5- Limiar: faca a operacao de limiar em suas imagens! \n sitaxe: ./'nome do arquivo compilado' 'nome da lista' limiar(funcao) 'numero de cinza desejado' \n");
    printf("6- Inversao: faca a operacao de inversao em suas imagens! \n sitaxe: ./'nome do arquivo compilado' 'nome da lista' inverter(funcao) \n");
    printf("7- Espelhamento vertical: faca a operacao de espelhar suas imagens! \n sitaxe: ./'nome do arquivo compilado' 'nome da lista' espelharv(funcao) \n");
    printf("8- Espelhamento horizontal: faca a operacao de espelhar suas imagens! \n sitaxe: ./'nome do arquivo compilado' 'nome da lista' espelharh(funcao) \n");
    printf("WARNING: se atente a sintaxe de cada funcao para nao haver erros\n");
    printf("WARNING: sempre passe o nome das listas com extensao .bin e a imagens sempre devem ser .pgm\n");

}
//criarei uma funcao para testar sempre o nome da lista
int testaNome(const char *nomeArquivo){
    size_t tamanhoNomeArquivo = strlen(nomeArquivo);
    if(tamanhoNomeArquivo < 5 || strcmp(nomeArquivo + tamanhoNomeArquivo - 4, ".bin") != 0){
        printf("Nome do arquivo invalido. Deve terminar com '.bin'. \n");
        return 1; // para indicar erro a pagina main
    }
    return 0; //return esperado pela main
}
//verificamos se o arquivo inicial passado na linha termina com .pgm
int testaPGM(const char *arquivoInicial){
    size_t tamanhoArquivoInicial = strlen(arquivoInicial);
    if(tamanhoArquivoInicial < 4 || strcmp(arquivoInicial + tamanhoArquivoInicial - 4, ".pgm") != 0){
        printf("Arquivo inicial invalido. Deve terminar com '.pgm' \n");
        return 1;
    }
    return 0;
}
//funcao para criar novas listas com elemento inicial
Lista criarLista(const char *nomeArquivo, const char *arquivoInicial) {
    Lista novaLista;

    //logica para inicializar a lista com um elemento
    strcpy(novaLista.elemento.nomeArquivo, arquivoInicial);

    printf("Lista '%s' criada com sucesso! \n", nomeArquivo);

    FILE *arquivoLista = fopen(nomeArquivo, "wb");
    if(arquivoLista == NULL) {
        printf("Erro ao criar o arquivo lista.bin \n");
        return;
    }

    if(fwrite(novaLista.elemento.nomeArquivo, sizeof(char), strlen(novaLista.elemento.nomeArquivo), arquivoLista) != strlen(novaLista.elemento.nomeArquivo)){
        printf("Erro ao escrever no arquivo lista.bin \n");
        fclose(arquivoLista);
        return;   
    } 

    fclose(arquivoLista);

    return novaLista;
}
// Função de comparação para qsort
int compararStrings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

// Função para imprimir os arquivos da lista em ordem alfabética
void imprimirListaOrdenada(const char *nomeArquivo) {
    FILE *arquivoLista = fopen(nomeArquivo, "r");  // Abre o arquivo para leitura de texto
    if (arquivoLista == NULL) {
        printf("Erro ao abrir o arquivo lista.bin para leitura");
        return;
    }

    char linha[50];  // Ajuste o tamanho conforme necessário
    char **elementos = NULL;  // Array de strings para armazenar os elementos
    int numElementos = 0;  // Número total de elementos na lista

    // Lê e armazena cada linha da lista
    while (fgets(linha, sizeof(linha), arquivoLista) != NULL) {
        // Remove o caractere de nova linha, se estiver presente
        if (linha[strlen(linha) - 1] == '\n') {
            linha[strlen(linha) - 1] = '\0';
        }

        // Verifica se a linha não é vazia antes de adicionar ao array
        if (linha[0] != '\0') {
            // Aloca espaço para a string e copia a linha
            char *elemento = strdup(linha);

            // Adiciona a string ao array
            elementos = realloc(elementos, (numElementos + 1) * sizeof(char *));
            elementos[numElementos++] = elemento;
        }
    }

    // Fecha o arquivo após a leitura
    fclose(arquivoLista);

    // Ordena o array de strings
    qsort(elementos, numElementos, sizeof(char *), compararStrings);

    // Imprime os elementos ordenados
    for (int i = 0; i < numElementos; i++) {
        printf("Elemento da lista: %s\n", elementos[i]);
        free(elementos[i]);  // Libera a memória alocada para cada string
    }

    free(elementos);  // Libera o array de strings
}
// Função para adicionar um novo arquivo à lista
void adicionarArquivo(const char *nomeArquivoLista, const char *novoArquivo) {
    FILE *arquivoLista = fopen(nomeArquivoLista, "a+");  // Abre o arquivo em modo de adição e leitura
    if (arquivoLista == NULL) {
        printf("Erro ao abrir o arquivo lista.bin para adição");
        return;
    }

    // Posiciona o cursor no início do arquivo
    fseek(arquivoLista, 0, SEEK_SET);

    // Procura a última linha no arquivo
    char ultimaLinha[50];  // Ajuste o tamanho conforme necessário
    while (fgets(ultimaLinha, sizeof(ultimaLinha), arquivoLista) != NULL) {
        // Não faz nada, apenas lê até o final do arquivo
    }

    // Verifica se a última linha está vazia
    if (ultimaLinha[0] != '\0' && ultimaLinha[0] != '\n') {
        // Se a última linha não está vazia, adiciona uma quebra de linha
        fprintf(arquivoLista, "\n");
    }

    // Escreve o novo arquivo na lista
    fprintf(arquivoLista, "%s\n", novoArquivo);
    printf("Nome adicionado com sucesso! \n");

    // Fecha o arquivo após a adição
    fclose(arquivoLista);
}

// Função para remover um arquivo da lista
void removerArquivo(const char *nomeArquivoLista, const char *arquivoRemover) {
    FILE *arquivoLista = fopen(nomeArquivoLista, "r");  // Abre o arquivo para leitura
    if (arquivoLista == NULL) {
        printf("Erro ao abrir o arquivo lista.bin para leitura");
        return;
    }

    // Cria um arquivo temporário para armazenar a lista atualizada
    FILE *arquivoTemp = fopen("temp_lista.bin", "w");  // Abre o arquivo temporário para escrita
    if (arquivoTemp == NULL) {
        printf("Erro ao criar arquivo temporário");
        fclose(arquivoLista);
        return;
    }

    char linha[50];  // Ajuste o tamanho conforme necessário
    int encontrado = 0;  // Flag para indicar se o arquivo foi encontrado

    // Lê e verifica cada linha da lista
    while (fgets(linha, sizeof(linha), arquivoLista) != NULL) {
        // Remove o caractere de nova linha, se estiver presente
        if (linha[strlen(linha) - 1] == '\n') {
            linha[strlen(linha) - 1] = '\0';
        }

        // Verifica se a linha atual é igual ao arquivo a ser removido
        if (strcmp(linha, arquivoRemover) == 0) {
            encontrado = 1;
        } else {
            // Se não for igual, escreve a linha no arquivo temporário
            fprintf(arquivoTemp, "%s\n", linha);
        }
    }

    // Fecha os arquivos após a leitura/escrita
    fclose(arquivoLista);
    fclose(arquivoTemp);

    // Remove o arquivo original e renomeia o temporário
    remove(nomeArquivoLista);
    rename("temp_lista.bin", nomeArquivoLista);

    // Informa se o arquivo foi removido ou não
    if (encontrado) {
        printf("Arquivo removido com sucesso: %s\n", arquivoRemover);
    } else {
        printf("O arquivo %s não foi encontrado na lista.\n", arquivoRemover);
    }
}
// Função para ler uma imagem a partir de um arquivo
imgb read_img(const char *nomeArquivo) {
    FILE *fimg = fopen(nomeArquivo, "r");
    if (fimg == NULL) {
        perror("Erro ao abrir arquivo da imagem para leitura");
        exit(EXIT_FAILURE);
    }

    // Tipo de imagem. Vamos fixar essa linha como "P2"
    char ver[5];
    fgets(ver, sizeof(ver), fimg);
    if (strcmp(ver, "P2\n") != 0) {
        fprintf(stderr, "Formato de imagem não suportado: %s", ver);
        exit(EXIT_FAILURE);
    }

    // Ignorar comentários
    char c = getc(fimg);
    while (c == '#') {
        while (getc(fimg) != '\n');
        c = getc(fimg);
    }
    ungetc(c, fimg);

    // Dimensões da imagem
    imgb I;
    fscanf(fimg, "%d", &I.w);
    fscanf(fimg, "%d", &I.h);
    fscanf(fimg, "%d", &I.cinza);

    I.pixel = malloc(I.h * I.w * sizeof(int));
    if (I.pixel != NULL) {
        for (int i = 0; i < I.h; i++)
            for (int j = 0; j < I.w; j++) {
                if (fscanf(fimg, "%d", &I.pixel[i * I.w + j]) != 1) {
                    printf("Erro ao ler valor do pixel em (%d, %d)\n", i, j);
                    free(I.pixel);
                    fclose(fimg);
                    exit(EXIT_FAILURE);
                }
            }
    } else {
        printf("Falha na alocação de memória.\n");
    }

    fclose(fimg);
    return I;
}
// Função para aplicar a limiarização a uma imagem
void limiar(imgb *imagem, int valorlimiar) {
    for (int i = 0; i < imagem->h; i++)
        for (int j = 0; j < imagem->w; j++) {
            if (imagem->pixel[i * imagem->w + j] <= valorlimiar) {
                imagem->pixel[i * imagem->w + j] = 0;
            } else {
                imagem->pixel[i * imagem->w + j] = 255;
            }
        }
}

// Função para liberar a memória alocada para a imagem
void free_imgb(imgb *imagem) {
    free(imagem->pixel);
}

// Função para limiarizar uma lista de imagens
void limiarizarLista(const char *nomeArquivoLista, int valorlimiar) {
    FILE *arquivoLista = fopen(nomeArquivoLista, "r");
    if (arquivoLista == NULL) {
        printf("Erro ao abrir o arquivo lista.bin para leitura.\n");
        return;
    }

    char linha[100];  // Ajuste o tamanho conforme necessário

    // Lê e limiariza cada imagem da lista
    while (fgets(linha, sizeof(linha), arquivoLista) != NULL) {
        size_t tamanhoLinha = strlen(linha);
        if (linha[tamanhoLinha - 1] == '\n') {
            linha[tamanhoLinha - 1] = '\0';
        }

        // Abre o arquivo da imagem
        FILE *arquivoImagem = fopen(linha, "r");
        if (arquivoImagem != NULL) {
            imgb imagem = read_img(linha);

            // Aplica a limiarização na imagem
            limiar(&imagem, valorlimiar);

            // Cria o nome do novo arquivo com sufixo "_limiar.pgm"
            char novoNomeArquivo[100];  // Ajuste o tamanho conforme necessário

            // Encontrar a última ocorrência de '/' ou '\' na linha (se existir)
            char *barra = strrchr(linha, '/');
            char *barraInvertida = strrchr(linha, '\\');
            char *ultimaBarra = barra > barraInvertida ? barra : barraInvertida;

            char *nomeSemPath = ultimaBarra != NULL ? ultimaBarra + 1 : linha;

            // Encontrar a última ocorrência de '.' no nome (se existir)
            char *extensao = strrchr(nomeSemPath, '.');
            if (extensao != NULL) {
                // Calcular o comprimento do nome do arquivo sem a extensão
                size_t tamanhoNomeSemExtensao = extensao - nomeSemPath;

                // Copiar o nome do arquivo sem a extensão para novoNomeArquivo
                strncpy(novoNomeArquivo, nomeSemPath, tamanhoNomeSemExtensao);
                novoNomeArquivo[tamanhoNomeSemExtensao] = '\0';

                // Adicionar "_limiar.pgm" ao final do novoNomeArquivo
                strncat(novoNomeArquivo, "_limiar.pgm", sizeof(novoNomeArquivo) - tamanhoNomeSemExtensao - 1);
            } else {
                // Caso não haja extensão, simplesmente adiciona "_limiar.pgm"
                snprintf(novoNomeArquivo, sizeof(novoNomeArquivo), "%s_limiar.pgm", nomeSemPath);
            }

            // Abre o novo arquivo para escrita
            FILE *novoArquivoImagem = fopen(novoNomeArquivo, "w");
            if (novoArquivoImagem != NULL) {
                // Escreve os dados da imagem limiarizada no novo arquivo
                fprintf(novoArquivoImagem, "P2\n");
                fprintf(novoArquivoImagem, "%d %d\n", imagem.w, imagem.h);
                fprintf(novoArquivoImagem, "%d\n", imagem.cinza);

                for (int i = 0; i < imagem.h; i++)
                    for (int j = 0; j < imagem.w; j++)
                        fprintf(novoArquivoImagem, "%d ", imagem.pixel[i * imagem.w + j]);

                // Libera a memória da imagem
                free_imgb(&imagem);

                // Fecha o novo arquivo da imagem
                fclose(novoArquivoImagem);
            } else {
                printf("Erro ao criar o novo arquivo da imagem %s.\n", novoNomeArquivo);
            }

            // Fecha o arquivo da imagem original
            fclose(arquivoImagem);
        } else {
            printf("Erro ao abrir o arquivo da imagem %s para leitura.\n", linha);
        }
        printf("Limiar feita com sucesso! \n");
    }

    // Fecha o arquivo da lista
    fclose(arquivoLista);
}
void inversa(imgb *I)
/*
    Realiza a transformação inversa da imagem.
*/
{
    if (I->pixel!=NULL)
    {
        for (int i=0; i<I->h; i++)
            for  (int j=0; j<I->w; j++)
            {
                I->pixel[i*I->w+j] = I->cinza-I->pixel[i*I->w+j];
            }
    }
    else
    {
        printf("Imagem de entrada é NULL.");
    }
}

void inverterLista(const char *nomeArquivoLista) {
    FILE *arquivoLista = fopen(nomeArquivoLista, "r");
    if (arquivoLista == NULL) {
        printf("Erro ao abrir o arquivo lista.bin para leitura.\n");
        return;
    }

    char linha[100];  // Ajuste o tamanho conforme necessário

    // Lê e inverte cada imagem da lista
    while (fgets(linha, sizeof(linha), arquivoLista) != NULL) {
        size_t tamanhoLinha = strlen(linha);
        if (linha[tamanhoLinha - 1] == '\n') {
            linha[tamanhoLinha - 1] = '\0';
        }

        char nomeArquivo[100];

        // Use sscanf para extrair o nome do arquivo
        if (sscanf(linha, "%s", nomeArquivo) == 1) {
            // Abre o arquivo da imagem
            FILE *arquivoImagem = fopen(nomeArquivo, "r");
            if (arquivoImagem != NULL) {
                // Agora, passamos o nome do arquivo (nomeArquivo) para a função read_img
                imgb imagem = read_img(nomeArquivo);

                // Aplica a inversão na imagem
                inversa(&imagem);

                // Cria o nome do novo arquivo com sufixo "_inversa.pgm"
                char novoNomeArquivo[100];  // Ajuste o tamanho conforme necessário

                // Encontrar a última ocorrência de '/' ou '\' na linha (se existir)
                char *barra = strrchr(nomeArquivo, '/');
                char *barraInvertida = strrchr(nomeArquivo, '\\');
                char *ultimaBarra = barra > barraInvertida ? barra : barraInvertida;

                char *nomeSemPath = ultimaBarra != NULL ? ultimaBarra + 1 : nomeArquivo;

                // Encontrar a última ocorrência de '.' no nome (se existir)
                char *extensao = strrchr(nomeSemPath, '.');
                if (extensao != NULL) {
                    // Calcular o comprimento do nome do arquivo sem a extensão
                    size_t tamanhoNomeSemExtensao = extensao - nomeSemPath;

                    // Copiar o nome do arquivo sem a extensão para novoNomeArquivo
                    strncpy(novoNomeArquivo, nomeSemPath, tamanhoNomeSemExtensao);
                    novoNomeArquivo[tamanhoNomeSemExtensao] = '\0';

                    // Adicionar "_inversa.pgm" ao final do novoNomeArquivo
                    strncat(novoNomeArquivo, "_inversa.pgm", sizeof(novoNomeArquivo) - tamanhoNomeSemExtensao - 1);
                } else {
                    // Caso não haja extensão, simplesmente adiciona "_inversa.pgm"
                    snprintf(novoNomeArquivo, sizeof(novoNomeArquivo), "%s_inversa.pgm", nomeSemPath);
                }

                // Abre o novo arquivo para escrita
                FILE *novoArquivoImagem = fopen(novoNomeArquivo, "w");
                if (novoArquivoImagem != NULL) {
                    // Escreve os dados da imagem invertida no novo arquivo
                    fprintf(novoArquivoImagem, "P2\n");
                    fprintf(novoArquivoImagem, "%d %d\n", imagem.w, imagem.h);
                    fprintf(novoArquivoImagem, "%d\n", imagem.cinza);

                    for (int i = 0; i < imagem.h; i++)
                        for (int j = 0; j < imagem.w; j++)
                            fprintf(novoArquivoImagem, "%d ", imagem.pixel[i * imagem.w + j]);

                    // Libera a memória da imagem
                    free_imgb(&imagem);

                    // Fecha o novo arquivo da imagem
                    fclose(novoArquivoImagem);
                } else {
                    printf("Erro ao criar o novo arquivo da imagem %s.\n", novoNomeArquivo);
                }

                // Fecha o arquivo da imagem original
                fclose(arquivoImagem);
            } else {
                printf("Erro ao abrir o arquivo da imagem %s para leitura.\n", nomeArquivo);
            }
        } else {
            printf("Erro ao ler nome do arquivo: %s\n", linha);
        }
    }

    // Fechar o arquivo da lista
    fclose(arquivoLista);
}
void espelharVertical(imgb *I) {
    if (I->pixel != NULL) {
        for (int i = 0; i < I->h / 2; i++) {
            for (int j = 0; j < I->w; j++) {
                // Troca os pixels verticalmente
                int temp = I->pixel[i * I->w + j];
                I->pixel[i * I->w + j] = I->pixel[(I->h - 1 - i) * I->w + j];
                I->pixel[(I->h - 1 - i) * I->w + j] = temp;
            }
        }
    } else {
        printf("Imagem de entrada é NULL.\n");
    }
}

void espelharVerticalLista(const char *nomeArquivoLista) {
    FILE *arquivoLista = fopen(nomeArquivoLista, "r");
    if (arquivoLista == NULL) {
        printf("Erro ao abrir o arquivo lista.bin para leitura.\n");
        return;
    }

    char linha[100];  // Ajuste o tamanho conforme necessário

    // Lê e aplica espelhamento vertical em cada imagem da lista
    while (fgets(linha, sizeof(linha), arquivoLista) != NULL) {
        size_t tamanhoLinha = strlen(linha);
        if (linha[tamanhoLinha - 1] == '\n') {
            linha[tamanhoLinha - 1] = '\0';
        }

        char nomeArquivo[100];

        // Use sscanf para extrair o nome do arquivo
        if (sscanf(linha, "%s", nomeArquivo) == 1) {
            // Abre o arquivo da imagem
            FILE *arquivoImagem = fopen(nomeArquivo, "r");
            if (arquivoImagem != NULL) {
                // Agora, passamos o nome do arquivo (nomeArquivo) para a função read_img
                imgb imagem = read_img(nomeArquivo);

                // Aplica o espelhamento vertical na imagem
                espelharVertical(&imagem);

                // Cria o nome do novo arquivo com sufixo "_espelhado_vertical.pgm"
                char novoNomeArquivo[100];  // Ajuste o tamanho conforme necessário

                // Encontrar a última ocorrência de '/' ou '\' na linha (se existir)
                char *barra = strrchr(nomeArquivo, '/');
                char *barraInvertida = strrchr(nomeArquivo, '\\');
                char *ultimaBarra = barra > barraInvertida ? barra : barraInvertida;

                char *nomeSemPath = ultimaBarra != NULL ? ultimaBarra + 1 : nomeArquivo;

                // Encontrar a última ocorrência de '.' no nome (se existir)
                char *extensao = strrchr(nomeSemPath, '.');
                if (extensao != NULL) {
                    // Calcular o comprimento do nome do arquivo sem a extensão
                    size_t tamanhoNomeSemExtensao = extensao - nomeSemPath;

                    // Copiar o nome do arquivo sem a extensão para novoNomeArquivo
                    strncpy(novoNomeArquivo, nomeSemPath, tamanhoNomeSemExtensao);
                    novoNomeArquivo[tamanhoNomeSemExtensao] = '\0';

                    // Adicionar "_espelhado_vertical.pgm" ao final do novoNomeArquivo
                    strncat(novoNomeArquivo, "_espelhado_vertical.pgm", sizeof(novoNomeArquivo) - tamanhoNomeSemExtensao - 1);
                } else {
                    // Caso não haja extensão, simplesmente adiciona "_espelhado_vertical.pgm"
                    snprintf(novoNomeArquivo, sizeof(novoNomeArquivo), "%s_espelhado_vertical.pgm", nomeSemPath);
                }

                // Abre o novo arquivo para escrita
                FILE *novoArquivoImagem = fopen(novoNomeArquivo, "w");
                if (novoArquivoImagem != NULL) {
                    // Escreve os dados da imagem espelhada verticalmente no novo arquivo
                    fprintf(novoArquivoImagem, "P2\n");
                    fprintf(novoArquivoImagem, "%d %d\n", imagem.w, imagem.h);
                    fprintf(novoArquivoImagem, "%d\n", imagem.cinza);

                    for (int i = 0; i < imagem.h; i++)
                        for (int j = 0; j < imagem.w; j++)
                            fprintf(novoArquivoImagem, "%d ", imagem.pixel[i * imagem.w + j]);

                    // Libera a memória da imagem
                    free_imgb(&imagem);

                    // Fecha o novo arquivo da imagem
                    fclose(novoArquivoImagem);
                } else {
                    printf("Erro ao criar o novo arquivo da imagem %s.\n", novoNomeArquivo);
                }

                // Fecha o arquivo da imagem original
                fclose(arquivoImagem);
            } else {
                printf("Erro ao abrir o arquivo da imagem %s para leitura.\n", nomeArquivo);
            }
        } else {
            printf("Erro ao ler nome do arquivo: %s\n", linha);
        }
    }

    // Fechar o arquivo da lista
    fclose(arquivoLista);
    printf("Espelhamento feito com sucesso! \n");
}
void espelharHorizontal(imgb *I, char direcao) {
    if (I->pixel != NULL) {
        for (int i = 0; i < I->h; i++) {
            for (int j = 0; j < I->w / 2; j++) {
                // Troca os pixels horizontalmente
                int temp;
                if (direcao == 'r') {
                    temp = I->pixel[i * I->w + j];
                    I->pixel[i * I->w + j] = I->pixel[i * I->w + I->w - 1 - j];
                    I->pixel[i * I->w + I->w - 1 - j] = temp;
                } else if (direcao == 'l') {
                    temp = I->pixel[i * I->w + j];
                    I->pixel[i * I->w + j] = I->pixel[i * I->w + I->w - 1 - j];
                    I->pixel[i * I->w + I->w - 1 - j] = temp;
                } else {
                    printf("Direção inválida. Use 'r' para right ou 'l' para left.\n");
                    return;
                }
            }
        }
    } else {
        printf("Imagem de entrada é NULL.\n");
    }
}

void espelharHorizontalLista(const char *nomeArquivoLista, const char *direcao) {
    FILE *arquivoLista = fopen(nomeArquivoLista, "r");
    if (arquivoLista == NULL) {
        printf("Erro ao abrir o arquivo lista.bin para leitura.\n");
        return;
    }

    char linha[100];  // Ajuste o tamanho conforme necessário

    // Lê e aplica espelhamento horizontal em cada imagem da lista
    while (fgets(linha, sizeof(linha), arquivoLista) != NULL) {
        size_t tamanhoLinha = strlen(linha);
        if (linha[tamanhoLinha - 1] == '\n') {
            linha[tamanhoLinha - 1] = '\0';
        }

        char nomeArquivo[100];

        // Use sscanf para extrair o nome do arquivo
        if (sscanf(linha, "%s", nomeArquivo) == 1) {
            // Abre o arquivo da imagem
            FILE *arquivoImagem = fopen(nomeArquivo, "r");
            if (arquivoImagem != NULL) {
                // Agora, passamos o nome do arquivo (nomeArquivo) para a função read_img
                imgb imagem = read_img(nomeArquivo);

                // Aplica o espelhamento horizontal na imagem
                espelharHorizontal(&imagem, *direcao);

                // Cria o nome do novo arquivo com sufixo "_espelhado_horizontal.pgm"
                char novoNomeArquivo[100];  // Ajuste o tamanho conforme necessário

                // Encontrar a última ocorrência de '/' ou '\' na linha (se existir)
                char *barra = strrchr(nomeArquivo, '/');
                char *barraInvertida = strrchr(nomeArquivo, '\\');
                char *ultimaBarra = barra > barraInvertida ? barra : barraInvertida;

                char *nomeSemPath = ultimaBarra != NULL ? ultimaBarra + 1 : nomeArquivo;

                // Encontrar a última ocorrência de '.' no nome (se existir)
                char *extensao = strrchr(nomeSemPath, '.');
                if (extensao != NULL) {
                    // Calcular o comprimento do nome do arquivo sem a extensão
                    size_t tamanhoNomeSemExtensao = extensao - nomeSemPath;

                    // Copiar o nome do arquivo sem a extensão para novoNomeArquivo
                    strncpy(novoNomeArquivo, nomeSemPath, tamanhoNomeSemExtensao);
                    novoNomeArquivo[tamanhoNomeSemExtensao] = '\0';

                    // Adicionar "_espelhado_horizontal.pgm" ao final do novoNomeArquivo
                    strncat(novoNomeArquivo, "_espelhado_horizontal.pgm", sizeof(novoNomeArquivo) - tamanhoNomeSemExtensao - 1);
                } else {
                    // Caso não haja extensão, simplesmente adiciona "_espelhado_horizontal.pgm"
                    snprintf(novoNomeArquivo, sizeof(novoNomeArquivo), "%s_espelhado_horizontal.pgm", nomeSemPath);
                }

                // Abre o novo arquivo para escrita
                FILE *novoArquivoImagem = fopen(novoNomeArquivo, "w");
                if (novoArquivoImagem != NULL) {
                    // Escreve os dados da imagem espelhada horizontalmente no novo arquivo
                    fprintf(novoArquivoImagem, "P2\n");
                    fprintf(novoArquivoImagem, "%d %d\n", imagem.w, imagem.h);
                    fprintf(novoArquivoImagem, "%d\n", imagem.cinza);

                    for (int i = 0; i < imagem.h; i++)
                        for (int j = 0; j < imagem.w; j++)
                            fprintf(novoArquivoImagem, "%d ", imagem.pixel[i * imagem.w + j]);

                    // Libera a memória da imagem
                    free_imgb(&imagem);

                    // Fecha o novo arquivo da imagem
                    fclose(novoArquivoImagem);
                } else {
                    printf("Erro ao criar o novo arquivo da imagem %s.\n", novoNomeArquivo);
                }

                // Fecha o arquivo da imagem original
                fclose(arquivoImagem);
            } else {
                printf("Erro ao abrir o arquivo da imagem %s para leitura.\n", nomeArquivo);
            }
        } else {
            printf("Erro ao ler nome do arquivo: %s\n", linha);
        }
    }

    // Fecha o arquivo da lista
    fclose(arquivoLista);
    printf("Espelhamento feito com sucesso! \n");
}
