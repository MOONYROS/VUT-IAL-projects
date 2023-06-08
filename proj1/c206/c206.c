/* ******************************* c206.c *********************************** */
/*  Předmět: Algoritmy (IAL) - FIT VUT v Brně                                 */
/*  Úkol: c206 - Dvousměrně vázaný lineární seznam                            */
/*  Návrh a referenční implementace: Bohuslav Křena, říjen 2001               */
/*  Vytvořil: Martin Tuček, říjen 2004                                        */
/*  Upravil: Kamil Jeřábek, září 2020                                         */
/*           Daniel Dolejška, září 2021                                       */
/*           Daniel Dolejška, září 2022                                       */
/* ************************************************************************** */
/*
** Implementujte abstraktní datový typ dvousměrně vázaný lineární seznam.
** Užitečným obsahem prvku seznamu je hodnota typu int. Seznam bude jako datová
** abstrakce reprezentován proměnnou typu DLList (DL znamená Doubly-Linked
** a slouží pro odlišení jmen konstant, typů a funkcí od jmen u jednosměrně
** vázaného lineárního seznamu). Definici konstant a typů naleznete
** v hlavičkovém souboru c206.h.
**
** Vaším úkolem je implementovat následující operace, které spolu s výše
** uvedenou datovou částí abstrakce tvoří abstraktní datový typ obousměrně
** vázaný lineární seznam:
**
**      DLL_Init ........... inicializace seznamu před prvním použitím,
**      DLL_Dispose ........ zrušení všech prvků seznamu,
**      DLL_InsertFirst .... vložení prvku na začátek seznamu,
**      DLL_InsertLast ..... vložení prvku na konec seznamu,
**      DLL_First .......... nastavení aktivity na první prvek,
**      DLL_Last ........... nastavení aktivity na poslední prvek,
**      DLL_GetFirst ....... vrací hodnotu prvního prvku,
**      DLL_GetLast ........ vrací hodnotu posledního prvku,
**      DLL_DeleteFirst .... zruší první prvek seznamu,
**      DLL_DeleteLast ..... zruší poslední prvek seznamu,
**      DLL_DeleteAfter .... ruší prvek za aktivním prvkem,
**      DLL_DeleteBefore ... ruší prvek před aktivním prvkem,
**      DLL_InsertAfter .... vloží nový prvek za aktivní prvek seznamu,
**      DLL_InsertBefore ... vloží nový prvek před aktivní prvek seznamu,
**      DLL_GetValue ....... vrací hodnotu aktivního prvku,
**      DLL_SetValue ....... přepíše obsah aktivního prvku novou hodnotou,
**      DLL_Previous ....... posune aktivitu na předchozí prvek seznamu,
**      DLL_Next ........... posune aktivitu na další prvek seznamu,
**      DLL_IsActive ....... zjišťuje aktivitu seznamu.
**
** Při implementaci jednotlivých funkcí nevolejte žádnou z funkcí
** implementovaných v rámci tohoto příkladu, není-li u funkce explicitně
 * uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam
** předá někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako procedury
** (v jazyce C procedurám odpovídají funkce vracející typ void).
**
**/

#include "c206.h"

int error_flag;
int solved;

/**
 * Vytiskne upozornění na to, že došlo k chybě.
 * Tato funkce bude volána z některých dále implementovaných operací.
 */
void DLL_Error() {
	printf("*ERROR* The program has performed an illegal operation.\n");
	error_flag = TRUE;
}

/**
 * Provede inicializaci seznamu list před jeho prvním použitím (tzn. žádná
 * z následujících funkcí nebude volána nad neinicializovaným seznamem).
 * Tato inicializace se nikdy nebude provádět nad již inicializovaným seznamem,
 * a proto tuto možnost neošetřujte.
 * Vždy předpokládejte, že neinicializované proměnné mají nedefinovanou hodnotu.
 *
 * @param list Ukazatel na strukturu dvousměrně vázaného seznamu
 */
void DLL_Init( DLList *list ) {
	
	list->firstElement = NULL;
	list->lastElement = NULL;
	list->activeElement = NULL;	// incializace seznamu
}

/**
 * Zruší všechny prvky seznamu list a uvede seznam do stavu, v jakém se nacházel
 * po inicializaci.
 * Rušené prvky seznamu budou korektně uvolněny voláním operace free.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Dispose( DLList *list ) {
	
	/** Kontrola existence retezce. */
	if(list == NULL)
		return;

	DLLElementPtr tmpElement = list->firstElement;
	
	list->firstElement = NULL;
	list->lastElement = NULL;
	list->activeElement = NULL;	// vytvorim si tmpElement a smazu ukazatel na aktivini, prvni a posledni prvek
	
    while(tmpElement != NULL)
    {
        DLLElementPtr toDelete = tmpElement;
        tmpElement = tmpElement->nextElement;
        free(toDelete);	// vytvorim si nahradni prvek, ktery budu mazat, predtim ale prenastavim tmpElement
    }
}

/**
 * Vloží nový prvek na začátek seznamu list.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení na začátek seznamu
 */
void DLL_InsertFirst( DLList *list, int data ) {

	if(list == NULL)
		return;

	struct DLLElement *newElement = malloc(sizeof(struct DLLElement));
	if(newElement == NULL)
	{
		DLL_Error();
		return;	// alokace noveho prvku, pokud se nepovede, volam error a vracim se z funkce
	}
	else if(list->firstElement == NULL)	// pokud v seznamu neni prvni prvek, novy prvek se nastavi na prvni a zaroven posledni prvek v seznamu
	{
		newElement->nextElement = NULL;
		newElement->previousElement = NULL;
		list->firstElement = newElement;
		list->lastElement = newElement;
	}
	else	// pokud v seznamu je prvni prvek, prenastavim ukazatele a novy prvek nastavim na prvni prvek
	{
		newElement->nextElement = list->firstElement;
		newElement->previousElement = NULL;
		list->firstElement->previousElement = newElement;
		list->firstElement = newElement;
	}

	newElement->data = data;	// nakonec novemu prvku priradim data
}

/**
 * Vloží nový prvek na konec seznamu list (symetrická operace k DLL_InsertFirst).
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení na konec seznamu
 */
void DLL_InsertLast( DLList *list, int data ) {

	if(list == NULL)
		return;	// alokace noveho prvku, pokud se nepovede, volam error a vracim se z funkce

	struct DLLElement *newElement = malloc(sizeof(struct DLLElement));

	if(newElement == NULL)
	{
		DLL_Error();
		return;
	}
	else if(list->lastElement == NULL)	// pokud v seznamu neni posledni prvek, novy prvek se nastavi na prvni a zaroven posledni prvek TATO SITUACE BY NIKDY NEMELA NASTAT
	{
		newElement->nextElement = NULL;
		newElement->previousElement = NULL;
		list->firstElement = newElement;
		list->lastElement = newElement;	
	}
	else	// pokud v seznamu je posledni prvek, prenastavim ukazatele a novy prvek nastavim na posledni prvek
	{
		newElement->nextElement = NULL;
		newElement->previousElement = list->lastElement;
		list->lastElement->nextElement = newElement;
		list->lastElement = newElement;
	}

	newElement->data = data;
}

/**
 * Nastaví první prvek seznamu list jako aktivní.
 * Funkci implementujte jako jediný příkaz, aniž byste testovali,
 * zda je seznam list prázdný.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_First( DLList *list ) {

	list->activeElement = list->firstElement;	// nastavim prvni prvek seznamu na aktivni prvek
}

/**
 * Nastaví poslední prvek seznamu list jako aktivní.
 * Funkci implementujte jako jediný příkaz, aniž byste testovali,
 * zda je seznam list prázdný.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Last( DLList *list ) {

	list->activeElement = list->lastElement;	// nastavi posledni prvek senzamu jako aktivni
}

/**
 * Prostřednictvím parametru dataPtr vrátí hodnotu prvního prvku seznamu list.
 * Pokud je seznam list prázdný, volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void DLL_GetFirst( DLList *list, int *dataPtr ) {

	if(list == NULL)	// pokud seznam neexistuje, vracim se z funkce
		return;
	else if((list->firstElement == NULL) || (list->lastElement == NULL)) // pokud je senzam prazdny (chybi prvni nebo posledni prvek) volame error
	{
		DLL_Error();
		return;
	}
	else
		if(dataPtr != NULL)
			*dataPtr = list->firstElement->data;	// do dataPtr davam hodnotu prvniho elementu
}

/**
 * Prostřednictvím parametru dataPtr vrátí hodnotu posledního prvku seznamu list.
 * Pokud je seznam list prázdný, volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void DLL_GetLast( DLList *list, int *dataPtr ) {

	if(list == NULL)	// pokud senzam neexistuje, vracim se z funkce
		return;
	else if((list->firstElement == NULL) || (list->lastElement == NULL))	// pokud je senzam prazdny (chybi prvni nebo posledni prvek) volame error
	{
		DLL_Error();
		return;
	}
	else
		if(dataPtr != NULL)
			*dataPtr = list->lastElement->data;	// do dataPtr davam hodnotu posledniho elementu
}

/**
 * Zruší první prvek seznamu list.
 * Pokud byl první prvek aktivní, aktivita se ztrácí.
 * Pokud byl seznam list prázdný, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteFirst( DLList *list ) {

	if((list == NULL) || (list->firstElement == NULL))	// pokud senzam neexistuje nebo je prazdny, vracim se z funkce
		return;

	if(list->firstElement == list->activeElement)	// pokud je prvni prvek zaroven aktivni, aktivita senzamu se ztraci
		list->activeElement = NULL;
	else if(list->firstElement->nextElement == NULL)	// pokud je prvni prvek jediny prvek v seznamu, uvolnime ho a first a last element nastavime na NULL
	{
		free(list->firstElement);
		list->firstElement = NULL;
		list->lastElement = NULL;
	}
	else	// v jinem pripade nastavime dalsi prvek od prvniho prvku na prvni prvek seznamu a puvodni prvni prvek uvolnime
	{
		DLLElementPtr tmpElement = list->firstElement;
		list->firstElement = tmpElement->nextElement;
		list->firstElement->previousElement = NULL;
		free(tmpElement);
	}
}

/**
 * Zruší poslední prvek seznamu list.
 * Pokud byl poslední prvek aktivní, aktivita seznamu se ztrácí.
 * Pokud byl seznam list prázdný, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteLast( DLList *list ) {

	if((list == NULL) || (list->firstElement == NULL) || (list->lastElement == NULL))	// pokud seznam neexistuje nebo pokud neexistuje prvni nebo posledni prvek, vracime se z funkce
		return;

	if(list->lastElement == list->activeElement)	// pokud je posledni prvek zaroven aktivni, aktivita senzamu se ztraci
		list->activeElement = NULL;
	else if(list->lastElement->previousElement == NULL) // pokud byl posledni prvek nemel predchozi prvek, uvolnime ho a first a last element nastavime na NULL
	{
		free(list->lastElement);
		list->firstElement = NULL;
		list->lastElement = NULL;
	}
	else	// v jinem pripade nastavime predchozi prvek od posledniho prvku na posledni prvek seznamu a puvodni prvni prvek uvolnime
	{
		DLLElementPtr tmpElement = list->lastElement;
		list->lastElement = tmpElement->previousElement;
		list->lastElement->nextElement = NULL;
		free(tmpElement);
	}
}

/**
 * Zruší prvek seznamu list za aktivním prvkem.
 * Pokud je seznam list neaktivní nebo pokud je aktivní prvek
 * posledním prvkem seznamu, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteAfter( DLList *list ) {

	if((list == NULL) || (list->activeElement == NULL) || (list->activeElement == list->lastElement))	// pokud seznam neexistuje nebo pokud neexistuje aktivni nebo je aktivni zaroven posledni
		return;

	DLLElementPtr tmpElement = list->activeElement->nextElement;	// tmpElement nastavime na prvek, ktery budeme mazat

	if(tmpElement->nextElement == NULL)	// pokud je tmpElement posledni prvek seznamu, aktivni prvek nastavime na posledni prvek a tmpElement smazeme
	{
		list->activeElement->nextElement = NULL;
		list->lastElement = list->activeElement;
		free(tmpElement);
	}
	else	// jinak prenastavime ukazatele a tmpElement uvolnime
	{
		list->activeElement->nextElement = tmpElement->nextElement;
		tmpElement->nextElement->previousElement = list->activeElement;
		free(tmpElement);
	}
}

/**
 * Zruší prvek před aktivním prvkem seznamu list .
 * Pokud je seznam list neaktivní nebo pokud je aktivní prvek
 * prvním prvkem seznamu, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteBefore( DLList *list ) {

	if((list == NULL) || (list->activeElement == NULL) || (list->activeElement == list->firstElement))	// pokud seznam neexistuje nebo pokud neexistuje aktivni nebo je aktivni zaroven prvni
		return;

	DLLElementPtr tmpElement = list->activeElement->previousElement;	// tmpElement nastavim na mazany element
	
	if(tmpElement->previousElement == NULL)	// pokud tmpElement nema predchozi element, prenastavime ukazatel a active element bude zaroven first a uvolnime tmpElement
	{
		list->activeElement->previousElement = NULL;
		list->firstElement = list->activeElement;
		free(tmpElement);
	}
	else	// jinak prenastavime ukazatele a uvolnime tmpElement
	{
		list->activeElement->previousElement = tmpElement->previousElement;
		tmpElement->previousElement->nextElement = list->activeElement;
		free(tmpElement);
	}
}

/**
 * Vloží prvek za aktivní prvek seznamu list.
 * Pokud nebyl seznam list aktivní, nic se neděje.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení do seznamu za právě aktivní prvek
 */
void DLL_InsertAfter( DLList *list, int data ) {

	if((list == NULL) || (list->activeElement == NULL))	// pokud seznam neexistuje nebo neexistuje aktivni prvek, vracime se z funkce
		return;

	struct DLLElement *newElement = malloc(sizeof(struct DLLElement));
	if(newElement == NULL)	// alokujeme novy prvek, pri neuspesne alokaci volame error a vracime se z funkce
	{
		DLL_Error();
		return;
	}
	else if(list->activeElement == list->lastElement)	// pokud je aktivni prvek zaroven posledni prvek, prenastavime ukazetel a novy prvek nastavime zaroven na posledni prvek seznamu
	{
		newElement->nextElement = NULL;
		newElement->previousElement = list->activeElement;
		list->activeElement->nextElement = newElement;
		list->lastElement = newElement;
	}
	else	// jinak prenastavime ukazatele a novy prvek vlozime za aktivni prvek do seznamu
	{
		newElement->nextElement = list->activeElement->nextElement;
		newElement->previousElement = list->activeElement;
		list->activeElement->nextElement = newElement;
	}

	newElement->data = data;	// novemu prvku nakonec dame jeho data
}

/**
 * Vloží prvek před aktivní prvek seznamu list.
 * Pokud nebyl seznam list aktivní, nic se neděje.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení do seznamu před právě aktivní prvek
 */
void DLL_InsertBefore( DLList *list, int data ) {

	if((list == NULL) || (list->activeElement == NULL))	// pokud seznam neexistuje nebo neni aktivni, vracime se z funkce
		return;

	struct DLLElement *newElement = malloc(sizeof(struct DLLElement));
	if(newElement == NULL)	// pokud se nepodarilo alokovat novy prvek, volame error a vracime se z funkce
	{
		DLL_Error();
		return;
	}
	else if(list->activeElement == list->firstElement)	// pokud je aktivni prvek zaroven prvni prvek, prenastavime ukazetel a novy prvek nastavime zaroven na prvni prvek seznamu
	{
		newElement->nextElement = list->activeElement;
		newElement->previousElement = NULL;
		list->activeElement->previousElement = newElement;
		list->firstElement = newElement;
	}
	else	// jinak prenastavime ukazatele a novy prvek vlozime pred aktivni prvek do seznamu
	{
		newElement->nextElement = list->activeElement;
		newElement->previousElement = list->activeElement->previousElement;
		list->activeElement->previousElement = newElement;
	}

	newElement->data = data;	// novemu prvku nakonec dame jeho data
}

/**
 * Prostřednictvím parametru dataPtr vrátí hodnotu aktivního prvku seznamu list.
 * Pokud seznam list není aktivní, volá funkci DLL_Error ().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void DLL_GetValue( DLList *list, int *dataPtr ) {

	if(list == NULL)	// pokud seznam neexistuje, vracime se z funkce
		return;

	if(list->activeElement == NULL)	// pokud seznam nema aktivni prvek, volame error a vracime se z funkce
	{
		DLL_Error();
		return;
	}
	else
		*dataPtr = list->activeElement->data;	// davame do dataPtr hodnotu aktivniho prvku
}

/**
 * Přepíše obsah aktivního prvku seznamu list.
 * Pokud seznam list není aktivní, nedělá nic.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Nová hodnota právě aktivního prvku
 */
void DLL_SetValue( DLList *list, int data ) {

	if((list == NULL) || (list->activeElement == NULL))	// pokud seznam neexistuje nebo neni aktivni, vracime se z funkce
		return;
	else
		list->activeElement->data = data;	// do aktivniho prvku vlozime data
}

/**
 * Posune aktivitu na následující prvek seznamu list.
 * Není-li seznam aktivní, nedělá nic.
 * Všimněte si, že při aktivitě na posledním prvku se seznam stane neaktivním.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Next( DLList *list ) {

	if((list == NULL) || (list->activeElement == NULL))	// pokud seznam neexistuje nebo neni aktivni, vracime se z funkce
		return;
	else
	{
		DLLElementPtr tmpElement = list->activeElement->nextElement;	// aktivni prvek nastavime na dalsi prvek aktivniho prvku seznamu
		list->activeElement = tmpElement;
	}
}


/**
 * Posune aktivitu na předchozí prvek seznamu list.
 * Není-li seznam aktivní, nedělá nic.
 * Všimněte si, že při aktivitě na prvním prvku se seznam stane neaktivním.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Previous( DLList *list ) {

	if((list == NULL) || (list->activeElement == NULL))	// pokud seznam neexistuje nebo neni aktivni, vracime se z funkce
		return;
	else
	{
		DLLElementPtr tmpElement = list->activeElement->previousElement;	// aktivni prvek nastavime na predochozi prvek aktivniho prvku seznamu
		list->activeElement = tmpElement;
	}

}

/**
 * Je-li seznam list aktivní, vrací nenulovou hodnotu, jinak vrací 0.
 * Funkci je vhodné implementovat jedním příkazem return.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 *
 * @returns Nenulovou hodnotu v případě aktivity prvku seznamu, jinak nulu
 */
int DLL_IsActive( DLList *list ) {

	/* if((list == NULL) || list->activeElement == NULL)	// pokud list neexistuje nebo neni aktivni, vracime 0, jinak vracime 1
		return 0;
	else	
		return 1;*/

	return (list->activeElement != NULL);	// jestlize seznam je aktivni, vracime true (nenulova hodnota), jinak vraci false, tedy 0
}

/* Konec c206.c */
