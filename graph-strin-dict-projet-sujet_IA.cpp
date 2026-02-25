#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <set>
#include <limits>
#include <iomanip>

class Vertex;

class Edge {
    friend class Graph;
    friend class Vertex;

    Vertex* destination;
    double weight;

    Edge(Vertex* dest, double w) : destination(dest), weight(w) {}
};

class Vertex {
    friend class Graph;

    std::string name;
    std::vector<Edge*> edges;

    explicit Vertex(std::string n) : name(std::move(n)) {}
};

// Classe Matrix dédiée (Règle 6)
class Matrix {
    friend class Graph;
    size_t size;
    std::vector<std::vector<double>> data;

public:
    explicit Matrix(size_t n) : size(n), data(n, std::vector<double>(n, std::numeric_limits<double>::infinity())) {
        for (size_t i = 0; i < size; ++i) {
            data[i][i] = 0.0;
        }
    }
};

class Graph {
    std::vector<Vertex*> vertices;
    std::unordered_map<std::string, int> name_to_index;
    Matrix* adj_matrix{nullptr};

    void dfs_recursive(const Vertex* current, std::set<std::string>& visited) const {
        visited.insert(current->name);
        std::cout << current->name << " ";

        for (const auto* edge : current->edges) {
            if (visited.find(edge->destination->name) == visited.end()) {
                dfs_recursive(edge->destination, visited);
            }
        }
    }

    Vertex* get_or_create_vertex(const std::string& name) {
        auto it = name_to_index.find(name);
        if (it != name_to_index.end()) {
            return vertices[it->second];
        }
        
        Vertex* new_vertex = new Vertex(name);
        vertices.push_back(new_vertex);
        name_to_index[name] = static_cast<int>(vertices.size() - 1);
        return new_vertex;
    }

public:
    ~Graph() {
        for (auto* vertex : vertices) {
            for (auto* edge : vertex->edges) {
                delete edge;
            }
            delete vertex;
        }
        delete adj_matrix;
    }

    void add_edge(const std::string& begin, const std::string& end, double value) {
        Vertex* v_begin = get_or_create_vertex(begin);
        Vertex* v_end = get_or_create_vertex(end);
        v_begin->edges.push_back(new Edge(v_end, value));
    }

    void load_from_file(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Error: Cannot open file " + filename);
        }

        std::string from, to;
        double value;
        while (file >> from >> to >> value) {
            add_edge(from, to, value);
        }
    }

    void dfs() const {
        std::set<std::string> visited;
        std::cout << "DFS Traversal: ";
        for (const auto* vertex : vertices) { //je ne comprend pas cette boucle 
            if (visited.find(vertex->name) == visited.end()) {
                dfs_recursive(vertex, visited);
            }
        }
        std::cout << "\n";
    }

    void build_adjacency_matrix() {
        delete adj_matrix; // Nettoie si la matrice existe déjà
        size_t n = vertices.size();
        adj_matrix = new Matrix(n);

        for (size_t i = 0; i < n; ++i) {
            for (const auto* edge : vertices[i]->edges) {
                int dest_idx = name_to_index.at(edge->destination->name);
                adj_matrix->data[i][dest_idx] = edge->weight;
            }
        }
    }

    void compute_floyd_warshall() {
        if (!adj_matrix) build_adjacency_matrix();
        
        size_t n = vertices.size();
        auto& dist = adj_matrix->data;

        for (size_t k = 0; k < n; ++k) {
            for (size_t i = 0; i < n; ++i) {
                for (size_t j = 0; j < n; ++j) {
                    if (dist[i][k] != std::numeric_limits<double>::infinity() && 
                        dist[k][j] != std::numeric_limits<double>::infinity()) {
                        if (dist[i][k] + dist[k][j] < dist[i][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                        }
                    }
                }
            }
        }
        print_matrix();
    }

    void print_matrix() const {
        if (!adj_matrix) return;
        size_t n = vertices.size();
        std::cout << "Floyd-Warshall Shortest Paths:\n";
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (adj_matrix->data[i][j] == std::numeric_limits<double>::infinity()) { //vrai infini par l'IA
                    std::cout << std::setw(8) << "INF";
                } else {
                    std::cout << std::setw(8) << adj_matrix->data[i][j];
                }
            }
            std::cout << "\n";
        }
    }
};

int main() {
    try {
        Graph g;
        g.load_from_file("graph0.gr");
        g.dfs();
        g.compute_floyd_warshall();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}

//l'IA me dit qu'elle utilise de la lazy initialisation contrairement a mon code 