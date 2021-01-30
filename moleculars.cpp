#include <iostream>
#include <string>

using namespace std;

class Elem {
    int protonszam;
    int neutronszam;
    int elektronszam;
public:
    Elem() : protonszam(0), neutronszam(0), elektronszam(0) {}

    int get_protonszam() const {
        return protonszam;
    }

    int get_neutronszam() const {
        return neutronszam;
    }

    int get_elektronszam() const {
        return elektronszam;
    }

    Elem(int protonszam, int neutronszam, int elektronszam) : protonszam(protonszam), neutronszam(neutronszam),
                                                              elektronszam(elektronszam) {}

    virtual ~Elem() {

    }

    virtual const bool isAlkalifem() const {
        const bool a = false;
        return a;
    }

    void operator++() {
        elektronszam++;
    }

    Elem &operator--() {
        if (elektronszam - 1 < 0) {
            cout << "Hiba" << endl;
            return *this;
        } else {
            elektronszam--;
            return *this;
        }
    }

    void operator+=(int szam) {
        elektronszam += szam;
    }

    void operator-=(int szam) {
        if (elektronszam - szam < 0) {
            cout << "Hiba" << endl;
        } else {
            elektronszam -= szam;
        }
    }

    const bool operator==(Elem elem) const {
        if (protonszam != elem.protonszam || elektronszam != elem.elektronszam || neutronszam != elem.neutronszam) {
            return false;
        }
        return true;
    }

};

class Natrium final : public Elem {
public:
    Natrium() : Elem(11, 12, 11) {
        cout << "Natrium letrehozva" << endl;
    }

    virtual ~Natrium() {
        cout << "Natrium torolve" << endl;
    }

    const bool isAlkalifem() const override {
        const bool a = true;
        return a;
    }


};

class Klor : public Elem {
public:
    Klor() : Elem(17, 18, 17) {
        cout << "Klor letrehozva" << endl;
    }

    virtual ~Klor() {
        cout << "Klor torolve" << endl;
    }
};

class Molekula {
    string nev;
    int darabszam;
    Elem *alkotok;
    int aktualis;
    int max;
public:
    const string &get_nev() const {
        return nev;
    }

    int get_darabszam() const {
        return darabszam;
    }

    Elem *get_alkotok() const {
        return alkotok;
    }

    int get_aktualis() const {
        return aktualis;
    }

    Molekula(const string &nev, int max) {
        this->nev = nev;
        this->aktualis = 0;
        this->darabszam = 0;
        this->alkotok = new Elem[max];
        this->max = max;
    }


    Molekula(Molekula &molekula) {
        nev = molekula.nev;
        aktualis = molekula.aktualis;
        darabszam = molekula.darabszam;
        max = molekula.max;
        alkotok = new Elem[molekula.max];
        for (int i = 0; i < molekula.aktualis; ++i) {
            alkotok[i] = molekula.alkotok[i];
        }
    }

    Molekula& operator=(const Molekula &molekula) {
        if (this == &molekula) {
            return *this;
        }
        delete[] alkotok;
        nev = molekula.nev;
        aktualis = molekula.aktualis;
        darabszam = molekula.darabszam;
        max = molekula.max;
        alkotok = new Elem[molekula.max];
        for (int i = 0; i < molekula.aktualis; ++i) {
            alkotok[i] = molekula.alkotok[i];
        }
        return *this;
    }

    virtual ~Molekula() {
        //cout << "a c++ kitalaloja hogy van?" << endl;
        delete[] alkotok;
    }

    bool add(const Molekula &molekula) {
        if (nev == molekula.nev) {
            darabszam++;
            return true;
        }
        return false;
    }

    bool add(const Elem &elem) {
        if (max - aktualis > 0) {
            alkotok[aktualis] = elem;
            aktualis++;
            return true;
        }
        return false;

    }
};


int main() {
    std::cout << "Hello, World!" << std::endl;
    Elem elem = Elem(15, 20, 30);
    Elem elem1 = Elem(15, 20, 30);
    cout << elem.get_elektronszam() << endl;
    cout << elem1.get_elektronszam() << endl;
    Natrium natrium = Natrium();
    string nev = "jancsi";
    int szam = 15;
    Molekula *mo =new Molekula(nev, szam);
    cout << mo->get_aktualis() << endl;


    if (elem == Elem(15, 25, 30))
        cout << "azonos" << endl;
    else cout << "kolonbozo";

    return 0;
}
