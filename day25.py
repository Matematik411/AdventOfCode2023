from igraph import Graph
f = open("inputs/25.txt", "r")
graph = {}

for line in f.readlines():
    n = line.split(": ")
    graph[n[0]] = n[1].split(" ")
    graph[n[0]][-1] = graph[n[0]][-1][:-1]


# print(graph)
gr = Graph.ListDict(graph)
minCut = gr.mincut().sizes()

# print(gr)
print(minCut)

print("a: ", minCut[0] * minCut[1])