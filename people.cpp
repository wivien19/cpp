#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

class Telepes {
 string nev;
 string szul_bolygo;
 string bolygo;
 unsigned ero;
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

    Telepes(const string &nev, const string &szulBolygo, const string &bolygo, unsigned int ero) : nev(nev),
                                                                                                   szul_bolygo(
                                                                                                           szulBolygo),
                                                                                                   bolygo(bolygo),
                                                                                                   ero(ero) {
        this->nev = nev;
        this->szul_bolygo = szulBolygo;
        this->bolygo = bolygo;
        this->ero = ero;
    }

    Telepes() {
        nev = "";
        szul_bolygo = "";
        ero = 1;
        bolygo = "";
    }

    Telepes(const string &nev, const string &bolygo, unsigned int ero) : nev(nev), bolygo(bolygo), ero(1) {
        this->nev = nev;
        this->bolygo = bolygo;
        szul_bolygo = bolygo;
        this->ero = ero;
    }
    Telepes(const string &nev, const string &bolygo) : Telepes(nev, bolygo, 1) {
        this->nev = nev;
        this->bolygo = bolygo;
        szul_bolygo = bolygo;
        this->ero = ero;
    }

    bool kivandorlo() {
        bool sol = true;
       char *arry =   const_cast<char*>(szul_bolygo.c_str());
       char *b =   const_cast<char*>(bolygo.c_str());
        for (int i = 0; i < (bolygo.length()+szul_bolygo.length())/2+1; ++i) {
            if (tolower(arry[i]) != tolower(b[i])){
                return sol;
            }
        }
        sol = false;
        return sol;
    }

   void dolgozik(std::string& munkak) {
        char *f = const_cast<char*>(munkak.c_str());
        string id = "";

        int counter = 1;
        if (munkak.length() != 1){
            for (int i = 0; i < munkak.length(); ++i) {
                if (f[i] == ';') {
                    counter++;
                }
                if (counter > ero){
                    string a = string(1,f[i]);
                    id.append(a);
                }
            }
        } else {
            if (ero < 1){
                string a = string(1,f[0]);
                id.append(a);
            }
        }
        if (id.length()>1){
            id = id.substr(1, id.length());
        }

         munkak = id;
      //  cout << munkak;
       }



};


int main() {
    std::cout << "Hello, World!" << std::endl;
    Telepes telepes = {"Peter", "Fal", "fale", 0};
 //   telepes.dolgozik((string ) "h");

    return 0;
}
