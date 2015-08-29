#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include "Candidature.h"

class Candidatures_List
{
	typedef Candidature candidature;
	typedef struct nodo {
		candidature * candidat;
		nodo * next;
		nodo * previous;
	} nodo;

	nodo * start;
	nodo * end;
	nodo * ip;

public:

	Candidatures_List()
	{
		start = NULL;
		end = NULL;
		ip = NULL;
	}

	bool isThereAnyCandidature()
	{
		return (!(start == NULL));
	}

	void point1stCandidature()
	{
		ip = start;
	}

	void pointFinalCandidature()
	{
		ip = end;
	}

	void moveCandidaturesPointer()
	{
		if (ip != NULL) {
			ip = ip->next;
		}
	}

	void moveBackCandidaturesPointer()
	{
		if (ip != start) {
			if (ip != NULL)
				ip = ip->previous;
			else
				ip = end;
		}
	}

	bool is1stCandidaturePointed()
	{
		return (ip == start);
	}

	bool isFinalCandidaturePointed()
	{
		return (ip == end);
	}

	bool isCandidaturesListEndPointed()
	{
		return (ip == NULL);
	}

	void checkPointedCandidature(Candidature *&candidature)
	{
		if (ip != NULL)
			candidature = ip->candidat;
	}

	void addNewCandidature(Candidature *candidature_) 
	{
		nodo * new_ = new nodo;
		new_->candidat = candidature_;
		new_->previous = NULL;
		new_->next = NULL;

		if (ip == NULL)
		{
			if (!isThereAnyCandidature())
			{
				new_->next = ip;
				start = new_;
				end = new_;
			}
			else
			{
				new_->previous = end;
				end->next = new_;
				end = new_;
			}
		}
		else
		{
			if (ip->previous != NULL)
			{
				new_->previous = ip->previous;
				new_->next = ip;
				ip->previous->next = new_;
				ip->previous = new_;
			}
			else
			{
				start = new_;
				new_->next = ip;
				new_->previous = NULL;
				ip->previous = new_;
			}
		}

		ip = new_;
	}

	void deletePointedCandidature()
	{
		nodo *auxiliary;
		if (!isFinalCandidaturePointed() && isThereAnyCandidature())
		{
			auxiliary = ip;
			if (ip == start)
				start = start->next;
			if (ip == end)
				end = end->previous;

			ip = ip->next;

			if (auxiliary->previous != NULL)
				auxiliary->previous->next = ip;
			if (!(auxiliary->next == NULL))
				ip->previous = auxiliary->previous;

			delete auxiliary;
		}
	}

	void displaySeatsDistributionResults()
	{
		if (this->isThereAnyCandidature())
		{
			cout << "The distribution is the following: " << endl; 
			this->point1stCandidature();
			int i = 1;
			while (!this->isCandidaturesListEndPointed())
			{
				Candidature * auxiliary = NULL;
				this->checkPointedCandidature(auxiliary);
				string name;
				auxiliary->getName(name);
				cout << i << ") " << name << " " << auxiliary->getObtainedSeats() << endl;
				i++;
				this->moveCandidaturesPointer();
			}
			cout << endl;
		}
	}

	~Candidatures_List()
	{
		point1stCandidature();
		while (!isCandidaturesListEndPointed())
		{
			deletePointedCandidature();
			moveCandidaturesPointer();
		}

		start = NULL;
		end = NULL;
		ip = NULL;
	}
};

