#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class BinTree
{
private:
    struct nodo
    {
        char etiqueta;
        nodo *padre;
        nodo *hijoIzq;
        nodo *hijoDer;
    };

    nodo *raiz;
    
    void guardaArbol(ofstream &out, nodo *actual)
    {
        bool esHijoVacio = (actual == nullptr);
        bool esHoja = esHijoVacio ? true : (actual->hijoIzq == nullptr && actual->hijoDer == nullptr);

        if (esHijoVacio)
        {
            out << "#";
        }
        else if (esHoja && !esHijoVacio)
        {
            out << actual->etiqueta << ".";
        }
        else // Nodo con hijos
        {
            out << actual->etiqueta;
            guardaArbol(out, actual->hijoIzq);
            guardaArbol(out, actual->hijoDer);
        }
    }

public:
    BinTree() {}
    BinTree(string cadena)
    {
        int pos = 0;
        raiz = construir(cadena, pos, nullptr);
    }

    nodo *construir(string &cadena, int &pos, nodo *padre)
    {
        nodo *nuevo = nullptr;
        if (pos < cadena.size())
        {
            char c = cadena[pos];
            pos++;

            if (cadena[pos] == '.')
            {
                pos++;
                nuevo = new nodo;
                nuevo->etiqueta = c;
                nuevo->padre = padre;
                nuevo->hijoIzq = nullptr;
                nuevo->hijoDer = nullptr;
            }
            else if (c != '#' && c != '.')
            {
                nuevo = new nodo;
                nuevo->etiqueta = c;
                nuevo->padre = padre;
                nuevo->hijoIzq = construir(cadena, pos, nuevo);
                nuevo->hijoDer = construir(cadena, pos, nuevo);
            }
        }

        return nuevo;
    }

    // Funciones relacionadas con Ficheros --------------------------------------------

    void guardarArchivo(const string &nombre)
    {
        ofstream out(nombre);
        if (!out)
        {
            cerr << "Error abriendo archivo\n";
            return;
        }
        guardaArbol(out, raiz);
        out.close();
    }

    void leerArchivo(const string &nombre)
    {
        ifstream in(nombre);
        if (!in)
        {
            cerr << "Error abriendo archivo\n";
            return;
        }
        string contenido;
        getline(in, contenido);
        in.close();

        int pos = 0;
        raiz = construir(contenido, pos, nullptr);
    }

    // Representación Arbol ----------------------------------------

    void inorden(nodo *actual)
    {
        if (actual == nullptr)
            return;

        inorden(actual->hijoIzq);
        cout << actual->etiqueta << " ";
        inorden(actual->hijoDer);
    }

    void mostrarInorden()
    {
        inorden(raiz);
        cout << endl;
    }
};

//********************************************************************************

int main(int argc, char **args)
{
    string cadena = args[1];

    int entrada = -1;
    do
    {
        cout << "Se ha ingresado [0: Arbol directamente] [1: Archivo de texto con el arbol]?: ";
        cin >> entrada;
    } while (entrada > 1 || entrada < 0);
    
    BinTree arbol;
    if (entrada == 0) arbol = BinTree(cadena);
    else arbol.leerArchivo(cadena);
   

    cout << "Recorrido inorden: ";
    arbol.mostrarInorden();

    string nombreArchivo = "arbol.txt";
    arbol.guardarArchivo(nombreArchivo);

    cout << endl << "Arbol guardado en " << nombreArchivo << endl;

    return 0;
}