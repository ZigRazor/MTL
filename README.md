<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![GPL-3.0 License][license-shield]][license-url]

![MTL](logo/logo.gif)
# MTL
Multi Thread Library

## Roadmap

- [x] Thread Class
- [x] Thread Manager
- [x] Thread Pool
- [x] Task Class
- [x] Ordered Task
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

Work in Progress...
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