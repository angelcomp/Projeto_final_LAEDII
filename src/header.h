
// Estruturas
struct no_lista { // Ocupa 10 bytes na simulação do João
	struct no_lista * ant;
	char * nome;
	struct no_lista * prox;
};

typedef struct {
	struct no_lista * inicio;
	struct no_lista * fim;
} lista;

struct no_fila {
	char * nome;
	struct no_fila *prox;
};

typedef struct {
	struct no_fila *inicio;
	struct no_fila *fim;
} fila;

// Funções para a manipulação de listas
void lista_criar(lista *q);
int lista_inserir(lista *q, char novo_item[]);
void lista_mostrar(lista q);
int lista_estaVazia(lista q);
int lista_retirar_por_nome(lista *q, char *ptr_novo_nome);
int lista_retirar_por_posicao(lista *q, int indice);
void lista_esvaziar(lista *q);

// Funções para a manipulação de filas
void fila_criar(fila *q);
int fila_inserir(fila *q, char *ptr_nome);
int fila_retirar(fila *q, char receptor_nome[], int tamanho_buffer_receptor);
int fila_estaVazia(fila q);
void fila_mostrar(fila q);
char * fila_inicio(fila q);
int fila_procurar(fila q, char busca[]);
void fila_esvaziar(fila *q);

// Funções do menu
void mostrarCardapio(lista c);
void mostrarPedidos(fila p);
void adicionarItemCardapio(lista *c);
void removerItemCardapio(lista *c);
void cadastrarPedido(fila *p);
void servirPedido(fila *p);

// Funções utilitárias
char * nova_string(char texto[]);