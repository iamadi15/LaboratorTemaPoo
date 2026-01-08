// main.cpp
#include "Entitate.h"
#include <fstream>
#include <sstream>

// ==========================================================
// GESTIONARE CENTRALIZATĂ 
// ==========================================================

unique_ptr<ProfilStudent> profilStudent = make_unique<ProfilStudent>();
vector<unique_ptr<Oportunitate>> listaOportunitati;

// ==========================================================
// FUNCTII MENIU 
// ==========================================================
// Declaratiile functiilor care nu sunt membri de clasa:
void incarcaDateDinFisier();
void adaugaOportunitate();
void vizualizeazaToateOportunitatile();
void filtreazaOportunitati();
void ghidAngajare();
void inregistreazaStagiuFacultate();
void afiseazaMeniu(); // Rezolva eroarea 'afiseazaMeniu' identifier not found

// ==========================================================
// IMPLEMENTARE FUNCTII
// ==========================================================

void incarcaDateDinFisier() {
    // ATENTIE: Verificati ca numele "date_initiale.txt" este corect in folderul Debug
    std::ifstream fisier("date_initiale.txt");

    if (!fisier.is_open()) {
        cout << "!!! Eroare la deschiderea fisierului 'date_initiale.txt'. Fisierul trebuie sa fie in directorul de rulare (Debug)." << endl;
        cout << "!!! Va rugam introduceti detaliile profilului (Optiunea 1) manual." << endl;
        return;
    }

    cout << "\n==================================================" << endl;
    cout << "Incarcare date din 'date_initiale.txt'..." << endl;

    // 1. Citeste Profilul Studentului (primele 5 linii)
    profilStudent->citesteDinStream(fisier);

    // 2. Citeste Oportunitatile (citire linie cu linie pana la EOF)
    string linieOportunitate;
    while (getline(fisier, linieOportunitate) && !linieOportunitate.empty()) {
        stringstream ss(linieOportunitate);
        string titlu, domeniu, oras, competente_str;

        // Citim primele 3 campuri (Titlu, Domeniu, Oras) separate prin virgula
        if (getline(ss, titlu, ',') &&
            getline(ss, domeniu, ',') &&
            getline(ss, oras, ','))
        {
            // Restul liniei este lista de competente
            getline(ss, competente_str);

            // Parsam lista de competente
            stringstream cs(competente_str);
            vector<string> competente_necesare;
            string comp;
            while (getline(cs, comp, ',')) {
                comp.erase(0, comp.find_first_not_of(" \n\r\t"));
                comp.erase(comp.find_last_not_of(" \n\r\t") + 1);
                if (!comp.empty()) competente_necesare.push_back(comp);
            }

            listaOportunitati.push_back(make_unique<Oportunitate>(
                titlu, domeniu, oras, std::move(competente_necesare)));
        }
    }

    fisier.close();
    cout << "Date incarcate cu succes. Oportunitati gasite: " << listaOportunitati.size() << endl;
    cout << "==================================================" << endl;
}

void adaugaOportunitate() {
    string titlu, domeniu, oras;
    cout << "\n--- Adaugare Stagiu/Oportunitate ---" << endl;
    cout << "Titlu: ";
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, titlu);
    cout << "Domeniu (ex: IT, Finante, Marketing): ";
    getline(cin, domeniu);
    cout << "Oras: ";
    getline(cin, oras);

    vector<string> comp = citesteLista("Competente necesare", std::cin);

    listaOportunitati.push_back(make_unique<Oportunitate>(titlu, domeniu, oras, comp));
    cout << "\nStagiul '" << titlu << "' a fost adaugat." << endl;
}

void vizualizeazaToateOportunitatile() {
    if (listaOportunitati.empty()) {
        cout << "Nu exista stagii disponibile." << endl;
        return;
    }
    cout << "\n==================================================" << endl;
    for (size_t i = 0; i < listaOportunitati.size(); ++i) {
        cout << "Nr. " << i + 1 << ": ";
        listaOportunitati[i]->afiseazaDetalii();
        cout << "--------------------------------------------------" << endl;
    }
    cout << "==================================================" << endl;
}

void filtreazaOportunitati() {
    string filtruDomeniu, filtruOras, filtruCompetenta;

    cout << "\n--- Filtrare Oportunitati ---" << endl;
    cout << "Filtru Domeniu (lasati gol pentru orice): ";
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, filtruDomeniu);
    cout << "Filtru Oras (lasati gol pentru orice): ";
    getline(cin, filtruOras);
    cout << "Filtru Competenta (lasati gol pentru orice): ";
    getline(cin, filtruCompetenta);

    int count = 0;

    transform(filtruDomeniu.begin(), filtruDomeniu.end(), filtruDomeniu.begin(), ::tolower);
    transform(filtruOras.begin(), filtruOras.end(), filtruOras.begin(), ::tolower);
    transform(filtruCompetenta.begin(), filtruCompetenta.end(), filtruCompetenta.begin(), ::tolower);

    cout << "\n--- Rezultate Filtrare ---" << endl;
    cout << "==================================================" << endl;

    for (const auto& op : listaOportunitati) {
        bool matchDomeniu = filtruDomeniu.empty();
        if (!matchDomeniu) {
            string domeniuLower = op->getDomeniu();
            transform(domeniuLower.begin(), domeniuLower.end(), domeniuLower.begin(), ::tolower);
            if (domeniuLower.find(filtruDomeniu) != string::npos) matchDomeniu = true;
        }

        bool matchOras = filtruOras.empty();
        if (!matchOras) {
            string orasLower = op->getOras();
            transform(orasLower.begin(), orasLower.end(), orasLower.begin(), ::tolower);
            if (orasLower.find(filtruOras) != string::npos) matchOras = true;
        }

        bool matchCompetenta = filtruCompetenta.empty();
        if (!matchCompetenta) {
            for (const auto& comp : op->getCompetenteNecesare()) {
                string compLower = comp;
                transform(compLower.begin(), compLower.end(), compLower.begin(), ::tolower);
                if (compLower.find(filtruCompetenta) != string::npos) {
                    matchCompetenta = true;
                    break;
                }
            }
        }

        if (matchDomeniu && matchOras && matchCompetenta) {
            cout << "Nr. " << ++count << ": ";
            op->afiseazaDetalii();
            cout << "--------------------------------------------------" << endl;
        }
    }

    if (count == 0) cout << "Nu s-au gasit oportunitati conform filtrelor." << endl;
    cout << "==================================================" << endl;
}

void ghidAngajare() {
    cout << "\n--- Ghid Pregatire Angajare ---" << endl;
    cout << "1. Modele de CV: Utilizati sabloane moderne." << endl;
    cout << "2. Interviu: Cercetati compania inainte." << endl;
    cout << "3. Intrebari de Practica (Exemple): 'De ce doriti sa lucrati la compania noastra?', 'Explicati conceptul de mostenire in OOP.' etc." << endl;
}

void inregistreazaStagiuFacultate() {
    if (profilStudent->getNume() == "N/A") {
        cout << "\n!!! Va rugam creati profilul studentului mai intai (Optiunea 1)." << endl;
        return;
    }

    cout << "\n--- Inregistrare Stagiu in Dosarul de Practica ---" << endl;
    cout << "Student: " << profilStudent->getNume() << endl;
    cout << "Introduceti Numele companiei: ";
    string companie;
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, companie);
    cout << "Introduceti Data de inceput (DD/MM/AAAA): ";
    string dataStart;
    getline(cin, dataStart);

    cout << "\nStagiul cu compania '" << companie << "', incepand cu " << dataStart << " a fost inregistrat in sistemul facultatii." << endl;
}


void afiseazaMeniu() {
    cout << "\n=======================================================" << endl;
    cout << "       SISTEM DE MANAGEMENT AL CARIEREI STUDENTILOR (OOP)" << endl;
    cout << "=======================================================" << endl;
    cout << "1. Creare/Vizualizare Profil Student (Sectiunea 1)" << endl;
    cout << "2. Adauga Oportunitate de Stagiu" << endl;
    cout << "3. Vizualizare Toate Oportunitatile" << endl;
    cout << "4. Filtrare Oportunitati (Sectiunea 2)" << endl;
    cout << "5. Ghid Pregatire Angajare (Sectiunea 3)" << endl;
    cout << "6. Inregistrare Stagiu (Pentru Facultate) (Sectiunea 4)" << endl;
    cout << "0. Iesire" << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << "Alegeti o optiune: ";
}

// ==========================================================
// FUNCTIA PRINCIPALA (MAIN)
// ==========================================================

int main() {
    incarcaDateDinFisier();

    int optiune;

    do {
        afiseazaMeniu();
        if (!(cin >> optiune)) {
            cin.clear();
            cin.ignore(10000, '\n');
            optiune = -1;
        }

        switch (optiune) {
        case 1:
            profilStudent->editeaza();
            profilStudent->afiseazaDetalii();
            break;
        case 2:
            adaugaOportunitate();
            break;
        case 3:
            vizualizeazaToateOportunitatile();
            break;
        case 4:
            filtreazaOportunitati();
            break;
        case 5:
            ghidAngajare();
            break;
        case 6:
            inregistreazaStagiuFacultate();
            break;
        case 0:
            cout << "\nIesire din program. La revedere!" << endl;
            break;
        default:
            cout << "\nOptiune invalida. Va rugam alegeti din meniu." << endl;
            break;
        }

    } while (optiune != 0);

    return 0;
}