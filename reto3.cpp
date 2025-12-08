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

    nodo* raiz;

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

    nodo* construir(string &cadena, int &pos, nodo* padre)
    {
        char c = cadena[pos];
        pos++;
        nodo *nuevo = nullptr;

        if (pos < cadena.size() && cadena[pos] == '.')
        {
            pos++;
            nuevo = new nodo;
            nuevo->etiqueta = c;
            nuevo->padre = padre;
            nuevo->hijoIzq = nullptr;
            nuevo->hijoDer = nullptr;
        }
        else if (pos < cadena.size() && c != '#' && c != '.')
        {
            nuevo = new nodo;
            nuevo->etiqueta = c;
            nuevo->padre = padre;
            nuevo->hijoIzq = construir(cadena, pos, nuevo);
            nuevo->hijoDer = construir(cadena, pos, nuevo);
        }

        return nuevo;
    }

    void guardaArbol(ofstream &out, nodo* actual)
    {
        bool esHijoVacio = (actual == nullptr);
        bool esHoja = (actual->hijoIzq == nullptr && actual->hijoDer == nullptr);

        if (esHijoVacio)
        {
            out << "#";
        } else if (esHoja && !esHijoVacio)
        {
            out << actual->etiqueta << ".";
        } else // Nodo con hijos
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
    BinTree arbol(cadena);

    arbol.mostrarInorden();

    string nombreArchivo = "arbol.txt";
    arbol.guardarArchivo(nombreArchivo);

    return 0;
}