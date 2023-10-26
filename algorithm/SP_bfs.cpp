#include <bits/stdc++.h>

using namespace std;

const int N = 1e7, M = 1e6;

map<string, int> nodes_id;
vector<int> path[M];
int h[N], ne[N * 2], e[N * 2], dis[N], idx;
bool st[M];
double w[N];
queue<int> q;

int nodes_num, edges_num;
ofstream ofs;

struct Nodes
{
    double x, y;
    string id;
} nodes[M];

struct Edges
{
    string node1_id, node2_id;
    double w;
} edges[M];

void add(int a, int b, double c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

void init()
{
    memset(h, -1, sizeof h);

    for (int i = 0; i < edges_num; i++)
    {
        string id_1 = edges[i].node1_id, id_2 = edges[i].node2_id;
        double c = edges[i].w;

        int a = nodes_id[id_1], b = nodes_id[id_2];
        add(a, b, c), add(b, a, c);
    }
}

void write_x(int u)
{
    int id = path[u][0];
    double x = nodes[id].x, y = nodes[id].y;
    ofs << to_string(x);
    for (int i = 1; i < path[u].size(); i++)
    {
        int id = path[u][i];
        double x = nodes[id].x;
        ofs << "," << to_string(x);
    }
    ofs << "\n"
        << to_string(y);
}

void write_y(int u)
{
    for (int i = 1; i < path[u].size(); i++)
    {
        int id = path[u][i];
        double y = nodes[id].y;
        ofs << "," << to_string(y);
    }
    ofs << "\n"
        << "\n";
}

void bfs(const string& s1,const string& s2)
{
    
    int start = nodes_id[s1], end = nodes_id[s2];

    q.push(start);
    st[start] = true;
    path[start].push_back(start);

    while (q.size())
    {
        int t = q.front();
        q.pop();

        if (t == end)
        {
            write_x(t);
            write_y(t);
            break;
        }

        // 遍历所有邻边
        for (int i = h[t]; ~i; i = ne[i])
        {
            int j = e[i];
            if (st[j])
                continue;
            st[j] = true;
            q.push(j);

            // 更新路径信息
            dis[j] = dis[t] + 1;
            path[j] = path[t];
            path[j].push_back(j);
        }
    }

    for (int i = 0; i < nodes_num; i++)
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

    if (!fin1.is_open() || !fin2.is_open())
    {
        std::cerr << "cannot open the file" << endl
                  << "end !!";
        exit(0);
    }

    char data[1024];
    while (fin1.getline(data, sizeof(data)))
    {
        stringstream ss(data);
        string temp[5];

        int cnt = 0;
        while (ss >> temp[cnt++])
            ;

        edges[edges_num++] = {temp[0].substr(0, temp[0].find_first_of('.')), temp[1].substr(0, temp[1].find_first_of('.')), stod(temp[2])};
    }
    fin1.close();

    while (fin2.getline(data, sizeof(data)))
    {
        stringstream ss(data);
        string temp[5];

        int cnt = 0;
        while (ss >> temp[cnt++])
            ;

        string id = temp[2].substr(0, temp[2].find_first_of('.'));
        nodes_id[id] = nodes_num;
        nodes[nodes_num++] = {stod(temp[0]), stod(temp[1]), id};
    }
    fin2.close();

    init();

    ofs.open("t.txt");
    if (ofs)
    {
        ofs.clear();
        bfs(argv[1],argv[2]);
        ofs.close();
    }

    return 0;
}