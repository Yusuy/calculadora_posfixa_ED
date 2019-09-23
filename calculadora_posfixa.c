/**UnB - Universidade de Brasília**/
/**Estudante: Victor Gabriel Rodrigues de Almeida**/
/**Matrícula: 14/0052399**/



#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
    char sim;
    double num;
    struct elemento *proximo;
}t_elemento;

typedef struct lista{
    t_elemento *primeiro;
    t_elemento *ultimo;
}t_lista;

typedef struct pilha{
    t_lista *l;
}t_pilha;


/********************************************************************************************************/
/****************************************** --- Lista --- ***********************************************/
/********************************************************************************************************/

t_lista *criarLista(){
   t_lista *l = (t_lista *)malloc(sizeof(t_lista));
   l->primeiro = NULL;
   l->ultimo = NULL;
   return l;
}

void insereInicioChar(char valor, t_lista *l){
    t_elemento *novoprimeiro = (t_elemento *)malloc(sizeof(t_elemento));
    novoprimeiro->sim = valor;
    novoprimeiro->proximo = l->primeiro;
    l->primeiro = novoprimeiro;
    if(l->ultimo == NULL){
        l->ultimo = novoprimeiro;
    }
}

void insereInicioNum(double valor, t_lista *l){
    t_elemento *novoprimeiro = (t_elemento *)malloc(sizeof(t_elemento));
    novoprimeiro->num = valor;
    novoprimeiro->sim = 'x';
    novoprimeiro->proximo = l->primeiro;
    l->primeiro = novoprimeiro;
    if(l->ultimo == NULL){
        l->ultimo = novoprimeiro;
    }
}

void insereFinalChar(char valor, t_lista *l){
   t_elemento *novoultimo = (t_elemento *)malloc(sizeof(t_elemento));
   novoultimo->sim = valor;
   novoultimo->proximo = NULL;
   if(l->primeiro == NULL){
      l->primeiro = novoultimo;
   }else{
     l->ultimo->proximo = novoultimo;
   }
   l->ultimo = novoultimo;
}

void insereFinalNum(double valor, t_lista *l){
   t_elemento *novoultimo = (t_elemento *)malloc(sizeof(t_elemento));
   novoultimo->num = valor;
   novoultimo->sim = 'x';
   novoultimo->proximo = NULL;
   if(l->primeiro == NULL){
      l->primeiro = novoultimo;
   }else{
     l->ultimo->proximo = novoultimo;
   }
   l->ultimo = novoultimo;
}

int estaVazia(t_lista *l){
    if(l->primeiro == NULL){
       return 1;
    }
    return 0;
}

int removeInicioChar(t_lista *l){
    if(estaVazia(l)){
        return -1;
    }
    char tmp = l->primeiro->sim;
    t_elemento *removido = l->primeiro;
    l->primeiro = l->primeiro->proximo;
    free(removido);
    if(l->primeiro == NULL){
       l->ultimo = NULL;
    }
    return tmp;
}

double removeInicioNum(t_lista *l){
    if(estaVazia(l)){
        return -1;
    }
    double tmp = l->primeiro->num;
    t_elemento *removido = l->primeiro;
    l->primeiro = l->primeiro->proximo;
    free(removido);
    if(l->primeiro == NULL){
       l->ultimo = NULL;
    }
    return tmp;
}

void esvaziarLista(t_lista *l){
    while(l->primeiro != NULL){
        removeInicioChar(l);
    }
    free(l);
}

void imprimirListaChar(t_lista *l){
    t_elemento *atual = l->primeiro;

    printf("\n");
    while(atual != NULL){
          printf("%c",atual->sim);
          atual = atual->proximo;
    }
}


/********************************************************************************************************/
/********************************************* --- Pilha --- ********************************************/
/********************************************************************************************************/

t_pilha *criarPilha(){
   t_pilha *p =  (t_pilha *)malloc(sizeof(t_pilha));
   p->l = criarLista();
   return p;
}

void empilharChar(char caractere, t_pilha *p){
  insereInicioChar(caractere, p->l);
}

void empilharNum(double numero, t_pilha *p){
  insereInicioNum(numero, p->l);
}

char desempilharChar(t_pilha *p){
  return removeInicioChar(p->l);
}

double desempilharNum(t_pilha *p){
  return removeInicioNum(p->l);
}

int estaVaziaPilha(t_pilha *p){
    return estaVazia(p->l);
}

void imprimirPilhaChar(t_pilha *p){
    t_elemento *atual = p->l->primeiro;

    if (p->l == NULL){
        printf("\nPilha Vazia!\n");
    }
    else{
        printf("\n");
        while(atual != NULL){
            printf("%c",atual->sim);
            atual = atual->proximo;
        }
    }
}


/********************************************************************************************************/
/***************************************** --- Operações --- ********************************************/
/********************************************************************************************************/

/**Funçao que lê expressao apenas com caracteres e salva em uma lista**/
t_lista *lerExpressao(){
    char n;
    t_lista *expressao = criarLista();

    while(n != '\n'){
        scanf("%c", &n);
        if(n == '\n'){
            break;
        }
        if(n == '+' || n == '-' || n == '*' || n == '/' || n == '(' || n == ')' || n == '0' || n == '1'  || n == '2' || n == '3' || n == '4' || n == '5' || n == '6' || n == '7' || n == '8' || n == '9' ){
            insereFinalChar(n, expressao);
        }
    }

    return expressao;
}

/**Funçao auxiliar para andar numeros (caractere) da lista (é usada na funçao listaCharNum)**/
int passaNum(t_elemento *num){
    while(num!=NULL){
        if(num->sim == '0' || num->sim == '1' || num->sim == '2' || num->sim == '3' || num->sim == '4' || num->sim == '5' || num->sim == '6' || num->sim == '7' || num->sim == '8' || num->sim == '9'){
            num = num->proximo;
        }
        else{
            break;
        }
    }

    return num;
}

/**Funçao que retorna numero (double)**/
double pegaNum(t_elemento *num){
    char numero[50];
    t_elemento *atual = num;
    t_elemento *proximo;
    int i = 1;
    numero[0] = atual->sim;
    proximo = atual->proximo;
    double valor;

    atual = atual->proximo;
    while(atual != NULL){
        if(atual->sim == '0' || atual->sim == '1' || atual->sim == '2' || atual->sim == '3' || atual->sim == '4' || atual->sim == '5' || atual->sim == '6' || atual->sim == '7' || atual->sim == '8' || atual->sim == '9'){
            numero[i] = atual->sim;
        }

        else{
            break;
        }

        atual = atual->proximo;
        i++;
    }

    valor = atol(numero);
    return valor;
}

/**Funçao que reorganiza a expressao, de forma a facilitar calculo**/
void reorganizarExpressao(t_lista *l){
    t_elemento *excluido = l->primeiro;
    t_elemento *anterior;
    t_elemento *atual;
    t_elemento *proximo;
    int i = 0;

    if(l->primeiro != NULL){
        anterior = l->primeiro;
    }

    while(excluido->proximo != NULL){
        if(excluido != NULL){

            if(excluido->sim == '-' && excluido->proximo->sim == '-'){
                //printf("\nCaso --\n");
                if(excluido == l->primeiro){
                    excluido->proximo->sim = '+';
                    l->primeiro = excluido->proximo;
                }
                else{
                    excluido->proximo->sim = '+';
                    anterior->proximo = excluido->proximo;
                }
                free(excluido);
                break;
            }
            else if(excluido->sim == '+' && excluido->proximo->sim == '+'){
                //printf("\nCaso ++\n");
                if(excluido == l->primeiro){
                    excluido->proximo->sim = '+';
                    l->primeiro = excluido->proximo;
                }
                else{
                    excluido->proximo->sim = '+';
                    anterior->proximo = excluido->proximo;
                }
                free(excluido);
                break;
            }
            else if(excluido->sim == '+' && excluido->proximo->sim == '-'){
                //printf("\nCaso +-\n");
                if(excluido == l->primeiro){
                    excluido->proximo->sim = '-';
                    l->primeiro = excluido->proximo;
                }
                else{
                    excluido->proximo->sim = '-';
                    anterior->proximo = excluido->proximo;
                }
                free(excluido);
                break;
            }
            else if(excluido->sim == '-' && excluido->proximo->sim == '+'){
                //printf("\nCaso -+\n");
                if(excluido == l->primeiro){
                    excluido->proximo->sim = '-';
                    l->primeiro = excluido->proximo;
                }
                else{
                    excluido->proximo->sim = '-';
                    anterior->proximo = excluido->proximo;
                }
                free(excluido);
                break;//Terminar aqui, corrigir o loop
            }
        }
        anterior = excluido;
        excluido = excluido->proximo;
    }

    atual = l->primeiro;
    proximo = atual->proximo;
    while(atual->proximo != NULL){
        if(atual != NULL){
            if(atual->sim == '0' || atual->sim == '1' || atual->sim == '2' || atual->sim == '3' || atual->sim == '4' || atual->sim == '5' || atual->sim == '6' || atual->sim == '7' || atual->sim == '8' || atual->sim == '9' || atual->sim == ')'){
                if(proximo->sim == '('){
                    t_elemento *novo = (t_elemento *)malloc(sizeof(t_elemento));
                    novo->sim = '*';
                    atual->proximo = novo;
                    novo->proximo = proximo;
                }
            }
        }
        atual = atual->proximo;
        proximo = atual->proximo;
    }

    atual = l->primeiro;
    proximo = atual->proximo;
    while(atual->proximo != NULL){
        if(atual != NULL){
            if(atual->sim == ')'){
                if(proximo->sim == '0' || proximo->sim == '1' || proximo->sim == '2' || proximo->sim == '3' || proximo->sim == '4' || proximo->sim == '5' || proximo->sim == '6' || proximo->sim == '7' || proximo->sim == '8' || proximo->sim == '9' | proximo->sim == '('){
                    t_elemento *novo = (t_elemento *)malloc(sizeof(t_elemento));
                    novo->sim = '*';
                    atual->proximo = novo;
                    novo->proximo = proximo;
                }
            }
        }
        atual = atual->proximo;
        proximo = atual->proximo;
    }

    //imprimirListaChar(l);

    i=0;
    atual = l->primeiro;
    proximo = atual->proximo;
    while(proximo!=NULL){
        if(proximo != NULL){
            if(atual->sim == '-' && proximo->sim == '-'){
                i++;
            }
            else if(atual->sim == '+' && proximo->sim == '-'){
                i++;
            }
            else if(atual->sim == '-' && proximo->sim == '+'){
                i++;
            }
            else if(atual->sim == '+' && proximo->sim == '+'){
                i++;
            }
        }
        atual = atual->proximo;
        proximo = atual->proximo;
    }
    if(i!=0){
        reorganizarExpressao(l);
    }
}

/**Funçao que transforma a lista interamente de chars em lista com doubles e chars**/
int listaCharNum(t_lista *l){

    t_lista *equacao = criarLista();
    t_elemento *atual = l->primeiro;
    double valor;
    char n;

    insereFinalNum(0, equacao);

    if(atual->sim == '-'){
        insereFinalChar('-', equacao);
    }
    else{
        insereFinalChar('+', equacao);
    }

    if(atual->sim == '-' || atual->sim == '+'){
        atual = atual->proximo;
    }
    //printf("Simbolo 3: %c", atual->sim);

    while(atual!=NULL){
        if(atual == NULL){
                break;
        }

        else if(atual->sim == '-' || atual->sim == '+' || atual->sim == '/' || atual->sim == '*' || atual->sim == '(' || atual->sim == ')'){
            insereFinalChar(atual->sim, equacao);
            atual = atual->proximo;
        }

        else{
            valor = pegaNum(atual);
            //printf("Numero %d", valor);
            insereFinalNum(valor, equacao);
            atual = passaNum(atual);
        }
    }

    esvaziarLista(l);
    return equacao;
}

/**Funçao que checa a validade da expressao**/
int checarValidade(t_lista *expressao){
    t_pilha *pilha = criarPilha();
    t_elemento *caractere = expressao->primeiro;
    int j = 0, sinal = 0;

    if(expressao == NULL || expressao->primeiro->sim == '*' || expressao->primeiro->sim == '/'){
        return 0;
    }

    while(caractere!=NULL){
        if(caractere == NULL){
        break;
        }
        if(caractere->sim == '('){
            empilharChar(caractere->sim, pilha);
        }
        caractere = caractere->proximo;
    }

//    imprimirPilhaChar(pilha);

    caractere = expressao->primeiro;
    while(caractere!=NULL){
        if(caractere->sim == '('){
            j++;
        }
        else if(caractere->sim == ')' && j != 0){
            if(caractere->proximo!=NULL){
                if(caractere->proximo->sim != '('){
                    desempilharChar(pilha);
                    j--;
                }
            }
            else{
                desempilharChar(pilha);
                j--;
            }
        }
        //printf("%d[%c] - ", j, caractere->sim);
        caractere = caractere->proximo;
    }

    caractere = expressao->primeiro;
    while(caractere!=NULL){
        if(caractere->proximo == NULL){
            if(caractere->sim == '+' || caractere->sim == '*' || caractere->sim == '/' || caractere->sim == '-'){
                sinal++;
            }
        }
        else if(caractere->proximo!=NULL){
            if(caractere->sim == '+' || caractere->sim == '*' || caractere->sim == '/' || caractere->sim == '-'){
                if(caractere->proximo->sim == '*' || caractere->proximo->sim == '/'){
                    sinal++;
                }
            }
                else if (caractere->sim == '(' && caractere->proximo->sim == ')'){
                    sinal++;
                }
        }

        caractere = caractere->proximo;
    }

    caractere = expressao->primeiro;
    while(caractere!=NULL){
         if(caractere->sim == '*' || caractere->sim == '/'){
            if(caractere->proximo->sim == '*' || caractere->proximo->sim == '/' || caractere->proximo->sim == '+' || caractere->proximo->sim == '-'){
                    sinal++;
            }
        }
         caractere = caractere->proximo;
     }

    caractere = expressao->primeiro;
    while(caractere!=NULL){
        if(caractere->sim == '('){
            sinal++;
        }
        else if(caractere->sim == ')'){
            sinal--;
        }
        else if(caractere->sim == '/' && caractere->proximo->num == 0){
            sinal++;
        }
        caractere = caractere->proximo;
    }

    //printf("Sinal: %d", sinal);
    if(estaVaziaPilha(pilha) != 1 || sinal!=0){
        return 0;
    }
}

/**Funçao que imprime equação com doubles e chars**/
void imprimirEq(t_lista *l){
    t_elemento *atual = l->primeiro;

    while(atual != NULL){
          if(atual->sim == 'x'){
            printf("%.2lf ", atual->num);
          }
          else{
            printf("%c ", atual->sim);
          }
          atual = atual->proximo;
    }
    printf("\n");
}

/**Função que retorna a prioridade de um operador**/
int prioridadeOperador(char p){
    int pri = 0;

    if (p == '+' || p == '-'){
        pri = 1;
    }
    else if (p == '*' || p == '/'){
        pri = 2;
    }
    else if (p == '('){
        pri = 0;
    }

    return pri;
}

/**Função que retorna resultado de operações parciais**/
double Operacao(double num1, double num2, char operacao){
    double resultado;

    switch(operacao){
        case '+':
            resultado = num2+num1;
            break;

        case '-':
            resultado = num2-num1;
            break;

        case '*':
            resultado = num2*num1;
            break;

        case '/':
            resultado = num2/num1;
            break;
    }

    return resultado;
}

/**Função que retorna forma posfixa de expressao infixa**/
int posfixaEq(t_lista *exp){
    t_pilha *operadores = criarPilha();
    t_lista *posfixa = criarLista();
    t_elemento *atual = exp->primeiro;

    char c;

    while(atual!=NULL){
        if(atual->sim == 'x'){
            insereFinalNum(atual->num, posfixa);
            //printf("\nNumero na pos: %.2lf", atual->num);
        }

        else if(atual->sim == '('){
            empilharChar(atual->sim, operadores);
            //printf("\nEmpilhou: (");
        }

        else if(atual->sim == ')'){
            while(1){
                c = desempilharChar(operadores);

                if(c == '(' || operadores->l->primeiro == NULL){
                    //printf("\nEncontrou: )");
                    break;
                }

                insereFinalChar(c, posfixa);
                //printf("\n()Passou pra pos: %c", c);
            }
        }

        else{
            while(operadores->l->primeiro != NULL && (prioridadeOperador(operadores->l->primeiro->sim) >= prioridadeOperador(atual->sim))){
                c = desempilharChar(operadores);
                insereFinalChar(c, posfixa);
                //printf("\nPassou pra pos: %c", c);
            }
            empilharChar(atual->sim, operadores);
            //printf("\nEmpilhou: %c", atual->sim);
        }
        atual = atual->proximo;
    }

    while(operadores->l->primeiro != NULL){
        c = desempilharChar(operadores);
        insereFinalChar(c, posfixa);
        //printf("\n-Resto-Passou pra pos: %c", c);
    }

    //imprimirEq(posfixa);
    esvaziarLista(exp);
    return posfixa;

}

/**Função que calcula resultado da expressao na forma posfixa**/
double calcPos(t_lista *pos){
    t_elemento *atual = pos->primeiro;
    t_pilha *resultado = criarPilha();

    char op;
    double num_1, num_2, res;

    while(atual != NULL){
        if(atual->sim == 'x'){
            empilharNum(atual->num, resultado);
        }
        else{
            num_1 = desempilharNum(resultado);
            num_2 = desempilharNum(resultado);
            op = atual->sim;
            res = Operacao(num_1, num_2, op);
            empilharNum(res, resultado);
        }
        atual = atual->proximo;
    }

    res = desempilharNum(resultado);
    return res;

}

/********************************************************************************************************/
/********************************************** --- Main --- ********************************************/
/********************************************************************************************************/

int main (int argc, char *argv[]){

    double resultado = 0;
    t_lista *expressao = lerExpressao();

    //expressaoDouble(equacao);
    reorganizarExpressao(expressao);
    t_lista *equacao = listaCharNum(expressao);

    if(checarValidade(equacao) == 0){
        return printf("\nExpressao Invalida!\n");
    }


    printf("\nEquacao: "); //resultado
    imprimirEq(equacao);
    t_lista *posfixa = posfixaEq(equacao);
    resultado = calcPos(posfixa);
    printf(" = %.2lf", resultado);

    printf("\n\nForma posfixa: ");imprimirEq(posfixa);

}
