#include "patient.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int id;
int main(void)
{  
    // Criação da lista e arquivo vinculado à mesma
    LinkedList* list = ll_create();
    FILE *filename;
    filename = fopen("bd_paciente.csv", "a");
    if (filename == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    // Verifica se o arquivo está vazio, se sim, escreve o cabeçalho
    if(get_file_size("bd_paciente.csv")==0){
        fprintf(filename,"ID,CPF,Nome,Idade,Data_Cadastro\n");
        fflush(filename);
    }

    // Inicializa a lista encadeada com dados do arquivo CSV, se existirem
    inserir_dados_csv(list);
    id = random_id(list); // Inicializa um id aleatório

    // Declaração de variáveis
    char escolha;
    int sair = 0;
    char opcao_menu;
    char nome[100];
    char cpf[12];

    while(sair == 0)
    {
        print_menu(); // Mostra o menu

        scanf(" %c", &opcao_menu);
        getchar();  // Limpa o buffer após a leitura do caractere

        // Opção para consultar pacientes no banco de dados/lista.
        if (opcao_menu == '1') {   
            int escolha;
            printf("Escolha o modo de consulta:\n");
            printf("1 - Por nome\n");
            printf("2 - Por CPF\n");
            printf("3 - Retornar ao menu principal\n\n");

            scanf("%d", &escolha);
            getchar();  // Limpa o buffer

            // Para realizar a pesquisa pelo nome
            if(escolha == 1) {
                printf("Digite o nome:\n ");
                fgets(nome, sizeof(nome), stdin); // Atribui à variável nome o que o usuário digitou
                nome[strcspn(nome, "\n")] = 0;    // Remove o '\n'
                ll_nome_is_in(list, nome); // Verifica se o nome existe na lista encadeada
            } 
            else if (escolha == 2) { // Para realizar a pesquisa pelo CPF
                printf("Digite o CPF:\n ");
                fgets(cpf, sizeof(cpf), stdin); // Atribui à variável cpf o que o usuário digitou
                cpf[strcspn(cpf, "\n")] = 0;
                if(ll_cpf_is_in(list, cpf)==1){}; // Verifica se o CPF existe na lista encadeada
            }
        } 
        else if (opcao_menu == '2') { // Opção para atualização do paciente
            int id_patient; // Variável para guardar ID digitado pelo usuário
            ll_print(list); // Imprime toda a lista encadeada
            printf("Digite o ID do registro a ser atualizado:\n");
            scanf("%d", &id_patient); // Atribui à variável id_patient o ID desejado
            getchar(); // Limpa o buffer

            // Chama uma função para verificar se o paciente existe na lista
            if (ll_is_in(list, id_patient) != NULL) {
                Pacient* patient = update_patient(list, id_patient); // Atualiza o paciente
                print_patient(patient); // Mostra na tela as informações do paciente
                printf("Confirma os novos valores para o registro acima? (S/N): ");
                scanf(" %c", &escolha); // Atribui à variável escolha a decisão do usuário
                getchar(); // Limpa o buffer

                if (escolha == 'S' || escolha == 's') {
                    ll_remove(list, id_patient); // Remove os dados antigos do paciente da lista e do arquivo CSV
                    ll_insert(list, patient); // Insere os dados novos do paciente na lista
                    escrever_arquivo_csv(patient); // Insere os dados novos no arquivo CSV
                    printf("Registro atualizado com sucesso.\n");
                }else{
                    free(patient); // Libera a memória alocada para o paciente se a resposta for "não"
                    printf("Atualização cancelada.\n");
                }
            } else {
                printf("ID nao existe.\n");
            }
        } 
        else if (opcao_menu == '3') { // Função para remover paciente
            int excluir_id; // Variável para guardar o ID que o usuário deseja excluir
            printf("Digite o ID do registro a ser removido: ");
            scanf("%d", &excluir_id); // Atribui à variável excluir_id o ID desejado
            getchar(); // Limpa o buffer

            // Chama a função para verificar se o ID existe
            if (ll_id_is_in(list, excluir_id) != 0) {
                printf("Tem certeza de que deseja excluir o registro abaixo? (S/N): ");
                scanf(" %c", &escolha);
                getchar(); // Limpa o buffer
                
                if (escolha == 'S' || escolha == 's') {
                    ll_remove(list, excluir_id); // Função para remover o paciente do sistema
                    printf("Registro removido com sucesso.\n");
                } else {
                    printf("Processo cancelado.\n");
                }
            } else {
                printf("ID nao existe.\n");
            }
        } 
        else if (opcao_menu == '4') { // Função para inserir paciente no sistema
            printf("\n");
            Pacient* patient = new_pacient(id, list); // Chama a função para inserir um novo paciente na lista
            if (patient != NULL) {
                printf("\nConfirma os novos valores para o registro abaixo? (S/N)\n");
                print_patient(patient); // Mostra as informações do paciente na tela
                scanf(" %c", &escolha);
                getchar(); // Limpa o buffer

                if (escolha == 'S' || escolha == 's') {
                    ll_insert(list, patient); // Insere o paciente na lista
                    escrever_arquivo_csv(patient); // Escreve as informações no arquivo CSV
                    printf("O registro foi inserido com sucesso.\n");
                    id = random_id(list); // Gera um novo ID aleatório
                }
            }
        } 
        else if (opcao_menu == '5') { // Função para imprimir as informações dos pacientes na tela
            ll_print(list);
        } 
        else if (opcao_menu == 'Q' || opcao_menu == 'q') { // Função para sair do sistema
            ll_free(list); // Libera a memória
            sair = 1; // Sai do sistema
        } 
        else {
            printf("Opção inválida! Tente novamente.\n");
        }
        
        printf("\n");
    }
    fclose(filename);  // Fechar o arquivo após terminar a manipulação
    return 0;
}
