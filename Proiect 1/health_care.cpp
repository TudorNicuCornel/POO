#include <iostream>
#include <fstream>

float computePrice(int varsta , bool fidelitate , int valabilitate , bool pensionar)
{
    float price = 0,reducere = 0;

    if(valabilitate == 1)
        price = 300;

    if(valabilitate == 3)
        price = 790.99;

    if (valabilitate == 12) {
        price = 2900;
    }

    if(varsta > 16 && varsta <= 25)
    {
        reducere = 10;
        if(fidelitate == 1)
            reducere = 20;
    }

    if(varsta <= 16 && fidelitate == 0)

        reducere = 100;
    else
    {
        if(varsta <= 16)
        {
            reducere = 15;
            if(fidelitate)
                reducere = 25;
        }
    }

    if(varsta > 25 && varsta <= 50)
    {
        reducere = 5;
            if(fidelitate)
                reducere = 15;
    }

    if(pensionar)
    {
        reducere = 35;
            if(fidelitate)
                reducere = 45;
    }

    price= price- ( (price * reducere ) / 100);

    return price;
}

class HealthPackage
{

private:
    int varsta{};
    bool fidelitate{};
    int valabilitate{};
    bool pensionar{};
    float price{};
public:
    HealthPackage() = default;

    bool operator==(const HealthPackage &rhs) const {
        return varsta == rhs.varsta &&
               fidelitate == rhs.fidelitate &&
               valabilitate == rhs.valabilitate &&
               pensionar == rhs.pensionar &&
               price == rhs.price;
    }

    HealthPackage& operator=(const HealthPackage &a)
    {
        if(&a == this)
            return *this;
        this->varsta = a.varsta;
        this->fidelitate = a.fidelitate;
        this->valabilitate = a.valabilitate;
        this->pensionar = a.pensionar;
        this->price = a.price;
        return *this;
    }

    virtual ~HealthPackage() = default;

    HealthPackage(const HealthPackage &x)
    {
        varsta = x.varsta;
        fidelitate = x.fidelitate;
        valabilitate = x.valabilitate;
        pensionar = x.pensionar;
        price = x.price;
    }

    HealthPackage(int varsta,bool fidelitate,int valabilitate,bool pensionar){
        this->varsta = varsta;
        this->fidelitate = fidelitate;
        this->valabilitate = valabilitate;
        this->pensionar = pensionar;
        this->price = computePrice(varsta,fidelitate,valabilitate,pensionar);
    };

    friend std::ostream &operator<<(std::ostream &os, const HealthPackage &aPackage) {
        os.setf(std::ios::boolalpha);

        os << "varsta: " << aPackage.varsta << " fidelitate: " << aPackage.fidelitate << " valabilitate: "
           << aPackage.valabilitate << " pensionar: " << aPackage.pensionar <<" pret: "<<aPackage.price;
        return os;
    }

    friend std::istream &operator>>(std::istream &is,  HealthPackage &aPackage) {
        is.setf(std::ios::boolalpha);

        std::cout<<" varsta: ";
        is >> aPackage.varsta;
        std::cout<<"fidelitate: ";
        is >>aPackage.fidelitate;
        std::cout<<"valabilitate: ";
        is >>aPackage.valabilitate ;
        std::cout<<"pensionar: ";
        is >>aPackage.pensionar;
        aPackage.price = computePrice(aPackage.varsta,aPackage.fidelitate,aPackage.valabilitate,aPackage.pensionar);
        return is;
    }

    float getPrice() const
    {
        return price;
    }

    __attribute__((unused)) void setgetPrice(float yprice) {
        HealthPackage::price = yprice;
    }

    __attribute__((unused))int getVarsta() const {
        return varsta;
    }

    __attribute__((unused)) void setVarsta(int yvarsta) {
        HealthPackage::varsta = yvarsta;
    }

    __attribute__((unused))bool isFidelitate() const {
        return fidelitate;
    }

    __attribute__((unused))void setFidelitate(bool yfidelitate) {
        HealthPackage::fidelitate = yfidelitate;
    }

    __attribute__((unused)) int getValabilitate() const {
        return valabilitate;
    }

    __attribute__((unused))void setValabilitate(int yvalabilitate) {
        HealthPackage::valabilitate = yvalabilitate;
    }

    __attribute__((unused))bool isPensionar() const {
        return pensionar;
    }

    __attribute__((unused))void setPensionar(bool ypensionar) {
        HealthPackage::pensionar = ypensionar;
    }

};


int main() {

    HealthPackage empty;

    HealthPackage client(23, true, 3, false);
    HealthPackage happyClient(47, false, 3, false);
    HealthPackage curiousClient(77, false, 12, true);
    HealthPackage clients[] = {client, happyClient, curiousClient};

    std::ofstream f("facturi.txt");

    f.setf(std::ios::boolalpha);

    int i=0;

    for (const HealthPackage& package : clients) {
        i++;
       f << "Detalii Factura " << i << ": " << std::endl
       << "varsta: " << package.getVarsta() << std::endl
       << "fidelitate: " << package.isFidelitate() << std::endl
       << "valabilitate: " << package.getValabilitate() << std::endl
       << "pensionar: " << package.isPensionar() << std::endl
       << "pretul facturii: " << package.getPrice() << std::endl << std::endl; // va afisa 632.792 751.4405 1885

    }

    std::cin >> empty;
    std::cout << empty;

    i++;

    f << "Detalii Factura " << i<< ": " << std::endl
      << "varsta: " << empty.getVarsta() << std::endl
      << "fidelitate: " << empty.isFidelitate() << std::endl
      << "valabilitate: " << empty.getValabilitate() << std::endl
      << "pensionar: " << empty.isPensionar() << std::endl
      << "Pretul facturii: " << empty.getPrice() << std::endl << std::endl;

    return 0;
}
