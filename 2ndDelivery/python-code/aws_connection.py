# Import SDK packages
from AWSIoTPythonSDK.MQTTLib import AWSIoTMQTTClient

# import all needed packages
import time
import json
import datetime
import tkinter
import random
import PIL.Image
from PIL import ImageTk


# Path for essential files
ROOT_CA = r"./rootCA.pem"
PRIVATE_KEY = r"./private.key"
CERTIFICATE = r"./cert.crt"
ENDPOINT = "a25zaonwonq5gg-ats.iot.us-east-1.amazonaws.com"
TOPIC = "/board"

def fit_center(pil_image):
    root = tkinter.Tk()
    w, h = root.winfo_screenwidth(), root.winfo_screenheight()
    root.overrideredirect(1)
    root.attributes("-fullscreen", True)
    root.wm_attributes("-topmost", 1)
    root.geometry("%dx%d+0+0" % (w, h))
    root.focus_set()
    root.bind("<Escape>", lambda e: (e.widget.withdraw(), e.widget.quit()))
    root.after(20000, root.destroy) 
    canvas = tkinter.Canvas(root, width=w, height=h, highlightthickness=0)
    canvas.pack()
    canvas.configure(background='black')

    img_width, img_height = pil_image.size
    ratio = min(w / img_width, h / img_height)
    img_width = int(img_width * ratio)
    img_height = int(img_height * ratio)
    pil_image = pil_image.resize((img_width, img_height), PIL.Image.ANTIALIAS)

    image = ImageTk.PhotoImage(pil_image)
    imagesprite = canvas.create_image(w / 2, h / 2, image=image)
    root.mainloop()


# Custom MQTT message callback
# Modify this to handle the arrival of a message
def customCallback(client, userdata, message):
    print("Received a new message: ")
    print(str(message.payload.decode("utf-8")))
    imageReader(str(message.payload.decode("utf-8")))
    print("from topic: ")
    print(message.topic)
    print("\n")


def start_connection(topic, payload):
    print("Start connection")
    # This function set the connection with the MQTTClient of AWS
    # Send the unique id of the station who is generating data
    myMQTTClient = AWSIoTMQTTClient("raspberry")

    myMQTTClient.configureEndpoint(ENDPOINT, 8883)
    myMQTTClient.configureCredentials(ROOT_CA, PRIVATE_KEY, CERTIFICATE)

    # Infinite offline Publish queueing
    myMQTTClient.configureOfflinePublishQueueing(-1)
    myMQTTClient.configureDrainingFrequency(2)  # Draining: 2 Hz
    myMQTTClient.configureConnectDisconnectTimeout(10)  # 10 sec
    myMQTTClient.configureMQTTOperationTimeout(5)  # 5 sec
    # Start the connection, publish the data on the channel using the topic
    myMQTTClient.connect()
    myMQTTClient.publish(topic, payload, 0)
    myMQTTClient.subscribe(topic, 1, customCallback)

    return myMQTTClient


# Open the image
def imageReader(filename, path="./images"):
    try:
        img = PIL.Image.open(filename + ".jpg")
        fit_center(img)
    except IOError:
        pass
    return


if __name__ == "__main__":
    payload = {"raspberry space station": "I'm ON, mi ricevi?"}
    # print("Messagge sent: ", payload)
    # print("Waiting for messages on topic: ", TOPIC)
    # Start the connection with AWS and wait for messages on topic
    client = start_connection(TOPIC, json.dumps(payload))

    # Wait infinitely for messages
    while True:
        # Save CPU resources
        time.sleep(100000)
