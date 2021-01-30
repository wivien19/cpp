#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

class Telepes {
    string nev;
    string szul_bolygo;
    mutable string bolygo;
    unsigned ero;
public:
    bool vegan;
public:
    const string &get_nev() const {
        return nev;
    }

    void set_nev(const string &nev) {
        Telepes::nev = nev;
    }

    const string &get_szul_bolygo() const {
        return szul_bolygo;
    }

    void set_szul_bolygo(const string &szulBolygo) {
        szul_bolygo = szulBolygo;
    }

    const string &get_bolygo() const {
        return bolygo;
    }

    void set_bolygo(const string &bolygo) {
        Telepes::bolygo = bolygo;
    }

    unsigned int get_ero() const {
        return ero;
    }

    void set_ero(unsigned int ero) {
        Telepes::ero = ero;
    }

    bool is_vegan() const {
        return vegan;
    }

    void set_vegan(bool vegan) {
        Telepes::vegan = vegan;
    }

    Telepes() {
        nev = "";
        szul_bolygo = "";
        ero = 1;
        bolygo = "";
    }
    /*TODO*/

   Telepes(const string &nev, const string &szulBolygo, const string &bolygo, bool vegan, int ero) : nev(nev),
                                                                                                   szul_bolygo(
                                                                                                           szulBolygo),
                                                                                                   bolygo(bolygo),
                                                                                                   vegan(vegan), ero(ero) {
        this->nev = nev;
        this->szul_bolygo = szulBolygo;
        this->bolygo = bolygo;
        this->ero = ero;
    }


   bool operator==(const Telepes& telepes) const {
      bool ertek = true;

       if (nev != telepes.nev || ero != telepes.ero || vegan != telepes.vegan) {
           ertek = false;
       }
       for (int i = 0; i < (bolygo.length()); ++i) {
                if (tolower(bolygo[i]) != tolower(telepes.bolygo[i])){
                    ertek = false;
                    break;
                }
            }
        for (int i = 0; i < (szul_bolygo.length()); ++i) {
        if (tolower(szul_bolygo[i]) != tolower(telepes.szul_bolygo[i])){
            ertek = false;
            break;
        }
    }
       return ertek;
    }


};
class Kolonia;
bool veganE(const Kolonia& k);
class Kolonia{
    string nev;
    string bolygo;
    unsigned letszam;
    Telepes lakok[25];
public:
    const string &get_nev() const {
        return nev;
    }

    const string &get_bolygo() const {
        return bolygo;
    }

    unsigned int get_letszam() const {
        return letszam;
    }

    const Telepes *get_lakok() const {
        return lakok;
    }

    void set_nev(const string &nev) {
        Kolonia::nev = nev;
    }

    void set_bolygo(const string &bolygo) {
        Kolonia::bolygo = bolygo;
    }

    Kolonia(const string &nev, const string &bolygo) : nev(nev), bolygo(bolygo), letszam(0){}

    /*TODO*/
   Kolonia(const string &nev, const string &bolygo, unsigned letszam) : nev(nev), bolygo(bolygo), letszam(letszam){}

    Kolonia(): nev(""), bolygo(""), letszam(0) {}

    Kolonia& operator+=(Telepes telepes) {

        bool veg = veganE(*this);
        if (telepes.is_vegan() || !veg) {

            if (letszam < 25){
                letszam++;
                telepes.set_bolygo(get_bolygo());
                for (int i = 0; i < 25; ++i) {
                    if (lakok[i].get_nev().empty()) {
                        lakok[i] = telepes;
                        break;
                    }
                }
            } else{
                cout <<"A kolonia megtelt" << endl;
            }
        }
        else {
              cout << "A kolonia vegan" << endl;
        }
        return *this;

    }
    Kolonia& operator+=(Kolonia kolonia) {
        bool egyenloek = true;
        char *a =   const_cast<char*>(bolygo.c_str());
        char *b =   const_cast<char*>(kolonia.bolygo.c_str());
        for (int i = 0; i < (bolygo.length()); ++i) {
            if (tolower(a[i]) != tolower(b[i])){
                egyenloek = false;
                break;
            }
        }
        if (egyenloek && (letszam+kolonia.letszam <= 25)){
            int szam = 0;
            letszam += kolonia.letszam;
           // cout << "ennyi a szam: " << letszam << endl;
            for (int i = 0; i < 25; ++i) {
                if (lakok[i].get_nev().empty()){
                    lakok[i] = kolonia.lakok[szam];
                    szam++;
                }
            }

        } else if (!egyenloek){
            cerr << "Hiba az egyesitesben: bolygo" << endl;
        } else if (letszam+kolonia.letszam > 25){
            cerr << "Hiba az egyesitesben: meret" << endl;
        }
        return *this;
    }
    Kolonia operator-(const Telepes& telepes) const {
        Kolonia k_uj = {};
        k_uj.letszam = this->letszam;
        int szam = 0;
        int counter = 0;
        for (int i = 0; i < this->get_letszam(); ++i) {
            if(this->get_lakok()[i].get_nev() == telepes.get_nev()){
                if (counter == 0){
                    k_uj.letszam--;
                    counter++;
                } else{
                    k_uj.lakok[szam] = this->get_lakok()[i];
                    szam++;
                   // cout << "valami" << endl;
                }

            } else{
                k_uj.lakok[szam] = this->get_lakok()[i];
               // cout << "e" << endl;
                szam++;

            }
           // cout << telepes.get_nev() << this->get_lakok()[0].get_nev() << "   " << endl;

        }
        return k_uj;
    }
};



bool veganE(const Kolonia& k){
    bool sokVegan = false;
    int counter = 0;
    for (int i = 0; i < k.get_letszam(); ++i) {
        if (k.get_lakok()[i].is_vegan()){
            counter++;
        }
        if (counter > k.get_letszam()/2){
            sokVegan = true;
            break;
        }
    }
    return sokVegan;

}



int main(){
    Telepes t = {"Bela", "BOLYGO", "HOLLANDI", true, 1};
    Telepes t2 = {"Jancsii", "BOLYGO", "HOLLANDI", true, 1};
    Telepes t3 = {"Bela", "BOLYGO", "HOLLANDI", true, 1};

    Kolonia k = {"Jancsii", "HOLLANDI"};
    Kolonia k2;
    k+=t;
    cout << k.get_lakok()[0].get_nev()  << endl;
    //k+=t2;
    cout << (t == k.get_lakok()[0]) << endl;
    k2 = k-t;

    cout << k2.get_lakok()[0].get_nev() << " " <<  k2.get_letszam() << "  "  << endl;

    return 0;
}