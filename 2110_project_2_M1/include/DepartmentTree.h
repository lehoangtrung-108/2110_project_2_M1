// Purpose: Implements the general academic department tree. Author: Project team.
#ifndef DEPARTMENTTREE_H
#define DEPARTMENTTREE_H
#include <memory>
#include <string>
#include <vector>
class DepartmentTree {
public:
    bool add(const std::string& name, const std::string& parent, std::string& reason);
    bool contains(const std::string& name) const;
    void search(const std::string& name) const;
    void displayHierarchy() const;
    void preorder() const;
    bool empty() const;
private:
    struct Node {
        std::string name;
        Node* parent;
        std::vector<std::unique_ptr<Node>> children;
        Node(const std::string& n, Node* p) : name(n), parent(p) {}
    };
    Node* findNode(const std::string& name) const;
    void printIndented(const Node* node, int depth) const;
    void collectPreorder(const Node* node, std::vector<std::string>& out) const;
    std::unique_ptr<Node> root_;
};
#endif
