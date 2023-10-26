# 把osm图转为nodes和edges

import  osmnx as ox
import numpy as np

G =  ox.load_graphml(r"/mnt/d/MyDocuments/WXRecv/WeChat Files/wxid_nsgq9j12gqso12/FileStorage/File/2023-10/ShangHai2")

nodes_sh,edges_sh=ox.graph_to_gdfs(G)
osmids = nodes_sh.index.values

edges = []
for ll in range(edges_sh.shape[0]):
    edge = edges_sh.iloc[ll]
    edge = (edge.name[0],edge.name[1],edge.length)
    edges.append(edge)
edges = np.array(edges)


nodes_sh['index'] = nodes_sh.index.values
nodes = nodes_sh[['x','y','index']].values

np.savetxt("data/edges.txt",edges.astype(np.float64),fmt="%.8lf")
np.savetxt("data/nodes.txt",nodes.astype(np.float64),fmt="%.8lf")