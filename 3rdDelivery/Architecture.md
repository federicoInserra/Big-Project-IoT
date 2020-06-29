# Architecture

The following architecture is the one that we thought about for the project. At the end of this explanation you will find another architecture that is the one that we are going to implement due to a lack of resources.

## End-user component: Objects with NFC tags

We have some objects to interact with the statue. Every object has an NFC tag with an ID that can be read by the board. For each statue we have three objects, the first one is relevant to the statue (e.g. for a statue of Julio Caesar we might use a stab), and the other two are random objects. When the user reaches the statue with an object, the board reads the message to AWS and receives the correct image to show. If the object was the right one, the image will be a colorized version of the statue, otherwise we might have some funny images showing up.

The application writes on the NFC tag that is positioned on the statue. It's composed by a simple user interface that shows images of the statues and when the user taps on such image the app will show a pop up that tell the user to approach the board near the statue.

When the board read the tag, it checks the code and sends a message over MQTT to AWS platform with the id of the tag and a timestamp.

## Cloud Infrastructure on Amazon Web Services

The Cloud Infrastructure is on AWS. We use AWS IoT's MQTT broker to manage the communication between the boards.

We use the cloud infratructure for two main purposes:

1. We can collect statistics on how many people interact with the statues and see which are the most popular plaster casts in the museum. In this way we can highlight the most popular statues or emphasize those that would otherwise be eclipsed.
2. Scalability: If we want to add a statue to the project, we load the image on AWS and the board downloads it and shows it. If it is already downloaded the board use the image locally.

Inside the AWS infrastructure we used the SQL database on Amazon RDS that can be queried by Grafana to obtain informations about the popularity of a statue and display them on a dashboard that is available for museum curators. 

## Internet of Things elements

The Internet of Things element is an STM32 Nucleo Board. The board has an NFC tag reader that is activated through an NFC tag or a Smartphone with the NFC module.
The board has a Wi-Fi module that allows the connection to the internet. We expect to connect a display to the board to show the images of the statues.

## High-level scheme

Object with NFC Tag <--NFC--> STM32 Board <--MQTT--> AWS <--MQTT --> STM32 Board
                                                      |
                                                      |
                                                      v
                                                 SQL Database --> Dashboard   
![Architecture](https://github.com/federicoInserra/Big-Project-IoT/blob/master/photo/arch1.png)\

# Evaluation Architecture

Due to lack of resources we are going to try the code on a different architecture. The first part of the archiecture is the same, but we have a smartphone application, instead of objects, that writes on the NFC tag on the board and the board publishes a message on the MQTT topic containing the tect record of the NFC tag. AWS IoT receive this message, and the Raspberry Pi that is subsribed to the topic receive the message sent from the STM32 board. The Raspberry Pi is connected to a display that will show the image that has as identifier the message received. If the image is not present locally a request to AWS is perfomed asking for the image, as soon the image arrives it is saved and then it's shown.

The board that we used is the [STM32 B-L475E-IOT01A](https://www.st.com/en/evaluation-tools/b-l475e-iot01a.html).
For our purpose, the most important features are:

* A Cortex M4 core
* Dynamic NFC tag based on M24SR
* ISM43362 Wi-Fi module 

Considering that the M24SR is just a Dynamic NFC tag and not an NFC reader, we can't use an object with an NFC tag on it, but we have to use a Smartphone that can act as reader/writer to write on the NFC EEPROM.

## High-level scheme

Smartphone <--NFC--> IoT Board <--MQTT--> AWS <--MQTT--> Raspberry Pi + Display
                                           |
                                           |
                                           v
                                    SQL Database --> Dashboard   
![Architecture](https://github.com/federicoInserra/Big-Project-IoT/blob/master/photo/arch2.png)\

## Old Document
Here you can find the old architecture version [Old document](https://github.com/federicoInserra/Big-Project-IoT/blob/master/2ndDelivery/Architecture.md)
