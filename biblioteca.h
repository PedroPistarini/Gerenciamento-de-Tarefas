#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>

// O Time deverá elaborar um Sistema de Gerenciamento de Tarefas 
// Datas 
typedef struct {

    int dia;
    int mes;
    int ano;

}Data; 

// Tarefa
typedef struct tarefa{

    int cod_tarefa;
    char nome[30], projeto[30];
    Data inicio;
    Data termino;
    int status;

}Tarefa;

// No
typedef struct Nos{

    Tarefa * tarefa;
    struct Nos* prox_tarefa;

}No;

// Definindo Lista
typedef No Lista; 

// Estrutura da fila, começo e final
typedef struct Fila{

    No* ini;
    No* fim;

} Fila;

void enter_continua()
{
    printf("\n\nPressione Enter para continuar...");
    fflush(stdin);
    getchar();
    system("cls");
}

Fila* criaFila() 
{
    Fila* f = (Fila*)malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

Lista* criaLista(){
    Lista *l = (Lista*)malloc(sizeof(Lista));
    l->tarefa = NULL;
    l->prox_tarefa = NULL;
    return l;
}

Tarefa* criaTarefa ()
{
    Tarefa* tarefas = (Tarefa*)malloc(sizeof(Tarefa));

    printf("\t\n Criacao de tarefas! ");

    printf("\n Codigo da tarefa: ");
    scanf("%d", &tarefas->cod_tarefa);

    printf("\n Nome da Tarefa: ");
    fflush(stdin);
    gets(tarefas->nome);

    printf("\n Nome do Projeto: ");
    fflush(stdin);
    gets(tarefas->projeto);

    printf("\n Data de inicio: ");

    scanf("%d", &tarefas->inicio.dia);printf(" Mes: ");
    scanf("%d", &tarefas->inicio.mes);printf(" Ano: ");
    scanf("%d", &tarefas->inicio.ano);

    printf("\n Data de termino: ");
    scanf("%d", &tarefas->termino.dia);printf(" Mes: ");
    scanf("%d", &tarefas->termino.mes);printf(" Ano: ");
    scanf("%d", &tarefas->termino.ano);
    
    printf(" \n Status do projeto - [1] atrasado - [0] em dia - [-1] pendente: ");
    scanf("%d", &tarefas->status);

    return tarefas;
}

void alteraTarefa(Tarefa* tarefas){

    int n;

    printf("\n [01] Codigo da tarefa!");
    printf("\n [02] Nome da Tarefa!");
    printf("\n [03] Nome do Projeto!");
    printf("\n [04] Data de inicio!");
    printf("\n [05] Data de termino!");
    printf("\n [06] Status do projeto - [1] atrasado - [0] em dia - [-1] pendente!");

    do{ 
        printf("\t\n\n Qual deseja alterar:  ");
        scanf("%d",&n);
    } while (n < 1 || n > 6);
    
    switch (n){

        case 1:
            printf("\n Codigo da tarefa: ");
            scanf("%d", &tarefas->cod_tarefa);
        break;

        case 2: 
            printf("\n Nome da Tarefa: ");
            fflush(stdin);
            gets(tarefas->nome);
        break;

        case 3:
            printf("\n Nome do Projeto: ");
            fflush(stdin);
            gets(tarefas->projeto);
        break;

        case 4: 
            printf("\n Data de inicio: ");
            scanf("%d", &tarefas->inicio.dia);printf(" Mes: ");
            scanf("%d", &tarefas->inicio.mes);printf(" Ano: ");
            scanf("%d", &tarefas->inicio.ano);
        break;

        case 5:
            printf("\n Data de termino: ");
            scanf("%d", &tarefas->termino.dia);printf(" Mes: ");
            scanf("%d", &tarefas->termino.mes);printf(" Ano: ");
            scanf("%d", &tarefas->termino.ano);
        break;
        
        case 6:
            printf(" \n Status do projeto - [1] atrasado - [0] em dia - [-1] pendente: ");
            scanf("%d", &tarefas->status);
        break;

        default:
            printf("\n\n ERRO:  Digite de 1 a 6!");
        break;
    } 
}

void insereFila_tarefa (Fila* f, Tarefa* tarefa){

    No* nova_tarefa = (No*) malloc(sizeof(No));

    nova_tarefa->tarefa = tarefa;
    nova_tarefa->prox_tarefa = NULL;

    if (f->ini == NULL) {
        f->ini = f->fim = nova_tarefa;
    } else {
        f->fim->prox_tarefa = nova_tarefa;
        f->fim = nova_tarefa;
    }
}

void imprime_tarefa (Tarefa* T){

    printf("\n\n");
    printf("\t\n Codigo da tarefa: %d", T->cod_tarefa);
    printf("\t\n Nome da Tarefa: %s", T->nome);
    printf("\t\n Nome do Projeto: %s", T->projeto);
    printf("\t\n Data de inicio: %02d / %02d / %04d ", T->inicio.dia, T->inicio.mes, T->inicio.ano);
    printf("\t\n Data de Termino: %02d / %02d / %04d", T->termino.dia, T->termino.mes, T->termino.ano);
    printf("\t\n Status do projeto - [1] atrasado - [0] em dia - [-1] pendente: %d ", T->status);
 
}

void imprime_tarefa_concluida (Tarefa* T){
    
    time_t tempoAtual;
    struct tm *infoTempo;

    // Obtém o tempo atual
    time(&tempoAtual);
    
    // Converte o tempo atual em uma estrutura de informações de tempo local
    infoTempo = localtime(&tempoAtual);

    // Obtém o dia, mês e ano do tempo atual
    int dia = infoTempo->tm_mday;
    int mes = infoTempo->tm_mon + 1;  // O mês é baseado em zero, então adicionamos 1
    int ano = infoTempo->tm_year + 1900;  // O ano começa em 1900

    printf("\n\n");
    printf("\t\n Codigo da tarefa: %d", T->cod_tarefa);
    printf("\t\n Nome da Tarefa: %s", T->nome);
    printf("\t\n Nome do Projeto: %s", T->projeto);
    printf("\t\n Data de inicio: %02d / %02d / %04d ", T->inicio.dia, T->inicio.mes, T->inicio.ano);
    printf("\t\n Data de Termino: %02d / %02d / %04d", dia, mes, ano);
    printf("\t\n Status do projeto - [1] atrasado - [0] em dia - [-1] pendente [2] Concluida: %d ", 2);

}

void imprime_fila(Fila* F) {
    No* aux = F->ini;

    while (aux != NULL) {
        imprime_tarefa(aux->tarefa);
        aux = aux->prox_tarefa;
    }
}

void imprime_lista(Lista* pendente)
{
    No* aux = pendente;

    while (aux != NULL) {
        imprime_tarefa(aux->tarefa);
        aux = aux->prox_tarefa;
    }
}

void imprime_lista_concluida(Lista* L)
{
    No* aux = L;

    while (aux != NULL) {

        imprime_tarefa_concluida(aux->tarefa);
        aux = aux->prox_tarefa;
    }
}

void imprime_com_sem_atraso(Lista* concluido)
{
    No* aux = concluido;

    while (aux != NULL)
    {
        if(aux->tarefa->status == 1)
        {
            printf("\n\n Tarefa com atraso -> ");
            imprime_tarefa_concluida(aux->tarefa);
        }
        else
        {
            printf("\n\n\n Tarefa sem atraso -> ");
            imprime_tarefa_concluida(aux->tarefa);
        }

        aux = aux->prox_tarefa;
    }   
}

void impressao_de_listas(Lista* concluido, Lista* pendente)
{
    int n;
    
    printf("\n\n Impressao de Listas\n");
    
    printf("\n [1] Lista de Tarefas Pendentes!");
    printf("\n [2] Lista de Tarefas Concluidas!");
    printf("\n [3] Lista de Tarefas Concluidas com ou sem atraso");
    printf("\n [4] Imprimir todas as listas!");

    do{
    printf("\n\n Qual deseja imprimir -> ");
    scanf("%d", &n);
    }while(n < 1 || n > 4);

    switch(n)
    {
        case 1: 
            imprime_lista(pendente);
        break;

        case 2: 
            imprime_lista_concluida(concluido);
        break;

        case 3: 
            imprime_com_sem_atraso(concluido);
        break;

        case 4:
            printf("\n\n Lista Pendente ->");
            imprime_lista(pendente);

            printf("\n Lista Concluida -> ");
            imprime_lista_concluida(concluido);

            printf("\n\n Lista Concluida Com ou sem Atraso -> ");
            imprime_com_sem_atraso(concluido);

        break;

        default:
        break;
    }
}

void modificarTarefa(Fila* f) {

    int codigo;
    printf("\nDigite o codigo da tarefa que deseja modificar: ");
    scanf("%d", &codigo);

    No* aux = f->ini;

    while (aux != NULL) {
        if (aux->tarefa->cod_tarefa == codigo) {
            printf("\nTarefa encontrada. Digite os novos dados da tarefa:\n");
            
            alteraTarefa(aux->tarefa);

            printf("\nTarefa modificada com sucesso!\n");
        }
        else{
            printf("\nTarefa com codigo %d nao encontrada.\n", codigo);
        }
        aux = aux->prox_tarefa;
    }
}

void joga_para_lista(Fila* fila, Lista* lista) {

    if (fila->ini != NULL) {
        No* aux = fila->ini;
        fila->ini = fila->ini->prox_tarefa; // Atualiza o ponteiro ini da fila

        aux->prox_tarefa = NULL; // Desconecta o nó da fila
        if (lista->tarefa == NULL) {
            lista->tarefa = aux->tarefa;
            lista->prox_tarefa = NULL;
        } else {
            No* percorre = lista;
            while (percorre->prox_tarefa != NULL) {
                percorre = percorre->prox_tarefa;
            }
            percorre->prox_tarefa = aux;
        }
    }
}

void concluirTarefa(Fila* f, Lista* concluido) {

    int codigo;
    printf("\nDigite o codigo da tarefa que deseja concluir: ");
    scanf("%d", &codigo);

    if(f->ini->tarefa->cod_tarefa == codigo)
    {
        joga_para_lista(f, concluido);
        //concluido->tarefa->status = 2;
        printf("\n\n Tarefa concluida com sucesso!\n");
    }
    else
    printf("\nTarefa com codigo %d nao encontrada.\n", codigo);
}

void atualizacao_status(Fila* f, Lista* pendente)
{
    time_t tempoAtual;
    struct tm *infoTempo;

    // Obtém o tempo atual
    time(&tempoAtual);
    
    // Converte o tempo atual em uma estrutura de informações de tempo local
    infoTempo = localtime(&tempoAtual);

    // Obtém o dia, mês e ano do tempo atual
    int dia = infoTempo->tm_mday;
    int mes = infoTempo->tm_mon + 1;  // O mês é baseado em zero, então adicionamos 1
    int ano = infoTempo->tm_year + 1900;  // O ano começa em 1900

    No* aux = f->ini;

    while (aux != NULL)
    {
        if(ano > aux->tarefa->termino.ano || mes > aux->tarefa->termino.mes || dia > aux->tarefa->termino.dia) 
        {
            aux->tarefa->status = -1;
            joga_para_lista(f, pendente);
            printf("\n\n Status Atualizado com Sucesso! ");
        }

        aux = aux->prox_tarefa;
    }
}
