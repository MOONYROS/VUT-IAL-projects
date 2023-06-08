/*
 * Binárny vyhľadávací strom — iteratívna varianta
 *
 * S využitím dátových typov zo súboru btree.h, zásobníkov zo súborov stack.h a
 * stack.c a pripravených kostier funkcií implementujte binárny vyhľadávací
 * strom bez použitia rekurzie.
 */

#include "../btree.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Inicializácia stromu.
 *
 * Užívateľ musí zaistiť, že incializácia sa nebude opakovane volať nad
 * inicializovaným stromom. V opačnom prípade môže dôjsť k úniku pamäte (memory
 * leak). Keďže neinicializovaný ukazovateľ má nedefinovanú hodnotu, nie je
 * možné toto detegovať vo funkcii.
 */
void bst_init(bst_node_t **tree) {
        *tree = NULL;
}

/*
 * Nájdenie uzlu v strome.
 *
 * V prípade úspechu vráti funkcia hodnotu true a do premennej value zapíše
 * hodnotu daného uzlu. V opačnom prípade funckia vráti hodnotu false a premenná
 * value ostáva nezmenená.
 *
 * Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
 */
bool bst_search(bst_node_t *tree, char key, int *value) {
    while(tree != NULL)
    {
        if(key > tree->key)
            tree = tree->right;
        else if(key < tree->key)
            tree = tree->left;
        else
        {
            *value = tree->value;   // uspech, do value zapiseme hodnotu uzlu a vratime true
            return true;
        }
    }
    return false;
}

/*
 * Vloženie uzlu do stromu.
 *
 * Pokiaľ uzol so zadaným kľúčom v strome už existuje, nahraďte jeho hodnotu.
 * Inak vložte nový listový uzol.
 *
 * Výsledný strom musí spĺňať podmienku vyhľadávacieho stromu — ľavý podstrom
 * uzlu obsahuje iba menšie kľúče, pravý väčšie.
 *
 * Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
 */
void bst_insert(bst_node_t **tree, char key, int value) {
    int tmpValue;
    bst_node_t *pTree = *tree;
    bst_node_t *lastNode = *tree;
    bst_node_t *newNode;
    if(bst_search(*tree, key, &tmpValue))
    {
        (*tree)->value = value;
    }
    else
    {
        newNode = malloc(sizeof(bst_node_t));
        if(newNode == NULL)
            return;

        newNode->key = key;
        newNode->value = value;
        newNode->left = NULL;
        newNode->right = NULL;
        if(pTree == NULL)
        {
            *tree = newNode;
            return;
        }
        while(pTree != NULL)
        {
            if(key > pTree->key)
            {
                lastNode = pTree;
                pTree = pTree->right;
            }
            else if(key < pTree->key)
            {
                lastNode = pTree;
                pTree = pTree->left;
            }
        }
        if(key > lastNode->key)
            lastNode->right = newNode;
        else
            lastNode->left = newNode;
    }
}

/*
 * Pomocná funkcia ktorá nahradí uzol najpravejším potomkom.
 *
 * Kľúč a hodnota uzlu target budú nahradené kľúčom a hodnotou najpravejšieho
 * uzlu podstromu tree. Najpravejší potomok bude odstránený. Funkcia korektne
 * uvoľní všetky alokované zdroje odstráneného uzlu.
 *
 * Funkcia predpokladá že hodnota tree nie je NULL.
 *
 * Táto pomocná funkcia bude využitá pri implementácii funkcie bst_delete.
 *
 * Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
 */
void bst_replace_by_rightmost(bst_node_t *target, bst_node_t **tree) {
    // pocitame s tim, ze strom je incializovany
    bst_node_t *pTree = *tree;
    bst_node_t *pPrev = NULL;
 
    while(pTree->right != NULL)
    {
        pPrev = pTree;
        pTree = pTree->right;
    }
    target->key = pTree->key;
    target->value = pTree->value;

    if(pPrev == NULL)
        *tree = pTree->left;
    else
        if(pTree->left != NULL)
            pPrev->right = pTree->left;
        else
            pPrev->right = NULL;
    // printf("MAZEME %c:%d\n", pTree->key, pTree->value);
    free(pTree);
}

/*
 * Odstránenie uzlu v strome.
 *
 * Pokiaľ uzol so zadaným kľúčom neexistuje, funkcia nič nerobí.
 * Pokiaľ má odstránený uzol jeden podstrom, zdedí ho otec odstráneného uzla.
 * Pokiaľ má odstránený uzol oba podstromy, je nahradený najpravejším uzlom
 * ľavého podstromu. Najpravejší uzol nemusí byť listom!
 * Funkcia korektne uvoľní všetky alokované zdroje odstráneného uzlu.
 *
 * Funkciu implementujte iteratívne pomocou bst_replace_by_rightmost a bez
 * použitia vlastných pomocných funkcií.
 */
void bst_delete(bst_node_t **tree, char key) {
    bst_node_t *pNode = *tree;
    bst_node_t **pptr = NULL;
    while(pNode != NULL)
    {
        if(key > pNode->key)
        {
            pptr = &(pNode->right);
            pNode = pNode->right;
        }
        else if(key < pNode->key)
        {
            pptr = &(pNode->left);
            pNode = pNode->left;
        }
        else if(key == pNode->key)
            break;

    }
    if(pNode == NULL)
        return;
    if((pNode->right != NULL) && (pNode->left == NULL))
    {
        if(pptr == NULL)
            *tree = pNode->right;
        else
            *pptr = pNode->right;
        free(pNode);
    }
    else if((pNode->right == NULL) && (pNode->left != NULL))
    {
        if(pptr == NULL)
            *tree = pNode->left;
        else
            *pptr = pNode->left;
        free(pNode);
    }
    else if((pNode->right == NULL) && (pNode->left == NULL))
    {
        *pptr = NULL;
        free(pNode);
    }
    else
        bst_replace_by_rightmost(pNode, &(pNode->left));

    
}

/*
 * Zrušenie celého stromu.
 *
 * Po zrušení sa celý strom bude nachádzať v rovnakom stave ako po
 * inicializácii. Funkcia korektne uvoľní všetky alokované zdroje rušených
 * uzlov.
 *
 * Funkciu implementujte iteratívne pomocou zásobníku uzlov a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_dispose(bst_node_t **tree) {
    stack_bst_t s1;
    stack_bst_init(&s1);
    bst_node_t *pNode = *tree;
    do  
    {
        if (pNode == NULL)
        {
            if (!stack_bst_empty(&s1))
            {
                pNode = stack_bst_top(&s1);
                stack_bst_pop(&s1);
            }
        }
        else
        {
            if (pNode->right != NULL)
                stack_bst_push(&s1, pNode->right);
            bst_node_t *tmpNode = pNode;
            pNode = pNode->left;
            free(tmpNode);
        }
    } while ((pNode != NULL) || (!stack_bst_empty(&s1)));
    *tree = NULL;
}

/*
 * Pomocná funkcia pre iteratívny preorder.
 *
 * Prechádza po ľavej vetve k najľavejšiemu uzlu podstromu.
 * Nad spracovanými uzlami zavola bst_print_node a uloží ich do zásobníku uzlov.
 *
 * Funkciu implementujte iteratívne pomocou zásobníku uzlov a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_leftmost_preorder(bst_node_t *tree, stack_bst_t *to_visit) {
    bst_node_t *pNode = tree;
    
    while(pNode != NULL)
    {
        stack_bst_push(to_visit, pNode);
        bst_print_node(pNode);
        pNode = pNode->left;
    }
}

/*
 * Preorder prechod stromom.
 *
 * Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node.
 *
 * Funkciu implementujte iteratívne pomocou funkcie bst_leftmost_preorder a
 * zásobníku uzlov bez použitia vlastných pomocných funkcií.
 */
void bst_preorder(bst_node_t *tree) {
    stack_bst_t s1;
    bst_node_t *pNode = tree;
    stack_bst_init(&s1);
    
    bst_leftmost_preorder(pNode, &s1);
    while(!stack_bst_empty(&s1))
    {
        pNode = stack_bst_top(&s1);
        stack_bst_pop(&s1);
        bst_leftmost_preorder(pNode->right, &s1);
    }
}

/*
 * Pomocná funkcia pre iteratívny inorder.
 *
 * Prechádza po ľavej vetve k najľavejšiemu uzlu podstromu a ukladá uzly do
 * zásobníku uzlov.
 *
 * Funkciu implementujte iteratívne pomocou zásobníku uzlov a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_leftmost_inorder(bst_node_t *tree, stack_bst_t *to_visit) {
    bst_node_t *pNode = tree;
    while(pNode != NULL)
    {
        stack_bst_push(to_visit, pNode);
        pNode = pNode->left;
    }
}

/*
 * Inorder prechod stromom.
 *
 * Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node.
 *
 * Funkciu implementujte iteratívne pomocou funkcie bst_leftmost_inorder a
 * zásobníku uzlov bez použitia vlastných pomocných funkcií.
 */
void bst_inorder(bst_node_t *tree) {
    stack_bst_t s1;
    bst_node_t *pNode = tree;
    stack_bst_init(&s1);

    bst_leftmost_inorder(pNode, &s1);
    while(!stack_bst_empty(&s1))
    {
        pNode = stack_bst_top(&s1);
        stack_bst_pop(&s1);
        bst_print_node(pNode);
        bst_leftmost_inorder(pNode->right, &s1);
    }
    
}

/*
 * Pomocná funkcia pre iteratívny postorder.
 *
 * Prechádza po ľavej vetve k najľavejšiemu uzlu podstromu a ukladá uzly do
 * zásobníku uzlov. Do zásobníku bool hodnôt ukladá informáciu že uzol
 * bol navštívený prvý krát.
 *
 * Funkciu implementujte iteratívne pomocou zásobníkov uzlov a bool hodnôt a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_leftmost_postorder(bst_node_t *tree, stack_bst_t *to_visit,
                            stack_bool_t *first_visit) {
    bst_node_t *pNode = tree;

    while(pNode != NULL)
    {
        stack_bst_push(to_visit, pNode);
        stack_bool_push(first_visit, true);
        pNode = pNode->left;
    }
    
}

/*
 * Postorder prechod stromom.
 *
 * Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node.
 *
 * Funkciu implementujte iteratívne pomocou funkcie bst_leftmost_postorder a
 * zásobníkov uzlov a bool hodnôt bez použitia vlastných pomocných funkcií.
 */
void bst_postorder(bst_node_t *tree) {
    bool fromLeft;
    bst_node_t *pNode = tree;
    stack_bst_t s1;
    stack_bool_t sBool;
    stack_bst_init(&s1);
    stack_bool_init(&sBool);

    bst_leftmost_postorder(pNode, &s1, &sBool);
    while(!stack_bst_empty(&s1))
    {
        pNode = stack_bst_top(&s1);
        fromLeft = stack_bool_top(&sBool);
        stack_bool_pop(&sBool);

        if(fromLeft)
        {
            stack_bool_push(&sBool, false);
            bst_leftmost_postorder(pNode->right, &s1, &sBool);
        }
        else
        {
            stack_bst_pop(&s1);
            bst_print_node(pNode);
        }
    }
}
