//
// Created by Tyler on 6/19/21.
//

#include "../include/storage_memory.h"

namespace ndn {

std::shared_ptr<const Data> chord::MemoryStorage::get(const Name &dataName) {
    if (m_map.count(dataName) == 0) return nullptr;
    return m_map.at(dataName);
}

bool chord::MemoryStorage::add(const Name &dataName, const Data &data) {
    if (m_map.count(dataName) == 1) return false;
    m_map.emplace(dataName, std::make_shared<Data>(data));
    return true;
}

bool chord::MemoryStorage::del(const Name &dataName) {
    if (m_map.count(dataName) == 0) return false;
    m_map.erase(dataName);
    return true;
}

}