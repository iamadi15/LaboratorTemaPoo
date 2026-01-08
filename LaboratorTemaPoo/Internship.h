#ifndef INTERNSHIP_H
#define INTERNSHIP_H

#include "Oportunitate.h"

class Internship : public Oportunitate {
    std::string domeniu;
    std::string competentaNecesara;

public:
    Internship(std::string t, std::string o,
        std::string d, std::string c);

    void afisare() const override;
};

#endif
