# Architecture

## Smartphone App

The application receives the messages sent by Beacons (using Bluetooth LE) and understands the room in which it is.
The App sends a message **A** (JSON) to Google Cloud Platform (using HTTPS). The message contains:

- The location (identified by the room number)
- Player Username
- Live Score
- Starting time

The Cloud Infrastructure sends back a JSON message **M** structured like this:

- A Question Array
- An answer Array
- An array containing correct answers
- an array that contains “Fun Facts” about the statues
- The ranking of all players

The user answers the question, the application checks if the answer is correct or not, and then sends a Message **B** to the Cloud Infrastructure. **B** is structured in the following way:

- Player Location (Room number)
- Username
- actual score
- actual time

Every time the user changes room the app sends a message **B** to the Cloud Infrastructure if the room has not been visited yet by the user, the Cloud Infrastructure replays with a message **M**.

For the application we use Flutter that guarantees the compatibility cross-platform with a single codebase. Plus, it has all the necessary libraries for managing Bluetooth, JSON, and HTTP.

## Cloud Infrastructure on Google Cloud Platform

On Google platform we use:

- [Google Pub/Sub](https://cloud.google.com/pubsub?hl=it): A message broker, receives messages through HTTP, every new message received on a topic T run a serverless function.
- [Google Cloud Function](https://cloud.google.com/functions?hl=it): To execute Server-less functions that saves messages in a SQL database. The platform scales automatically scales stateless containers.
- [Google Cloud SQL](https://cloud.google.com/sql/): to manage **relational** databases. It is a Server with low latency.
- [Google Data Studio](https://datastudio.google.com/): Data visualisation platform that allows selecting Google BigQuery as input to have data for each message published on topic T.

## The Things

### Opzione 1

- Board [STM NUCLEO-F446RE](https://www.st.com/en/evaluation-tools/nucleo-f446re.html)
- [X-NUCLEO-IDB05A1](https://www.st.com/en/ecosystems/x-nucleo-idb05a1.html) Bluetooth Low Energy expansion board

### Opzione 2

Board [nRF52DK](https://www.nordicsemi.com/Software-and-Tools/Development-Kits/nRF52-DK) **on Iotlab** for testing.

### Opzione 3

[Estimote Proximity Beacons](https://estimote.com/)
