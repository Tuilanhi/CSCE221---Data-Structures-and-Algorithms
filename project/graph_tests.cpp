/*
/ File name: graph_tests.cpp
/ Project number: CSCE 221 Project, Spring 2022
/ Date file was created: April 22, 2022
/ Section: 511
/ Name: Nhi Vu, Joshua Hillis
/ email address: vuthuynhi@tamu.edu joshuahillis292002@tamu.edu
/ This cpp file contains the implementation of testing cases for the functions in Graph header files. It creates a graph and add in vertices and edges for the Graph,
/ and calls the prim and dijsktra function to print out the shortest path from a given vertex to another by calculating its cost.
*/

#include <iostream>
#include <sstream>
#include "graph.h"

using std::cout, std::endl;

int main()
{
    std::cout << "make an empty digraph" << std::endl;
    Graph G;

    std::cout << "add vertices" << std::endl;
    for (size_t n = 0; n <= 8; n++)
    {
        G.add_vertex(n);
    }

    std::cout << "add directed edges" << std::endl;
    G.add_edge(5, 6, 1);
    G.add_edge(8, 7, 2);
    G.add_edge(4, 2, 3);
    G.add_edge(8, 6, 4);
    G.add_edge(8, 5, 5);
    G.add_edge(5, 8, 6);
    G.add_edge(6, 7, 7);
    G.add_edge(7, 2, 8);
    G.add_edge(7, 4, 9);
    G.add_edge(0, 2, 10);
    G.add_edge(4, 1, 11);
    G.add_edge(6, 4, 12);
    G.add_edge(1, 2, 13);
    G.add_edge(1, 0, 14);
    G.add_edge(5, 3, 15);
    G.add_edge(6, 3, 16);
    G.add_edge(4, 3, 17);
    G.add_edge(3, 0, 18);
    G.add_edge(3, 1, 19);

    std::cout << "G has " << G.vertex_count() << " vertices" << std::endl;
    std::cout << "G has " << G.edge_count() << " edges" << std::endl;
    std::cout << std::endl;

    std::cout << "compute mst path from 0" << std::endl;
    G.prim(0);

    std::cout << "print minimum spanning paths" << std::endl;
    for (size_t n = 0; n <= 8; n++)
    {
        std::cout << "minimum spanning path from 0 to " << n << std::endl;
        std::cout << "  ";
        G.print_path(n);
    }
    std::cout << std::endl;

    std::cout << "compute shortest path from 2" << std::endl;
    G.dijkstra(2);

    std::cout << "print shortest paths" << std::endl;
    for (size_t n = 1; n <= 7; n++)
    {
        std::cout << "shortest path from 2 to " << n << std::endl;
        std::cout << "  ";
        G.print_shortest_path(n);
    }

    // Testing copy constructor and copy assignment
    Graph J(G);
    Graph K;
    K.operator=(G);

    // Testing remove vertex
    K.remove_vertex(7);
    K.remove_vertex(6);
    K.remove_vertex(1);

    // Testing remove edge
    K.remove_edge(2, 5);

    // Test is_path
    K.is_path(2);

    Graph X;
    Graph Y;

    // Make another graph
    for (int i = 1; i <= 6; i++)
    {
        X.add_vertex(i);
    }

    // Test add_edges more
    X.add_edge(1, 5, 6);
    X.add_edge(2, 6, 3);
    X.add_edge(2, 1, 1);
    X.add_edge(2, 4, 3);
    X.add_edge(3, 4, 3);
    X.add_edge(3, 6, 3);
    X.add_edge(5, 3, 3);
    X.add_edge(6, 4, 4);

    // Another graph
    Y = X;

    X.dijkstra(2);

    std::cout << "\n\n";

    std::cout << "print shortest paths for X: " << std::endl;
    for (size_t n = 1; n <= 6; n++)
    {
        std::cout << "shortest path from 2 to " << n << std::endl;
        std::cout << "  ";
        X.print_path(n);
    }
    std::cout << std::endl;

    cout << "Calculating the cost between (1, 5): " << X.cost(1, 5) << endl;

    cout << "Does Graph X contains vertex 3? " << boolalpha << X.contains_vertex(3) << endl;
    cout << "Is edge (3, 4) available? " << boolalpha << X.contains_edge(3, 4) << endl;

    // Test remove vertex more
    X.remove_vertex(2);
    X.remove_vertex(3);

    cout << "Does Graph X contains vertex 3? " << boolalpha << X.contains_vertex(3) << endl;
    cout << "Is edge (3, 4) available? " << boolalpha << X.contains_edge(3, 4) << endl;
    cout << "Calculating the cost between (3, 4): " << X.cost(3, 4) << endl;
    cout << endl;

    Y.prim(2);

    std::cout << "print minimum spanning paths for Y: " << std::endl;
    for (size_t n = 1; n <= 6; n++)
    {
        std::cout << "shortest path from 2 to " << n << std::endl;
        std::cout << "  ";
        Y.print_shortest_path(n);
    }
    std::cout << std::endl;

    Graph Z;
    Z = Y;

    // Test for no path, distance in a non-existent path, non-existent vertex
    std::cout << "Printing non existent path: " << std::endl;
    Z.print_shortest_path(28);
    std::cout << "Distance for non existent path: " << Z.distance(28) << std::endl;
    std::cout << "Z contains vertex 28: " << Z.contains_vertex(28) << std::endl;

    // Try and add an edge to a non-existent vertex
    Z.add_edge(2, 28, 4);
    // Try and add a vertex that's already in the graph, and remove a non-existent vertex
    Z.add_vertex(2);
    Z.remove_vertex(28);
    // Try removing a non-existent edge
    Z.remove_edge(2, 28);
    // Test self assignment
    Z = Z;
    // Try prim's and dijkstra's from a non-existent vertex
    Z.prim(28);
    Z.dijkstra(28);

    // Print non-existent path
    Z.print_path(28);
    return 0;
}