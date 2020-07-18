#include "cola.h"
#include <stdlib.h>

typedef struct nodo {
	void *dato;
	struct nodo *prox;
} nodo_t;

nodo_t* crear_nodo(void* dato){
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if (nodo == NULL){
		return NULL;
	}
	nodo->dato = dato;
	return nodo;
}

void destruir_nodo(nodo_t *nodo){
	free(nodo);
}

struct cola {
	nodo_t *prim;
	nodo_t *ult;
};

cola_t* cola_crear(void){
	cola_t* cola = malloc(sizeof(cola_t)); 
	if (cola == NULL){ 
		return NULL; 
	}
	cola->prim = NULL;
	cola->ult = NULL;
	return cola;
}

void cola_destruir(cola_t *cola, void (*destruir_dato)(void*)){
	while (!cola_esta_vacia(cola)){
		if (destruir_dato != NULL){
			destruir_dato(cola_ver_primero(cola));
		}
		cola_desencolar(cola);		
	}
	free(cola);
}

bool cola_esta_vacia(const cola_t *cola){ 
	return cola->prim == NULL;
}

bool cola_encolar(cola_t *cola, void* valor){
	nodo_t* nuevo_nodo = crear_nodo(valor);
	if (nuevo_nodo == NULL){
		return false;
	}
	if (cola_esta_vacia(cola)){
		cola->prim = nuevo_nodo;
	}
	else {
		cola->ult->prox = nuevo_nodo;	
	}
	cola->ult = nuevo_nodo;
	cola->ult->prox = NULL;
	return true;

}

void* cola_ver_primero(const cola_t *cola){
	if (cola_esta_vacia(cola)){
		return NULL;
	}
	return cola->prim->dato;
}

void* cola_desencolar(cola_t *cola){
	if (cola_esta_vacia(cola)){
		return NULL;
	}
	void* dato = cola->prim->dato;
	nodo_t* nodo_a_destruir = cola->prim;
	cola->prim = cola->prim->prox;
	if (cola_esta_vacia(cola)){
		cola->ult = NULL;
	}
	destruir_nodo(nodo_a_destruir);
	return dato;

}