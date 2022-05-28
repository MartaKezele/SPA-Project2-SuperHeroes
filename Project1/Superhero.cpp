#include "Superhero.h"
#include<sstream>

// konstruktori

Superhero::Superhero()
{
}

Superhero::Superhero(string name, string alignment, double intelligence, double strength, double speed, double durability, double power, double combat, double total)
{
	set_name(name);
	set_alignment(alignment);
	set_intelligence(intelligence);
	set_strength(strength);
	set_speed(speed);
	set_durability(durability);
	set_power(power);
	set_combat(combat);
	set_total(total);
}

// setteri

void Superhero::set_name(string name)
{
	this->name = name;
}

void Superhero::set_alignment(string alignment)
{
	this->alignment = alignment;
}

void Superhero::set_intelligence(double intelligence)
{
	this->intelligence = intelligence;
}

void Superhero::set_strength(double strength)
{
	this->strength = strength;
}

void Superhero::set_speed(double speed)
{
	this->speed = speed;
}

void Superhero::set_durability(double durability)
{
	this->durability = durability;
}

void Superhero::set_power(double power)
{
	this->power = power;
}

void Superhero::set_combat(double combat)
{
	this->combat = combat;
}

void Superhero::set_total(double total)
{
	this->total = total;
}

// getteri

string Superhero::get_name()
{
	return name;
}

string Superhero::get_alignment()
{
	return alignment;
}

double Superhero::get_intelligence()
{
	return intelligence;
}

double Superhero::get_strength()
{
	return strength;
}

double Superhero::get_speed()
{
	return speed;
}

double Superhero::get_durability()
{
	return durability;
}

double Superhero::get_power()
{
	return power;
}

double Superhero::get_combat()
{
	return combat;
}

double Superhero::get_total()
{
	return total;
}

// funkcija za isips osnovnih podataka o superheroju

string Superhero::to_string()
{
	string poruka = "Upisano";
	stringstream ss_total;
	if (total < 0)
	{
		poruka = "Nije upisano";
	}
	else
	{
		ss_total << total;
	}

	stringstream ss;
	ss
		<< "name: " << name
		<< "\t"
		<< "alignment: " << (alignment == "" ? "Nije upisano" : alignment)
		<< "\t\t"
		<< "total: " << (poruka == "Nije upisano" ? poruka : ss_total.str());

	return ss.str();
}
