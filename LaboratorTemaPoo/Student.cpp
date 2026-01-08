#include <iostream>
#include "Student.h"

Student::Student(std::string n, std::string e, std::string s,
    std::vector<std::string> c,
    std::vector<std::string> i)
    : Profil(n, e), specializare(s), competente(c), interese(i) {
}

void Student::afisare() const {
    Profil::afisare();
    std::cout << "Specializare: " << specializare << std::endl;

    std::cout << "Competente: ";
    for (auto c : competente) std::cout << c << " ";
    std::cout << std::endl;

    std::cout << "Interese: ";
    for (auto i : interese) std::cout << i << " ";
    std::cout << std::endl;
}