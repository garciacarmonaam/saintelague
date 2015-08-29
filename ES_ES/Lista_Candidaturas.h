#pragma once
#include "Candidatura.h"

class Lista_Candidaturas
{
	typedef Candidatura candidatura;
	typedef struct nodo {
		candidatura * candidat;
		nodo * siguiente;
		nodo * anterior;
	} nodo;

	nodo * inicio;
	nodo * fin;
	nodo * pi;

public:

	Lista_Candidaturas()
	{
		inicio = NULL;
		fin = NULL;
		pi = NULL;
	}

	bool hayCandidaturas()
	{
		return (!(inicio == NULL));
	}

	void marcar1aCandidatura()
	{
		pi = inicio;
	}

	void marcarUltimaCandidatura()
	{
		pi = fin;
	}

	void avanzarMarcadorCandidaturas()
	{
		if (pi != NULL) {
			pi = pi->siguiente;
		}
	}

	void retrocedeMarcadorCandidaturas()
	{
		if (pi != inicio) {
			if (pi != NULL)
				pi = pi->anterior;
			else
				pi = fin;
		}
	}

	bool seMarca1aCandidatura()
	{
		return (pi == inicio);
	}

	bool seMarcaUltimaCandidatura()
	{
		return (pi == fin);
	}

	bool seMarcaFinRelacionCandidaturas()
	{
		return (pi == NULL);
	}

	void consultarCandidaturaMarcada(Candidatura *&candidatura)
	{
		if (pi != NULL)
			candidatura = pi->candidat;
	}

	void insertarNuevaCandidatura(Candidatura *candidatura_)
	{
		nodo * nueva_ = new nodo;
		nueva_->candidat = candidatura_;
		nueva_->anterior = NULL;
		nueva_->siguiente = NULL;

		if (pi == NULL)
		{
			if (!hayCandidaturas())
			{
				nueva_->siguiente = pi;
				inicio = nueva_;
				fin = nueva_;
			}
			else
			{
				nueva_->anterior = fin;
				fin->siguiente = nueva_;
				fin = nueva_;
			}
		}
		else
		{
			if (pi->anterior != NULL)
			{
				nueva_->anterior = pi->anterior;
				nueva_->siguiente = pi;
				pi->anterior->siguiente = nueva_;
				pi->anterior = nueva_;
			}
			else
			{
				inicio = nueva_;
				nueva_->siguiente = pi;
				nueva_->anterior = NULL;
				pi->anterior = nueva_;
			}
		}

		pi = nueva_;
	}

	void borrarCandidaturaMarcada()
	{
		nodo *auxiliar;
		if (!seMarcaFinRelacionCandidaturas() && hayCandidaturas())
		{
			auxiliar = pi;
			if (pi == inicio)
				inicio = inicio->siguiente;
			if (pi == fin)
				fin = fin->anterior;

			pi = pi->siguiente;

			if (auxiliar->anterior != NULL)
				auxiliar->anterior->siguiente = pi;
			if (!(auxiliar->siguiente == NULL))
				pi->anterior = auxiliar->anterior;

			delete auxiliar;
		}
	}

	void mostrarResultadosDistribucionEscanos()
	{
		if (this->hayCandidaturas())
		{
			cout << "La distribución resulta ser la siguiente: " << endl; 
			this->marcar1aCandidatura();
			int i = 1;
			while (!this->seMarcaFinRelacionCandidaturas())
			{
				Candidatura * auxiliar = NULL;
				this->consultarCandidaturaMarcada(auxiliar);
				string nombre;
				auxiliar->consultarNombre(nombre);
				cout << i << ") " << nombre << " " << auxiliar->consultarEscanosObtenidos() << endl;
				i++;
				this->avanzarMarcadorCandidaturas();
			}
			cout << endl;
		}
	}

	~Lista_Candidaturas()
	{
		marcar1aCandidatura();
		while (!seMarcaFinRelacionCandidaturas())
		{
			borrarCandidaturaMarcada();
			avanzarMarcadorCandidaturas();
		}

		inicio = NULL;
		fin = NULL;
		pi = NULL;
	}
};

