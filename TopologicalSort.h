/*
 * File:   TopologicalSort.h
 * Author: Olivier Cuisenaire
 *
 * Created on 08. octobre 2014, 14:07
 *
 * A implementer
 * Classe permettant le tri topologique d'un graphe oriente
 */

#ifndef ASD2_TopologicalSort_h
#define ASD2_TopologicalSort_h

#include "DirectedCycle.h"
#include <list>
#include <vector>
#include <exception>
#include "ParcoursEnProfondeur.h"

template < typename GraphType >
class TopologicalSort {
private:
	/* A DEFINIR */
    DFS<GraphType>* g;
    vector<int> sorted;
    
public:
    //constructeur
    TopologicalSort(const GraphType& g)   {
        /* A IMPLEMENTER */
        DirectedCycle<GraphType> DCG(g);
        try {


            if (DCG.HasCycle()) {
                cout << "yes" << endl;
                list<int> cycle = DCG.Cycle();
                /* cout << "Cycle: ";
                 for(int i : cycle)
                     cout << i << " ";
                 cout << endl;
                 */
                throw GraphNotDAGException(cycle);
            } else {
                cout << "no" << endl;
            }
        }catch(const GraphNotDAGException& e){
            cout << e.what() << endl;
            for(auto i : e.Cycle()){
                cout << i << " ";
                throw e;
            }
            cout << endl;
        }
        /* vous devez verifier la presence d'un cycle, auquel cas il faut lancer une  GraphNotDAGException*/
        this->g = new DFS<GraphType>(g);




    }
    
    //tableau contenant l'ordre de parcours des indexes des sommets dans le graphe
    const std::vector<int>& Order() {
        /* A IMPLEMENTER */
        //return ...
        g->visitGraph([](int v){}, [this](int v){
            sorted.push_back(v);
           // cout << "KK" << v << endl;
        });
        std::reverse(sorted.begin(),sorted.end());
        return sorted;
    }
    
    //exception si le graphe n'est pas un DAG (Directed Acyclic Graph)
    class GraphNotDAGException : public std::exception {
        
    private:
        //indexes des sommets du cycle qui empeche le tris topologique
        const std::list<int> cycle;
        
    public:
        GraphNotDAGException(const std::list<int> cycle) noexcept : exception(), cycle(cycle) {
            
        }
        
        virtual const char* what() const noexcept {
            return "Topological sort impossible : the graph is not a DAG";
        }
        
        const std::list<int>& Cycle() const noexcept {
            return cycle;
        }
    };
};


#endif
