/** Jest to przykład bardzo prostej listy jednokierunkowej w języku
 * Ansi C. Aby nie komplikować przykładu jako typ przechowywany
 * zastosowano proste wartości typu INT w prawdziwych zastosowaniach należy
 * przygotować odpowiednio wersje generyczne umożliwiające przechowywanie
 * różnych typów danych co w języku C możliwe jest jedynie za pomocą jedynego
 * typu generycznego void*
 */


#include <stdio.h>
#include <stdlib.h>


/** Podstawowa struktura przechowująca pojedynczy węzeł listy
 * 	w zmiennej int val przechowywana jest właściwa dana
 * 	natomiast wskaźnik next będący tego samego typu jak struktura
 * 	pokazuje na następny element na liście.
 * 	Dodatkowa instrukcja typedef node_t umożlwia w języku ANSI C utworzenie typu pochodnego
 * 	struct node, tak aby za każdym razem nie trzeba było pisać struct node 
 * 	Dodatkowe informacje na temat samych struktur możemy znaleźć tutaj:
 * https://pl.wikibooks.org/wiki/C/Typy_z%C5%82o%C5%BCone
 *
 */
typedef struct node {
    int val;
    struct node * next;
} node_t;


/* create_node tworzy nowy element listy na stercie i zwraca wskaźnik do tego elementu
 * W przypadku gdy funkcja malloc nie powiedzie sie, zwraca NULL co oznacza to ze nie możemy zaalokować pamięci
 * i zwracana jest wartość NULL.
 * Utworzenie nowego węzła polega na zaalokowaniu pamięci dla tego węzła a następnie w
 * zaalokowanej pamięci przechowującej strukturę do pola val wpisywana jest wartość
 * do przechowania, natomiast pole -> next ustawiane jest na NULL ponieważ to jest
 * ostatni element na liście.
 * Więcej informacji na temat alokowania pamięci na stercie za pomocą funkcji malloc
 * możemy znaleźć tutaj:
 * https://pl.wikibooks.org/wiki/C/malloc
 */
node_t* create_node(int val)
{
	node_t * head = NULL;
	head = malloc(sizeof(node_t));
	if (head == NULL) {
		return NULL;
	}

	head->val = val;
	head->next = NULL;
}

/** Funkcja print_list przechodzi przez wszystkie elementy listy
 * oraz wypisuje zawartość wszystkich elementów. Jest to zatem operacja która
 * w skrypcie została nazwana przejsciem przez liste.
 * Funkcja rozpoczyna działanie od przypisania wskażnikowi na bieżący element
 * current głowy listy a następnie przejście za pomocą instrukcji while przez wszystkie elementy listy.
 * Instrukcja warunkowa while sprawdza czy wartość logiczna w wyrażeniu jest prawdziwa, jeśli nie jest prawdziwa
 * to kończy działanie. Natomiast jeśli jest prawdziwa to wykonuje instrukcje znajdującą się za while, a następnie
 * przechodzi kolejny raz do sprawdzenia warunku i cykl zaczyna się od początku, aż do momentu
 * gdy wyrażenie będzie fałszywe.  W przypadku przechodzeniu przez wszystkie elementy listy instrukcję wykonujemy do czasu
 * gdy zmienna current przyjmie wartość NULL co oznacza że dotarliśmy do ostatniego elementu listy.
 * Więcej na temat instrukcji sterujących możemy znaleźć tutaj.
 * https://pl.wikibooks.org/wiki/C/Instrukcje_steruj%C4%85ce#while
 *
 */
void print_list(node_t * head)
{
    node_t * current = head;

    while (current != NULL) {
        printf("%d\n", current->val);
        current = current->next;
    }
}

/** Przy liście jednokierunkowej wstawienie elementu na ostatnią pozycję wymaga przejścia przez wszystkie
 * elementy tej listy aż do końca a następnie doczepienie na końcu nowego elementu.
 * Przejście przez wszystkie elementy realizowane jest przez pętlę while, gdzie po dotarciu do ostatniego elementu,
 * do zmiennej current->next wskazującej na ostatni element, wpisywany jest adres nowego obszaru pamięci dla nowo utworzonego
 * węzła, co powoduje zamazanie poprzednio znajdującej się wartości NULL.
 * Następnie do nowego węzła przypisywana jest wartość val a na zakończenie wskaźnik wskaźnik next nowego węzła ustawiany jest na NULL
 * co jest znacznikiem ostatniego elementu na liście. */

void insert_end(node_t * head, int val)
{
    node_t * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    /* now we can add a new variable */
    current->next = malloc(sizeof(node_t));
    current->next->val = val;
    current->next->next = NULL;
}


/** Funkcja dopisuje nowy element na początku listy,
 * nie musimy przechodzić przez wszystkie elementy.
 * Funkcja przyjmuje wskaźnik do wskaźnika na listę (co umożliwia zwrócenie wartości z funkcji)
 * Napierw za pomocą funkcji malloc alokowany jest nowwy węzeł, następnie do tego węzła wpisywana jest wartość
 * a do pola next wpisywany jest wskaźnik na węzęł stanowiący poprzednio pierwszy element.
 * Następnie wskaźnik do początku listy zmieniany jest na nowo zaalokowany węzeł. Tym sposobem nowo utworzony węzeł
 * staje się pierwszy natomiast poprzednia głowa listy doczepiana jest za pierwszym elementem.
 */
void insert_begin(node_t ** head, int val)
{
    node_t * new_node;
    new_node = malloc(sizeof(node_t));
    new_node->val = val;
    new_node->next = *head;
    *head = new_node;
}


/** Usunięcie pierwszego elementu na liscie jest badzo podobne, jednak wymaga sprawdzenia kilku
 * warunkow. Na początek sprawdzamy czy wskaźnik na głowe listy nie jest nullem co oznacza że znajujemy się
 *  w ostatnim węźle i nie ma nic do usunicia.
 *  Następnie , wzkaźnikowi na następny węzęł (next_node) przypisujemy wartośc drugiego węzła od głowy.
 *  ,a pamięc przechowującą aktualną głowę usuwamy. Następnie do wkaźnika na początek listy *head przypisujemy
 *  wartość zmiennej new_node. W ten sposób drugi element staje się nową głową listy.
 */
int remove_first(node_t ** head)
{
    int retval = -1;
    node_t * next_node = NULL;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;

    return retval;
}


/** W przypadku usunięcia ostatniego elementu listy , sytuacja jest podobna do poprzedniego przypadku jednak
 * mamy dodatkowe warunki
 * jeśli jest to jedyny element na liście to usuwamy go, jeśli elementów jest więcej to przechodzimy
 * do końca listy, a następnie usuwamy ostati element.
 */
int remove_last(node_t * head) {
    int retval = 0;
    /* Jeśli jest to jedyny element na liście to usuwamy go */
    if (head->next == NULL) {
        retval = head->val;
        free(head);
        return retval;
    }

    /* Jeśli jest więcej elementów przechodzimy przez wszystkie węzły aż do końca */
    node_t * current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    /* Aktualnie jesteśmy na końcu listy więc możemy usunąć węzeł końcowy a wskaźnikowi 
	 * na następny przypisać wartość NULL */
    retval = current->next->val;
    free(current->next);
    current->next = NULL;
    return retval;

}

/** Zadanie do wykonania */
remove_by_index(int num) {

}


void remove_by_val(node_t * head, int req) {
    node_t *current = head;

    if (current != NULL && current->val == req) {
        head = current->next;
        free(current);
        return;
    }

    while (current != NULL && current->val != req) {
        head = current;
        current = current->next;
    }

    if (current == NULL) return;

    head->next = current->next;
    free(current);
}



//remove_by_index(node_t * head, int index)


/** A teraz proste przykłady użycia tej prostej listy jednokierunkowej */

int main() {
	//! Wskaźnik do głowy listy
	node_t *list;
	//! Wstaw pierwszy element na listę i utwórz ją
	list = create_node(1);
	//! Dodaj element na koniec listy
	insert_end( list, 2 );
	//! Dodaj element na koniec listy
	insert_end( list, 3 );
	//! Dodaj element na koniec listy
	insert_end( list, 4 );
	//! Dodaj element na koniec listy
	insert_end( list, 5 );
	//! Dodaj element na koniec listy
	insert_end( list, 6 );
	// Wypisz wszystkie elemnty na liście tera zlista zawiera 6 elementów
	print_list( list );
	printf("------------------\n");
	remove_by_val( list, 4);
	// Usuń pierwszy i ostatni element
	remove_first( &list );
	remove_last( list );
	// Wypisz wszystkie elemnty na liście teraz lista zawiera wartości od 2 do 5
	// usunieto pierwszy element z początku i końca listy
	print_list( list );
	getchar();
}

