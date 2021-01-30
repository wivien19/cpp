#include <iostream>
#include <string>

using namespace std;

class Allat {
    int tures;
    bool husevo;
    bool novenyevo;

protected:
    Allat(int tures, bool husevo, bool novenyevo) : tures(tures), husevo(husevo), novenyevo(novenyevo) {
        cout << "Allat letrehozva" << endl;
    }
public:
    Allat() : tures(0), husevo(false), novenyevo(false){
        cout << "Allat letrehozva" << endl;
    }

    virtual ~Allat() {
        cout << "Allat torolve" << endl;
    }

    int get_tures() const {
        return tures;
    }

    bool get_husevo() const {
        return husevo;
    }

    bool get_novenyevo() const {
        return novenyevo;
    }
    bool isMindenevo(){
        if (novenyevo && husevo){
            return true;
        }
        return false;
    }
    virtual string hangot_ad(){
        return "";
    }
    Allat& operator<<(int ertek){
        if (tures + ertek < 1){
            cout << "Hiba" << endl;
            return *this;
        }
        tures += ertek;
        return *this;
    }


};
class  Oroszlan final : public Allat {
public:
    Oroszlan() : Allat(4, true, false) {
        cout << "Oroszlan letrehozva" << endl;
    }

    virtual ~Oroszlan() {
        cout << "Oroszlan torolve" << endl;
    }

    virtual string hangot_ad() override {
        return "Morr";
    }


};
class Medve final : public Allat {
public:
    Medve() : Allat(1, true, true) {
        cout << "Medve letrehozva" << endl;
    }

    virtual ~Medve() {
        cout << "Medve torolve" << endl;
    }

    virtual string hangot_ad() override {
        return "Brumm";
    }
};
class Tehen final : public Allat{

    string *oltasok;
    unsigned aktualis_oltasok;
    unsigned  meret;

public:
    Tehen(unsigned oltasmax = 10) : Allat(20, false, true), aktualis_oltasok(0), meret(oltasmax) {

        oltasok = new string[oltasmax];
    }

   Tehen(const Tehen& tehen) : Allat(tehen){
        aktualis_oltasok = tehen.aktualis_oltasok;
        meret = tehen.meret;
        oltasok = new string[meret];
        for (unsigned i = 0; i < aktualis_oltasok; ++i) {
            oltasok[i] = tehen.oltasok[i];
        }
    }

    virtual ~Tehen() {
        delete [] oltasok;
        cout << "Tehen torolve" << endl;

    }

    string *get_oltasok() const {
        return oltasok;
    }

    unsigned int get_aktualis_oltasok() const {
        return aktualis_oltasok;
    }

    Tehen& operator+=(const string& szoveg){
        if (aktualis_oltasok  < meret){

            oltasok[aktualis_oltasok++] = szoveg;

            return *this;
        }
        cout << "Hiba" << endl;
        return *this;
    }

    virtual string hangot_ad() override {
        return "Muuu";
    }


};
class Ketrec {
    int letszam;
    int max_letszam;
    int tipus;
public:
    Ketrec() : letszam(0), max_letszam(0), tipus(0) {}

    int get_letszam() const {
        return letszam;
    }

    int get_max_letszam() const {
        return max_letszam;
    }

    int get_tipus() const {
        return tipus;
    }
    Ketrec operator++(int){
        if(letszam == 0 || letszam + 1 > max_letszam){
            std::cout << "Hiba" << std::endl;
            return *this;
        }
        Ketrec tmp = *this;
        letszam++;
        return tmp;
    }

    Ketrec& operator+=(const Allat& allat){
        if(letszam == 0){
            tipus =allatTipusok(allat);
            max_letszam = allat.get_tures();
            letszam = 1;
            return *this;
        }
        if(allatTipusok(allat) != tipus || letszam + 1 > max_letszam || allat.get_tures() < letszam + 1){
            std::cout<<"Hiba"<<std::endl;
            return *this;
        }
        letszam++;
        if(max_letszam > allat.get_tures()){
            max_letszam = allat.get_tures();
        }

        return *this;

    }


    Ketrec& operator+=(const Ketrec& ketrec){
        if(letszam == 0 || ketrec.get_letszam() == 0){
            if(ketrec.get_letszam() != 0){
                letszam = ketrec.get_letszam();
                max_letszam = ketrec.get_max_letszam();
                tipus = ketrec.get_tipus();
            }
            return *this;
        }
        if(tipus != ketrec.get_tipus() || letszam + ketrec.get_letszam() > max_letszam || letszam + ketrec.get_letszam() > ketrec.get_max_letszam()){
            std::cout<<"Hiba"<<std::endl;
            return *this;
        }
        letszam += ketrec.get_letszam();
        max_letszam = ketrec.get_max_letszam() < max_letszam ? ketrec.get_max_letszam() : max_letszam;

        return *this;
    }

    void urit(){
        letszam = 0;
        max_letszam = 0;
        tipus = 0;
    }

private: unsigned allatTipusok(const Allat &allat){
        if (allat.get_novenyevo() && allat.get_husevo()) return 3;
        if (allat.get_novenyevo()) return 1;
        if (allat.get_husevo()) return 2;
        return 0;
    }

};


int main() {
    std::cout << "Hello, World!" << std::endl;
    unsigned szam = 8;
    Tehen *tehen = new Tehen(szam);
    cout << tehen->hangot_ad() << endl;
    string a = "valami";
    string b = "jancsi";
    cout << tehen->get_aktualis_oltasok() << "ennyi" << endl;
    *tehen += a;

    cout << tehen->get_oltasok()[0]<< endl;
    *tehen += b;
    cout << tehen->get_oltasok()[1]<< endl;
    return 0;
}
