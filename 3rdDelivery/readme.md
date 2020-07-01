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

To program the STM32 board, we used MbedOS 6 which with its API allows us to simply perform the four main operations that the board must perform:

1. Connettersi ad Internet usando il modulo Wi-Fi.
2. Connettersi al broker MQTT su AWS IoT usando MQTT over SSL.
3. Leggere il contenuto della EEPROM NFC.
4. Pubblicare il contenuto della EEPROM NFC su un topic MQTT.

For point 1 just set the fields `wifi-ssid` and `wifi-password` in the file `mbed_app.json`, then in the `main.cpp` we can connect to the internet using our default network interface.

```
WiFiInterface *network;
network = WiFiInterface::get_default_instance();
int ret = network->connect(MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA_WPA2);
```

The `MQTT_server_setting.h` and `MQTT_credentials.h` files contain respectively the parameters of the MQTT broker and the keys needed to establish the connection. So to establish a connection we have to open a `TLSSocket` in the following way:

```
TLSSocket *socket = new TLSSocket;
SocketAddress addr;
nsapi_error_t ret = network->gethostbyname(MQTT_SERVER_HOST_NAME, &addr);
addr.set_port(MQTT_SERVER_PORT);
ret = socket->open(network);
socket->set_hostname(MQTT_SERVER_HOST_NAME);
ret = socket->set_root_ca_cert(SSL_CA_PEM);
ret = socket->set_client_cert_key(SSL_CLIENT_CERT_PEM, SSL_CLIENT_PRIVATE_KEY_PEM);
ret = socket->connect(addr);
```

And then we can send an MQTT CONNECT packet by writing on the newly created socket.

```
MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
data.cleansession = false;
data.MQTTVersion = 4; // Version 3.1.1
data.clientID.cstring = (char *)MQTT_CLIENT_ID;
mqttClient = new MQTTClient(socket);
int rc = mqttClient->connect(data);
```

To read the content of the NFC tag we can use the NFC tag management libraries based on the M24SR series and NFC Data Exchange Format (NDEF). We must first initialize the tag, set the callbacks and open the session.

```
I2C i2cChannel(NFC_I2C_SDA_PIN, NFC_I2C_SCL_PIN);
M24SR nfcTag(M24SR_ADDR, i2cChannel, &nfc_interrupt_callback, NFC_GPO_PIN,NFC_RF_DISABLE_PIN);
nfcTag.init(NULL);
nfcTag.get_session();
NDefLib::NDefNfcTag &tag = nfcTag.get_NDef_tag();
ReadCallbacks NDefReadCallback(sessionOpenLed, ongoingOperationLed,sessionClosedLed);
tag.set_callback(&NDefReadCallback);
tag.open_session();
```

We are now ready to publish on the MQTT topic the message containing as payload the content of the NFC tag.

```
tag.open_session()
const char *strMessage = NDefReadCallback.get_string();
led = LED_ON;
MQTT::Message message;
message.retained = false;
message.dup = false;
const size_t buf_size = 128;
char *buf = new char[buf_size];
message.payload = (void *)buf;
message.qos = MQTT::QOS0;
int ret =
    snprintf(buf, buf_size, "{ \"name\": \"%s\"}",
            strMessage);
message.payloadlen = ret;
int rc = mqttClient->publish(MQTT_TOPIC_SUB, message);
delete[] buf;
```

### Part 2: The setup on AWS

#### AWS IoT

To get started with AWS IoT, you need an AWS account. Once you have created your account, you can log in and navigate to 
the AWS IoT Console. We are now ready to register a new *Thing* using the web interface. For our demonstration we have setup two things, one for the STM32 board, one for the Raspberry Pi. 
AWS uses certificate-based authentication and authorisation 
to create a secure connection between the device and AWS IoT Core. The easiest way to do that is to use the **"One-click certificate creation"**


/Screenshot 2020-06-30 at 16.20.04.png

You can download the certificate for the thing, the private key, and the root CA for AWS IoT. (You do not need the public key). Save each of them to your computer, choose Activate and then click on Done. Now we need to create a Policy for our thing. AWS IoT Core policies are used to authorise your device to perform AWS IoT Core operations, such as subscribing or publishing to MQTT topics. Your device presents its certificate 
when sending messages to AWS IoT Core. To allow your device to perform AWS IoT Core operations, you must create an 
AWS IoT Core policy and attach it to your device certificate.



In the left navigation menu choose Secure and then Policies. From here click on Create and then insert the name you prefer for the policy and then in the *Advanced mode* view you can insert all the permission needed, in our case the device have to be able to Connect, Publish, Subscribe and Receive. You can view all the policy actions [here](https://docs.aws.amazon.com/iot/latest/developerguide/iot-policy-actions.html)

```
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Effect": "Allow",
      "Action": "iot:Connect",
      "Resource": "*"
    },
    {
      "Effect": "Allow",
      "Action": "iot:Publish",
      "Resource": "*"
    },
    {
      "Effect": "Allow",
      "Action": "iot:Subscribe",
      "Resource": "*"
    },
    {
      "Effect": "Allow",
      "Action": "iot:Receive",
      "Resource": "*"
    }
  ]
}
```

#### AWS RDS
To add a level of persistence of our data, we opted for an SQL database on AWS RDS, using PostgresSQL 10 as the engine, using the *Free Tier* as the creation template, which despite being the least powerful, is still enough for the amount of data it has to handle. 
Let's save the database name, host, port, password and user we will need in the future for the Lambda function and the dashboard.


#### AWS Lambda

With Lambda Layers it’s really easy to connect our Node.js Lambda Function to PostgreSQL an AWS RDS.
We can create a *Layer* that contains the **node-postgres** dependency and attach it to our Node.js function.

To create a layer we have to setup a basic Node.js application  with **node-postgres**  as dependency. In our preferred terminal run:

```
mkdir nodePostgres
cd nodePostgres
mkdir nodejs
cd nodejs
npm init
npm install --save pg
```

In the nodePostgres folder zip the *nodejs* folder inside. You should see nodejs.zip inside the nodePostgres folder.
In the AWS Lambda Console, click the *≡ Menu* at top left, select *Layers* and create a new layer uploading the nodejs.zip file that we have created before with Node.js 12.x as Compatible Runtime.
We are now ready to write our Lambda function from scratch, using Node.js 12.x as Runtime.
Using an NPM package in Lambda Layers works the same way as plain Node.js. `require(‘pg’)` works as expected because the NPM module `pg` is already packaged in the nodePostgres Lambda Layer.
Before to write the code we have to import the layer creato precedentemente and fill the PGDATABASE, PGHOST, PGPASSWORD, PGPORT, PGUSER environment variables using the informations given before by AWS RDS.
The necessary code to save the input of the function in a table in the database is the following:

```
exports.handler = async(event) => {
  const { Client } = require("pg");
  const client = new Client();
  await client.connect();
  const text =
    "INSERT INTO things(timestamp, name, deviceid) VALUES($1, $2, $3) RETURNING *";
  const values = [new Date(event.timestamp), event.name, event.clientid];
  try {
    const res = await client.query(text, values);
    await client.end();
    const response = {
      statusCode: 200,
      result: res.rows[0].name,
    };
    return response;
  }
  catch (err) {
    const response = {
      statusCode: 500,
      result: err,
      values: values
    };
    return response;
  }
};
```

Before testing the code we have to check if the Lambda function can connect to the database, to achieve this we can connect our function to a *virtual private cloud (VPC)*, the same VPC of our database that we can find in the AWS RDS dashboard.

#### Bring all them together 
We have successfully linked AWS Lambda with AWS RDS, how can we trigger this Lambda every time a message is published over MQTT? 
To do it we will use an *AWS IoT rule* who listen for every message that arrives for a certain topic and then does an action with this message. In this case the action will be to invoke the Lambda function precedentemente creata.
On the AWS IoT console click Act->Rules->Create, here we have to perform a query using an [SQL-like syntax](https://docs.aws.amazon.com/iot/latest/developerguide/iot-sql-reference.html).
We want to save all the *MQTT payload*, plus a *timestamp* and the *client id* of the publisher. La query dunque sarà 

```
SELECT *, timestamp() as timestamp, clientid() as clientid FROM '/board'
```

The action will take as input the output of this query, in JSON format. Using the *Add action* button we can select the **"Send a message to a Lambda function"** option and choose our Lambda function.
### Part 3: Python on the Raspberry

### Part 4: NFC on the Web: WebNFC APIs

Since the STM32 B-L475E-IOT01A NFC module works only in the NFC reader/writer mode, it's not possibile to read the signal from an NFC TAG on an object, we have to find a way to let the user write the requested hologram to the board. Both [Google](https://developer.android.com/guide/topics/connectivity/nfc) and [Apple](https://developer.apple.com/documentation/corenfc) provides NFC API to use the NFC module present in many modern smartphones, but we preferred to use the [Web NFC](https://w3c.github.io/web-nfc/) API since they allow to interact with the NFC inside the browser, without users having to download an app. These APIs are currently in draft and are supported only  in Chrome/Chromium 81+, enabling the `#experimental-web-platform-features` flag in `chrome://flags`, but they allow to quickly develop website capable of read/write NFC tags.
On a website serving in HTTPS (HTTP will not work) we will create a function triggered by an HTML5 `<button>` that instantiate an `NDEFWriter` object and start the writing process. Writing a text string to an NFC tag is straightforward, in our case the text string will be the name of the selected statue.

```
async function write(event) {
  let name = event.srcElement.name;
  try {
    const writer = new NDEFWriter();
    textField.innerHTML = "Move your smartphone closer to the receiver";
    await writer.write(name).then(() => {
      textField.innerHTML = "Message sent successfully";
    });
  } catch (error) {
    textField.innerHTML = `Error: ${error}`;
  }
}
```

We can add this `write` function as event listener for our buttons.

```
const buttons = document.querySelectorAll("body > div > button");
const textField = document.getElementById("message");
buttons.forEach((button) => {
  button.addEventListener("click", write);
});
```

The name written on the NFC tag is the name of the HTML button component.

```
<button class="write" name="ca" />
```

### Part 5: The Dashboard on Grafana

To monitor and visualize all the messages stored in the database we built a Dashboard using [Grafana](https://grafana.com/). Grafana allows you to query, visualize, alert on and understand your metrics no matter where they are stored. Create, explore, and share dashboards teams and foster a data driven culture. You can [install](https://grafana.com/grafana/download) it locally, host it online on your severs, or on your preferred PasS. You can also use [Grafana Cloud](https://grafana.com/products/cloud/) that with its *Starter* tier allow you to test the platform without to spend anything.
Once created an account the first thing to do is add a data source, in our case the PostgresSQL 10 database on AWS RDS, always remembering to add the ip address that is trying to connect to the database to you VPC on AWS as inbound rule.

We can perform query on the database and visualize the results using beautiful widgets. The query builder tool allows us to write powerful query without mess-up with the SQL syntax.

/Schermata 2020-06-30 alle 23.34.47.png

## Evaluation of the system

We evaluated the project by establishing a set of Key Performance Indicators at the beginning of the development cycle. We also interviewed some people to have first feedback on the idea.
From a more technical point of view, we defined the following KPIs that are relative to the characteristics of a system.
The first evaluation was on the privacy of users. We didn't want to store any sensitive information about our users, and this was possible because we only store inside the database the date and time of activation of the hologram.
Another KPI was the data security, obtained thanks to AWS that claims high security for its databases. Data security is also implemented in the communication because between the board and AWS is secured by MQTT on SSL, and the image is requested by an HTTPS Get. All these protocols contribute to keeping all information safe.
The reactivity of the system, namely how much time passes between the interaction with the board and when the hologram appears. We obtained around 2.2 seconds of latency using Pillow as the library that manages the opening of the image inside the Python script.
The last technical point for the evaluation was the total cost of the system, that shouldn't be too high. We estimated a final cost of 195€ for the system, including the costs of AWS.
We also considered the user experience as a key point for the success of the system. This is done by considering the increasing of visits at the museum, the ratio of people that visit the museum, and the number of people that use the system and the satisfaction of users.
We will manage the first two once we install the Castgram in a museum, for the third one we asked users that tested Castgram to rate the system under different aspects, ease of use, aesthetic and general impression of the system. We scored an average grade 9/10 on the aesthetic, average grade 7/10 on ease of use, and average grade 8/10 on the general impression.
