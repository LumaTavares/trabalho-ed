#ifndef PATIENT_H
#define PATIENT_H

#include <stdio.h>

typedef struct pacient Pacient;     //Representa a estrutura do paciente.
typedef struct list LinkedList;     // Representa uma lista encadeada.    
typedef struct list_node ListNode;  // Representa um nó em uma lista encadeada. 

LinkedList* ll_create();

char *formatar_cpf(Pacient *patient);

Pacient* new_pacient(int id,LinkedList *l);

Pacient* update_patient(LinkedList *l, int id);

void print_patient(Pacient *patient);

int ll_is_empty(LinkedList *l);

void ll_insert(LinkedList *l, Pacient *pacients);

Pacient* ll_is_in(LinkedList *l, int v);

int ll_nome_is_in(LinkedList *l, char *nome);

int ll_cpf_is_in(LinkedList *l,char *cpf);

void ll_print(LinkedList *l);

void print_menu();

void ll_free(LinkedList *l);

int ll_id_is_in(LinkedList *l,int id);

int random_id(LinkedList *l);

int escrever_arquivo_csv(Pacient *patient);

int inserir_dados_csv(LinkedList *l);

int ll_remove(LinkedList *l, int id);

int csv_remove(LinkedList *l, int id);

long get_file_size(const char *filename);

#endif








