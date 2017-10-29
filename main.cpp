/*
 * File:   DFSOrder.h
 * Author: Cuisenaire
 * Labo 2
 * Created on 3. novembre 2014, 08:23
 */


#include <cstdlib>
#include <iostream>
#include "DiGraph.h"
#include "TopologicalSort.h"

#include "Util.h"
#include "SymbolGraph.h"

using namespace std;

//methode permettant de verifier le graphe trie par rapport au fichier d'entree
bool checkOrder(const std::vector<int>& order,
                const SymbolGraph<DiGraph>& SG,
                const std::string& filename,
                char delim) {

    std::vector<int> positionInOrder(order.size());
    for( size_t i = 0; i < order.size(); ++i )
        positionInOrder[order[i]] = int(i);
    
    bool ok = true;
    
    std::string line;
    
    std::ifstream s(filename);
    while (std::getline(s, line))
    {
        //sanitization
        if(line.find("\r") != std::string::npos) {
            line.erase(line.size() - 1);
        }

        auto names = split(line,delim);




        for(size_t i = 1; i < names.size(); ++i) {
         
            int v = SG.index(names[0]); // module
            int w = SG.index(names[i]); // ieme prerequis
            
            if ( positionInOrder[ v ] < positionInOrder [ w ]) {
                cout << "Erreur d'ordre : " << names[0] << " avant " << names[i] << endl;
                ok = false;
            } 
        }
    }
    s.close();
    
    return ok;
}


int test(string filename, char DELIM);
int main(int argc, const char * argv[]) {
    string filename2 = "../prerequis2.txt";
    string filename = "../prerequis.txt";
    const char DELIM = ',';

    test(filename, DELIM);
    cout << "==============" << endl;
    test(filename2, DELIM);
    return EXIT_SUCCESS;

}

/*test fonction
 * 1. Test if graph is a Directed Acyclic Graph
 * 2. Show Topological sort if so, cycle if not.
 */
int test(string filename, char DELIM){
    SymbolGraph<DiGraph> SG(filename, DELIM);
    //if you want to see the adjacency lists of graph, uncomment next line.
    //SG.print();
    try {
        TopologicalSort<DiGraph> TDG(SG.G());
        vector<int> sort = TDG.Order();

        cout << filename << " is a DAG" << endl << endl;

        cout << "Topological sort:" << endl;
        for(auto i : sort){
            cout << SG.name(i) << " ";
        }
        cout << endl;
        if(checkOrder(sort, SG, filename, ',')){
            cout << "Check passed succesfully." << endl;
        }

    }catch(const TopologicalSort<DiGraph>::GraphNotDAGException& e) {
        cout << filename << " is not a DAG. " << endl << endl;

        cout << "contains the following cycle:" << endl;
        for(auto i : e.Cycle()){
            cout << SG.name(i) << " -> ";
        }
        cout << SG.name(e.Cycle().front()) << "..." << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
