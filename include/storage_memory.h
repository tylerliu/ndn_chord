//
// Created by Tyler on 6/19/21.
//

#ifndef NDN_CHORD_STORAGE_MEMORY_H
#define NDN_CHORD_STORAGE_MEMORY_H

#include "storage.h"

namespace ndn {
namespace chord {

class MemoryStorage : public Storage {
  public:
    std::shared_ptr<const Data> get(const Name &dataName);

    bool add(const Name &dataName, const Data &data);

    bool del(const Name &dataName);

  private:
    std::map<Name, std::shared_ptr<Data>> m_map;
};

} // namespace chord
} // namespace ndn

#endif //NDN_CHORD_STORAGE_MEMORY_H
