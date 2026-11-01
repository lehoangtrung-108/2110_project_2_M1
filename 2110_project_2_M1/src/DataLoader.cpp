// Purpose: Reads, validates, and loads campus text files. Author: Project team.
#include "DataLoader.h"
#include <cctype>
#include <fstream>
#include <iostream>
namespace {
std::string lowerCopy(std::string s) {
    for(char& c:s)c=static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return s;
}
}
std::string DataLoader::trim(const std::string& value) {
    const std::string ws=" \t\r\n";
    auto first=value.find_first_not_of(ws);
    if(first==std::string::npos)return "";
    auto last=value.find_last_not_of(ws);
    return value.substr(first,last-first+1);
}
std::vector<std::string> DataLoader::split(const std::string& line) {
    std::vector<std::string> fields; std::size_t start=0;
    while(true) {
        auto pos=line.find('|',start);
        fields.push_back(trim(line.substr(start,pos==std::string::npos?pos:pos-start)));
        if(pos==std::string::npos)break;
        start=pos+1;
    }
    return fields;
}
bool DataLoader::load(const std::string& dir,std::vector<Facility>& facilities,
                      HashTable& table,CampusGraph& graph,DepartmentTree& tree) const {
    bool allOpened=true;
    auto process=[&](const std::string& filename, auto handler) {
        std::ifstream in(dir+"/"+filename);
        if(!in) { std::cerr<<"Error: cannot open "<<filename<<"; treating it as empty.\n"; allOpened=false; return; }
        std::string line; std::size_t lineNo=0,accepted=0,rejected=0;
        while(std::getline(in,line)) {
            ++lineNo;
            std::string t=trim(line);
            if(t.empty() || t[0]=='#')continue;
            std::string reason;
            if(handler(split(line),reason)) ++accepted;
            else { ++rejected; std::cerr<<"Warning: "<<filename<<":"<<lineNo<<": "<<reason<<"\n"; }
        }
        std::cout<<filename<<": "<<accepted<<" accepted, "<<rejected<<" rejected";
        if(filename=="facilities.txt")
            std::cout<<" (hash capacity "<<table.capacity()<<", entries "<<table.size()<<", collisions "<<table.collisions()<<")";
        std::cout<<"\n";
    };
    process("buildings.txt",[&](const auto& f,std::string& r){
        if(f.size()!=1){r="expected 1 field";return false;}
        if(f[0].empty()){r="empty building name";return false;}
        if(!graph.addBuilding(f[0])){r="duplicate building name";return false;} return true;
    });
    process("connections.txt",[&](const auto& f,std::string& r){
        if(f.size()!=2){r="expected 2 fields";return false;}
        if(f[0].empty()||f[1].empty()){r="empty required field";return false;}
        return graph.addConnection(f[0],f[1],r);
    });
    process("facilities.txt",[&](const auto& f,std::string& r){
        if(f.size()!=4){r="expected 4 fields";return false;}
        if(f[0].empty()||f[1].empty()||f[2].empty()||f[3].empty()){r="empty required field";return false;}
        Facility x{HashTable::normalize(f[0]),f[1],graph.canonicalName(f[2]),f[3]};
        if(!HashTable::validId(x.id)){r="invalid facility ID; expected F plus exactly three digits";return false;}
        if(x.building.empty()){r="unknown building: "+f[2];return false;}
        if(table.find(x.id)){r="duplicate facility ID: "+x.id;return false;}
        table.insert(x); facilities.push_back(x); return true;
    });
    process("departments.txt",[&](const auto& f,std::string& r){
        if(f.size()!=2){r="expected 2 fields";return false;}
        if(f[0].empty()||f[1].empty()){r="empty required field";return false;}
        std::string parent=lowerCopy(f[1])=="none"?"NONE":f[1];
        return tree.add(f[0],parent,r);
    });
    return allOpened;
}
