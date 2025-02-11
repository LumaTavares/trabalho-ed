# Gerenciamento de Pacientes

## Descrição do Projeto
Este projeto é um sistema de gerenciamento de pacientes desenvolvido em C. Ele permite que o usuário cadastre, consulte, atualize e remova registros de pacientes armazenados em um arquivo CSV.

## Estrutura do Projeto

O projeto está estruturado da seguinte forma:

```
/
|-- src/
|   |-- main.c          # Arquivo principal do sistema
|   |-- patient.c       # Implementação das funções relacionadas aos pacientes
|   |-- patient.h       # Definição das estruturas e protótipos das funções
|
|-- bd_paciente.csv     # Arquivo de armazenamento dos registros
|-- README.md           # Documentação do projeto
```

## Funcionalidades

O sistema possui as seguintes funcionalidades:

1. **Consulta de pacientes** por nome ou CPF
2. **Atualização de registros** de pacientes
3. **Remoção de pacientes** do banco de dados
4. **Cadastro de novos pacientes**
5. **Exibição de todos os registros**

## Compilação e Execução no Windows

### Requisitos:

- MinGW instalado (para compilar programas em C no Windows)
- Um editor de texto ou IDE (VSCode, Code::Blocks, Dev-C++, etc.)
- Terminal (CMD ou PowerShell)

### Passos:

1. **Baixe e instale o MinGW** (caso não tenha instalado). Certifique-se de que `gcc` está no Path.
2. **Abra o terminal (CMD ou PowerShell)** e navegue até a pasta do projeto:

   ```sh
   cd caminho/para/o/projeto
   ```

3. **Compile o programa** usando o `gcc`:

   ```sh
   gcc -o sistema src/main.c src/patient.c -Wall
   ```

4. **Execute o programa**:

   ```sh
   ./sistema
   ```

## Detalhamento das Funções

### `main.c`

O arquivo `main.c` é o ponto de entrada do programa. Ele inicializa a lista de pacientes e gerencia a interação com o usuário.

### `patient.c` e `patient.h`

O arquivo `patient.c` implementa as funções definidas em `patient.h`, que são utilizadas para manipular os registros de pacientes.

- **Estrutura `Pacient`**:
  
  ```c
  struct pacient {
      int id;
      char cpf[15];
      char nome[100];
      char age[5];
      char year[20];
  }
  ```
 - **Estrutura `LinkedList`**:
```c
   struct list
{
    ListNode *first; // Variável que prepresenta o ponteiro para o primeiro nó da lista.
};
```
- **Estrutura `Node`**:
  ```c
  struct list_node
  {
    Pacient* info;
    ListNode* next;
  }
  ```
  
- **`ll_create()`** - Criação de uma lista encadeada vazia
- **`formatar_cpf()`** -  Formatação da string CPF do paciente   
- **`new_pacient()`** - Cria um novo paciente e retorna um ponteiro para ele.
- **`update_patient()`** - Atualiza os dados de um paciente existente.
- **`print_patient()`** - Exibe os detalhes de um paciente.
- **`ll_is_empty()`** - Atribuição de uma lista encadeada vazia.
- **`ll_insert()`** - Insere um novo paciente na lista.
- **`ll_is_in()`** - Verifica se um ID existe na lista.
- **`ll_nome_is_in()`** - Verifica se um paciente existe pelo nome.
- **`ll_cpf_is_in()`** - Verifica se um paciente existe pelo CPF.
- **`ll_print()`** - Exibe todos os registros.
- **`print_menu()`** - Exibe o menu de opções.
- **`ll_free()`** -  Desaloca a memória da lista encadeada.
- **`ll_id_is_in()`** -  Verifica se o ID do paciente está na lista encadeada.
- **`random_id()`** - Gera um ID aleatório para um novo paciente.
- **`escrever_arquivo_csv()`** - Salva os dados atualizados no arquivo CSV.
- **`inserir_dados_csv()`** - Lê os dados do arquivo CSV e os carrega na lista.
- **`ll_remove()`** - Remove um paciente da lista.
- **`csv_remove()`** - Remove uma linha correspondente aos dados de um paciente no arquivo csv.

## Exemplo de Uso

1. Ao iniciar o programa, o usuário verá o seguinte menu:

   ```
   1 - Consultar paciente
   2 - Atualizar cadastro
   3 - Remover paciente
   4 - Inserir novo paciente
   5 - Exibir todos os pacientes
   Q - Sair
   ```

2. Se o usuário escolher a opção `1`, ele poderá buscar um paciente pelo nome ou CPF.
3. Para cadastrar um novo paciente, basta escolher a opção `4` e inserir os dados.
4. Para atualizar um paciente, a opção `2` permite modificar os dados existentes.
5. Para excluir um paciente, basta inserir o ID e confirmar a remoção.

## Considerações Finais

- O programa salva automaticamente as alterações no arquivo `bd_paciente.csv`.
- Certifique-se de que o arquivo CSV está no diretório correto.
- Caso encontre problemas, verifique a permissão de escrita/leitura do arquivo.

Este projeto pode ser expandido com funcionalidades extras, como interface gráfica ou banco de dados SQL. Contribuições são bem-vindas!

---
Desenvolvido por Heitor Mendes e Luma Tavares.
