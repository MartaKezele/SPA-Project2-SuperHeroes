#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
#include<map>
#include<chrono>
#include<list>
#include<algorithm>
#include<queue>
#include<ctime>
#include<unordered_map>
#include<unordered_set>
#include"Superhero.h"
using namespace std;
using namespace::chrono;

double convert(string& temp) 
{

	if (temp == "")
	{
		return -1;
	}
	else
	{
		stringstream converter(temp);
		double broj;
		converter >> broj;
		return broj;
	}
}

void load(ifstream& in, vector<Superhero>& v)
{
	string line;
	getline(in, line);
	while (getline(in, line))
	{
		stringstream ss(line);

		string name;
		getline(ss, name, ',');

		string alignment;
		getline(ss, alignment, ',');

		string temp;
		getline(ss, temp, ',');
		double intelligence = convert(temp);

		getline(ss, temp, ',');
		double strength = convert(temp);

		getline(ss, temp, ',');
		double speed = convert(temp);

		getline(ss, temp, ',');
		double durability = convert(temp);

		getline(ss, temp, ',');
		double power = convert(temp);

		getline(ss, temp, ',');
		double combat = convert(temp);

		getline(ss, temp, ',');
		double total = convert(temp);

		v.emplace_back(name, alignment, intelligence, strength, speed, durability, power, combat, total);
	}
}

void izbornik(int& izbor)
{
	system("CLS");
	cout << "Izbornik:" << endl;

	cout << "1. Pretraga po imenu" << endl;
	cout << "2. Prikaz po brzini" << endl;
	cout << "3. Kopiranje u novi vektor" << endl;
	cout << "4. Prikaz po strani" << endl;
	cout << "5. Insertion vs Shell" << endl;
	cout << "6. Lets play guess" << endl;
	cout << "7. Monkey Play" << endl;
	cout << "8. The Quick Dance" << endl;
	cout << "9. Pretraga po imenu" << endl;
	cout << "10. Vizualiziraj" << endl;
	cout << "11. Izrada imena iz imena" << endl;
	cout << "12. Zavrsetak programa" << endl << endl;

	cout << "Odaberite jednu opciju iz izbornika. (Upisite broj opcije): ";
	cin >> izbor;
	cin.ignore();
}

void poluizbornik(bool& povratak)
{
	cout << endl << "Upisite 1 za povratak na izbornik ili 0 za zavrsetak programa: ";
	cin >> povratak;
	cin.ignore();
}

// IZBOR 1

void copy_to_map(vector<Superhero>& v, map<string, Superhero>& m)
{
	for (int i = 0; i < v.size(); i++)
	{
		m.insert(pair<string, Superhero>(v[i].get_name(), v[i]));
	}

}

void pretraga_po_imenu(vector<Superhero>& v)
{
	system("CLS");
	cout << "1. PRETRAGA PO IMENU" << endl << endl;

	cout << "Upisite ime superheroja: ";
	string ime;
	getline(cin, ime);

	// mapa
	map<string, Superhero> m;
	copy_to_map(v, m);
	bool found = 1;
	auto begin = high_resolution_clock::now();

	try
	{
		m.at(ime);
	}
	catch (const std::out_of_range& e)
	{
		cout << "Nema superheroja ovog imena." << endl;
		found = 0;
	}

	auto end = high_resolution_clock::now();
	auto mapa = duration_cast<microseconds>(end - begin).count();

	// ispis podataka o (ne)naðenom superheroju
	if(found) cout << m[ime].to_string() << endl;

	// lista
	list<Superhero> l(v.begin(), v.end());
	begin = high_resolution_clock::now();

	for (auto it = l.begin(); it != l.end(); ++it)
	{
		if (it->get_name() == ime)
		{
			break;
		}
	}

	end = high_resolution_clock::now();
	auto lista = duration_cast<microseconds>(end - begin).count();

	// vektor
	begin = high_resolution_clock::now();

	for (int i = 0; i < v.size(); i++)
	{
		if (v[i].get_name() == ime)
		{
			break;
		}
	}

	end = high_resolution_clock::now();
	auto vektor = duration_cast<microseconds>(end - begin).count();

	// ispis top ljestvice brzine kontejnera
	cout << endl << "ljestvica brzine trazenja ovisno o vrsti kontenjera (izrazeno u mikrosekundama): " << endl;
	if (mapa <= vektor && mapa <= lista)
	{
		cout << "1. mapa: " << mapa << endl;

		if (vektor <= lista)
		{
			cout << "2. vektor: " << vektor << endl;
			cout << "3. lista: " << lista << endl;
		}
		else {
			cout << "2. lista: " << lista << endl;
			cout << "3. vektor: " << vektor << endl;
		}
	}
	else if (vektor <= mapa && vektor <= lista)
	{
		cout << "1. vektor: " << vektor << endl;

		if (mapa <= lista)
		{
			cout << "2. mapa: " << mapa << endl;
			cout << "3. lista: " << lista << endl;
		}
		else {
			cout << "2. lista: " << lista << endl;
			cout << "3. mapa: " << mapa << endl;
		}
	}
	else if (lista <= mapa && lista <= vektor)
	{
		cout << "1. lista: " << lista << endl;

		if (mapa <= vektor)
		{
			cout << "2. mapa: " << mapa << endl;
			cout << "3. vektor: " << vektor << endl;
		}
		else {
			cout << "2. vektor: " << vektor << endl;
			cout << "3. mapa: " << mapa << endl;
		}
	}
}

// IZBOR 2

struct BrziImaPrioritet
{
	bool operator() (Superhero& s1, Superhero& s2)
	{
		return s1.get_speed() < s2.get_speed();
	}
};

struct SporijiImaPrioritet
{
	bool operator() (Superhero& s1, Superhero& s2)
	{
		return s1.get_speed() > s2.get_speed();
	}
};

void prikaz_po_brzini(vector<Superhero>& v)
{
	system("CLS");
	cout << "2. PRIKAZ PO BRZINI" << endl << endl;

	cout << "Zelite li prikaz od slabijih prema jacim (1) ili od jacih prema slabijim (2) super junacima (svojstvo Speed)?" << endl;
	cout << "unesite broj: ";
	int izbor;
	cin >> izbor;

	cout << endl;

	if (izbor == 1)
	{
		cout << "Brzina" << "\t\t\t\t\t\t" << "Ime" << endl;
		priority_queue< Superhero, vector<Superhero>, SporijiImaPrioritet> pq(v.begin(), v.end());

		while (!pq.empty())
		{
			Superhero temp = pq.top();
			if (temp.get_speed() < 0)
			{
				cout << "Nije upisana brzina za ovog superheroja.\t" << temp.get_name() << endl;
			}
			else	cout << temp.get_speed() << "\t" << temp.get_name() << endl;
			pq.pop();
		}
	}
	else if (izbor == 2)
	{
		cout << "Brzina" << "\t" << "Ime" << endl;
		priority_queue< Superhero, vector<Superhero>, BrziImaPrioritet> pq(v.begin(), v.end());

		while (!pq.empty())
		{
			Superhero temp = pq.top();
			if (temp.get_speed() < 0)
			{
				cout << "Nije upisana brzina za ovog superheroja.\t" << temp.get_name() << endl;
			}
			else	cout << temp.get_speed() << "\t" << temp.get_name() << endl;
			pq.pop();
		}
	}
}

// IZBOR 3

void kopiranje_u_novi_vektor(vector<Superhero>& v)
{
	system("CLS");
	cout << "4. KOPIRANJE U NOVI VEKTOR" << endl << endl;

	multimap<double, Superhero> m;
	for (int i = 0; i < v.size(); i++)
	{
		m.insert(pair<double, Superhero>(v[i].get_total(), v[i]));
	}

	vector<Superhero> novi_v;

	bool dalje;
	do
	{
		double min;
		cout << "Unesite min vrijednost: ";
		cin >> min;

		double max;
		cout << "Unesite max vrijednost: ";
		cin >> max;

		for (auto it = m.upper_bound(min); it != m.lower_bound(max); ++it)
		{
			novi_v.push_back(it->second);
		}

		cout << "Zelite li ponovo unjeti min i max vrijednosti za \"Total\"?" << endl;
		cout << "Unesite 1 ako zelite ponovo unjeti vrijednosti, a 0 ako ne zelite: ";
		cin >> dalje;

	} while (dalje);

	for (int i = 0; i < novi_v.size(); i++) {

		cout << novi_v[i].get_total() << "\t" << novi_v[i].get_name() << endl;

	}
}

// IZBOR 4

struct DobarImaPrioritet
{
	bool operator() (Superhero& s1, Superhero& s2)
	{
		int s1_priority;
		int s2_priority;

		if (s1.get_alignment() == "good") s1_priority = 3;
		else if (s1.get_alignment() == "neutral") s1_priority = 2;
		else if (s1.get_alignment() == "bad") s1_priority = 1;
		else if (s1.get_alignment() == "") s1_priority = 0;

		if (s2.get_alignment() == "good") s2_priority = 3;
		else if (s2.get_alignment() == "neutral") s2_priority = 2;
		else if (s2.get_alignment() == "bad") s2_priority = 1;
		else if (s2.get_alignment() == "") s2_priority = 0;

		if (s1_priority == s2_priority)
		{
			if (s1.get_name() < s2.get_name())
			{
				s2_priority += 1;
			}
		}

		return s1_priority < s2_priority;
	}
};

void prikaz_po_strani(vector<Superhero>& v)
{
	system("CLS");
	cout << "4. PRIKAZ PO STRANI" << endl << endl;

	priority_queue< Superhero, vector<Superhero>, DobarImaPrioritet> pq(v.begin(), v.end());

	while (!pq.empty())
	{
		Superhero temp = pq.top();
		if (temp.get_alignment() == "")
		{
			cout << "Nije upisana strana za ovog superheroja.\t" << temp.get_name() << endl;
		}
		else	cout << temp.get_alignment() << "\t" << temp.get_name() << endl;
		pq.pop();
	}
}

// IZBOR 5

int insertion_sort(vector<Superhero>& v)
{
	int broj_zamjena = 0;
	for (int i = 1; i < v.size(); i++) { // Prvog preskaèemo.
		for (int j = i; j > 0 && v[j - 1].get_name() < v[j].get_name(); j--) {
			swap(v[j], v[j - 1]);
			broj_zamjena++;
		}
	}

	return broj_zamjena;
}

int shell_sort(vector<Superhero>& v)
{
	int broj_zamjena = 0;
	for (int step = v.size() / 2; step > 0; step /= 2) {
		for (int i = step; i < v.size(); i++) {
			Superhero temp = v[i];
			for (int j = i; j >= step && v[j - step].get_name() < temp.get_name(); j -= step) {
				swap(v[j], v[j - step]);
				broj_zamjena++;
			}
		}
	}
	return broj_zamjena;
}

void insertion_vs_shell(vector<Superhero>& v)
{
	system("CLS");
	cout << "5. INSERTION VS SHELL" << endl << endl;

	vector<Superhero> v1(v.begin(), v.end());
	vector<Superhero> v2(v.begin(), v.end());

	// insertion sort
	cout << "Insertion sort" << endl;
	auto begin = high_resolution_clock::now();
	cout << "broj zamjena: " << insertion_sort(v1) << endl;
	auto end = high_resolution_clock::now();
	cout << "duration: " << duration_cast<milliseconds>(end - begin).count() << "ms" << endl << endl;

	// shell sort
	cout << "Shell sort" << endl;
	begin = high_resolution_clock::now();
	cout << "broj zamjena: " << shell_sort(v2) << endl;
	end = high_resolution_clock::now();
	cout << "duration: " << duration_cast<milliseconds>(end - begin).count() << "ms" << endl;
}

// IZBOR 6

int get_rnd(int min, int max) {

	return rand() % (max - min + 1) + min;
}

void lets_play_guess()
{
	system("CLS");
	cout << "6. LET'S PLAY GUESS" << endl << endl;

	srand(time(nullptr));
	int n = get_rnd(1, 100000000);

	cout << "Izgeneriran je slucajni broj " << n << "." << endl;
	cout << "Sto mislite koliko ce trajati razbacivanje, sortiranje i binarno pretrazivanje vektora u potrazi za brojem 13?" << endl;
	cout << "Upisite broj u mikrosekundama: ";
	double pretpostavka;
	cin >> pretpostavka;

	vector<int> v;
	for (int i = 0; i < n; i++) {
		v.push_back(i + 1);
	}
	random_shuffle(v.begin(), v.end());

	auto begin = chrono::high_resolution_clock::now();

	// sortiranje

	sort(v.begin(), v.end());

	// binarno trazenje broja 13

	binary_search(v.begin(), v.end(), 13);

	auto end = chrono::high_resolution_clock::now();
	auto trajanje = duration_cast<microseconds>(end - begin).count();

	cout << endl << "Trajanje: " << trajanje << " mikrosekundi" << endl;
	cout << "Razlika izmedju vase pretpostavke i stvarnog vremena trajanja: " << abs(trajanje - pretpostavka) << " mikrosekundi" << endl;
}

// IZBOR 7

bool comp(Superhero& a, Superhero& b)
{
	if (a.get_name() < b.get_name())
	{
		return true;
	}
	return false;
}

void monkey_play(vector<Superhero>& v)
{
	system("CLS");
	cout << "7. MONKEY PLAY" << endl << endl;

	ofstream out("permutacije.txt");
	if (!out)
	{
		cout << "Greska kod otvaranja datoteke." << endl;
		return;
	}

	vector<Superhero> v1;
	srand(time(nullptr));

	out << "pocetni (slucajno generirani) redoslijed" << endl;
	for (int i = 0; i < 6; i++)
	{
		v1.push_back(v[get_rnd(0, v.size() - 1)]);
		out << v1.back().get_name() << endl;
	}
	out << endl << endl;

	int k = 1;
	while (next_permutation(v1.begin(), v1.end(), comp))
	{
		out << "permutacija " << k << "." << endl;
		for (int i = 0; i < v1.size(); i++)
		{
			out << v1[i].get_name() << endl;
		}
		out << endl << endl;
		k++;
	}

	out.close();

	cout << "Superheroji sortirani po imenu u padajucem redoslijedu: " << endl;
	reverse(v1.begin(), v1.end());
	for (int i = 0; i < v1.size(); i++)
	{
		cout << v1[i].get_name() << endl;
	}

	cout << endl << "U datoteci \"permutacije.txt\" nalazi se popis svih permutacija." << endl;
}

// IZBOR 8

void quick_sort(Superhero* data, int left, int right, int brojac, ofstream& out) 
{
	// svaki put kad je pozvana funkcija povecaj brojac za 1 (napravljeno u pozivu) i upisi redak u datoteku
	for (int i = 0; i < brojac; i++)
	{
		out << "#";
	}
	out << endl;

	// svaki put kad je zavrsila rekurzija smanji brojac za 1 i upisi redak u datoteku
	if (right <= left) 
	{ 
		brojac -= 1;
		for (int i = 0; i < brojac; i++)
		{
			out << "#";
		}
		out << endl;
		return; 
	} 

	Superhero& pivot = data[left]; 
	int i = left + 1; 
	int j = right; 
	while (i <= j && i <= right && j > left) 
	{
		while (data[i].get_total() <= pivot.get_total() && i <= right) 
		{ 
			// Pomièemo i u desno. 
			i++; 
		} 
		while (data[j].get_total() > pivot.get_total() && j > left) 
		{ 
			// Pomièemo j u lijevo. 
			j--; 
		} 
		if (i < j) 
		{ 
			// Zamijenimo ih. 
			swap(data[i], data[j]); 
		} 
	} 
	swap(pivot, data[j]); 
	quick_sort(data, left, j - 1, brojac+1, out); 
	quick_sort(data, j + 1, right, brojac+1, out); 
}

void the_quick_dance(vector<Superhero>& v)
{
	system("CLS");
	cout << "8. THE QUICK DANCE" << endl << endl;

	cout << "Upisite broj elemenata: ";
	int n;
	cin >> n;

	Superhero* v1 = new Superhero[n];

	srand(time(nullptr));
	for (int i = 0; i < n; i++)
	{
		v1[i] = v[get_rnd(0, v.size() - 1)];
	}

	ofstream out("the_quick_dance.txt");
	if (!out)
	{
		cout << "Greska kod otvaranja datoteke." << endl;
		return;
	}

	quick_sort(v1, 0, n - 1, 1, out);

	cout << "Vas quick dance se nalazi u datoteci \"the_quick_dance.txt\"." << endl;

	delete[] v1;
}

// IZBOR 9

void pretraga_po_imenu_unordered_map(vector<Superhero>& v)
{
	system("CLS");
	cout << "9. PRETRAGA PO IMENU" << endl << endl;

	string ime;
	cout << "Upisite ime superjunaka kojeg zelite pronaci: ";
	getline(cin, ime);

	// unordered map
	unordered_map<string, Superhero> um;
	for (int i = 0; i < v.size(); i++)
	{
		string key = v[i].get_name();
		Superhero val = v[i];
		um.insert({ key, val });
	}

	auto begin = high_resolution_clock::now();
	bool found = 1;
	try
	{
		um.at(ime);
	}
	catch (const std::out_of_range& e)
	{
		cout << "Nema superheroja ovog imena." << endl;
		found = 0;
	}
	if (found)
	{
		cout << um[ime].to_string() << endl;
	}
	auto end = high_resolution_clock::now();
	auto mapa = duration_cast<microseconds>(end - begin).count();

	// lista
	list<Superhero> l(v.begin(), v.end());
	begin = high_resolution_clock::now();

	for (auto it = l.begin(); it != l.end(); ++it)
	{
		if (it->get_name() == ime)
		{
			break;
		}
	}

	end = high_resolution_clock::now();
	auto lista = duration_cast<microseconds>(end - begin).count();

	// vektor
	begin = high_resolution_clock::now();

	for (int i = 0; i < v.size(); i++)
	{
		if (v[i].get_name() == ime)
		{
			break;
		}
	}

	end = high_resolution_clock::now();
	auto vektor = duration_cast<microseconds>(end - begin).count();

	// ispis top ljestvice brzine kontejnera
	cout << endl << "ljestvica brzine trazenja ovisno o vrsti kontenjera (izrazeno u mikrosekundama): " << endl;
	if (mapa <= vektor && mapa <= lista)
	{
		cout << "1. unordered mapa: " << mapa << endl;

		if (vektor <= lista)
		{
			cout << "2. vektor: " << vektor << endl;
			cout << "3. lista: " << lista << endl;
		}
		else {
			cout << "2. lista: " << lista << endl;
			cout << "3. vektor: " << vektor << endl;
		}
	}
	else if (vektor <= mapa && vektor <= lista)
	{
		cout << "1. vektor: " << vektor << endl;

		if (mapa <= lista)
		{
			cout << "2. unordered mapa: " << mapa << endl;
			cout << "3. lista: " << lista << endl;
		}
		else {
			cout << "2. lista: " << lista << endl;
			cout << "3. unordered mapa: " << mapa << endl;
		}
	}
	else if (lista <= mapa && lista <= vektor)
	{
		cout << "1. lista: " << lista << endl;

		if (mapa <= vektor)
		{
			cout << "2. unordered mapa: " << mapa << endl;
			cout << "3. vektor: " << vektor << endl;
		}
		else {
			cout << "2. vektor: " << vektor << endl;
			cout << "3. unordered mapa: " << mapa << endl;
		}
	}
}

// IZBOR 10

void vizualiziraj(vector<Superhero>& v)
{
	system("CLS");
	cout << "10. VIZUALIZACIJA" << endl << endl;

	unordered_multimap<string, Superhero> umm;
	for (int i = 0; i < v.size(); i++)
	{
		string key = v[i].get_name();
		Superhero val = v[i];
		umm.insert({ key, val });
	}

	for (int i = 0; i < umm.bucket_count(); i++) 
	{
		cout << "Bucket: " << i << ": ";
		if (umm.bucket_size(i) == 0)
		{
			cout << "[EMPTY]" << endl;
		}
		else
		{
			int brojac = 1;
			for (auto it = umm.begin(i); it != umm.end(i); ++it)
			{
				if (brojac == umm.bucket_size(i))
				{
					cout << it->first << endl;
				}
				else cout << it->first << " -- ";

				brojac += 1;
			}
		}
	}
}

// IZBOR 11

void izrada_imena_iz_imena()
{
	system("CLS");
	cout << "11. IZRADA IMENA IZ IMENA" << endl << endl;

	cout << "Ucitajte ime prvog superheroja: ";
	string ime1;
	getline(cin, ime1);

	cout << "Ucitajte ime drugog superheroja: ";
	string ime2;
	getline(cin, ime2);

	unordered_multiset<char> ums1;
	for (int i = 0; i < ime1.length(); i++)
	{
		char c = tolower(ime1[i]);
		ums1.insert(c);
	}

	unordered_multiset<char> ums2;
	for (int i = 0; i < ime2.length(); i++)
	{
		char c = tolower(ime2[i]);
		ums2.insert(c);
	}

	for (auto it = ums2.begin(); it != ums2.end(); ++it) 
	{ 
		if (ums1.count(*it) < ums2.count(*it))
		{
			cout << endl << "NIJE MOGUCE kreirati ime \"" << ime2 << "\" pomocu imena \"" << ime1 << "\"." << endl;
			return;
		}
	}

	cout << endl << "MOGUCE JE kreirati ime \"" << ime2 << "\" pomocu znakova iz imena \"" << ime1 << "\"." << endl;
}


int main()
{
	ifstream in("SPA_PROJ_003_HEROES_data_1.csv");
	if (!in)
	{
		cout << "Greska kod otvaranja datoteke." << endl;
		return -1;
	}

	vector<Superhero> v;
	load(in, v);
	in.close();

	int izbor;
	bool povratak;
	do
	{
		izbornik(izbor);

		if (izbor == 1)
		{
			pretraga_po_imenu(v);

			poluizbornik(povratak);
			if (povratak == 0) return 0;
		}
		else if (izbor == 2)
		{
			prikaz_po_brzini(v);

			poluizbornik(povratak);
			if (povratak == 0) return 0;
		}
		else if (izbor == 3)
		{
			kopiranje_u_novi_vektor(v);

			poluizbornik(povratak);
			if (povratak == 0) return 0;
		}
		else if (izbor == 4)
		{
			prikaz_po_strani(v);

			poluizbornik(povratak);
			if (povratak == 0) return 0;
		}
		else if (izbor == 5)
		{
			insertion_vs_shell(v);

			poluizbornik(povratak);
			if (povratak == 0) return 0;
		}
		else if (izbor == 6)
		{
			lets_play_guess();

			poluizbornik(povratak);
			if (povratak == 0) return 0;
		}
		else if (izbor == 7)
		{
			monkey_play(v);

			poluizbornik(povratak);
			if (povratak == 0) return 0;
		}
		else if (izbor == 8)
		{
			the_quick_dance(v);

			poluizbornik(povratak);
			if (povratak == 0) return 0;
		}
		else if (izbor == 9)
		{
			pretraga_po_imenu_unordered_map(v);

			poluizbornik(povratak);
			if (povratak == 0) return 0;
		}
		else if (izbor == 10)
		{
			vizualiziraj(v);

			poluizbornik(povratak);
			if (povratak == 0) return 0;
		}
		else if (izbor == 11)
		{
			izrada_imena_iz_imena();

			poluizbornik(povratak);
			if (povratak == 0) return 0;
		}

	} while (izbor != 12);

	return 0;
}