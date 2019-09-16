#include<iomanip>
using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.

void judejimas(char kryptis, string& juosta, string& zymejimas, long long& pozicija) {
	int back = pozicija;
	if (kryptis == 'R')
	{
		pozicija++;
		if (pozicija < 0 || pozicija >= juosta.length())
		{
			juosta = "end_of_tape";
		}
		else{
		zymejimas[pozicija] = '^';
		zymejimas[back] = '_';
		}
		
		//cout << zymejimas << endl;
	}
	else
	{
		pozicija--;
		if (pozicija < 0 || pozicija >= juosta.length())
		{
			juosta = "end_of_tape";
		}
		else {
			zymejimas[pozicija] = '^';
			zymejimas[back] = '_';
		}
		
		//cout << zymejimas << endl;
	}

}