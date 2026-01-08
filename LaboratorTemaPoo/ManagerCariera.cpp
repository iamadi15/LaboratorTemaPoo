// ManagerCariera.cpp
#include "Entitate.h"
#include <sstream> 

// ==========================================================
// IMPLEMENTARE UTILITY (citesteLista)
// ==========================================================

vector<string> citesteLista(const string& prompt, std::istream& is) {
    vector<string> lista;
    string input;

    // Daca citim de la consola (std::cin), afisam prompt-ul
    if (&is == &std::cin) {
        cout << prompt << " (separat prin virgula): ";
        if (is.peek() == '\n') is.ignore(10000, '\n');
    }

    if (!getline(is, input)) return lista; // Citim linia

    stringstream ss(input);
    string element;

    while (getline(ss, element, ',')) {
        // Curatam spatiile albe (Trim)
        element.erase(0, element.find_first_not_of(" \n\r\t"));
        element.erase(element.find_last_not_of(" \n\r\t") + 1);

        if (!element.empty()) {
            lista.push_back(element);
        }
    }
    return lista;
}

// ==========================================================
// IMPLEMENTARE ProfilStudent
// ==========================================================

ProfilStudent::ProfilStudent() : nume("N/A") {}

void ProfilStudent::citesteDinStream(std::istream& is) {
    bool from_console = (&is == &std::cin);

    // 1. Nume complet
    if (from_console) cout << "Nume complet: ";
    if (!getline(is, nume)) return;

    // 2. Specializare
    if (from_console) cout << "Specializare: ";
    if (!getline(is, specializare)) return;

    // 3. Link CV Digital
    if (from_console) cout << "Link CV Digital: ";
    if (!getline(is, cv_digital)) return;

    // 4. Competente
    string prompt_comp = from_console ? "Competente" : "";
    competente = citesteLista(prompt_comp, is);

    // 5. Interese
    string prompt_intr = from_console ? "Interese" : "";
    interese = citesteLista(prompt_intr, is);

    if (from_console) {
        cout << "\nProfilul a fost actualizat cu succes!" << endl;
    }
}

void ProfilStudent::editeaza() {
    cout << "\n--- Editare Profil Student ---" << endl;
    citesteDinStream(std::cin);
}

void ProfilStudent::afiseazaDetalii() const {
    cout << "\n--- Profilul Studentului ---" << endl;
    if (nume == "N/A") {
        cout << "!!! Nu exista niciun profil inregistrat. Va rugam sa il creati." << endl;
        return;
    }
    cout << "Nume: " << nume << endl;
    cout << "Specializare: " << specializare << endl;
    cout << "CV Digital: " << cv_digital << endl;

    cout << "Competente: ";
    for (const auto& comp : competente) { cout << comp << "; "; }
    cout << endl;

    cout << "Interese: ";
    for (const auto& intr : interese) { cout << intr << "; "; }
    cout << endl;
}

// ==========================================================
// IMPLEMENTARE Oportunitate
// ==========================================================

Oportunitate::Oportunitate(string t, string d, string o, vector<string> c)
    : titlu(std::move(t)), domeniu(std::move(d)), oras(std::move(o)), competente_necesare(std::move(c)) {
}

void Oportunitate::editeaza() {
    cout << "!!! Oportunitatile nu pot fi editate direct prin meniu." << endl;
}

void Oportunitate::afiseazaDetalii() const {
    cout << "Titlu: " << titlu << endl;
    cout << "  Domeniu: " << domeniu << " | Oras: " << oras << endl;
    cout << "  Necesar: ";
    for (const auto& comp : competente_necesare) { cout << comp << ", "; }
    cout << endl;
}