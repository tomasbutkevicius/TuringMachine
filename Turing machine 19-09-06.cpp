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
#include <algorithm>
#include <condition_variable>
#include <mutex> //lock() unlock()
#include "judejimas.h"
using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;
mutex m;
#define THREADSTREAM

#include <iostream>
#include <sstream>
#include <mutex>


#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

	void cls()
{
	// Get the Win32 handle representing standard output.
	// This generally only has to be done once, so we make it static.
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD topLeft = { 0, 0 };

	// std::cout uses a buffer to batch writes to the underlying console.
	// We need to flush that to the console because we're circumventing
	// std::cout entirely; after we clear the console, we don't want
	// stale buffered text to randomly be written out.
	std::cout.flush();

	// Figure out the current width and height of the console window
	if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
		// TODO: Handle failure!
		abort();
	}
	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

	DWORD written;

	// Flood-fill the console with spaces to clear it
	FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

	// Reset the attributes of every character to the default.
	// This clears all background colour formatting, if any.
	FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

	// Move the cursor back to the top left for the next sequence of writes
	SetConsoleCursorPosition(hOut, topLeft);
}
	void setCursorPosition(int x, int y)
	{
		static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		std::cout.flush();
		COORD coord = { (SHORT)x, (SHORT)y };
		SetConsoleCursorPosition(hOut, coord);
	}
	struct komandos {
	int pradzia_busenos = 0;
	int galas_busenos = 0;
	int busena = 0;
	char esamas_simb;
	char naujas_simb;
	char kryptis;
	string nauja_busena;
};
void struct_print(komandos eilute) {
	cout << eilute.busena << " " << eilute.esamas_simb << " " << eilute.naujas_simb << " " << eilute.kryptis << " " << eilute.nauja_busena << endl;
}

string random_file() {
	int skaicius = rand() % 4 + 1;
	string failas = to_string(skaicius) + ".txt";
	return failas;
}
void print(int i, string zymejimas, string juosta, string failas, int pozicija, int spausdint_x, int spausdint_y) {
	m.lock();
	setCursorPosition(0, spausdint_y);
	if (juosta == "end_of_tape")
		cout << "";
	else {
		setCursorPosition(spausdint_x, spausdint_y -1);
		cout << failas << endl;
		setCursorPosition(spausdint_x, spausdint_y);
		cout << juosta <<endl;
		setCursorPosition(spausdint_x, spausdint_y+1);
		cout << zymejimas <<endl;
	}
	m.unlock();
	sleep_for(0.01s);
}
void vykdymas(string failas, int spausdint_x, int spausdint_y) {
	
	vector<komandos> eilute;
	string zymejimas = "";
	srand(time(NULL));
	int a(0), busenos_vieta(0), past_busena(0);
	long long i(0), pozicija(0);
	//input:
	int get_file(1);
	string juosta; //pvz 00000000000000000000000*0000
	int thread_count(0);
	//INPUT ^^^^^^ ____________________________
	ifstream rf(failas);



	//_______________________^kintamieji^_____________v skaitymas v______________________________//



	rf >> pozicija;
	pozicija;
	rf >> juosta;
	while (rf >> a) //Nuskaito komandas
	{
		eilute.push_back(komandos());
		rf >> eilute[i].esamas_simb >> eilute[i].naujas_simb >> eilute[i].kryptis >> eilute[i].nauja_busena;
		eilute[i].busena = a;
		i++;
	}
	for (i = 0; i < eilute.size() - 1; i++)
	{
		for (int j = i + 1; j < eilute.size(); j++)
		{
			if (eilute[i].busena > eilute[j].busena)  //surikiuoja
			{
				komandos x;
				x = eilute[i];
				eilute[i] = eilute[j];
				eilute[j] = x;

			}
		}
	}
	//----------------------------------------------------------------//
	for (i = 0; i < eilute.size(); i++)
	{
		if (eilute[i].busena != past_busena) //nustato naujos busenos eilutes pradine pozicija
		{
			eilute[i].pradzia_busenos = busenos_vieta;
		}
		if (i > 0 && past_busena == eilute[i].busena)
		{
			eilute[i].pradzia_busenos = eilute[i - 1].pradzia_busenos;
		}
		past_busena = eilute[i].busena;
		busenos_vieta++;
	}

	for (i = 0; i < eilute.size() - 1; i++)
	{
		if (eilute[i].pradzia_busenos != eilute[i + 1].pradzia_busenos)
		{
			eilute[i].galas_busenos = eilute[i + 1].pradzia_busenos - 1;
			int j = i - 1;
			while (eilute[j].galas_busenos == 0)
			{
				eilute[j].galas_busenos = eilute[i].galas_busenos;
				if (j == 0)
					break;
				j--;
			}
		}
	}
	for (i = 0; i < eilute.size(); i++)
	{
		if (eilute[i].galas_busenos == 0)
			eilute[i].galas_busenos = eilute.size() - 1;
	}
	for (i = 0; i < juosta.length(); i++)
		zymejimas += "_";
	zymejimas[pozicija] = '^';

	print(i, zymejimas, juosta, failas, pozicija, spausdint_x, spausdint_y);
	//_______________Vykdymas__________________________//
	i = 0;
	while (eilute[i].nauja_busena != "X" && juosta!="end_of_tape")
	{
		int nauja_busena = stoi(eilute[i].nauja_busena);
		if (eilute[i].esamas_simb == juosta[pozicija]) //Kai esamas simbolis sutampa su juosteles simboliu
		{
			if (eilute[i].esamas_simb != eilute[i].naujas_simb)  //Kai esamas simbolis nesutampa su nauju
			{
				juosta[pozicija] = eilute[i].naujas_simb;
				judejimas(eilute[i].kryptis, juosta, zymejimas, pozicija);
				if(juosta!="end_of_tape")
				print(i, zymejimas, juosta, failas, pozicija, spausdint_x, spausdint_y);
				//struct_print(eilute[i]);
				if (eilute[i].busena != nauja_busena)    //Kai yra nauja busena
				{
					for (int j = 0; j < eilute.size(); j++)
					{
						if (eilute[j].busena == nauja_busena)
							i = eilute[j].pradzia_busenos;
					}
				}
			}

			else  //Kai esamas simbolis sutampa su nauju
			{
				judejimas(eilute[i].kryptis, juosta, zymejimas, pozicija);
				if (eilute[i].busena != nauja_busena)
				{
					for (int j = 0; j < eilute.size(); j++)
					{
						if (eilute[j].busena == nauja_busena)
							i = eilute[j].pradzia_busenos;
					}
				}
			}
		}
		else if (eilute[i].esamas_simb != juosta[pozicija]) //Kai esamas simbolis nesutampa su juosteles simboliu
		{
			if (eilute[i].galas_busenos == i)
			{
				i = eilute[i].pradzia_busenos;
			}
			else{
				i++;
				//cout << "iesko" << endl;
			}
		}
		//__________________vvv___Print___vvv________________________________________//
		if (juosta == "end_of_tape")
		{
			spausdint_y += 4;
		}
		print(i, zymejimas, juosta, failas, pozicija, spausdint_x, spausdint_y);
	}
}

int main() {
	//https://stackoverflow.com/questions/18238747/c-holding-a-number-of-threads
	//https://www.youtube.com/watch?v=n5Pst7CY2vo
	//https://stackoverflow.com/questions/34842526/update-console-without-flickering-c  --> update console without flickering
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	srand(time(NULL));
	int thread_count;
	int spausdint_y = 5;
	int spausdint_x = 0;
	cout << "alt+f4 to exit" << endl;
	cout << "Max 10 threads stable" << endl;
	cout << "How many threads: ";
	cin >> thread_count;
	cout << endl;
	int get_file(0);
	string failas[100];
	vector<thread> thread_boy;
	for (int j = 0; j < thread_count; j++)
	{
		cout << "Enter >0 for random file; 0 to enter your file name" << endl;
				cin >> get_file;
				if (get_file)
				{
					failas[j] = random_file();
				}
				else
				{
					string name;
					cout << "Enter your file (1.txt)" << endl;
					cin >> name;
					failas[j] = name;
				}
				ifstream rf(failas[j]);
				if (rf.fail()) {
					//File does not exist code here
					cout << "File does not exist. Wait to restart." << endl;
					sleep_for(2s);
					system("cls");
					main();
				}
	}
	system("cls");

	for (int j = 0; j < thread_count; j++)
	{
		thread_boy.push_back(thread(vykdymas, failas[j], spausdint_x, spausdint_y));
		spausdint_y += 10;
		if (j == 4) {
			spausdint_x += 100;
			spausdint_y = 5;
		}
		//sleep_for(0.5s);
	}
	for (auto j = thread_boy.begin(); j != thread_boy.end(); ++j)
	{
		j->join();
	}
	main();
}


