#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include "list.h"

//  struct list, list : structure capable de gérer une liste dynamique
//    simplement chainée sur le type void, d'alias list
typedef struct list list;

//  list_empty : crée un objet de type list. La liste est initialement vide.
//    Renvoie un pointeur vers l'objet en cas de succès, NULL en cas d'échec
extern list *list_empty(void);

//  list_is_empty : renvoie true ou false selon que la liste associée à s est
//    vide ou non
extern bool list_is_empty(const list *p);

//  list_length : renvoie la longueur de la liste associée à s
extern size_t list_length(const list *p);

//  list_head_value, list_tail_value : si la liste associée à s n'est pas
//    vide, affecte à *ptr la valeur de l'élément de tête (head) ou de queue
//    (tail) et renvoie zéro. Renvoie une valeur non nulle sinon
extern int list_head_value(const list *p, void **ptr);
extern int list_tail_value(const list *p, void **ptr);

//  list_insert_head, list_insert_tail : insère une copie de *ptr en tête
//    (head) ou en queue (tail) de la liste associée à s. Renvoie zéro en cas de
//    succès, une valeur non nulle en cas d'échec
extern int list_insert_head(list *p, void *ptr);
extern int list_insert_tail(list *p, void *ptr);

//  list_move_head_head, list_move_head_tail : déplace l'élément de tête de la
//    liste associée à src vers la tête (head_head) ou la queue (head_tail) de
//    la liste associée à dest. Renvoie zéro en cas de succès, une valeur non
//    nulle en cas d'échec pour cause de liste associée à src vide
extern int list_move_head_head(list *src, list *dest);
extern int list_move_head_tail(list *src, list *dest);

//  list_move_all_head, list_move_all_tail : déplace en tête (head) ou en
//    queue (tail) de la liste associée à dest la liste associée à src. En cas
//    de succès, la liste associée à src est vide à la terminaison et la
//    fonction renvoie zéro. En cas d'échec, parce que src == dest, renvoie une
//    valeur non nulle
extern int list_move_all_head(list *src, list *dest);
extern int list_move_all_tail(list *src, list *dest);

//  holdall_apply : exécute fun sur les adresses ajoutées au fourretout associé
//    à ha. Si, pour une adresse, fun renvoie une valeur non nulle, l'exécution
//    prend fin et holdall_apply renvoie cette valeur. Sinon, fun est exécutée
//    sur toutes les adresses et holdall_apply renvoie zéro
extern int list_apply(list *p, int (*fun)(void *));

//  list_dispose : si *sptr ne vaut pas NULL, libère les ressources allouées à
//    *sptr ainsi qu'à la liste associée puis affecte la valeur NULL à *sptr
extern void list_dispose(list **ptr);


#endif
