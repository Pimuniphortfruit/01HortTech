#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100
#define MAX_FORNECEDORES 50
#define MAX_USUARIOS 50
#define MAX_VENDAS 100
#define USER_FILE "usuarios.txt"
#define PRODUCT_FILE "produtos.txt"
#define SUPPLIER_FILE "fornecedores.txt"
#define SALES_FILE "vendas.txt"

typedef struct {
    int codigo;
    char nome[50];
    float quantidade; // em quilogramas
    float preco_por_kg; // em reais
    char categoria[50];
    char validade[11];
} Produto;

typedef struct {
    int codigo;
    char nome[50];
    char contato[20];
    char endereco[100];
    char produto_fornecido[50];
} Fornecedor;

typedef struct {
    char usuario[50];
    char senha[20];
    char cargo[30];
    char permissao[20]; // Administrativo,Funcionário
} Usuario;

typedef struct {
    int codigo_venda; // Novo campo para código da venda
    int codigo_produto;
    char nome_produto[50];
    float quantidade_vendida;
    float total_venda;
    char metodo_pagamento[20];
} Venda;

Produto produtos[MAX_PRODUTOS];
Fornecedor fornecedores[MAX_FORNECEDORES];
Usuario usuarios[MAX_USUARIOS];
Venda vendas[MAX_VENDAS];
int quantidade_produtos = 0, quantidade_fornecedores = 0, quantidade_usuarios = 0, quantidade_vendas = 0;

void carregar_usuarios() {

    FILE *file = fopen(USER_FILE, "r");
    char buffer[200];
    int i=0;
    if (file) {
    while(fgets(buffer, 300, file) != NULL){
        buffer[strcspn(buffer, "\n")] = '\0';
      printf("%s\n", buffer);
        char *split = strtok(buffer, "|");

        if(split != NULL){
                strcpy(usuarios[i].usuario, split);
                //usuarios[i].usuario[strcspn(usuarios[i].usuario, "\n")] = '\0';
                  printf("Nome: %s\n", usuarios[i].usuario);
                if(split != NULL){
                    split = strtok(NULL, "|");

                    strcpy(usuarios[i].senha, split);
                  //  usuarios[i].senha[strcspn()]
                    printf("Senha; %s\n", usuarios[i].senha);
                    if(split != NULL){
                        split = strtok(NULL, "|");

                        strcpy(usuarios[i].cargo, split);
                        printf("Cargo: %s\n", usuarios[i].cargo);

                        if(split != NULL){
                            split = strtok(NULL, "|");

                            strcpy(usuarios[i].permissao, split);
                            printf("Permissões: %s", usuarios[i].permissao);
                        }
                    }
                }

        }
        quantidade_usuarios = quantidade_usuarios + 1;
        //printf("quantidde %i", quantidade_usuarios);
        i++;
    }
        printf("Usuários carregados com sucesso! Total: %d\n", quantidade_usuarios);
    } else {
        printf("Erro ao carregar usuários. O arquivo pode não existir.\n");
    }
}

void salvar_produtos() {
    FILE *file = fopen(PRODUCT_FILE, "w");
    if (file) {
        for (int i = 0; i < quantidade_produtos; i++) {
            fprintf(file, "%d %s %.2f %.2f %s %s\n", produtos[i].codigo, produtos[i].nome,
                    produtos[i].quantidade, produtos[i].preco_por_kg, produtos[i].categoria,
                    produtos[i].validade);
        }
        fclose(file);
        printf("Produtos salvos com sucesso!\n");
    } else {
        printf("Erro ao salvar produtos.\n");
    }
}

void carregar_produtos() {
    FILE *file = fopen(PRODUCT_FILE, "r");
    if (file) {
        while (fscanf(file, "%d %49s %f %f %49s %10s", &produtos[quantidade_produtos].codigo,
                      produtos[quantidade_produtos].nome, &produtos[quantidade_produtos].quantidade,
                      &produtos[quantidade_produtos].preco_por_kg, produtos[quantidade_produtos].categoria,
                      produtos[quantidade_produtos].validade) == 6) {
            quantidade_produtos++;
            if (quantidade_produtos >= MAX_PRODUTOS) {
                printf("Limite de produtos atingido. Não é possível carregar mais.\n");
                break;
            }
        }
        fclose(file);
        printf("Produtos carregados com sucesso! Total: %d\n", quantidade_produtos);
    } else {
        printf("Erro ao carregar produtos.\n");
    }
}

void carregar_fornecedores() {
    FILE *file = fopen(SUPPLIER_FILE, "r");
    if (file) {
        while (fscanf(file, "%d %49s %19s %99s %49s", &fornecedores[quantidade_fornecedores].codigo,
                      fornecedores[quantidade_fornecedores].nome,
                      fornecedores[quantidade_fornecedores].contato,
                      fornecedores[quantidade_fornecedores].endereco,
                      fornecedores[quantidade_fornecedores].produto_fornecido) == 5) {
            quantidade_fornecedores++;
            if (quantidade_fornecedores >= MAX_FORNECEDORES) {
                printf("Limite de fornecedores atingido. Não é possível carregar mais.\n");
                break;
            }
        }
        fclose(file);
        printf("Fornecedores carregados com sucesso! Total: %d\n", quantidade_fornecedores);
    } else {
        printf("Erro ao carregar fornecedores.\n");
    }
}

void carregar_vendas() {
    FILE *file = fopen(SALES_FILE, "r");
    if (file) {
        while (fscanf(file, "%d %49s %f %f %19s", &vendas[quantidade_vendas].codigo_venda,
                      vendas[quantidade_vendas].nome_produto, &vendas[quantidade_vendas].quantidade_vendida,
                      &vendas[quantidade_vendas].total_venda, vendas[quantidade_vendas].metodo_pagamento) == 5) {
            quantidade_vendas++;
            if (quantidade_vendas >= MAX_VENDAS) {
                printf("Limite de vendas atingido. Não é possível carregar mais.\n");
                break;
            }
        }
        fclose(file);
        printf("Vendas carregadas com sucesso! Total: %d\n", quantidade_vendas);
    } else {
        printf("Erro ao carregar vendas.\n");
    }
}

void salvar_vendas() {
    FILE *file = fopen(SALES_FILE, "w");
    if (file) {
        for (int i = 0; i < quantidade_vendas; i++) {
            fprintf(file, "%d %s %.2f %.2f %s\n", vendas[i].codigo_venda, vendas[i].nome_produto,
                    vendas[i].quantidade_vendida, vendas[i].total_venda, vendas[i].metodo_pagamento);
        }
        fclose(file);
        printf("Vendas salvas com sucesso!\n");
    } else {
        printf("Erro ao salvar vendas.\n");
    }
}

int autenticar_usuario() {
    char usuario[50], senha[20];
    printf("Usuário: ");
    scanf("%49s", usuario);
    printf("Senha: ");
    scanf("%19s", senha);

    for (int i = 0; i <= quantidade_usuarios; i++) {
        if (strcmp(usuarios[i].usuario, usuario) == 0 && strcmp(usuarios[i].senha, senha) == 0) {
            printf("Bem-vindo, %s!\n", usuarios[i].usuario);
            return i; // Retorna o índice do usuário autenticado
        }
    }
    printf("Usuário ou senha incorretos.\n");
    return -1; // Autenticação falhou
}

#include <ctype.h>  // Inclua esta biblioteca para usar a função isalpha

void cadastrar_produto() {
    if (quantidade_produtos < MAX_PRODUTOS) {
        Produto p;
        char input_codigo[10];  // Buffer temporário para ler o código como string
        int codigo_valido = 0;

        // Validação do código numérico
        while (!codigo_valido) {
            printf("Código do produto (somente números): ");
            scanf("%s", input_codigo);

            // Verifica se a entrada é composta somente por dígitos
            codigo_valido = 1;  // Assume que a entrada é válida
            for (int i = 0; i < strlen(input_codigo); i++) {
                if (!isdigit(input_codigo[i])) {
                    codigo_valido = 0;  // Se não for número, invalida a entrada
                    printf("Entrada inválida! O código deve conter apenas números.\n");
                    break;
                }
            }
        }

        // Converte o código de string para inteiro após validação
        p.codigo = atoi(input_codigo);

        // Verificar se o código já existe
        for (int i = 0; i < quantidade_produtos; i++) {
            if (produtos[i].codigo == p.codigo) {
                printf("Código de produto já existe!\n");
                return;
            }
        }

        // Validação do nome (somente letras)
        int nome_valido = 0;
        while (!nome_valido) {
            printf("Nome do produto (somente letras): ");
            scanf("%s", p.nome);

            nome_valido = 1;  // Assume que o nome é válido
            for (int i = 0; i < strlen(p.nome); i++) {
                if (!isalpha(p.nome[i])) {  // Verifica se todos os caracteres são letras
                    nome_valido = 0;  // Invalida se não forem apenas letras
                    printf("Entrada inválida! O nome deve conter apenas letras.\n");
                    break;
                }
            }
        }

        printf("Quantidade inicial (kg): ");
        scanf("%f", &p.quantidade);
        printf("Preço por kg: ");
        scanf("%f", &p.preco_por_kg);
        printf("Categoria: ");
        scanf("%49s", p.categoria);
        printf("Validade (dd/mm/aaaa): ");
        scanf("%10s", p.validade);

        produtos[quantidade_produtos++] = p;
        salvar_produtos();  // Salva os produtos após o cadastro
        printf("Produto cadastrado com sucesso!\n");
    } else {
        printf("Limite de produtos atingido!\n");
    }
}
void cadastrar_fornecedor() {
    if (quantidade_fornecedores < MAX_FORNECEDORES) {
        Fornecedor f;

        printf("Código do fornecedor: ");
        scanf("%d", &f.codigo);
        getchar(); // Limpa o buffer após a leitura numérica

        printf("Nome do fornecedor: ");
        fgets(f.nome, sizeof(f.nome), stdin);
        f.nome[strcspn(f.nome, "\n")] = '\0';

        printf("Contato (telefone): ");
        fgets(f.contato, sizeof(f.contato), stdin);
        f.contato[strcspn(f.contato, "\n")] = '\0';

        printf("Endereço: ");
        fgets(f.endereco, sizeof(f.endereco), stdin);
        f.endereco[strcspn(f.endereco, "\n")] = '\0';

        printf("Produto fornecido: ");
        fgets(f.produto_fornecido, sizeof(f.produto_fornecido), stdin);
        f.produto_fornecido[strcspn(f.produto_fornecido, "\n")] = '\0';

        fornecedores[quantidade_fornecedores++] = f;
        salvar_fornecedores();
        printf("Fornecedor cadastrado com sucesso!\n");
    } else {
        printf("Limite de fornecedores atingido!\n");
    }
}

void realizar_venda(int usuario_index) {
    if (quantidade_vendas < MAX_VENDAS) {
        Venda v;
        printf("Código do produto: ");
        scanf("%d", &v.codigo_produto);

        for (int i = 0; i < quantidade_produtos; i++) {
            if (produtos[i].codigo == v.codigo_produto) {
                printf("Nome do produto: %s\n", produtos[i].nome);
                printf("Quantidade a ser vendida (kg): ");
                scanf("%f", &v.quantidade_vendida);

                if (v.quantidade_vendida > produtos[i].quantidade) {
                    printf("Quantidade indisponível em estoque.\n");
                    return;
                }

                strcpy(v.nome_produto, produtos[i].nome);
                produtos[i].quantidade -= v.quantidade_vendida; // Atualiza o estoque

                printf("Preço por kg: R$ %.2f\n", produtos[i].preco_por_kg);
                v.total_venda = v.quantidade_vendida * produtos[i].preco_por_kg;
                printf("Total da venda: R$ %.2f\n", v.total_venda);

                printf("Método de pagamento (Dinheiro, Cartão): ");
                scanf("%19s", v.metodo_pagamento);

                v.codigo_venda = quantidade_vendas + 1; // Código da venda é o próximo índice
                vendas[quantidade_vendas++] = v;

                salvar_produtos(); // Salva os produtos após a venda
                salvar_vendas();   // Salva a venda no arquivo
                printf("Venda realizada com sucesso! Código da venda: %d\n", v.codigo_venda);
                return;
            }
        }
        printf("Produto não encontrado.\n");
    } else {
        printf("Limite de vendas atingido!\n");
    }
}

void cancelar_venda() {
    int codigo_venda;
    printf("Digite o código da venda a ser cancelada: ");
    scanf("%d", &codigo_venda);

    for (int i = 0; i < quantidade_vendas; i++) {
        if (vendas[i].codigo_venda == codigo_venda) {
            for (int j = 0; j < quantidade_produtos; j++) {
                if (strcmp(vendas[i].nome_produto, produtos[j].nome) == 0) {
                    produtos[j].quantidade += vendas[i].quantidade_vendida; // Repor ao estoque
                    break;
                }
            }
            for (int k = i; k < quantidade_vendas - 1; k++) {
                vendas[k] = vendas[k + 1]; // Remove a venda cancelada
            }
            quantidade_vendas--;
            salvar_produtos(); // Salva os produtos após cancelar a venda
            salvar_vendas(); // Salva as vendas após cancelamento
            printf("Venda cancelada com sucesso!\n");
            return;
        }
    }
    printf("Venda não encontrada.\n");
}

void exibir_estoque() {
    printf("Estoque de produtos:\n");
    for (int i = 0; i < quantidade_produtos; i++) {
        printf("Código: %d | Nome: %s | Quantidade (kg): %.2f | Preço por kg: R$ %.2f | Categoria: %s | Validade: %s\n",
               produtos[i].codigo, produtos[i].nome, produtos[i].quantidade, produtos[i].preco_por_kg,
               produtos[i].categoria, produtos[i].validade);
    }
}
void repor_estoque() {
    if (quantidade_produtos > 0) { // Verifica se há produtos cadastrados
        int encontrado = 0;
        int opcaoBusca;
        int codigo;
        char nome[50];  // Armazena o nome do produto se a busca for por nome
        float quantidadeRepor;
        char novaValidade[11]; // Para armazenar a nova data de validade (formato "dd/mm/yyyy")

        // Escolha do método de busca
        printf("Deseja buscar o produto por:\n1 - Código\n2 - Nome\nEscolha uma opção: ");
        scanf("%d", &opcaoBusca);

        // Verifica se a busca será por código ou por nome
        if (opcaoBusca == 1) {
            // Busca por código
            printf("Digite o código do produto para reposição: ");
            scanf("%d", &codigo);

            // Percorre a lista de produtos para encontrar o produto pelo código
            for (int i = 0; i < quantidade_produtos; i++) {
                if (produtos[i].codigo == codigo) {
                    encontrado = 1;
                    printf("Produto encontrado: %s\n", produtos[i].nome);
                    printf("Estoque atual: %.2f kg\n", produtos[i].quantidade);
                    printf("Validade atual: %s\n", produtos[i].validade);

                    // Atualização de estoque e validade
                    printf("Digite a quantidade a ser reposta (kg): ");
                    scanf("%f", &quantidadeRepor);
                    produtos[i].quantidade += quantidadeRepor;

                    printf("Novo estoque de %s: %.2f kg\n", produtos[i].nome, produtos[i].quantidade);

                    printf("Digite a nova validade (dd/mm/yyyy): ");
                    scanf("%s", novaValidade);
                    strcpy(produtos[i].validade, novaValidade);

                    printf("Nova validade de %s: %s\n", produtos[i].nome, produtos[i].validade);
                    salvar_produtos();
                    printf("Estoque e validade atualizados e salvos com sucesso!\n");
                    break;
                }
            }
        } else if (opcaoBusca == 2) {
            // Busca por nome
            printf("Digite o nome do produto para reposição: ");
            scanf(" %[^\n]", nome); // Lê uma linha de texto com espaços

            // Percorre a lista de produtos para encontrar o produto pelo nome
            for (int i = 0; i < quantidade_produtos; i++) {
                if (strcmp(produtos[i].nome, nome) == 0) {
                    encontrado = 1;
                    printf("Produto encontrado: %s\n", produtos[i].nome);
                    printf("Estoque atual: %.2f kg\n", produtos[i].quantidade);
                    printf("Validade atual: %s\n", produtos[i].validade);

                    // Atualização de estoque e validade
                    printf("Digite a quantidade a ser reposta (kg): ");
                    scanf("%f", &quantidadeRepor);
                    produtos[i].quantidade += quantidadeRepor;

                    printf("Novo estoque de %s: %.2f kg\n", produtos[i].nome, produtos[i].quantidade);

                    printf("Digite a nova validade (dd/mm/yyyy): ");
                    scanf("%s", novaValidade);
                    strcpy(produtos[i].validade, novaValidade);

                    printf("Nova validade de %s: %s\n", produtos[i].nome, produtos[i].validade);
                    salvar_produtos();
                    printf("Estoque e validade atualizados e salvos com sucesso!\n");
                    break;
                }
            }
        } else {
            printf("Opção inválida.\n");
            return;
        }

        // Verifica se o produto foi encontrado
        if (!encontrado) {
            printf("Produto não encontrado.\n");
        }
    } else {
        printf("Nenhum produto cadastrado.\n");
    }
}

void relatorio_vendas() {
    printf("Relatório de vendas:\n");
    for (int i = 0; i < quantidade_vendas; i++) {
        printf("Código da Venda: %d | Produto: %s | Quantidade vendida (kg): %.2f | Total (R$): %.2f | Método de pagamento: %s\n",
               vendas[i].codigo_venda, vendas[i].nome_produto, vendas[i].quantidade_vendida,
               vendas[i].total_venda, vendas[i].metodo_pagamento);
    }
}

void encerrar_sessao() {
    printf("Sessão encerrada. Até a próxima!\n");
}

void pesquisar_produto() {
    int opcao;
    printf("Pesquisar produto por:\n");
    printf("1. Código\n");
    printf("2. Nome\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        int codigo;
        printf("Digite o código do produto: ");
        scanf("%d", &codigo);

        for (int i = 0; i < quantidade_produtos; i++) {
            if (produtos[i].codigo == codigo) {
                printf("Produto encontrado:\n");
                printf("Código: %d\n", produtos[i].codigo);
                printf("Nome: %s\n", produtos[i].nome);
                printf("Quantidade (kg): %.2f\n", produtos[i].quantidade);
                printf("Preço por kg: R$ %.2f\n", produtos[i].preco_por_kg);
                printf("Categoria: %s\n", produtos[i].categoria);
                printf("Validade: %s\n", produtos[i].validade);
                return;
            }
        }
        printf("Produto com o código %d não encontrado.\n", codigo);

    } else if (opcao == 2) {
        char nome[50];
        printf("Digite o nome do produto: ");
        scanf("%s", nome);

        for (int i = 0; i < quantidade_produtos; i++) {
            if (strcmp(produtos[i].nome, nome) == 0) {
                printf("Produto encontrado:\n");
                printf("Código: %d\n", produtos[i].codigo);
                printf("Nome: %s\n", produtos[i].nome);
                printf("Quantidade (kg): %.2f\n", produtos[i].quantidade);
                printf("Preço por kg: R$ %.2f\n", produtos[i].preco_por_kg);
                printf("Categoria: %s\n", produtos[i].categoria);
                printf("Validade: %s\n", produtos[i].validade);
                return;
            }
        }
        printf("Produto com o nome '%s' não encontrado.\n", nome);

    } else {
        printf("Opção inválida!\n");
    }
}
void exibir_fornecedor() {
    if (quantidade_fornecedores == 0) {
        printf("Nenhum fornecedor cadastrado.\n");
        return;
    }

    printf("Lista de Fornecedores Cadastrados:\n");
    for (int i = 0; i < quantidade_fornecedores; i++) {
        printf("\nFornecedor %d:\n", i + 1);
        printf("Código: %d\n", fornecedores[i].codigo);
        printf("Nome: %s\n", fornecedores[i].nome);
        printf("Contato: %s\n", fornecedores[i].contato);
        printf("Endereço: %s\n", fornecedores[i].endereco);
        printf("Produto fornecido: %s\n", fornecedores[i].produto_fornecido);
    }
}

void pesquisar_fornecedor() {
    char nome[50];
    printf("Digite o nome do fornecedor a ser pesquisado: ");
    scanf("%s", nome);

    for (int i = 0; i < quantidade_fornecedores; i++) {
        if (strcmp(fornecedores[i].nome, nome) == 0) {
            printf("Fornecedor encontrado:\n");
            printf("Código: %d\n", fornecedores[i].codigo);
            printf("Nome: %s\n", fornecedores[i].nome);
            printf("Contato: %s\n", fornecedores[i].contato);
            printf("Endereço: %s\n", fornecedores[i].endereco);
            return;
        }
    }
    printf("Fornecedor com o nome '%s' não encontrado.\n", nome);
}
void salvar_fornecedores() {
    FILE *file = fopen(SUPPLIER_FILE, "w");
    if (file) {
        for (int i = 0; i < quantidade_fornecedores; i++) {
            fprintf(file, "%d %s %s %s %s\n", fornecedores[i].codigo, fornecedores[i].nome,
                    fornecedores[i].contato, fornecedores[i].endereco, fornecedores[i].produto_fornecido);
        }
        fclose(file);
        printf("Fornecedores salvos com sucesso!\n");
    } else {
        printf("Erro ao salvar fornecedores.\n");
    }
}
void cadastrar_usuario() {
    if (quantidade_usuarios >= MAX_USUARIOS) {
        printf("Não é possível cadastrar mais usuários. Limite atingido.\n");
        return;
    }

    Usuario novo_usuario;
    int tipo_usuario;

    // Solicita nome do usuário e senha
    printf("Digite o nome do usuário: ");
    scanf("%49s", novo_usuario.usuario);

    printf("Digite a senha: ");
    scanf("%19s", novo_usuario.senha);

    // Solicita o tipo de usuário
    printf("Escolha o tipo de usuário:\n1. Funcionario\n2. Administrador\n");
    scanf("%d", &tipo_usuario);

    // Define o cargo e as permissões com base na escolha
    if (tipo_usuario == 1) {
        strcpy(novo_usuario.cargo, "funcionario");
        strcpy(novo_usuario.permissao, "1,4,6,7,8,10,12"); // Permissões do funcionario
    } else if (tipo_usuario == 2) {
        strcpy(novo_usuario.cargo, "administrador");
        strcpy(novo_usuario.permissao, "1,2,3,4,5,6,7,8,9,10,11,12"); // Todas as permissões
    } else {
        printf("Tipo de usuário inválido. Cadastro cancelado.\n");
        return;
    }

    // Adiciona o novo usuário ao array de usuários
    usuarios[quantidade_usuarios] = novo_usuario;
    quantidade_usuarios++;

    // Salva o usuário no arquivo "usuario.txt"
    FILE *file = fopen("usuarios.txt", "a");
    if (file) {
        fprintf(file, "%s %s %s %s\n",
                novo_usuario.usuario,
                novo_usuario.senha,
                novo_usuario.cargo,
                novo_usuario.permissao);
        fclose(file);
        printf("Usuário '%s' cadastrado e salvo no arquivo com sucesso!\n", novo_usuario.cargo);
    } else {
        printf("Erro ao abrir o arquivo para salvar o usuário.\n");
    }
}
void salvar_usuarios() {
    FILE *file = fopen("usuarios.txt", "w"); // Abre o arquivo para escrita
    if (!file) {
        printf("Erro ao abrir o arquivo para salvar os usuários.\n");
        return;
    }

    for (int i = 0; i < quantidade_usuarios; i++) {
        fprintf(file, "%s %s %s %s\n",
                usuarios[i].usuario,
                usuarios[i].senha,
                usuarios[i].cargo,
                usuarios[i].permissao);
    }

    fclose(file);
    printf("Usuários salvos no arquivo com sucesso!\n");
}
int main() {
    carregar_usuarios();
    carregar_produtos();
    carregar_fornecedores();
    carregar_vendas();

    int usuario_index = autenticar_usuario();
    if (usuario_index == -1) {
        return 0; // Sai se a autenticação falhar
    }

    // Verifica o cargo do usuário autenticado
    int is_admin = strcmp(usuarios[usuario_index].cargo, "administrador") == 0;

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Cadastrar Fornecedor\n");
        printf("3. Cadastrar Usuario\n");
        printf("4. Pesquisar Produto\n");
        printf("5. Pesquisar Fornecedor\n");
        printf("6. Realizar Venda\n");
        printf("7. Cancelar Venda\n");
        printf("8. Exibir Estoque\n");
        printf("9. Exibir Fornecedores\n");
        printf("10. Repor Estoque\n");
        printf("11. Gerar Relatório de Vendas\n");
        printf("12. Encerrar Sessão\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        // Restrição de acesso baseado no cargo
        if (!is_admin) { // Se for um funcionário
            if (opcao != 1 && opcao != 4 && opcao != 6 && opcao != 7 &&
                opcao != 8 && opcao != 10 && opcao != 12) {
                printf("Permissão negada para esta operação.\n");
                continue;
            }
        }

        // Executa a opção escolhida se o usuário tiver permissão
        switch (opcao) {
            case 1: cadastrar_produto(); break;
            case 2: if (is_admin) cadastrar_fornecedor(); break;
            case 3: if (is_admin) cadastrar_usuario(); break;
            case 4: pesquisar_produto(); break;
            case 5: if (is_admin) pesquisar_fornecedor(); break;
            case 6: realizar_venda(usuario_index); break;
            case 7: cancelar_venda(); break;
            case 8: exibir_estoque(); break;
            case 9: if (is_admin) exibir_fornecedor(); break;
            case 10: repor_estoque(); break;
            case 11: if (is_admin) relatorio_vendas(); break;
            case 12: encerrar_sessao(); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 12);
}
