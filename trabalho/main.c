#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> // Biblioteca para rodar palavras com acentuação

void menu() {
    printf("1 - Consultar paciente\n"
           "2 - Atualizar paciente\n"
           "3 - Remover paciente\n"
           "4 - Inserir paciente\n"
           "5 - Imprimir lista de pacientes\n"
           "Q - Sair\n");
}

void ler_pacientes(FILE *arquivo) {
    char buffer[1024];
    char *data;

    // Lê e imprime cada linha do arquivo
    while (fgets(buffer, sizeof(buffer), arquivo)) {
         // Substitui as vírgulas por espaços
         for(int i=0;buffer[i] !='\0';i++){
            if (buffer[i] == ',') {
                buffer[i] = ' ';  // Substitui vírgula por espaço
            }
         }
        // Imprime a linha após a substituição
        printf("%s", buffer);
    }
    
}

int main() {
    // Declaração de variáveis
    char opcao;
    FILE *bd_pacienteFILE = fopen("../bd_paciente.csv", "r");
  

    // Configura o ambiente para suportar caracteres UTF-8
    setlocale(LC_ALL, "pt_BR.UTF-8");
    system("chcp 65001");  // Configura o terminal para UTF-8 no Windows

    if (bd_pacienteFILE == NULL) {
        printf("Erro ao abrir o arquivo de pacientes.\n");
        return 1;
    }

    // Chama a função para executar o menu
    menu();
    printf("Digite a opção desejada:\n ");
    
    // Adicionando um espaço antes de %c para garantir que o buffer seja limpo corretamente
    scanf(" %c", &opcao);

    while(opcao != 'q') {  // Continua até o usuário digitar 'q'
        switch (opcao) {
            case '5':
                // Chama a função para ler e imprimir a lista de pacientes
                printf("Imprimindo lista de pacientes:\n");
                ler_pacientes(bd_pacienteFILE);
                break;
            // Outros casos para outras opções
            case '1':
                printf("Consultar paciente.\n");
                break;
            case '2':
                printf("Atualizar paciente.\n");
                break;
            case '3':
                printf("Remover paciente.\n");
                break;
            case '4':
                printf("Inserir paciente.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

        // Mostrar o menu novamente
        printf("\n");
        menu();
        printf("Digite a opção desejada:\n ");
        scanf(" %c", &opcao); // Adicionando um espaço antes de %c para limpar o buffer
    }
    
    // Fechar o arquivo após o uso
    fclose(bd_pacienteFILE);

    return 0;
}
