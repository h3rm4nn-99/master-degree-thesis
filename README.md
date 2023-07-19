# Secure UAV Communication using Post-Quantum Cryptography

## What's this?
This repository provides links to other repository on my GitHub Profile containing a fork of various open-source projects that concern **Drones** and, in general, **UAVs**

In particular:

- **ArduPilot**: an open-source autopilot system that supports various vehicle types. It also provides an **emulator** of these vehicles to run the system without actual hardware;
- **QGroundControl**: an open source **GCS** (Ground Control Station) written using the Qt Framework.

## What's the goal of this work?
ArduPilot and QGroundControl talk using the **MAVLink** protocol. 

This protocol is very lightweight but it's also pretty insecure since it doesn't provide any kind of security or communication cryptography measure. A previous [work](https://github.com/angelopassaro/SEC-UAV) by [Angelo Passaro](https://github.com/angelopassaro) tries to enhance the security of the MAVLink protocol using *lightweight cryptography* modifying the above projects.

The goal of my work is to use the same blueprint of the aforementioned work to integrate Post Quantum Cryptography algorithms in the MAVLink protocol.

## Progress
- [ ] Recreate the environment of the previous work;
- [ ] Introduce new algorithms;
- [ ] Test the results

## How to build?
This section assumes that you're using **Ubuntu Linux 22.04 LTS** (the latest LTS version at the time of writing), that you've already cloned this repository and you have already installed the `build-essential` package that includes the C compiler.
### Ardupilot
Before adding the aforementioned algorithms, you'll have to build the ArduPilot application in order for the necessary files to be generated. According to the [official documentation](https://ardupilot.org/dev/docs/building-the-code.html), you don't need to install any other packages manually. The project provides a script that automates the process when using Debian Based distributions (Ubuntu is one of them). The script is located at

```
ardupilot-thesis/Tools/environment_install/install-prereqs-ubuntu.sh -y
```

1. Run the script and follow the instructions;
2. Either log-out and log back again or type `. ~/.profile`.

Since in this work we'll be using the SITL emulator, you'll need to configure the `waf` tool to use the `sitl` board as shown below:

4. Run the command `ardupilot-thesis/waf configure --board sitl`
5. Run the command `ardupilot-thesis/waf copter` to use the generic **copter** vehicle type.

### QGroundControl
