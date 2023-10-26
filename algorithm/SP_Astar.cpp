#include <bits/stdc++.h>

#define x first
#define y second

using namespace std;

typedef pair<double, int> PDI;
typedef pair<double, pair<double, int>> PDP;

const int N = 1e7, M = 1e6;

map<string, int> nodes_id;
vector<int> path[M];
int h[N], ne[N * 2], e[N * 2], cnt[M], idx;
int S, T;
bool st[M];
double w[N], dis[N];

int nodes_num, edges_num, k = 1;
ofstream ofs;

struct Nodes
{
    double x, y;
    string id;
}nodes[M];

struct Edges
{
    string node1_id, node2_id;
    double w;
}edges[M];

void add(int a, int b, double c)
{
    e[idx] = b,  w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

void write_x(int u)
{
    int id = path[u][0];
    double x = nodes[id].x, y = nodes[id].y;
    ofs << to_string(x);
    for (int i = 1; i < path[u].size(); i ++ )
    {
        int id = path[u][i];
        double x = nodes[id].x;
        ofs << "," << to_string(x);
    }
    ofs << "\n" << to_string(y);
}

void write_y(int u)
{
    for (int i = 1; i < path[u].size(); i ++ )
    {
        int id = path[u][i];
        double y = nodes[id].y;
        ofs << "," << to_string(y);
    }
    ofs << "\n" << "\n";
}

void init()
{
    memset(h, -1, sizeof h);
    
    for (int i = 0; i < edges_num; i ++ )
    {
        string id_1 = edges[i].node1_id, id_2 = edges[i].node2_id;
        double c = edges[i].w;
        
        int a = nodes_id[id_1], b = nodes_id[id_2];
        add(a, b, c), add(b, a, c);
    }
}

void dijkstra()
{
    priority_queue<PDI, vector<PDI>, greater<PDI>> q;
    memset(dis, 0x3f, sizeof dis);
    dis[T] = 0;
    q.push({0, T});
    
    while (q.size())
    {
        auto t = q.top();
        q.pop();
        int u = t.y;
        double d = t.x;
        
        if (st[u]) continue;
        st[u] = true;
        
        for (int i = h[u]; ~i; i = ne[i])
        {
            int j = e[i];
            if (dis[j] > d + w[i])
            {
                dis[j] = d + w[i];
                q.push({dis[j], j});
            }
        }
    }
}

void Astar()
{
    memset(st, 0, sizeof st);
    priority_queue<PDP, vector<PDP>, greater<PDP>> q;
    q.push({dis[S], {0, S}});
    path[S].push_back(S);
    
    while (q.size())
    {
        auto t = q.top();
        q.pop();
        int u = t.y.y;
        double d = t.y.x;
        
        if (st[u]) continue;
        st[u] = true;

        if (T == u)
        {
           write_x(u);
           write_y(u);
           break; 
        }
        
        for (int i = h[u]; ~i; i = ne[i])
        {
            int j = e[i];
            q.push({dis[j] + d + w[i], {d + w[i], j}}); 
            path[j] = path[u];
            path[j].push_back(j);
        } 
    }

    for (int i = 0; i < nodes_num; i ++ )
        if (st[i])
        {
           write_x(i);
           write_y(i);
        }
}


int main(int argc,char** argv)
{
    ifstream fin1, fin2;
    fin1.open("../data/edges.txt");
    fin2.open("../data/nodes.txt");

    if(!fin1.is_open() || !fin2.is_open())
    {
        std::cerr<<"cannot open the file" << endl << "end !!";
        exit(0);
    }

    char data[1024];
    while (fin1.getline(data, sizeof(data)))
    {
        stringstream ss(data);
        string temp[5];

        int cnt = 0;
        while (ss >> temp[cnt ++]);

        edges[edges_num ++] = {temp[0].substr(0, temp[0].find_first_of('.')), temp[1].substr(0, temp[1].find_first_of('.')), stod(temp[2])};
    }
    fin1.close();

    while (fin2.getline(data, sizeof(data)))
    {
        stringstream ss(data);
        string temp[5];

        int cnt = 0;
        while (ss >> temp[cnt ++]);
        
        string id = temp[2].substr(0, temp[2].find_first_of('.'));
        nodes_id[id] = nodes_num;
        nodes[nodes_num ++] = {stod(temp[0]), stod(temp[1]), id};
    }
    fin2.close();

    init();
    string start(argv[1]), end(argv[2]);
    S = nodes_id[start], T = nodes_id[end];

    ofs.open("t.txt");
    if (ofs)
    {
        ofs.clear();
        dijkstra();
        Astar();
        ofs.close();

    }

    return 0;
}