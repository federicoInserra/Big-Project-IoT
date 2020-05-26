# Architecture

The following architecture is the one that we thought about for the project. At the end of this explanation you will find another architecture that is the one that we are going to implement due to a lack of resources.

## End-user component: Objects with NFC tags

We have some objects to interact with the statue. Every object has an NFC tag with an ID that can be read by the board. For each statue we have three objects, the first one is relevant to the statue (e.g. for a statue of Julio Caesar we might use a stab), and the other two are random objects. When the user reaches the statue with an object, the board reads the message to AWS and receives the correct image to show. If the object was the right one, the image will be a colorized version of the statue, otherwise we might have some funny images showing up.

The application writes on the NFC tag that is positioned on the statue. It's composed by a simple user interface that shows images of the statues and when the user taps on such image the app will show a pop up that tell the user to approach the board near the statue.

When the board read the tag, it checks the code and sends a message over MQTT to AWS platform with the id of the tag and a timestamp.

## Cloud Infrastructure on Amazon Web Services

The cloud infrastructure is an MQTT broker that subscribes to the topic of the statue and publishes on another topic over the MQTT protocol.

We use the cloud infratructure for two main purposes:

1. We can collect statistics on how many people interact with the statues and see which are the most popular plaster casts in the museum. In this way we can highlight the most popular statues or emphasize those that would otherwise be eclipsed.
2. Scalability: If we want to add a statue to the project, we load the image on AWS and the board downloads it and shows it. If it is already downloaded the board use the image locally.

## Internet of Things elements

The Internet of things element is an STM32 Nucleo Board. The board has an NFC tag reader that is activated through the smartphone application.
The board has a wifi module that allows the connection to the internet. We expect to connect a display to the board to show the images of the statues.

## High-level scheme

Object with Nfc Tag <--NFC--> IoT Board <--MQTT--> AWS <--MQTT --> IoT Board\

![Architecture](https://github.com/federicoInserra/Big-Project-IoT/blob/master/photo/arch1.png)\

# Evaluation Architecture

Due to lack of resources we are going to try the code on a different architecture. The first part of the archiecture is the same, we have a smartphone application, instead of objects, that writes on an NFC tag on the board and the board publishes a JSON message on the MQTT topic. The AWS reads this message and sends the image to a raspberry pi board. The raspberry pi is connected to a display that will show the image.

## High-level scheme

Smartphone <--NFC--> IoT Board <--MQTT--> AWS <--MQTT --> Raspberry Pi\
![Architecture](https://github.com/federicoInserra/Big-Project-IoT/blob/master/photo/arch2.png)\

Here you can find the old architecture version [Old document](https://github.com/federicoInserra/Big-Project-IoT/blob/master/1stDelivery/Architecture.md)
