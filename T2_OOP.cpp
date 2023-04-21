#include <iostream>
#include <fstream>
#include <random>

class IOInterface {
public:
	virtual std::istream& scan(std::istream&) = 0;
	virtual std::ostream& print(std::ostream&) = 0;
};

class Avion: public IOInterface{
protected:
	std::string model, origine, destinatie;
	static int cont;
	const int numarZbor;
	int timpTraseu;
	float combustibil;
public:
	Avion();
	Avion(std::string, std::string, std::string, float, int);
	Avion(const Avion&);
	Avion& operator=(const Avion&);
	std::istream& scan(std::istream& in) {
		std::cout << "Introduceti:\nModel avion: ";
		in >> this->model;
		std::cout << "Originea zborului: ";
		in >> this->origine;
		std::cout << "Destinatia: ";
		in >> this->destinatie;
		std::cout << "Durata zborului: ";
		in >> this->timpTraseu;
		std::cout << "Combustibilul aeronavei: ";
		in >> this->combustibil;
		return in;
	}
	std::ostream& print(std::ostream& out) const{
		out << this->model << '\t' << this->origine << '\t' << this->destinatie << '\t' << this->timpTraseu << '\t' << this->combustibil << '\n';
		return out;
	}
	friend std::istream& operator>>(std::istream&, Avion&);
	friend std::ostream& operator<<(std::ostream&, const Avion&);
	virtual void valoare() = 0;
};

int Avion::cont = 0;

Avion::Avion():numarZbor(++cont) {
	this->model = "Nedefinit";
	this->origine = "NED";
	this->destinatie = "NED";
	this->timpTraseu = 0;
	this->combustibil = 0;
}

Avion::Avion(std::string model, std::string origine, std::string destinatie, float combustibil, int timpTraseu) :numarZbor(++cont) {
	this->model = model;
	this->origine = origine;
	this->destinatie = destinatie;
	this->timpTraseu = timpTraseu;
	this->combustibil = combustibil;
}

Avion::Avion(const Avion& obj) :numarZbor(++cont) {
	this->model = obj.model;
	this->origine = obj.origine;
	this->destinatie = obj.destinatie;
	this->timpTraseu = obj.timpTraseu;
	this->combustibil = obj.combustibil;
}

Avion& Avion::operator=(const Avion& obj) {
	this->model = obj.model;
	this->origine = obj.origine;
	this->destinatie = obj.destinatie;
	this->timpTraseu = obj.timpTraseu;
	this->combustibil = obj.combustibil;
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
};

int main() {
	return 0;
}