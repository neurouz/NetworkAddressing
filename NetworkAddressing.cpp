#include <iostream>
using namespace std;

enum Mrezna_Klasa { A, B, C };
const char* MreznaKlasaChar[] = { "A Klasa - Velika mreza\n", "B Klasa - Srednja mreza\n", "C Klasa - Mala mreza\n" };

#define crt {cout<<"--------------------------------------------------------------------------------------\n";}

auto crta = "\n-------------------------------\n";

char* DodajString(const char* temp) {
	char* n = new char[strlen(temp) + 1];
	strcpy_s(n, strlen(temp) + 1, temp);
	return n;
}
auto _GET_ERROR()
{
	char* error = new char[strlen("IP Adresa nije validna!") + 1];
	strcpy_s(error, strlen("IP Adresa nije validna!") + 1, "IP Adresa nije validna!");
	return error;
}

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
char* Get8Digit(int broj) {
	char novi[9] = "00000000";
	int indeks = 7;
	while (broj) {
		const int cifra = broj % 10;
		novi[indeks] = cifra + '0';
		indeks--;
		broj /= 10;
	}
	char* n = new char[strlen(novi) + 1];
	strcpy_s(n, strlen(novi) + 1, novi);
	return n;
}
char* GetAdresuMreze(char* ip, char* subnet) {

	if (ip == nullptr)
		throw exception("IP Adresa nije validna!\n");

	char temp[50];
	for (size_t i = 0; i < strlen(ip); i++)
	{
		if (ip[i] == '.') temp[i] = ip[i];
		else if (ip[i] == '1' && subnet[i] == '1') temp[i] = '1';
		else temp[i] = '0';
	}
	temp[strlen(ip)] = '\0';
	int x = strlen(temp) + 1;
	char* n = new char[x];
	strcpy_s(n, x, temp);
	return n;
}
char* GetPrvuIskoristivu(char* mreza) {

	if (mreza == nullptr)
		throw exception("IP Adresa nije validna!\n");

	char PosljednjiOktet[9];
	strcpy_s(PosljednjiOktet, 9, mreza + 27);
	int broj = atoi(PosljednjiOktet);
	int noviBroj = BinaryToDecimal(broj);
	noviBroj++;
	broj = DecimalToBinary(noviBroj);
	char* cat = Get8Digit(broj);
	char* novi = new char[strlen(mreza) + 1];
	strncpy_s(novi, strlen(mreza) + 1, mreza, 27);
	strcat_s(novi, strlen(mreza) + 1, cat);
	return novi;
}
char* GetBroadcastAdresu(int subnet, char* mreza) {

	if (mreza == nullptr)
		throw exception("IP Adresa nije validna!\n");

	char temp[50];
	for (size_t i = 0; i < subnet; i++)
	{
		if (mreza[i] == '.') { subnet++; temp[i] = mreza[i]; }
		else temp[i] = mreza[i];
	}
	for (size_t i = subnet; i < strlen(mreza); i++)
	{
		if (mreza[i] == '.') temp[i] = '.';
		else temp[i] = '1';
	}
	temp[35] = '\0';
	char* n = new char[strlen(temp) + 1];
	strcpy_s(n, strlen(temp) + 1, temp);
	return n;
}
char* GetZadnjuIskoristivu(char* broadcast) {

	if (broadcast == nullptr)
		throw exception("IP Adresa nije validna!\n");

	char PosljednjiOktet[9];
	strcpy_s(PosljednjiOktet, 9, broadcast + 27);
	int broj = atoi(PosljednjiOktet);
	int noviBroj = BinaryToDecimal(broj);
	noviBroj--;
	broj = DecimalToBinary(noviBroj);
	char* cat = Get8Digit(broj);
	char* novi = new char[strlen(broadcast) + 1];
	strncpy_s(novi, strlen(broadcast) + 1, broadcast, 27);
	strcat_s(novi, strlen(broadcast) + 1, cat);
	return novi;
}

char* GetAdresuDecimalno(char* binarna) {

	if (binarna == nullptr)
		throw exception("IP Adresa nije validna!\n");

	char temp[100];
	int Okteti[4] = { 0,0,0,0 };
	int stepen = 0;
	int brojacOkteta = 3;
	for (size_t i = strlen(binarna) - 1; i != -1; i--)
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
	char t1[8], t2[8], t3[8], t4[8];

	int n1 = BinaryToDecimal(Okteti[0]);
	int n2 = BinaryToDecimal(Okteti[1]);
	int n3 = BinaryToDecimal(Okteti[2]);
	int n4 = BinaryToDecimal(Okteti[3]);

	_itoa_s(n1, t1, 10);
	_itoa_s(n2, t2, 10);
	_itoa_s(n3, t3, 10);
	_itoa_s(n4, t4, 10);

	strcpy_s(temp, t1);
	strcat_s(temp, ".");
	strcat_s(temp, t2);
	strcat_s(temp, ".");
	strcat_s(temp, t3);
	strcat_s(temp, ".");
	strcat_s(temp, t4);

	char* newIP = new char[strlen(temp) + 1];
	strcpy_s(newIP, strlen(temp) + 1, temp);
	return newIP;
}

class SubnetMask
{
public:
	SubnetMask(int sn) : subnet(sn) {
		_subnetMask = new char[2];
		strcpy_s(_subnetMask, 2, " ");
		if (sn <= 8) klasa = A;
		if (sn > 8 && sn <= 16) klasa = B;
		if (sn > 16) klasa = C;
	};
	SubnetMask() {
		_subnetMask = new char[2];
		strcpy_s(_subnetMask, 2, " ");
		subnet = 0;
		if (subnet <= 8) Mrezna_Klasa(A);
		if (subnet > 8 && subnet <= 16) Mrezna_Klasa(B);
		if (subnet > 16) Mrezna_Klasa(C);
	};
	~SubnetMask() {
		delete[]_subnetMask; _subnetMask = nullptr;
		subnet = 0;
	};

	void LoadSubnetMask() {
		char temp[36] = "00000000.00000000.00000000.00000000";
		int kopija = subnet;
		for (size_t i = 0; i < kopija; i++)
		{
			if (temp[i] == '.') kopija++;
			else temp[i] = '1';
		}

		delete[]_subnetMask; _subnetMask = nullptr;
		_subnetMask = new char[strlen(temp) + 1];
		strcpy_s(_subnetMask, strlen(temp) + 1, temp);
	}
	void PrintSubnetMask() const {
		cout << "\nSubnet:\t\t\t/" << subnet << endl;
		cout << "Subnet maska:\t\t" << _subnetMask;
		cout << "  |  " << GetAdresuDecimalno(_subnetMask) << endl;
	}
	char* GetSubnetBinary() const {
		return _subnetMask;
	}
	int GetSubnetDecimal() const {
		return subnet;
	}
	Mrezna_Klasa GetKlasu() const{
		return klasa;
	}

private:
	char* _subnetMask;
	Mrezna_Klasa klasa;
	int subnet;
};

class IP_Adress
{
public:
	IP_Adress() {
		_ip = nullptr;
		_ip_binary = nullptr;
	};
	~IP_Adress() {
		delete[]_ip; _ip = nullptr;
		delete[]_ip_binary; _ip_binary = nullptr;
	};

	void Add_IP(const char* IP) {
		if (CheckValid(IP)) {
			_ip = DodajString(IP);
		}
		else
			_valid = false;
	}
	bool CheckValid(const char* ip) const {
		if (strlen(ip) > 15)
			return false;

		bool check = true; int brCif = 0;

		for (size_t i = 0; i < strlen(ip); i++)
		{
			if (ip[i] == '-') return false;
		}
		for (size_t i = 0; i < strlen(ip); i++)
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
		for (size_t i = strlen(ip) - 1; i != -1; i--)
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

		if (_ip == nullptr) return;

		char temp[100];
		int Okteti[4] = { 0,0,0,0 };
		int stepen = 0;
		int brojacOkteta = 3;
		for (size_t i = strlen(_ip) - 1; i != -1; i--)
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

		strcpy_s(temp, Get8Digit(n1));
		strcat_s(temp, ".");
		strcat_s(temp, Get8Digit(n2));
		strcat_s(temp, ".");
		strcat_s(temp, Get8Digit(n3));
		strcat_s(temp, ".");
		strcat_s(temp, Get8Digit(n4));

		_ip_binary = new char[strlen(temp) + 1];
		strcpy_s(_ip_binary, strlen(temp) + 1, temp);
	}
	void PrintIP() const {
		if (_ip != nullptr) {
			crt;
			cout << "IP Adresa (Decimalno):\t" << _ip << endl;
		}
		if (_ip_binary != nullptr) {
			cout << "IP Adresa (Binarno):\t" << _ip_binary << endl;
		}
	}
	char* GetIPBinary() const {
		return _ip_binary;
	}
	char* GetIPDecimal() const {
		return _ip;
	}

private:
	char* _ip;
	char* _ip_binary;
	bool _valid = true;
};

int main() {

	IP_Adress IP1;
	IP1.Add_IP("192.168.1.104");
	IP1.convert_to_binary();
	IP1.PrintIP();

	SubnetMask mask1(24);
	mask1.LoadSubnetMask();
	mask1.PrintSubnetMask();

	crt;
	cout << "\t\t\tKlasa mreze: " << MreznaKlasaChar[mask1.GetKlasu()];
	crt;

	try {
		char* Adresa_mreze = GetAdresuMreze(IP1.GetIPBinary(), mask1.GetSubnetBinary());
		cout << "\nAdresa mreze:\t\t" << Adresa_mreze;
		cout << "  |  " << GetAdresuDecimalno(Adresa_mreze) << endl;
		char* Prva_iskoristiva = GetPrvuIskoristivu(Adresa_mreze);
		cout << "Prva iskoristiva:\t" << Prva_iskoristiva;
		cout << "  |  " << GetAdresuDecimalno(Prva_iskoristiva) << endl;
		char* Broadcast_adresa = GetBroadcastAdresu(mask1.GetSubnetDecimal(), IP1.GetIPBinary());
		cout << "Broadcast adresa:\t" << Broadcast_adresa;
		cout << "  |  " << GetAdresuDecimalno(Broadcast_adresa) << endl;
		char* Zadnja_iskoristiva = GetZadnjuIskoristivu(Broadcast_adresa);
		cout << "Posljednja iskoristiva:\t" << Zadnja_iskoristiva;
		cout << "  |  " << GetAdresuDecimalno(Zadnja_iskoristiva) << endl;

		const int stepen = 32 - mask1.GetSubnetDecimal();
		const int host = pow(2, stepen) - 2;
		cout << "Ukupno hostova:\t\t" << host << endl;
		crt;

		delete[] Adresa_mreze; Adresa_mreze = nullptr;
		delete[] Prva_iskoristiva; Prva_iskoristiva = nullptr;
		delete[] Zadnja_iskoristiva; Zadnja_iskoristiva = nullptr;
		delete[] Broadcast_adresa; Broadcast_adresa = nullptr;
	}
	catch (const exception& e) { cout << "Exception error :: " << e.what(); }

	cin.get();
	return 0;
}
