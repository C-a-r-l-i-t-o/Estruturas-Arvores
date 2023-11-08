#include <stdio.h>
#include <stdlib.h>

// Definindo o registro que representará
// cada elemento da árvore binária
struct ARVORE {
    int num;
    struct ARVORE *esq, *dir;
};

// Função para inserir um nó na árvore
struct ARVORE *inserir(struct ARVORE *raiz, int numero) {
    if (raiz == NULL) {
        struct ARVORE *novo = (struct ARVORE *)malloc(sizeof(struct ARVORE));
        novo->num = numero;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }

    if (numero < raiz->num) {
        raiz->esq = inserir(raiz->esq, numero);
    } else if (numero > raiz->num) {
        raiz->dir = inserir(raiz->dir, numero);
    }

    return raiz;
}

// Função para consultar um nó na árvore
int consultar(struct ARVORE *raiz, int numero) {
    if (raiz == NULL) {
        return 0; // Nó não encontrado
    }

    if (numero == raiz->num) {
        return 1; // Nó encontrado
    }

    if (numero < raiz->num) {
        return consultar(raiz->esq, numero);
    } else {
        return consultar(raiz->dir, numero);
    }
}

// Função para listar os elementos da árvore em ordem
void listarEmOrdem(struct ARVORE *raiz) {
    if (raiz != NULL) {
        listarEmOrdem(raiz->esq);
        printf("%d ", raiz->num);
        listarEmOrdem(raiz->dir);
    }
}

// Função para excluir um nó da árvore
struct ARVORE *remover(struct ARVORE *raiz, int numero) {
    if (raiz == NULL) {
        return raiz;
    }

    if (numero < raiz->num) {
        raiz->esq = remover(raiz->esq, numero);
    } else if (numero > raiz->num) {
        raiz->dir = remover(raiz->dir, numero);
    } else {
        // Nó com um ou nenhum filho
        if (raiz->esq == NULL) {
            struct ARVORE *temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            struct ARVORE *temp = raiz->esq;
            free(raiz);
            return temp;
        }

        // Nó com dois filhos: obtem o sucessor in-order (menor nó à direita)
        struct ARVORE *temp = raiz->dir;
        while (temp->esq != NULL) {
            temp = temp->esq;
        }

        // Copia o conteúdo do sucessor para este nó
        raiz->num = temp->num;

        // Remove o sucessor
        raiz->dir = remover(raiz->dir, temp->num);
    }
    return raiz;
}

// Função para desalocar a árvore e liberar a memória
struct ARVORE *desalocar(struct ARVORE *raiz) {
    if (raiz != NULL) {
        raiz->esq = desalocar(raiz->esq);
        raiz->dir = desalocar(raiz->dir);
        free(raiz);
    }
    return NULL;
}

int main() {
    struct ARVORE *raiz = NULL;
    int op, numero;

    do {
        printf("\nMENU DE OPCOES\n");
        printf("1 - Inserir na arvore\n");
        printf("2 - Consultar um no da arvore\n");
        printf("3 - Consultar toda a arvore em ordem\n");
        printf("4 - Excluir um no da arvore\n");
        printf("5 - Esvaziar a arvore\n");
        printf("6 - Sair\n");
        printf("Digite sua opcao: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                printf("\nDigite o numero a ser inserido na arvore: ");
                scanf("%d", &numero);
                raiz = inserir(raiz, numero);
                printf("Numero inserido na arvore!\n");
                break;
            case 2:
                if (raiz == NULL) {
                    printf("\nArvore vazia!\n");
                } else {
                    printf("\nDigite o elemento a ser consultado: ");
                    scanf("%d", &numero);
                    if (consultar(raiz, numero)) {
                        printf("Numero encontrado na arvore!\n");
                    } else {
                        printf("Numero nao encontrado na arvore!\n");
                    }
                }
                break;
            case 3:
                if (raiz == NULL) {
                    printf("\nArvore vazia!\n");
                } else {
                    printf("\nListando todos os elementos da arvore em ordem:\n");
                    listarEmOrdem(raiz);
                    printf("\n");
                }
                break;
            case 4:
                if (raiz == NULL) {
                    printf("\nArvore vazia!\n");
                } else {
                    printf("\nDigite o numero que deseja excluir: ");
                    scanf("%d", &numero);
                    if (consultar(raiz, numero)) {
                        raiz = remover(raiz, numero);
                        printf("Numero excluido da arvore!\n");
                    } else {
                        printf("Numero nao encontrado na arvore!\n");
                    }
                }
                break;
            case 5:
                if (raiz == NULL) {
                    printf("\nArvore vazia!\n");
                } else {
                    raiz = desalocar(raiz);
                    printf("\nArvore esvaziada!\n");
                }
                break;
            case 6:
                raiz = desalocar(raiz); // Liberar memória antes de sair
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (op != 6);

    return 0;
}

