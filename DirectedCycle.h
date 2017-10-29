/*
 * File:   DirectedCycle.h
 * Author: Olivier Cuisenaire
 * Created on 08. octobre 2014, 10:46
 *
 * A implementer
 * Classe permettant la detection de cycle sur un graphe oriente
 */

#ifndef ASD2_DirectedCycle_h
#define ASD2_DirectedCycle_h

using namespace std;

template<typename GraphType>
class DirectedCycle {
private:
    vector<bool> marked;
    vector<bool> stacked;
    //contains the detected cycle if not DAG
    vector<bool> stackCycle;
    bool foundCycle = false;
    const GraphType* g;

public:
	//constructeur
	DirectedCycle(const GraphType& g) {
        marked.resize(g.V());
        stacked.resize(g.V());
        stackCycle.resize(g.V());

        this->g = &g;
	}

	//indique la presence d'un cycle
	bool HasCycle() {
        foundCycle = false;
        //we need to check every possible starting point.
        //this is due to the fact we're in a *directed* graph.
        for(int i =0; i<g->V();++i) {
            DetectCycle(i);
            if(foundCycle)
                return true;
        }
        return false;
	}



	//liste les indexes des sommets formant une boucle
	list<int> Cycle() {
        list<int> cycle;
        for(int i =0;i<stackCycle.size();i++){
            if(stackCycle[i])
                cycle.push_back(i);
        }
        return cycle;
	}

    //allow the detection of a cycle in a graph, starting at v.
private: bool DetectCycle(int v){
        marked[v] = true;
        stacked[v] = true;

        for (auto i : g->adjacent(v)){
            if(foundCycle)
                return true;
            else if(!marked[i]){
                DetectCycle(i);
            }
            else if(stacked[i]){
                foundCycle = true;
                //construct the cycle list.
                stackCycle.insert(stackCycle.begin(), stacked.begin(), stacked.end());
            }
        }
        stacked[v] = false;
    }
};


#endif
