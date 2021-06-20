//
// Created by Tyler on 6/19/21.
//

#ifndef NDN_CHORD_STORAGE_H
#define NDN_CHORD_STORAGE_H

#include <memory>
#include <ndn-cxx/data.hpp>
#include <ndn-cxx/name.hpp>

namespace ndn {
namespace chord {

class Storage {
  public:
    virtual ~Storage() = default;

    virtual std::shared_ptr<const Data> get(const Name &dataName) = 0;

    virtual bool add(const Name &dataName, const Data &data) = 0;

    virtual bool del(const Name &dataName) = 0;
};

} // namespace chord
} // namespace ndn


#endif //NDN_CHORD_STORAGE_H
