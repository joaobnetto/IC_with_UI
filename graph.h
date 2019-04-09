#ifndef GRAPH_H
#define GRAPH_H

#include <QVector>
#include "sala.h"
#include <vector>
#include <deque>

class Graph
{
private:
    struct Edge{
        int from, to, capacity, cost;
    };
    std::vector<std::vector<int>> adj, cost, capacity;
    void shortest_paths(int n, int v0, std::vector<int>& d, std::vector<int>& p);
    std::vector < Edge > edges;
public:

    int min_cost_flow(int N, int K, int s, int t);
    void criaArestas(const QVector < Pedido > &pedidos, const QVector < Sala > &salas);
    void iterarArestas(const QVector < Pedido > &pedidos, QVector < Sala > &salas, int dia, int turno, int k, QSet < int > &nao_alocados);
};

#endif // GRAPH_H
