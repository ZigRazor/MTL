#include "gtest/gtest.h"
#include "MTL.h"

using namespace MTL;

class DummyRunnable : public MTLRunnable
{
public:
    DummyRunnable()
    {
        threadIf = nullptr;
    }

    virtual void run(MTLThreadInterface *threadIf) override
    {
        this->threadIf = threadIf;
        run_called = true;
        resume_called = false;
        suspend_called = false;
        stop_called = false;
        clean_exit_called = false;
        force_exit_called = false;
    }

    virtual void suspend() override
    {
        run_called = false;
        resume_called = false;
        suspend_called = true;
        stop_called = false;
        clean_exit_called = false;
        force_exit_called = false;
    }

    virtual void resume() override
    {
        run_called = false;
        resume_called = true;
        suspend_called = false;
        stop_called = false;
        clean_exit_called = false;
        force_exit_called = false;
    }

    virtual void stop() override
    {
        run_called = false;
        resume_called = false;
        suspend_called = false;
        stop_called = true;
        clean_exit_called = false;
        force_exit_called = false;
    }

    virtual void clean_exit() override
    {
        run_called = false;
        resume_called = false;
        suspend_called = false;
        stop_called = false;
        clean_exit_called = true;
        force_exit_called = false;
    }

    virtual void force_exit() override
    {
        run_called = false;
        resume_called = false;
        suspend_called = false;
        stop_called = false;
        clean_exit_called = false;
        force_exit_called = true;
    }

    bool run_called = false;
    bool resume_called = false;
    bool suspend_called = false;
    bool stop_called = false;
    bool clean_exit_called = false;
    bool force_exit_called = false;

};

// The fixture for testing class Foo.
class MTLRunnableTest : public ::testing::Test
{
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.
    //MTLRunnableTest()
    //{
    //    // You can do set-up work for each test here.
    //}
    //~MTLRunnableTest() override
    //{
    //    // You can do clean-up work that doesn't throw exceptions here.
    //}
    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    //void SetUp() override
    //{
    //    // Code here will be called immediately after the constructor (right
    //    // before each test).
    //}
    //void TearDown() override
    //{
    //    // Code here will be called immediately after each test (right
    //    // before the destructor).
    //}
    // Class members declared here can be used by all tests in the test suite
    // for Foo.

    DummyRunnable runnable;
};

TEST_F(MTLRunnableTest, test_1)
{
    runnable.run(nullptr);
    ASSERT_TRUE(runnable.run_called);
    ASSERT_FALSE(runnable.resume_called);
    ASSERT_FALSE(runnable.suspend_called);
    ASSERT_FALSE(runnable.stop_called);
    ASSERT_FALSE(runnable.clean_exit_called);
    ASSERT_FALSE(runnable.force_exit_called);

    runnable.resume();
    ASSERT_FALSE(runnable.run_called);
    ASSERT_TRUE(runnable.resume_called);
    ASSERT_FALSE(runnable.suspend_called);
    ASSERT_FALSE(runnable.stop_called);
    ASSERT_FALSE(runnable.clean_exit_called);
    ASSERT_FALSE(runnable.force_exit_called);

    runnable.suspend();
    ASSERT_FALSE(runnable.run_called);
    ASSERT_FALSE(runnable.resume_called);
    ASSERT_TRUE(runnable.suspend_called);
    ASSERT_FALSE(runnable.stop_called);
    ASSERT_FALSE(runnable.clean_exit_called);
    ASSERT_FALSE(runnable.force_exit_called);

    runnable.stop();
    ASSERT_FALSE(runnable.run_called);
    ASSERT_FALSE(runnable.resume_called);
    ASSERT_FALSE(runnable.suspend_called);
    ASSERT_TRUE(runnable.stop_called);
    ASSERT_FALSE(runnable.clean_exit_called);
    ASSERT_FALSE(runnable.force_exit_called);

    runnable.clean_exit();
    ASSERT_FALSE(runnable.run_called);
    ASSERT_FALSE(runnable.resume_called);
    ASSERT_FALSE(runnable.suspend_called);
    ASSERT_FALSE(runnable.stop_called);
    ASSERT_TRUE(runnable.clean_exit_called);
    ASSERT_FALSE(runnable.force_exit_called);

    runnable.force_exit();
    ASSERT_FALSE(runnable.run_called);
    ASSERT_FALSE(runnable.resume_called);
    ASSERT_FALSE(runnable.suspend_called);
    ASSERT_FALSE(runnable.stop_called);
    ASSERT_FALSE(runnable.clean_exit_called);
    ASSERT_TRUE(runnable.force_exit_called);


}