#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    char nome[100];
    char cpf[20];
    Data data_nasc;
    char tel[20];
} Pessoa;

typedef struct {
    Pessoa dono;
    Data data_compra;
    int id;
    float largura;
    float comprimento;
    float area;
    float preco_m2;
} Terrenos;

#endif
