#include <iostream>
#include <string>

using namespace std;

class VilagitoDisz{
    unsigned fenyesseg;
    bool bekapcsolva = false;
public:
    unsigned int get_fenyesseg() const {
        if (bekapcsolva){
            return fenyesseg;
        }
        return 0;
    }

    VilagitoDisz(unsigned int fenyesseg) : fenyesseg(fenyesseg) {}

    VilagitoDisz() {
        fenyesseg = 0;
        bekapcsolva = false;
    }
    VilagitoDisz& operator++() {
        bekapcsolva = true;
        return *this;
    }
    VilagitoDisz& operator--() {
        bekapcsolva = false;
        return *this;
    }



};

class KisKaracsonyfa{
    VilagitoDisz* csucs_disz;
    string fa_tipus;
public:
    KisKaracsonyfa(const string &fa_tipus = "luc") : fa_tipus(fa_tipus) {
        csucs_disz = nullptr;
    }

    void disz_felhelyezese(VilagitoDisz disz){
        if (csucs_disz != nullptr){
            delete [] csucs_disz;
        }
         VilagitoDisz *disz2 = new VilagitoDisz(disz) ;
         csucs_disz = disz2;
    }
    void bekapcsol(){
        if (csucs_disz != nullptr){
            ++(*this->csucs_disz);
        }

    }
    void kikapcsol(){
        if (csucs_disz != nullptr){
            --(*this->csucs_disz);
        }
    }
    unsigned int get_fenyesseg(){
        if (csucs_disz == nullptr){
            return 0;
        }
        return csucs_disz->get_fenyesseg();
    }

    KisKaracsonyfa(const KisKaracsonyfa &kisKaracsonyfa){
        this->csucs_disz = new VilagitoDisz(*kisKaracsonyfa.csucs_disz);
        this->fa_tipus = kisKaracsonyfa.fa_tipus;
    }

    KisKaracsonyfa& operator=(KisKaracsonyfa& kisKaracsonyfa){
        if (this == &kisKaracsonyfa){
            return *this;
        }
        delete csucs_disz;
        csucs_disz = new VilagitoDisz(*kisKaracsonyfa.csucs_disz);
        fa_tipus = kisKaracsonyfa.fa_tipus;
        return *this;
    }

    virtual ~KisKaracsonyfa() {
        delete [] csucs_disz;
    }

};

class NagyKaracsonyfa {
    VilagitoDisz* diszek;
    unsigned diszek_szama;
    unsigned act = 0;
public:
    NagyKaracsonyfa(unsigned int diszekSzama) : diszek_szama(diszekSzama) {
        diszek = new VilagitoDisz[diszekSzama];
    }

    virtual ~NagyKaracsonyfa() {
        delete [] diszek;
    }

    void disz_felhelyezese(VilagitoDisz vilagitoDisz){
        if (act < diszek_szama){
            diszek[act] = vilagitoDisz;
            act++;
        }
    }
    void bekapcsol(){
        if (diszek != nullptr){
            for (int i = 0; i < act; ++i) {
                ++(diszek[i]);
            }
        }
    }

    void kikapcsol(){
        if (diszek != nullptr){
            for (int i = 0; i < act; ++i) {
                --(diszek[i]);
            }
        }

    }

    unsigned get_fenyesseg(){
        int osszFenyesseg = 0;
        if (diszek == nullptr) return 0;
        for (int i = 0; i < diszek_szama; ++i) {
            osszFenyesseg += diszek[i].get_fenyesseg();
        }
        return osszFenyesseg;
    }
    NagyKaracsonyfa(NagyKaracsonyfa &nagyKaracsonyfa){
        diszek_szama = nagyKaracsonyfa.diszek_szama;
        act = nagyKaracsonyfa.act;
        diszek = new VilagitoDisz(*nagyKaracsonyfa.diszek);
    }
    NagyKaracsonyfa& operator=(NagyKaracsonyfa& nagyKaracsonyfa) {
        if (this == &nagyKaracsonyfa){
            return *this;
        }
        delete [] diszek;
        diszek_szama = nagyKaracsonyfa.diszek_szama;
        act = nagyKaracsonyfa.act;
        diszek = new VilagitoDisz(*nagyKaracsonyfa.diszek);
        for (int i = 0; i < diszek_szama; ++i) {
            diszek[i] = nagyKaracsonyfa.diszek[i];
        }
        return *this;
    }
};


int main() {
    std::cout << "Hello, World!" << std::endl;
    KisKaracsonyfa karacsonyfa();
    VilagitoDisz* vilagitoDisz;
   // cout << karacsonyfa().get_fa_tipus();
    //cout << karacsonyfa.disz_felhelyezese(vilagitoDisz);
    return 0;
}
