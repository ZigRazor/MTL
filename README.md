<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
# MTL

![MTL](logo/logo.gif)
[![Contributors][contributors-shield]][contributors-url] [![Forks][forks-shield]][forks-url] [![Stargazers][stars-shield]][stars-url] [![Issues][issues-shield]][issues-url] [![GPL-3.0 License][license-shield]][license-url]

Multi Threading Library

## Roadmap

- [x] Thread Class
- [x] Thread Manager
- [X] Thread Pool
- [x] Task Class
- [X] Ordered Task
- [x] Task Flow
- [ ] Complete Documentation
- [ ] Doxygen Integration
- [ ] First Beta Release
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
