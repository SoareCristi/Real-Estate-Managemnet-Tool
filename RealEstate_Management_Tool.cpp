#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

class Contract{

protected:

    int m_nrContract, m_anulSemnarii;
    double m_valoareProdus;
    string m_beneficiar, m_furnizor;

public:

    //Constructori
    Contract(): m_nrContract(-1), m_anulSemnarii(-1), m_valoareProdus(-1), m_beneficiar(""), m_furnizor(""){}

    Contract(int nr, int an, double valoare, string beneficiar, string furnizor):
        m_nrContract(nr),
        m_anulSemnarii(an),
        m_valoareProdus(valoare),
        m_beneficiar(beneficiar),
        m_furnizor(furnizor){}

    //Constructor de copiere
    Contract(Contract &c):
        m_nrContract(c.m_nrContract),
        m_anulSemnarii(c.m_anulSemnarii),
        m_valoareProdus(c.m_valoareProdus),
        m_beneficiar(c.m_beneficiar),
        m_furnizor(c.m_furnizor){}

    //Destructor
    virtual ~Contract(){}

    //Operatori >> <<
    friend istream& operator>> (istream& in, Contract& c);

    friend ostream& operator<< (ostream& out, Contract& c);

    Contract& operator= (Contract& c){
        m_nrContract = c.m_nrContract;
        m_anulSemnarii = c.m_anulSemnarii;
        m_valoareProdus = c.m_valoareProdus;
        m_beneficiar = c.m_beneficiar;
        m_furnizor = c.m_furnizor;

        return *this;
    }

    //Metode
    virtual double ValoareTotalaContract() const{
        return m_valoareProdus;
    }

    int GetNr()const {return m_nrContract;}

    int GetAn()const {return m_anulSemnarii;}

    virtual void Citire() = 0;

    virtual void Afisare() = 0;

    void ReinnoireContract(int an){m_anulSemnarii = an;}

};

istream& operator>> (istream& in, Contract& c)
{
    cout << "Nr. de contract: ";
    in >> c.m_nrContract;

    cout << "Anul semnarii contractului: ";
    in >> c.m_anulSemnarii;

    cout << "Valoarea contractului: ";
    in >> c.m_valoareProdus;

    in.ignore();
    cout << "Beneficiarul contractului: ";
    getline(in, c.m_beneficiar);

    cout << "Furnizorul serviciilor: ";
    getline(in, c.m_furnizor);

    return in;
}

ostream& operator<< (ostream& out, Contract& c)
{
    out << "Nr. contract: " << c.m_nrContract << "\nAnul semnarii: " << c.m_anulSemnarii << "\nValoare: " << c.m_valoareProdus;
    out << "\nBeneficiar: " << c.m_beneficiar << "\nFurnizor: " << c.m_furnizor << endl;

    return out;
}



class ContractInchiriere: public Contract{
protected:

    int m_perioada;

public:

    //Constructori
    ContractInchiriere(): m_perioada(0){}

    ContractInchiriere(int nr, int an, double valoare, string beneficiar, string furnizor, int perioada):
        Contract(nr, an, valoare, beneficiar, furnizor),
        m_perioada(perioada){}

    //Constructor de copiere
    ContractInchiriere(ContractInchiriere& i):
        Contract(i),
        m_perioada(i.m_perioada){}

    //Destructor
    ~ContractInchiriere(){}

    //Operatori
    friend istream& operator>> (istream& in, ContractInchiriere& i);

    friend ostream& operator<< (ostream& out, ContractInchiriere& i);

    ContractInchiriere& operator= (ContractInchiriere& i){
        m_nrContract = i.m_nrContract;
        m_anulSemnarii = i.m_anulSemnarii;
        m_valoareProdus = i.m_valoareProdus;
        m_beneficiar = i.m_beneficiar;
        m_furnizor = i.m_furnizor;
        m_perioada = i.m_perioada;

        return *this;
    }

    //Metode
    double ValoareTotalaContract() const{
        return m_valoareProdus * m_perioada;
    }

    int GetPerioada() const{return m_perioada;}

    void Citire() = 0;

    void Afisare() = 0;

};

istream& operator>> (istream& in, ContractInchiriere& i)
{
    in >> dynamic_cast<Contract&>(i);

    cout << "Perioada contractului(nr. luni): ";
    i.m_perioada = 0;
    while (i.m_perioada < 1){
        try{
            in >> i.m_perioada;
            if (i.m_perioada < 1)
                throw (i.m_perioada);
        }
        catch(int perioada){
            cout << "\nNu poti introduce un nr. luni mai mic decat 1!\nIntroduceti iar perioada contractului(nr. luni): ";
        }
    }

    return in;
}

ostream& operator<< (ostream& out, ContractInchiriere& i)
{
    out << dynamic_cast<Contract&>(i);
    out << "Perioada: " << i.m_perioada << " luni.\n";

    return out;
}



class ContractApartament: public Contract{
protected:

    int m_nrCamere, m_nrBai;

public:

    //Constructori
    ContractApartament(): m_nrCamere(0), m_nrBai(0){}

    ContractApartament(int nr, int an, double valoare, string beneficiar, string furnizor, int nrCamere, int nrBai):
        Contract(nr, an, valoare, beneficiar, furnizor),
        m_nrCamere(nrCamere),
        m_nrBai(nrBai){}

    //Constructor de copiere
    ContractApartament(ContractApartament& a):
        Contract(a),
        m_nrCamere(a.m_nrCamere),
        m_nrBai(a.m_nrBai){}

    //Destructor
    ~ContractApartament(){}

    //Operatori
    friend istream& operator>> (istream& in, ContractApartament& a);

    friend ostream& operator<< (ostream& out, ContractApartament& a);

    ContractApartament& operator= (ContractApartament& a){
        m_nrContract = a.m_nrContract;
        m_anulSemnarii = a.m_anulSemnarii;
        m_valoareProdus = a.m_valoareProdus;
        m_beneficiar = a.m_beneficiar;
        m_furnizor = a.m_furnizor;
        m_nrCamere = a.m_nrCamere;
        m_nrBai = a.m_nrBai;

        return *this;
    }

    void Citire(){
        cin >> *this;
        cout << "\nA fost citit un ContractApartament!\n\n";
    }

    void Afisare(){
        cout << *this;
        cout << "\nA fost afisat un ContractApartament!\n\n";
    }
};

istream& operator>> (istream& in, ContractApartament& a)
{
    in >> dynamic_cast<Contract&>(a);

    cout << "Nr. camere: ";
    a.m_nrCamere = 0;
    while (a.m_nrCamere < 1){
        try{
            in >> a.m_nrCamere;
            if (a.m_nrCamere < 1)
                throw (a.m_nrCamere);
        }
        catch (int nrCamere){
            cout << "\nNu poti introduce un imobil cu mai putin de o camera!\nIntroduceti iar nr. camere: ";
        }
    }

    cout << "Nr. bai: ";
    a.m_nrBai = 0;
    while (a.m_nrBai < 1){
        try{
            in >> a.m_nrBai;
            if (a.m_nrBai < 1)
                throw (a.m_nrBai);
        }
        catch (int nrBai){
            cout << "\nNu poti introduce un imobil cu mai putin de o baie!\nIntroduceti iar nr. bai: ";
        }
    }

    return in;
}

ostream& operator<< (ostream& out, ContractApartament& a)
{
    out << dynamic_cast<Contract&>(a) << "Nr. camere: " << a.m_nrCamere << "\nNr. bai: " << a.m_nrBai << endl;

    return out;
}



class ContractInchiriereApartament: public ContractInchiriere{
protected:

    int m_nrCamere, m_nrBai;

public:

    //Constructori
    ContractInchiriereApartament(){}

    ContractInchiriereApartament(int nr, int an, double valoare, string beneficiar, string furnizor, int perioada, int nrCamere, int nrBai):
        ContractInchiriere(nr, an, valoare, beneficiar, furnizor, perioada),
        m_nrCamere(nrCamere),
        m_nrBai(nrBai){}


    //Constructor de copiere
    ContractInchiriereApartament(ContractInchiriereApartament& ia):
        ContractInchiriere(ia),
        m_nrCamere(ia.m_nrCamere),
        m_nrBai(ia.m_nrBai){}

    friend istream& operator>> (istream& in, ContractInchiriereApartament& ia);

    friend ostream& operator<< (ostream& out, ContractInchiriereApartament& ia);

    ContractInchiriereApartament& operator= (ContractInchiriereApartament& ia){
        m_nrContract = ia.m_nrContract;
        m_anulSemnarii = ia.m_anulSemnarii;
        m_valoareProdus = ia.m_valoareProdus;
        m_beneficiar = ia.m_beneficiar;
        m_furnizor = ia.m_furnizor;
        m_perioada = ia.m_perioada;
        m_nrCamere = ia.m_nrCamere;
        m_nrBai = ia.m_nrBai;

        return *this;
    }

    //Metode

    void Citire(){
        cin >> *this;
        cout << "\nA fost citit un ContractInchiriereApartament!\n\n";
    }

    void Afisare(){
        cout << *this;
        cout << "\nA fost afisat un ContractInchiriereApartament!\n\n";
    }
};

istream& operator>> (istream& in, ContractInchiriereApartament& ia)
{
    in >> dynamic_cast<ContractInchiriere&>(ia);

    cout << "Nr. camere: ";
    ia.m_nrCamere = 0;
    while (ia.m_nrCamere < 1){
        try{
            in >> ia.m_nrCamere;
            if (ia.m_nrCamere < 1)
                throw (ia.m_nrCamere);
        }
        catch (int nrCamere){
            cout << "\nNu poti introduce un imobil cu mai putin de o camera!\nIntroduceti iar nr. camere: ";
        }
    }

    cout << "Nr. bai: ";
    ia.m_nrBai = 0;
    while (ia.m_nrBai < 1){
        try{
            in >> ia.m_nrBai;
            if (ia.m_nrBai < 1)
                throw (ia.m_nrBai);
        }
        catch (int nrBai){
            cout << "\nNu poti introduce un imobil cu mai putin de o baie!\nIntroduceti iar nr. bai: ";
        }
    }

    return in;
}

ostream& operator<< (ostream& out, ContractInchiriereApartament& ia)
{
    out << dynamic_cast<ContractInchiriere&>(ia) << "Nr. camere: " << ia.m_nrCamere << "\nNr. bai: " << ia.m_nrBai << endl;

    return out;
}



class ContractVila: public ContractApartament{

    int m_nrEtaje;

public:

    //Constructori
    ContractVila(): m_nrEtaje(0){}

    ContractVila(int nr, int an, double valoare, string beneficiar, string furnizor, int nrCamere, int nrBai, int nrEtaje):
        ContractApartament(nr, an, valoare, beneficiar, furnizor, nrCamere, nrBai),
        m_nrEtaje(nrEtaje){}

    //Constructor de copiere
    ContractVila(ContractVila& v):
        ContractApartament(v),
        m_nrEtaje(v.m_nrEtaje){}

    //Destructor
    ~ContractVila(){}

    //Operatori
    friend istream& operator>> (istream& in, ContractVila& v);

    friend ostream& operator<< (ostream& out, ContractVila& v);

    ContractVila& operator= (ContractVila& v){
        m_nrContract = v.m_nrContract;
        m_anulSemnarii = v.m_anulSemnarii;
        m_valoareProdus = v.m_valoareProdus;
        m_beneficiar = v.m_beneficiar;
        m_furnizor = v.m_furnizor;
        m_nrCamere = v.m_nrCamere;
        m_nrBai = v.m_nrBai;
        m_nrEtaje = v.m_nrEtaje;

        return *this;
    }

    //Metode

    void Citire(){
        cin >> *this;
        cout << "\nA fost citit un ContractVila!\n\n";
    }

    void Afisare(){
        cout << *this;
        cout << "\nA fost afisat un ContractVila!\n\n";
    }
};

istream& operator>> (istream& in, ContractVila& v)
{
    in >> dynamic_cast<ContractApartament&>(v);
    cout << "Nr. etaje: ";
    v.m_nrEtaje = 0;
    while (v.m_nrEtaje < 1){
        try{
            in >> v.m_nrEtaje;
            if (v.m_nrEtaje < 1)
                throw (v.m_nrEtaje);
        }
        catch (int nrEtaje){
            cout << "\nVila nu poate avea niciun etaj!\nIntroduceti iar nr. etaje: ";
        }
    }

    return in;
}

ostream& operator<< (ostream& out, ContractVila& v)
{
    out << dynamic_cast<ContractApartament&>(v) << "Nr. etaje: " << v.m_nrEtaje << endl;

    return out;
}



class ContractInchiriereVila: public ContractInchiriereApartament{

    int m_nrEtaje;

public:

    //Constructori
    ContractInchiriereVila(): m_nrEtaje(0){}

    ContractInchiriereVila(int nr, int an, double valoare, string beneficiar, string furnizor, int perioada, int nrCamere, int nrBai, int nrEtaje):
        ContractInchiriereApartament(nr, an, valoare, beneficiar, furnizor, perioada, nrCamere, nrBai),
        m_nrEtaje(nrEtaje){}

    //Constructor de copiere
    ContractInchiriereVila(ContractInchiriereVila& iv):
        ContractInchiriereApartament(iv),
        m_nrEtaje(iv.m_nrEtaje){}

    //Destructor
    ~ContractInchiriereVila(){}

    //Operatori

    friend istream& operator>> (istream& in, ContractInchiriereVila& iv);

    friend ostream& operator<< (ostream& out, ContractInchiriereVila& iv);

    ContractInchiriereApartament& operator= (const ContractInchiriereVila& iv){
        m_nrContract = iv.m_nrContract;
        m_anulSemnarii = iv.m_anulSemnarii;
        m_valoareProdus = iv.m_valoareProdus;
        m_beneficiar = iv.m_beneficiar;
        m_furnizor = iv.m_furnizor;
        m_perioada = iv.m_perioada;
        m_nrCamere = iv.m_nrCamere;
        m_nrBai = iv.m_nrBai;
        m_nrEtaje = iv.m_nrEtaje;

        return *this;
    }

    //Metode

    void Citire(){
        cin >> *this;
        cout << "\nA fost citit un ContractInchiriereVila!\n\n";
    }

    void Afisare(){
        cout << *this;
        cout << "\nA fost afisat un ContractInchiriereVila!\n\n";
    }
};

istream& operator>> (istream& in, ContractInchiriereVila& iv)
{
    in >> dynamic_cast<ContractInchiriereApartament&>(iv);
    cout << "Nr. etaje: ";
    iv.m_nrEtaje = 0;
    while (iv.m_nrEtaje < 1){
        try{
            in >> iv.m_nrEtaje;
            if (iv.m_nrEtaje < 1)
                throw (iv.m_nrEtaje);
        }
        catch (int nrEtaje){
            cout << "\nVila nu poate avea niciun etaj!\nIntroduceti iar nr. etaje: ";
        }
    }

    return in;
}

ostream& operator<< (ostream& out, ContractInchiriereVila& iv)
{
    out << dynamic_cast<ContractInchiriereApartament&>(iv) << "Nr. etaje: " << iv.m_nrEtaje << endl;

    return out;
}


template<class T> class Agentie;
template<class T> istream& operator>> (istream& in, Agentie<T>& a);
template<class T> ostream& operator<< (ostream& out, Agentie<T>& a);

template<class T>
class Agentie{

    static int s_nrAgentii;

    int m_nrContracte;
    vector< pair<T*, bool> > m_dosar;

public:

    //Constructori
    Agentie(): m_nrContracte(0){
        m_dosar.resize(0);
        s_nrAgentii ++;
    }

    Agentie(vector< pair<T*, bool> > dosar, int nrContracte):
        m_nrContracte(nrContracte){
        m_dosar.resize(nrContracte);
        for (int i = 0; i < nrContracte; i ++){
            m_dosar[i].first = new T(*dosar[i].first);
            m_dosar[i].second = dosar[i].second;
        }
        s_nrAgentii ++;
    }

    //Constructor de copiere
    Agentie(Agentie& a): m_nrContracte(a.m_nrContracte){
        m_dosar.resize(a.m_nrContracte);
        for (int i = 0; i < a.m_nrContracte; i ++){
            m_dosar[i].first = new T(*a.m_dosar[i].first);
            m_dosar[i].second = a.m_dosar[i].second;
        }
        s_nrAgentii ++;
    }

    //Destructor
    ~Agentie(){
        for (int i = 0; i < m_nrContracte; i ++)
            delete m_dosar[i].first;
        m_nrContracte = 0;
        m_dosar.clear();
        s_nrAgentii --;
    }

    //Operatori
    friend istream& operator>> <>(istream& in, Agentie& a);

    friend ostream& operator<< <>(ostream& out, Agentie& a);

    //Metode
    void ReinnoireContract (int i, int an){
            m_dosar[i].first->ReinnoireContract(an);
            m_dosar[i].second = true;
    }

    static int GetNrAgentii(){return s_nrAgentii;}
};

template<class T>
int Agentie<T>::s_nrAgentii = 0;

template<class T>
istream& operator>> (istream& in, Agentie<T>& a)
{
    int optiune = 0;
    cout << "Introduceti numarul de contracte pe care le gestioneaza agentia: ";
    in >> a.m_nrContracte;
    a.m_dosar.resize(a.m_nrContracte);

    cout << "\nIntroduceti cele " << a.m_nrContracte << " contracte:\n\n";
    for (int i = 0; i < a.m_nrContracte; i ++){
        optiune = 0;
        cout << "Alegeti tipul de contract:\n";
        cout << "1. Contract de vanzare apartament\n2. Contract de vanzare vila\n3. Contract inchiriere apartament\n4. Contract inchiriere vila\n";
        while (optiune != 1 && optiune != 2 && optiune != 3 && optiune != 4){
            try{
                in >> optiune;
                if (optiune != 1 && optiune != 2 && optiune != 3 && optiune != 4)
                    throw 0;
            }
            catch (int){
                cout << "Optiune invalida!\nAlegeti iar tipul de contract: ";
            }
        }
        if (optiune == 1){
            a.m_dosar[i].first = new ContractApartament;
            a.m_dosar[i].first->Citire();
            a.m_dosar[i].second = false;
        }
        else if (optiune == 2){
            a.m_dosar[i].first = new ContractVila;
            a.m_dosar[i].first->Citire();
            a.m_dosar[i].second = false;
        }
        else if (optiune == 3){
            a.m_dosar[i].first = new ContractInchiriereApartament;
            a.m_dosar[i].first->Citire();
            a.m_dosar[i].second = false;
        }
        else if (optiune == 4){
            a.m_dosar[i].first = new ContractInchiriereVila;
            a.m_dosar[i].first->Citire();
            a.m_dosar[i].second = false;
        }
    }

    return in;
}

template<class T>
ostream& operator<< (ostream& out, Agentie<T>& a)
{
    out << "Cele " << a.m_nrContracte << " contracte gestionate de agentie sunt:\n\n";
    for (int i = 0; i < a.m_nrContracte; i ++)
        a.m_dosar[i].first->Afisare();
    out << endl;

    return out;
}



template<> class Agentie<ContractInchiriere>;
template<> istream& operator>> (istream& in, Agentie<ContractInchiriere>& a);
template<> ostream& operator<< (ostream& out, Agentie<ContractInchiriere>& a);

template<>
class Agentie<ContractInchiriere>{

    static int s_nrAgentii;
    static const bool ok = true;
    int m_nrContracte, m_nrContracteReinnoite;
    vector<ContractInchiriere*> m_dosar;
    vector<ContractInchiriere*> m_dosarReinnoite;

public:

    //Constructori
    Agentie(): m_nrContracte(0), m_nrContracteReinnoite(0){
        m_dosar.resize(0);
        m_dosarReinnoite.resize(0);
        s_nrAgentii ++;
    }

    //Destructor
    ~Agentie(){
        for (int i = 0; i < m_nrContracte; i ++)
            delete m_dosar[i];
        for (int i = 0; i < m_nrContracteReinnoite; i ++)
            delete m_dosarReinnoite[i];
        m_nrContracte = 0;
        m_nrContracteReinnoite = 0;
        m_dosar.clear();
        m_dosarReinnoite.clear();
        s_nrAgentii --;
    }

    //Operatori
    friend istream& operator>> <>(istream& in, Agentie& a);

    friend ostream& operator<< <>(ostream& out, Agentie& a);

    Agentie<ContractInchiriere>& operator -=(ContractInchiriere& a){
        ContractInchiriereApartament* aux1 = dynamic_cast<ContractInchiriereApartament*>(&a);
        ContractInchiriereVila* aux2 = dynamic_cast<ContractInchiriereVila*>(&a);

        for (int i = 0; i < m_nrContracte; i ++){
            if (m_dosar[i]->GetNr() == a.GetNr()){
                for (int j = i; j < m_nrContracte - 1; j ++)
                    m_dosar[j] = m_dosar[j+1];

                m_nrContracte--;

                if (aux1 != NULL){
                    ContractInchiriereApartament* aux11 = new ContractInchiriereApartament;
                    *aux11 = *aux1;
                    m_nrContracteReinnoite ++;
                    m_dosarReinnoite.push_back(dynamic_cast<ContractInchiriere*>(aux11));
                }
                if (aux2 != NULL){
                    ContractInchiriereVila* aux22 = new ContractInchiriereVila;
                    *aux22 = *aux2;
                    m_nrContracteReinnoite ++;
                    m_dosarReinnoite[m_nrContracteReinnoite] = dynamic_cast<ContractInchiriere*>(aux22);
                }
                break;
            }
        }
    }


    //Metode
    static int GetNrAgentii() {return s_nrAgentii;}

};

template<>
int Agentie<ContractInchiriere>::s_nrAgentii = 0;

template<>
istream& operator>> (istream& in, Agentie<ContractInchiriere>& a)
{
    int optiune = 0;
    cout << "Introduceti numarul de contracte pe care le gestioneaza agentia specializata: ";
    in >> a.m_nrContracte;
    a.m_dosar.resize(a.m_nrContracte);

    cout << "\nIntroduceti cele " << a.m_nrContracte << " contracte:\n\n";
    for (int i = 0; i < a.m_nrContracte; i ++){
        optiune = 0;
        cout << "Alegeti tipul de contract:\n";
        cout << "1. Contract inchiriere apartament\n2. Contract inchiriere vila\n";
        while (optiune != 1 && optiune != 2){
            try{
                in >> optiune;
                if (optiune != 1 && optiune != 2)
                    throw 0;
            }
            catch (int){
                cout << "Optiune invalida!\nAlegeti iar tipul de contract: ";
            }
        }
        if (optiune == 1){
            a.m_dosar[i] = new ContractInchiriereApartament;
            a.m_dosar[i]->Citire();
        }
        else if (optiune == 2){
            a.m_dosar[i] = new ContractInchiriereVila;
            a.m_dosar[i]->Citire();
        }
    }

    a.m_nrContracteReinnoite = 0;

    return in;
}

template<>
ostream& operator<< (ostream& out, Agentie<ContractInchiriere>& a)
{
    out << "Cele " << a.m_nrContracte << " contracte care NU au fost reinnoite gestionate de agentie sunt:\n\n";
    for (int i = 0; i < a.m_nrContracte; i ++)
        a.m_dosar[i]->Afisare();
    out << endl;

    out << "Cele " << a.m_nrContracteReinnoite << " contracte care AU fost reinnoite gestionate de agentie sunt:\n\n";
    for (int i = 0; i < a.m_nrContracteReinnoite; i ++)
        a.m_dosarReinnoite[i]->Afisare();
    out << endl;

    return out;
}

void demo()
{
    Agentie<Contract> a;
    cin >> a;
    cout << endl << endl << a;
}

int main()
{
    demo();

    return 0;
}
