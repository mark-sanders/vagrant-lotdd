# vagrant-lotdd
Vagrant-based development environment for C++ test-driven development.

See [Modern C++ Programming with Test-Driven Development](https://pragprog.com/book/lotdd/modern-c-programming-with-test-driven-development) by Jeff Langr.

Just using Vagrant shell provision, and assuming we're in a Windows environment.

The Vagrantfile starts with a Ubuntu 14.04 image then installs build essentials (gcc, make, etc.), git, cmake and unzip.

Then it downloads and builds [Google Mock](https://code.google.com/p/googlemock/) version 1.6.0

Start developing modern, test-driven C++ with the following commands:
```
vagrant up
vagrant ssh
cd projects/c2
mkdir mybuild
cd mybuild
cmake .. && make && ./test
```