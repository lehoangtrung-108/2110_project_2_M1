// Purpose: Custom separate-chaining hash table for facility IDs. Author: Project team.
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "Facility.h"
#include <list>
#include <string>
#include <vector>
class HashTable {
public:
    explicit HashTable(std::size_t capacity = 11);
    bool insert(const Facility& facility);
    const Facility* find(const std::string& id) const;
    static std::string normalize(const std::string& value);
    static bool validId(const std::string& id);
    std::size_t capacity() const;
    std::size_t size() const;
    std::size_t collisions() const;
private:
    std::size_t hash(const std::string& key) const;
    std::vector<std::list<Facility>> buckets_;
    std::size_t entries_ = 0;
    std::size_t collisions_ = 0;
};
#endif
