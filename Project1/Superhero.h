#pragma once
#include<string>
using namespace std;

class Superhero
{
private:
	string name;
	string alignment;
	double intelligence;
	double strength;
	double speed;
	double durability;
	double power;
	double combat;
	double total;

public:
	// konstruktori
	Superhero();
	Superhero(string name, string alignment, double intelligence, double strength, double speed, double durability, double power, double combat, double total);

	// setteri
	void set_name(string name);
	void set_alignment(string alignment);
	void set_intelligence(double intelligence);
	void set_strength(double strength);
	void set_speed(double speed);
	void set_durability(double durability);
	void set_power(double power);
	void set_combat(double combat);
	void set_total(double total);

	// getteri
	string get_name();
	string get_alignment();
	double get_intelligence();
	double get_strength();
	double get_speed();
	double get_durability();
	double get_power();
	double get_combat();
	double get_total();

	// funkcija za isips osnovnih podataka o superheroju
	string to_string();

};

