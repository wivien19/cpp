#include <iostream>
#include <string>

using namespace std;

class PostazasiHiba : public exception{

     unsigned const type;
public:
    PostazasiHiba(const unsigned int type) : type(type) {}

    const char* what() const noexcept override {
        if (type == 1){
            return "Belepesi hiba";
        }
        if (type == 2){
            return "Hibas cimzett";
        }
        if ( type == 3){
            return "Ures level";
        }
        return "Ismeretlen hiba";
    }

};
class Level{
    string felado;
    string cimzett;
    string tartalom;
    mutable int allapot;
public:
    const string &get_felado() const {
        return felado;
    }

    const string &get_cimzett() const {
        return cimzett;
    }

    const string &get_tartalom() const {
        return tartalom;
    }

    void set_allapot(int allapot) {
        Level::allapot = allapot;
    }

    int get_allapot() const {
        return allapot;
    }


    Level(const string &felado, const string &cimzett, const string &tartalom) : felado(felado), cimzett(cimzett),
                                                                                 tartalom(tartalom), allapot(0) {}

    Level(const string &felado, const string &cimzett) : felado(felado), cimzett(cimzett), tartalom(""), allapot(0) {}
    Level(const string &felado) : felado(felado), cimzett(""), tartalom(""), allapot(0) {}
    Level() : felado(""), cimzett(""), tartalom(""), allapot(0) {}

   virtual bool felad(const string &szoveg, unsigned  idopont) = 0;

};
class Email : public Level {
    string targy;
    unsigned idopont;
    bool csatolmany;
public:
    const string &get_targy() const {
        return targy;
    }

    unsigned int get_idopont() const {
        return idopont;
    }

    bool is_csatolmany() const {
        return csatolmany;
    }

    Email() : Level(), targy(""), idopont(0), csatolmany(false) {
        set_allapot(0);
    }

    Email(const string &felado, const string &cimzett, const string &tartalom, const string &targy) :
    Level(felado, cimzett, tartalom), targy(targy), idopont(0),
                                                   csatolmany(false) {}

    bool felad(const string &szoveg, unsigned int idopont) override {
        if (szoveg != get_felado()){
           //set_allapot(-1);
            this->idopont = idopont;
            throw PostazasiHiba(1);
        }
        int counter = 0;
        for (int i = 0; i < get_cimzett().length(); ++i) {
            if (get_cimzett()[i] == '@'){
                counter++;
            }
        }
        this->idopont = idopont;
        if (counter != 1) throw PostazasiHiba(2);
       /* std::size_t f = get_cimzett().find();
        if (f == string::npos) {
           //set_allapot(1);

        }*/
        if (targy.empty() && get_tartalom().empty()){
           // set_allapot(0);
            this->idopont = idopont;
            throw PostazasiHiba(3);
        }
        cout << "Elkuldve" << endl;
        set_allapot(2);

        this->idopont = idopont;
        return true;
    }
    explicit operator string () const{
       return "felado: " + get_felado() + "\n"+
        "cimzett: " + get_cimzett() + "\n" +
        "targy: " + get_targy() + "\n" +
        "uzenet:"+"\n" +
        get_tartalom() + "\n";

    }
};
class Postafiok {
protected:
    string email_cim;
    Email *bejovo_levelek;
    Email *elkuldott_levelek;
    unsigned bejovo_db;
    unsigned elkuldott_db;

public:
    Postafiok(const string &emailCim) : email_cim(emailCim), bejovo_levelek(nullptr), elkuldott_levelek(nullptr), bejovo_db(0), elkuldott_db(0) {}

    virtual ~Postafiok(){
        delete [] bejovo_levelek;
        delete [] elkuldott_levelek;
    }

    Postafiok(const Postafiok &postafiok){

        email_cim = postafiok.email_cim;
        bejovo_db = postafiok.bejovo_db;
        elkuldott_db = postafiok.elkuldott_db;
        if (postafiok.bejovo_levelek == nullptr){
            bejovo_levelek = nullptr;
        }  if (postafiok.elkuldott_levelek != nullptr){
            elkuldott_levelek = nullptr;
        }
        if (postafiok.bejovo_levelek != nullptr && postafiok.elkuldott_levelek != nullptr){
            bejovo_levelek = new Email[bejovo_db];
            elkuldott_levelek = new Email[elkuldott_db];
            if (bejovo_db > 0) {
                for (int i = 0; i < postafiok.bejovo_db; ++i) {
                    bejovo_levelek[i] = postafiok.bejovo_levelek[i];
                }
            }
            if (elkuldott_db > 0) {
                for (int i = 0; i < postafiok.elkuldott_db; ++i) {
                    elkuldott_levelek[i] = postafiok.elkuldott_levelek[i];
                }
            }

        }


    }

    Postafiok& operator=(const Postafiok& postafiok){

        if (this == &postafiok){
            return *this;
        }
        delete [] bejovo_levelek;
        delete [] elkuldott_levelek;
        if (postafiok.bejovo_levelek == nullptr){
            bejovo_levelek = nullptr;
        }  if (postafiok.elkuldott_levelek != nullptr){
            elkuldott_levelek = nullptr;
        }
        if (postafiok.bejovo_levelek != nullptr && postafiok.elkuldott_levelek != nullptr){
            email_cim = postafiok.email_cim;
            bejovo_db = postafiok.bejovo_db;
            elkuldott_db = postafiok.elkuldott_db;
            bejovo_levelek = new Email[bejovo_db];
            elkuldott_levelek = new Email[elkuldott_db];

            for (int i = 0; i < bejovo_db; ++i) {
                bejovo_levelek[i] = postafiok.bejovo_levelek[i];
            }
            for (int i = 0; i < elkuldott_db; ++i) {
                elkuldott_levelek[i] = postafiok.elkuldott_levelek[i];
            }
        }

        return *this;
    }

    virtual Postafiok& operator+=(const Email &email){
        if (email.get_cimzett() != email_cim) throw invalid_argument( "Hibas cimzett");

       /* Email *uj = new Email[bejovo_db+1];

        for (int i = 0; i < bejovo_db-1; ++i) {
            uj[i] = bejovo_levelek[i];
        }
        bejovo_levelek = uj;
        bejovo_levelek[bejovo_db++] = email;
        return *this;*/
       if (bejovo_levelek != nullptr){
           bejovo_levelek[bejovo_db++] = email;
       }

        return *this;
    }


    friend bool operator==(const Postafiok &rhs, const string &s) {
        return s == rhs.email_cim;
    }
    friend bool operator==(const string &s,const Postafiok &rhs) {
        return s == rhs.email_cim;
    }



};

class IngyenesPostafiok : public Postafiok{

    unsigned max_tarhely;

public:
    unsigned int get_max_tarhely() const {
        return max_tarhely;
    }

    void set_max_tarhely(unsigned int maxTarhely) {
        max_tarhely = maxTarhely;
    }

    IngyenesPostafiok(const string &emailCim, unsigned int maxTarhely) : Postafiok(emailCim), max_tarhely(maxTarhely) {}

    Postafiok &operator+=(const Email &email) override {


        if (bejovo_db + elkuldott_db <max_tarhely){
            return Postafiok::operator+=(email);
        }

        return *this;
    }
};
class Tort  {
    int szamlalo = 0;
    int nev = 0;
    Tort operator+(double sz){
        Tort tort = *this;
        tort.szamlalo = 0;
        return tort;
}
};




int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
