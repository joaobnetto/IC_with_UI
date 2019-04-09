#include "graph.h"
#include <math.h>
#include <QSet>
#define INFI 1000000000


// Facilmente editar o custo das arestas, faz poder modificar a alocação sem modificar a estrutura.

int calcularCusto(Sala s, Pedido p){
    int k = 0;
    int base = (int) fabs(s.getCapacidade() - p.capacidade);
    int ratio = s.getCapacidade() * 100 / p.capacidade;
    if(s.getTipo() != p.tipo) return -5000000;
    else if(ratio < 80) return -5000000;
    else if(s.getGrupo() != Sala::getPredioGrupo(p.predio)) return -5000000;
    else if(p.predio != s.getPredio()) k = 1;
    bool bf = false;
    for(int i = 0; i < 6;++i){
        for(int j = 0;j < 3;++j){
            for(int k = 0;k < 6;++k){
                if(s.mesmoHorario(i,j,k, p.capacidade, p.info, p.curso, p.predio, p.periodo)){
                    bf = true;
                    break;
                }
            }
            if(bf)break;
        }
        if(bf)break;
    }
    return base + p.periodo*10 - p.prioridade*100 - bf*150 + k*50;

}

void Graph::criaArestas(const QVector < Pedido > &pedidos, const QVector < Sala > &salas){
    int n = pedidos.size(), m = salas.size();
    // std::cout << pedidos.size() << std::endl;
    for(int i = 1;i <= n;++i){
        edges.push_back({0, i, 1, 0});// arestas dos pedidos
    }
    for(int i = 1;i <= m;++i){
        edges.push_back({n+i, n+m+1, 1, 0}); // arestas das salas.
    }
    // imprimeArestas();
    for(int i = 1;i <= m;++i){
        for(int j = 1;j <= n;++j){
            int custo = calcularCusto(salas[i-1], pedidos[j-1]);
            if(custo > -3000000){
                edges.push_back({j,n+i, 1, custo});
            }
        }
    }
}

// Começo do algoritmo MAX_FLOW do emaxx.ru

void Graph::shortest_paths(int n, int v0, std::vector<int>& d, std::vector<int>& p) {
    d.assign(n, INFI);
    d[v0] = 0;
    std::vector<int> m(n, 2);
    std::deque<int> q;
    q.push_back(v0);
    p.assign(n, -1);

    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        m[u] = 0;
        for (int v : adj[u]) {
            if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
                d[v] = d[u] + cost[u][v];
                p[v] = u;
                if (m[v] == 2) {
                    m[v] = 1;
                    q.push_back(v);
                } else if (m[v] == 0) {
                    m[v] = 1;
                    q.push_front(v);
                }
            }
        }
    }
}

int Graph::min_cost_flow(int N, int K, int s, int t) {
    adj.assign(N, std::vector<int>());
    cost.assign(N, std::vector<int>(N, 0));
    capacity.assign(N, std::vector<int>(N, 0));
    for (Edge e : edges) {
        adj[e.from].push_back(e.to);
        adj[e.to].push_back(e.from);
        cost[e.from][e.to] = e.cost;
        cost[e.to][e.from] = -e.cost;
        capacity[e.from][e.to] = e.capacity;
    }

    int flow = 0;
    int cost = 0;
    std::vector<int> d, p;
    while (flow < K) {
        shortest_paths(N, s, d, p);
        if (d[t] == INFI)
            break;

        // find max flow on that path
        int f = K - flow;
        int cur = t;
        while (cur != s) {
            f = std::min(f, capacity[p[cur]][cur]);
            cur = p[cur];
        }

        // apply flow
        flow += f;
        cost += f * d[t];
        cur = t;
        while (cur != s) {
            capacity[p[cur]][cur] -= f;
            capacity[cur][p[cur]] += f;
            cur = p[cur];
        }
    }
    // std::cout << flow << std::endl;
    return flow;
}

// Fim do algoritmo.

// Procuro as arestas que utilizei nessa iteração do max_flow, e salvo as arestas que foram utilizadas
// Desse jeito tenho a ligação da sala ao pedido.

void Graph::iterarArestas(const QVector < Pedido > &pedidos, QVector < Sala > &salas, int dia, int turno, int k, QSet < int > &nao_alocados){
    int n = pedidos.size(), m = salas.size();
    bool found = false;
    QMap < int , int > mark;
    for(int i = 1;i <= m;++i){
        // std::cout << n+i << ": ";
        for(auto j : adj[n+i]){
            if(capacity[n+i][j] == 1 && j <= pedidos.size()){
                salas[i-1].setHorario(dia,turno,k, pedidos[j-1]);
                mark[j]++;
                found = true;
                break;
            }
        }
    }
    for(int i = 1;i <= pedidos.size();++i){
        if(!mark[i]) nao_alocados.insert(pedidos[i-1].pedidoOriginal);
    }
    // std::cout << std::endl;
}
