#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Data
{
    int dia, mes, ano;
}Data;

typedef struct Pessoa
{
    char nome[100];
    char cpf[20];
    Data data_nasc;
    char tel[20];
}Pessoa;

typedef struct Terrenos
{
    int id;
    Pessoa dono;
    Data data_compra;
    float largura, comprimento, area, preco_m2;
}Terrenos;

#endif