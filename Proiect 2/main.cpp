#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

enum SongType {
    Vinyl ,
    CD
};

enum MusicPlayer {
    VinylPlayer ,
    CdPlayer
};

class Product
{
protected:
    double price;
    string name;
public:
    virtual ~Product() = default;

    Product():price(0),name("a"){}

    Product(double price, const string &name) : price(price), name(name) {}


    virtual istream& citire(istream& is) {
        cout << "Price:";
        is>>price;
        cout << "Name:";
        is.get();
        getline(is, name);
        return is;
    }

   friend istream& operator>>(istream& is, Product &p) {
        p.citire(is);
        return is;
    }

    virtual ostream& afisare(ostream &os)
    {
        os<<"Price:"<<price<<" Name:"<<name;
        return os;
    }

    friend ostream& operator <<(ostream& os, Product& p)
    {
        p.afisare(os);
        return os;
    }

};


class Song:public Product
{
private:
    string title;
    string author;
    int length;
    SongType type;
public:
    ~Song()=default;

    Song():title("a"),author("b"),length(0),type(SongType::CD){}

    Song(double price,string name,const string &title, const string &author, int length, SongType type) :Product(price,name), title(title), author(author),
                                                                                 length(length), type(type) {}

    istream& citire(istream &is) override
    {
        Product::citire(is);
        cout<<"Title:";
        getline(is,title);
        cout<<"Author:";
        getline(is,author);
        cout<<"Length(seconds):";
        is>>length;
        cout<<"SongType(1-CD,0-Vinyl):";
        int s;
        is>>s;
        if(s==0)
            type= SongType::Vinyl;
        else
            type= SongType::CD;
        return is;
    }

     ostream& afisare(ostream &os){
        Product::afisare(os);
        os<<" Title:"<<title<<" Author:"<<author<<" Lenght:"<<length;
        os<<" SongType:";
        if(type==0)
            os<<"Vinyl";
        else
            os<<"CD";
        return os;
    }

    const string &getTitle() const {
        return title;
    }

    const string &getAuthor() const {
        return author;
    }


    SongType getType() const {
        return type;
    }

};


class Player: public Product
{
private:
    string title;
    string singer;
    MusicPlayer type;

public:
    ~Player() override =default;

    Player():title("a"),singer("b"),type(MusicPlayer::CdPlayer){}

    Player(double price ,string name,string title,string singer,MusicPlayer type):Product(price,name),title(title),singer(singer),type(type){}

    istream& citire(istream &is) override
    {
        Product::citire(is);
        cout<<"Title:";
        getline(is,title);
        cout<<"Singer:";
        getline(is,singer);
        cout<<"MusicPlayer(1-CdPlayer,0-VinylPlayer):";
        int mp;
        is>>mp;
        if(mp==1)
            type=MusicPlayer::CdPlayer;
        else
            type=MusicPlayer::VinylPlayer;
        return is;
    }

    ostream &afisare(ostream &os) override
    {
        Product::afisare(os);
        os<<" Title:"<<title<<" Singer:"<<singer<<" MusicPlayer:";
        if(type==0)
            os<<"VinylPlayer";
        else
            os<<"CDPlayer";
        return os;
    }

    const string &getTitle() const {
        return title;
    }

    MusicPlayer getType() const {
        return type;
    }

};

class Sticker:public Product
{
private:
    string text;
public:
    ~Sticker() override =default;

    Sticker():text("a"){}

    Sticker(double price,string name,string text):Product(price,name),text(text){}

    istream &citire(istream& is)
    {
        Product::citire(is);
        cout<<"sticker:";
        getline(is,text);
        return is;
    }

    ostream &afisare(ostream& os)
    {
        Product::afisare(os);
        os<<" sticker:"<<text;
        return os;
    }

    const string &getText() const {
        return text;
    }

};


class MusicStore: public error_code {
private:
    static MusicStore* instance;
    MusicStore()=default;
    vector<shared_ptr<Product>> p;
    vector<Product *> product;
public:
     ~MusicStore() = default;

     static MusicStore* getInstance();

     void meniu()
     {
         cout<<"\n\tMENIU\tALEGETI O OPTIUNE:\n";
         cout<<"1. Citire Produse\n";
         cout<<"2. Afisare Produse\n";
         cout<<"3. Compatibilitati\n";
         cout<<"0. Iesire\n";
     }

    void addProduct() {
         int nrProduse;
         cout<<"Introduceti numarul de produse pe care doriti sa le cititi:";cin >> nrProduse;
         for (int i = 0; i < nrProduse; i++) {
             int option, c = 0;
             shared_ptr<Product> produs;
             while (c == 0) {
                 cout<<"1-Product\n";
                 cout<<"2-Song\n";
                 cout<<"3-Player\n";
                 cout<<"4-Sticker\n";
                 cout<<"Tipul produsului dorit:";
                 cin>>option;
                 c=1;
                 switch (option) {
                     case 1: {
                         produs= make_shared<Product>();
                         break;
                     }
                     case 2: {
                         produs= make_shared<Song>();
                         break;
                     }
                     case 3: {
                         produs= make_shared<Player>();
                         break;
                     }
                     case 4: {
                         produs= make_shared<Sticker>();
                         break;
                     }
                     default:
                         cout << "error";
                         break;
                 }
                 produs->citire(cin);
                 p.push_back(produs);
             }
         }
     }

     void afisare()
     {
        for(auto &p1 : p)
        {
                p1->afisare(cout);
                cout<<endl;
        }
     }

    void compatibleSong(const Song &a,const Song &b)
    {
        if(a.getAuthor()==b.getAuthor())
            cout<<"The songs are compatible\n";
        else
            cout<<"error";
    }

    void compatibleSongPlayer(const Song &a, const Player &b)
    {
        if (a.getType() == SongType::Vinyl && b.getType() == MusicPlayer::VinylPlayer) {
            cout << "The song and the player are compatible\n";
        } else if (a.getType() == SongType::CD && b.getType() == MusicPlayer::CdPlayer)
            cout << "The song and the player are compatible\n";
        else
            cout << "error";
    }

    void compatibleStickerSong(const Song &a, const Sticker &b)
    {
         if(a.getTitle().find(b.getText())!=string::npos)
             cout<<"The sticker and the song are compatible\n";
         else
             cout<<"error";
    }

    void compatibleStickerPlayer(const Sticker &a, const Player &b)
    {
         if(b.getTitle().find(a.getText())!=string::npos)
             cout<<"The sticker and the player are compatible\n";
         else
             cout<<"error";
    }

};

MusicStore* MusicStore::instance=nullptr;

MusicStore *MusicStore::getInstance() {

        if(instance==nullptr){
            instance=new MusicStore();
        }
        return instance;
}

void run()
{
    int option=0;
    MusicStore *MusicStore= MusicStore::getInstance();
    do{
        MusicStore->meniu();
        cout<<"Introduceti numarul optiunii:";
        cin>>option;

        switch (option) {
            case 1:{
                MusicStore->addProduct();
                break;}
            case 2:{
                cout<<endl;
                MusicStore->afisare();
                break;
            }
            case 3:
            {
                int conditie;
                cout<<"1. compatibleSong\n";
                cout<<"2. compatibleSongPlayer\n";
                cout<<"3. compatibleStickerSong\n";
                cout<<"4. compatibleStickerPlayer\n";
                cout<<"5. Iesire in meniul principal\n";
                cout<<"Introduceti numarul optiunii:";
                cin>>conditie;
                switch (conditie) {
                    case 1: {
                        Song c1, c2;
                        cout << "Song 1:\n";
                        cin >> c1;
                        cout << "Song 2:\n";
                        cin >> c2;
                        MusicStore->compatibleSong(c1, c2);
                        break;
                    }
                    case 2: {
                        Song c1;
                        cout << "Song:\n";cin >> c1;
                        Player c2;
                        cout << "Player:\n";cin >> c2;
                        MusicStore->compatibleSongPlayer(c1, c2);
                        break;
                    }
                    case 3: {
                        Song c1;
                        Sticker c2;
                        cout << "Song\n";cin >> c1;
                        cout << "Sticker:\n";cin >> c2;
                        MusicStore->compatibleStickerSong(c1, c2);
                        break;
                    }
                    case 4: {
                        Sticker c1;
                        Player c2;
                        cout << "Sticker:\n";cin >> c1;
                        cout << "Player:\n";cin >> c2;
                        MusicStore->compatibleStickerPlayer(c1, c2);
                        break;
                    }
                    case 5:{
                        cout<<"Iesire din meniu compatibilitati...\n";
                        break;
                    }
                    default:
                        cout<<"error";
                        break;
                }
                break;
            }
            case 0:{
                cout<<"Iesire din aplicatie..\n";
                break;}
            default:{
                cout<<"error";
                break;
            }
        }
    }while(option!=0);
}

int main() {
    run();
    return 0;
}
