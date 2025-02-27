#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 1024 // Максимальная длина входных данных

// Структура стека для чисел
typedef struct {
    double data[MAX_SIZE];
    int top;
} Stack;

// Инициализация стека
void init_stack(Stack* stack) {
    stack->top = -1;
}

// Проверка, пуст ли стек
int is_empty(Stack* stack) {
    return stack->top == -1;
}

// Добавление элемента в стек
void push(Stack* stack, double value) {
    if (stack->top >= MAX_SIZE - 1) {
        fprintf(stderr, "Стек переполнен\n");
        exit(1);
    }
    stack->data[++stack->top] = value;
}

// Удаление элемента из стека
double pop(Stack* stack) {
    if (is_empty(stack)) {
        fprintf(stderr, "Стек пуст\n");
        exit(1);
    }
    return stack->data[stack->top--];
}

// Функция для определения приоритета операторов
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Функция для выполнения операции между двумя числами
double apply_operator(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                fprintf(stderr, "Деление на ноль\n");
                exit(1);
            }
            return a / b;
        default:
            fprintf(stderr, "Неизвестный оператор\n");
            exit(1);
    }
}

// Функция для преобразования строки в число
double parse_number(const char* expression, int* index) {
    double number = 0.0;
    int decimal_point = 0;
    int power = 1;
    while ((*index < strlen(expression)) && (isdigit(expression[*index]) || expression[*index] == '.')) {
        if (expression[*index] == '.') {
            decimal_point = 1;
            (*index)++;
            continue;
        }
        if (!decimal_point) {
            number = number * 10 + (expression[*index] - '0');
        } else {
            power *= 10;
            number += (expression[*index] - '0') / (double)power;
        }
        (*index)++;
    }
    return number;
}

// Основная функция для вычисления выражения
double evaluate_expression(const char* expression, int use_float) {
    Stack values;
    Stack operators;
    init_stack(&values);
    init_stack(&operators);
    int i = 0;
    while (i < strlen(expression)) {
        if (isspace(expression[i])) {
            i++;
            continue;
        }
        if (isdigit(expression[i]) || expression[i] == '.') {
            double num = parse_number(expression, &i);
            push(&values, num);
        } else if (expression[i] == '(') {
            push(&operators, expression[i]);
        } else if (expression[i] == ')') {
            while (!is_empty(&operators) && operators.data[operators.top] != '(') {
                double val2 = pop(&values);
                double val1 = pop(&values);
                char op = pop(&operators);
                push(&values, apply_operator(val1, val2, op));
            }
            if (!is_empty(&operators)) {
                pop(&operators); // Удаляем '('
            }
        } else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            while (!is_empty(&operators) && precedence(operators.data[operators.top]) >= precedence(expression[i])) {
                double val2 = pop(&values);
                double val1 = pop(&values);
                char op = pop(&operators);
                push(&values, apply_operator(val1, val2, op));
            }
            push(&operators, expression[i]);
        }
        i++;
    }
    while (!is_empty(&operators)) {
        double val2 = pop(&values);
        double val1 = pop(&values);
        char op = pop(&operators);
        push(&values, apply_operator(val1, val2, op));
    }
    return pop(&values);
}

// Главная функция
int main(int argc, char* argv[]) {
    char expression[MAX_SIZE];
    if (!fgets(expression, sizeof(expression), stdin)) {
        return 1; // Ошибка чтения
    }
    expression[strcspn(expression, "\n")] = 0; // Убираем символ новой строки
    if (strlen(expression) >= MAX_SIZE - 1) {
        return 1; // Превышена максимальная длина
    }

    // Вычисление результата
    double result = evaluate_expression(expression, argc > 1 && strcmp(argv[1], "--float") == 0);

    // Вывод результата
    if (argc > 1 && strcmp(argv[1], "--float") == 0) {
        printf("%.4f\n", result); // Режим с плавающей точкой (4 знака после запятой)
    } else {
        printf("%d\n", (int)result); // Целочисленный режим
    }

    return 0;
}
