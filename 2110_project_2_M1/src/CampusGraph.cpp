// Purpose: Implements the campus adjacency-list graph and BFS. Author: Project team.
#include "CampusGraph.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <queue>
#include <vector>
std::string CampusGraph::normalize(const std::string& value) {
    std::string out = value;
    for (char& c : out) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return out;
}
int CampusGraph::indexOf(const std::string& name) const {
    const std::string key = normalize(name);
    for (std::size_t i=0; i<vertices_.size(); ++i)
        if (normalize(vertices_[i].name) == key) return static_cast<int>(i);
    return -1;
}
bool CampusGraph::addBuilding(const std::string& name) {
    if (name.empty() || indexOf(name) >= 0) return false;
    vertices_.push_back({name, {}});
    return true;
}
bool CampusGraph::addConnection(const std::string& a, const std::string& b, std::string& reason) {
    int u=indexOf(a), v=indexOf(b);
    if (u<0) { reason="unknown building: "+a; return false; }
    if (v<0) { reason="unknown building: "+b; return false; }
    if (u==v) { reason="self-connection"; return false; }
    if (std::find(vertices_[u].neighbors.begin(),vertices_[u].neighbors.end(),v)!=vertices_[u].neighbors.end()) {
        reason="duplicate or reversed connection"; return false;
    }
    vertices_[u].neighbors.push_back(v);
    vertices_[v].neighbors.push_back(u);
    ++edges_;
    return true;
}
bool CampusGraph::hasBuilding(const std::string& name) const { return indexOf(name)>=0; }
std::string CampusGraph::canonicalName(const std::string& name) const {
    int i=indexOf(name); return i<0 ? "" : vertices_[i].name;
}
void CampusGraph::display() const {
    if (vertices_.empty()) { std::cout<<"No buildings are loaded.\n"; return; }
    for (const auto& v:vertices_) {
        std::cout<<v.name<<":";
        if (v.neighbors.empty()) std::cout<<" (no connections)";
        else for (int n:v.neighbors) std::cout<<" "<<vertices_[n].name;
        std::cout<<"\n";
    }
}
void CampusGraph::displayDegrees() const {
    std::cout<<"Total buildings: "<<vertices_.size()<<"\nTotal connections: "<<edges_<<"\n";
    for (const auto& v:vertices_) std::cout<<v.name<<" degree: "<<v.neighbors.size()<<"\n";
}
void CampusGraph::bfs(const std::string& start) const {
    int s=indexOf(start);
    if (s<0) { std::cout<<"Unknown building: "<<start<<"\n"; return; }
    std::vector<bool> visited(vertices_.size(),false);
    std::vector<int> distance(vertices_.size(),-1);
    std::queue<int> q; visited[s]=true; distance[s]=0; q.push(s);
    std::size_t reached=0;
    while(!q.empty()) {
        int u=q.front(); q.pop(); ++reached;
        std::cout<<vertices_[u].name<<" (distance "<<distance[u]<<")\n";
        for(int v:vertices_[u].neighbors) if(!visited[v]) {
            visited[v]=true; distance[v]=distance[u]+1; q.push(v);
        }
    }
    std::cout<<"Reachable: "<<reached<<" of "<<vertices_.size()<<" buildings\n";
}
std::size_t CampusGraph::buildingCount() const { return vertices_.size(); }
std::size_t CampusGraph::connectionCount() const { return edges_; }
