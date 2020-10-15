
// Estruturas
struct no { // Ocupa 10 bytes na simulação do João
	struct no * ant;
	char * nome;
	struct no * prox;
};

typedef struct {
	struct no * inicio;
	struct no * fim;
} lista_sde;

// Funções para a manipulação de listas
void criar(lista_sde *q);
int inserir(lista_sde *q, char novo_item[]);
void mostrar(lista_sde q);
int estaVazia(lista_sde q);
int retirar_por_nome(lista_sde *q, char novo_item[]);

// Funções utilitárias
char * alocar_nova_string(char *texto);