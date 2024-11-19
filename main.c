#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHAVE_CRIPTOGRAFIA 12345  // Valor fixo para criptografar e descriptografar
#define MULTIPLICADOR 8



typedef struct no {
    struct no * proximo;
    char tipoProduto[50];
    char tipoProcesso[50];
    char data[20];
    char local[50];
    char destino[50];
} No;


typedef struct procReci {
    No *listaP; // Armazena o ponteiro para o início da lista de cada processo de reciclagem.
    struct procReci *proximoP; // Ponteiro para o próximo processo na lista de processos
} ProcReci;



// Função para criptografar um endereço
unsigned long criptografarEndereco(void* endereco) {
    return ((unsigned long)endereco * MULTIPLICADOR) + CHAVE_CRIPTOGRAFIA;
}


// Função para descriptografar o endereço
void* descriptografarEndereco(unsigned long enderecoCriptografado) {
    return (void*)((enderecoCriptografado - CHAVE_CRIPTOGRAFIA) / MULTIPLICADOR);
}


// Função para iniciar uma lista de processos vazia
ProcReci* inicia() {
    return NULL;
}


// Função para iniciar um novo processo e encadeá-lo na lista de processos
ProcReci* novoPsso(ProcReci* listaProcessos) {
    ProcReci* novoProc;
    novoProc = (ProcReci*) malloc(sizeof(ProcReci));   // aloca um espaço na memória
    novoProc->listaP = NULL;
    novoProc->proximoP = listaProcessos;

    return novoProc;
}




// Função de inserção
No* insere(No* listaP) {
    system("clear"); // limpa o console
   
    No* novoNo;
    novoNo = (No*) malloc(sizeof(No)); // aloca um espaço na memória, com tamanho de um nó
    novoNo->proximo = listaP;
   
    printf("=============== Cadastro de Produto ================");
    printf("\n Nó do registro alocado no endereço: %p \n", (void*)novoNo);
    printf("====================================================\n\n");


    printf("Digite o tipo do produto: ");
    fgets(novoNo->tipoProduto, 50, stdin);
    novoNo->tipoProduto[strcspn(novoNo->tipoProduto, "\n")] = '\0';  // Remove '\n'


    printf("Digite a etapa do processo: ");
    fgets(novoNo->tipoProcesso, 50, stdin);
    novoNo->tipoProcesso[strcspn(novoNo->tipoProcesso, "\n")] = '\0';  // Remove '\n'


    printf("Digite a data (DD/MM/AAAA): ");
    fgets(novoNo->data, 20, stdin);
    novoNo->data[strcspn(novoNo->data, "\n")] = '\0';  // Remove '\n'


    printf("Digite o local: ");
    fgets(novoNo->local, 50, stdin);
    novoNo->local[strcspn(novoNo->local, "\n")] = '\0';  // Remove '\n'


    printf("Digite o destino: ");
    fgets(novoNo->destino, 50, stdin);
    novoNo->destino[strcspn(novoNo->destino, "\n")] = '\0';  // Remove '\n'
   
   
    printf("\n=============== Nó concluido ======================\n \n\n\n\n");
   
    return novoNo;
}


// Função para rastrear um nó específico pelo endereço
void rastrearPorEndereco(ProcReci* lista) {
    char enderecoStr[20];
    printf("========================================================================\n");
    printf("Digite o endereco alocado do nó (em formato hexadecimal): ");
    scanf("%s", enderecoStr);
    getchar();
   
    // Converte o endereço criptografado da string para unsigned long
    unsigned long enderecoCriptografado = strtoul(enderecoStr, NULL, 16);


    // Descriptografa para obter o endereço real
    ProcReci* processoProcurado = (ProcReci*) descriptografarEndereco(enderecoCriptografado);
   
    ProcReci* auxProc = lista; // recebe a lista com os processos inseridos
   
    int found = 0;
   
    while (auxProc != NULL) { // enquanto houver processos
        if (auxProc == processoProcurado) { // se for igual ao procurdo
            found = 1;
            break;
        }
        auxProc = auxProc->proximoP;
    }
   
    if (found) {
        printf("==============================================\n");
        printf("Produto encontrado no endereco %p:\n", (void*)auxProc);
        printf("==============================================\n");
        No* aux = auxProc->listaP; // Recebe uma lista com os registros
        No* anterior = NULL;
       
        // Se anterior não for NULL, verifica se o ponteiro "proximo" do nó anterior é igual ao endereço do nó atual
        if (anterior != NULL && anterior->proximo != aux) {
            printf("Erro de integridade: o nó no endereço %p não aponta corretamente para o próximo nó.\n", (void*)anterior);
            return;
        }
       
        while (aux != NULL) {
            printf("Produto: %s\n", aux->tipoProduto);
            printf("Etapa: %s\n", aux->tipoProcesso);
            printf("Data: %s\n", aux->data);
            printf("Local: %s\n", aux->local);
            printf("Destino: %s\n", aux->destino);
            printf("Endereço: %p\n", (void*)aux);
            printf("==============================================\n\n");
           
            anterior = aux;  // Move para o próximo nó
            aux = aux->proximo;
        }
    } else {
        printf("Nó não encontrado com o endereço fornecido.\n");
    }
}






void menuInicial() {
    printf("\n=============  Menu  ============= \n");
    printf("1 - Iniciar processo de reciclagem\n");
    printf("2 - Rastrear processo concluido\n");
    printf("0 - Sair\n");
    printf("================================== \n");
    printf("Escolha uma opcao: ");
}


int menuNoConc(int sn) {
    printf("========== Deseja continuar ou finalizar? ==========\n");
    printf("1 - Continuar adicionando etapas\n");
    printf("2 - Finalizar o processo\n");
    printf("====================================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &sn);
    getchar();  // Consumir o '\n' deixado pelo scanf
   
    return sn;
}


int main(void) {
    ProcReci* listaProcessos;
    listaProcessos = inicia(); // lista começa vazia (NULL)
   
    ProcReci* processoAtual = NULL;
    int option;
   
   
    while (1) {
        menuInicial();
        scanf("%d", &option);
        getchar();  // Consumir o '\n' deixado pelo scanf
       
        // Inicia um novo processo de reciclagem
        if (option == 1) {
       
            processoAtual = novoPsso(listaProcessos);
            listaProcessos = processoAtual;  // Atualiza o novo processo na lista de processos
           
            int sn = 1;
           
            while (sn == 1) {
                processoAtual->listaP = insere(processoAtual->listaP);
                sn = menuNoConc(sn);
            }
            if (sn == 2) {
               
                unsigned long enderecoCriptografado = criptografarEndereco(processoAtual); // criptografa o endereço
                system("clear");
                printf("==================== Cadastro Encerrado =====================");
                printf("\nProcesso registrado, seu códgio criptografato é: %lx \n", enderecoCriptografado);
                printf("\nProcesso registrado, seu endereço registrado é: %p \n", (void*)processoAtual);
                printf("=============================================================\n\n");
               // printf("Cadastro Encerrado, seu códgio de rastreio é: \n %p", );
            }


        }
       
        // rastrear processo
        else if (option == 2) {
            system("clear");
            rastrearPorEndereco(listaProcessos);
         
        }
        else if (option == 0) {
            system("clear");
            printf("encerrando programa...");
            break;
        }
    }
}
