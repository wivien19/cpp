#include <iostream>
#include <string>

using namespace std;
class Hiba : public exception {
    int hibakod;
public:
    int get_hibakod() const {
        return hibakod;
    }

    Hiba(int hibakod) : hibakod(hibakod) {}
};
class Jatek {

    string nev;
    unsigned tarhely_igeny;
    unsigned firmware_igeny;

public:
    unsigned int get_tarhely_igeny() const {
        return tarhely_igeny;
    }

    unsigned int get_firmware_igeny() const {
        return firmware_igeny;
    }

    Jatek(const string &nev, unsigned int tarhelyIgeny, unsigned int firmwareIgeny) : nev(nev),
                                                                                      tarhely_igeny(tarhelyIgeny),
                                                                                      firmware_igeny(firmwareIgeny) {}

    Jatek(): nev(""),
    tarhely_igeny(0),
    firmware_igeny(0){}

    bool operator==(Jatek jatek) const {
        if (nev == jatek.nev && tarhely_igeny == jatek.tarhely_igeny && firmware_igeny == jatek.firmware_igeny){
            return true;
        }
        return false;
    }
};

class Jatekplatform{

    unsigned max_tarhely;
    unsigned felhasznalt_tarhely;
    Jatek *jatekok;
    unsigned jatek_szam;
    unsigned firmware;

public:
    Jatek *get_jatekok() const {
        return jatekok;
    }

    unsigned int get_jatek_szam() const {
        return jatek_szam;
    }

    unsigned int get_firmware() const {
        return firmware;
    }

    Jatekplatform(unsigned int maxTarhely, unsigned int firmware) : max_tarhely(maxTarhely), firmware(firmware),
    jatekok(nullptr), jatek_szam(0), felhasznalt_tarhely(0){}

    virtual ~Jatekplatform() {
        delete [] jatekok;
    }
    Jatekplatform(const Jatekplatform &jatekplatform) : max_tarhely(jatekplatform.max_tarhely),
                                                        felhasznalt_tarhely(jatekplatform.felhasznalt_tarhely),
                                                        jatekok(new Jatek[jatekplatform.jatek_szam]),
                                                        jatek_szam(jatekplatform.jatek_szam),
                                                        firmware(jatekplatform.firmware){

        for (int i = 0; i < jatek_szam; ++i) {
            jatekok[i] = jatekplatform.jatekok[i];
        }
    }

    Jatekplatform& operator=(Jatekplatform &jatekplatform){
        if (&jatekplatform == this){
            return *this;
        }
        delete [] jatekok;
        max_tarhely = jatekplatform.max_tarhely;
        firmware = jatekplatform.firmware;
        jatek_szam = jatekplatform.jatek_szam;
        felhasznalt_tarhely = jatekplatform.felhasznalt_tarhely;

        jatekok = new Jatek[jatekplatform.jatek_szam];
        for (int i = 0; i < jatek_szam; ++i) {
            jatekok[i] = jatekplatform.jatekok[i];
        }
        return *this;
    }
    Jatekplatform& operator++(){
        firmware++;
        return *this;
    }
    Jatekplatform operator++(int szam){
        Jatekplatform tmp = *this;
       operator++();
        return tmp;
    }
    virtual Jatekplatform& operator+=(const Jatek &jatek){
        for (int i = 0; i < jatek_szam; ++i) {
            if (jatekok[i] == jatek){
                throw Hiba(1);
            }
        }

            if (max_tarhely - felhasznalt_tarhely < jatek.get_tarhely_igeny()){
                throw Hiba(2);
            }

            if (firmware < jatek.get_firmware_igeny()){
                throw Hiba(3);
            }

            Jatek *uj = new Jatek[jatek_szam+1];
        for (int i = 0; i < jatek_szam; ++i) {
            uj[i] = jatekok[i];
        }
        delete [] jatekok;
        jatekok = uj;
        jatekok[jatek_szam++] = jatek;
        felhasznalt_tarhely += jatek.get_tarhely_igeny();
        return *this;



    }

};

class Playstation : public Jatekplatform{
    bool pro;
public:
    bool get_pro() const {
        return pro;
    }

    Playstation(unsigned int maxTarhely, unsigned int firmware, bool pro) : Jatekplatform(maxTarhely, firmware),
                                                                            pro(pro) {}

    Jatekplatform &operator+=(const Jatek &jatek) override {
        if (!pro) return Jatekplatform::operator+=(jatek);
        try {
            return Jatekplatform::operator+=(jatek);
        } catch (const Hiba& h) {
            if (h.get_hibakod() != 3)
                throw;
        }
        if (get_firmware() < jatek.get_firmware_igeny()){
            for (unsigned i =get_firmware(); i <  jatek.get_firmware_igeny(); ++i) {
                operator++();
            }
        }
        return Jatekplatform::operator+=(jatek);
    }
};


int main() {
    std::cout << "Hello, World!" << std::endl;
    Jatekplatform jatekplatform = Jatekplatform(15,10);

    cout << jatekplatform.get_firmware();
    return 0;
}
