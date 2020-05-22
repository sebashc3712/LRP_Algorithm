#ifndef cargaArchivos_H
#define cargaArchivos_H

#include <vector>
#include <string>
using namespace std;

typedef float dist_t;

//Estructura para almacenar la demanda de un cliente
struct demanda{
	vector < vector < float > > listadoItems;
};

//Estructura para cargar la información de las instancias
struct instancia{
	string nombreInstancia;
	float largoContenedor;
	float anchoContenedor;
	float altoContenedor;
	float volumenContenedor;
	float capacidadVehiculo;
	int numeroClientes;
	int numeroVehiculos;
	int numeroItems;
	vector < vector < float > > coordenadas;
	vector <demanda> demandaClientes;
};

struct mdcvfp {
    int nvehicles;
    int ncustomers;
    int ndepots;
    int heightVehicle;
    int widthVehicle;
    int lengthVehicle;
    float volumeVehicle;
    dist_t factor_demand_dist; // Factor to convert capacity in distance
    dist_t penalty_reloc; // cost for relocating a customer
    int numberTypeWaste;
    struct depot {
        int max_duration;
        int max_load;
    };
    vector <depot> depots;
    struct customer {
        int id;
        float x;
        float y;
        int service;
        int demand;
        int frequency;
        int numberBoxes;
        int demandVolume;
    };
    vector <customer> customers;
    struct box{
        int customerId;
        int boxId;
        int heightBox;
        int widthBox;
        int lengthBox;
        bool fragilityBox;
        int wasteType;
    };
    vector <box> boxes;
    struct relocation_point{
        int customerId;
        int x;
        int y;
    };
    vector <relocation_point> relocation_points;
};

/////////////////////////
//Listado de prototipos//
/////////////////////////

//Carga de instancias
void obtenerInformacionInstancia(string,vector< vector<float> > &, vector< vector<float> > &, vector< vector<float> > &, float &,float &);

//Carga de grafos en archivos de texto plano (formato establecido en la definición de la función
vector< vector<string> > cargarGrafoListaAdyacencia(string);

//Exploración de directorios
vector<string> listarArchivos(char *);

//Menús
string mostrarMenuInstancias(char *);

//Función para cargar instancias de CVRP_CLP correspondientes
void cargarInstanciaCVRP_CLP(string, instancia &);

//Función para dar salida a instancias del tipo correspondiente
void mostrarInstanciaCVRP_CLP(instancia);


#endif
