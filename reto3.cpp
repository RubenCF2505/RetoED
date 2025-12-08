#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class BinTree
{
    struct nodo
    {
        char etiqueta;
        nodo *padre;
        nodo *hijoIzq;
        nodo *hijoDer;
    };

    nodo *raiz;

public:
    BinTree() {}
    BinTree(string cadena)
    {
        /*if (cadena.length() > 0)
        {
            raiz.etiqueta = cadena[0];
            raiz.hijoDer = nullptr;
            raiz.hijoIzq = nullptr;
            raiz.padre = nullptr;

            cadena.erase(0, 1);
            auto it = cadena.begin();
            auto it2 = cadena.begin();
            nodo *actual = &raiz;

            while (it != cadena.end())
            {

                if (*it != '#')
                {
                    crearHijoIzq(actual, *it);
                    actual = actual->hijoIzq;

                    ++it;
                    ++it2;
                }
                else
                {
                    ++it2;
                    if (it2 != cadena.end() && *it2 != '#')
                    {
                        crearHijoDer(actual, *it2);
                        actual = actual->hijoDer;

                        ++it;
                        ++it2;
                    }
                    else
                    {
                        actual = actual->padre;

                        if (it2 != cadena.end())
                            ++it2;
                        ++it;
                    }
                }
            }
        }*/
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
    /*void crearHijoIzq(nodo *padre, char etiqueta)
    {
        nodo *nuevo = new nodo;
        nuevo->etiqueta = etiqueta;
        nuevo->padre = padre;
        padre->hijoIzq = nuevo;
        nuevo->hijoIzq = nullptr;
        nuevo->hijoDer = nullptr;
    }
    void crearHijoDer(nodo *padre, char etiqueta)
    {
        nodo *nuevo = new nodo;
        nuevo->etiqueta = etiqueta;
        nuevo->padre = padre;
        padre->hijoDer = nuevo;
        nuevo->hijoIzq = nullptr;
        nuevo->hijoDer = nullptr;
    }*/
};

int main(int argc, char **args)
{
    string cadena = args[1];

    int entrada = -1;
    do
    {
        cout << endl << "Se ha ingresado [0: Arbol directamente] [1: Archivo de texto con el arbol]?: ";
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