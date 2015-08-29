#include <cstring>
#include <iostream>
using namespace std;

class Candidatura
{
	string nombre;
	int codigo;
	int votos;
	int escanos_obtenidos; // Inicialmente 0

	public:

		Candidatura()
		{
			this->nombre = "No definida";
			this->votos = 0;
			this->codigo = 0;
			this->escanos_obtenidos = 0;
		}

		Candidatura(string nombre_, int votos_, int codigo_)
		{
			this->nombre = nombre_;
			this->votos = votos_;
			this->codigo = codigo_;
			this->escanos_obtenidos = 0;
		}

		Candidatura(const Candidatura &candidat)
		{
			this->nombre = candidat.nombre;
			this->votos = candidat.votos;
			this->codigo = candidat.codigo;
			this->escanos_obtenidos = candidat.escanos_obtenidos;
		}

		void consultarNombre(string &nombre_)
		{
			nombre_ = this->nombre;
		}

		void modificarNombre(string nombre_cand)
		{
			this->nombre = nombre_cand;
		}

		int consultarCodigo()
		{
			return this->codigo;
		}

		int consultarNumeroVotos()
		{
			return this->votos;
		}

		void definirEscanosObtenidos(int escanos_)
		{
			this->escanos_obtenidos = escanos_;
		}

		int consultarEscanosObtenidos()
		{
			return this->escanos_obtenidos;
		}

		void mostrarInfoCandidatura()
		{
			cout << "Nombre: " << this->nombre <<
				endl << "Votos: " << this->votos << endl
				<< "Código: " << this->codigo <<
				endl << "Escaños: " << this->escanos_obtenidos << endl
				<< endl;
		}

		~Candidatura()
		{
		}
};

