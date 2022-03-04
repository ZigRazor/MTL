#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MTL.h"

using namespace MTL;
using namespace std;

class MTLMessageQueueTest : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.
    MTLMessageQueueTest()
    {
        // You can do set-up work for each test here.
        
    }
    ~MTLMessageQueueTest() override
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    // void SetUp() override
    //{
    //    // Code here will be called immediately after the constructor (right
    //    // before each test).
    //}
    // void TearDown() override
    //{
    //    // Code here will be called immediately after each test (right
    //    // before the destructor).
    //}
    // Class members declared here can be used by all tests in the test suite
    // for Foo.

    MTLMessageQueue messageQueue;
};

TEST_F(MTLMessageQueueTest, test_pushMessage_get_size)
{
    Message message = shared_ptr<int>(new int(1));

    messageQueue.pushMessage(message);

    EXPECT_EQ(messageQueue.getQueueSize(), 1);
}

TEST_F(MTLMessageQueueTest, test_pushMessage_popMessage_size)
{
    Message message = shared_ptr<int>(new int(1));

    messageQueue.pushMessage(message);

    EXPECT_EQ(messageQueue.getQueueSize(), 1);

    Message message2 = messageQueue.popMessage();

    EXPECT_EQ(messageQueue.getQueueSize(), 0);
}

TEST_F(MTLMessageQueueTest, test_pushMessage_popMessage_size_2)
{
    Message message = shared_ptr<int>(new int(1));
    Message message2 = shared_ptr<int>(new int(2));

    messageQueue.pushMessage(message);
    messageQueue.pushMessage(message2);

    EXPECT_EQ(messageQueue.getQueueSize(), 2);

    Message message3 = messageQueue.popMessage();

    EXPECT_EQ(messageQueue.getQueueSize(), 1);
}

TEST_F(MTLMessageQueueTest, test_pushMessage_popMessage_size_1000)
{
    for (int i = 0; i < 1000; i++)
    {
        Message message = shared_ptr<int>(new int(i));
        messageQueue.pushMessage(message);
        EXPECT_EQ(messageQueue.getQueueSize(), i+1);
    }
    
    for (int i = 0; i < 1000; i++)
    {
        Message message = messageQueue.popMessage();
        EXPECT_EQ(*(static_cast<int*>(message.get())), i);
        EXPECT_EQ(messageQueue.getQueueSize(), 1000-i-1);
    }

}

TEST_F(MTLMessageQueueTest, test_popMessage_empty_queue)
{
    Message message = messageQueue.popMessage();
    EXPECT_EQ(message, nullptr);
}

TEST_F(MTLMessageQueueTest, test_popMessage_empty_queue_2)
{
    for (int i = 0; i < 1000; i++)
    {
        Message message = shared_ptr<int>(new int(i));
        messageQueue.pushMessage(message);
        EXPECT_EQ(messageQueue.getQueueSize(), i+1);
    }
    
    for (int i = 0; i < 1000; i++)
    {
        Message message = messageQueue.popMessage();
        EXPECT_EQ(*(static_cast<int*>(message.get())), i);
        EXPECT_EQ(messageQueue.getQueueSize(), 1000-i-1);
    }
    Message message = messageQueue.popMessage();
    EXPECT_EQ(message, nullptr);
}

TEST_F(MTLMessageQueueTest, test_clear_queue)
{
    for (int i = 0; i < 1000; i++)
    {
        Message message = shared_ptr<int>(new int(i));
        messageQueue.pushMessage(message);
        EXPECT_EQ(messageQueue.getQueueSize(), i+1);
    }
    
    messageQueue.clear();
    EXPECT_EQ(messageQueue.getQueueSize(), 0);
}

TEST_F(MTLMessageQueueTest, test_empty_queue)
{
    EXPECT_EQ(messageQueue.isEmpty(), true);
}

TEST_F(MTLMessageQueueTest, test_empty_queue_2)
{
    for (int i = 0; i < 1000; i++)
    {
        Message message = shared_ptr<int>(new int(i));
        messageQueue.pushMessage(message);
        EXPECT_EQ(messageQueue.isEmpty(), false);
    }
    
    messageQueue.clear();
    EXPECT_EQ(messageQueue.isEmpty(), true);
}


TEST_F(MTLMessageQueueTest, test_empty_queue_3)
{
    for (int i = 0; i < 1000; i++)
    {
        Message message = shared_ptr<int>(new int(i));
        messageQueue.pushMessage(message);
        EXPECT_EQ(messageQueue.getQueueSize(), i+1);
    }
    
    
    for(int i = 0; i < 1000; i++)
    {
        Message message = messageQueue.popMessage();
        EXPECT_EQ(*(static_cast<int*>(message.get())), i);
        EXPECT_EQ(messageQueue.getQueueSize(), 1000-i-1);
    }
    EXPECT_EQ(messageQueue.isEmpty(), true);
}

TEST_F(MTLMessageQueueTest, test_stress_pushMessage_4_threads){
    auto lambda_insert = [this]() {
        for (int i = 0; i < 1000000; i++)
        {
            Message message = shared_ptr<int>(new int(i));
            messageQueue.pushMessage(message);
        }
    };
    std::thread* threads[4];
    for (int i = 0; i < 4; i++)
    {
        threads[i] = new std::thread(lambda_insert);
    }
    for (int i = 0; i < 4; i++)
    {
        threads[i]->join();
    }
    EXPECT_EQ(messageQueue.getQueueSize(), 4000000);
}

TEST_F(MTLMessageQueueTest, test_stress_popMessage_4_threads){
    auto lambda_insert = [this]() {
        for (int i = 0; i < 1000000; i++)
        {
            Message message = shared_ptr<int>(new int(i));
            messageQueue.pushMessage(message);
        }
    };
    std::thread* threads[4];
    for (int i = 0; i < 4; i++)
    {
        threads[i] = new std::thread(lambda_insert);
    }
    for (int i = 0; i < 4; i++)
    {
        threads[i]->join();
    }
    EXPECT_EQ(messageQueue.getQueueSize(), 4000000);

    auto lambda_popMessage = [this]() {
        for (int i = 0; i < 1000000; i++)
        {
            Message message = messageQueue.popMessage();
        }
    };
    std::thread* threads2[4];
    for (int i = 0; i < 4; i++)
    {
        threads2[i] = new std::thread(lambda_popMessage);
    }
    for (int i = 0; i < 4; i++)
    {
        threads2[i]->join();
    }    
    EXPECT_EQ(messageQueue.getQueueSize(), 0);
}