/*NUME: Tudor Nicu-Cornel,gr 263
 TUTORE: Deaconu Eduard Stefan
 COMPILATOR: MingW Codeblocks
 PROGRAM: CLION
  */

#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <map>
#include <memory>

enum activitati {
    spalare=0
    ,periere=1
    ,joaca=2
    ,dresaj=3,
    socializare=4,
    niciUna=5
};
class PachetClasic
{
protected:
    int nrMese;
    bool singur;
    std::list <std::string> alergeni;
public:
    ~PachetClasic()=default;
    PachetClasic():nrMese(0),singur(false){}
    PachetClasic(int _nrMese,bool _singur,std::list<std::string> _alergeni)
    {
        this->nrMese=_nrMese;
        this->singur=_singur;
        this->alergeni=_alergeni;
    }

    virtual std::istream& citire(std::istream &is)
    {
        std::cout<<"Nr de mese pe zi este: ";
        is>>nrMese;
        is.setf(std::ios::boolalpha);
        std::cout<<"Singur in camera(true,false): ";
        is>>singur;
        int nr;
        std::string alergen;
        std::cout<<"Numarul de alergeni:";std::cin>>nr;
        std::cout<<"Alergenii sunt:";
        for(int i=0;i<nr;i++) {
            is >> alergen;
            alergeni.push_back(alergen);
        }
        return is;
    }

    friend std::istream& operator >>(std::istream &is,PachetClasic &p)
    {
        p.citire(is);
        return is;
    }

    virtual std::ostream& afisare(std::ostream &os)
    {
        os<<"Nr de mese pe zi:"<<nrMese;
        os<<" Singur in camera:"<<singur;
        os<<" Alergeni:";
        std::list<std::string>::iterator i;
        for(i=alergeni.begin();i!=alergeni.end();i++) {
            os << *i << " ";
        }
        return os;
    }

    friend std::ostream& operator <<(std::ostream &os,PachetClasic &p)
    {
        p.afisare(os);
        return os;
    }

};

class PachetSportiv:virtual public PachetClasic
{
protected:
    int nrPlimbari;
public:
    ~PachetSportiv()=default;
    PachetSportiv():nrPlimbari(0){}
    PachetSportiv(int _nrMese,bool _singur,std::list<std::string> _alergeni,int _nrPlimbari):PachetClasic(_nrMese,_singur,_alergeni)
    {
        this->nrPlimbari=_nrPlimbari;
    }
    std::istream& citire(std::istream& is) override
    {
        PachetClasic::citire(is);
        std::cout<<"Nr de plimbari:";
        is>>nrPlimbari;
        return is;
    }

    std::ostream& afisare(std::ostream& os) override
    {
        PachetClasic::afisare(os);
        os<<" Nr de plimbari:"<<nrPlimbari;
        return os;
    }

};


class PachetConfort:virtual public PachetClasic
{
protected:
    activitati nr1;
    activitati nr2;
public:
    ~PachetConfort()=default;
    PachetConfort(): nr1(static_cast<activitati>(0)), nr2(static_cast<activitati>(0)){}
    PachetConfort(int _nrMese,bool _singur,std::list<std::string> _alergeni,activitati _nr1,activitati _nr2):PachetClasic(_nrMese,_singur,_alergeni)
    {
        this->nr1=_nr1;
        this->nr2=_nr2;
    }

    std::istream& citire(std::istream& is) override
    {
        PachetClasic::citire(is);
        int a1,a2;
        std::cout<<"Activitatea 1:";
        std::cin>>a1;
        std::cout<<"Activitatea 2:";
        std::cin>>a2;
        if(a1==0){
            nr1=activitati::spalare;}
        else if(a1==1)
        {
            nr1=activitati::periere;
            }
        else if(a1==2)
        {
            nr1=activitati::joaca;
            }
        else if(a1==3)
        {
            nr1=activitati::dresaj;
            }
        else if(a1==4)
        {
            nr1=activitati::socializare;
            }
        else if(a1==5)
        {
            nr1=activitati::niciUna;
            }

        if(a2==0){
            nr2=activitati::spalare;}
        else if(a2==1)
        {
            nr2=activitati::periere;
        }
        else if(a2==2)
        {
            nr2=activitati::joaca;
        }
        else if(a2==3)
        {
            nr2=activitati::dresaj;
        }
        else if(a2==4)
        {
            nr2=activitati::socializare;
        }
        else if(a2==5)
        {
            nr2=activitati::niciUna;
        }


        return is;
    }

    std::ostream& afisare(std::ostream& os) override
    {
        PachetClasic::afisare(os);
        os<<" Activitatea 1 este:"<<nr1;
        os<<" Activitatea 2 este:"<<nr2;

        return os;
    }


};

class PachetVIP:public PachetSportiv, public PachetConfort
{
private:
    std::vector<activitati> alegereActivitati;
    std::map<std::string,int> plimbari;
public:
    ~PachetVIP()=default;
    PachetVIP()=default;
    PachetVIP(int _nrMese,bool _singur,std::list<std::string> _alergeni,int _nrPlimbari
              ,activitati _nr1,activitati _nr2,std::vector<activitati> _alegereActivitati,std::map<std::string,int> _plimbari):
              PachetSportiv(_nrMese,_singur,_alergeni,_nrPlimbari)
    {
        this->nr1=_nr1;
        this->nr2=_nr2;
        this->alegereActivitati=_alegereActivitati;
        this->plimbari=_plimbari;
    }

    std::istream &citire(std::istream &is)
    {
        PachetSportiv::citire(is);
        int a1,a2;
        std::cout<<"Activitatea 1:";
        std::cin>>a1;
        std::cout<<"Activitatea 2:";
        std::cin>>a2;
        if(a1==0){
            nr1=activitati::spalare;}
        else if(a1==1)
        {
            nr1=activitati::periere;
        }
        else if(a1==2)
        {
            nr1=activitati::joaca;
        }
        else if(a1==3)
        {
            nr1=activitati::dresaj;
        }
        else if(a1==4)
        {
            nr1=activitati::socializare;
        }
        else if(a1==5)
        {
            nr1=activitati::niciUna;
        }

        if(a2==0){
            nr2=activitati::spalare;}
        else if(a2==1)
        {
            nr2=activitati::periere;
        }
        else if(a2==2)
        {
            nr2=activitati::joaca;
        }
        else if(a2==3)
        {
            nr2=activitati::dresaj;
        }
        else if(a2==4)
        {
            nr2=activitati::socializare;
        }
        else if(a2==5)
        {
            nr2=activitati::niciUna;
        }

        int nrActiv,activitate;
        if(nrActiv>=1)
        {
            for(int i=0;i<nrActiv;i++)
            {
                is>>activitate;
                if(activitate==0){
                    alegereActivitati.push_back(activitati::spalare);}
                else if(activitate==1)
                {
                    alegereActivitati.push_back(activitati::periere);
                }
                else if(activitate==2)
                {
                    alegereActivitati.push_back(activitati::joaca);
                }
                else if(activitate==3)
                {
                    alegereActivitati.push_back(activitati::dresaj);
                }
                else if(activitate==4)
                {
                    alegereActivitati.push_back(activitati::socializare);
                }
                else if(activitate==5)
                {
                    alegereActivitati.push_back(activitati::niciUna);
                }

            }
        }
        std::string ora;
        int minute;
        for(int i=0;i<nrPlimbari;i++)
        {
            std::cout<<"Ora plimbare:";
            is>>ora;
            std::cout<<"Durata plimbare(minute):";
            is>>minute;
            plimbari.insert(std::pair<std::string,int>(ora,minute));
        }

        return is;
    }

    std::ostream& afisare(std::ostream &os)
    {
        PachetSportiv::afisare(os);
        os<<" Activitatea 1 este:"<<nr1;
        os<<" Activitatea 2 este:"<<nr2;
        std::vector<activitati>::iterator i;
        std::map<std::string,int>::iterator j;
        os<<" Activitati alese:";
        for(i=alegereActivitati.begin();i!=alegereActivitati.end();i++)
            os<<*i<<",";

        for(j=plimbari.begin();j!=plimbari.end();j++)
            os<<" Ora plimbarii este:"<<j->first<<" Durata plimbarii:"<<j->second;
        return os;
    }

};

class client
{
private:
    std::string nume;
    std::string nrTelefon;
    std::string adresa;
    std::string cnp;
public:
    client():nume("a"),nrTelefon("0"),adresa("str"),cnp("o"){}
    client(std::string _nume,std::string _nrTelefon,std::string _adresa,std::string _cnp)
    {
        this->nume=_nume;
        this->nrTelefon=_nrTelefon;
        this->adresa=_adresa;
        this->cnp=_cnp;
    }

    std::istream &citire(std::istream &is)
    {
        std::cout<<"Nume:";
        is>>nume;
        std::cout<<"Telefon:";
        is>>nrTelefon;
        std::cout<<"Adresa:";
        is>>adresa;
        std::cout<<"CNP:";
        is>>cnp;
        return is;
    }

    friend std::istream& operator >>(std::istream &is,client &p)
    {
        p.citire(is);
        return is;
    }

    std::ostream& afisare(std::ostream &os)
    {
        os<<"Nume:"<<nume;
        os<<"Telefon:"<<nrTelefon;
        os<<"Adresa:"<<adresa;
        if(cnp.length()==13) {
            os << "CNP:" << cnp;
        }
        else
        {
            os<<"INVALID";
        }
        return os;
    }

    friend std::ostream& operator <<(std::ostream &os,client &p)
    {
        p.afisare(os);
        return os;
    }



};

class animal
{
private:
    std::string numeA;
    int varsta;
    std::string rasa;
    std::string codUnic;
public:
    animal():numeA("s"),varsta(0),rasa("a"),codUnic("0"){}

    animal(std::string _numeA,int _varsta,std::string _rasa,std::string _codUnic)
    {
        this->numeA=_numeA;
        this->varsta=_varsta;
        this->rasa=_rasa;
        this->codUnic=_codUnic;
    }

    std::istream &citire(std::istream &is)
    {
        std::cout<<"Nume:";
        is>>numeA;
        std::cout<<"Varsta:";
        is>>varsta;
        std::cout<<"Rasa:";
        is>>rasa;
        std::cout<<"Cod unic:";
        is>>codUnic;
        return is;
    }

    friend std::istream& operator >>(std::istream &is,animal &p)
    {
        p.citire(is);
        return is;
    }

    std::ostream& afisare(std::ostream &os)
    {
        os<<"Nume:"<<numeA;
        os<<"Varsta:"<<varsta;
        os<<"Rasa:"<<rasa;
        os << "Cod unic:" << codUnic;
        return os;
    }

    friend std::ostream& operator <<(std::ostream &os,animal &p)
    {
        p.afisare(os);
        return os;
    }


};

//Proiectul 2-Tudor Nicu Cornel
//Incepere preluare sursa


class Interfata {
private:
    static Interfata* instance;
    Interfata()=default;
    std::vector<std::shared_ptr<PachetClasic>> p;

public:
    ~Interfata() = default;

    static Interfata* getInstance();

    void meniu()
    {
        std::cout<<"\n\tMENIU\tALEGETI O OPTIUNE:\n";
        std::cout<<"1. Adaugare Formular\n";
        std::cout<<"2. Afisare Formular\n";
        std::cout<<"0. Iesire\n";
    }

    void addPachet() {
        int nrFormulare;
        std::cout<<"Introduceti numarul de formulare pe care doriti sa le cititi:";std::cin >> nrFormulare;
        for (int i = 0; i < nrFormulare; i++) {
            int option, c = 0;
            std::shared_ptr<PachetClasic> produs;
            while (c == 0) {
                std::cout<<"1-Pachet Clasic\n";
                std::cout<<"2-Pachet Confort\n";
                std::cout<<"3-Pachet Sportiv\n";
                std::cout<<"4-Pachet VIP\n";
                std::cout<<"Tipul Pachetului dorit:";
                std::cin>>option;
                c=1;
                switch (option) {
                    case 1: {
                        produs= std::make_shared<PachetClasic>();
                        break;
                    }
                    case 2: {
                        produs= std::make_shared<PachetConfort>();
                        break;
                    }
                    case 3: {
                        produs= std::make_shared<PachetSportiv>();
                        break;
                    }
                    case 4: {
                        produs= std::make_shared<PachetVIP>();
                        break;
                    }
                    default:
                        std::cout << "error";
                        break;
                }
                produs->citire(std::cin);
                p.push_back(produs);
            }
        }
    }

    void afisare()
    {
        for(auto &p1 : p)
        {
            p1->afisare(std::cout);
            std::cout<<std::endl;
        }
    }
};

Interfata* Interfata::instance=nullptr;

Interfata *Interfata::getInstance() {

    if(instance==nullptr){
        instance=new Interfata();
    }
    return instance;
}

void run()
{
    int option=0;
    Interfata *Interfata= Interfata::getInstance();
    do{
        Interfata->meniu();
        std::cout<<"Introduceti numarul optiunii:";
        std::cin>>option;

        switch (option) {
            case 1:{
                Interfata->addPachet();
                break;}
            case 2:{
                std::cout<<std::endl;
                Interfata->afisare();
                break;
            }
            case 0:{
                std::cout<<"Iesire din aplicatie..\n";
                break;}
            default:{
                std::cout<<"error";
                break;
            }
        }
    }while(option!=0);
}

//final preluare sursa proiect 2-Tudor Nicu Cornel

int main() {
    run();
    return 0;
}
