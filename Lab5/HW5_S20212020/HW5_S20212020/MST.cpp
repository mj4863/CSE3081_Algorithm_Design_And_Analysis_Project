#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#define ll long long
using namespace std;

struct Edge {
    int src, dest, weight;
};

// Min Heap 구현
vector<Edge> heap;

void insert_min_heap(Edge item) {
    heap.push_back(item);
    size_t child = heap.size() - 1;
    while (child > 0) {
        int parent = (child - 1) / 2;
        if (heap[parent].weight <= item.weight) break;
        heap[child] = heap[parent];
        child = parent;
    }
    heap[child] = item;
}

Edge delete_min_heap() {
    if (heap.empty()) {
        cerr << "Heap is empty.\n";
        exit(1);
    }

    Edge root = heap[0];
    Edge tmp = heap.back();
    heap.pop_back();

    if (heap.empty()) return root;

    size_t parent = 0, child = 1, n = heap.size();

    while (child < n) {
        if (child + 1 < n && heap[child].weight > heap[child + 1].weight) child++;
        if (tmp.weight <= heap[child].weight) break;
        heap[parent] = heap[child];
        parent = child;
        child = 2 * parent + 1;
    }
    heap[parent] = tmp;

    return root;
}

// Disjoint Set 구현
vector<int> parent, node_rank, componentSize;
vector<ll> componentWeight;
int total_components;

int Find(int x) {
    if (x == parent[x]) return x;
    return parent[x] = Find(parent[x]);
}

void Union(int x, int y, int weight) {
    int rootX = Find(x);
    int rootY = Find(y);

    if (rootX == rootY) return;

    if (node_rank[rootX] < node_rank[rootY]) {
        parent[rootX] = rootY;
        componentWeight[rootY] += componentWeight[rootX] + weight;
        componentSize[rootY] += componentSize[rootX];
    }
    else {
        parent[rootY] = rootX;
        componentWeight[rootX] += componentWeight[rootY] + weight;
        componentSize[rootX] += componentSize[rootY];
        if (node_rank[rootX] == node_rank[rootY]) node_rank[rootX]++;
    }

    total_components--;
}

vector<pair<int, ll>> getComponentInfo() {
    vector<pair<int, ll>> result;
    for (int i = 0; i < parent.size(); i++) {
        int root = Find(i);
        if (root == i) {
            result.push_back({ componentSize[i], componentWeight[i] });
        }
    }
    return result;
}

void kruskal(ifstream& graph, int n, int n_vertices) {
    Edge e;
    for (int i = 0; i < n; i++) {
        graph >> e.src >> e.dest >> e.weight;
        insert_min_heap(e);
    }

    int mst_edge_count = 0;
    int k_scanned = 0;  // 처리한 간선의 개수를 추적
    while (!heap.empty() && mst_edge_count < n_vertices - 1) {
        Edge edge = delete_min_heap();
        k_scanned++;  // 간선을 처리할 때마다 증가

        if (Find(edge.src) != Find(edge.dest)) {
            Union(edge.src, edge.dest, edge.weight);
            mst_edge_count++;
        }
    }

    cout << "Processed edges until MST completion: " << k_scanned << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ifstream in("commands.txt");
    if (!in.is_open()) {
        cerr << "Cannot open the file: commands.txt\n";
        return 1;
    }

    string dir_info, input_file, output_file;
    in >> dir_info >> input_file >> output_file;

    string input_path = dir_info + "/" + input_file;
    string output_path = output_file;

    ifstream in_graph(input_path);
    if (!in_graph.is_open()) {
        cerr << "Cannot open the file: " << input_path << '\n';
        return 1;
    }

    int n_vertices, n_edges, MAX_WEIGHT;
    in_graph >> n_vertices >> n_edges >> MAX_WEIGHT;

    total_components = n_vertices;

    parent.resize(n_vertices);
    for (int i = 0; i < n_vertices; i++) parent[i] = i;

    node_rank.resize(n_vertices, 0);
    componentWeight.resize(n_vertices, 0);
    componentSize.resize(n_vertices, 1);


    clock_t s_time, e_time;
    double exec_time;
    s_time = clock();
    kruskal(in_graph, n_edges, n_vertices);
    e_time = clock();
    exec_time = ((double)(e_time - s_time)) / CLOCKS_PER_SEC;
    cout << "Kruskal Algorithm Run Time: " << exec_time << " s\n";

    vector<pair<int, ll>> answer = getComponentInfo();
    sort(answer.begin(), answer.end());

    ofstream fout(output_path);

    fout << total_components;
    for (auto& comp : answer) {
        fout << '\n' << comp.first << ' ' << comp.second;
    }

    in.close();
    in_graph.close();
    fout.close();

    return 0;
}