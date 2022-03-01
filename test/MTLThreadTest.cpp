#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MTL.h"

using namespace MTL;

class MockRunnable : public MTLRunnable
{
public:
    MOCK_METHOD(void, run, (MTLThreadInterface * threadIf), (override));
    MOCK_METHOD(void, suspend, (), (override));
    MOCK_METHOD(void, resume, (), (override));
    MOCK_METHOD(void, stop, (), (override));
    MOCK_METHOD(void, clean_exit, (), (override));
    MOCK_METHOD(void, force_exit, (), (override));
};

class MTLThreadTest : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.
    MTLThreadTest() : runnable()
    {
        // You can do set-up work for each test here.
        thread = new MTLThread(runnable);
    }
    ~MTLThreadTest() override
    {
        // You can do clean-up work that doesn't throw exceptions here.
        delete thread;
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

    MockRunnable runnable;
    MTLThread *thread;
};

TEST_F(MTLThreadTest, test_run)
{
    std::mutex mutex;                 // boost::mutex mutex;
    std::condition_variable cond_var; // boost::condition_variable cond_var;
    bool done(false);

    EXPECT_CALL(runnable, run(thread))
        .Times(1)
        .WillOnce(testing::Invoke([&]()
                                  {
            std::lock_guard<std::mutex> lock(mutex);  // boost::mutex::scoped_lock lock(mutex);
            done = true;
            cond_var.notify_one();
            return; }));

    thread->run(nullptr);

    {
        std::unique_lock<std::mutex> lock(mutex);              // boost::mutex::scoped_lock lock(mutex);
        EXPECT_TRUE(cond_var.wait_for(lock,                    // cond_var.timed_wait
                                      std::chrono::seconds(1), // boost::posix_time::seconds(1),
                                      [&done]
                                      { return done; }));
    }
}

TEST_F(MTLThreadTest, test_suspend)
{
    std::mutex mutex;                 
    std::condition_variable cond_var; 
    bool done(false);

    EXPECT_CALL(runnable, run(thread))
        .Times(1)
        .WillOnce(testing::Invoke([&]()
                                  {
            std::lock_guard<std::mutex> lock(mutex);  
            done = true;
            cond_var.notify_one();
            return; }));

    thread->run(nullptr);

    {
        std::unique_lock<std::mutex> lock(mutex);              
        EXPECT_TRUE(cond_var.wait_for(lock,                   
                                      std::chrono::seconds(1), 
                                      [&done]
                                      { return done; }));
    }

    done = false;

    EXPECT_CALL(runnable, suspend())
        .Times(1)
        .WillOnce(testing::Invoke([&]()
                                  {
            std::lock_guard<std::mutex> lock(mutex); 
            done = true;
            cond_var.notify_one();
            return; }));

    thread->suspend();
    {
        std::unique_lock<std::mutex> lock(mutex);              
        EXPECT_TRUE(cond_var.wait_for(lock,                    
                                      std::chrono::seconds(1),
                                      [&done]
                                      { return done; }));
    }
}

TEST_F(MTLThreadTest, test_resume)
{
    std::mutex mutex;                 
    std::condition_variable cond_var; 
    bool done(false);

    EXPECT_CALL(runnable, run(thread))
        .Times(1)
        .WillOnce(testing::Invoke([&]()
                                  {
            std::lock_guard<std::mutex> lock(mutex);  
            done = true;
            cond_var.notify_one();
            return; }));

    thread->run(nullptr);

    {
        std::unique_lock<std::mutex> lock(mutex);              
        EXPECT_TRUE(cond_var.wait_for(lock,                   
                                      std::chrono::seconds(1), 
                                      [&done]
                                      { return done; }));
    }

    done = false;

    EXPECT_CALL(runnable, resume())
        .Times(1)
        .WillOnce(testing::Invoke([&]()
                                  {
            std::lock_guard<std::mutex> lock(mutex); 
            done = true;
            cond_var.notify_one();
            return; }));

    thread->resume();
    {
        std::unique_lock<std::mutex> lock(mutex);              
        EXPECT_TRUE(cond_var.wait_for(lock,                    
                                      std::chrono::seconds(1),
                                      [&done]
                                      { return done; }));
    }
}

TEST_F(MTLThreadTest, test_stop)
{
    std::mutex mutex;                 
    std::condition_variable cond_var; 
    bool done(false);

    EXPECT_CALL(runnable, run(thread))
        .Times(1)
        .WillOnce(testing::Invoke([&]()
                                  {
            std::lock_guard<std::mutex> lock(mutex);  
            done = true;
            cond_var.notify_one();
            return; }));

    thread->run(nullptr);

    {
        std::unique_lock<std::mutex> lock(mutex);              
        EXPECT_TRUE(cond_var.wait_for(lock,                   
                                      std::chrono::seconds(1), 
                                      [&done]
                                      { return done; }));
    }

    done = false;

    EXPECT_CALL(runnable, stop())
        .Times(1)
        .WillOnce(testing::Invoke([&]()
                                  {
            std::lock_guard<std::mutex> lock(mutex); 
            done = true;
            cond_var.notify_one();
            return; }));

    thread->stop();
    {
        std::unique_lock<std::mutex> lock(mutex);              
        EXPECT_TRUE(cond_var.wait_for(lock,                    
                                      std::chrono::seconds(1),
                                      [&done]
                                      { return done; }));
    }
}

TEST_F(MTLThreadTest, test_clean_exit)
{
    std::mutex mutex;                 
    std::condition_variable cond_var; 
    bool done(false);

    EXPECT_CALL(runnable, run(thread))
        .Times(1)
        .WillOnce(testing::Invoke([&]()
                                  {
            std::lock_guard<std::mutex> lock(mutex);  
            done = true;
            cond_var.notify_one();
            return; }));

    thread->run(nullptr);

    {
        std::unique_lock<std::mutex> lock(mutex);              
        EXPECT_TRUE(cond_var.wait_for(lock,                   
                                      std::chrono::seconds(1), 
                                      [&done]
                                      { return done; }));
    }

    done = false;

    EXPECT_CALL(runnable, clean_exit())
        .Times(1)
        .WillOnce(testing::Invoke([&]()
                                  {
            std::lock_guard<std::mutex> lock(mutex); 
            done = true;
            cond_var.notify_one();
            return; }));

    thread->clean_exit();
    {
        std::unique_lock<std::mutex> lock(mutex);              
        EXPECT_TRUE(cond_var.wait_for(lock,                    
                                      std::chrono::seconds(1),
                                      [&done]
                                      { return done; }));
    }
}

TEST_F(MTLThreadTest, test_force_exit)
{
    std::mutex mutex;                 
    std::condition_variable cond_var; 
    bool done(false);

    EXPECT_CALL(runnable, run(thread))
        .Times(1)
        .WillOnce(testing::Invoke([&]()
                                  {
            std::lock_guard<std::mutex> lock(mutex);  
            done = true;
            cond_var.notify_one();
            return; }));

    thread->run(nullptr);

    {
        std::unique_lock<std::mutex> lock(mutex);              
        EXPECT_TRUE(cond_var.wait_for(lock,                   
                                      std::chrono::seconds(1), 
                                      [&done]
                                      { return done; }));
    }

    done = false;

    EXPECT_CALL(runnable, force_exit())
        .Times(1)
        .WillOnce(testing::Invoke([&]()
                                  {
            std::lock_guard<std::mutex> lock(mutex); 
            done = true;
            cond_var.notify_one();
            return; }));

    thread->force_exit();
    {
        std::unique_lock<std::mutex> lock(mutex);              
        EXPECT_TRUE(cond_var.wait_for(lock,                    
                                      std::chrono::seconds(1),
                                      [&done]
                                      { return done; }));
    }
}

TEST_F(MTLThreadTest, test_no_suspend)
{
    std::mutex mutex;                 
    std::condition_variable cond_var; 
    bool done(false);

    EXPECT_CALL(runnable, run(thread))
        .Times(1)
        .WillOnce(testing::Invoke([&]()
                                  {
            std::lock_guard<std::mutex> lock(mutex);  
            done = true;
            cond_var.notify_one();
            return; }));

    thread->run(nullptr);

    {
        std::unique_lock<std::mutex> lock(mutex);              
        EXPECT_TRUE(cond_var.wait_for(lock,                   
                                      std::chrono::seconds(1), 
                                      [&done]
                                      { return done; }));
    }

    done = false;

    EXPECT_CALL(runnable, force_exit())
        .Times(1)
        .WillOnce(testing::Invoke([&]()
                                  {
            std::lock_guard<std::mutex> lock(mutex); 
            done = true;
            cond_var.notify_one();
            return; }));

    thread->force_exit();
    {
        std::unique_lock<std::mutex> lock(mutex);              
        EXPECT_TRUE(cond_var.wait_for(lock,                    
                                      std::chrono::seconds(1),
                                      [&done]
                                      { return done; }));
    }

    done = false;

    EXPECT_CALL(runnable, suspend())
        .Times(0);
       
    thread->suspend();

}

TEST_F(MTLThreadTest, test_no_resume)
{
    std::mutex mutex;                 
    std::condition_variable cond_var; 
    bool done(false);

    EXPECT_CALL(runnable, run(thread))
        .Times(1)
        .WillOnce(testing::Invoke([&]()
                                  {
            std::lock_guard<std::mutex> lock(mutex);  
            done = true;
            cond_var.notify_one();
            return; }));

    thread->run(nullptr);

    {
        std::unique_lock<std::mutex> lock(mutex);              
        EXPECT_TRUE(cond_var.wait_for(lock,                   
                                      std::chrono::seconds(1), 
                                      [&done]
                                      { return done; }));
    }

    done = false;

    EXPECT_CALL(runnable, force_exit())
        .Times(1)
        .WillOnce(testing::Invoke([&]()
                                  {
            std::lock_guard<std::mutex> lock(mutex); 
            done = true;
            cond_var.notify_one();
            return; }));

    thread->force_exit();
    {
        std::unique_lock<std::mutex> lock(mutex);              
        EXPECT_TRUE(cond_var.wait_for(lock,                    
                                      std::chrono::seconds(1),
                                      [&done]
                                      { return done; }));
    }

    done = false;

    EXPECT_CALL(runnable, resume())
        .Times(0);
       
    thread->resume();

}

TEST_F(MTLThreadTest, test_no_stop)
{
    std::mutex mutex;                 
    std::condition_variable cond_var; 
    bool done(false);

    EXPECT_CALL(runnable, run(thread))
        .Times(1)
        .WillOnce(testing::Invoke([&]()
                                  {
            std::lock_guard<std::mutex> lock(mutex);  
            done = true;
            cond_var.notify_one();
            return; }));

    thread->run(nullptr);

    {
        std::unique_lock<std::mutex> lock(mutex);              
        EXPECT_TRUE(cond_var.wait_for(lock,                   
                                      std::chrono::seconds(1), 
                                      [&done]
                                      { return done; }));
    }

    done = false;

    EXPECT_CALL(runnable, force_exit())
        .Times(1)
        .WillOnce(testing::Invoke([&]()
                                  {
            std::lock_guard<std::mutex> lock(mutex); 
            done = true;
            cond_var.notify_one();
            return; }));

    thread->force_exit();
    {
        std::unique_lock<std::mutex> lock(mutex);              
        EXPECT_TRUE(cond_var.wait_for(lock,                    
                                      std::chrono::seconds(1),
                                      [&done]
                                      { return done; }));
    }

    done = false;

    EXPECT_CALL(runnable, stop())
        .Times(0);
       
    thread->stop();

}

TEST_F(MTLThreadTest, test_no_rerun)
{
    std::mutex mutex;                 
    std::condition_variable cond_var; 
    bool done(false);

    EXPECT_CALL(runnable, run(thread))
        .Times(1)
        .WillOnce(testing::Invoke([&]()
                                  {
            std::lock_guard<std::mutex> lock(mutex);  
            done = true;
            cond_var.notify_one();
            return; }));

    thread->run(nullptr);

    {
        std::unique_lock<std::mutex> lock(mutex);              
        EXPECT_TRUE(cond_var.wait_for(lock,                   
                                      std::chrono::seconds(1), 
                                      [&done]
                                      { return done; }));
    }

    done = false;

    EXPECT_CALL(runnable, clean_exit())
        .Times(1)
        .WillOnce(testing::Invoke([&]()
                                  {
            std::lock_guard<std::mutex> lock(mutex); 
            done = true;
            cond_var.notify_one();
            return; }));

    thread->clean_exit();
    {
        std::unique_lock<std::mutex> lock(mutex);              
        EXPECT_TRUE(cond_var.wait_for(lock,                    
                                      std::chrono::seconds(1),
                                      [&done]
                                      { return done; }));
    }

    done = false;

    EXPECT_CALL(runnable, run(thread))
        .Times(0);
       
    thread->run(nullptr);
}