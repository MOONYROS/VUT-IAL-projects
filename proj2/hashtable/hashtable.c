/*
 * Tabuľka s rozptýlenými položkami
 *
 * S využitím dátových typov zo súboru hashtable.h a pripravených kostier
 * funkcií implementujte tabuľku s rozptýlenými položkami s explicitne
 * zreťazenými synonymami.
 *
 * Pri implementácii uvažujte veľkosť tabuľky HT_SIZE.
 */

#include "hashtable.h"
#include <stdlib.h>
#include <string.h>

int HT_SIZE = MAX_HT_SIZE;

/*
 * Rozptyľovacia funkcia ktorá pridelí zadanému kľúču index z intervalu
 * <0,HT_SIZE-1>. Ideálna rozptyľovacia funkcia by mala rozprestrieť kľúče
 * rovnomerne po všetkých indexoch. Zamyslite sa nad kvalitou zvolenej funkcie.
 */
int get_hash(char *key) {
  int result = 1;
  int length = strlen(key);
  for (int i = 0; i < length; i++) {
    result += key[i];
  }
  return (result % HT_SIZE);
}

/*
 * Inicializácia tabuľky — zavolá sa pred prvým použitím tabuľky.
 */
void ht_init(ht_table_t *table) {
    for(int i = 0; i < HT_SIZE; i++)
        (*table)[i] = NULL;
}

/*
 * Vyhľadanie prvku v tabuľke.
 *
 * V prípade úspechu vráti ukazovateľ na nájdený prvok; v opačnom prípade vráti
 * hodnotu NULL.
 */
ht_item_t *ht_search(ht_table_t *table, char *key) {
    if(table == NULL)
        return NULL;
    
    int index = get_hash(key);
    ht_item_t *tmpItem = (*table)[index];

    while(tmpItem != NULL)
    {
        if(strcmp(tmpItem->key, key) == 0)
            return tmpItem;
        
        tmpItem = tmpItem->next;
    }
    return NULL;
}

/*
 * Vloženie nového prvku do tabuľky.
 *
 * Pokiaľ prvok s daným kľúčom už v tabuľke existuje, nahraďte jeho hodnotu.
 *
 * Pri implementácii využite funkciu ht_search. Pri vkladaní prvku do zoznamu
 * synonym zvoľte najefektívnejšiu možnosť a vložte prvok na začiatok zoznamu.
 */
void ht_insert(ht_table_t *table, char *key, float value) {
    ht_item_t *foundItem = ht_search(table, key);
    if(foundItem != NULL)
        foundItem->value = value;
    else
    {
        int index = get_hash(key);
        ht_item_t *tmpItem = (*table)[index]; 
        ht_item_t *newItem = malloc(sizeof(ht_item_t));
        if(newItem == NULL)
            return;
        newItem->key = key;
        newItem->value = value;
        newItem->next = NULL;
        if(tmpItem == NULL)
            (*table)[index] = newItem;
        else
        {
            newItem->next = tmpItem;
            (*table)[index] = newItem;
        }
    }
}

/*
 * Získanie hodnoty z tabuľky.
 *
 * V prípade úspechu vráti funkcia ukazovateľ na hodnotu prvku, v opačnom
 * prípade hodnotu NULL.
 *
 * Pri implementácii využite funkciu ht_search.
 */
float *ht_get(ht_table_t *table, char *key) {
    if(table != NULL)
    {
        ht_item_t *foundItem = ht_search(table, key);
        if(foundItem != NULL)
            return &foundItem->value;
    }
    return NULL;
}

/*
 * Zmazanie prvku z tabuľky.
 *
 * Funkcia korektne uvoľní všetky alokované zdroje priradené k danému prvku.
 * Pokiaľ prvok neexistuje, nerobte nič.
 *
 * Pri implementácii NEVYUŽÍVAJTE funkciu ht_search.
 */
void ht_delete(ht_table_t *table, char *key) {
    if(table != NULL)
    {
        int index = get_hash(key);
        ht_item_t *item = (*table)[index];
        ht_item_t *prevItem = NULL; // pomocny prvek, pokud se pri kolizi stane, ze nebude hledany prvek prvni v seznamu
        while(item != NULL)
        {
            if(strcmp(item->key, key) == 0)
            {
                ht_item_t *toDelete = item;
                if((*table)[index] == item) //prvek je na prvnim miste
                {
                    (*table)[index] = item->next;
                    free(toDelete);
                }
                else //prvek je na jinem nez prvnim miste (potreba pouzit prevItem)
                {
                    prevItem->next = toDelete->next;
                    free(toDelete);
                }
                return;
            }
            prevItem = item;
            item = item->next;
        }
    }
}

/*
 * Zmazanie všetkých prvkov z tabuľky.
 *
 * Funkcia korektne uvoľní všetky alokované zdroje a uvedie tabuľku do stavu po
 * inicializácii.
 */
void ht_delete_all(ht_table_t *table) {
    for (int i = 0; i < HT_SIZE; i++)
    {
        if ((*table)[i] != NULL)
        {
            ht_item_t *tmpItem = (*table)[i]->next;
            while (tmpItem != NULL)
            {
                ht_item_t *toDelete = tmpItem;
                tmpItem = tmpItem->next;
                free(toDelete);
            }
            free((*table)[i]);
            (*table)[i] = NULL;
        }
        
    }
}
