#ifndef STUDENT_H
#define STUDENT_H

#include "Profil.h"
#include <vector>
#include <string>

class Student : public Profil {
    std::string specializare;
    std::vector<std::string> competente;
    std::vector<std::string> interese;

public:
    Student(std::string n, std::string e, std::string s,
        std::vector<std::string> c,
        std::vector<std::string> i);

    void afisare() const override;
};

#endif
