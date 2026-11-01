// Purpose: Implements custom ID hashing and separate chaining. Author: Project team.
#include "HashTable.h"
#include <cctype>
HashTable::HashTable(std::size_t capacity) : buckets_(capacity ? capacity : 11) {}
std::string HashTable::normalize(const std::string& value) {
    std::string out = value;
    for (char& c : out) c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    return out;
}
bool HashTable::validId(const std::string& id) {
    if (id.size() != 4 || id[0] != 'F') return false;
    return id[1] >= '0' && id[1] <= '9' && id[2] >= '0' && id[2] <= '9' && id[3] >= '0' && id[3] <= '9';
}
std::size_t HashTable::hash(const std::string& key) const {
    // Polynomial rolling hash: sum of (character code * 31^position), modulo capacity.
    std::size_t h = 0;
    for (unsigned char c : key) h = (h * 31 + c) % buckets_.size();
    return h;
}
bool HashTable::insert(const Facility& facility) {
    const std::string key = normalize(facility.id);
    const std::size_t index = hash(key);
    for (const auto& item : buckets_[index]) if (item.id == key) return false;
    if (!buckets_[index].empty()) ++collisions_;
    Facility copy = facility;
    copy.id = key;
    buckets_[index].push_back(copy);
    ++entries_;
    return true;
}
const Facility* HashTable::find(const std::string& id) const {
    const std::string key = normalize(id);
    const auto& bucket = buckets_[hash(key)];
    for (const auto& item : bucket) if (item.id == key) return &item;
    return nullptr;
}
std::size_t HashTable::capacity() const { return buckets_.size(); }
std::size_t HashTable::size() const { return entries_; }
std::size_t HashTable::collisions() const { return collisions_; }
