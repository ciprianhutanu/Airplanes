#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <unordered_map>
#include <list>
#include <chrono>
#include <thread>
#include <conio.h>
#include <typeinfo>

template <class A>
void elimElement(std::vector<A>& v, int i) {
	if (v.size() <= 1) {
		v.clear();
		return;
	}
	for (int j = i; j < v.size() - 1; j++) {
		v[j] = v[j + 1];
	}
	v.pop_back();
}


class Avion {
protected:
	std::string model, origine, destinatie;
	static int cont;
	const int numarZbor;
	int timpTraseu, timpDecolare;
	float combustibil;
public:
	Avion();
	Avion(std::string, std::string, std::string, float, int, int);
	Avion(const Avion&);
	Avion& operator=(const Avion&);
	friend std::istream& operator>>(std::istream&, Avion&);
	friend std::ostream& operator<<(std::ostream&, const Avion&);
	bool operator>(const Avion&);
	virtual int valoare(float) = 0;
	float getCombustibil() {
		return this->combustibil;
	}
	int getTimpTraseu() {
		return this->timpTraseu;
	}
	void setCombustibil(float x) {
		this->combustibil = x;
	}
	void setTimpDecolare(int timpDecolare) {
		this->timpDecolare = timpDecolare;
	}
	void consumCombustibil() {
		this->combustibil -= 41.57;
	}
	void scadereTimp() {
		this->timpTraseu--;
	}
};

int Avion::cont = 0;

Avion::Avion() :numarZbor(++cont) {
	this->model = "Nedefinit";
	this->origine = "NED";
	this->destinatie = "NED";
	this->timpDecolare = 0;
	this->timpTraseu = 0;
	this->combustibil = 0;
}

Avion::Avion(std::string model, std::string origine, std::string destinatie, float combustibil, int timpDecolare, int timpTraseu) :numarZbor(++cont) {
	this->model = model;
	this->origine = origine;
	this->destinatie = destinatie;
	this->timpTraseu = timpTraseu;
	this->timpDecolare = timpDecolare;
	this->combustibil = combustibil;
}

Avion::Avion(const Avion& obj) :numarZbor(++cont) {
	this->model = obj.model;
	this->origine = obj.origine;
	this->destinatie = obj.destinatie;
	this->timpTraseu = obj.timpTraseu;
	this->timpDecolare = obj.timpDecolare;
	this->combustibil = obj.combustibil;
}

Avion& Avion::operator=(const Avion& obj) {
	if (this != &obj) {
		this->model = obj.model;
		this->origine = obj.origine;
		this->destinatie = obj.destinatie;
		this->timpTraseu = obj.timpTraseu;
		this->timpDecolare = obj.timpDecolare;
		this->combustibil = obj.combustibil;
	}
	return *(this);
}

std::istream& operator>>(std::istream& in, Avion& obj) {
	std::cout << "Introduceti:\nModel avion: ";
	in >> obj.model;
	obj.origine = "BUC";
	std::cout << "Destinatia: ";
	in >> obj.destinatie;
	do {
		std::cout << "Durata zborului: ";
		in >> obj.timpTraseu;
	} while (obj.timpTraseu <= 0);
	obj.timpDecolare = 0;
	obj.combustibil = obj.timpTraseu * 41.57;
	return in;
}

std::ostream& operator<<(std::ostream& out, const Avion& obj) {
	out << obj.numarZbor << '\t' << obj.model << '\t' << obj.origine << '\t' << obj.destinatie << '\t' << obj.timpDecolare / 60 << ':' << obj.timpDecolare % 60 << '\t' << obj.timpTraseu << '\t' << obj.combustibil << '\t';
	return out;
}

bool Avion::operator>(const Avion& obj) {
	if (this->combustibil > obj.combustibil)
		return true;
	return false;
}

class AvionCalatori :virtual public Avion {
protected:
	int numarCalatori;
public:
	AvionCalatori();
	AvionCalatori(std::string, std::string, std::string, float, int, int, int);
	AvionCalatori(const AvionCalatori&);
	AvionCalatori operator=(const AvionCalatori&);
	friend std::istream& operator>>(std::istream& in, AvionCalatori& obj);
	friend std::ostream& operator<<(std::ostream& out, const AvionCalatori& obj);
	int valoare(float mult) {
		return this->numarCalatori * mult;
	}
	int getNumarCalatori() {
		return this->numarCalatori;
	}
	void setNumarCalatori(int x) {
		this->numarCalatori = x;
	}
};

AvionCalatori::AvionCalatori() {
	this->numarCalatori = 0;
}

AvionCalatori::AvionCalatori(std::string model, std::string origine, std::string destinatie, float combustibil, int timpDecolare, int timpTraseu, int numarCalatori) : Avion(model, origine, destinatie, combustibil, timpDecolare, timpTraseu) {
	this->numarCalatori = numarCalatori;
}

AvionCalatori::AvionCalatori(const AvionCalatori& obj) : Avion(obj) {
	this->numarCalatori = obj.numarCalatori;
}

AvionCalatori AvionCalatori::operator=(const AvionCalatori& obj) {
	if (this != &obj) {
		Avion::operator=(obj);
		this->numarCalatori = obj.numarCalatori;
	}
	return *(this);
}

std::istream& operator>>(std::istream& in, AvionCalatori& obj) {
	in >> (Avion&)obj;
	std::cout << "Numar calatori: ";
	in >> obj.numarCalatori;
	return in;
}

std::ostream& operator<<(std::ostream& out, const AvionCalatori& obj) {
	out << "CAL" << '\t';
	out << (Avion&)obj;
	out << obj.numarCalatori << '\n';
	return out;
}

class AvionMarfa :virtual public Avion {
protected:
	int cantitateMarfa;
public:
	AvionMarfa();
	AvionMarfa(std::string, std::string, std::string, float, int, int, int);
	AvionMarfa(const AvionMarfa&);
	AvionMarfa operator=(const AvionMarfa&);
	friend std::istream& operator>>(std::istream& in, AvionMarfa& obj);
	friend std::ostream& operator<<(std::ostream& out, const AvionMarfa& obj);
	int valoare(float mult) {
		return this->cantitateMarfa * mult;
	}
	int getCantMarfa() {
		return this->cantitateMarfa;
	}
	void setCantMarfa(int x) {
		this->cantitateMarfa = x;
	}
};

AvionMarfa::AvionMarfa() {
	this->cantitateMarfa = 0;
}

AvionMarfa::AvionMarfa(std::string model, std::string origine, std::string destinatie, float combustibil, int timpDecolare, int timpTraseu, int cantitateMarfa) : Avion(model, origine, destinatie, combustibil, timpDecolare, timpTraseu) {
	this->cantitateMarfa = cantitateMarfa;
}

AvionMarfa::AvionMarfa(const AvionMarfa& obj) : Avion(obj) {
	this->cantitateMarfa = obj.cantitateMarfa;
}

AvionMarfa AvionMarfa::operator=(const AvionMarfa& obj) {
	if (this != &obj) {
		Avion::operator=(obj);
		this->cantitateMarfa = obj.cantitateMarfa;
	}
	return *(this);
}

std::istream& operator>>(std::istream& in, AvionMarfa& obj) {
	in >> (Avion&)obj;
	std::cout << "Cantitate marfa: ";
	in >> obj.cantitateMarfa;
	return in;
}

std::ostream& operator<<(std::ostream& out, const AvionMarfa& obj) {
	out << "MAR" << '\t';
	out << (Avion&)obj;
	out << "-\t" << obj.cantitateMarfa << '\n';
	return out;
}

class AvionMilitar :public AvionCalatori, public AvionMarfa {
private:
	std::string organizatieMilitara;
public:
	AvionMilitar();
	AvionMilitar(std::string, std::string, std::string, float, int, int, int, int, std::string);
	AvionMilitar(const AvionMilitar&);
	AvionMilitar operator=(const AvionMilitar&);
	friend std::istream& operator>>(std::istream& in, AvionMilitar& obj);
	friend std::ostream& operator<<(std::ostream& out, const AvionMilitar& obj);
	int valoare(float mult) {
		return mult * (this->numarCalatori + this->cantitateMarfa);
	}
};

AvionMilitar::AvionMilitar() {
	this->organizatieMilitara = "NEDEFINIT";
}

AvionMilitar::AvionMilitar(std::string model, std::string origine, std::string destinatie, float combustibil, int timpDecolare, int timpTraseu, int numarCalatori, int cantitateMarfa, std::string organizatieMilitara) :
	Avion(model, origine, destinatie, combustibil, timpDecolare, timpTraseu),
	AvionCalatori(model, origine, destinatie, combustibil, timpDecolare, timpTraseu, numarCalatori),
	AvionMarfa(model, origine, destinatie, combustibil, timpDecolare, timpTraseu, cantitateMarfa) {
	this->organizatieMilitara = organizatieMilitara;
}

AvionMilitar::AvionMilitar(const AvionMilitar& obj) :Avion(obj), AvionCalatori(obj), AvionMarfa(obj) {
	this->organizatieMilitara = obj.organizatieMilitara;
}

AvionMilitar AvionMilitar::operator=(const AvionMilitar& obj) {
	if (this != &obj) {
		AvionCalatori::operator=(obj);
		AvionMarfa::operator=(obj);
		this->organizatieMilitara = obj.organizatieMilitara;
	}
	return *(this);
}

std::istream& operator>>(std::istream& in, AvionMilitar& obj) {
	in >> (Avion&)obj;
	std::cout << "Numar militari: ";
	in >> obj.numarCalatori;
	std::cout << "Cantitate marfa: ";
	in >> obj.cantitateMarfa;
	std::cout << "Denumire organizatie militara: ";
	in >> obj.organizatieMilitara;
	return in;
}

std::ostream& operator<<(std::ostream& out, const AvionMilitar& obj) {
	out << "MIL" << '\t';
	out << (Avion&)obj;
	out << obj.numarCalatori << '\t' << obj.cantitateMarfa << '\t' << obj.organizatieMilitara << '\n';
	return out;
}


class Zbor {
private:
	Avion* avion;
public:
	Zbor() { this->avion = NULL; }
	Zbor(Avion* avion) {
		if (typeid(*avion) == typeid(AvionCalatori))
			this->avion = new AvionCalatori();
		if (typeid(*avion) == typeid(AvionMarfa))
			this->avion = new AvionMarfa();
		if (typeid(*avion) == typeid(AvionMilitar))
			this->avion = new AvionMilitar();
		this->avion = avion;
	}
	Zbor operator=(const Zbor& obj) {
		if (this->avion != NULL) {
			this->avion = NULL;
			delete this->avion;
			this->avion = NULL;
		}
		this->avion = obj.avion;
		return *(this);
	}
	friend std::istream& operator>>(std::istream& in, Zbor& obj) {
		int optiune;
		do {
			std::cout << "1. Avion calatori\n2. Avion marfa\n3. Avion militar\n";
			in >> optiune;
		} while (optiune > 3 or optiune < 1);
		if (optiune == 1) {
			obj.avion = new AvionCalatori();
			in >> dynamic_cast<AvionCalatori&>(*obj.avion);
		}
		if (optiune == 2) {
			obj.avion = new AvionMarfa();
			in >> dynamic_cast<AvionMarfa&>(*obj.avion);
		}
		if (optiune == 3) {
			obj.avion = new AvionMilitar();
			in >> dynamic_cast<AvionMilitar&>(*obj.avion);
		}
		return in;
	}
	friend std::ostream& operator<<(std::ostream& out, const Zbor& obj) {
		if (typeid(*obj.avion) == typeid(AvionCalatori))
			out << dynamic_cast<AvionCalatori&>(*obj.avion);
		if (typeid(*obj.avion) == typeid(AvionMarfa))
			out << dynamic_cast<AvionMarfa&>(*obj.avion);
		if (typeid(*obj.avion) == typeid(AvionMilitar))
			out << dynamic_cast<AvionMilitar&>(*obj.avion);
		return out;
	}
	bool operator>(const Zbor& obj) {
		if (this->avion > obj.avion)
			return true;
		return false;
	}
	Avion* getAvion() const {
		return this->avion;
	}
	~Zbor() {
		if (this->avion != NULL) {
			this->avion = NULL;
			delete this->avion;
		}
	}
};

class Game {
private:
	std::vector<Zbor> listaAvioane;
	std::vector<Zbor> listaAvioaneBonus;
	std::vector<int> timpTerminale;

	const std::vector<std::string> orase = {
		"BUC","SCV","NYC",
		"ROM","LON","LAA",
		"BER","AMS","MAD",
		"LIS","SOF","CLJ",
		"IAS","TOK","MEX",
		"BRA","PRA","WDC",
		"BAK","ATH" };

	const std::unordered_map<std::string, int> listaAeropoarte = {
		{"BUC",0}, {"SCV",57}, {"NYC",602},
		{"ROM",115}, {"LON",186}, {"LAA", 820},
		{"BER",127}, {"AMS",164}, {"MAD",215},
		{"LIS",242}, {"SOF",52}, {"CLJ",54},
		{"IAS",54}, {"TOK",694}, {"MEX",852},
		{"BRA",776}, {"PRA",119}, {"WDC",634},
		{"BAK",179}, {"ATH",85} };

	const std::list<std::string> modeleAvioane = {
		"Boing",
		"Airbus",
		"Douglas",
		"McDonel",
		"Antonov" };

	const std::list<std::string> organizatii = {
		"NATO",
		"OTSC",
		"OSC",
		"ASEAN",
		"LigaAraba",
		"UA",
		"ONU" };

	int numarTerminale, numarCalatori, cantitateMarfa, scor;
	float bani, mult;
public:
	Game() {
		this->numarTerminale = 1;
		this->bani = 0;
		this->bani = 0;
		this->scor = 0;
		this->numarCalatori = 0;
		this->cantitateMarfa = 0;
		this->mult = 1;
		this->timpTerminale.push_back(0);
	}
	Game& operator=(const Game& obj) {
		if (this != &obj) {
			this->listaAvioane.clear();
			if (obj.listaAvioane.size()) {
				for (int i = 0; i < obj.listaAvioane.size(); i++) {
					this->listaAvioane.push_back(obj.listaAvioane[i]);
				}
			}
			this->listaAvioaneBonus.clear();
			if (obj.listaAvioaneBonus.size()) {
				for (int i = 0; i < obj.listaAvioaneBonus.size(); i++) {
					this->listaAvioaneBonus.push_back(obj.listaAvioaneBonus[i]);
				}
			}
			this->timpTerminale.clear();
			if (obj.timpTerminale.size()) {
				for (int i = 0; i < obj.timpTerminale.size(); i++) {
					this->timpTerminale.push_back(obj.timpTerminale[i]);
				}
			}
			this->numarCalatori = obj.numarCalatori;
			this->numarTerminale = obj.numarTerminale;
			this->bani = obj.bani;
			this->mult = obj.mult;
			this->scor = obj.scor;
			this->cantitateMarfa = obj.cantitateMarfa;
		}
		return  *(this);
	}
	friend std::ostream& operator<<(std::ostream& out, const Game obj) {
		out << "Veniri:\nIndex\tCat\tID\tMod\tOrig\tDest\tPle\tDurata\tC\tPas\tM(tone)\tOrg\n";
		for (int i = 0; i < obj.listaAvioane.size(); i++) {
			if (obj.listaAvioane[i].getAvion()->getTimpTraseu() <= 10)
			{
				out << "\033[1;31m";
				out << i << '\t' << obj.listaAvioane[i];
				out << "\033[0m";
			}
			else
				out << i << '\t' << obj.listaAvioane[i];
		}
		out << "\033[1;34m";
		out << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";
		out << "\033[0m";
		out << "Plecari:\nIndex\tCat\tID\tMod\tOrig\tDest\tPle\tDurata\tC\tPas\tM(tone)\tOrg\n";
		for (int i = 0; i < obj.listaAvioaneBonus.size(); i++) {
			out << i << '\t' << obj.listaAvioaneBonus[i];
		}
		out << "\033[1;34m";
		out << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";
		out << "\033[0m";
		for (int i = 1; i <= obj.numarTerminale; i++) {
			out << "T" << i << ": ";
			if (obj.timpTerminale[i - 1] == 0)
				out << "Liber\n";
			else
				out << "Ocupat pentru inca: " << obj.timpTerminale[i - 1] << "m\n";
		}
		out << "\033[1;34m";
		out << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";
		out << "\033[0m";
		out << "Scor: " << obj.scor << '\n';
		out << "Balanta: " << obj.bani << '\n';
		out << "Bonus: " << obj.mult << "x\n";
		out << "Calatori gata de plecare: " << obj.numarCalatori << '\n';
		out << "Marfa pregatita de decolare: " << obj.cantitateMarfa << '\n';
		out << "\033[1;34m";
		out << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";
		out << "\033[0m";
		return out;
	}
	void generareAvion(int timpDecolare) {
		int o, tipAvion, timpTraseu;
		float combustibil;
		std::string origine, destinatie, model;
		Avion* a;
		tipAvion = rand() % 3;
		auto i = this->modeleAvioane.begin();
		std::advance(i, rand() % 5);
		model = *i;
		do {
			o = rand() % 20;
		} while (o == 0);
		origine = this->orase[o];
		destinatie = "BUC";
		timpTraseu = this->listaAeropoarte.find(origine)->second;
		combustibil = timpTraseu * 41.57;
		if (tipAvion == 0) {
			int numarCalatori = rand() % 150 + 50;
			a = new AvionCalatori(model, origine, destinatie, combustibil, timpDecolare, timpTraseu, numarCalatori);
		}
		else if (tipAvion == 1) {
			int cantitateMarfa = rand() % 150 + 50;
			a = new AvionMarfa(model, origine, destinatie, combustibil, timpDecolare, timpTraseu, cantitateMarfa);
		}
		else {
			int cantitateMarfa = rand() % 150 + 50, numarCalatori = rand() % 150 + 50;
			auto organizatie = this->organizatii.begin();
			std::advance(organizatie, rand() % 7);
			std::string orgMilitara = *organizatie;
			a = new AvionMilitar(model, origine, destinatie, combustibil, timpDecolare, timpTraseu, numarCalatori, cantitateMarfa, orgMilitara);
		}
		Zbor zbor(a);
		this->listaAvioane.push_back(zbor);
		a = NULL;
		delete a;
	}

	void aterizareTerminal(int t, int i) {
		int j, cnt = 0;
		for (j = 0; j < this->numarTerminale; j++)
			if (this->timpTerminale[j] != 0)
				cnt++;
		if (cnt == this->numarTerminale)
		{
			std::cout << "Nu sunt terminale libere\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			return;
		}
		if (this->listaAvioane.size() == 0) {
			std::cout << "Nu este programat niciun zbor!\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			return;
		}
		while (t > this->numarTerminale or t < 1 or this->timpTerminale[t - 1] > 0) {
			std::cout << "Terminal invalid! Mai incercati:\nNumar terminal: ";
			std::cin >> t;
		}
		while (i >= this->listaAvioane.size() or i < 0) {
			std::cout << "Zbor inexistent! Mai incercati:\nNumar zbor: ";
			std::cin >> i;
		}
		if (this->listaAvioane[i].getAvion()->getTimpTraseu() > 10) {
			std::cout << "Avionul nu poate ateriza inca!";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			return;
		}
		else {
			this->bani += this->listaAvioane[i].getAvion()->valoare(this->mult);
			elimElement(this->listaAvioane, i);
			this->timpTerminale[t - 1] = 25;
			std::cout << "Avionul va ateriza la terminalul T" << t << '\n';
			this->scor++;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
	void upgradeNumarTerminale() {
		if (this->bani >= 500)
		{
			this->bani -= 500;
			this->numarTerminale++;
			this->timpTerminale.push_back(0);
			std::cout << "Terminal adaugat!";
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		else {
			std::cout << "Fonduri insuficiente!";
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
	void upgradeBonus() {
		if (this->bani >= 300) {
			this->mult += 0.5;
			this->bani -= 300;
			std::cout << "Tranzatie finalizata!";
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		else {
			std::cout << "Fonduri insuficiente!";
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
	void efectulTimpului() {
		int i, k, a = -1;
		k = rand() % 3;
		this->numarCalatori += k;
		k = rand() % 3;
		this->cantitateMarfa += k;
		for (i = 0; i < this->numarTerminale; i++) {
			if (this->timpTerminale[i] > 0)
				this->timpTerminale[i]--;
		}
		for (i = 0; i < this->listaAvioane.size(); i++) {
			if (this->listaAvioane[i].getAvion()->getTimpTraseu() == 1) {
				this->listaAvioane[i].getAvion()->scadereTimp();
				this->listaAvioane[i].getAvion()->setCombustibil(0);
			}
			if (this->listaAvioane[i].getAvion()->getCombustibil() > 0 and this->listaAvioane[i].getAvion()->getTimpTraseu() > 0) {
				this->listaAvioane[i].getAvion()->consumCombustibil();
				this->listaAvioane[i].getAvion()->scadereTimp();
			}
		}
		for (i = 0; i < this->listaAvioaneBonus.size(); i++) {
			if (this->listaAvioaneBonus[i].getAvion()->getCombustibil() > 0 and this->listaAvioaneBonus[i].getAvion()->getTimpTraseu() > 0) {
				this->listaAvioaneBonus[i].getAvion()->consumCombustibil();
				this->listaAvioaneBonus[i].getAvion()->scadereTimp();
			}
		}
		do {
			a = -1;
			for (i = 0; i < this->listaAvioaneBonus.size(); i++) {
				if (this->listaAvioaneBonus[i].getAvion()->getTimpTraseu() == 0) {
					this->listaAvioaneBonus[i].getAvion()->setCombustibil(0);
					this->bani += this->listaAvioaneBonus[i].getAvion()->valoare(this->mult);
					a = i;
				}
			}
			if (this->listaAvioaneBonus.size() >= 1 and a >= 0) {
				elimElement(this->listaAvioaneBonus, a);
			}
		} while (a >= 0 and this->listaAvioaneBonus.size() >= 1);
	}
	void avionBonus(int i) {
		try {
			Zbor z;
			system("CLS");
			std::cout << "\033[1;32m";
			std::cout << "Calatori: " << this->getNumarCalatori() << '\n';
			std::cout << "Marfa: " << this->getCantMarfa() << '\n';
			std::cout << "\033[0m";
			std::cin >> z;
			Avion* a = z.getAvion();
			if (typeid(*a) == typeid(AvionCalatori)) {
				int n = (dynamic_cast<AvionCalatori&>(*a)).getNumarCalatori();
				if (this->numarCalatori == 0)
					throw std::runtime_error("Calatori insuficienti");
				while (n > this->numarCalatori)
				{
					std::cout << "\nPrea multi calatori, mai incercati:\nNumar calatori: ";
					std::cin >> n;
				}
				(dynamic_cast<AvionCalatori&>(*a)).setNumarCalatori(n);
				this->numarCalatori -= n;
			}
			if (typeid(*a) == typeid(AvionMarfa)) {
				int n = (dynamic_cast<AvionMarfa&>(*a)).getCantMarfa();
				if (this->cantitateMarfa == 0)
					throw std::runtime_error("Marfa insuficienta");
				while (n > this->cantitateMarfa)
				{
					std::cout << "\nPrea multa marfa, mai incercati:\nCantitate marfa: ";
					std::cin >> n;
				}
				(dynamic_cast<AvionMarfa&>(*a)).setCantMarfa(n);
				this->cantitateMarfa -= n;
			}
			if (typeid(*a) == typeid(AvionMilitar)) {
				int n = (dynamic_cast<AvionMilitar&>(*a)).getNumarCalatori();
				if (this->numarCalatori == 0)
					throw std::runtime_error("Militari insuficienti");
				while (n > this->numarCalatori)
				{
					std::cout << "\nPrea multi militari, mai incercati:\nNumar militari: ";
					std::cin >> n;
				}
				(dynamic_cast<AvionMilitar&>(*a)).setNumarCalatori(n);
				this->numarCalatori -= n;
				n = (dynamic_cast<AvionMilitar&>(*a)).getCantMarfa();
				if (this->cantitateMarfa == 0)
					throw std::runtime_error("Marfa insuficienta");
				while (n > this->cantitateMarfa)
				{
					std::cout << "\nPrea multa marfa, mai incercati:\nCantitate marfa: ";
					std::cin >> n;
				}
				(dynamic_cast<AvionMilitar&>(*a)).setCantMarfa(n);
				this->cantitateMarfa -= n;
			}
			listaAvioaneBonus.push_back(z);
			std::cout << "\033[1;32m";
			std::cout << "Avionul a decolat!";
			std::cout << "\033[0m";
			std::this_thread::sleep_for(std::chrono::seconds(3));
		}
		catch (const std::runtime_error& error) {
			std::cout << error.what();
			std::this_thread::sleep_for(std::chrono::seconds(3));
		}

	}
	int verificareViata() {
		for (int i = 0; i < this->listaAvioane.size(); i++) {
			if (this->listaAvioane[i].getAvion()->getCombustibil() == 0)
				return i;
		}
		return -1;
	}
	int getScor() {
		return this->scor;
	}
	float getBani() {
		return this->bani;
	}
	int getNumarCalatori() {
		return this->numarCalatori;
	}
	int getCantMarfa() {
		return this->cantitateMarfa;
	}
	void saveGame();
	void loadGame();
};

void Game::saveGame() {
	try {
		std::ofstream saveFile("savefile.dat", std::ios::out | std::ios::binary);
		if (!saveFile) {
			throw 101;
		}
		saveFile.clear();
		saveFile.write((char*)&scor, sizeof(int));
		saveFile.write((char*)&bani, sizeof(float));
		saveFile.write((char*)&numarTerminale, sizeof(int));
		saveFile.write((char*)&numarCalatori, sizeof(int));
		saveFile.write((char*)&cantitateMarfa, sizeof(int));
		saveFile.write((char*)&mult, sizeof(float));
		//int n = (int)listaAvioane.size();
		//saveFile.write((char*)&n, sizeof(int));
		//for (int i = 0; i < listaAvioane.size(); i++)
		//{
			//saveFile.write((char*)&listaAvioane[i], sizeof(Zbor));
		//}
		saveFile.close();
		std::cout << "Progesul a fost salvat";
	}
	catch (int error) {
		std::cout << "Eroare la deschiderea fisierului";
	}
}

void Game::loadGame() {
	try {
		std::ifstream saveFile("savefile.dat", std::ios::out | std::ios::binary);
		if (!saveFile) {
			throw 102;
		}
		saveFile.read((char*)&scor, sizeof(int));
		saveFile.read((char*)&bani, sizeof(float));
		saveFile.read((char*)&numarTerminale, sizeof(int));
		saveFile.read((char*)&numarCalatori, sizeof(int));
		saveFile.read((char*)&cantitateMarfa, sizeof(int));
		saveFile.read((char*)&mult, sizeof(float));
		//int n;
		//saveFile.read((char*)&n, sizeof(int));
		//listaAvioane.resize(n);
		//for (int i = 0; i < n; i++)
		//{
		//	saveFile.read((char*)&listaAvioane[i], sizeof(Zbor));
		//}
		saveFile.close();
	}
	catch (int error) {
		std::cout << "Eroare la citirea din salvare";
	}
}

class Meniu {
	static Meniu* obiect;
	Meniu() = default;
	Meniu(const Meniu&) = default;
	Game g;
public:
	static Meniu* getInstance() {
		if (!obiect)
			obiect = new Meniu();
		return obiect;
	}

	void Joc() {
		int i = 0, k = 50;
		bool running = true;
		while (running) {
			if (_kbhit()) {
				char c = _getch();
				if (c == 'm' or c == 'M') {
					running = !running;
				}
			}
			if (running) {
				system("CLS");
				g.efectulTimpului();
				std::cout << g;
				std::cout << "Apasa tasta 'm' pentru meniu\n";
				std::this_thread::sleep_for(std::chrono::microseconds(200000));
				int x = rand() % k;
				if (x == 0)
					g.generareAvion(i);
				i++;
				if (i % 100 == 0 and k > 10)
					k -= 2;
				int n = g.verificareViata();
				if (n >= 0) {
					std::cout << "\033[1;31m";
					std::cout << "Avionul cu indexul " << n << " s-a prabusit! Joc incheiat...\n";
					std::cout << "\033[0m";
					std::this_thread::sleep_for(std::chrono::seconds(5));
					system("CLS");
					std::cout << "\033[1;32m";
					std::cout << "Scorul obtinut: " << g.getScor();
					std::cout << "\033[0m";
					std::this_thread::sleep_for(std::chrono::seconds(3));
					running = false;
				}
			}
			else {
				while (true) {
					int k;
					system("CLS");
					std::cout << g;
					std::cout << "0. Iesire\n1. Aterizati avion\n2. Magazin\n3. Continuare\n4. Salvare Joc\n";
					std::cin >> k;
					if (k <= 0 or k > 4) {
						running = !running;
						break;
					}
					if (k == 1) {
						int t, i;
						std::cout << "Introduceti numar terminal: ";
						std::cin >> t;
						std::cout << "Introduceti index avion: ";
						std::cin >> i;
						g.aterizareTerminal(t, i);
					}
					while (true and k == 2) {
						system("CLS");
						std::cout << "\033[1;32m";
						std::cout << "Bani: " << g.getBani() << '\n';
						std::cout << "Calatori: " << g.getNumarCalatori() << '\n';
						std::cout << "Marfa: " << g.getCantMarfa() << '\n';
						std::cout << "\033[0m";
						std::cout << "0. Iesire\n1. Adaugare terminal(500$)\n2. Marire bonus(300$)\n3. Decolare avion:\n";
						int j;
						std::cin >> j;
						if (j <= 0 or j > 3)
							break;
						if (j == 1) {
							g.upgradeNumarTerminale();
							break;
						}
						if (j == 2) {
							g.upgradeBonus();
							break;
						}
						if (j == 3) {
							g.avionBonus(i);
							break;
						}
					}
					if (k == 3)
						break;
					if (k == 4) {
						g.saveGame();
						std::this_thread::sleep_for(std::chrono::seconds(3));
					}
				}
				running = !running;
			}
		}
	}
	void meniuExplicatii() {
		system("CLS");
		std::cout << "  Esti directorul turnului de control al unui aeroport si trebuie sa atribui fiecare avion in aterizare un terminal, pana ca acesta sa ramana fara combustibil.\n";
		std::cout << "  Aterizarea unui avion incepe in ultimele 10 minute de zbor. Afisajul fiecarui avion isi va schimba culoarea in rosu in momentul inceperii procedurilor de aterizare.\n";
		std::cout << "  Ecranul principal se imparte in 4 sectiuni: 'Veniri', 'Plecari', 'Terminale' si 'Statistici'.\n";
		std::cout << "\t->In 'Veniri' vor fi afisate toate zborurile ce vor ateriza in aeroportul tau. Sunt generate aleatoriu.\n";
		std::cout << "\t->In 'Plecari' vor fi afisate toate avioanele 'bonus'. Exista o sansa de 1% odata la 0.2secunde de a primi un avion bonus. Se revendica din meniu, sub tagul 'Magazin'.\n";
		std::cout << "\t->In 'Terminale' se vor afisa toate terminalele detinute de aeroport. Mare grija, odata ce un avion aterizeaza, terminalul selectat va fi ocupat pentru 25m! Ele se pot achizitiona din meniu-'Magazin' pentru 500$.\n";
		std::cout << "\t->In 'Statistici' se vor afisa:\n\t\t- Scorul - creste cu 1 la fiecare avion aterizat.\n\t\t- Balanta - banii castigati din avioanele aterizate si cele bonus.\n\t\t- Bonusul - acesta se va inmulti cu valoarea fiecarei curse(poate fi marit pentru 300$ in 'Magazin').\n\t\t- Avioanele bonus - numarul de avioane bonus.\n";
		std::cout << "  Pentru fiecare avion se vor afisa: Indexul, Categoria(Cat), Numarul zborului(ID), Modelul(Mod), Originea(Orig), Destinatia(Dest), Ora plecarii(Ple), Durata ramasa a zborului(Durata), Combustibilul ramas(C), Numarul de pasageri <daca este cazul>(Pas), Cantitatea de marfa<daca este cazul>(M), Organizatia militara<daca este cazul>(Org)\n";
		std::cout << "  Valoarea unui avion se calculeaza astfel:\n\t\tV = ( numar_pasageri + cantitate_marfa ) * bonus\n";
		std::cout << "Introduceti un input de la tastatura pentru a reveni la meniul principal...";
		char k;
		std::cin >> k;
	}
	void meniuPrincipal() {
		int optiune;
		while (true) {
			system("CLS");
			std::cout << "\033[1;34m";
			std::cout << "   ___    _   _____    _____     ____    _____    _____ " << '\n';
			std::cout << "  / _ \\  | | |  __ \\  |  __ \\   / __ \\  |  __ \\  |_   _|" << '\n';
			std::cout << " | |_| | | | | |__) | | |__) | | /  \\ | | |__) |   | |  " << '\n';
			std::cout << " |  _  | | | |  _  /  |  _ _/  | \\__/ | |  _  /    | |  " << '\n';
			std::cout << " |_| |_| |_| |_| \\_\\  |_|       \\____/  |_| \\_\\    |_|  " << '\n';
			std::cout << "\033[0m";
			std::cout << "\t\t   1. Joc nou\n\t\t   2. Incarca salvare\n\t\t   3. Reguli\n\t\t   4. Exit\n\t\t   ";
			std::cin >> optiune;
			if (optiune == 1) {
				Game g1;
				g = g1;
				Meniu::Joc();
			}
			else if (optiune == 2) {
				Game g1;
				g = g1;
				g.loadGame();
				Meniu::Joc();
			}
			else if (optiune == 3) {
				Meniu::meniuExplicatii();
			}
			else
				return;
		}
	}
	~Meniu() {
		if (obiect)
			delete obiect;
	}
};

Meniu* Meniu::obiect = 0;

int main() {
	srand(time(NULL));
	Meniu* m = m->getInstance();
	m->meniuPrincipal();
	return 0;
}