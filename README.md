
 ---
### 🛰️ Mini Projeto – Sistema de Gestão de Terrenos (Linguagem C)
 
📌 Disciplina: Introdução à Programação em C

 ---

 
### 🌐 Link do Projeto no GitHub

➡️ [https://github.com/users/EduardaCCampos/projects/3](https://github.com/users/EduardaCCampos/projects/3)

 ---

---
### 👩‍💻 Desenvolvedores
| Nome | GitHub |
| :--- | :--- |
| Clara Bertão | [@clarabertao](https://github.com/clarabertao) |
| Eduarda Lima | [@EduardaCCampos](https://github.com/EduardaCCampos) |
| Julia Coité | [@Julicoit](https://github.com/juliacoit) |
| Sarah Godinho | [@Sarocaa](https://github.com/Sarocaa) |

---

### 🚀 Descrição do Projeto
 ---
- Este projeto implementa um sistema completo de gerenciamento de terrenos, utilizando:

- Vetor de ponteiros para structs

- Alocação dinâmica de memória

- Manipulação de arquivos

- Menu interativo em loop

- Cálculo automático de área, preço total e estatísticas gerais

O objetivo é gerenciar até 100 terrenos, permitindo criar, editar, remover, buscar e salvar os dados.

---


### 🧩 Funcionalidades Implementadas
 ---
- Criar novo terreno

- Editar terreno existente

- Remover terreno

- Mostrar dados por ID

- Calcular valor do terreno

- Contar terrenos livres/ocupados

- Calcular valor total de todos

- Salvar e carregar os dados em arquivo

 #### 🗂️ Estruturas Utilizadas

| Struct | Campos Principais | Finalidade |
| :--- | :--- | :--- |
| **Data** | `dia`, `mes`, `ano` | Usada para datas de nascimento e compra. |
| **Pessoa** | `nome`, `cpf`, `data_nascimento`, `telefone` | Detalhes do proprietário do terreno. |
| **Terrenos** | `id`, `dono`, `data_compra`, `largura`, `comprimento`, `area`, `preco_m2` | Dados principais do imóvel. O **`id`** é a chave única. |

---

🖥️ Como executar
 ---

1. Compilar
   
gcc main.c funcoes.c -o terrenos


2. Executar

O arquivo deve ser passado como parâmetro:

./terrenos dados.dat

 

---
### ⚙️ Tecnologias Utilizadas

* C 
* Manipulação de Arquivos (binário)
* Ponteiros, Alocação Dinâmica (`malloc`, `free`, `calloc`)
* Git & GitHub

---
