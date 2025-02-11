#include "patient.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>

/*
    @struct pacient 
    
    @brief Estrutura que representa os dados do paciente.

    @param id -> Variável responsável pelo ID do paciente.
    @param cpf -> Variável responsável pelo CPF do paciente.
    @param name -> Variável responsável pelo nome do paciente.
    @param age -> Variável responsável pela idade do paciente.
    @param year -> Variável responsável pela data de cadastro do paciente.

*/
struct pacient
{
    int id;             
    char cpf[15];       
    char name[100];     
    int age;        
    char year[20];      
};


/*
    @struct list

    @brief Estrutura de uma lista encadeada.

    @param first -> Variável que prepresenta o ponteiro para o primeiro nó da lista.
*/
struct list
{
    ListNode *first; // Variável que prepresenta o ponteiro para o primeiro nó da lista.
};


/*
    @struct list_node

    @brief Estrutura do nó da lista encadeada.

    @param info -> Ponteiro que aponta para a estrutura do paciente.
    @param next -> Ponteiro que aponta para o próximo nó da lista.
*/
struct list_node
{
    Pacient* info;      // Ponteiro que aponta para a estrutura do paciente.
    ListNode* next;     // Ponteiro que aponta para o próximo nó da lista.
};


/*
    @brief Função responsável pela criação de uma lista encadeada vazia e retorna um ponteiro.

    @return Retorna um ponteiro para a estrutura da lista encadeada.
*/
LinkedList *ll_create()
{
    LinkedList* l = (LinkedList *)malloc(sizeof(LinkedList)); // Alocação de memória para a estrutura da lista encadeada.
    l->first = NULL;                                          // Inicializando o ponteiro 'first' para NULL, indicando que uma lista vazia.
    return l;                                                 // Retorna um ponteiro para a lista recém-criada.   
}                                               


/*
    @brief Função responsável pela formatação da string CPF (Ex: 12345678901 -> 123.456.789-01).

    @param patient -> Ponteiro que acessa a estrutura do paciente.

    @return  Retorna uma string mascarada (formatada) correspondente ao CPF do paciente.  
*/
char *formatar_cpf(Pacient *patient) {
    static char format_cpf[15];     
    int j = 0;                      
    
    for (int i = 0; i < 11; i++) {
        format_cpf[j++] = patient->cpf[i];
        if (i == 2 || i == 5) {
            format_cpf[j++] = '.';
        } else if (i == 8) {
            format_cpf[j++] = '-';
        }
    }
    format_cpf[j] = '\0';

    return format_cpf;
}
    

/*
    @brief Função responsável para a criação de um novo paciente.

    @param id -> Parâmetro que recebe o ID do paciente.
    @param l -> Recebe a lista encadeada. 

    @return  Retorna um ponteiro para a estrutura do paciente. 
*/
Pacient* new_pacient(int id,LinkedList *l) {
    // char cpf[15];
    Pacient* patient = (Pacient*)malloc(sizeof(Pacient));
    assert(patient != NULL);                    // Garante que a alocação de memória foi bem-sucedida

    // Atribui o ID ao paciente
    patient->id = id;

    // Entrada do CPF
    printf("Digite o CPF: ");
    scanf("%11s", patient->cpf);                // Limita a entrada para evitar buffer overflow
    if (ll_cpf_is_in(l, patient->cpf) == 1) {
        printf("Erro: CPF ja existe\n");
        return NULL;  // Retorna da função
    }
    getchar();                                  // Consumir o '\n' do buffer

    // Entrada do Nome
    printf("Digite o Nome: ");
    fgets(patient->name, sizeof(patient->name), stdin);
    patient->name[strcspn(patient->name, "\n")] = 0;    // Remove o '\n'

    // Entrada da Idade
    printf("Digite a Idade: ");
    scanf("%d", &patient->age);  // Lê um número inteiro e armazena em patient->age
    getchar();  // Limpa o buffer                                 // Consumir o '\n' do buffer

    // Entrada do Ano de Cadastro
    printf("Digite o Ano de Cadastro: ");
    scanf("%11s", patient->year);
    getchar();                                  // Consumir o '\n' do buffer

    // Retorno da função new_pacient
    return patient;
}


/*
    @brief Função responsável para a atualização dos dados do paciente.

    @param l -> Recebe a lista encadeada. 
    @param id -> Parâmetro que recebe o ID do paciente.

    @return  Retorna um ponteiro para a estrutura do paciente. 
*/
Pacient* update_patient(LinkedList *l, int id)
{
    
    Pacient* patient = (Pacient*)malloc(sizeof(Pacient));
    assert(patient != NULL);                    // Garante que a alocação de memória foi bem-sucedida

    printf("Digite o novo valor para os campos CPF (apenas digitos), Nome, Idade e Data_Cadastro (para manter o valor atual de um campo, digite '-'):\n");
    
    patient = ll_is_in(l,id);                   // Busca e seleciona o paciente na lista tendo como critério o ID fornecido.
    if (patient != NULL){

        //Criação de variáveis para armazenamento dos novos dados para atualização dos daddos paciente 
        char new_cpf[15];                     
        char new_name[100];
        //int new_age;
        char new_year[20];

        scanf("%11s", new_cpf);                 // Entrada de dados do novo cpf para atualização.
        getchar();                              // Consume o '\n'(Limpeza do Buffer)
        if (ll_cpf_is_in(l, new_cpf) == 1) {
            printf("Erro: CPF ja existe\n");
            return NULL;                        // Retorno nulo seguindo a exceção da condicional estabelecida.
        }                           

        if (strcmp(new_cpf, "-") != 0)          // Verificação caso o usuário deseja ou não atualizar o CPF do paciente.
        {
            strcpy(patient->cpf, new_cpf);      // Leva as novas informações para atualizar dentro da estrutura do paciente.
        }

        fgets(new_name, sizeof(new_name), stdin);       // Entrada de dados do novo cpf para atualização.
        new_name[strcspn(new_name, "\n")] = 0;          // Remove o '\n' (Limpeza do Buffer)
        if (strcmp(new_name, "-") != 0)                 // Verificação caso o usuário deseja ou não atualizar o nome do paciente.
        {
            strcpy(patient->name, new_name);
        }

        // Entrada da nova idade
        printf("Digite a Idade: ");
        scanf("%d", &patient->age);  // Lê o valor inteiro para a idade
        getchar();  // Remove o '\n' (Limpeza do buffer)

        scanf("%11s", new_year);                        // Entrada de dados da nova data de cadastro para atualização.
        getchar();                                      // Remove o '\n' (Limpeza do Buffer)
        if (strcmp(new_year, "-") != 0)
        {
            strcpy(patient->year, new_year);    // Leva as novas informações para atualizar dentro da estrutura do paciente.
        }
        
        return patient;     // Retorno da função update_patient.
    }
    return NULL;            //Retorna NULL caso não encontre nenhum paciente com ID informado pelo usuário.
}

/*
    @brief Função responsável pela saída de dados formatada dos dados do paciente.

    @param patient -> Recebe um ponteiro para a estrutura do paciente.  
*/
void print_patient(Pacient *patient)
{
    char *cpf_formatado;
    cpf_formatado=formatar_cpf(patient);
    printf("%-3s %-15s %-20s %-10s %-12s\n", "ID", "CPF", "Nome", "Idade", "Data_Cadastro"); // Print patient details
    printf("%-3d %-15s %-20s %-d %-12s\n", patient->id, cpf_formatado, patient->name, patient->age, patient->year);/////////////////////////////
}

/*
    @brief Função responsável para atribuir uma lista encadeada vazia.

    @param l -> Recebe um ponteiro para a lista encadeada.

    @return  Retorna uma lista enacadeada vazia
*/
int ll_is_empty(LinkedList *l)
{
    return l->first == NULL; 
}


/*
    @brief Função responsável para inserção de um elemento na lista encadeada.

    @param l -> Recebe um ponteiro para a lista encadeada.
    @param patient -> Recebe um ponteiro para a estrutura do pacient (Pacient)
*/
void ll_insert(LinkedList* l, Pacient* patient)
{
    ListNode *node = (ListNode *)malloc(sizeof(ListNode)); 
    node->info = patient;                                        
    node->next = l->first;                                 
    l->first = node;                                       
}


/*
    @brief Função para verificar se um elemento está na lista encadeada

    @param l -> Recebe um ponteiro para a lista encadeada.
    @param patient -> Recebe um ponteiro para a estrutura do pacient (Pacient)

    @return  Retorna um ponteiro para a estrutura do paciente.
*/
Pacient* ll_is_in(LinkedList *l, int v)
{
    ListNode *p = l->first;
    while (p != NULL)
    {
        if (p->info->id == v){
            return p->info;
        }
        p = p->next;
    }
    return NULL;
}

/*
    @brief Função para verificar se o nome do paciente está na lista encadeada

    @param l -> Recebe um ponteiro para a lista encadeada.
    @param nome -> Recebe um ponteiro de caracteres.

    @return  Retorna 0 indicando que a execução da função foi bem sucedida.
*/
int ll_nome_is_in(LinkedList *l, char *nome)
{
    ListNode *p = l->first;
    while (p != NULL)
    {
        if (strstr(p->info->name, nome) != NULL) //nome pode está está contindo na string
        {
            print_patient(p->info);
        }
        p = p->next;
    }
    return 0;
}

/*
    @brief Função para verificar se o cpf do paciente está na lista encadeada.

    @param l -> Recebe um ponteiro para a estrutura da lista encadeada.
    @param cpf -> Recebe um ponteiro de caracteres.

    @return  Retorna 0 indicando que a execução da função foi bem sucedida, 1 caso contrário.
*/
int ll_cpf_is_in(LinkedList *l,char *cpf){
    ListNode *p = l->first;
    while (p != NULL)
    {
        if (strcmp(p->info->cpf, cpf) == 0){ 
            print_patient(p->info);
            return 1;
        }
        p = p->next;
    }
    return 0;
}

/*
    @brief Função que imprime a lista encadeada

    @param l -> Recebe um ponteiro para a estrutura da lista encadeada.
*/
void ll_print(LinkedList *l)
    {
        for (ListNode *p = l->first; p != NULL; p = p->next)
        {   
            if (ll_is_empty(l)) {
            printf("The list is empty.\n");
            return;
            }
            print_patient(p->info);
            
        }
        printf("\n"); // Print a newline character to separate the output.
    }


/*
    @brief Função responsável pela impressão da interface do menu.
*/
void print_menu()
{
    printf("Healthy Sys \n");
    printf("\n");
    printf("1 - Consultar paciente\n");
    printf("2 - Atualizar paciente\n");
    printf("3 - Remover paciente\n");
    printf("4 - Inserir paciente\n");
    printf("5 - Imprimir lista de paciente\n");
    printf("Q - Sair\n");
    printf("\n");

}


/*
    @brief Função que desaloca a memória a lista encadeada.

    @param l -> Recebe um ponteiro para a estrutura da lista encadeada.
*/
void ll_free(LinkedList *l)
{
    ListNode *p = l->first;
    while (p != NULL)
    {
        ListNode *t = p->next; // Store a reference to the next node.
        free(p);               // Free the memory allocated for the current node.
        p = t;                 // Move to the next node.
    }
    free(l); // Free the memory allocated for the list structure itself.
}

/*
    @brief Função para verificar se o ID do paciente está na lista encadeada.

    @param l -> Recebe um ponteiro para a estrutura da lista encadeada.
    @param id -> Parâmetro que recebe o ID do paciente.

    @return  Retorna 0 se não o paciente buscado não está existente, caso contrário retorna 1.
*/
int ll_id_is_in(LinkedList *l, int id) {
    ListNode *p = l->first;
    while (p != NULL) {
        if (p->info->id == id) { 
            print_patient(p->info); // Mostra as informações do paciente
            return 1; // Retorna 1 se o paciente for encontrado
        }
        p = p->next;
    }
    return 0; // Retorna 0 se o paciente não for encontrado
}


/*
    @brief Função que faz geração de números aleatórios para incluir no ID do paciente.

    @param l -> Recebe um ponteiro para a estrutura da lista encadeada.

    @return  Retorna número gerado a ser usado como o ID do paciente.
*/
int random_id(LinkedList *l) {
    srand(time(NULL));  // Inicializa o gerador de números aleatórios com a hora atual
    int min = 0, max = 1000;  // Define o intervalo de números aleatórios (entre 0 e 1000)
    int numero;  // Variável para armazenar o número gerado

    // Loop principal: continua até encontrar um número único
    while (1) {
        numero = min + rand() % (max - min + 1);  // Gera um número aleatório dentro do intervalo [min, max]

        ListNode *p = l->first;  // Ponteiro para percorrer a lista encadeada
        int encontrado = 0;  // Flag para verificar se o número já está na lista

        // Percorre a lista para verificar se o número já existe
        while (p != NULL) {
            if (p->info->id == numero) {  // Se o número já existir na lista
                encontrado = 1;  // Marca como encontrado
                break;  // Sai do loop
            }
            p = p->next;  // Avança para o próximo nó na lista
        }

        // Se o número não foi encontrado, sai do loop principal e retorna o número
        if (!encontrado) {
            break;  // Sai do loop principal
        }
    }
    
    return numero;  // Retorna o número único gerado
}

/*
    @brief Função para escrever os dados do paciente no arquivo em formato de csv.

    @param patient -> Recebe um ponteiro para a estrutura do paciente (Pacient).

    @return  Retorna 0 indicando que a execução da função foi bem sucedida, caso conrario retorna 1.
*/
int escrever_arquivo_csv(Pacient *patient) {
    FILE *file;
    file = fopen("bd_paciente.csv", "a");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    // Escreve os dados do paciente no arquivo CSV
    fprintf(file, "%d,%s,%s,%d,%s\n", patient->id, patient->cpf, patient->name, patient->age, patient->year);

    fclose(file);  // Fecha o arquivo após terminar a manipulação
    return 0;
}

/*
    @brief Função para inicializar a lista encadeada com os dados já existentes no arquivo em formato de csv

    @param patient -> Recebe um ponteiro para a estrutura do paciente (Pacient).

    @return Retorna 0 indicando que a execução da função foi bem sucedida, caso contrário retorna 1.
*/
int inserir_dados_csv(LinkedList *l) {
    FILE *file = fopen("bd_paciente.csv", "r");  // Modo de leitura do arquivo
    if (file == NULL) {
        printf("Banco de dados vazio");
        return 1;  // Retorna erro se não for possível abrir o arquivo
    }

    char line[1024];  // Buffer para armazenar cada linha do arquivo

     // Ler e ignorar a primeira linha (cabeçalho)
     fgets(line, sizeof(line), file);


    // Ler o arquivo linha por linha
    while (fgets(line, sizeof(line), file)) {
        Pacient *patient = malloc(sizeof(Pacient));  // Alocar memória para o paciente
        if (patient == NULL) {
            printf("Erro ao alocar memória para paciente!\n");
            fclose(file);  // Fechar o arquivo antes de retornar
            return 1;  // Retorna erro se não for possível alocar memória
        }

        // Usando strtok para separar os valores na linha
        char *token = strtok(line, ",");  // Lê o primeiro valor (id)
        if (token != NULL) {
            patient->id = atoi(token);  // Converte o id para inteiro
        }

        token = strtok(NULL, ",");  // Lê o CPF
        if (token != NULL) {
            strncpy(patient->cpf, token, sizeof(patient->cpf) - 1);
        }

        token = strtok(NULL, ",");  // Lê o nome
        if (token != NULL) {
            strncpy(patient->name, token, sizeof(patient->name) - 1);
        }

        token = strtok(NULL, ",");  // Lê a idade
        if (token != NULL) {
            // Converte o token para um inteiro
            patient->age = strtol(token, NULL, 10);  // Converte a string para inteiro
        }

        token = strtok(NULL, ",");  // Lê o ano
        if (token != NULL) {
            strncpy(patient->year, token, sizeof(patient->year) - 1);
        }

        // Inserir o paciente na lista vinculada
        ll_insert(l, patient); 
    }

    fclose(file);  // Fechar o arquivo após a leitura
    return 0;  // Retorna sucesso
}

/*
    @brief Função para remover um elemento da lista encadeada.

    @param l -> Recebe um ponteiro para a estrutura da lista encadeada.
    @param id -> Parâmetro que recebe o ID do paciente.

    @return Retorna 0 indicado que o elemento foi encontrado, 1 caso contrário.
*/
int ll_remove(LinkedList *l, int id)//lista e id 
{
    ListNode *p = l->first; // Ponteiro para o nó atual sendo examinado
    ListNode *prev = NULL;  // Ponteiro para o nó anterior

    // Pecorre a lista
    while (p != NULL)
    {
        // Verifica se o nó atual contém o elemento a ser removido
        if (p->info->id == id)
        {
             // Se o elemento a ser removido estiver no início da lista
            if (prev == NULL)
                l->first = p->next; // Atualiza o ponteiro 'first' para pular o primeiro nó
                // Se o elemento a ser removido estiver no meio ou no final da lista
            else
                prev->next = p->next;  // Atualiza o ponteiro 'next' do nó anterior

            
            csv_remove(l,id);
            free(p);  // Libera a memória ocupada pelo nó removido
            return 1; // Retorna lista sem o element

        }
        else
        {
            prev = p;     // Atualiza o ponteiro 'prev' 
            p = p->next; // Move para o próximo nó
        }
    }

    return 0; // Indica que o elemento não foi encontrado
}

/*
    @brief Função para remover uma linha correspondente aos dados de um paciente no arquivo csv.

    @param l -> Recebe um ponteiro para a estrutura da lista encadeada.
    @param id -> Parâmetro que recebe o ID do paciente.

    @return Retorna 0 indicado que a função foi bem sucedida, 1 caso contrário.
*/
int csv_remove(LinkedList *l, int id){
    FILE *file = fopen("bd_paciente.csv", "w");
    if (!file) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }
    fprintf(file,"ID,CPF,Nome,Idade,Data_Cadastro\n");//escreve o cabeçalho no arquivo
    ListNode *p = l->first;
    
    while (p != NULL) {
        if (p->info->id != id) {  // Escreve todos os pacientes, exceto o que queremos remover
            fprintf(file, "%d,%s,%s,%d,%s\n", p->info->id, p->info->cpf, p->info->name, p->info->age, p->info->year);/////////////
        }
        p = p->next;
    }

    fclose(file);
    return 0;

}
//função para verificar o tamanho do arquivo
long get_file_size(const char *filename) {
    FILE *file = fopen(filename, "rb"); // Abre o arquivo no modo binário
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1; // Retorna 1 se ocorrer erro ao abrir o arquivo.
    }

    fseek(file, 0, SEEK_END); // Move o cursor para o final do arquivo
    long size = ftell(file);  // Obtém a posição atual (tamanho do arquivo)
    fclose(file); // Fecha o arquivo

    return size;//retorna o tamanho do arquivo.
}
