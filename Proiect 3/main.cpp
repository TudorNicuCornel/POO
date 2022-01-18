#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

class Vaccin{
protected:
    double pret;
    double temperatura_de_depozitare;
    list <string> substante;
public:
    virtual ~Vaccin()=default;
    Vaccin():pret(0),temperatura_de_depozitare(0){};

    Vaccin(double pret,double temperatura_de_depozitare,list<string> substante): pret(pret),
        temperatura_de_depozitare(temperatura_de_depozitare),substante(substante){};

    virtual istream& citire(istream& is)
    {
        cout<<"Pret:";
        is>>pret;
        cout<<" Temperatura de depozitare:";
        is>>temperatura_de_depozitare;
        int n;
        cout<<"Introduceti numarul de substante:";
        list<string>::iterator i;
        for (i = substante.begin(); i != substante.end(); i++)
            is>>*i;
        return is;
    }

    friend istream& operator >>(istream& is,Vaccin &p)
    {
        p.citire(is);
        return is;
    }

    virtual ostream& afisare(ostream &os)
    {
        os<<"Pret: "<<pret<<" Temperatura de depozitare:"<<temperatura_de_depozitare;
        list<string>::iterator i;
        int j=1;
        for(i=substante.begin();i!=substante.end();i++) {
           os<<"Substanta "<<j<<" este:"<< *i;
           j++;
        }
        return os;
    }

    friend ostream& operator<<(ostream& os, Vaccin &p)
    {
        p.afisare(os);
        return os;
    }

    virtual void afisareSchemaVaccinare()
    {
        cout<<"clasa baza";
    }

};

class VaccinAntigripal:public Vaccin{
private:
    string tulpina;
    bool respecta_organizatia;
public:
    ~VaccinAntigripal()=default;

    VaccinAntigripal():tulpina("a"),respecta_organizatia(false){};

    VaccinAntigripal(double pret,double temperatura_de_depozitare,
                     list <string> substante,string tulpina,
                     bool respecta_organizatia):
                     Vaccin(pret,temperatura_de_depozitare,substante),
                     tulpina(tulpina),respecta_organizatia(respecta_organizatia){};

    istream& citire(istream &is) override
    {
        Vaccin::citire(is);
        cout<<"Tulpina pt care se administreaza:";
        is>>tulpina;
        is.setf(std::ios::boolalpha);
        cout<<" Respecta Regulile Organizatiei?(true,false):";
        is>>respecta_organizatia;
        return is;
    }

    ostream& afisare(ostream &os){
        Vaccin::afisare(os);
        os<<" Tulpina:"<<tulpina<<" Respecta Regulile Organizatiei?:"<<respecta_organizatia;
        return os;
    }

    void afisareSchemaVaccinare() override
    {
        cout << "Vaccinul antigripal se administreaza la adulti o doza de 0.5 ml, iar la copii si adolescenti o doza ";
        cout << "de 0.3 ml, repetandu-se din 2 in 2 ani.\n";
    }

};

class VaccinAntihepatic: public Vaccin{
private:
    std::string tip;
    std::string mod_vaccinare;
public:
    VaccinAntihepatic():tip("a"),mod_vaccinare("a"){};

    VaccinAntihepatic(double pret,double temperatura_de_depozitare,
                     list <string> substante,string tip,
                     string mod_vaccinare):
            Vaccin(pret,temperatura_de_depozitare,substante),
            tip(tip),mod_vaccinare(mod_vaccinare){};

    istream& citire(istream &is)
    {
        Vaccin::citire(is);
        cout<<"Tipul Vaccinului:";
        cin>>tip;
        cout<<"Modul de vaccinare:";
        cin>>mod_vaccinare;
        return is;
    }

    ostream& afisare(ostream &os)
    {
        Vaccin::afisare(os);
        os<<" Tipul vaccinului este:"<<tip;
        os<<" Modul de vaccinare este:"<<mod_vaccinare;
        return os;
    }

    void afisareSchemaVaccinare() override {

        cout << "Vaccinul antihepatita A si B, la copii cu varsta mai mica de 1 an se adminstreaza 2 ";
        cout
                << "injectari la un interval de o luna, a treia injectare dupa 6 luni de la prima administrare, la adulti\n";
        cout
                << "conform schemei de imunizare recomandata de medic; cel Antihepatita C doar la recomandarea medicului.\n";
    }
};

class VaccinAntiSarsCov2:public Vaccin
{
private:
    list <string> efecte;
    list <string> medicamente_contraindicate;
    double eficienta;
public:
    VaccinAntiSarsCov2():eficienta(0){};

    VaccinAntiSarsCov2(double pret,double temperatura_de_depozitare,
                      list <string> substante,list<string> efecte,
                       list<string> medicamente_contraindicate):
            Vaccin(pret,temperatura_de_depozitare,substante),
            efecte(efecte),medicamente_contraindicate(medicamente_contraindicate){};

    istream& citire(istream &is)
    {
        Vaccin::citire(is);
        cout<<"Introduceti numarul de substante:";
        list<string>::iterator i;
        for (i = efecte.begin(); i != efecte.end(); i++)
            is>>*i;
        cout<<"Introduceti numarul de substante:";
        for (i = medicamente_contraindicate.begin(); i != medicamente_contraindicate.end(); i++)
            is>>*i;
        cout<<"Eficienta vaccinului:";
        is>>eficienta;
        return is;
    }

    ostream& afisare(ostream &os)
    {
        Vaccin::afisare(os);

        list<string>::iterator i;
        int j=1;
        for (i = efecte.begin(); i != efecte.end(); i++){
            os<<"Efectul "<<j<<" este:"<< *i;
            j++;
        }

        j=1;
        for (i = medicamente_contraindicate.begin(); i != medicamente_contraindicate.end(); i++){
            os<<"Medicamentul contraindicat "<<j<<" este:"<< *i;
            j++;
        }
        os<<"Eficienta vaccinului este:"<<eficienta;

        return os;
    }

    void afisareSchemaVaccinare() override {

        cout << "Vaccinul anti Sars-Cov2 se administreaza persoanelor cu varsta de peste 16 ani, ";
        cout << "2 doze la o perioada de 21 zile.\n";
    }

};

struct ComandaVaccin {
    Vaccin *vaccin;
    int cantitate;
};

class Comanda {
private:
    const int idComanda{};
    int zi{};
    int luna{};
    int an{};
    string numeClient;
    vector< ComandaVaccin> vaccinuri;

public:
    Comanda() {}

    ~Comanda() {}

    Comanda(const int idComanda, int zi, int luna, int an, const string &numeClient,
             vector<ComandaVaccin> &vaccinuri) : idComanda(idComanda), zi(zi), luna(luna), an(an),
                                                      numeClient(numeClient), vaccinuri(vaccinuri) {}


    friend istream &operator>>(istream &is, Comanda &comanda) {
        comanda.citire(is);
        return is;
    }

    istream &citire(istream &is) {
        cout << "zi:";
        is >> zi;

        cout << "luna:";
        is >> luna;

        cout << "an";
        is >> an;

        cout << "numeClient:";
        is >> numeClient;

        cout << "Introduceti numarul de vaccinuri:";
        int nrVaccinuri;
        is >> nrVaccinuri;
               for (int i = 0; i < nrVaccinuri; i++) {
                    int option, c = 0;
                    Vaccin *vaccin;
                    while (c == 0) {
                        cout<<"1-VaccinAntigripal\n";
                        cout<<"2-VaccinSarsCov2\n";
                        cout<<"3-VaccinAntihepatic\n";
                        cout<<"Tipul vaccinului dorit:";
                        cin>>option;
                        c=1;
                            switch (option) {
                                case 1: {
                                    vaccin = new VaccinAntigripal();
                                    break;
                                }
                                case 2: {
                                    vaccin = new VaccinAntiSarsCov2();
                                    break;
                                }
                                case 3: {
                                    vaccin = new VaccinAntihepatic();
                                    break;
                                }
                                default:
                                    cout << "error";
                                    break;
                            }
                            vaccin->citire(cin);
                            int cantitate;
                            cout << "Cantitate:";
                            is >> cantitate;
                            struct ComandaVaccin comanda;
                            vaccinuri.push_back({vaccin, cantitate});
                    }
                }


            return is;
        }


        ostream &afisare(ostream &os) const {
            os << "idComanda: " << idComanda << "\n";
            os << "data: " << zi << "/" << luna << "/" << an << "\n";
            os << "numeClient: " << numeClient << "\n";
            int i = 1;
            for (auto &vaccin: vaccinuri) {
                os << "vaccinul " << i << " : " << vaccin.vaccin <<" cantitate"<< vaccin.cantitate << "\n";
            }
            return os;
            }

    friend ostream &operator<<(ostream &os, const Comanda &comanda) {
        comanda.afisare(os);
        return os;
    }

};


int main() {
    VaccinAntigripal a;
    VaccinAntihepatic b;
    VaccinAntiSarsCov2 c;
    cin>>a>>b>>c;
    cout<<a<<b<<c;
    Vaccin* list[3];
    list[0]=new VaccinAntigripal();
    list[1]=new VaccinAntihepatic();
    list[2]=new VaccinAntiSarsCov2();
    for(int i=0;i<3;i++)
        list[i]->afisareSchemaVaccinare();
    return 0;
}
