#include <iostream>
#include <string>

using  namespace  std;

class MemoriaHiba : public exception {

 const int hibakod;
public:
     MemoriaHiba(int hibakod) : hibakod(hibakod) {}
    const char* what() const noexcept override {
        if (hibakod == 1){
            return "Olvasasi hiba";
        }
        if (hibakod == -1){
            return "Megtelt a memoriakartya";
        }
        return "Ismeretlen hiba";
    }
};
class MediaTartalom {
public:
    string nev;
    string utvonal;

    const string &get_nev() const {
        return nev;
    }

    MediaTartalom(const string &nev, const string &utvonal = "") : nev(nev), utvonal(utvonal) {}

    virtual double get_meret() const = 0;

    string fajl_utvonala(){
        return utvonal + "/" + nev;
    }
    void operator<<(string szoveg){
        utvonal += ("/" + szoveg);
    }
};

class Fenykep : public MediaTartalom {

    int meret_x;  //szelesseg
    int meret_y;  //magassag

public:
    Fenykep(const string &nev, int meretX, int meretY, const string &utvonal = "") : MediaTartalom(nev, utvonal),
                                                                                meret_x(meretX), meret_y(meretY) {}

    Fenykep() : MediaTartalom("", ""), meret_x(0), meret_y(0) {}

    double get_meret() const override {
        double var = (meret_x*meret_y)*3/1000;
        return var ;
    }

    bool hibas() const{
        if (meret_x == -1 && meret_y == -1) return true;
        return false;
    }
    bool operator==(Fenykep &fenykep){

    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
