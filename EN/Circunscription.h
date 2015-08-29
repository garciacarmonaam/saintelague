#include "Candidatures_List.h"
#include <fstream>
#include <string>

class Circunscription
{
	Candidatures_List *candidatures;
	string name;
	int code;
	int seats;
	int candidatures_number;
	int distribution[1000][1000];

public:

	Circunscription(string name, int seats)
	{
		this->candidatures = new Candidatures_List();
		this->name = name;
		this->code = 0; // Default value
		this->seats = seats;
		this->candidatures_number = 0;
	}

	Circunscription(string name, int seats, int code)
	{
		this->candidatures = new Candidatures_List();
		this->name = name;
		this->code = code; // Default value
		this->seats = seats;
		this->candidatures_number = 0;
	}

	void loadCandidatures(float election_thresold) // Percentage value (for example, if value is 3%, election_thresold=3)
	{
		ifstream count_file;
		string total_votes;
		string txtfile_name;

		cout << "Please write text file (.txt) name:" << endl;
		cin >> txtfile_name;

		count_file.open(txtfile_name + ".txt");
		while (!count_file.is_open())
		{
			cout << "The file is corrupted or damaged" << endl;
			txtfile_name.clear();
			cin >> txtfile_name;
			count_file.open(txtfile_name + ".txt");
		}

		if (count_file.is_open())
		{
			if (!count_file.eof())
			{
				int cod = 0;
				getline(count_file, total_votes);
				bool isInterruptionEnabled = true;
				candidatures->point1stCandidature();
				int total_votes_ = atoi(total_votes.c_str());
				while (!count_file.eof() && isInterruptionEnabled)
				{
					string candidature;
					string candidature_votes;

					getline(count_file, candidature, '#');
					getline(count_file, candidature_votes);
					int candid_votes = atoi(candidature_votes.c_str());
					if (float(candid_votes) < (election_thresold / 100)*float(total_votes_))
						isInterruptionEnabled = false;
					else
					{
						candidatures->addNewCandidature(new Candidature(candidature, candid_votes, cod));
						distribution[0][cod] = candid_votes;
						candidatures->moveCandidaturesPointer();
						cod++;
					}
					this->candidatures_number = cod;
				}
				count_file.close();
			}
			else
				cout << "The file doesn't contain the right data to proceed." << endl;
		}
	}

	void distributeSeats()
		{
			for (int i = 0; i < this->seats; i++)
			{
				int mostvoted_code = 0;
				int votes = 0;
				for (int j = 0; j < this->candidatures_number; j++)
				{
					if (distribution[i][j] > votes)
					{
						mostvoted_code = j;
						votes = distribution[i][j];
					}
				}

				Candidature *mostvoted = NULL;
				bool hasItBeenFound = false;
				this->candidatures->point1stCandidature();
				while (!this->candidatures->isCandidaturesListEndPointed() && !hasItBeenFound)
				{
					this->candidatures->checkPointedCandidature(mostvoted);
					if (mostvoted->getCode() == mostvoted_code)
						hasItBeenFound = true;
					else
						this->candidatures->moveCandidaturesPointer();
				}

				int current_seats = mostvoted->getObtainedSeats();
				mostvoted->setObtainedSeats(current_seats + 1);
				this->candidatures->point1stCandidature();

				if (i + 1 < this->seats)
				{
					distribution[i + 1][mostvoted_code] = distribution[0][mostvoted_code] / (2 * mostvoted->getObtainedSeats() + 1);
					int k = 0;
					while (k < this->candidatures_number)
					{
						if (k != mostvoted_code)
							distribution[i + 1][k] = distribution[i][k];
						k++;
					}
				}
			}
		}

	void modifyCircunscriptionName(const string &name)
		{
			this->name = name;
		}

	string getCircunscriptionName()
		{
			return this->name;
		}

	void setCircunscriptionCode(const int &code)
		{
			this->code = code;
		}

	int getCircunscriptionCode()
		{
			return this->code;
		}

	void redefineCircunscriptionSeats(const int &seats)
		{
			this->seats = seats;
		}

	int getCircunscriptionSeats()
		{
			return this->seats;
		}

	void setCandidaturesNumber(const int &candidatures_number)
		{
			this->candidatures_number = candidatures_number;
		}

	int getCandidaturesNumber()
		{
			return this->candidatures_number;
		}

	void displayResults()
		{
			this->candidatures->displaySeatsDistributionResults();
		}

	~Circunscription()
		{
			delete this->candidatures;
		}
};