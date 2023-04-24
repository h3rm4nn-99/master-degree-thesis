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

[WIP]
