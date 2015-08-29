#include <cstring>
#include <iostream>
using namespace std;

class Candidature
{
	string name;
	int code;
	int votes;
	int obtained_seats; // Primarily, 0

	public:

		Candidature()
		{
			this->name = "No definida";
			this->votes = 0;
			this->code = 0;
			this->obtained_seats = 0;
		}

		Candidature(string name_, int votes_, int code_)
		{
			this->name = name_;
			this->votes = votes_;
			this->code = code_;
			this->obtained_seats = 0;
		}

		Candidature(const Candidature &candidat)
		{
			this->name = candidat.name;
			this->votes = candidat.votes;
			this->code = candidat.code;
			this->obtained_seats = candidat.obtained_seats;
		}

		void getName(string &name_)
		{
			name_ = this->name;
		}

		void setName(string candid_name)
		{
			this->name = candid_name;
		}

		int getCode()
		{
			return this->code;
		}

		int getNumberOfVotes()
		{
			return this->votes;
		}

		void setObtainedSeats(int seats_)
		{
			this->obtained_seats = seats_;
		}

		int getObtainedSeats()
		{
			return this->obtained_seats;
		}

		void displayCandidatureInfo()
		{
			cout << "Name: " << this->name << endl << "Votes: " << this->votes << endl << "Code: " << this->code << endl << "Seats: " << this->obtained_seats << endl << endl;
		}

		~Candidature()
		{
		}
};

