#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <set>

class Vertex; 

class Edge {
    
    friend class Graph;
    friend class Vertex;

    Vertex* dest;
    double weight;

    Edge(Vertex* d, double w) {
        dest = d;
        weight = w;
    }
};

class Vertex {
    friend class Graph;

    std::string name;
    std::vector<Edge*> edges;

    Vertex(std::string n) {
        name = n;
    }
};

class Graph {
    std::vector<Vertex*> vertices;
    std::unordered_map<std::string, int> name_to_index;
    std::vector<std::vector<double>> matrix; 

    
    void dfs_helper(Vertex* v, std::set<std::string>& visited) {
        visited.insert(v->name);
        std::cout << v->name << " ";

        for (int i = 0; i < v->edges.size(); i++) {
            Edge* e = v->edges[i];
            if (visited.find(e->dest->name) == visited.end()) {
                dfs_helper(e->dest, visited);
            }
        }
    }

public:
    
    ~Graph() {
        for (int i = 0; i < vertices.size(); i++) {
            for (int j = 0; j < vertices[i]->edges.size(); j++) {
                delete vertices[i]->edges[j];
            }
            delete vertices[i];
        }
    }

    void add_vertex_if_not_exists(const std::string& name) {
        if (name_to_index.find(name) == name_to_index.end()) {
            Vertex* new_v = new Vertex(name);
            vertices.push_back(new_v);
            name_to_index[name] = vertices.size() - 1;
        }
    }

    void add_edge(const std::string& begin, const std::string& end, double value) {
        add_vertex_if_not_exists(begin);
        add_vertex_if_not_exists(end);

        int index_begin = name_to_index[begin];
        Vertex* v_begin = vertices[index_begin];
        
        int index_end = name_to_index[end];
        Vertex* v_end = vertices[index_end];

        Edge* new_edge = new Edge(v_end, value);
        v_begin->edges.push_back(new_edge);
    }

    
    void read_from_file(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Fichier introuvable");
        }
        std::string from, to;
        double value;
        while (file >> from >> to >> value) {
            add_edge(from, to, value);
        }
        file.close();
    }

    
    void dfs() {
        std::set<std::string> visited;
        std::cout << "Parcours DFS : ";
        for (int i = 0; i < vertices.size(); i++) {
            if (visited.find(vertices[i]->name) == visited.end()) {
                dfs_helper(vertices[i], visited);
            }
        }
        std::cout << std::endl;
    }

    
    void build_matrix() {
        int n = vertices.size();
        matrix.assign(n, std::vector<double>(n, 999999.9)); // 999999.9 simule l'infini

        for (int i = 0; i < n; i++) {
            matrix[i][i] = 0.0; 
            for (int j = 0; j < vertices[i]->edges.size(); j++) {
                Edge* e = vertices[i]->edges[j];
                int dest_index = name_to_index[e->dest->name];
                matrix[i][dest_index] = e->weight;
            }
        }
    }

    void floyd_warshall() {
        build_matrix();
        int n = vertices.size();

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (matrix[i][k] + matrix[k][j] < matrix[i][j]) {
                        matrix[i][j] = matrix[i][k] + matrix[k][j];
                    }
                }
            }
        }

        std::cout << "Plus courts chemins (Floyd-Warshall) :" << std::endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 999999.9) std::cout << "INF\t";
                else std::cout << matrix[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    try {
        Graph g;
        g.read_from_file("graph0.gr");
        g.dfs();
        g.floyd_warshall();
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    return 0;
}