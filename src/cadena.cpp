#include "../include/cadena.h"
#include "../include/info.h"

#include <stddef.h>
#include <stdio.h>
#include <assert.h>

struct nodo {
    info_t dato;
    nodo *anterior;
    nodo *siguiente;
};

struct rep_cadena {
    nodo *inicio;
    nodo *final;
};

cadena_t crear_cadena(){
    cadena_t res = new rep_cadena;
    res->inicio = res->final = NULL;
    return res;
}

void insertar_al_final(info_t i, cadena_t &cad){
    nodo *nuevo = new nodo;
    nuevo->dato = i;
    nuevo->siguiente = NULL;
    nuevo->anterior = cad->final;
    if (cad->final == NULL){
        assert(cad->inicio == NULL);
        cad->inicio = nuevo;
    } else {
        assert(cad->inicio != NULL);
        cad->final->siguiente = nuevo;
    }
    cad->final = nuevo;
}


void insertar_antes(info_t i, localizador_t loc, cadena_t &cad){
    nodo *nuevo = new nodo;
    nuevo-> dato=i;
    nuevo->anterior=anterior(loc,cad)->dato;
    nuevo->siguiente=siguiente(loc,cad)->dato;
    localizador_t locf=nuevo;
    if (!es_vacia_cadena(cad)){
    anterior(loc, cad)->siguiente=locf->dato;
    siguiente(loc,cad)->anterior=locf->dato;
    }
}

void insertar_segmento_despues(cadena_t &sgm, localizador_t loc, cadena_t &cad) {
    assert(es_vacia_cadena(cad) || precede_en_cadena(desde, hasta, cad));
    cadena_t res= crear_cadena();
    if (!es_vacia_cadena(cad)){
        localizador_t loc = desde;
        while (loc != siguiente(hasta,cad)){
            // ERROR: compartiria memoria
            // info_t info = loc -> dato;
            info_t info = copia_info((loc->dato));
            insertar_al_final(info, res);
            loc = siguiente(loc, cad);
        }
    }
    return res;
}

void liberar_cadena(cadena_t &cad) {
    nodo *a_borrar;
    while (cad-inicio != NULL) {
        a_borrar = cad->inicio;
        cad->inicio = cad->inicio->siguiente;
        liberar_info(a_borrar->dato);
        delete(a_borrar);
    }
    delete cad;
}

bool es_localizador(localizador_t loc){
    return loc != NULL;
}

bool es_vacia_cadena(cadena_t cad){
    bool res = true;
    if (!es_vacia_cadena(cad)){
        localizador_t loc = inicio_cadena(cad);
        while (res && es_localizador(siguiente(loc, cad))){
            localizador_t sig_loc = siguiente(loc, cad);
            if (numero_info(info_cadena(loc, cad)) > numero_info(info_cadena(sig_loc, cad))) res = false;
            else loc = siguiente(loc, cad);
        }
    }
    return res;
}

bool precede_en_cadena(localizador_t loc1, localizador_t loc2, cadena_t cad) {
    localizador_t cursor = loc1;
    while (es_localizador(cursor) && (cursor != loc2))
        cursor = siguiente(cursor, cad);
    return ((cursor == loc2 && (localizador_en_cadena(loc1, cad)));
}

localizador_t menor_en_cadena(localizador_t loc, cadena_t cad) {
    assert(localizador_en_cadena(loc, cad));
    localizador_t res = loc;
    while (es_localizador(siguiente(loc, cad))) {
        loc = siguiente(loc, cad);
        if (numero_info(info_cadena(loc, cad)) < numero_info(info_cadena(res, cad)))
            res = loc;
    }
    return res;
}

localizador_t siguiente_clave(int clave, localizador_t loc, cadena_t cad) {
    assert(es_vacia_cadena(cad) || localizador_en_cadena(loc, cad));
    localizador_t res = loc;
    if (es_vacia_cadena(cad))
        res = NULL;
    else {
        while (es_localizador(res) && numero_info(info_cadena(res, cad)) != clave)
            res = siguiente(res, cad);
    }
    return res;
}

void cambiar_en_cadena(info_t, localizador_t loc, cadena_t &cad){
    assert(localizador_en_cadena(loc, cad));
    loc->dato = i;
}