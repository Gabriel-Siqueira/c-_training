#include <iostream>
#include <vector>
#include <list>

using namespace std;

typedef enum Set {open,close,none} Set;

typedef struct Edge{
    int end;
    int value;
} Edge;

typedef struct Ver{
    list<Edge> edges;
    int father;
    int distance;
    Set set;
} Ver;

vector<Ver> build_graf(int size){
    int ver1,ver2,edge;
    Edge aux;
    vector<Ver> graf (size);
    for(int i = 0; i < size; i++){
        graf[i].set = none;
    }
    cin >> ver1 >> ver2 >> edge;
    while(ver1 != -1){
        aux.value = edge;
        aux.end = ver2;
        graf[ver1].edges.push_front (aux);
        cin >> ver1 >> ver2 >> edge;
    }
    return graf;
}

int find_closer(vector<Ver> graf, int& closer){
    int i;
    for(i = 0; i < graf.size() && graf[i].set != open; i++);
    if(i == graf.size()) return 0;
    closer = i;
    for(i = i+1; i < graf.size(); i++){
        if(graf[i].set == open && graf[i].distance < graf[closer].distance)
            closer = i;
    }
    return 1;
}

int find_path(vector<Ver> graf,int start,int end){
    int new_closed,distance;
    Edge test;
    graf[start].distance = 0;
    graf[start].father = -1;
    graf[start].set = open;
    while( graf[end].set != close && find_closer(graf,new_closed) ){
        graf[new_closed].set = close;
        while(graf[new_closed].edges.size() != 0){
            test = graf[new_closed].edges.front();
            graf[new_closed].edges.pop_front();
            distance = graf[new_closed].distance + test.value;
            if(graf[test.end].set == open && graf[test.end].distance > distance){
                graf[test.end].distance = distance;
                graf[test.end].father = new_closed;
            }else if(graf[test.end].set == none){
                graf[test.end].distance = distance;
                graf[test.end].father = new_closed;
                graf[test.end].set = open;
            }
        }
    }
    if(graf[end].set == close) return graf[end].distance;
    return -1;
}

int main(){
    int size,start,end;
    vector<Ver> graf;
    int distance;
    cout << "size: ";
    cin >> size;
    graf = build_graf(size);
    cout << "start: ";
    cin >> start;
    cout << "end: ";
    cin >> end;
    distance = find_path(graf,start,end);
    if(distance >= 0) cout << distance << endl;
    return 0;
}
