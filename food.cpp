#include <iostream>
#include <string>

using namespace std;

struct Etel{
public:
    string nev;
    int hutes;

    Etel(const string &nev, int hutes) : nev(nev), hutes(hutes) {}
    Etel() : nev(""), hutes(0) {}
    string print() const{
        return  "nev:" + nev + ",hofok:" + to_string(hutes);
    }
};
class Hiba {
public:
    virtual string hiba() const{
        return "Hiba tortent";
    }
};
class Megromlik : public Hiba{
private:
    Etel etel;
public:
    Megromlik(const Etel &etel) : etel(etel) {}

public:
    virtual string hiba() const override {
        return"A " +etel.nev + " tarolasahoz legalabb " + to_string(etel.hutes) + " fok kell" ;
    }

};
class Megtelt : public Hiba {
    string mit;
public:
    Megtelt(const string &mit) : mit(mit) {}

public:
    virtual string hiba() const override {
        return "Nem sikerult letarolni a " + mit +"-t";
    }
};
class Hutoegyseg {
    int hofok;
    Etel tartalom[10];
    unsigned aktualis;
public:
    int get_hofok() const {
        return hofok;
    }

    const Etel *get_tartalom() const {
        return tartalom;
    }

    unsigned int get_aktualis() const {
        return aktualis;
    }

    Hutoegyseg(const string &hofok2) :  aktualis(0) {
        try {
            hofok = stoi(hofok2);
        }
        catch (invalid_argument& e) {
            hofok = -1;
        }
    }

    Hutoegyseg& operator+=(const Etel &etel){
        if (hofok > etel.hutes){
            throw Megromlik(etel);
        }
        if (aktualis >= 10){
            throw Megtelt(etel.nev);
        }
        tartalom[aktualis++] = etel;
        return *this;
    }
    void print() const{
        if (aktualis == 0) throw Hiba();
        for (unsigned i = 0; i < aktualis; ++i) {
           cout<< tartalom[i].print() << endl;
        }

    }
};
bool feltolt(Hutoegyseg& h, Etel etelek[], unsigned etelszam){
    try {
        for (unsigned i = 0; i < etelszam; ++i) {
            h += etelek[i];
        }
        return true;
    } catch (...) {
        return false;
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    Etel etel = Etel("kajaa", 3);
    cout << etel.print() << endl;
    Hutoegyseg hutoegyseg = Hutoegyseg("2");
    hutoegyseg += etel;
    hutoegyseg.print();

    return 0;
}
