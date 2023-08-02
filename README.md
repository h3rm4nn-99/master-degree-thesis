# Secure UAV Communication using Post-Quantum Cryptography

## What's this?
This repository provides links to other repository on my GitHub Profile containing a fork of various open-source projects that concern **Drones** and, in general, **UAVs**

In particular:

- **ArduPilot**: an open-source autopilot system that supports various vehicle types. It also provides an **emulator** of these vehicles to run the system without actual hardware;
- **QGroundControl**: an open source **GCS** (Ground Control Station) written using the Qt Framework.

## What's the goal of this work?
ArduPilot and QGroundControl talk using the **MAVLink** protocol. 

This protocol is very lightweight but it's also pretty insecure since it doesn't provide any kind of security or communication cryptography measure. A previous [work](https://github.com/angelopassaro/SEC-UAV) by [Angelo Passaro](https://github.com/angelopassaro) tries to enhance the security of the MAVLink protocol using *lightweight cryptography* modifying the above projects.

The goal of my work is to use the same blueprint of the aforementioned work to integrate Post Quantum Cryptography algorithms in the ArduPilot and QGroundControl softwares.

This project uses the `liboqs` (Open Quantum Safe) library that offers a C/C++ implementation of the **Kyber** KEM Algorithm. Thus, it's a pre-requisite of this work.

## Progress
- [x] Recreate the environment of the previous work (kinda);
- [x] Introduce new algorithms (currently working on qgroundcontrol);
- [ ] Test the results

## How to install `liboqs`
Probably the easisest way to install this library is to build if from the [source code](https://github.com/open-quantum-safe/liboqs) and install it **system-wide**. The steps required to build and install the library are listed on their GitHub repository's README but I'll list them here anyway.

1. Install the required dependencies

```
sudo apt install astyle cmake gcc ninja-build libssl-dev python3-pytest python3-pytest-xdist unzip xsltproc doxygen graphviz python3-yaml valgrind
```

2. Clone the repository's main branch and `cd` into the newly-created folder

```
git clone -b main https://github.com/open-quantum-safe/liboqs.git
cd liboqs
```

3. Build the code

```
mkdir build && cd build
cmake -GNinja ..
ninja
```

4. Create a `.deb` package

```
ninja package
```

5. Install the `.deb` package (generated in the current working directory)

```
sudo apt install ./liboqs-0.8.1-dev-Linux.deb
```

From now on, the KEM Algorithm API can be included using the:

```c
#include <oqs/oqs.h>
```

directive.

## How to build?
This section assumes that you're using **Ubuntu Linux 22.04 LTS** (the latest LTS version at the time of writing), that you've already cloned this repository and you have already installed the `build-essential` package that includes the C compiler. 

Initialize the submodules with

```
git submodule init
```

### Ardupilot
Before adding the aforementioned algorithms, you'll have to build the ArduPilot application in order for the necessary files to be generated. According to the [official documentation](https://ardupilot.org/dev/docs/building-the-code.html), you don't need to install any other packages manually. The project provides a script that conveniently automates the process when using Debian Based distributions (Ubuntu is indeed one of them). The script is located at

```
ardupilot-thesis/Tools/environment_install/install-prereqs-ubuntu.sh -y
```

1. Run the script and follow the instructions;
2. Either log-out and log back again or type `. ~/.profile`.

Since in this work we'll be using the SITL emulator, you'll need to configure the `waf` tool to use the `sitl` board as shown below:

3. Enter the ArduPilot directory and initialize (again) the submodules with the previous command;
4. Run the command `ardupilot-thesis/waf configure --board sitl`;
5. Run the command `ardupilot-thesis/waf copter` to use the generic **copter** vehicle type.

### QGroundControl
