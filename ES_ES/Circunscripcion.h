#include "Lista_Candidaturas.h"
#include <fstream>
#include <string>
class Circunscripcion
{
	Lista_Candidaturas *candidaturas;
	string nombre;
	int codigo;
	int escanos;
	int numero_candidaturas;
	int distribucion[1000][1000];

public:

	Circunscripcion(string nombre, int escanos)
	{
		this->candidaturas = new Lista_Candidaturas();
		this->nombre = nombre;
		this->codigo = 0; // Por defecto
		this->escanos = escanos;
		this->numero_candidaturas = 0;
	}

	Circunscripcion(string nombre, int escanos, int codigo)
	{
		this->candidaturas = new Lista_Candidaturas();
		this->nombre = nombre;
		this->codigo = codigo; // Por defecto
		this->escanos = escanos;
		this->numero_candidaturas = 0;
	}

	void cargarCandidaturas(float umbral_electoral) // Valor porcentual (por ejemplo, si es 3%, poner 3).
	{
		ifstream fichero_recuento;
		string votos_totales;
		string nombre_archivotxt;

		cout << "Escriba el nombre del archivo (.txt) por favor:" << endl;
		cin >> nombre_archivotxt;

		fichero_recuento.open(nombre_archivotxt + ".txt");
		while (!fichero_recuento.is_open())
		{
			cout << "El archivo está dañado o no existe" << endl;
			nombre_archivotxt.clear();
			cin >> nombre_archivotxt;
			fichero_recuento.open(nombre_archivotxt + ".txt");
		}

		if (fichero_recuento.is_open())
		{
			if (!fichero_recuento.eof())
			{
				int cod = 0;
				getline(fichero_recuento, votos_totales);
				bool ininterrupcion_activada = true;
				candidaturas->marcar1aCandidatura();
				int total_votos = atoi(votos_totales.c_str());
				while (!fichero_recuento.eof() && ininterrupcion_activada)
				{
					string candidatura;
					string votos_candidat;

					getline(fichero_recuento, candidatura, '#');
					getline(fichero_recuento, votos_candidat);
					int votos_candid = atoi(votos_candidat.c_str());
					if (float(votos_candid) < (umbral_electoral / 100)*float(total_votos))
						ininterrupcion_activada = false;
					else
					{
						candidaturas->insertarNuevaCandidatura(new Candidatura(candidatura, votos_candid, cod));
						distribucion[0][cod] = votos_candid;
						candidaturas->avanzarMarcadorCandidaturas();
						cod++;
					}
					this->numero_candidaturas = cod;
				}
				fichero_recuento.close();
			}
			else
				cout << "El archivo no contiene los datos adecuados para poder proceder." << endl;
		}
	}

		void distribuirEscaniosCandidaturas()
		{
			for (int i = 0; i < this->escanos; i++)
			{
				int codigo_masvotada = 0;
				int votos = 0;
				for (int j = 0; j < this->numero_candidaturas; j++)
				{
					if (distribucion[i][j] > votos)
					{
						codigo_masvotada = j;
						votos = distribucion[i][j];
					}
				}

				Candidatura *masvotada = NULL;
				bool encontrada = false;
				this->candidaturas->marcar1aCandidatura();
				while (!this->candidaturas->seMarcaFinRelacionCandidaturas() && !encontrada)
				{
					this->candidaturas->consultarCandidaturaMarcada(masvotada);
					if (masvotada->consultarCodigo() == codigo_masvotada)
						encontrada = true;
					else
						this->candidaturas->avanzarMarcadorCandidaturas();
				}

				int esc_havegot = masvotada->consultarEscanosObtenidos();
				masvotada->definirEscanosObtenidos(esc_havegot + 1);
				this->candidaturas->marcar1aCandidatura();

				if (i + 1 < this->escanos)
				{
					distribucion[i + 1][codigo_masvotada] = distribucion[0][codigo_masvotada] / (2 * masvotada->consultarEscanosObtenidos() + 1);
					int k = 0;
					while (k < this->numero_candidaturas)
					{
						if (k != codigo_masvotada)
							distribucion[i + 1][k] = distribucion[i][k];
						k++;
					}
				}
			}
		}

		void modificarNombreCircunscripcion(const string &nombre)
		{
			this->nombre = nombre;
		}

		string obtenerNombreCircunscripcion()
		{
			return this->nombre;
		}

		void definirCodigoCircunscripcion(const int &codigo)
		{
			this->codigo = codigo;
		}

		int obtenerCodigoCircunscripcion()
		{
			return this->codigo;
		}

		void redefinirEscanosCircunscripcion(const int &escanos)
		{
			this->escanos = escanos;
		}

		int obtenerEscanosCircunscripcion()
		{
			return this->escanos;
		}

		void definirNumeroCandidaturas(const int &num_candid)
		{
			this->numero_candidaturas = num_candid;
		}

		int obtenerNumeroCandidaturas()
		{
			return this->numero_candidaturas;
		}

		void mostrarResultados()
		{
			this->candidaturas->mostrarResultadosDistribucionEscanos();
		}

		~Circunscripcion()
		{
			delete this->candidaturas;
		}
};