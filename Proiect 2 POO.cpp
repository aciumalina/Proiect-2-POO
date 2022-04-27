#include <iostream>
#include <string>
#include <typeinfo>
#include <stdlib.h>
using namespace std;

class Persoana
{
protected:
    string nume;
    string prenume;
    string cnp;
    int cod;

public:
    Persoana();                                                                 //constructorul fara parametri
    Persoana(string nume, string prenume, string cnp, int cod);            //constructor cu toti parametri
    Persoana(const Persoana &p);                                                //copy-constructor
    Persoana& operator = (const Persoana &p);                                   //supraincarcare atribuire
    virtual ~Persoana();                                                                //destructor
    friend istream& operator << (istream& in, Persoana& p);
    friend ostream& operator >> (ostream& out, const Persoana& p);
    virtual void afisareGen() = 0;                                              //metoda care face clasa abstracta

    virtual istream& citire(istream& in)                            //citirea
    {
        cout << "Introduceti numele"<<endl;
        in >> this->nume;
        cout << "Introduceti prenumele" << endl;
        in >> this->prenume;
        cout << "Introduceti CNP-ul " << endl;
        in >> this->cnp;
        cout << "Introduceti codul unic " << endl;
        in >> this->cod;

        return in;
    }

    virtual ostream& afisare(ostream& out) const                    //afisarea
    {
        out << "Numele este " << this->nume << endl;
        out << "Prenumele este " << this->prenume << endl;
        out << "CNP-ul este " << this->cnp << endl;

        return out;
    }

    string getNume() {return this->nume;}                       //getter pt nume
    int getCod() {return this->cod;}
    void setNume(string nume) {this->nume = nume;}              //setter pt nume
};

Persoana::Persoana() {
    this->nume = "Anonim";
    this->prenume = "Anonim";
    this->cnp = "Necunoscut";
    this->cod = 0;
}

Persoana::Persoana(string nume, string prenume, string cnp, int cod) {
    this->nume = nume;
    this->prenume = prenume;
    this->cnp = cnp;
    this->cod = cod;
}

Persoana::Persoana(const Persoana &p) {
    this->nume = p.nume;
    this->prenume = p.prenume;
    this->cnp = p.cnp;
    this->cod = p.cod;
}

Persoana& Persoana::operator = (const Persoana &p)
{
    if(this!= &p)
    {
        this->nume = p.nume;
        this->prenume = p.prenume;
        this->cnp = p.cnp;
        this->cod = p.cod;
    }
    return *this;
}

Persoana::~Persoana() {
    this->nume = "Anonim";
    this->prenume = "Invalid";
    this->cnp = "Invalid";
    this->cod = 0;
    cout<<"pers"<<endl;
}

istream& operator << (istream& in, Persoana& p)
{
    return p.citire(in);
}

ostream& operator >> (ostream& out, const Persoana& p)
{
    return p.afisare(out);
}

class Pacient: virtual public Persoana
{
protected:
    int varsta;
    bool asigurare;

public:
    Pacient();                                                  //constructor fara parametri
    Pacient(string nume, string prenume, string cnp, int cod, int varsta, bool asigurare);             //constructor cu toti parametri
    Pacient(const Pacient& pac);                                                            //copy-constructor
    Pacient& operator = (const Pacient &pac);                                           //supraincarcare =
    virtual ~Pacient();
    void afisareGen();                                                              //una dintre functionalitatile clasei
    void filtrareVarsta(int v1, int v2) const;                                                          //a doua functionalitate a clasei care filtreaza pacientii dupa varsta

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
};

Pacient::~Pacient()
{
    this->asigurare = false;
    this->varsta = 0;
    cout<<"pac"<<endl;
}

Pacient::Pacient():Persoana() {
    this->varsta = 0;
    this->asigurare = false;
}

Pacient::Pacient(string nume, string prenume, string cnp, int cod, int varsta, bool asigurare): Persoana(nume, prenume, cnp,cod)
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

void Pacient::filtrareVarsta(int v1, int v2) const {
    if (this->varsta >= v1 && this->varsta <= v2)
        cout << this->nume << " " <<this->prenume <<endl;
}

class Doctor: virtual public Persoana
{
protected:
    float rating;
    string specializare;
    int anulAngajarii;

public:
    Doctor();
    Doctor(string nume, string prenume, string cnp, int cod, float rating, string specializare, int anulAngajarii);
    Doctor(const Doctor& d);
    Doctor& operator = (const Doctor& d);
    void afisareGen();                                                                 //prima functionalitate a clasei
    virtual ~Doctor();

    void filtruDoctor(string specializare, float rating) const;                       //ilustrare functionalitate clasa Doctor (cautare doctori dupa specializare, avand peste un anumit rating)


    virtual istream& citire(istream& in)
    {
        Persoana::citire(in);
        cout << "Introduceti rating-ul " << endl;
        in >> this->rating;
        cout << "Introduceti specializarea " << endl;
        in >> this->specializare;
        cout << "Introduceti anul angajarii" << endl;
        in >> this->anulAngajarii;

        return in;
    }

    virtual ostream& afisare(ostream& out) const
    {
        Persoana::afisare(out);
        out << "Rating-ul este " << this->rating << endl;
        out << "Specializarea este " << this->specializare << endl;
        out << "Anul angajarii este " << this->anulAngajarii << endl;

        return out;
    }

};

Doctor::Doctor():Persoana()
{
    this->rating = 0;
    this->specializare = "Necunoscut";
    this->anulAngajarii = 0;
}

Doctor::Doctor(string nume, string prenume, string cnp,int cod, float rating, string specializare, int anulAngajarii):Persoana(nume, prenume, cnp, cod)
{
    this->rating = rating;
    this->specializare = specializare;
    this->anulAngajarii = anulAngajarii;
}

Doctor::Doctor(const Doctor& d):Persoana(d)
{
    this->rating = d.rating;
    this->specializare = d.specializare;
    this->anulAngajarii = d.anulAngajarii;
}

Doctor& Doctor::operator=(const Doctor &d) {

    if(this != &d)
    {
        Persoana::operator=(d);
        this->rating = d.rating;
        this->specializare = d.specializare;
        this->anulAngajarii = d.anulAngajarii;
    }

    return *this;
}

Doctor::~Doctor()
{
    this->specializare = "Invalid";
    this->rating = 0;
    this->anulAngajarii = 0;
    cout<<"doc"<<endl;
}

void Doctor::afisareGen() {
    char cifra = (this->cnp)[0];
    int c = cifra - '0';
    if(c % 2 == 0) cout << "Doctorul este de gen Feminin" << endl;
    else cout << "Doctorul este de gen Masculin" << endl;
}

void Doctor::filtruDoctor(string specializare, float rating) const
{
    if (this->specializare == specializare && this->rating >= rating)
    {
        cout<<nume<<" "<<prenume<<endl;
    }
}

class PacientSiDoctor: public virtual Doctor, public virtual Pacient
{
private:
    int discount;

public:
    PacientSiDoctor():Pacient(), Doctor(), Persoana()                       //constructor fara parametri
    {
        this->discount = 0;
    }

    //constructor cu toti parametri
    PacientSiDoctor(const string &nume, const string &prenume, const string &cnp, int varsta, bool asigurare, float rating, const string &specializare, int anulAngajarii, int discount):Persoana(nume, prenume, cnp, cod), Pacient(nume, prenume, cnp, cod, varsta, asigurare), Doctor(nume, prenume, cnp, cod, rating, specializare, anulAngajarii)
    {
        this->discount = discount;
    }

    PacientSiDoctor(const PacientSiDoctor& pd):Persoana(pd), Pacient(pd), Doctor(pd)                //copy-constructor
    {
        this->discount = pd.discount;
    }

    PacientSiDoctor& operator = (const PacientSiDoctor& pd)                                     //operator =
    {
        if(this != &pd)
        {
            Pacient::operator = (pd);
            this->rating = pd.rating;
            this->specializare = pd.specializare;
            this->discount = pd.discount;
        }
        return *this;
    }

    ~PacientSiDoctor()
    {
        this->discount = 0;
        cout<<"hibrid"<<endl;
    }


    virtual istream& citire(istream& in)
    {
        (dynamic_cast < Pacient* > (this))->Pacient::citire(in);
        cout << "Introduceti rating-ul " << endl;
        in >> this->rating;
        cout << "Introduceti specializarea " << endl;
        in >> this->specializare;
        cout << "Introduceti anul angajarii " <<endl;
        in >> this->anulAngajarii;
        cout << "Introduceti discount-ul aditional pentru servicii " <<endl;
        in >> this->discount;

        return in;
    }

    virtual ostream& afisare(ostream& out) const
    {
        (dynamic_cast < const Pacient* > (this))->Pacient::afisare(out);
        out << "Rating-ul este " << this->rating << endl;
        out << "Specializarea este " << this->specializare << endl;
        out << "Anul angajarii este " << this->anulAngajarii << endl;
        out << "Discount-ul aditional pentru servicii este de " << this->discount << "%" <<endl;

        return out;
    }

    void afisareGen(){
        char cifra = (this->cnp)[0];
        int c = cifra - '0';
        if(c % 2 == 0) cout << "Persoana este de gen Feminin" << endl;
        else cout << "Persoana este de gen Masculin" << endl;
    }

    void calculReducereExtra() const                              //functionalitate clasa, calculeaza in functie de anii de vechime daca doctorii pot beneficia de alte reduceri la serviciile spitalului
    {
        time_t t = time(nullptr);
        tm* now = localtime(&t);
        int aniLucru = (now->tm_year + 1900) - this->anulAngajarii;
        if(aniLucru <= 3) cout << "Doctorul nu are suficienti ani de vechime pentru a beneficia de un discount aditional " << endl;
        else if (aniLucru <= 7) cout << "In calitate de pacient, doctorul " << this->nume << " " <<this->prenume <<" va beneficia de un discount extra de 20% la serviciile oferite" << endl;
        else cout << "In calitate de pacient, doctorul " << this->nume << " " <<this->prenume <<" va beneficia de un discount extra de 35% la serviciile oferite" << endl;
    }
};


class Serviciu
{
    string serviciu_oferit;                                 //analize, consultatie, interpretare analize, investigatii, control, ecografie etc
    int tarifTotal;
    float reducere;
    int cod;

public:
    Serviciu()                                                         //constructor fara parametri
    {
        serviciu_oferit = "";
        tarifTotal = 0;
        reducere = 0;
        cod = 0;
    }

    Serviciu(const string& serviciu_oferit, int tarif, float reducere)          //constructor cu toti parametri
    {
        this->serviciu_oferit = serviciu_oferit;
        if (reducere == 0)
            this->tarifTotal = tarif;
        else this->tarifTotal = reducere * tarif;
        this->reducere = reducere;
        this->cod = cod;
    }

    ~Serviciu()                                                             //destructor
    {
        serviciu_oferit = "";
        tarifTotal = 0;
        reducere = 0;
        cod = 0;
    }

    Serviciu(const Serviciu& s)                                            //copy-constructor
    {
        this->serviciu_oferit = s.serviciu_oferit;
        this->tarifTotal = s.tarifTotal;
        this->reducere = s.reducere;
        this->cod = s.cod;
    }

    Serviciu& operator = (const Serviciu& serv)                                //supraincarcarea operatorului = pentru Serviciu
    {
        if(this != &serv)
        {
            this->serviciu_oferit = serv.serviciu_oferit;
            this->tarifTotal = serv.tarifTotal;
            this->reducere = serv.reducere;
            this->cod = serv.cod;

        }
        return *this;
    }

    friend ostream& operator << (ostream& out, const Serviciu& serv)                 //afisare
    {
        out<<"Serviciul oferit este " <<serv.serviciu_oferit<<endl;
        out<<"Tariful serviciului este " <<serv.tarifTotal<<endl;
        out<< "Reducerea serviciul este de " << serv.reducere<<endl;
        out << "Codul este " << serv.cod<<endl;
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
        cout << "Codul unic al serviciului este: "<<endl;
        in >>serv.cod;

        if (serv.reducere == 0) serv.tarifTotal = serv.tarifTotal;
        else serv.tarifTotal = serv.tarifTotal * (1-serv.reducere);
        return in;
    }

    void impartireTarif() const                                                   //functionalitate a clasei, din tariful total calculeaza si afiseaza TVA si pretul brut
    {
        cout<<"TVA-ul serviciului oferit este " << (this->tarifTotal * 9)/100 << " RON"<<endl;
        cout << "Tariful brut al serviciului este " << (this->tarifTotal * 91)/100 << " RON"<< endl;
    }

    int getCod() {return this->cod;}                                        //getter cod
    string getServiciu_oferit(){return serviciu_oferit;}                //getter pt serviciul oferit
    void setServiciu(string serviciu){this->serviciu_oferit = serviciu;}            //setter serviciu oferit
};

void optiuniMeniu()
{
    cout<<endl;
    cout<<"Pentru a introduce informatii noi, alegeti optiunea 1"<<endl;                    //create
    cout<<"Pentru a modifica anumite informatii, alegeti optiunea 2 "<<endl;                         //update
    cout<<"Pentru stergerea de date din sistem, alegeti optiunea 3 "<<endl;                     //delete
    cout<<"Pentru a afisa informatii, alegeti optiunea 4 "<<endl;                               //read
    cout<<"Pentru a filtra doctorii dupa specializare si rating, alegeti optiunea 5 "<<endl;
    cout << "Pentru a filtra pacientii in functie de varsta, alegeti optiunea 6" << endl;
    cout << "Pentru a afisa pretul brut si TVA-ul serviciilor oferite, alegeti optiunea 7" <<endl;
    cout << "Pentru a include un doctor existent in sistemul de pacienti, alegeti optiunea 8" << endl;
    cout << "Alta optiune inchide meniul" << endl;
}

void optiuneaUnu(Doctor*** vec, Pacient* pac[], Serviciu* serv[], int &sizeVec,int &nrVec, int &sizePac, int &nrPac, int &sizeServ, int &nrServ) {
    while (1)
    {
        cout << "Alegeti in ce sectiune doriti sa introduceti informatii(1-Doctor, 2-Pacient, 3-Servicii)"<<endl;
        cout<< "Prin orice alta comanda se revine la meniul principal "<<endl;
        int opt;
        cin >> opt;
        if (opt == 1) {
            if(nrVec + 1 > sizeVec)                             //daca nr de doctori ajunge la limita maxima alocata de sizeVec, voi suplimenta
            {
                auto **tmp = new Doctor*[nrVec + 10];                 //suplimentez cu 10
                for(int i =0; i < nrVec; i++)
                {
                    tmp[i] = (*vec)[i];                             //copiez intr-un temporar
                    //delete vec[i];
                }
                delete[] *vec;
                (*vec) = tmp;                             //vec devine tmp
                sizeVec += 10;

                (*vec)[nrVec] = new Doctor;
                (*vec)[nrVec++]->citire(cin);               //aici citesc noul obiect
                break;
            }

            else{
                int i;
                for(i = 0; i < nrVec; i++)                        //mai intai parcurg pana la nrVec si unde am prima pozitie libera, introduc noul doctor si voi schimba nrVec
                {
                    //vec[i] = new Doctor;
                    if ((*vec)[i] == nullptr)
                    {
                        (*vec)[i] = new Doctor;
                        (*vec)[i]->citire(cin);
                        break;
                    }
                }
                (*vec)[i] = new Doctor;
                if(i == nrVec) {(*vec)[nrVec++]->citire(cin); break;}           //daca ajung la i == nrVec inseamna ca toate pozitiile sunt ocupate, deci voi introduce obiectul pe pozitia nrVec si incrementez nrVec
            }
        }

        else if (opt == 2)
        {
            if(nrPac + 1 > sizePac)                                             //aceiasi pasi ca la extinderea vectorului vec
            {

                auto *tmp2 = new Pacient[nrPac + 10];
                for(int i =0; i < nrPac; i++)
                {
                    tmp2[i] = (*pac)[i];
                }
                delete [] *pac;
                *pac = tmp2;
                sizePac += 10;
                (*pac)[nrPac++].citire(cin);
                break;
            }

            else{
                int i;
                for(i = 0; i < nrPac; i++)                        //mai intai parcurg pana la nrPac si unde am prima pozitie libera, introduc noul pacient si voi schimba nrPac
                {
                    if ((*pac)[i].getNume() == "Anonim")
                    {
                        (*pac)[i].citire(cin);
                        break;
                    }
                }
                if(i == nrPac) {(*pac)[nrPac++].citire(cin); break;}
            }
        }

        else if (opt == 3)                                      //aceiasi pasi ca la extinderea vectorului vec
        {
            if(nrServ + 1 > sizeServ)
            {
                auto *tmp4 = new Serviciu[nrServ + 10];
                for(int i =0; i < nrServ; i++)
                {
                    tmp4[i] = (*serv)[i];
                }
                delete [] *serv;
                *serv = tmp4;
                sizeServ += 10;
                cin>>(*serv)[nrServ++];
                break;
            }

            else{
                int i;
                for(i = 0; i < nrServ; i++)                        //mai intai parcurg pana la nrServ si unde am prima pozitie libera, introduc noul serviciu si voi schimba nrServ
                {
                    if ((*serv)[i].getServiciu_oferit() == "")
                    {
                        cin >> (*serv)[i];
                        break;
                    }
                }
                if(i == nrServ) {cin>>(*serv)[nrServ++]; break;}
            }
        }
        else break;
    }
}

void optiuneaDoi(Doctor* vec[], Pacient pac[], Serviciu serv[], int nrVec, int nrPac,int nrServ) {
    cout<<"Alegeti in ce sectiune doriti sa modificati informatii(1-Doctor, 2-Pacient, 3-Servicii)"<<endl;
    cout<<"Prin orice alta comanda se revine la meniul principal "<<endl;
    int opt;
    cin >> opt;
    while (1){
        if (opt == 1) {
            int id, i;
            cout << "Introduceti codul doctorului ale carui informatii doriti sa le modificati " << endl;
            cin >> id;
            for (i = 0; i < nrVec; i++) {
                if (vec[i]->getCod() == id && vec[i]->getNume() != "Anonim") {
                    vec[i]->citire(cin);                              //modificare presupune reintroducerea obiectului cu cin, nu doar modificarea unei singure variabile
                    break;
                }
            }
            if (i == nrVec) {
                cout << "Nu s-a gasit niciun doctor cu id-ul specificat" << endl;
                break;
            }
            break;
        }
        else if (opt == 2) {
            int cod, i;
            cout << "Introduceti codul pacientului ale carui informatii doriti sa le modificati " << endl;
            cin >> cod;
            for (i = 0; i < nrPac; i++) {
                if (pac[i].getCod() == cod && pac[i].getNume() != "Anonim") {
                    pac[i].citire(cin);                                  //modificare inseamna recitirea cu totul a obiectului respectiv
                    break;
                }
            }
            if (i == nrPac) {
                cout << "Nu s-a gasit niciun pacient cu codul introdus" << endl;
                break;
            }
            break;
        }

        else if (opt == 3) {
            int cod, i;
            cout << "Introduceti codul serviciului ale carui informatii doriti sa le modificati " << endl;
            cin >> cod;
            for (i = 0; i < nrServ; i++) {
                if (serv[i].getCod() == cod && serv[i].getServiciu_oferit() != "") {
                    cin >> serv[i];
                    break;
                }
            }
            if (i == nrServ) {
                cout << "Nu s-a gasit niciun serviciu cu codul introdus " << endl;
                break;
            }
            break;
        }
        else break;
    }
}
void optiuneaTrei(Doctor* vec[], Pacient pac[], Serviciu serv[], int nrVec, int nrPac, int nrServ) {
        cout<<"Alegeti din ce sectiune doriti sa stergeti date(1-Doctor, 2-Pacient, 3-Servicii)"<<endl;
    cout<<"Pentru a reveni la meniul principal, alegeti orice alta optiune"<<endl;
    int opt;
    cin >> opt;
    while (1){
        if (opt == 1) {
            int id, i;
            cout << "Introduceti id-ul doctorului pe care doriti sa il stergeti " << endl;
            cin >> id;
            for (i = 0; i < nrVec; i++) {
                if (vec[i]->getCod() == id && vec[i]->getNume() != "Anonim") {           //verific ca obiectul sa nu fi fost sters deja
                    cout << "Doctorul cu id-ul " << id << " a fost sters" << endl;
                    vec[i]->setNume("Anonim");                                                //prin prenumele setat la "Anonim" indic ca acel doctor nu mai exista
                    break;
                }
            }
            if (i==nrVec) {cout <<"Nu s-a gasit niciun doctor cu codul introdus"<<endl; break;}
            break;

        } else if (opt == 2) {
            int cod, i;
            cout << "Introduceti codul pacientului pe care doriti sa il stergeti " << endl;
            cin >> cod;
            for (i = 0; i < nrPac; i++) {
                if (pac[i].getCod() == cod && pac[i].getNume() != "Anonim") {
                    cout << "Pacientul cu codul " << cod << " a fost sters" << endl;
                    pac[i].setNume("Anonim");          //acelasi lucru ca la doctor, setez prenumele la "Anonim" pentru a sti daca un obiect a devenit inactiv
                    break;
                }
            }
            if (i == nrPac) {cout<<"Nu s-a gasit niciun pacient cu codul introdus"<<endl; break;}
            break;

        }
        else if (opt == 3) {
            int cod, i;
            cout << "Introduceti codul serviciului pe care doriti sa il stergeti " << endl;
            cin >> cod;
            for (i = 0; i < nrServ; i++) {
                if (serv[i].getCod() == cod && serv[i].getServiciu_oferit() != "") {           //verific sa nu fi fost sters deja
                    cout << "Serviciul cu codul " << cod << " a fost sters" << endl;
                    serv[i].setServiciu("");                        //voi seta doar serviciul la "" si cand voi gasi primul obiect cu "" pe post de serviciu, voi sti ca este inactiv
                    break;
                }

            } if (i == nrServ) {cout<<"Nu s-a gasit niciun serviciu cu codul introdus"<<endl; break;}
            break;
        }
        else break;
    }
}
void optiuneaPatru(Doctor* vec[], Pacient pac[], Serviciu serv[], int nrVec, int nrPac,int nrServ)
{
    cout<<"Alegeti din ce sectiune doriti sa afisati date(1-Doctor, 2-Pacient, 3-Servicii)"<<endl;
    cout<<"Pentru a reveni la meniul principal, alegeti orice alta optiune"<<endl;
    int opt;
    cin >> opt;
    while (1){
        if (opt == 1) {
            cout<<"Daca doriti afisarea tuturor doctorilor, alegeti optiunea 1"<<endl;
            cout<<"Pentru afisarea unui singur doctor cunoscut dupa ID, alegeti optiunea 2"<<endl;
            cout<<"Pentru a reveni la meniul principal, alegeti orice alta optiune"<<endl;
            int optiune;
            cin>>optiune;
            if (optiune == 1){
                for(int i = 0; i < nrVec; i++)
                {
                    if(vec[i]->getNume() != "Anonim")                 //prin aceasta verificare doresc sa nu afisez obiectele care inca exista in vector pana la nrVec, dar care au fost sterse anterior
                    {
                        cout<<"INFORMATII DOCTOR"<<endl;
//                       if(typeid(vec[i]) == typeid(PacientSiDoctor))
//                       {dynamic_cast <const PacientSiDoctor*> (&vec[i])->afisare(cout);}
                        vec[i]->afisare(cout)<<endl;
                    }
                }
            }
            else if (optiune == 2){
                cout<<"Introduceti codul doctorului cautat"<<endl;          //voi cauta prin vector dupa cod
                int ID;
                cin>>ID;
                int i;
                for(i=0; i < nrVec; i++)
                {
                    if (vec[i]->getCod() == ID && vec[i]->getNume() != "Anonim")
                    {
                        vec[i]->afisare(cout)<<endl;
                        break;}
                    else if (i == nrVec-1 && vec[i]->getCod() != ID) {cout<<"Nu s-a gasit niciun doctor cu codul specificat"<<endl; break;}
                }

            }
            else{break;}
        }
        else if (opt == 2) {                                                                    //exact aceiasi pasi ca mai sus, in vectorul de Doctori
            cout<<"Daca doriti afisarea tuturor pacientilor, alegeti optiunea 1"<<endl;
            cout<<"Pentru afisarea unui singur pacient cunoscut dupa cod, alegeti optiunea 2"<<endl;
            cout<<"Pentru a iesi, alegeti orice alta optiune "<<endl;
            int optiune;
            cin>>optiune;
            if (optiune == 1){
                for(int i = 0; i<nrPac; i++)
                {
                    if(pac[i].getNume() != "Anonim")
                    {
                        cout<<"INFORMATII PACIENT"<<endl;
                        pac[i].afisare(cout)<<endl;
                    }
                }
            }
            else if (optiune == 2){
                cout<<"Introduceti codul pacientului cautat"<<endl;
                int ID;
                cin>>ID;
                for(int i=0; i<nrPac; i++)
                {
                    if (pac[i].getCod() == ID && pac[i].getNume() != "Anonim")
                    {pac[i].afisare(cout)<<endl;
                        break;}
                    else if (i == nrPac-1 && pac[i].getCod() != ID) {cout<<"Nu s-a gasit niciun pacient cu codul introdus"<<endl; break;}
                }
            }
            else{break;}
        }
        else if (opt == 3) {                                                                //exact aceiasi pasi ca mai sus, in vectorul de Doctori, Pacienti si Programari
            cout<<"Daca doriti afisarea tuturor serviciilor, alegeti optiunea 1"<<endl;
            cout<<"Pentru afisarea unui singur serviciu cunoscut dupa cod, alegeti optiunea 2"<<endl;
            cout<<"Pentru a reveni la meniul principal, alegeti orice alta optiune"<<endl;
            int optiune;
            cin>>optiune;
            if (optiune == 1){
                for(int i = 0; i<nrServ; i++)
                {
                    if(serv[i].getServiciu_oferit() != "")
                    {
                        cout<<"INFORMATII SERVICIU OFERIT"<<endl;
                        cout<<serv[i]<<endl;
                    }
                }
            }
            else if (optiune == 2){
                cout<<"Introduceti codul serviciului cautat"<<endl;
                int nr;
                cin>>nr;
                for(int i=0; i<nrServ; i++)
                {
                    if (serv[i].getCod() == nr && serv[i].getServiciu_oferit() != "")
                    {cout<<serv[i]<<endl;
                        break;
                    }
                    else if (i==nrServ-1 && serv[i].getCod() != nr) {cout <<"Nu s-a gasit niciun serviciu cu codul introdus "<<endl; break;}
                }
            }
            else break;
        }
        else break;
    }
}


int main()
{
    int sizePac = 100;                      //size-urile sunt dimensiunile vectorilor de obiecte
    int sizeServ = 40;
    int sizeVec = 1;

    Doctor **vec = new Doctor*[sizeVec];                //vec este vectorul de Doctori
    for(int i = 0; i < sizeVec; i ++)
    {
        vec[i] = nullptr;
    }
    auto *pac = new Pacient[sizePac];
    auto *serv = new Serviciu[sizeServ];

    int nrVec, nrPac, nrServ;
    cout<<"Specificati cati doctori doriti sa introduceti in sistem: "<<endl;
    cin >> nrVec;
    cout<<"Specificati cati pacienti doriti sa introduceti in sistem: "<<endl;
    cin >> nrPac;
    cout<<"Specificati cate servicii doriti sa introduceti in sistem: "<<endl;
    cin >> nrServ;
    if (nrVec != 0)                                                                                 //verific daca nr de doctori este diferit de 0, ca sa nu afisez mesajul degeaba
    {cout<<"INTRODUCETI DOCTORII PE RAND "<<endl;
        for(int i = 0; i<nrVec; i++)
        {
            cout<<"Informatii doctor"<<endl;
            vec[i] = new Doctor;
            vec[i]->citire(cin);
        }
    }

    if (nrPac != 0)
    {cout<<"INTRODUCETI PACIENTII PE RAND "<<endl;
        for(int i = 0; i<nrPac; i++)
        {
            cout<<"Informatii pacient"<<endl;
            pac[i].citire(cin);
        }
    }

    if (nrServ != 0)
    {cout<<"INTRODUCETI SERVICIILE PE RAND "<<endl;
        for(int i = 0; i<nrServ; i++)
        {
            cout<<"Informatii serviciu"<<endl;
            cin>>serv[i];
        }
    }

    while(1)
    {
        optiuniMeniu();
        int nrOpt;
        cin >> nrOpt;
        if (nrOpt == 1) {optiuneaUnu(&vec,&pac,&serv, sizeVec, nrVec, sizePac, nrPac,sizeServ, nrServ);}
        else if (nrOpt == 2) {optiuneaDoi(vec,pac,serv,nrVec, nrPac,nrServ );}
        else if (nrOpt == 3) {optiuneaTrei(vec,pac,serv,nrVec, nrPac,nrServ );}
        else if (nrOpt == 4) {optiuneaPatru(vec,pac,serv,nrVec, nrPac,nrServ);}
        else if (nrOpt == 5) {
            cout<<"Introduceti specializarea pe care o cautati "<<endl;
            string specializare;
            cin >> specializare;
            cout << "Introduceti rating-ul minim al doctorului "<<endl;
            float rating;
            cin >>rating;
            for(int i = 0; i<nrVec;i++)                         //pentru fiecare doctor voi trece prin functia de filtru pentru a vedea daca se incadreaza
            {
                if(vec[i]->getNume() != "Anonim" ) vec[i]->filtruDoctor(specializare,rating);
            }
        }
        else if (nrOpt == 6) {
            int minim, maxim;
            cout << "Introduceti varsta minima"<<endl;
            cin >> minim;
            cout << "Introduceti varsta maxima" << endl;
            cin >> maxim;
            for(int i = 0; i<nrPac; i++)
            {
                if(pac[i].getNume() != "Anonim") pac[i].filtrareVarsta(minim, maxim);
            }
        }
        else if (nrOpt == 7) {
            int cod;
            cout << "Introduceti codul serviciului pe care il cautati" << endl;
            cin >> cod;
            int i;
            for(i = 0; i<nrServ; i++)
            {
                if(serv[i].getCod() == cod && serv[i].getServiciu_oferit() != "")
                {
                    serv[i].impartireTarif();
                    break;
                }
            }
            if(i == nrServ) cout << "Nu s-a gasit niciun serviciu cu codul introdus"<<endl;

        }

        else if (nrOpt == 8)
        {
            int cod;
            cout << "Introduceti codul doctorului care devine si pacient" << endl;
            cin >> cod;
            int i;
            for(i = 0; i < nrVec; i++)
            {
                if(vec[i]->getCod() == cod && vec[i]->getNume() != "Anonim")
                {
                    //Doctor* d = new PacientSiDoctor;
                    delete vec[i];
                    vec[i] = new PacientSiDoctor;
                    if(vec[i])
                    {
                        vec[i]->citire(cin);
                    }
                    //if (dynamic_cast<PacientSiDoctor*>(&vec[i]) == nullptr) cout << "null";
                    //PacientSiDoctor* pd = dynamic_cast<PacientSiDoctor*>(&vec[i]);
                    //pd->citire(cin);
                    //dynamic_cast<PacientSiDoctor*>(&vec[i])->citire(cin);
                    //vec[i].citire(cin);
                    break;
                }
            }
            if(i == nrVec) cout << "Nu s-a gasit niciun doctor cu codul introdus" << endl;
        }

        else break;
    }

    //Persoana p, p2;
    //Pacient p3, p4;
//    Persoana* p = new Doctor;
//    p->afisare(cout);
//    cout << endl;
//    Doctor* d = dynamic_cast <Doctor*> (p);
//    d->afisare(cout);

//    PacientSiDoctor p;
//    p.citire(cin);
//    p.afisareGen();

    for(int i = 0; i < nrVec; i++)
    {
        delete vec[i];
    }

    delete[] vec;
    delete[] pac;
    delete[] serv;

    return 0;
}