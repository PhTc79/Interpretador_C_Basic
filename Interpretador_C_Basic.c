#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Estrutura para armazenar variáveis
typedef struct {
    char name;     // Nome da variável (ex. A, B, C)
    int value;     // Valor da variável
} Variable;

// Função para procurar o valor de uma variável
int get_variable(Variable vars[], int num_vars, char name) {
    for (int i = 0; i < num_vars; i++) {
        if (vars[i].name == name) {  // Procura a variável pelo nome
            return vars[i].value;    // Retorna o valor da variável
        }
    }
    return 0;  // Se a variável não for encontrada, retorna 0
}

// Função para definir ou atualizar o valor de uma variável
void set_variable(Variable vars[], int *num_vars, char name, int value) {
    for (int i = 0; i < *num_vars; i++) {
        if (vars[i].name == name) {  // Se a variável já existe, atualiza o valor
            vars[i].value = value;
            return;
        }
    }
    // Se a variável não existe, cria uma nova
    vars[*num_vars].name = name;
    vars[*num_vars].value = value;
    (*num_vars)++;  // Aumenta o número de variáveis
}

// Função para processar cada linha do código BASIC
void process_line(char *line, Variable vars[], int *num_vars) {
    int line_num;
    char command[10];

    // Lê o número da linha e o comando (ex: LET, PRINT)
    sscanf(line, "%d %s", &line_num, command);

    // Se o comando for LET, é uma atribuição ou operação
    if (strcmp(command, "LET") == 0) {
        char var_name;     // Variável para armazenar o nome da variável (ex. A, B, C)
        char op;           // Operador matemático (+, -, *, /)
        int operand1, operand2;
        char var1, var2;

        // Verifica se é uma operação entre variáveis (ex: A + B)
        if (sscanf(line, "%*d LET %c = %c %c %c", &var_name, &var1, &op, &var2) == 4) {
            // Obtém os valores das variáveis (ex: valor de A e valor de B)
            operand1 = get_variable(vars, *num_vars, var1);
            operand2 = get_variable(vars, *num_vars, var2);

            // Executa a operação com base no operador
            if (op == '+') {
                set_variable(vars, num_vars, var_name, operand1 + operand2);  // Atribui o resultado de A + B à variável
            } else if (op == '-') {
                set_variable(vars, num_vars, var_name, operand1 - operand2);  // Atribui o resultado de A - B à variável
            } else if (op == '*') {
                set_variable(vars, num_vars, var_name, operand1 * operand2);  // Atribui o resultado de A * B à variável
            } else if (op == '/') {
                set_variable(vars, num_vars, var_name, operand1 / operand2);  // Atribui o resultado de A / B à variável
            }
        } else {
            // Atribuição direta (ex: LET A = 10)
            sscanf(line, "%*d LET %c = %d", &var_name, &operand1);
            set_variable(vars, num_vars, var_name, operand1);  // Armazena o valor na variável
        }
    } 
    // Se o comando for PRINT, imprime o valor da variável
    else if (strcmp(command, "PRINT") == 0) {
        char text[20];  // Texto a ser impresso (ex: "A + B = ")
        char var_name;  // Nome da variável cujo valor será impresso
        int value;

        // Lê o texto e o nome da variável
        sscanf(line, "%*d PRINT \"%[^\"]\" ; %c", text, &var_name);
        value = get_variable(vars, *num_vars, var_name);  // Obtém o valor da variável
        printf("%s %d\n", text, value);  // Imprime o texto seguido do valor da variável
    }
}

int main() {
    // Programa BASIC que será processado
    const char *program[] = {
        "10 REM programa em BASIC",
        "20 LET A = 10",
        "30 LET B = 5",
        "40 LET C = A + B",
        "50 PRINT \"A + B = \" ; C",
        "60 LET D = A * B",
        "70 PRINT \"A * B = \" ; D",
        "80 LET E = A - B",
        "90 PRINT \"A - B = \" ; E",
        "100 LET F = A / B",
        "110 PRINT \"A / B = \" ; F",
        "120 END"
    };

    // Array para armazenar as variáveis e seus valores
    Variable vars[10];
    int num_vars = 0;

    // Processa cada linha do programa
    for (int i = 0; i < 12; i++) {
        process_line((char *)program[i], vars, &num_vars);  // Processa cada linha
    }

    return 0;  // Finaliza o programa
}
