#ifndef PROFIL_H
#define PROFIL_H

#include <string>

class Profil {
protected:
    std::string nume;
    std::string email;

public:
    Profil(std::string n, std::string e);
    virtual void afisare() const;
    virtual ~Profil();
};

#endif
