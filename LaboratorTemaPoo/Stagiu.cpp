#include <iostream>
#include "Stagiu.h"

void Stagiu::inregistrare() {
    std::cout << "Companie: ";
    std::cin >> companie;
    std::cout << "Durata (luni): ";
    std::cin >> durata;
    std::cout << "Stagiu inregistrat cu succes!\n";
}