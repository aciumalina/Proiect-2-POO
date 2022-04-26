#include <iostream>
#include <string>
using namespace std;

class Persoana
{
protected:
    string nume;
    string prenume;
    string email;
    string cnp;

public:
    Persoana();                                                                 //constructorul fara parametri
    Persoana(string nume, string prenume, string email, string cnp);            //constructor cu toti parametri
    Persoana(const Persoana &p);                                                //copy-constructor
    Persoana& operator = (const Persoana &p);                                   //supraincarcare atribuire
    ~Persoana();                                                                //destructor
    friend istream& operator << (istream& in, Persoana& p);
    friend ostream& operator >> (ostream& out, const Persoana& p);
    virtual void afisareGen() = 0;                                              //metoda care face clasa abstracta

    virtual istream& citire(istream& in)                            //citirea
    {
        cout << "Introduceti numele"<<endl;
        in >> this->nume;
        cout << "Introduceti prenumele" << endl;
        in >> this->prenume;
        cout << "Introduceti adresa de email" << endl;
        in >> this->email;
        cout << "Introduceti CNP-ul " << endl;
        in >> this->cnp;

        return in;
    }
    virtual ostream& afisare(ostream& out) const                    //afisarea
    {
        out << "Numele este " << this->nume << endl;
        out << "Prenumele este " << this->prenume << endl;
        out << "Adresa de email este " << this->email << endl;
        out << "CNP-ul este " << this->cnp << endl;

        return out;
    }

};

Persoana::Persoana() {
    this->nume = "Anonim";
    this->prenume = "Anonim";
    this->email = "Necunoscut";
    this->cnp = "Necunoscut";
}

Persoana::Persoana(string nume, string prenume, string email, string cnp) {
    this->nume = nume;
    this->prenume = prenume;
    this->email = email;
    this->cnp = cnp;
}

Persoana::Persoana(const Persoana &p) {
    this->nume = p.nume;
    this->prenume = p.prenume;
    this->email = p.email;
    this->cnp = p.cnp;
}

Persoana& Persoana::operator = (const Persoana &p)
{
    if(this!= &p)
    {
        this->nume = p.nume;
        this->prenume = p.prenume;
        this->email = p.email;
        this->cnp = p.cnp;
    }
    return *this;
}

Persoana::~Persoana() {
    this->nume = "Invalid";
    this->prenume = "Invalid";
    this->email = "Invalid";
    this->cnp = "Invalid";
}

istream& operator << (istream& in, Persoana& p)
{
    return p.citire(in);
}

ostream& operator >> (ostream& out, const Persoana& p)
{
    return p.afisare(out);
}

class Pacient: public virtual Persoana
{
protected:
    int varsta;
    bool asigurare;

public:
    Pacient();                                                  //constructor fara parametri
    Pacient(string nume, string prenume, string email, string cnp, int varsta, bool asigurare);             //constructor cu toti parametri
    Pacient(const Pacient& pac);                                                            //copy-constructor
    Pacient& operator = (const Pacient &pac);                                           //supraincarcare =
    void afisareGen();                                                              //una dintre functionalitatile clasei
    void filtrareVarsta(int v1, int v2);                                                          //a doua functionalitate a clasei care filtreaza pacientii dupa varsta

    virtual istream& citire(istream& in)
    {
        Persoana::citire(in);
        cout << "Introduceti varsta pacientului " << endl;
        in >> this-> varsta;
        cout << "Precizati daca pacientul este asigurat[1/0] " << endl;
        in >> this->asigurare;

        return in;
    }

    virtual ostream& afisare(ostream& out) const
    {
        Persoana::afisare(out);
        out << "Varsta pacientului este " << this->varsta << endl;
        if(!this->asigurare) out << "Pacientul nu are asigurare " << endl;
        else out << "Pacientul are asigurare " << endl;

        return out;
    }

    ~Pacient();


};

Pacient::~Pacient()
{
    Persoana::~Persoana();
    this->asigurare = false;
    this->varsta = 0;
}

Pacient::Pacient():Persoana() {
    this->varsta = 0;
    this->asigurare = false;
}

Pacient::Pacient(string nume, string prenume, string email, string cnp, int varsta, bool asigurare): Persoana(nume, prenume, email, cnp)
{
    this->varsta = varsta;
    this->asigurare = asigurare;
}

Pacient::Pacient(const Pacient &pac): Persoana(pac) {
    this->varsta = pac.varsta;
    this->asigurare = pac.asigurare;
}

Pacient& Pacient::operator=(const Pacient &pac) {
    if(this != &pac)
    {
        Persoana::operator=(pac);
        this->varsta = pac.varsta;
        this->asigurare = pac.asigurare;
    }
    return *this;
}

void Pacient::afisareGen() {
    char cifra = (this->cnp)[0];
    int c = cifra - '0';
    if(c % 2 == 0) cout << "Pacientul " << this->nume << " " << this->prenume << " este de gen Feminin" << endl;
    else cout << "Pacientul " << this->nume << " " << this->prenume << " este de gen Masculin" << endl;
}

void Pacient::filtrareVarsta(int v1, int v2) {
    if (this->varsta >= v1 && this->varsta <= v2)
        cout << this->nume << " " <<this->prenume <<endl;
}

class Doctor: public virtual Persoana
{
protected:
    float rating;
    string specializare;

public:
    Doctor();
    Doctor(string nume, string prenume, string email, string cnp, float rating, string specializare);
    Doctor(const Doctor& d);
    Doctor& operator = (const Doctor& d);
    void afisareGen();                                                          //prima functionalitate a clasei
    ~Doctor();

    void filtruDoctor(string specializare, float rating);                       //ilustrare functionalitate clasa Doctor (cautare doctori dupa specializare, avand peste un anumit rating)


    virtual istream& citire(istream& in)
    {
        Persoana::citire(in);
        cout << "Introduceti rating-ul " << endl;
        in >> this->rating;
        cout << "Introduceti specializarea " << endl;
        in >> this->specializare;

        return in;
    }

    virtual ostream& afisare(ostream& out) const
    {
        Persoana::afisare(out);
        out << "Salariul este " << this->rating << endl;
        out << "Specializarea este " << this->specializare << endl;

        return out;
    }

};

Doctor::Doctor():Persoana()
{
    this->rating = 0;
    this->specializare = "Necunoscut";
}

Doctor::Doctor(string nume, string prenume, string email, string cnp, float rating, string specializare):Persoana(nume, prenume, email, cnp)
{
    this->rating = rating;
    this->specializare = specializare;
}

Doctor::Doctor(const Doctor& d):Persoana(d)
{
    this->rating = d.rating;
    this->specializare = d.specializare;
}

Doctor& Doctor::operator=(const Doctor &d) {
    if(this != &d)
    {
        Persoana::operator=(d);
        this->rating = d.rating;
        this->specializare = d.specializare;
    }

    return *this;
}

Doctor::~Doctor()
{
    Persoana::~Persoana();
    this->specializare = "Invalid";
    this->rating = 0;
}

void Doctor::afisareGen() {
    char cifra = (this->cnp)[0];
    int c = cifra - '0';
    if(c % 2 == 0) cout << "Doctorul este de gen Feminin" << endl;
    else cout << "Doctorul este de gen Masculin" << endl;
}

void Doctor::filtruDoctor(string specializare, float rating)
{
    if (this->specializare == specializare && this->rating >= rating)
    {
        cout<<nume<<" "<<prenume<<endl;
    }
}

class Ceva: public virtual Doctor, public virtual Pacient
{
private:
    float discount;
public:
    Ceva():Pacient(), Doctor(), Persoana()
    {
        this->discount = 0;
    }
};


class Serviciu
{
    string serviciu_oferit;                                 //analize, consultatie, interpretare analize, investigatii, control, ecografie etc
    int tarifTotal;
    float reducere;

public:
    Serviciu()                                                         //constructor fara parametri
    {
        serviciu_oferit = "";
        tarifTotal = 0;
        reducere = 0;
    }

    Serviciu(const string& serviciu_oferit, double tarif, float reducere)          //constructor cu toti parametri
    {
        this->serviciu_oferit = serviciu_oferit;
        if (reducere == 0)
            this->tarifTotal = tarif;
        else this->tarifTotal = reducere * tarif;
        this->reducere = reducere;
    }

    ~Serviciu()                                                             //destructor
    {
        serviciu_oferit = "";
        tarifTotal = 0;
        reducere = 0;
    }

    Serviciu(const Serviciu& s)                                            //copy-constructor
    {
        this->serviciu_oferit = s.serviciu_oferit;
        this->tarifTotal = s.tarifTotal;
        this->reducere = s.reducere;
    }

    Serviciu& operator = (const Serviciu& serv)                                //supraincarcarea operatorului = pentru Serviciu
    {
        if(this != &serv)
        {
            this->serviciu_oferit = serv.serviciu_oferit;
            this->tarifTotal = serv.tarifTotal;
            this->reducere = serv.reducere;

        }
        return *this;
    }

    friend ostream& operator << (ostream& out, const Serviciu& serv)                 //afisare
    {
        out<<"Serviciul oferit este " <<serv.serviciu_oferit<<endl;
        out<<"Tariful serviciului este " <<serv.tarifTotal<<endl;
        out<< "Reducerea serviciul este de " << serv.reducere<<endl;
        return out;
    }

    friend istream& operator >> (istream& in, Serviciu& serv)                        //citire
    {
        cout << "Serviciul oferit este: "<<endl;
        in>>serv.serviciu_oferit;
        cout << "Tariful serviciului este de: "<<endl;
        in >> serv.tarifTotal;
        cout << "Reducerea acordata este de: "<<endl;
        in >>serv.reducere;

        if (serv.reducere == 0) serv.tarifTotal = serv.tarifTotal;
        else serv.tarifTotal = serv.tarifTotal * (1-serv.reducere);
        return in;
    }

    void impartireTarif()                                                    //functionalitate a clasei, din tariful total calculeaza si afiseaza TVA si pretul brut
    {
        cout<<"TVA-ul serviciului oferit este " << (this->tarifTotal * 9)/100 << " RON"<<endl;
        cout << "Tariful brut al serviciului este " << (this->tarifTotal * 91)/100 << " RON"<< endl;
    }
};



int main()
{
    //Persoana p, p2;
    Pacient p3, p4;
    //Doctor d;
    Serviciu s;
    cin >> s;
    s.impartireTarif();
    //p3.afisareGen();
    //d.afisare(cout);
    //cin << p3;
//    p3.citire(cin);
//    p3.afisare(cout);
    return 0;
}