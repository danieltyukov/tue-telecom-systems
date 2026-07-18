# Telecommunication Systems (5XTA0), TU/e

Simulation work for the Telecommunication Systems course (course code 5XTA0) in the
Electrical Engineering programme at Eindhoven University of Technology (TU/e). The
repository holds two OMNeT++ discrete-event simulation projects and a MATLAB script. One
project models call blocking in a circuit-switched exchange (the Erlang-B loss model), the
other models medium access control across a set of wireless cells using the INET
framework.

The GitHub language detector reports SuperCollider for this repository. That is a
misclassification: the `.sc` file is an Eclipse CDT scanner-configuration file, not audio
code. The actual work is OMNeT++ network descriptions (`.ned`), message definitions
(`.msg`), C++ modules (`.cc`, `.h`), and MATLAB.

## Erlang loss model (`src/`)

A discrete-event model of a telephone exchange with a fixed number of shared channels,
built as OMNeT++ simple modules in C++. A `CentralUnit` module holds the channel pool and
a list of active links. `User` modules draw call durations and inter-call times from
exponential and Erlang distributions and place calls to random other users. On each call
request the central unit either sets up the call, rejects it because the callee is busy, or
rejects it because no channel is free, and it counts requests, successes, hang-ups, and
both rejection types. Running this over many calls gives a simulated blocking probability
that can be compared against the analytical Erlang-B formula.

- `CentralUnit.cc`, `CentralUnit.h`, `CentralUnit.ned`: channel allocation and call
  bookkeeping.
- `User.cc`, `User.h`, `User.ned`: call generation and per-user state (idle, caller,
  callee).
- `Erlang.msg`: the call-signalling packet carrying caller and callee IDs.
- `package.ned`: package and namespace declaration.

`Erlang_loss_model.m` computes the analytical side: the Erlang-B blocking probability as a
function of offered traffic load, swept over channel counts from 7 to 70, plotted on both
linear and logarithmic axes. This is the reference the simulation is checked against.

## MAC techniques (`mac-techniques/`)

A medium access control assignment built on the INET framework. The network places seven
wireless cells, each an antenna tower (`WirelessHost`) with several ad-hoc nodes
(`AdhocHost`), backhauled to a central server over 100 Mbps Ethernet. The nodes run the
LMAC scheduled-access MAC (four time slots, 100 ms slot duration) over an APSK scalar radio
at 2.4 GHz with BPSK modulation, and send UDP traffic to the server. Neighbouring cells
alternate between 2.425 GHz and 2.475 GHz center frequencies, so the configuration also
exercises frequency reuse and inter-cell interference through a shared radio medium with a
defined SNIR threshold and receiver sensitivity.

- `5xta0_mac_assignment.ned`: the seven-cell network topology and wired backhaul.
- `omnetpp.ini`: radio, MAC, per-cell frequency, and traffic configuration.

## Topics

- Circuit switching and the Erlang-B loss model
- Blocking probability against offered traffic load
- Discrete-event simulation of call setup and teardown
- Exponential and Erlang inter-arrival and holding times
- Medium access control and scheduled (TDMA-style) access with LMAC
- Cellular layout, frequency reuse, and inter-cell interference
- Radio link parameters: modulation, bandwidth, SNIR threshold, sensitivity

## Running

The `src/` and `mac-techniques/` projects are OMNeT++ projects; the MAC project depends on
the INET framework. Open them in the OMNeT++ IDE (or build with the provided `Makefile` and
`opp_run`) and launch the simulation from `omnetpp.ini`. The Erlang project builds the
`CentralUnit` and `User` modules from the C++ sources; the MAC project uses INET's built-in
host, radio, and MAC modules configured through the ini file. Run `Erlang_loss_model.m` in
MATLAB to produce the analytical blocking-probability curves.

## Technologies

OMNeT++, INET framework, C++, MATLAB.
