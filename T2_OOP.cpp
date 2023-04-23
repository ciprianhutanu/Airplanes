#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <chrono>
#include <thread>
#include <conio.h>

class IOInterface {
public:
	virtual std::istream& scan(std::istream&) = 0;
	virtual std::ostream& print(std::ostream&) const = 0;
};

class Avion : public IOInterface {
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
	std::istream& scan(std::istream& in) {
		std::cout << "Introduceti:\nModel avion: ";
		in >> this->model;
		this->origine = "BUC";
		std::cout << "Destinatia: ";
		in >> this->destinatie;
		std::cout << "Durata zborului: ";
		in >> this->timpTraseu;
		this->timpDecolare = 0;
		this->combustibil = this->timpTraseu * 41.57;
		return in;
	}
	std::ostream& print(std::ostream& out) const {
		out << this->numarZbor << '\t' << this->model << '\t' << this->origine << '\t' << this->destinatie << '\t' << this->timpDecolare / 60 << ':' << this->timpDecolare % 60 << '\t' << this->timpTraseu << '\t' << this->combustibil << '\t';
		return out;
	}
	friend std::istream& operator>>(std::istream&, Avion&);
	friend std::ostream& operator<<(std::ostream&, const Avion&);
	virtual int valoare(float) = 0;
	virtual float getCombustibil() {
		return this->combustibil;
	}
	virtual int getTimpTraseu() {
		return this->timpTraseu;
	}
	virtual void setCombustibil(float x) {
		this->combustibil = x;
	}
	virtual void setTimpDecolare(int timpDecolare) {
		this->timpDecolare = timpDecolare;
	}
	virtual void consumCombustibil() {
		this->combustibil -= 41.57;
	}
	virtual void scadereTimp() {
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

Avion::Avion(std::string model, std::string origine, std::string destinatie, float combustibil, int timpDecolare,int timpTraseu) :numarZbor(++cont) {
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
	return obj.scan(in);
}

std::ostream& operator<<(std::ostream& out, const Avion& obj) {
	return obj.print(out);
}

class AvionCalatori :virtual public Avion {
protected:
	int numarCalatori;
public:
	AvionCalatori();
	AvionCalatori(std::string, std::string, std::string, float, int, int, int);
	AvionCalatori(const AvionCalatori&);
	AvionCalatori operator=(const AvionCalatori&);
	std::istream& scan(std::istream& in) {
		this->Avion::scan(in);
		std::cout << "Numar calatori(max.200): ";
		in >> this->numarCalatori;
		while (this->numarCalatori > 200)
		{
			std::cout << "Prea multi calatori! Mai incearca: ";
			in >> this->numarCalatori;
		}
		return in;
	}
	std::ostream& print(std::ostream& out) const{
		out << "CAL" << '\t';
		this->Avion::print(out);
		out << this->numarCalatori << '\n';
		return out;
	}
	friend std::istream& operator>>(std::istream& in, AvionCalatori& obj) {
		return obj.scan(in);
	}
	friend std::ostream& operator<<(std::ostream& out, const AvionCalatori& obj) {
		return obj.print(out);
	}
	int valoare(float mult) {
		return this->numarCalatori * mult;
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

class AvionMarfa :virtual public Avion {
protected:
	int cantitateMarfa;
public:
	AvionMarfa();
	AvionMarfa(std::string, std::string, std::string, float, int, int, int);
	AvionMarfa(const AvionMarfa&);
	AvionMarfa operator=(const AvionMarfa&);
	std::istream& scan(std::istream& in) {
		this->Avion::scan(in);
		std::cout << "Cantitate marfa(max.200): ";
		in >> this->cantitateMarfa;
		while (this->cantitateMarfa > 200)
		{
			std::cout << "Prea multa marfa! Mai incearca: ";
			in >> this->cantitateMarfa;
		}
		return in;
	}
	std::ostream& print(std::ostream& out) const {
		out << "MAR" << '\t';
		this->Avion::print(out);
		out << "-\t" << this->cantitateMarfa << '\n';
		return out;
	}
	friend std::istream& operator>>(std::istream& in, AvionMarfa& obj) {
		return obj.scan(in);
	}
	friend std::ostream& operator<<(std::ostream& out, const AvionMarfa& obj) {
		return obj.print(out);
	}
	int valoare(float mult) {
		return this->cantitateMarfa * mult;
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

class AvionMilitar :public AvionCalatori, public AvionMarfa {
private:
	std::string oraganizatieMilitara;
public:
	AvionMilitar();
	AvionMilitar(std::string, std::string, std::string, float, int, int, int, int, std::string);
	AvionMilitar(const AvionMilitar&);
	AvionMilitar operator=(const AvionMilitar&);
	std::istream& scan(std::istream& in) {
		Avion::scan(in);
		std::cout << "Numar militari(max.100): ";
		in >> this->numarCalatori;
		while (this->numarCalatori > 100)
		{
			std::cout << "Prea multi calatori! Mai incearca: ";
			in >> this->numarCalatori;
		}
		std::cout << "Cantitate marfa(max.100): ";
		in >> this->cantitateMarfa;
		while (this->cantitateMarfa > 100)
		{
			std::cout << "Prea multa marfa! Mai incearca: ";
			in >> this->cantitateMarfa;
		}
		std::cout << "Denumire organizatie militara: ";
		in >> oraganizatieMilitara;
		return in;
	}
	std::ostream& print(std::ostream& out) const{
		out << "MIL" << '\t';
		Avion::print(out);
		out << this->numarCalatori << '\t' << this->cantitateMarfa << '\t' << this->oraganizatieMilitara << '\n';
		return out;
	}
	friend std::istream& operator>>(std::istream& in, AvionMilitar& obj) {
		return obj.scan(in);
	}
	friend std::ostream& operator<<(std::ostream& out, const AvionMilitar& obj) {
		return obj.print(out);
	}
	int valoare(float mult) {
		return mult * (this->numarCalatori + this->cantitateMarfa);
	}
};

AvionMilitar::AvionMilitar() {
	this->oraganizatieMilitara = "NEDEFINIT";
}

AvionMilitar::AvionMilitar(std::string model, std::string origine, std::string destinatie, float combustibil, int timpDecolare, int timpTraseu, int numarCalatori, int cantitateMarfa, std::string organizatieMilitara):
							Avion(model, origine, destinatie, combustibil, timpDecolare, timpTraseu),
							AvionCalatori(model, origine, destinatie, combustibil, timpDecolare, timpTraseu, numarCalatori),
							AvionMarfa(model, origine, destinatie, combustibil, timpDecolare, timpTraseu, cantitateMarfa) {
	this->oraganizatieMilitara = oraganizatieMilitara;
}

AvionMilitar::AvionMilitar(const AvionMilitar& obj) :Avion(obj), AvionCalatori(obj), AvionMarfa(obj) {
	this->oraganizatieMilitara = obj.oraganizatieMilitara;
}

AvionMilitar AvionMilitar::operator=(const AvionMilitar& obj) {
	if (this != &obj) {
		AvionCalatori::operator=(obj);
		AvionMarfa::operator=(obj);
		this->oraganizatieMilitara = obj.oraganizatieMilitara;
	}
	return *(this);
}

class Zbor {
private:
	Avion* avion;
public:
	Zbor() { this->avion = NULL; }
	Zbor(Avion* avion, int optiune) {
		if (optiune == 0)
			this->avion = new AvionCalatori();
		if (optiune == 1)
			this->avion = new AvionMarfa();
		if (optiune == 2)
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
		if (optiune == 1)
			obj.avion = new AvionCalatori();
		if (optiune == 2)
			obj.avion = new AvionMarfa();
		if (optiune == 3)
			obj.avion = new AvionMilitar();
		in >> *(obj.avion);
		return in;
	}
	friend std::ostream& operator<<(std::ostream& out, const Zbor& obj) {
		out << *(obj.avion);
		return out;
	}
	Avion* getAvion() const{
		return this->avion;
	}
	/*~Zbor() {
		if (this->avion != NULL) {
			delete this->avion;
			this->avion = NULL;
		}
	}*/
};

class Game {
private:
	std::vector<Zbor> listaAvioane;
	std::vector<Zbor> listaAvioaneBonus;
	std::vector<int> timpTerminale;
	const std::vector<std::string> listaAeropoarte = { "BUC","SCV","NYC","ROM","LON","LAA","BER","AMS","MAD","LIS",
														"SOF","CLJ","IAS","TOK","MEX","BRA","SYD","WDC","CAI","ATH" };
	const std::vector<std::string> modeleAvioane = { "Boing","Airbus","Douglas","McDonel","Antonov" };
	const std::vector<std::string> organizatii = { "NATO", "OTSC", "OSC", "ASEAN", "LigaAraba", "UA", "ONU" };
	int numarTerminale, numarAvioaneBonus, scor;
	float bani, mult;
public:
	Game() {
		this->numarTerminale = 1;
		this->bani = 0;
		this->bani = 0;
		this->scor = 0;
		this->numarAvioaneBonus = 0;
		this->mult = 1;
		this->timpTerminale.push_back(0);
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
		out << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
		out << "Plecari:\nIndex\tCat\tID\tMod\tOrig\tDest\tPle\tDurata\tC\tPas\tM(tone)\tOrg\n";
		for (int i = 0; i < obj.listaAvioaneBonus.size(); i++) {
			out << i << '\t' << obj.listaAvioaneBonus[i];
		}
		out << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
		for (int i = 1; i <= obj.numarTerminale; i++) {
			out << "T" << i << ": ";
			if (obj.timpTerminale[i - 1] == 0)
				out << "Liber\n";
			else
				out << "Ocupat pentru inca: " << obj.timpTerminale[i - 1] << "m\n";
		}
		out << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
		out << "Scor: " << obj.scor << '\n';
		out << "Balanta: " << obj.bani << '\n';
		out << "Bonus: " << obj.mult << "x\n";
		out << "Avioane bonus: " << obj.numarAvioaneBonus << '\n';
		out << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
		return out;
	}
	void generareAvion(int timpDecolare) {
		int o, tipAvion, timpTraseu;
		float combustibil;
		std::string origine, destinatie, model;
		Avion* a;
		tipAvion = rand() % 3;
		model = this->modeleAvioane[rand() % 5];
		do {
			o = rand() % 20;
		} while (o == 0);
		origine = this->listaAeropoarte[o];
		destinatie = this->listaAeropoarte[0];
		timpTraseu = rand() % 180 + 25;
		combustibil = timpTraseu * 41.57;
		if (tipAvion == 0) {
			int numarCalatori = rand() % 200 + 1;
			a = new AvionCalatori(model, origine, destinatie, combustibil, timpDecolare, timpTraseu, numarCalatori);
		}
		else if (tipAvion == 1) {
			int cantitateMarfa = rand() % 200 + 1;
			a = new AvionMarfa(model, origine, destinatie, combustibil, timpDecolare, timpTraseu, cantitateMarfa);
		}
		else{
			int cantitateMarfa = rand() % 100 + 1, numarCalatori = rand() % 100 + 1;
			std::string orgMilitara = this->organizatii[rand() % 7];
			a = new AvionMilitar(model, origine, destinatie, combustibil, timpDecolare, timpTraseu, numarCalatori, cantitateMarfa, orgMilitara);
		}
		Zbor zbor(a, tipAvion);
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
			for (int k = i; k < this->listaAvioane.size() - 1; k++)
				this->listaAvioane[k] = this->listaAvioane[k + 1];
			this->listaAvioane.pop_back();
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
			this->mult += 0.1;
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
		k = rand() % 150;
		if (k == 0)
			this->numarAvioaneBonus++;
		for (i = 0; i < this->numarTerminale; i++) {
			if (this->timpTerminale[i] > 0)
				this->timpTerminale[i]--;
		}
		for (i = 0; i < this->listaAvioane.size(); i++){
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
			if ((this->listaAvioaneBonus[i].getAvion()->getTimpTraseu() == 1 or this->listaAvioaneBonus[i].getAvion()->getCombustibil() - 41.57 < 0) 
				and (this->listaAvioaneBonus[i].getAvion()->getTimpTraseu() > 0 and this->listaAvioaneBonus[i].getAvion()->getCombustibil() > 0)) {
				this->listaAvioaneBonus[i].getAvion()->scadereTimp();
				this->listaAvioaneBonus[i].getAvion()->setCombustibil(0);
				this->bani += this->listaAvioaneBonus[i].getAvion()->valoare(this->mult);
				a = i;
			}
			if (this->listaAvioaneBonus[i].getAvion()->getCombustibil() > 0 and this->listaAvioaneBonus[i].getAvion()->getTimpTraseu() > 0) {
				this->listaAvioaneBonus[i].getAvion()->consumCombustibil();
				this->listaAvioaneBonus[i].getAvion()->scadereTimp();
			}
		}
		if (this->listaAvioaneBonus.size() >= 1 and a!=-1) {
			for (int j = a; j < this->listaAvioaneBonus.size() - 1; j++)
				this->listaAvioaneBonus[j] = this->listaAvioaneBonus[j + 1];
			this->listaAvioaneBonus.pop_back();
			a = -1;
		}
	}
	void avionBonus(int i) {
		if (this->numarAvioaneBonus >= 1) {
			this->numarAvioaneBonus--;
			Zbor z;
			system("CLS");
			std::cin >> z;
			z.getAvion()->setTimpDecolare(i);
			this->listaAvioaneBonus.push_back(z);
			std::cout << "Avion a plecat!";
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		else {
			std::cout << "Fonduri insuficiente!";
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
	int verificareViata() {
		for (int i = 0; i < this->listaAvioane.size(); i++) {
			if (this->listaAvioane[i].getAvion()->getCombustibil() == 0)
				return i;
		}
		return - 1;
	}
	int getScor() {
		return this->scor;
	}
};

class Meniu {
public:
	void Joc() {
		Game g;
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
					std::cout << "Avionul cu indexul "<<n<<" s-a prabusit! Joc incheiat...\n";
					std::cout << "\033[0m";
					std::this_thread::sleep_for(std::chrono::seconds(3));
					system("CLS");
					std::cout << "\033[1;32m";
					std::cout << "Scorul obtinut: " << g.getScor();
					std::cout << "\033[0m";
					running = false;
				}
			}
			else {
				int k;
				std::cout << "0. Iesire\n1. Aterizati avion\n2. Magazin\n3. Continuare\n";
				std::cin >> k;
				if (k <= 0 or k > 3) {
					running = !running;
				}
				if (k == 1) {
					int t, i;
					std::cout << "Introduceti terminal: ";
					std::cin >> t;
					std::cout << "Introduceti avion: ";
					std::cin >> i;
					g.aterizareTerminal(t, i);
				}
				while (k == 2) {
					system("CLS");
					std::cout << "0. Iesire\n1. Adaugare terminal(500$)\n2. Marire bonus(300$)\n3. Avion bonus\n";
					int j;
					std::cin >> j;
					if (j <= 0 or j > 3)
						k = 0;
					if (j == 1)
						g.upgradeNumarTerminale(), k = 0;
					if (j == 2)
						g.upgradeBonus(), k = 0;
					if (j == 3)
						g.avionBonus(i), k = 0;
				}
				running = !running;
			}
		}
	}
	void meniuExplicatii() {
			system("CLS");
			std::cout << "  Esti directorul turnului de control al unui aeroport si trebuie sa atribui fiecare avion in aterizare un terminal, pana ca acesta sa ramana fara combustibil.\n";
			std::cout << "  Aterizarea unui avion incepe in ultimele 10 minute de zbor. Afisajul fiecarui avion isi va schimba culoarea in rosu in momentul inceperii procedurilor de aterizare.\n";
			std::cout << "  Ecranul principal se imparte in 4 sectiunii: 'Veniri', 'Plecari', 'Terminale' si 'Statistici'.\n";
			std::cout << "\t->In 'Veniri' vor fi afisate toate zborurile ce vor ateriza in aeroportul tau. Sunt generate aleatoriu.\n";
			std::cout << "\t->In 'Plecari' vor fi afisate toate avioanele 'bonus'. Exista o sansa de 1% odata la 0.2secunde de a primi un avion bonus. Se revendica din meniu, sub tagul 'Magazin'.\n";
			std::cout << "\t->In 'Terminale' se vor afisa toate terminalele destinute de aeroport. Mare grija, odata ce un avion aterizeaza, terminalul selectat va fi ocupat pentru 25m! Ele se pot achizitiona din meniu-'Magazin' pentru 500$.\n";
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
			std::cout << "\t\t   1. Joc nou\n\t\t   2. Reguli\n\t\t   3. Exit\n\t\t   ";
			std::cin >> optiune;
			if (optiune == 1)
				Meniu::Joc();
			else if (optiune == 2) {
				Meniu::meniuExplicatii();
			}
			else
				return;
		}
	}
};

int main() {
	srand(time(NULL));
	Meniu m;
	m.meniuPrincipal();
	return 0;
}
