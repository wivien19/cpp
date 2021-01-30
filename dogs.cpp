#include <iostream>
#include <string>

using namespace std;

class Kutya {

    string nev;
    unsigned kor;

public:
    const string &get_nev() const {
        return nev;
    }

    unsigned int get_kor() const {
        return kor;
    }

    Kutya(const string &nev, unsigned int kor) : nev(nev), kor(kor) {
        cout << "Kutya letrehozva" << endl;
    }

public:
   /* virtual string pedigre(){
        string a = to_string (kor);
        return "nev:" + nev+", kor:" + a +" ev";
    }*/

    virtual string pedigre() const{
        string a = to_string (kor);
        return "nev:" + nev+", kor:" + a +" ev";
    }

    virtual string* terel(const string* nyaj, unsigned& nyajhossz) const{
        if (nyaj == nullptr || nyajhossz == 0){
            nyajhossz = 0;
            return nullptr;
        }
        string* tomb= new string[nyajhossz];
        for (int i = 0; i < nyajhossz; ++i) {
            tomb[i] = nyaj[i];
        }
        return tomb;

    }
   /* const string* terel(const string* nyaj, unsigned& nyajhossz) const{
        if (nyaj == nullptr || nyajhossz == 0){
            nyajhossz = 0;
            return nullptr;
        }
        string* tomb= new string[nyajhossz];
        for (int i = 0; i < nyajhossz; ++i) {
            tomb[i] = nyaj[i];
        }
        return tomb;

    }*/

};
  class BorderCollie : public Kutya{
     unsigned terelo_kapacitas;


 public:
     unsigned int get_terelo_kapacitas() const {
         return terelo_kapacitas;
     }

     BorderCollie(const string &nev, unsigned int kor, unsigned int tereloKapacitas) : Kutya(nev, kor),
                                                                                       terelo_kapacitas(
                                                                                               tereloKapacitas) {}
      virtual string pedigre() const{
          string a = to_string (get_kor());
          string b = to_string(terelo_kapacitas);
          return "nev:" + get_nev()+", kor:" + a +" ev, faj:border collie, terelo kapacitas:"+ b +" db birka";
      }

      string* terel(const string* nyaj, unsigned& nyajhossz) const override{
          if (nyaj == nullptr || nyajhossz == 0) {
              nyajhossz = 0;
              return nullptr;
          }
          string* tomb = new string[nyajhossz];
          for (int i = 0; i < nyajhossz; ++i) {
              tomb[i] = nyaj[i];
          }
          int terelt = 0;
          int i = 0;
          int j = 0;
          string csere;

          while (terelt < terelo_kapacitas && i != nyajhossz) {
              if(tomb[i] != ""){
                  terelt++;
                  csere = tomb[j];
                  tomb[j] = tomb[i];
                  tomb[i] = csere;
                  j++;
              }
              i++;
          }
          int ujhosz = 0;
          for (int k = 0; k < nyajhossz; ++k) {
              if(tomb[k] == "") {
                  ujhosz++;
              } else {
                  ujhosz = 0;
              }
          }
          nyajhossz -= ujhosz;
          return tomb;
      }

  };
void print(const Kutya& k){
    cout << k.pedigre() << endl;
}
int main() {
    std::cout << "Hello, World!" << std::endl;
    BorderCollie bc("Jess", 12, 2);
    string nyaj[] = {"","","", "Frici", "Julcsa",   "gyuri", "margit"};
    unsigned hossz = 7;
    string* osszeterelt = bc.terel(nyaj, hossz);
    for (unsigned i = 0; i < hossz; ++i) {
      cout << osszeterelt[i] << 'e' << endl;

    }



    return 0;
}
