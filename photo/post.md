# Post

## The Idea
**Castgram** is a new experience to enjoy inside ancient art museums. During the research for the project, we found out that originally
statues weren't white as they are now but coloured. Since few people knew this, we wanted to create an original method to show people this aspect of the museum. We also desired to create a unique user experience so we came up with this idea. Inside one room, there is the board with some objects that are related to different historical figures, represented by a statue in the room. 
When a person chooses an object, he approaches the statue with it and a hologram of the statue appears. The hologram shows the coloured statue
that is related to the object, for each object there is a different hologram. With this system, users have a different experience inside the museum that is brand new and they are also able to see the true aspect of classical statues.

## The architecture of the System and components
The hardware components of the system are: 
- NFC tag, attached to the object, that can be read from the board.
- STM32 Nucleo board.
- AWS IoT.
- AWS Lambda.
- AWS RDS.
- AWS S3.

We used the following protocols:
- MQTT over SSL 
- HTTPS

The architecture is composed in this way, the NFC tag writes on the board an NDEF text field when the board receives the message from the tag, it publishes it on the MQTT topic on AWS IoT. 
On AWS, we use an AWS Lambda function to save the timestamp with timezone, and the statue required on a PostgresSQL Database on AWS RDS.
The board performs an HTTP request to get the image required and, when it's available, the hologram is shown on a display. Thanks to a prism, the two-dimensional image is reflected as a hologram.

Since the board we used does not have a display
on which to show the image of the hologram, we used a different architecture to evaluate the project. We added a Raspberry Pi that allows us to show the hologram on a screen. 

The architecture is represented here. 

<Image>

The Raspberry Pi is subscribed to the MQTT topic and, when a message arrives, we check if the image is in the main memory, if not, the Raspberry executes an HTTP request to the S3 bucket on AWS and saves the image in main memory.


## Details of the IoT elements.
The main component of the system is an STM32 B-L475E-IOT01A Nucleo Board by STMicroelectronics with the following main features:a Cortex M4 core, a Dynamic NFC tag based on the M24SR series and a Wi-Fi module from Inventek Systems (ISM43362-M3G-L44), running MbedOS 6.1. 
The Raspberry Pi is a Model 1B+ with a processor Core ARM11 Single Core with 512MB of RAM, and the Raspbian operating system. 
A Python 3 script manages the requests for images on the Raspberry Pi.
On AWS, we used different services to complete the cloud part of the architecture. 

First, we create an IoT object on AWS IoT that manages the MQTT publish/subscribe request and function as an MQTT broker.
Every message published on the selected topic, an AWS Lambda function is triggered, with the main purpose of saving the MQTT payload on PostgresSQL database on AWS RDS.
The Lambda function is a function in Node.js 12.x that issues a query on the database to insert new entries every time a person activates the hologram.

### Part 1: MbedOS 6
To program the STM32 board, we used MbedOS 6 che con le sue API ci permette di eseguire semplicemente le quattro operazioni principali che deve compiere la board:

1. Connettersi ad Internet usando il modulo Wi-Fi.
2. Connettersi al broker MQTT su AWS IoT usando MQTT over SSL.
3. Leggere il contenuto della EEPROM NFC.
4. Pubblicare il contenuto della EEPROM NFC su un topic MQTT.

Per il punto 1 basta impostare i campi `wifi-ssid` e `wifi-password` nel file `mbed_app.json` e nel `main.cpp` 

```
network = WiFiInterface::get_default_instance();
int ret = network->connect(MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA_WPA2);
```
### Part 2: The setup on AWS
### Part 3: Python on the Raspberry
### Part 4: NFC on the Web: WebNFC APIs


## Evaluation of the system 
We evaluated the project by establishing a set of Key Performance Indicators at the beginning of the development cycle. We also interviewed some people to have first feedback on the idea. 
From a more technical point of view, we defined the following KPIs that are relative to the characteristics of a system. 
The first evaluation was on the privacy of users. We didn't want to store any sensitive information about our users, and this was possible because we only store inside the database the date and time of activation of the hologram. 
Another KPI was the data security, obtained thanks to AWS that claims high security for its databases. Data security is also implemented in the communication because between the board and AWS is secured by MQTT on SSL, and the image is requested by an HTTPS Get. All these protocols contribute to keeping all information safe.
<Error>
The reactivity of the system, namely how much time passes between the interaction with the board and when the hologram appears. We obtained around 2.2 seconds of latency using **OpenCV** as the library that manages the opening of the image inside the python script.
</Error>
The last technical point for the evaluation was the total cost of the system, that shouldn't be too high. We estimated a final cost of 195€ for the system, including the costs of AWS. 
We also considered the user experience as a key point for the success of the system. This is done by considering the increasing of visits at the museum, the ratio of people that visit the museum, and the number of people that use the system and the satisfaction of users. 
We will manage the first two once we install the Castgram in a museum, for the third one we asked users that tested Castgram to rate the system under different aspects, ease of use, aesthetic and general impression of the system. We scored an average grade 9/10 on the aesthetic, average grade 7/10 on ease of use, and average grade 8/10 on the general impression.
