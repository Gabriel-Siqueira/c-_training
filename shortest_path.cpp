#include <iostream>
#include <vector>
#include <list>

using namespace std;

typedef enum Set {NONE,OPEN,CLOSER} Set;

struct Edge{
    int end;
    int value;
};

class Ver{
private:
    list<Edge> edges;
    list<Edge>::iterator it;
    int father;
    int distance;
    Set set;
public:
    Ver(int father = -1, int distance = -1, Set set = NONE) : edges(),father(father),distance(distance),set(set) {}

    void add_edge(Edge edge){
        edges.push_front (edge);
    }
    void set_iterator() {it = edges.begin();};
    Edge next_edge() {
        Edge next;
        next = *it;
        it++;
        return next;
    }
    bool have_edges() {return it != edges.end();}

    Set get_set() {return set;}
    int get_father() {return father;}
    int get_distance() {return distance;}
    void change_set(Set set) {this->set = set;}
    void change_father(int father) {this->father = father;}
    void change_distance(int distance) {this->distance = distance;}
};

class Graf{
private:
    vector<Ver> vertices;
public:
    Graf(int size){
        int ver1,ver2,edge_value;
        Edge edge_aux;
        Ver ver_aux;
        vertices.resize(size, ver_aux);
        cin >> ver1 >> ver2 >> edge_value;
        while(ver1 != -1){
            edge_aux.end = ver2;
            edge_aux.value = edge_value;
            vertices[ver1].add_edge(edge_aux);
            cin >> ver1 >> ver2 >> edge_value;
        }
    }

    int find_closer(int& closer){
        int i;
        for(i = 0; i < vertices.size() && vertices[i].get_set() != OPEN; i++);
        if(i == vertices.size()) return 0;
        closer = i;
        for(i = i+1; i < vertices.size(); i++){
            if(vertices[i].get_set() == OPEN && vertices[i].get_distance() < vertices[closer].get_distance())
                closer = i;
        }
            return 1;
    }

    void set_iterator(int pos) {vertices[pos].set_iterator();}
    Edge next_edge(int pos) {return vertices[pos].next_edge();}
    bool have_edges(int pos) {return vertices[pos].have_edges();}

    Set get_set(int pos) {return vertices[pos].get_set();}
    int get_distance(int pos) {return vertices[pos].get_distance();}
    void change_set(Set set,int pos) {vertices[pos].change_set(set);}
    void change_distance(int distance,int pos) {vertices[pos].change_distance(distance);}
    void change_father(int father,int pos) {vertices[pos].change_father(father);}
};

int find_path(Graf& graf,const int start,const int end){
    int new_closed,distance;
    Edge test;
    graf.change_set(OPEN,start);
    graf.change_distance(0,start);
    while( graf.get_set(end) != CLOSER && graf.find_closer(new_closed) ){
        graf.change_set(CLOSER,new_closed);
        graf.set_iterator(new_closed);
        while(graf.have_edges(new_closed)){
            test = graf.next_edge(new_closed);
            distance = graf.get_distance(new_closed) + test.value;
            if(graf.get_set(test.end) == OPEN && graf.get_distance(test.end) > distance){
                graf.change_distance(distance,test.end);
                graf.change_father(new_closed,test.end);
            }else if(graf.get_set(test.end) == NONE){
                graf.change_distance(distance,test.end);
                graf.change_father(new_closed,test.end);
                graf.change_set(OPEN,test.end);
            }
        }
    }
    if(graf.get_set(end) == CLOSER) return graf.get_distance(end);
    return -1;
}

int main(){
    int size,start,end;
    int distance;
    cout << "size: ";
    cin >> size;
    Graf graf(size);
    cout << "start: ";
    cin >> start;
    cout << "end: ";
    cin >> end;
    distance = find_path(graf,start,end);
    if(distance >= 0) cout << distance << endl;
    return 0;
}
