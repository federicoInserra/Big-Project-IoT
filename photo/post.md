# Post
## The Idea
Castgram is a new experience to enjoy inside ancient art museums. During the research for the project, we found out that originally
statues weren't white as they are now but colored. Since few people knew this, we wanted to create an original method to show people this aspect of the museum. We also desired to create a unique user experience so we came up with this idea. Inside one room, there is the board with some objects that are related to different historical figures, represented by a statue in the room. 
When a person chooses an object, he approaches the statue with it and a hologram of the statue appears. The hologram shows the colored statue
that is related to the object, for each object there is a different hologram. With this system, users have a different experience inside the museum that is brand new and they are also able to see the true aspect of classical statues.

## The architecture of the System and components
The hardware components of the system are: 
- NFC tag, attached to the object, that writes on the board.
- STM32 Nucleo board.
- AWS IoT.
- AWS Lambda.
- AWS RDS.
- S3 Bucket.
We used the following protocols:
- MQTT over SSL 
- HTTPS

The architecture is composed in this way, the NFC tag writes on the board a text field when the board receives the message from the tag, it publishes it on the MQTT topic on AWS IoT. 
On AWS, we use a lambda function to save the date and the statue required on a SQL Database, AWS RDS.
The board performs an HTTP request to get the image required and, when it's available, the hologram is shown on a display. Thanks to a prism, the two-dimensional image is reflected as a hologram.

Since the board we used does not have a display
on which to show the image of the hologram, we used a different architecture to evaluate the project. We added a Raspberry Pi that allows us to show the hologram on a screen. 

The architecture is represented here. 

The Raspberry Pi is subscribed to the MQTT topic and, when a message arrives, we check if the image is in main memory, if not, the Raspberry executes an HTTP request to the S3 bucket on AWS and saves the image in main memory. 
## Details of the IoT elements.
The main component of the system is an STM32 Nucleo Board with the following features:
a Cortex M4 core, a Dynamic NFC tag based on M24SR
and the Wi-Fi module with the MbedOS 6.1 operating system. 
The Raspberry Pi is a Model B+ with a processor Core ARM11 Single Core with 512MB of RAM, and the Raspbian operating system. 

The main component of the system is an STM32 Nucleo Board with the following features:
a Cortex M4 core, a Dynamic NFC tag based on M24SR
and the Wi-Fi module with the MbedOS 6.1 operating system. 
The Raspberry Pi is a Model B+ with a processor Core ARM11 Single Core with 512MB of RAM, and the Raspbian operating system. 
A Python 3 script manages the requests for images on the Raspberry Pi
On AWS, we used different services to complete the cloud part of the architecture. 
First, we create an IoT hub that manages the MQTT publish/subscribe request and function as an MQTT broker. We also used the Lambda Function of AWS to send data to the AWS RDS database. 
Lambda function is a function in Node.js 12x that issues a query on the database to insert new entries every time a person activates the hologram. 




