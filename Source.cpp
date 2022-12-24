#include <iostream>
#include <string>
using namespace std;

class Tahta {
private:
	char tahta[3][3];	//Oyun tahtasýný tutan 3x3 matris

public:
	Tahta() {
		//Tahtayý baþlangýç deðerlerine sýfýrlayalým
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				tahta[i][j] = ' ';
			}
		}
	}

	//Tahtayý ekrana yazdýran yöntem
	void yazdir() {
		
		cout << "  0 1 2" << endl; //Sütun numaralarý
		for (int i = 0; i < 3; i++) {
			cout << i << " "; //Satýr numaralarý
			for (int j = 0; j < 3; j++) {
				cout << tahta[i][j] << " ";
			}
			cout << endl;
		}
	}

	//Koordinatlarý verilen hücreye X veya O koyan yöntem
	bool hucreKoy(int x, int y, char karakter) {
		if (tahta[x][y] != ' ') { //Hücre boþ deðilse
			return false; //Hücre koyulmadý
		}
		else {
			tahta[x][y] = karakter; //Hücreye karakter koy
			return true; //Hücreye koyuldu
		}
	}
	//Tahtaya kazanan olup olmadýðýný kontrol eden yöntem
	char kazanan() {
		//Satýr kontrol et
		for (int i = 0; i < 3; i++) {
			if (tahta[i][0] == tahta[i][1] && tahta[i][1] == tahta[i][2] && tahta[i][0] == tahta[i][2]) {
				return tahta[i][0];
			}
		}

		//Sütunlarý kontrol et
		for (int i = 0; i < 3; i++) {
			if (tahta[0][i] == tahta[1][i] && tahta[1][i] == tahta[2][i] && tahta[0][i] == tahta[2][i]) {
				return tahta[0][i];
			}
		}

		//Çaprazlarý kontrol et
		if (tahta[0][0] == tahta[1][1] && tahta[1][1] == tahta[2][2] && tahta[0][0] == tahta[2][2]) {
			return tahta[0][0];
		}
		if (tahta[0][2] == tahta[1][1] && tahta[1][1] == tahta[2][0] && tahta[0][2] == tahta[2][0]) {
			return tahta[0][2];
		}

	}
	//Tahtada boþ hücre kalýp kalmadýðýný kontrol eden yöntem
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
	char karakter; //Oyuncunun kullandýðý karakter(X veya O )

public:
	Oyuncu(char c) {
		karakter = c;
	}

	char getKarakter(){ return karakter; }
	void setKarakter(char karakter) { this->karakter = karakter; }


	//Tahtada koordinatlarý verilen hücreyi doldurmayý deneyen yöntem

	bool hucreDoldur(Tahta& tahta, int x, int y) {
		return tahta.hucreKoy(x, y, karakter); //Tahtaya hücre koymayý dene
	}
};

class Oyun {
private:
	Tahta tahta; //Oyun tahtasý
	Oyuncu* oyuncu1, * oyuncu2; //Oyuncular

public:
	Oyun(Oyuncu& o1, Oyuncu& o2) {
		oyuncu1 = &o1;
		oyuncu2 = &o2;
	}

	void oyna() {
		//Oyunun baþlangýç ekraný
		cout << "         ~~Tic Tac Toe Oyununa Hoþgeldiniz~~"    << endl;
		cout << "         ===================================" << endl;
		cout << endl;
		tahta.yazdir();

		int tur = 1; //Hangi oyuncunun sýrasý olduðunu tutan deðiþken
		while (true) {
			int x, y;
			Oyuncu* oyuncu; //Hangi oyuncunun sýrasý olduðunu tutan nesne

			if (tur % 2 == 1) { //Turun 1,3,5,... olduðu durumlar
				oyuncu = oyuncu1;
			}
			else { //Turun 2,4,6,... olduðu durumlar
				oyuncu = oyuncu2;
			}
			cout << endl;
			cout << oyuncu->getKarakter() << " oyuncusu sýrasý. X koordinatýný giriniz: ";
			cin >> x;

			cout << oyuncu->getKarakter() << " oyuncusu sýrasý. Y koordinatýný giriniz: ";
			cin >> y;

			//Hücre doldurulmaya çalýþýlýr
			if (!oyuncu->hucreDoldur(tahta, x, y)) { //Hücre doldrulmadýysa
				cout << "Bu hücre zaten dolu. Lütfen baþka bir hücre seçiniz." << endl;
				continue; //Döngünün baþýna dön
			}

			//Tahtayý ekrana yazdýr
			tahta.yazdir();

			//Kazanan olup olmadýðýný kontrol et
			char kazanan = tahta.kazanan();
			if (kazanan != ' ') { //Kazanan var
				cout << kazanan << " kazandý!" << endl;
				break; // Oyunu bitir
			}

			//Boþ hücre kalýp kalmadýðýný kontrol et
			if (!tahta.bosVar()) { //Boþ hücre yoksa
				cout << "Berabere! " << endl;
				break; //Oyunu bitir
			}

			tur++; //Bir sonraki oyuncunun sýrasý
		}
	}
};


int main() {
	setlocale(LC_ALL, "Turkish");

	Oyuncu oyuncu1('X'), oyuncu2('O'); //Oyuncularý oluþtur
	Oyun oyun(oyuncu1, oyuncu2); //Oyun oluþtur

	oyun.oyna(); //Oyunu baþlat

	return 0;

}