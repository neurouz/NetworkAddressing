#include <iostream>
#include <string>
#include <cmath>
using namespace std;

enum Mrezna_Klasa { A, B, C };
const char* MreznaKlasaChar[] = { "A Klasa - Velika mreza\n", "B Klasa - Srednja mreza\n", "C Klasa - Mala mreza\n" };

#define crt {cout<<"--------------------------------------------------------------------------------------\n";}

auto crta = "\n-------------------------------\n";

int DecimalToBinary(int broj) {
	int novi = 0;
	int stepen = 0;
	while (broj) {
		int ostatak = broj % 2;
		novi += ostatak * pow(10, stepen);
		broj /= 2;
		stepen++;
	}
	return novi;
}
int BrojCifara(int broj) {
	int cif = 0;
	while (broj) {
		cif++;
		broj /= 10;
	}
	return cif;
}
int BinaryToDecimal(int broj) {
	int brCif = BrojCifara(broj);
	int stepen = 0;
	int Decimalno = 0;
	while (broj) {
		int cifra = broj % 10;
		if (cifra == 1)
			Decimalno += cifra * pow(2, stepen);
		broj /= 10;
		stepen++;
	}
	return Decimalno;
}
string Get8Digit(int broj) {
	string novi = "00000000";
	int indeks = 7;
	while (broj) {
		const int cifra = broj % 10;
		novi[indeks] = cifra + '0';
		indeks--;
		broj /= 10;
	}
	return novi;
}
string GetAdresuMreze(string ip, string subnet) {

	if (ip.c_str() == nullptr)
		throw exception();

	string temp;
	for (size_t i = 0; i < ip.length(); i++)
	{
		if (ip[i] == '.') temp += ip[i];
		else if (ip[i] == '1' && subnet[i] == '1') temp += '1';
		else temp += '0';
	}
	return temp;
}
string GetPrvuIskoristivu(string mreza) {

	if (mreza.c_str() == nullptr)
		throw exception();

	string PosljednjiOktet = mreza.substr(27, 35);
	int broj = stoi(PosljednjiOktet);
	int noviBroj = BinaryToDecimal(broj);
	noviBroj++;
	broj = DecimalToBinary(noviBroj);
	string cat = Get8Digit(broj);

	string novi = mreza.substr(0, 27);
	novi += cat;
	
	return novi;
}
string GetBroadcastAdresu(int subnet, string mreza) {

	if (mreza.c_str() == nullptr)
		throw exception();

	string temp;
	for (size_t i = 0; i < subnet; i++)
	{
		if (mreza[i] == '.') { subnet++; temp += mreza[i]; }
		else temp += mreza[i];
	}
	for (size_t i = subnet; i < mreza.length(); i++)
	{
		if (mreza[i] == '.') temp += '.';
		else temp += '1';
	}

	return temp;
}
string GetZadnjuIskoristivu(string broadcast) {

	if (broadcast.c_str() == nullptr)
		throw exception();

	string PosljednjiOktet = broadcast.substr(27, 35);
	int broj = stoi(PosljednjiOktet);
	int noviBroj = BinaryToDecimal(broj);
	noviBroj--;
	broj = DecimalToBinary(noviBroj);
	string cat = Get8Digit(broj);

	string novi = broadcast.substr(0, 27);
	novi += cat;

	return novi;
}

string GetAdresuDecimalno(string binarna) {

	if (binarna.c_str() == nullptr)
		throw exception();

	int Okteti[4] = { 0,0,0,0 };
	int stepen = 0;
	int brojacOkteta = 3;
	for (size_t i = binarna.length() - 1; i != -1; i--)
	{
		if (binarna[i] != '.') {
			char znak = binarna[i];
			int cifra = atoi(&znak);
			Okteti[brojacOkteta] += cifra * pow(10, stepen);
			stepen++;
		}
		if (binarna[i] == '.') {
			brojacOkteta--;
			stepen = 0;
		}
	}

	int n1 = BinaryToDecimal(Okteti[0]);
	int n2 = BinaryToDecimal(Okteti[1]);
	int n3 = BinaryToDecimal(Okteti[2]);
	int n4 = BinaryToDecimal(Okteti[3]);

	string t1 = to_string(n1);
	string t2 = to_string(n2);
	string t3 = to_string(n3);
	string t4 = to_string(n4);

	string temp = t1;
	temp += "." + t2 + "." + t3 + "." + t4;

	return temp;
}

class SubnetMask
{
public:
	SubnetMask(int sn) : subnet(sn) {
		if (sn <= 8) klasa = A;
		if (sn > 8 && sn <= 16) klasa = B;
		if (sn > 16) klasa = C;
	}

	static bool IsValid(int subnet)
	{
		return subnet > 1 && subnet < 32;
	}

	~SubnetMask() {
		subnet = 0;
	}

	void LoadSubnetMask() {
		string temp = "00000000.00000000.00000000.00000000";
		int kopija = subnet;
		for (size_t i = 0; i < kopija; i++)
		{
			if (temp[i] == '.') kopija++;
			else temp[i] = '1';
		}
		_subnetMask = temp;
	}
	void PrintSubnetMask() const {
		cout << "\nSubnet:\t\t\t/" << subnet << endl;
		cout << "Subnet maska:\t\t" << _subnetMask;
		cout << "  |  " << GetAdresuDecimalno(_subnetMask) << endl;
	}
	string GetSubnetBinary() const {
		return _subnetMask;
	}
	int GetSubnetDecimal() const {
		return subnet;
	}
	Mrezna_Klasa GetKlasu() const {
		return klasa;
	}

private:
	string _subnetMask;
	Mrezna_Klasa klasa;
	int subnet;
};

class IP_Adress
{
public:
	void Add_IP(string IP) {
		if (CheckValid(IP)) {
			_ip = IP;
		}
		else
			_valid = false;
	}
	static bool CheckValid(string ip) {
		if (ip.length() > 15)
			return false;

		bool check = true; int brCif = 0;

		for (size_t i = 0; i < ip.length(); i++)
		{
			if (ip[i] == '-') return false;
		}
		for (size_t i = 0; i < ip.length(); i++)
		{
			if (ip[i] == '.') {
				if (brCif > 3) return false;
				brCif = 0;
			}
			else brCif++;
		}

		int Okteti[4] = { 0,0,0,0 };
		int stepen = 0;
		int brojacOkteta = 3;
		for (size_t i = ip.length() - 1; i != -1; i--)
		{
			if (ip[i] != '.') {
				char znak = ip[i];
				int cifra = atoi(&znak);
				Okteti[brojacOkteta] += cifra * pow(10, stepen);
				stepen++;
			}
			if (ip[i] == '.') {
				brojacOkteta--;
				stepen = 0;
			}
		}

		for (size_t i = 0; i < 4; i++)
		{
			if (Okteti[i] < 0 || Okteti[i] > 255) return false;
		}

		return true;
	}
	void convert_to_binary() {

		if (_ip.c_str() == nullptr) return;

		int Okteti[4] = { 0,0,0,0 };
		int stepen = 0;
		int brojacOkteta = 3;
		for (size_t i = _ip.length() - 1; i != -1; i--)
		{
			if (_ip[i] != '.') {
				char znak = _ip[i];
				int cifra = atoi(&znak);
				Okteti[brojacOkteta] += cifra * pow(10, stepen);
				stepen++;
			}
			if (_ip[i] == '.') {
				brojacOkteta--;
				stepen = 0;
			}
		}
		char t1[8], t2[8], t3[8], t4[8];

		int n1 = DecimalToBinary(Okteti[0]);
		int n2 = DecimalToBinary(Okteti[1]);
		int n3 = DecimalToBinary(Okteti[2]);
		int n4 = DecimalToBinary(Okteti[3]);

		string temp = Get8Digit(n1);
		temp += "." + Get8Digit(n2) + "." + Get8Digit(n3) + "." + Get8Digit(n4);

		_ip_binary = temp;
	}
	void PrintIP() const {
		if (_ip.c_str() != nullptr) {
			crt;
			cout << "IP Adresa (Decimalno):\t" << _ip << endl;
		}
		if (_ip_binary.c_str() != nullptr) {
			cout << "IP Adresa (Binarno):\t" << _ip_binary << endl;
		}
	}
	string GetIPBinary() const {
		return _ip_binary;
	}
	string GetIPDecimal() const {
		return _ip;
	}

private:
	string _ip;
	string _ip_binary;
	bool _valid = true;
};

int main() {

	string ip_address;
	getline(cin, ip_address);
	
	if(!IP_Adress::CheckValid(ip_address))
	{
		cout << "> ERROR: IP Address is not valid.";
		return -1;
	}

	int subnet;
	cin >> subnet;

	if(!SubnetMask::IsValid(subnet))
	{
		cout << "> ERROR: Value of subnet mask must be between 1 and 32.";
		return -1;
	}

	IP_Adress IP1;
	IP1.Add_IP(ip_address);
	IP1.convert_to_binary();
	IP1.PrintIP();

	SubnetMask mask1(subnet);
	mask1.LoadSubnetMask();
	mask1.PrintSubnetMask();

	crt;
	cout << "\t\t\tKlasa mreze: " << MreznaKlasaChar[mask1.GetKlasu()];
	crt;

	try {
		string Adresa_mreze = GetAdresuMreze(IP1.GetIPBinary(), mask1.GetSubnetBinary());
		cout << "\nAdresa mreze:\t\t" << Adresa_mreze;
		cout << "  |  " << GetAdresuDecimalno(Adresa_mreze) << endl;
		string Prva_iskoristiva = GetPrvuIskoristivu(Adresa_mreze);
		cout << "Prva iskoristiva:\t" << Prva_iskoristiva;
		cout << "  |  " << GetAdresuDecimalno(Prva_iskoristiva) << endl;
		string Broadcast_adresa = GetBroadcastAdresu(mask1.GetSubnetDecimal(), IP1.GetIPBinary());
		cout << "Broadcast adresa:\t" << Broadcast_adresa;
		cout << "  |  " << GetAdresuDecimalno(Broadcast_adresa) << endl;
		string Zadnja_iskoristiva = GetZadnjuIskoristivu(Broadcast_adresa);
		cout << "Posljednja iskoristiva:\t" << Zadnja_iskoristiva;
		cout << "  |  " << GetAdresuDecimalno(Zadnja_iskoristiva) << endl;

		const int stepen = 32 - mask1.GetSubnetDecimal();
		const int host = pow(2, stepen) - 2;
		cout << "Ukupno hostova:\t\t" << host << endl;
		crt;
	}
	catch (const exception& e) { cout << "Exception error :: " << e.what(); }

	cin.get();
	return 0;
}
