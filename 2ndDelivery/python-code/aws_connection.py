# Import SDK packages
from AWSIoTPythonSDK.MQTTLib import AWSIoTMQTTClient

#import all needed packages
import time
import json
import datetime
import random


#Path for essential files
ROOT_CA = r"rootCa path"
PRIVATE_KEY = r"private key path"
CERTIFICATE = r"certificate path"
ENDPOINT = "aws endpoint"
TOPIC = "/board"


# Custom MQTT message callback
# Modify this to handle the arrival of a message
def customCallback(client, userdata, message):
    print("Received a new message: ")
    print(message.payload)
    print("from topic: ")
    print(message.topic)
    print("--------------\n\n")

def start_connection(topic, payload):
    #This function set the connection with the MQTTClient of AWS

    #Send the unique id of the station who is generating data
    myMQTTClient = AWSIoTMQTTClient("raspberry")

    myMQTTClient.configureEndpoint(ENDPOINT, 8883)
    myMQTTClient.configureCredentials(ROOT_CA, PRIVATE_KEY, CERTIFICATE)

    # Infinite offline Publish queueing
    myMQTTClient.configureOfflinePublishQueueing(-1)
    myMQTTClient.configureDrainingFrequency(2)  # Draining: 2 Hz
    myMQTTClient.configureConnectDisconnectTimeout(10)  # 10 sec
    myMQTTClient.configureMQTTOperationTimeout(5)  # 5 sec


    #Start the connection, publish the data on the channel using the topic
    myMQTTClient.connect()
    myMQTTClient.publish(topic, payload, 0)
    myMQTTClient.subscribe(topic, 1, customCallback)

    return myMQTTClient



#------------------------------------------------------------------------------MAIN--------------------------------------------------------------


payload = {"raspberry space station": "I'm ON, mi ricevi?"}

print("Messagge sent: ", payload)

print("Waiting for messages on topic: ", TOPIC )

# Start the connection with AWS and wait for messages on topic
client = start_connection(TOPIC, json.dumps(payload))

# Wait infinitely for messages
while(True):

    # Save CPU resources 
    time.sleep(100000) 








