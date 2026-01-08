// Entitate.h
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <istream> 

using namespace std;

// Functie Helper: Declaratie
vector<string> citesteLista(const string& prompt, std::istream& is);

// ==========================================================
// BAZA POLIMORFICĂ
// ==========================================================

class Entitate {
public:
    virtual ~Entitate() = default;
    virtual void afiseazaDetalii() const = 0;
    virtual void editeaza() = 0;
};

// ==========================================================
// CLASE DERIVATE
// ==========================================================

// 1. Profil Student 
class ProfilStudent : public Entitate {
private:
    string nume;
    string specializare;
    string cv_digital;
    vector<string> competente;
    vector<string> interese;

public:
    ProfilStudent(); // Constructor
    void editeaza() override;
    void afiseazaDetalii() const override;

    // Functie helper: ACUM ESTE PUBLICĂ pentru a putea fi apelată din main.cpp
    void citesteDinStream(std::istream& is);

    // Getters
    const string& getNume() const { return nume; }
    const string& getSpecializare() const { return specializare; }
    const vector<string>& getCompetente() const { return competente; }
};

// 2. Oportunitate de Practica 
class Oportunitate : public Entitate {
private:
    string titlu;
    string domeniu;
    string oras;
    vector<string> competente_necesare;

public:
    Oportunitate(string t, string d, string o, vector<string> c);
    void editeaza() override;
    void afiseazaDetalii() const override;

    // Getters
    const string& getTitlu() const { return titlu; }
    const string& getDomeniu() const { return domeniu; }
    const string& getOras() const { return oras; }
    const vector<string>& getCompetenteNecesare() const { return competente_necesare; }
};