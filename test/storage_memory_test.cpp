//
// Created by Tyler on 6/19/21.
//

#include "gtest/gtest.h"
#include "storage_memory.h"
#include <ndn-cxx/security/key-chain.hpp>
#include <ndn-cxx/security/signing-helpers.hpp>

using namespace ndn;
using namespace ndn::chord;

class MemoryStorageTest : public ::testing::Test {
    void SetUp() override {
        m_testData.setName("/right/answer");
        m_testData.setContent(makeEmptyBlock(tlv::Content));
        m_keyChain.sign(m_testData, signingWithSha256());
        m_testData.wireEncode();
    }

  protected:
    KeyChain m_keyChain;
    MemoryStorage m_storage;
    Data m_testData;
};

TEST_F(MemoryStorageTest, AddGet_success) {
    EXPECT_TRUE(m_storage.add("/a/b", m_testData));
    auto out = m_storage.get("/a/b");
    EXPECT_NE(out, nullptr);
    EXPECT_EQ(out->getName(), "/right/answer");
}

TEST_F(MemoryStorageTest, AddAdd_failure) {
    EXPECT_TRUE(m_storage.add("/a/b", m_testData));
    EXPECT_FALSE(m_storage.add("/a/b", Data()));
}

TEST_F(MemoryStorageTest, EmptyGet_failure) {
    auto out = m_storage.get("/a/b");
    EXPECT_EQ(out, nullptr);
}

TEST_F(MemoryStorageTest, AddDelete_success) {
    EXPECT_TRUE(m_storage.add("/a/b", m_testData));
    EXPECT_TRUE(m_storage.del("/a/b"));
}

TEST_F(MemoryStorageTest, EmptyDelete_failure) {
    EXPECT_FALSE(m_storage.del("/a/b"));
}