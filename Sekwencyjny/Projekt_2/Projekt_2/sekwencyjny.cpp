#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <vector>

using namespace std;

void genPattern(int len, int k, string fName) {
	ofstream myfile;
	myfile.open("patterns//" + fName + ".txt");
	string s;
	int i, j;
	for(j = 0; j < k; j++) {
		s = "";
		//int tmp = (rand() % len) + 1;
		for(i = 0; i < len; i++) 
			s += char(65 + (rand() % 26));
		myfile << s << endl;
	}
	myfile.close();
}

void genText(int len, string fName) {
	ofstream myfile;
	myfile.open("texts//" + fName + ".txt");
	for(int i = 0; i < len; i++)
		myfile << char(65 + (rand() % 26));
	myfile.close();
}

void test(string pName, string tName, int k) {
	ifstream pFile, tFile;
	ofstream rFile, mFile;
	clock_t start, stop;
	vector<string> patt;
	vector<int> result;
	string text, tmp, p;
	int i, j, l;
	double time = 0.0;

	pFile.open("patterns//" + pName + ".txt");
	tFile.open("texts//" + tName + ".txt");
	rFile.open("results//result.txt");
	mFile.open("results//matching.txt");

	while(getline(pFile, tmp)) {
		patt.push_back(tmp);
		result.push_back(0);
	}
	pFile.close();

	tFile >> text;
	tFile.close();

	for(l = 0; l < k; l++) {
		for(i = 0; i < patt.size(); i++)
			result.at(i) = 0;
		start = clock();
		for(i = 0; i < patt.size(); i++) {
			p = patt.at(i);
			int range = text.length() - (p.length() - 1);
			for(j = 0; j < range; j++)
				if (p == text.substr(j, p.length()))
					result.at(i)++;			
		}
		stop = clock();
		mFile << "Iteracja: " << l << endl;
		for(i = 0; i < result.size(); i++)
			mFile << patt.at(i) << " " << result.at(i) << endl;
		mFile << endl;
		rFile << l << "\t" << (stop - start)/1000.0 << endl;
		time += (stop - start)/1000.0;
	}
	time /= k;
	rFile << "Sredni czas: " << time;
	rFile.close();
	mFile.close();
	cout << "Sredni czas przetwarzania wynosi "<< time <<" sekund\n";;
}

int main() {
	int dec = -1;
	while(dec != 0) {
		cout << "Co chcesz zrobic?\n";
		cout << "1 - wygeneruj wzorce\n" << "2 - wygeneruj tekst\n" << "3 - rozpocznij test\n" << "0 - wyjdz\n";
		cin >> dec;

		switch (dec) {
		case 1: {
			int len, k;
			string fName;
			cout << "Podaj maksymalna dlugosc wzorca: ";
			cin >> len;
			cout << "Podaj liczbe wzorcow: ";
			cin >> k;
			cout << "Podaj nazwe pliku, do ktorego zostania zapisane wzorce (bez rozszerzenia): ";
			cin >> fName;
			genPattern(len, k, fName);
		} break;

		case 2: {
			int len;
			string fName;
			cout << "Podaj dlugosc tekstu: ";
			cin >> len;
			cout << "Podaj nazwe pliku, do ktorego zostania zapisany tekst (bez rozszerzenia): ";
			cin >> fName;
			genText(len, fName);
		} break;

		case 3: {
			string pName, tName;
			int k;
			cout << "Podaj nazwe pliku z wzorcami (bez rozszerzenia): ";
			cin >> pName;
			cout << "Podaj nazwe pliku z tekstem (bez rozszerzenia): ";
			cin >> tName;
			cout << "Liczba powtorzen: ";
			cin >> k;
			test(pName, tName, k);
		} break;

		case 0: break;

		default:
			cout << "Podano nieprawidlowa wartosc\n";
			break;
		}
	}

	return 0;
}