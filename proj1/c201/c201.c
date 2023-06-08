/* c201.c **********************************************************************
** Téma: Jednosměrný lineární seznam
**
**                     Návrh a referenční implementace: Petr Přikryl, říjen 1994
**                                          Úpravy: Andrea Němcová listopad 1996
**                                                   Petr Přikryl, listopad 1997
**                                Přepracované zadání: Petr Přikryl, březen 1998
**                                  Přepis do jazyka C: Martin Tuček, říjen 2004
**                                              Úpravy: Kamil Jeřábek, září 2020
**                                                    Daniel Dolejška, září 2021
**                                                    Daniel Dolejška, září 2022
**
** Implementujte abstraktní datový typ jednosměrný lineární seznam.
** Užitečným obsahem prvku seznamu je celé číslo typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou typu List.
** Definici konstant a typů naleznete v hlavičkovém souboru c201.h.
**
** Vaším úkolem je implementovat následující operace, které spolu s výše
** uvedenou datovou částí abstrakce tvoří abstraktní datový typ List:
**
**      List_Dispose ....... zrušení všech prvků seznamu,
**      List_Init .......... inicializace seznamu před prvním použitím,
**      List_InsertFirst ... vložení prvku na začátek seznamu,
**      List_First ......... nastavení aktivity na první prvek,
**      List_GetFirst ...... vrací hodnotu prvního prvku,
**      List_DeleteFirst ... zruší první prvek seznamu,
**      List_DeleteAfter ... ruší prvek za aktivním prvkem,
**      List_InsertAfter ... vloží nový prvek za aktivní prvek seznamu,
**      List_GetValue ...... vrací hodnotu aktivního prvku,
**      List_SetValue ...... přepíše obsah aktivního prvku novou hodnotou,
**      List_Next .......... posune aktivitu na další prvek seznamu,
**      List_IsActive ...... zjišťuje aktivitu seznamu.
**
** Při implementaci funkcí nevolejte žádnou z funkcí implementovaných v rámci
** tohoto příkladu, není-li u dané funkce explicitně uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam předá
** někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako procedury
** (v jazyce C procedurám odpovídají funkce vracející typ void).
**
**/

#include "c201.h"

#include <stdio.h> // printf
#include <stdlib.h> // malloc, free

int error_flag;
int solved;

/**
 * Vytiskne upozornění na to, že došlo k chybě. Nastaví error_flag na logickou 1.
 * Tato funkce bude volána z některých dále implementovaných operací.
 */
void List_Error() {
	printf("*ERROR* The program has performed an illegal operation.\n");
	error_flag = TRUE;
}

/**
 * Provede inicializaci seznamu list před jeho prvním použitím (tzn. žádná
 * z následujících funkcí nebude volána nad neinicializovaným seznamem).
 * Tato inicializace se nikdy nebude provádět nad již inicializovaným
 * seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
 * že neinicializované proměnné mají nedefinovanou hodnotu.
 *
 * @param list Ukazatel na strukturu jednosměrně vázaného seznamu
 */
void List_Init( List *list ) {
	
	/** Nastavim si prvni a aktivni element na NULL, nikam neukazuji. */
	list->firstElement = NULL;
	list->activeElement = NULL;
}

/**
 * Zruší všechny prvky seznamu list a uvede seznam list do stavu, v jakém se nacházel
 * po inicializaci. Veškerá paměť používaná prvky seznamu list bude korektně
 * uvolněna voláním operace free.
 *
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 **/
void List_Dispose( List *list ) {

	// Kontrola existence seznamu
	if(list == NULL)
		return;

	ListElementPtr tmpElement = list->firstElement;
	
	list->firstElement = NULL;
	list->activeElement = NULL;
	
    while(tmpElement != NULL)
    {
        ListElementPtr toDelete = tmpElement;	// vytvoreni prvku, ktery budu mazat, abych neztratil tmpElement
        tmpElement = tmpElement->nextElement;
        free(toDelete);
    }
}

/**
 * Vloží prvek s hodnotou data na začátek seznamu list.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci List_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 * @param data Hodnota k vložení na začátek seznamu
 */
void List_InsertFirst( List *list, int data ) {

	// Kontrola existence seznamu
	if(list == NULL)
		return;

	struct ListElement *newElement = malloc(sizeof(struct ListElement));	// alokace noveho prvku, ktery budu vkladat
	if(newElement == NULL)	// pokud se alokace nepovedla, volam error
		List_Error();
	else
	{
		newElement->data = data;
		newElement->nextElement = list->firstElement;	
		list->firstElement = newElement;	// prvku dam data a nastavim ho, jako prvni retezec v seznamu
	}
}

/**
 * Nastaví aktivitu seznamu list na jeho první prvek.
 * Funkci implementujte jako jediný příkaz, aniž byste testovali,
 * zda je seznam list prázdný.
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 */
void List_First( List *list ) {

	// nastaveni aktivniho elementu na prvni element seznamu
	list->activeElement = list->firstElement;
}

/**
 * Prostřednictvím parametru dataPtr vrátí hodnotu prvního prvku seznamu list.
 * Pokud je seznam list prázdný, volá funkci List_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void List_GetFirst( List *list, int *dataPtr ) {

	// kontrola existence seznamu
	if(list == NULL)
		return;

	if(list->firstElement == NULL)	// pokud prvni element neexistuje, volam error
		List_Error();
	else
		if(dataPtr != NULL)
			*dataPtr = list->firstElement->data;	// do dataPtr dam data prvniho elementu
}

/**
 * Zruší první prvek seznamu list a uvolní jím používanou paměť.
 * Pokud byl rušený prvek aktivní, aktivita seznamu se ztrácí.
 * Pokud byl seznam list prázdný, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 */
void List_DeleteFirst( List *list ) {

	if((list == NULL) || (list->firstElement == NULL))
		return;

	if(list->firstElement == list->activeElement)
		list->activeElement = NULL;	//prvni prvek seznamu byl aktivni => aktivita senzamu se ztraci

	ListElementPtr tmpElement = list->firstElement;
	list->firstElement = tmpElement->nextElement;
	free(tmpElement);	// druhy element nastavim na prvni a puvodne prvni element smazu
}

/**
 * Zruší prvek seznamu list za aktivním prvkem a uvolní jím používanou paměť.
 * Pokud není seznam list aktivní nebo pokud je aktivní poslední prvek seznamu list,
 * nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 */
void List_DeleteAfter( List *list ) {
	
	// kontrola existence seznamu
	if(list == NULL)
		return;

	if((list->activeElement == NULL) || (list->activeElement->nextElement == NULL))
		return;	// splneni podminky, ze pokud neni senzam aktivni nebo jeho posledni prvek, nic se nedeje

	ListElementPtr tmpElement = list->activeElement->nextElement;
	list->activeElement->nextElement = tmpElement->nextElement;
	free(tmpElement);	// tmpElement nastavim za aktivni element, zmenim ukazatele a smazu tmpElement
}

/**
 * Vloží prvek s hodnotou data za aktivní prvek seznamu list.
 * Pokud nebyl seznam list aktivní, nic se neděje!
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * zavolá funkci List_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 * @param data Hodnota k vložení do seznamu za právě aktivní prvek
 */
void List_InsertAfter( List *list, int data ) {

	// overeni existence seznamu a kontrola, jestli je seznam aktivni
	if((list == NULL) || (list->activeElement == NULL))
		return;
	
	struct ListElement *newElement = malloc(sizeof(struct ListElement));	// alokace noveho prvku
	if(newElement == NULL)
	{
		List_Error();
		return;
	}

	newElement->data = data;
	newElement->nextElement = list->activeElement->nextElement;
	list->activeElement->nextElement = newElement;	// do noveho prvku dam data a postavim ho za aktivni element a prenastavim ukazatele
}

/**
 * Prostřednictvím parametru dataPtr vrátí hodnotu aktivního prvku seznamu list.
 * Pokud seznam není aktivní, zavolá funkci List_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void List_GetValue( List *list, int *dataPtr ) {

	// kontrola existence seznamu
	if(list == NULL)
		return;

	if(list->activeElement == NULL)	// pokud seznam neni aktivni, volam error
	{
		List_Error();
		return;
	}
	else
		*dataPtr = list->activeElement->data; // do dataPtr dam hodnotu aktivniho prvku seznamu
}

/**
 * Přepíše data aktivního prvku seznamu list hodnotou data.
 * Pokud seznam list není aktivní, nedělá nic!
 *
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 * @param data Nová hodnota právě aktivního prvku
 */
void List_SetValue( List *list, int data ) {

	// pokud neni seznam nebo neni aktivni, nic se nedeje
	if((list == NULL) || (list->activeElement == NULL))
		return;
	else
		list->activeElement->data = data;	// aktivnimu prvku predam pozadovana data
}

/**
 * Posune aktivitu na následující prvek seznamu list.
 * Všimněte si, že touto operací se může aktivní seznam stát neaktivním.
 * Pokud není předaný seznam list aktivní, nedělá funkce nic.
 *
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 */
void List_Next( List *list ) {

	if((list == NULL) || (list->activeElement == NULL))	// pokud senzam neexistuje nebo neni aktivni, nedeje se nic
		return;
	else if(list->activeElement->nextElement == NULL)
		list->activeElement = NULL;	// pokud je aktivni prvek zaroven posledni, ztraci se aktivita seznamu
	else
		list->activeElement = list->activeElement->nextElement;	// pokud je nejaky prvek za aktivnim, prenastavi se aktivita za aktivni prvek
}

/**
 * Je-li seznam list aktivní, vrací nenulovou hodnotu, jinak vrací 0.
 * Tuto funkci je vhodné implementovat jedním příkazem return.
 *
 * @param list Ukazatel na inicializovanou strukturu jednosměrně vázaného seznamu
 */
int List_IsActive( List *list ) {

	// pokud seznam neexistuje nebo neni aktivni, vraci nulu
	/*if((list == NULL) || (list->activeElement == NULL))
		return 0;
	else	// jinak vraci jednicku (nenulovou hodnotu)
		return 1;*/

	return (list->activeElement != NULL);	// jestlize seznam je aktivni, vracime true (nenulova hodnota), jinak vraci false, tedy 0
}

/* Konec c201.c */
