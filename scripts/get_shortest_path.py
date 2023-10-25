# 随机生成若干条同起点路径

import osmnx as ox
import numpy as np
import random
import networkx as nx

# 加载沈阳地图
G =  ox.load_graphml(r"/mnt/d/MyDocuments/WXRecv/WeChat Files/wxid_nsgq9j12gqso12/FileStorage/File/2023-10/ShangHai2")
graph = G

nodes ,_ = ox.graph_to_gdfs(G)

# 随机生成100条路线 可以改
lines = 10

res = []

while lines > 0:
    print(lines)
    lines -=1
    # origin_osmid = nodes.index.values[random.randint(0,nodes.shape[0])]
    destination_osmid = nodes.index.values[random.randint(0,nodes.shape[0])]


    latitude_origin, longitude_origin = G.nodes[347648656]['x'],G.nodes[347648656]['y']
    latitude_destination, longitude_destination =  G.nodes[destination_osmid]['x'],G.nodes[destination_osmid]['y']

    # Select origin and destination nodes
    origin = ox.distance.nearest_nodes(graph, X=latitude_origin, Y=longitude_origin)
    destination = ox.distance.nearest_nodes(graph, X=latitude_destination, Y=longitude_destination)

    # Compute the shortest path
    shortest_path = nx.shortest_path(graph, origin, destination, weight="length")

    points = []

    for id in shortest_path:
        points.append([G.nodes[id]['x'],G.nodes[id]['y'],0])
    points = np.array(points)

    ls =  []
    for i in range(len(points) - 1):
        ls.append(
            [points[i][0],points[i][1]]
        )

    res.append({"coords":ls})
    
    
with open("data/shenyang11.json","w+") as f:
    print(str(res).replace('\'','\"'),file=f)
