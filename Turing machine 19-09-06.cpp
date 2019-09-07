// 19-09-05 Turing Machine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

void print(string zymejimas, string juosta, string failas, int pozicija){
	system("cls");
	cout << "Failas:" << failas << endl;
	cout << pozicija << endl;
	cout << juosta << endl;
	cout << zymejimas<<endl;
	sleep_for(0.5s);
}
void judejimas(string kryptis, string &juosta, string &zymejimas, long long &pozicija) {
	int back = pozicija;
		if (kryptis == "R")
				{
					pozicija++;
					zymejimas[pozicija] = '^';

					zymejimas[back] = '_';
					cout << zymejimas << endl;
					sleep_for(0.5s);
				}
				else
				{
					pozicija--;
					zymejimas[pozicija] = '^';
					zymejimas[back] = '_';
					cout << zymejimas << endl;
					sleep_for(0.5s);
				}
}
struct komandos {
	int pradzia_busenos = 0;
	int busena = 0;
	string esamas_simb;
	string naujas_simb;
	string kryptis;
	int nauja_busena;
};
int main() {
	vector<komandos> eilute;
	string zymejimas = "";
	srand(time(NULL));
	int a, busenos_vieta(0), past_busena(0);
	long long i(0), pozicija(0);
	string juosta; //pvz 00000000000000000000000*0000
	string failas = "4.txt";
	//_______________________^kintamieji^_____________v skaitymas v______________________________//


	ifstream rf(failas);
	rf >> pozicija;
	rf >> juosta;
	while (rf >> a) //Nuskaito komandas, isimena busenu pradzios koordinates
	{
		eilute.push_back(komandos());
		rf >> eilute[i].esamas_simb >> eilute[i].naujas_simb >> eilute[i].kryptis >> eilute[i].nauja_busena;
		eilute[i].busena = a;
		if (eilute[i].busena != past_busena) //nustato naujos busenos eilutes pradine pozicija
		{
			eilute[i].pradzia_busenos = busenos_vieta;
		}
		if (i > 0 && past_busena == eilute[i].busena)
		{
			eilute[i].pradzia_busenos = eilute[i - 1].pradzia_busenos;
		}
		past_busena = eilute[i].busena;
		i++;
		busenos_vieta++;
		
	}
	//----------------------------------------------------------------//
	for (i = 0; i < juosta.length(); i++)
		zymejimas += "_";
	zymejimas[pozicija] = '^';
	print(zymejimas, juosta, failas, pozicija);


	//_______________Vykdymas__________________________//

	for (i = 0; i < eilute.size(); i++)
	{
		judejimas(eilute[i].kryptis, juosta, zymejimas, pozicija);
	}
	//_____________________________________________________________________________//
	for (i = 0; i < eilute.size(); i++)
	{
		cout << eilute[i].busena << " " << eilute[i].esamas_simb << " " << eilute[i].naujas_simb << " " << eilute[i].kryptis << " " << eilute[i].nauja_busena << endl;
	}
	cout << "Busenos pradziu koord: ";
	for (i = 0; i < eilute.size(); i++)
	{
		cout << eilute[i].pradzia_busenos << ", ";
	}
	//main(); grizta atgal programa i pradzia
}
/*
00000000000000000000000*0000
0 0 0 R 0
0 1 1 R 0
0 * *L 1
1 0 1 R 0
1 1 0 L 1*/


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

