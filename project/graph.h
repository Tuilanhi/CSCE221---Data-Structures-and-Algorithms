/*
/ File name: graph.h
/ Project number: CSCE 221 Project, Spring 2022
/ Date file was created: April 22, 2022
/ Section: 511
/ Name: Nhi Vu, Joshua Hillis
/ email address: vuthuynhi@tamu.edu joshuahillis292002@tamu.edu
/ This header file contains the implementation of the functions in class Graph, in which it creates a graph, add vertex and edges to the graph, checks if the graph
/ contains a given vertex or edge, remove a given vertex and edge. class Graph also includes the implementation of Prim and Dijkstra that finds the shortest path between
/ 2 vertices, and prints out the path.
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <iostream>
#include <sstream>
#include <cstddef>
#include <queue>

using namespace std;

class Graph
{
private:
    struct Node
    {
        size_t src_id;
        list<Node *> adj;
        double cost = INFINITY;
        bool known = false;
        Node *path = nullptr;
        Node(size_t id) : src_id(id), adj() {}
    };
    unordered_map<size_t, unordered_map<size_t, double> > edge;
    unordered_map<size_t, Node *> vertex;

public:
    // Task 1
    Graph();
    Graph(const Graph &other);
    Graph &operator=(const Graph &other);
    ~Graph();

    size_t vertex_count() const;
    size_t edge_count() const;

    bool contains_vertex(size_t id) const;
    bool contains_edge(size_t src, size_t dest) const;
    double cost(size_t src, size_t dest) const;

    bool add_vertex(size_t id);
    bool add_edge(size_t src, size_t dest, double weight = 1);
    bool remove_vertex(size_t id);
    bool remove_edge(size_t src, size_t dest);

    // Task 2
    void prim(size_t source_id);
    bool is_path(size_t id) const;
    void print_path(size_t dest_id, std::ostream &os = std::cout) const;
    // Task 3
    void dijkstra(size_t source_id);
    double distance(size_t id) const;
    void print_help(size_t id, std::ostream &os = std::cout) const;
    void print_shortest_path(size_t dest_id, std::ostream &os = std::cout) const;
};

// name: constructor
// precondition: the graph has not been initialized
// postcondition: the graph has been created
Graph::Graph() : edge(), vertex() {}

// name: copy constructor
// precondition: the graph has not constructed its copied version
// postcondition: the graph has constructor a copied version of it
Graph::Graph(const Graph &other)
{
    for (auto V : other.vertex)
    {
        add_vertex(V.first);
    }

    for (auto A : other.edge)
    {
        for (auto B : A.second)
        {
            add_edge(A.first, B.first, B.second);
        }
    }
}
// name: copy assignment
// precondition: the graph has not copied the orig graph to the copied version
// postcondition: the graph has copied the orig graph to the copied version
Graph &Graph::operator=(const Graph &other)
{
    if (&other == this)
    {
        return *this;
    }

    edge.clear();

    for (auto V : other.vertex)
    {
        add_vertex(V.first);
    }

    for (auto A : other.edge)
    {
        for (auto B : A.second)
        {
            add_edge(A.first, B.first, B.second);
        }
    }

    return *this;
}

// name: destructor
// precondition: the graph has not destroyed itself
// postcondition: the graph has been destroyed
Graph::~Graph()
{
    edge.clear();

    for (auto V : vertex)
    {
        delete V.second;
    }
}

// name: vertex_count
// precondition: do not know the number of vertices in the graph
// postcondition: returns the number of vertices in the graph
size_t Graph::vertex_count() const
{
    return vertex.size();
}

// name: edge_count
// precondition: do not know the number of edges in the graph
// postcondition: returns the number of edges in the graph
size_t Graph::edge_count() const
{
    size_t sum = 0;
    for (auto current : vertex)
    {
        sum += current.second->adj.size();
    }
    return sum;
}

// name: contains_edge
// precondition: do not know if the graph contains the given vertex
// postcondition: returns true if the graph contains the given vertex and false otherwise
bool Graph::contains_vertex(size_t id) const
{
    if (vertex.count(id) == 1)
    {
        return true;
    }
    return false;
}

// name: contains_edge
// precondition: do not know if the graph contains the given edge
// postcondition: returns true if the graph contains the given edge and false otherwise
bool Graph::contains_edge(size_t src, size_t dest) const
{
    if (contains_vertex(src) && contains_vertex(dest))
    {
        return edge.count(src) == 1 && edge.at(src).count(dest) == 1;
    }
    return false;
}

// name: cost
// precondition: do not know the weight of the edge between src and dest
// postcondition: returns the weight of the edge between src and dest, or infinity if none exists
double Graph::cost(size_t src, size_t dest) const
{
    if (contains_edge(src, dest))
    {
        return edge.at(src).at(dest);
    }
    return INFINITY;
}

// name: add_vertex
// precondition: do not the know if the given vertex has already been inserted
// postcondition: returns true if the given vertex has been added successfully and false otherwise
bool Graph::add_vertex(size_t id)
{
    // Check that the vertex isn't already in the matrix
    if (contains_vertex(id))
    {
        return false;
    }

    vertex[id] = new Node(id);
    return true;
}

// name: add_edge
// precondition: do not the know if the given edge has already been inserted
// postcondition: returns true if the given edge has already been added successfully and false otherwise
bool Graph::add_edge(size_t src, size_t dest, double weight)
{
    if (contains_edge(src, dest) || !contains_vertex(src) || !contains_vertex(dest))
    {
        return false;
    }
    edge[src][dest] = weight;
    vertex.at(src)->adj.push_back(vertex.at(dest));
    return true;
}

// name: remove_vertex
// precondition: do not the know if the vertex has been successfully removed
// precondition: returns true if the vertex has been removed and false otherwise
bool Graph::remove_vertex(size_t id)
{
    if (!contains_vertex(id))
    {
        return false;
    }

    // Clear the destination nodes from the source node, then delete the source
    Node *current = vertex.at(id);
    for (auto neighbor : vertex)
    {
        neighbor.second->adj.remove(current);
        edge[neighbor.first].erase(current->src_id);
    }

    edge.erase(current->src_id);
    // Erase the vertex
    vertex.erase(current->src_id);

    delete current;

    return true;
}

// name: remove_edge
// precondition: do not know if the edge is removed
// postcondition: returns true if the edge is successfully removed and false otherwise
bool Graph::remove_edge(size_t src, size_t dest)
{
    if (!contains_edge(src, dest))
    {
        return false;
    }
    // easier than vertex
    edge.at(src).erase(dest);
    vertex.at(src)->adj.remove(vertex.at(dest));
    return true;
}

// name: prim
// precondition: do not know the minimum spanning tree from the specified source vertex to all other vertices
// postcondition: compute the minimum spanning tree from the specified source vertex to all other vertices in the graph
void Graph::prim(size_t source_id)
{
    for (auto [v_id, v] : vertex)
    {
        v->known = false;
        v->cost = INFINITY;
        v->path = nullptr;
        v->src_id = v_id;
    }

    if (contains_vertex(source_id))
    {
        Node *v = vertex.at(source_id);

        v->cost = 0;

        auto cmp = [](Node *left, Node *right)
        { return left->cost > right->cost; };
        priority_queue<Node *, vector<Node *>, decltype(cmp)> pq(cmp);
        pq.push(v);

        while (!pq.empty())
        {
            v = pq.top();
            pq.pop();
            v->cost = 0;
            v->known = true;

            for (auto iterator : v->adj)
            {
                double path_cost = cost(v->src_id, iterator->src_id);
                if (iterator->known == false)
                {
                    if (iterator->cost > path_cost)
                    {
                        iterator->cost = path_cost;
                        iterator->path = v;
                        pq.push(iterator);
                    }
                }
            }
        }
    }
    // if vertex does not exist
    else
    {
        return;
    }
}

// name: is_path
// precondition: do not know if theres a path from prim source vertex to the destination vertex
// postcondition: returns true if there is a path from prim source vertex to the destination vertex
bool Graph::is_path(size_t id) const
{
    Node *current_node = vertex.at(id);
    if (current_node->cost == INFINITY && current_node->known == false)
    {
        return false;
    }
    return true;
}

// name: print_help
// precondition: prim and dijsktra are not pretty printing
// postcondition: help prim and dijsktra are pretty printing
void Graph::print_help(size_t id, ostream &os) const
{
    Node *node = vertex.at(id);
    if (node->path == nullptr)
    {
        os << node->src_id;
        return;
    }
    print_help(node->path->src_id, os);
    os << " --> " << node->src_id;
}

// name: print_path
// precondition: the minimum spanning path from the prim source vertex to the specified destination vertex in a --> has not been printed
// postcondition: the minimum spanning path from the prim source vertex to the specified destination vertex in a --> has been printed
void Graph::print_path(size_t dest_id, ostream &os) const
{
    if (!contains_vertex(dest_id) || !is_path(dest_id))
    {
        os << "<no path>\n";
        return;
    }
    print_help(dest_id, os);
    os << endl;
}

// name: dijkstra
// precondition: the shortest path from the specified source vertex to all vertices in the graph has not been computed
// postcondition: returns the shortest path from the specified source vertex to all vertices in the graph
void Graph::dijkstra(size_t source_id)
{
    for (auto [v_id, v] : vertex)
    {
        v->known = false;
        v->cost = INFINITY;
        v->path = nullptr;
        v->src_id = v_id;
    }

    if (contains_vertex(source_id))
    {
        Node *v = vertex.at(source_id);

        v->cost = 0;

        auto cmp = [](Node *left, Node *right)
        { return left->cost > right->cost; };
        priority_queue<Node *, vector<Node *>, decltype(cmp)> pq(cmp);
        pq.push(v);

        while (!pq.empty())
        {
            v = pq.top();
            pq.pop();
            v->known = true;
            for (auto neighbor : v->adj)
            {
                double total_cost = v->cost + cost(v->src_id, neighbor->src_id);
                if (neighbor->known == false)
                {
                    if (neighbor->cost > total_cost)
                    {
                        neighbor->cost = total_cost;
                        neighbor->path = v;
                        pq.push(neighbor);
                    }
                }
            }
        }
    }
    // vertex does not exist
    else
    {
        return;
    }
    // TODO
}

// name: distance
// precondition: the cost of the shortest path from the dijkstra vertex to the specified destination vertex in unknown
// postcondition: returns the cost of the shortest path from the dijkstra vertex to the specified destination vertex in the graph
double Graph::distance(size_t id) const
{
    if (contains_vertex(id))
    {
        Node *v = vertex.at(id);
        return v->cost;
    }
    return INFINITY;
}

// name: print_shortest_path
// precondition: the shortest path from the Dijkstra source vertex to the specified destination vertex has not been printed
// postcondition: the shortest path from the Dijkstra source vertex to the specified destination vertex has been printed
void Graph::print_shortest_path(size_t dest_id, ostream &os) const
{
    if (!contains_vertex(dest_id) || !is_path(dest_id))
    {
        os << "<no path>\n";
        return;
    }
    print_help(dest_id, os);
    os << " distance: " << distance(dest_id);
    os << endl;
}
#endif // GRAPH_H