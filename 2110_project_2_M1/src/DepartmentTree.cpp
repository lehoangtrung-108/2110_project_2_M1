// Purpose: Implements department insertion, search, and preorder displays. Author: Project team.
#include "DepartmentTree.h"
#include <cctype>
#include <iostream>
void DepartmentTree::collectPreorder(const Node* node, std::vector<std::string>& out) const {
    if (!node) return;
    out.push_back(node->name);
    for (const auto& child:node->children) collectPreorder(child.get(),out);
}
DepartmentTree::Node* DepartmentTree::findNode(const std::string& name) const {
    std::vector<std::string> unused;
    if (!root_) return nullptr;
    std::vector<Node*> stack{root_.get()};
    auto norm=[](const std::string& x){ std::string y=x; for(char& c:y)c=static_cast<char>(std::tolower(static_cast<unsigned char>(c))); return y; };
    while(!stack.empty()) {
        Node* n=stack.back(); stack.pop_back();
        if(norm(n->name)==norm(name)) return n;
        for(auto it=n->children.rbegin();it!=n->children.rend();++it) stack.push_back(it->get());
    }
    return nullptr;
}
bool DepartmentTree::add(const std::string& name, const std::string& parent, std::string& reason) {
    if(name.empty()) { reason="department name cannot be blank"; return false; }
    if(findNode(name)) { reason="duplicate department: "+name; return false; }
    if(!root_) {
        if(!parent.empty() && parent!="NONE") { reason="the root must have parent NONE"; return false; }
        root_=std::make_unique<Node>(name,nullptr); return true;
    }
    Node* p=findNode(parent);
    if(!p) { reason="unknown parent: "+parent; return false; }
    p->children.push_back(std::make_unique<Node>(name,p));
    return true;
}
bool DepartmentTree::contains(const std::string& name) const { return findNode(name)!=nullptr; }
void DepartmentTree::search(const std::string& name) const {
    Node* n=findNode(name);
    if(!n) { std::cout<<"Department not found: "<<name<<"\n"; return; }
    int depth=0; for(Node* p=n->parent;p;p=p->parent) ++depth;
    std::cout<<"Name: "<<n->name<<"\nParent: "<<(n->parent?n->parent->name:"None")
             <<"\nDirect children: "<<n->children.size()<<"\nDepth: "<<depth<<"\n";
}
void DepartmentTree::printIndented(const Node* node,int depth) const {
    if(!node)return;
    for(int i=0;i<depth;++i) std::cout<<"    ";
    std::cout<<node->name<<"\n";
    for(const auto& child:node->children) printIndented(child.get(),depth+1);
}
void DepartmentTree::displayHierarchy() const {
    if(!root_) { std::cout<<"No departments are loaded.\n"; return; }
    printIndented(root_.get(),0);
}
void DepartmentTree::preorder() const {
    if(!root_) { std::cout<<"No departments are loaded.\n"; return; }
    std::vector<std::string> names; collectPreorder(root_.get(),names);
    for(std::size_t i=0;i<names.size();++i) std::cout<<(i?" -> ":"")<<names[i];
    std::cout<<"\n";
}
bool DepartmentTree::empty() const { return !root_; }
