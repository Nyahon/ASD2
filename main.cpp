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
// vous devez reutiliser celui du labo 1, ex 2 (cf. donnee)
#include "ParcoursEnProfondeur.h"
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

void printV(int val){
    //cout << val << endl;
}
int main(int argc, const char * argv[]) {
    string filename = "../prerequis2.txt";
  //  DiGraph DG = DG("../prerequis.txt");
    SymbolGraph<DiGraph> SG(filename, ',');
    SG.print();
   // SG = SG.G().reverse();
   // DFS<DiGraph> dfs(SG.G());
   // dfs.visitGraph(printV, [](int v){});

    DirectedCycle<DiGraph> DC(SG.G());
   // cout << "has cycle: " << (DC.HasCycle() ? "yes" : "no" ) << endl;

    try {
        TopologicalSort<DiGraph> TDG(SG.G());
        vector<int> sort = TDG.Order();

    for(auto i : sort){
        cout << i << " " << endl;
    }
    checkOrder(sort, SG, filename, ',');

    }catch(const exception& e) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
