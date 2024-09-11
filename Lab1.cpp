#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

// Functia de modificare a ISBN-ului in format ISBN(13)
string formatISBN13(const string& isbn) {
    if (isbn.length() != 13) {
        return "Invalid ISBN-13";
    }
    return isbn.substr(0, 3) + "-" + 
           isbn.substr(3, 1) + "-" +  
           isbn.substr(4, 4) + "-" + 
           isbn.substr(8, 4) + "-" +  
           isbn.substr(12, 1);        
}

// Clasa Carte
class Carte {
private:
    string titlu;
    string autor;
    string rawISBN; 

public:
    // Constructia unei carti
    Carte(string t, string a, string isbn) : titlu(t), autor(a), rawISBN(isbn) {
        if (isbn.length() == 13) {
            // Stocarea ISBN-ului formatat
            ISBN = formatISBN13(isbn);
        } else {
            ISBN = "Invalid ISBN";
        }
    }

    // Returnarea ISBN-ului initial
    string getRawISBN() const {
        return rawISBN;
    }

    // Returnarea ISBN-ului formatat
    string getISBN() const {
        return ISBN;
    }
    string getTitlu() const {
        return titlu;
    }

    // Afisarea cartii
    void afisareCarte() const {
        cout << "Titlu: " << titlu << ", Autor: " << autor << ", ISBN: " << ISBN << endl;
    }

private:
    string ISBN; // Formatted ISBN
};

// Clasa Biblioteca
class Biblioteca {
private:
    vector<Carte> carti;

public:
    // Metoda de adaugare a unei carti
    void adaugaCarte(const Carte& carte) {
        auto it = find_if(carti.begin(), carti.end(), [&](const Carte& c) {
            return c.getRawISBN() == carte.getRawISBN();
        });

        if (it != carti.end()) {
            cout << "Cartea cu ISBN-ul " << carte.getISBN() << " exista deja in biblioteca.\n";
        } else {
            carti.push_back(carte);
            cout << "Cartea \"" << carte.getTitlu() << "\" a fost adaugata cu succes.\n";
        }
    }

    // Metoda de stergere a cartii dupa ISBN-ul indicat
    void eliminaCarte(const string& isbn) {
        // Formatarea ISBN-ului indicat sa semene cu acel stocat
        string formattedISBN = formatISBN13(isbn);

        auto it = find_if(carti.begin(), carti.end(), [&](const Carte& c) {
            return c.getISBN() == formattedISBN;
        });

        if (it != carti.end()) {
            cout << "Cartea \"" << it->getTitlu() << "\" a fost eliminata din biblioteca.\n";
            carti.erase(it);
        } else {
            cout << "Cartea cu ISBN-ul " << isbn << " nu a fost gasita in biblioteca.\n";
        }
    }

    // Metoda de afisare a listei
    void afiseazaCarti() const {
        if (carti.empty()) {
            cout << "Biblioteca este goala.\n";
            return;
        }

        cout << "Lista de carti din biblioteca:\n";
        for (const auto& carte : carti) {
            cout << "------------------------\n";
            carte.afisareCarte();
        }
        cout << "------------------------\n";
    }
};

int main() {
    Biblioteca biblioteca;
    int optiune;
    string titlu, autor, isbn;

    do {
        cout << "\n----- Meniu Biblioteca -----\n";
        cout << "1. Adauga o carte\n";
        cout << "2. Elimina o carte\n";
        cout << "3. Afiseaza toate cartile\n";
        cout << "4. Iesi\n";
        cout << "Alege o optiune: ";
        cin >> optiune;
        cin.ignore(); 

        switch (optiune) {
            case 1:
                cout << "Introdu titlul cartii: ";
                getline(cin, titlu);
                cout << "Introdu autorul cartii: ";
                getline(cin, autor);
                
                do {
                    cout << "Introdu ISBN-ul cartii (13 caractere): ";
                    getline(cin, isbn);

                    //Sterge toate non numerele
                    isbn.erase(remove_if(isbn.begin(), isbn.end(), [](char c) { return !isdigit(c); }), isbn.end());

                    if (isbn.length() != 13) {
                        cout << "ISBN invalid! Te rog sa introduci un ISBN de 13 caractere.\n";
                    }

                } while (isbn.length() != 13);

                {
                    Carte nouaCarte(titlu, autor, isbn);
                    biblioteca.adaugaCarte(nouaCarte);
                }
                break;

            case 2:
                cout << "Introdu ISBN-ul cartii de eliminat: ";
                getline(cin, isbn);
                //Sterge toate non numerele 
                isbn.erase(remove_if(isbn.begin(), isbn.end(), [](char c) { return !isdigit(c); }), isbn.end());
                biblioteca.eliminaCarte(isbn);
                break;

            case 3:
                biblioteca.afiseazaCarti();
                break;

            case 4:
                cout << "La revedere!\n";
                break;

            default:
                cout << "Optiune invalida. Te rog sa incerci din nou.\n";
        }
    } while (optiune != 4);

    return 0;
}
