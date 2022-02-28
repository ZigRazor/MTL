<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
# MTL (Multi Threading Library)
<p align="center">
    <img src="logo/logo.gif" alt="MTL_Logo" width="500" height="500" style="display: block; margin: 0 auto" />
</p>

[![Contributors][contributors-shield]][contributors-url] [![Forks][forks-shield]][forks-url] [![Stargazers][stars-shield]][stars-url] [![Issues][issues-shield]][issues-url] [![GPL-3.0 License][license-shield]][license-url]

Multi Threading Library is a set of utilities, easy and ready to use for common task in multi threading environment and development.

## Roadmap

- [x] Thread Class
- [x] Thread Manager
- [X] Thread Pool
- [x] Task Class
- [X] Ordered Task
- [x] Task Flow
- [x] Complete Documentation
- [x] Doxygen Integration
- [x] First Beta Release
- [ ] Test Framework
- [ ] CI/CD Pipeline
- [ ] First Stable Release
- [ ] Thread Monitoring
- [ ] ...

See the [open issues](https://github.com/othneildrew/Best-README-Template/issues) for a full list of proposed features (and known issues).

## Getting Started

This is an example of how you may give instructions on setting up your project locally.
To get a local copy up and running follow these simple example steps.

### Prerequisites

The following are required to get the project up and running.

#### Google Test

[GoogleTest](https://github.com/google/googletest)

```bash
git clone https://github.com/google/googletest.git  # Dowload the Google Test repository
cd googletest                                       # Main directory of the cloned repository.
mkdir -p build                                      # Create a directory to hold the build output.
cd build                                            # Move into the build directory.   
cmake ..                                            # Generate native build scripts for GoogleTest.
make                                                # Compile
sudo make install                                   # Install in /usr/local/ by default
```

### Installation

```bash
git clone https://github.com/ZigRazor/MTL.git       # Dowload the MTL repository
cd MTL                                              # Main directory of the cloned repository.
mkdir -p build                                      # Create a directory to hold the build output.
cd build                                            # Move into the build directory.   
cmake ..                                            # Generate native build scripts for MTL.
make                                                # Compile
sudo make install                                   # Install in /usr/local/ by default
```

## Usage

The only things you have to do to get library in you project are to:
    - Include the header file `MTL.h` in your project.
    - Link the library `MTL.so` to your project.

### Thread Class

To let the thread class know what to do, you must create a Runnable object.

**MyRunnable.hpp**

```cpp
#include <iostream>
#include "MTL.h"

class MyRunnable : public MTL::MTLRunnable
{
public:
    MyRunnable() = default;
    virtual ~MyRunnable() = default;
    void run(MTL::MTLThreadInterface* threadIf)
    {
        std::cout << "Hello World!" << std::endl;
        int counter = 0;
        while (true)
        {
            if(threadIf->getThreadState() == MTL::E_MTLThreadState::STOPPED){
                std::cout << "Stopped" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }else if (threadIf->getThreadState() == MTL::E_MTLThreadState::SUSPENDED)
            {
                std::cout << "Suspended" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }else if (threadIf->getThreadState() == MTL::E_MTLThreadState::EXITED)
            {
                std::cout << "Exited" << std::endl;
                break;
            } else if (threadIf->getThreadState() == MTL::E_MTLThreadState::RUNNING)
            {
                //Simulate 20 seconds of running work
                if(counter == 20)
                {
                    threadIf->setThreadState(MTL::E_MTLThreadState::EXITED);
                }
                std::cout << "Running" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                counter++;
            }
        }
        
    }

    void stop()
    {
        std::cout << "Stop!" << std::endl;
    }

    void suspend()
    {
        std::cout << "Pause!" << std::endl;
    }

    void resume()
    {
        std::cout << "Resume!" << std::endl;
    }

    void clean_exit()
    {
        std::cout << "Clean Exit!" << std::endl;
    }

    void force_exit()
    {
        std::cout << "Force Exit!" << std::endl;
        ::exit(0); // clean Exit
    }
};
```

Then in the main function you can create a thread object and pass it the runnable object.

**main.cpp**

```cpp
#include "MyRunnable.hpp"

int main()
{
    MyRunnable myRunnable; // Create a runnable object
    MTL::MTLThread thread(myRunnable); // Create a thread object and pass it the runnable object.
    thread.run(); //Start the Thread
    std::this_thread::sleep_for(std::chrono::milliseconds(10000)); //Sleep for 10 seconds
    thread.suspend(); //Suspend the thread
    std::this_thread::sleep_for(std::chrono::milliseconds(5000)); //Sleep for 5 seconds
    thread.resume(); //Resume the thread
    int counter = 0;
    while(thread.isRunning()){ //Wait 10 seconds in the main thread
        if(counter == 10)
        {
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Counter: " << counter << std::endl;
        counter++;
    }
    return 0;
}
```

### Worker Threads Class

The Worker Thread class is a runnable with 2 more features:
    - It contains a message queue
    - Has to implement the function to process the messages

This class can be used to create a runnable to pass to a Thread object that receive an input message and elaborate it.

A simple example of implementation of the Worker Thread Class can be the following:

**MyWorkerThread.hpp**

```cpp
class MyWorker : public MTL::MTLWorkerThread
{
public:
    MyWorker() = default;
    virtual ~MyWorker() = default;
    virtual void processMessage(MTL::Message message) override
    {
        //When the message is dequeued it is passed to this function
        int* message_casted = static_cast< int *> (message.get()); //Cast the message to the correct type
        std::cout << "MyWorker::processMessage(" << *message_casted << ")" << std::endl; //Do somenthings with the message
    }
};
```

### Thread Manager Class

The Thread Manager class is a Runnable that can be used to manage threads.
If you want to manage a group of threads all togheter you can create a Thread Manager object and pass it to a Thread object.
The threads can be passed to the Thread Manager object and the Thread Manager object will manage the threads.
So if you have multiple tasks or multiple workers, you can collect them in a thread manager and all the action performed to the thread manager(start, stop, suspend, resume, etc) will be performed to all the threads.
A Simple example of usage can be the following:

```cpp
#include "MTL.h"
#include "MyWorker.hpp"

int main(){
    // Three different kind of workers
    MyWorker1 myWorker1;
    MyWorker2 myWorker2;
    MyWorker3 myWorker3;

    MTL::MTLThreadManager threadManager; //Create a thread manager object

    threadManager.addThread(std::make_unique<MTL::MTLThread>(myWorker1)); //Add a thread to the thread manager
    threadManager.addThread(std::make_unique<MTL::MTLThread>(myWorker2)); //Add a thread to the thread manager

    MTL::MTLThread thread(threadManager); //Create a thread object and pass it the thread manager
    thread.run(); //Start the thread manager that will start all the threads
    std::this_thread::sleep_for(std::chrono::milliseconds(5000)); //Let him work for 5 seconds
    thread.suspend(); //Suspend the thread manager that will suspend all the threads
    std::this_thread::sleep_for(std::chrono::milliseconds(5000)); //Let suspended for 5 seconds
    thread.resume(); //Resume the thread manager that will resume all the threads
    threadManager.addThread(std::make_unique<MTL::MTLThread>(myWorker3)); //Add a thread to the thread manager
    thread.clean_exit(); // Clean Exit the thread manager that will clean exit all the threads   
    while (thread.isRunning()) //Wait for the thread manager to exit
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Counter: " << counter << std::endl;
        counter++;
    }
    std::cout << "Thread Manager Terminated" << std::endl;
    return 0;
}
```

### Thread Pool Class

The Thread Pool class is a Thread Manager that can be used to create a fixed number of workers that execute the same task. When a message is enqueued to the thread pool, the message is passed to a workers.
This kind of thread manager is useful when you have to implement a multi threaded consumer.
An example of usage can be the following:

```cpp
#include "MTL.h"

int main(){
    MyWorker1 myWorker1; //Create a worker

    MTL::MTLThreadPool threadPool(myWorker1, 4); //Create a thread pool with 4 workers

    MTL::MTLThread thread(threadPool); //Create a thread object and pass it the thread pool
    thread.run(); //Start the thread pool that will start all the workers
    for (int i = 0; i < 10; ++i) // Enqueue 10 messages
    {
        std::cout << "Inject Message " << i << std::endl;
        MTL::Message message(new int(i));
        threadPool.onMessage(message);        
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10000)); //Let him work for 10 seconds
    std::cout << "Suspend" << std::endl; 
    thread.suspend(); // Suspend the thread pool that will suspend all the workers
    for (int i = 10; i < 20; ++i) // Enqueue 10 messages
    {
        std::cout << "Inject Message " << i << std::endl;
        MTL::Message message(new int(i));
        threadPool.onMessage(message);       
        
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(5000)); //Let Suspeded for 5 seconds
    std::cout << "Resume" << std::endl; 
    thread.resume(); // Resume the thread pool that will resume all the workers
    
    std::cout << "Exit" << std::endl;
    thread.clean_exit();  // Clean Exit the thread pool that will clean exit all the workers  
    while (thread.isRunning()) //Wait for the thread pool to exit
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Counter: " << counter << std::endl;
        counter++;
    }
    std::cout << "Thread Pool Terminated" << std::endl;

    return 0;
}
```

### Shared Object and Shared Memory Classes

The Shared Object class is a class that manage a shared memory object and can be used in a thread safe manner.

The Shared Memory class is a class that manage shared objects and can be used in a thread safe manner.

The two classes can be used to create a thread safe memory to share data between threads.

The following is a simple example of application:

**MySharedObject.hpp**

```cpp
#include "MTL.h"

class MySharedObject : public MTL::MTLSharedObject {
public:
    MySharedObject(unsigned int id) : MTLSharedObject(id) {
        std::cout << "MySharedObject::MySharedObject()" << std::endl;
        value = 0;
    }
    ~MySharedObject() {
        std::cout << "MySharedObject::~MySharedObject()" << std::endl;
    }

    int getValue() {
        return value;
    }
    void setValue(int v) {
        value = v;
    }
private:
    int value; //The value of the shared object
};
```

**MyRunnable.hpp**

```cpp
#include "MTL.h"

class MyRunnable : public MTL::MTLRunnable
{
public:
    MyRunnable(MTL::MTLSharedMemory* sharedMemory) : m_sharedMemory(sharedMemory)
    {};
    virtual ~MyRunnable() = default;
    void run(MTL::MTLThreadInterface* threadIf)
    {
        std::cout << "Hello World!" << std::endl;
        int counter = 0;
        while (true)
        {
            if(threadIf->getThreadState() == MTL::E_MTLThreadState::STOPPED){
                std::cout << "Stopped Thread Id: " << std::this_thread::get_id() << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }else if (threadIf->getThreadState() == MTL::E_MTLThreadState::SUSPENDED)
            {
                std::cout << "Suspended Thread Id: "<< std::this_thread::get_id() << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }else if (threadIf->getThreadState() == MTL::E_MTLThreadState::EXITED)
            {
                std::cout << "Exited Thread Id: " << std::this_thread::get_id() << std::endl;
                break;
            } else if (threadIf->getThreadState() == MTL::E_MTLThreadState::RUNNING)
            {
                // when running this runnable increment the shared memory value by 1
                MySharedObject& myObj = dynamic_cast<MySharedObject&>(m_sharedMemory->getSharedObjectById(1));
                std::cout << "Thread Id: " << std::this_thread::get_id()  << " starting Value: " << myObj.getValue() << " end Value: " << myObj.getValue() + 1 << std::endl;
                myObj.setValue(myObj.getValue() + 1);
                m_sharedMemory->releaseSharedObject(myObj);
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                counter++;
            }
        }
        
    }
    
    void stop()
    {
        std::cout << "Stopping" << std::endl;
    }

    void suspend()
    {
        std::cout << "Suspending" << std::endl;
    }

    void resume()
    {
        std::cout << "Resuming" << std::endl;
    }

    void clean_exit()
    {
        std::cout << "Exiting" << std::endl;
    }

    void force_exit()
    {
        std::cout << "Force Exiting" << std::endl;
    }

private:
    MTL::MTLSharedMemory* m_sharedMemory;
};
```

**main.cpp**

```cpp
#include "MTL.h"
#include "MySharedObject.hpp"
#include "MyRunnable.hpp"

int main()
{
    /**
     *  This example demostrate how the shared memory and shared object classes 
     *  can be used to share data between threads. Without alter the atomicity 
     *  of the execution over the memory objects
     
     
     **/
    
    std::unique_ptr<MySharedObject> myObj(new MySharedObject(1)); //Create a shared object
    MTL::MTLSharedMemory sharedMemory; //Create a shared memory
    sharedMemory.addSharedObject(std::move(myObj)); //Add the shared object to the shared memory
    MyRunnable myRunnable1(&sharedMemory); //Create a runnable
    MyRunnable myRunnable2(&sharedMemory); //Create another runnable

    MTL::MTLThread thread1(myRunnable1); //Create a thread from the runnable
    MTL::MTLThread thread2(myRunnable2); //Create another thread from the runnable
    thread1.run(); //Run the thread
    thread2.run(); //Run the thread
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //Let the threads run for 1 second
    std::cout << "Suspend Thread 1" << std::endl;
    thread1.suspend(); //Suspend the thread 1
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //Let the thread 2 runs for 1 second
    std::cout << "Resume Thread 1" << std::endl;  
    thread1.resume(); //Resume the thread 1
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //Let the threads run for 1 second
    std::cout << "Exit the Threads" << std::endl;
    thread1.clean_exit();    //Exit the thread 1
    thread2.clean_exit();    //Exit the thread 2

    thread1.join(); //Wait for the thread 1 to finish
    thread2.join(); //Wait for the thread 2 to finish
    
    std::cout << "Threads Joined" << std::endl;

    return 0;
}
```

### Task Class

The task class is a wrapper of C++ task class.
It needs a runnable task to be executed.
A simple example can be the following one:

**MyRunnableTask.hpp**

```cpp
#include <iostream>
#include "MTL.h"

class MyRunnableTask : public MTL::MTLRunnableTask
{
public:
    MyRunnableTask() = default;
    virtual ~MyRunnableTask() = default;
    std::shared_ptr<void> run(MTL::MTLTaskInterface *interface = nullptr)
    {
        std::cout << "Hello World!" << std::endl;
        std::cout << "Simulating Working for 3 seconds" << std::endl;

        for (int i = 0; i < 3; i++)
        {
            std::cout << "." << std::flush;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cout << std::endl;
        std::cout << "This is a Task that return 1" << std::endl;

        int i = 1;
        std::shared_ptr<void> result(new int(i));
        return result;
    }
};
```

**main.cpp**

```cpp
#include "MyRunnableTask.hpp"

int main()
{
    MyRunnableTask myRunnableTask; //Create a runnable task
    MTL::MTLTask task(myRunnableTask); //Create a task from the runnable task
    task.run(); //Run the task
    std::shared_ptr<void> result = task.getResult(); //Get the result of the task
    std::cout << "Result: " << *(static_cast<int *>(result.get())) << std::endl; //Print the result
    return 0;
}
```

### Ordered Task and Task Flow Classes

The Ordered Task class is derived from Task class and has a list of predecessors and a list of successors.

The Task Flow class is a class that allow to execute ordered task in a consistent manner and return the final result.

A simple example can be the following one:

**DerivedTasks.hpp**

```cpp
#include <iostream>
#include "MTL.h"

//Return 2
class Var2Task : public MTL::MTLRunnableTask
{
public:
    Var2Task() = default;
    virtual ~Var2Task() = default;
    std::shared_ptr<void> run(MTL::MTLTaskInterface *interface = nullptr)
    {
        MTL::MTLOrderedTaskInterface *orderedTaskIf = dynamic_cast<MTL::MTLOrderedTaskInterface *>(interface);
        std::cout << orderedTaskIf->getTaskName() << ": "
                  << "Start Task " << std::endl
                  << std::flush;
        std::cout << orderedTaskIf->getTaskName() << ": "
                  << "Simulating Working for 3 seconds" << std::endl
                  << std::flush;

        for (int i = 0; i < 3; i++)
        {
            std::cout << "." << std::flush;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        std::cout << std::endl;

        auto previousResult = orderedTaskIf->getPredecessorsResults();

        std::shared_ptr<void> result(new int(2));
        std::cout << orderedTaskIf->getTaskName() << ": "
                  << "Result = " << *((int *)(result.get())) << std::endl
                  << std::flush;
        return result;
    }
};

// Sum predecessors
class SumTask : public MTL::MTLRunnableTask
{
public:
    SumTask() = default;
    virtual ~SumTask() = default;
    std::shared_ptr<void> run(MTL::MTLTaskInterface *interface = nullptr)
    {
        MTL::MTLOrderedTaskInterface *orderedTaskIf = dynamic_cast<MTL::MTLOrderedTaskInterface *>(interface);
        std::cout << orderedTaskIf->getTaskName() << ": "
                  << "Start Task " << std::endl
                  << std::flush;
        std::cout << orderedTaskIf->getTaskName() << ": "
                  << "Simulating Working for 3 seconds" << std::endl
                  << std::flush;

        for (int i = 0; i < 3; i++)
        {
            std::cout << "." << std::flush;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        std::cout << std::endl;

        auto predecessorsResults = orderedTaskIf->getPredecessorsResults();
        std::shared_ptr<void> result(new int(0));
        if (predecessorsResults.empty())
        {
            std::shared_ptr<void> result(new int(0));
            return result;
        }
        else
        {
            auto it = predecessorsResults.begin();
            std::shared_ptr<void> result((int *)it->second.get());
            ++it;
            for (it; it != predecessorsResults.end(); ++it)
            {
                int *previousResult = (int *)(it->second.get());
                int *currentResult = (int *)(result.get());
                *currentResult = (*currentResult) + (*previousResult);
            }
            std::cout << orderedTaskIf->getTaskName() << ": "
                      << "Result = " << *((int *)(result.get())) << std::endl
                      << std::flush;
            return result;
        }
    }
};

// Multiply predecessors
class MulTask : public MTL::MTLRunnableTask
{
public:
    MulTask() = default;
    virtual ~MulTask() = default;
    std::shared_ptr<void> run(MTL::MTLTaskInterface *interface = nullptr)
    {
        MTL::MTLOrderedTaskInterface *orderedTaskIf = dynamic_cast<MTL::MTLOrderedTaskInterface *>(interface);
        std::cout << orderedTaskIf->getTaskName() << ": "
                  << "Start Task " << std::endl
                  << std::flush;
        std::cout << orderedTaskIf->getTaskName() << ": "
                  << "Simulating Working for 3 seconds" << std::endl
                  << std::flush;

        for (int i = 0; i < 3; i++)
        {
            std::cout << "." << std::flush;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        std::cout << std::endl
                  << std::flush;

        auto predecessorsResults = orderedTaskIf->getPredecessorsResults();
        std::shared_ptr<void> result(new int(0));
        if (predecessorsResults.empty())
        {
            std::shared_ptr<void> result(new int(0));
            return result;
        }
        else
        {
            auto it = predecessorsResults.begin();
            std::shared_ptr<void> result((int *)it->second.get());
            ++it;
            for (it; it != predecessorsResults.end(); ++it)
            {
                int *previousResult = (int *)(it->second.get());
                int *currentResult = (int *)(result.get());
                *currentResult = (*currentResult) * (*previousResult);
            }
            std::cout << orderedTaskIf->getTaskName() << ": "
                      << "Result = " << *((int *)(result.get())) << std::endl
                      << std::flush;
            return result;
        }
    }
};

```

**main.cpp**

```cpp
#include "DerivedTasks.hpp"

// This Example simulate the execution of the following expression ((a+b)+c)*(d+e) where a,b,c,d,e are value 2
int main()
{
    std::cout << "Running Example 7 for MTL Version " << MTL_VERSION_MAJOR << "." << MTL_VERSION_MINOR << "." << MTL_VERSION_PATCH << std::endl;
    Var2Task var2Task; // Task that return 2
    SumTask sum2Task; // Task that return the sum of the predecessors 
    MulTask mul2Task; // Task that return the multiplication of the predecessors

    auto taskA = std::make_shared<MTL::MTLOrderedTask>("a", var2Task); // Task that return 2
    auto taskB = std::make_shared<MTL::MTLOrderedTask>("b", var2Task); // Task that return 2
    auto taskC = std::make_shared<MTL::MTLOrderedTask>("c", var2Task); // Task that return 2
    auto taskD = std::make_shared<MTL::MTLOrderedTask>("d", var2Task); // Task that return 2
    auto taskE = std::make_shared<MTL::MTLOrderedTask>("e", var2Task); // Task that return 2

    auto taskF = std::make_shared<MTL::MTLOrderedTask>("f", sum2Task); // Task that return the sum of the predecessors
    auto taskG = std::make_shared<MTL::MTLOrderedTask>("g", sum2Task); // Task that return the sum of the predecessors
    auto taskH = std::make_shared<MTL::MTLOrderedTask>("h", sum2Task); // Task that return the sum of the predecessors

    auto taskI = std::make_shared<MTL::MTLOrderedTask>("i", mul2Task); // Task that return the multiplication of the predecessors

    MTL::MTLTaskFlow taskFlow; // Task Flow
    taskFlow.precede(taskA, taskF); // Task A precede Task F
    taskFlow.precede(taskB, taskF); // Task B precede Task F
    taskFlow.precede(taskC, taskG); // Task C precede Task G
    taskFlow.precede(taskF, taskG); // Task F precede Task G
    taskFlow.precede(taskD, taskH); // Task D precede Task H
    taskFlow.precede(taskE, taskH); // Task E precede Task H
    taskFlow.precede(taskG, taskI); // Task G precede Task I
    taskFlow.precede(taskH, taskI); // Task H precede Task I

    taskFlow.run(); // Run the task flow
    std::shared_ptr<void> result = taskFlow.getResult(); // Get the result of the task flow
    std::cout << "Result: " << *(static_cast<int *>(result.get())) << std::endl; // Print the result
    return 0;
}

```

_For more examples, please refer to the [Example Directory](https://github.com/ZigRazor/MTL/tree/main/example)_

## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!
Before these steps please read the [Contributing Guidelines](https://github.com/ZigRazor/MTL/blob/master/CONTRIBUTING.md) and the [Code of Conduct](https://github.com/ZigRazor/MTL/blob/master/CODE_OF_CONDUCT.md)

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

Distributed under the GPL-3.0 License. See [`LICENSE`](https://github.com/ZigRazor/MTL/blob/master/LICENSE) for more information.

## Detailed Documentation

You can find more detailed documentation at [MTL Documentation](https://raw.githack.com/ZigRazor/MTL/main/docs/html/index.html)

## Contact

ZigRazor - zigrazor@gmail.com

Project Link: [https://github.com/ZigRazor/MTL](https://github.com/ZigRazor/MTL)

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/ZigRazor/MTL.svg?style=for-the-badge
[contributors-url]: https://github.com/ZigRazor/MTL/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/ZigRazor/MTL.svg?style=for-the-badge
[forks-url]: https://github.com/ZigRazor/MTL/network/members
[stars-shield]: https://img.shields.io/github/stars/ZigRazor/MTL.svg?style=for-the-badge
[stars-url]: https://github.com/ZigRazor/MTL/stargazers
[issues-shield]: https://img.shields.io/github/issues/ZigRazor/MTL.svg?style=for-the-badge
[issues-url]: https://github.com/ZigRazor/MTL/issues
[license-shield]: https://img.shields.io/github/license/ZigRazor/MTL.svg?style=for-the-badge
[license-url]: https://github.com/ZigRazor/MTL/blob/master/LICENSE
