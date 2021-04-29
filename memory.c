
// --------------------------------------------------------------------------------------

// Autor:
    // Norman Steinhoff

// Jahr
    // 2021

// --------------------------------------------------------------------------------------

// Verwendete Abkürzungen:
    // Vor. == Voraussetzung
    // Eff. == Effekt
    // Erg. == Ergebnis
    // Anm. == Anmerkung

// --------------------------------------------------------------------------------------

// Standard_Header einbinden
#include <stdbool.h>
#include <stdio.h>

// Header einbinden
#include "memory.h"

char memory[MEM_SIZE];


// Einfach verkettete Liste
struct Block {
    bool occupied;
    struct Block (*next);
};

// Vor.:
// * { NULL != block }
// Eff.:
// 
// Erg.:
// 
// Anm.:
// 
size_t _block_size(struct Block (*block)) {

    // Ergebnis initialisieren
    size_t result = 0;

    // Prüfen, ob Nachfolger vorhanden
    if (NULL != block->next) { // Nachfolger existiert

        // Ergebnis anpassen
        result = (char*)(block->next) - (char*)(block) - sizeof(*block);
    }

    // Ergebnis liefern
    return result;
}

// Vor.:
// 
// Eff.:
// *    Initialisiert den zur Verfügung stehenden Speicherbereich und etwaige Verwaltungsdaten.
// Erg.:
// 
// Anm.:
// 
void memory_init(void) {

    // Start_ und Stop_Knoten bekanntmachen
    struct Block (*start) = (struct Block *) &memory[0];
    struct Block (*stop) = (struct Block *) &memory[MEM_SIZE - sizeof(*stop)];
    
    // Besetzung initialisieren
    start->occupied = false;
    stop->occupied = true;

    // Nachfolger setzen
    start->next = stop;
    stop->next = NULL;
}

// Vor.:
// 
// Eff.:
// 
// Erg.:
// *    Gibt einen Zeiger auf einen zusammenhängenden Speicherbereich der Größe byte_count zurück.
// Anm.:
// 
void * memory_allocate(size_t byte_count) {

    // Ergebnis initialisieren
    void * result = NULL;

    // Lauf_Variable initialisieren
    struct Block (*block_a) = (struct Block *)(&memory[0]);

    // passenden freien Block suchen, wenn möglich
    while (NULL != block_a) {

        // Prüfen, ob bereits gefunden
        if ((block_a->occupied) || (_block_size(block_a) + sizeof(struct Block) < byte_count)) { // nicht gefunden

            // weiter laufen
            block_a = block_a->next;
        }
        else {

            //
            break;
        }
    }

    // Prüfen, ob passender Block gefunden wurde
    if (NULL != block_a) { // Block existiert

        // neuen mittleren Block anlegen
        char (*addr) = (char *)(block_a) + sizeof(struct Block) + byte_count;
        struct Block (*block_b) = (struct Block *)(addr);

        // aktuellen Nachfolger von { block_a } bestimmen
        struct Block (*block_c) = block_a->next;

        // neu verketten
        block_a->next = block_b;
        block_b->next = block_c;

        // Besetzung anpassen
        block_a->occupied = true;
        block_b->occupied = false;
    }

    // Ergebnis setzen
    result = (void *)(block_a);

    // Ergebnis liefern
    return result;
}

// Vor.:
// 
// Eff.:
// *    Gibt einen von memory_allocate reservierten Speicherbereich wieder frei.
// Erg.:
// 
// Anm.:
// 
void memory_free(const void *const pointer) {
    
    //
    if (NULL != pointer) {

        //
        struct Block (*block) = (struct Block *)(pointer);

        //
        block->occupied = false;

        //
        while ((NULL != block->next) && (false == block->next->occupied)) {
            block->next = block->next->next;
        }
    }
}

// Vor.:
// 
// Eff.:
// *    Visualisiert den aktuellen Zustand des Speichers bzw. gibt Informationen über den Zustand aus.
// Erg.:
// 
// Anm.:
// 
void memory_print(void) {

    //
    printf("---------------------------------\n");

    //
    struct Block (*block) = (struct Block *) &memory[0];

    //
    int pos = 0;
        
    //
    while (NULL != block->next) {
        
        //
        if (block->occupied) {

            //
            printf("Block %d of size %lu (USED)\n", pos, _block_size(block));
        }
        else {

            //
            printf("Block %d of size %lu (FREE)\n", pos, _block_size(block));
        }

        //
        block = block->next;

        //
        ++pos;
    }

    //
    printf("---------------------------------\n");
}

// Vor.:
// 
// Eff.:
// 
// Erg.:
// *    Gibt einen Pointer auf das n-te Element in der Liste zurück, NULL, falls nicht existent.
// Anm.:
// 
void * memory_by_index(size_t index) {

    // Ergebnis initialisieren
    void * result = NULL;
    
    // Lauf_Variable initialisieren
    struct Block (*current) = (struct Block *) &memory[0];

    // Zum gewünschten Block laufen
    for (size_t a = 0; a < index; ++a) {
        
        // Existenz des Blocks überprüfen
        if (NULL != current) { // Block existiert

            // weiter laufen
            current = current->next;
        }
        else { // Block existiert nicht

            // Abbruch der Schleife
            break;
        }
    }

    // Ergebnis setzen
    result = (void *) current;

    // Ergebnis liefern
    return result;
}


