# Architecture

## Smartphone App (Client)

The application receives the messages sent by Beacons (using BLE) and understands the room in which it is.
The App sends a message **A** (JSON) to Google Cloud Platform (using HTTPS). The message contains:

- The location (identified by the room number)
- Player Username
- Live Score
- Starting time

GCP sends back a JSON message **M** structured like this:

- A Question Array
- An answer Array
- An array containing correct answers
- an array that contains “Fun Facts” about the statues
- The ranking of all players

The user answers the question, the application checks if the answer is correct or not, and then sends a Message **B** to the GCP. **B** is structured in the following way:

- Player Location (Room number)
- Username
- actual score
- actual time

Every time the user changes room the app sends a message **B** to GCP if the room has not been visited yet by the user, GCP replays with a message **M**.

For the application we use Flutter that guarantees the compatibility cross-platform with a single codebase. Plus, it has all the necessary libraries for BLE, JSON, and HTTP.

## GCP (PaaS)

On Google platform we use:

### Opzione 1

- [Google Cloud Run](https://cloud.google.com/run/): to run containers that include a RESTFUL application that interacts with the SQL Database. The platform scale automatically stateless containers.
- [Google Cloud SQL](https://cloud.google.com/sql/): to manage **relational** databases. It is a Server with low latency.

### Opzione 2

- [Google Pub/Sub](): message broker, receives messages through Http, every new message received on a topic T asks for a serverless function.
- [Google Cloud Function](): To execute Server-less functions that saves messages in a SQL database. The platform scales automatically scales stateless containers.
- [Google Cloud SQL](https://cloud.google.com/sql/): to manage **relational** databases. It is a Server with low latency.
- - [Google BigQuery](): Executes SQL queries every time that a message T is published (it’s useful to filter data)
- [Google Data Studio](): Data visualization platform that allows selecting Google BigQuery as input to have data for each message published on topic T.

## The Things

Range del Bluetooth non ben chiaro, da cercare bene

### Opzione 1

A Board STM NUCLEO-F446RE (14USD) + X-NUCLEO-IDB05A1 Bluetooth Low Energy expansion board (11USD)

### Opzione 2

Board nrf52dk (Bluetooth 5.2) https://www.nordicsemi.com/Software-and-Tools/Development-Kits/nRF52-DK **on Iotlab** for test (?)

### Opzione 3

Beacon
