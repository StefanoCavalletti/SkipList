#include "skip_list.h"
#include <iostream>
#include <cassert> 

void testCorrettezza() {
    std::cout << "--- Inizio Test di Correttezza SkipList ---" << std::endl;

    SkipList list;

    // 1. Test su lista vuota
    std::cout << "Test 1: Ricerca su lista vuota..." << std::endl;
    assert(list.search(10) == nullptr);
    assert(list.getSize() == 0);
    assert(list.remove(10) == false); // Non può rimuovere
    std::cout << "Test 1: Passato." << std::endl;

    // 2. Test di inserimento singolo e ricerca (Hit)
    std::cout << "Test 2: Inserimento singolo e ricerca..." << std::endl;
    assert(list.insert(10) == true);
    assert(list.getSize() == 1);
    assert(list.search(10) != nullptr);
    assert(list.search(10)->key == 10);
    std::cout << "Test 2: Passato." << std::endl;

    // 3. Test di inserimento duplicato
    std::cout << "Test 3: Inserimento duplicato..." << std::endl;
    assert(list.insert(10) == false); // Deve restituire false
    assert(list.getSize() == 1);       // La dimensione non deve cambiare
    std::cout << "Test 3: Passato." << std::endl;

    // 4. Test di ricerca (Miss)
    std::cout << "Test 4: Ricerca Miss..." << std::endl;
    assert(list.search(5) == nullptr);  // Chiave minore
    assert(list.search(15) == nullptr); // Chiave maggiore
    std::cout << "Test 4: Passato." << std::endl;

    // 5. Test di inserimenti multipli
    std::cout << "Test 5: Inserimenti multipli..." << std::endl;
    list.insert(5);
    list.insert(20);
    list.insert(15);
    list.insert(3);
    assert(list.getSize() == 5); // 10, 5, 20, 15, 3
    assert(list.search(3) != nullptr);
    assert(list.search(5) != nullptr);
    assert(list.search(10) != nullptr);
    assert(list.search(15) != nullptr);
    assert(list.search(20) != nullptr);
    std::cout << "Test 5: Passato." << std::endl;
    //list.print();

    // 6. Test di rimozione (Hit)
    std::cout << "Test 6: Rimozione (Hit)..." << std::endl;
    assert(list.remove(10) == true);
    assert(list.getSize() == 4);
    assert(list.search(10) == nullptr); // Non deve più trovarlo
    assert(list.search(5) != nullptr); // Gli altri ci sono ancora
    assert(list.search(20) != nullptr);
    std::cout << "Test 6: Passato." << std::endl;

    // 7. Test di rimozione (Miss)
    std::cout << "Test 7: Rimozione (Miss)..." << std::endl;
    assert(list.remove(99) == false);  // Elemento inesistente
    assert(list.remove(10) == false);  // Elemento già rimosso
    assert(list.getSize() == 4);
    std::cout << "Test 7: Passato." << std::endl;

    // 8. Test di rimozione estremi (head e tail logici)
    std::cout << "Test 8: Rimozione estremi..." << std::endl;
    assert(list.remove(3) == true);  // Rimuove il primo
    assert(list.remove(20) == true); // Rimuove l'ultimo
    assert(list.getSize() == 2);
    assert(list.search(3) == nullptr);
    assert(list.search(20) == nullptr);
    assert(list.search(5) != nullptr);
    assert(list.search(15) != nullptr);
    std::cout << "Test 8: Passato." << std::endl;
    //list.print();

    // 9. Test finale: svuotamento lista
    std::cout << "Test 9: Svuotamento lista..." << std::endl;
    list.remove(5);
    list.remove(15);
    assert(list.getSize() == 0);
    assert(list.first() == nullptr); // Il puntatore al livello 0 di head è null
    std::cout << "Test 9: Passato." << std::endl;

    // 10. Test di carico (stabilità)
    std::cout << "Test 10: Test di carico (10.000 inserimenti)..." << std::endl;
    for (int i = 0; i < 10000; ++i) {
        assert(list.insert(i) == true);
    }
    assert(list.getSize() == 10000);
    assert(list.search(5000) != nullptr);
    assert(list.search(9999) != nullptr);
    assert(list.search(10000) == nullptr);
    std::cout << "Test 10: Passato." << std::endl;

    std::cout << "\n--- Tutti i test di correttezza superati! ---" << std::endl;
}

int main() {
    testCorrettezza();
    return 0;
}
