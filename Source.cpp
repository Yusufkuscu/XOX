#include <iostream>
#include <string>
using namespace std;

class Tahta {
private:
	char tahta[3][3];	//Oyun tahtas�n� tutan 3x3 matris

public:
	Tahta() {
		//Tahtay� ba�lang�� de�erlerine s�f�rlayal�m
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				tahta[i][j] = ' ';
			}
		}
	}

	//Tahtay� ekrana yazd�ran y�ntem
	void yazdir() {
		
		cout << "  0 1 2" << endl; //S�tun numaralar�
		for (int i = 0; i < 3; i++) {
			cout << i << " "; //Sat�r numaralar�
			for (int j = 0; j < 3; j++) {
				cout << tahta[i][j] << " ";
			}
			cout << endl;
		}
	}

	//Koordinatlar� verilen h�creye X veya O koyan y�ntem
	bool hucreKoy(int x, int y, char karakter) {
		if (tahta[x][y] != ' ') { //H�cre bo� de�ilse
			return false; //H�cre koyulmad�
		}
		else {
			tahta[x][y] = karakter; //H�creye karakter koy
			return true; //H�creye koyuldu
		}
	}
	//Tahtaya kazanan olup olmad���n� kontrol eden y�ntem
	char kazanan() {
		//Sat�r kontrol et
		for (int i = 0; i < 3; i++) {
			if (tahta[i][0] == tahta[i][1] && tahta[i][1] == tahta[i][2] && tahta[i][0] == tahta[i][2]) {
				return tahta[i][0];
			}
		}

		//S�tunlar� kontrol et
		for (int i = 0; i < 3; i++) {
			if (tahta[0][i] == tahta[1][i] && tahta[1][i] == tahta[2][i] && tahta[0][i] == tahta[2][i]) {
				return tahta[0][i];
			}
		}

		//�aprazlar� kontrol et
		if (tahta[0][0] == tahta[1][1] && tahta[1][1] == tahta[2][2] && tahta[0][0] == tahta[2][2]) {
			return tahta[0][0];
		}
		if (tahta[0][2] == tahta[1][1] && tahta[1][1] == tahta[2][0] && tahta[0][2] == tahta[2][0]) {
			return tahta[0][2];
		}

	}
	//Tahtada bo� h�cre kal�p kalmad���n� kontrol eden y�ntem
	bool bosVar() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (tahta[i][j] == ' ') {
					return true;
				}
			}
		}
		return false;
	}
};

class Oyuncu {
private:
	char karakter; //Oyuncunun kulland��� karakter(X veya O )

public:
	Oyuncu(char c) {
		karakter = c;
	}

	char getKarakter(){ return karakter; }
	void setKarakter(char karakter) { this->karakter = karakter; }


	//Tahtada koordinatlar� verilen h�creyi doldurmay� deneyen y�ntem

	bool hucreDoldur(Tahta& tahta, int x, int y) {
		return tahta.hucreKoy(x, y, karakter); //Tahtaya h�cre koymay� dene
	}
};

class Oyun {
private:
	Tahta tahta; //Oyun tahtas�
	Oyuncu* oyuncu1, * oyuncu2; //Oyuncular

public:
	Oyun(Oyuncu& o1, Oyuncu& o2) {
		oyuncu1 = &o1;
		oyuncu2 = &o2;
	}

	void oyna() {
		//Oyunun ba�lang�� ekran�
		cout << "         ~~Tic Tac Toe Oyununa Ho�geldiniz~~"    << endl;
		cout << "         ===================================" << endl;
		cout << endl;
		tahta.yazdir();

		int tur = 1; //Hangi oyuncunun s�ras� oldu�unu tutan de�i�ken
		while (true) {
			int x, y;
			Oyuncu* oyuncu; //Hangi oyuncunun s�ras� oldu�unu tutan nesne

			if (tur % 2 == 1) { //Turun 1,3,5,... oldu�u durumlar
				oyuncu = oyuncu1;
			}
			else { //Turun 2,4,6,... oldu�u durumlar
				oyuncu = oyuncu2;
			}
			cout << endl;
			cout << oyuncu->getKarakter() << " oyuncusu s�ras�. X koordinat�n� giriniz: ";
			cin >> x;

			cout << oyuncu->getKarakter() << " oyuncusu s�ras�. Y koordinat�n� giriniz: ";
			cin >> y;

			//H�cre doldurulmaya �al���l�r
			if (!oyuncu->hucreDoldur(tahta, x, y)) { //H�cre doldrulmad�ysa
				cout << "Bu h�cre zaten dolu. L�tfen ba�ka bir h�cre se�iniz." << endl;
				continue; //D�ng�n�n ba��na d�n
			}

			//Tahtay� ekrana yazd�r
			tahta.yazdir();

			//Kazanan olup olmad���n� kontrol et
			char kazanan = tahta.kazanan();
			if (kazanan != ' ') { //Kazanan var
				cout << kazanan << " kazand�!" << endl;
				break; // Oyunu bitir
			}

			//Bo� h�cre kal�p kalmad���n� kontrol et
			if (!tahta.bosVar()) { //Bo� h�cre yoksa
				cout << "Berabere! " << endl;
				break; //Oyunu bitir
			}

			tur++; //Bir sonraki oyuncunun s�ras�
		}
	}
};


int main() {
	setlocale(LC_ALL, "Turkish");

	Oyuncu oyuncu1('X'), oyuncu2('O'); //Oyuncular� olu�tur
	Oyun oyun(oyuncu1, oyuncu2); //Oyun olu�tur

	oyun.oyna(); //Oyunu ba�lat

	return 0;

}