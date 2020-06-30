from awscrt import io, mqtt, auth, http
from awsiot import mqtt_connection_builder
from time import sleep
from json import loads
from requests import get
from tkinter import Tk, Canvas
from PIL import ImageTk, Image
from os import path

# Path for AWS Certificates
ROOT_CA = r"./rootCA.pem"
PRIVATE_KEY = r"./private.key"
CERTIFICATE = r"./cert.crt"
# MQTT Configuration
ENDPOINT = "a3bz5hd2mygo9b-ats.iot.eu-west-3.amazonaws.com"
TOPIC = "/board"
CLIENT_ID = "raspberry_1"
# Images Configuration
S3_URL = "https://statues-iot.s3.eu-west-3.amazonaws.com"
LOCAL_PATH = "./images"


# Open TK
def showImage(filename):
    img = Image.open(filename)
    fit_center(img)

# Open the image
def imageReader(name, localpath=LOCAL_PATH):
    filename = "{}.jpg".format(name)
    fullpath = "{}/{}".format(localpath, filename)
    if path.exists(fullpath):
        print("Image present locally")
        showImage(fullpath)
    else:
        img_url = "{}/{}".format(S3_URL, filename)
        r = get(img_url, stream=True)
        if r.status_code == 200:
            print("Image sucessfully downloaded: ", filename)
            r.raw.decode_content = True
            with open(fullpath, "wb") as f:
                f.write(r.content)
            showImage(fullpath)
        else:
            print("Image {} not downloaded, error {}".format(
                filename, r.status_code))

# Fullscreen Tk
def fit_center(pil_image):
    root = Tk()
    w, h = root.winfo_screenwidth(), root.winfo_screenheight()
    root.bind("<Escape>", lambda e: (e.widget.withdraw(), e.widget.quit()))
    root.after(20000, root.destroy)
    canvas = Canvas(root, width=w, height=h, highlightthickness=0)
    canvas.pack()
    canvas.configure(background='black')
    img_width, img_height = pil_image.size
    ratio = min(w / img_width, h / img_height)
    img_width = int(img_width * ratio)
    img_height = int(img_height * ratio)

    image = ImageTk.PhotoImage(pil_image)
    imagesprite = canvas.create_image(w / 2, h / 2, image=image)
    root.mainloop()


# Callback when connection is accidentally lost.
def on_connection_interrupted(connection, error, **kwargs):
    pass


# Callback when an interrupted connection is re-established.
def on_connection_resumed(connection, return_code, session_present, **kwargs):
    if return_code == mqtt.ConnectReturnCode.ACCEPTED and not session_present:
        print("Session did not persist. Resubscribing to existing topics...")
        resubscribe_future.add_done_callback(on_resubscribe_complete)


def on_resubscribe_complete(resubscribe_future):
    resubscribe_results = resubscribe_future.result()
    print("Resubscribe results: {}".format(resubscribe_results))

    for topic, qos in resubscribe_results['topics']:
        if qos is None:
            exit("Server rejected resubscribe to topic: {}".format(topic))


# Callback when the subscribed topic receives a message
def on_message_received(topic, payload, **kwargs):
    print("Received message from topic '{}': {}".format(topic, payload))
    try:
        json_message = payload.decode('utf8').replace("'", '"')
        data = loads(json_message)
        name = data["name"]
        imageReader(name)
    except Exception as e:
        exit(e)


if __name__ == '__main__':
    # Spin up resources
    event_loop_group = io.EventLoopGroup(1)
    host_resolver = io.DefaultHostResolver(event_loop_group)
    client_bootstrap = io.ClientBootstrap(event_loop_group, host_resolver)
    mqtt_connection = mqtt_connection_builder.mtls_from_path(
        endpoint=ENDPOINT,
        cert_filepath=CERTIFICATE,
        pri_key_filepath=PRIVATE_KEY,
        client_bootstrap=client_bootstrap,
        ca_filepath=ROOT_CA,
        on_connection_interrupted=on_connection_interrupted,
        on_connection_resumed=on_connection_resumed,
        client_id=CLIENT_ID,
        clean_session=False,
        keep_alive_secs=6)
    print("Connecting to {} with client ID '{}'...".format(
        ENDPOINT, CLIENT_ID))
    connect_future = mqtt_connection.connect()
    # Future.result() waits until a result is available
    connect_future.result()
    print("Connected!")
    try:
        # Subscribe
        print("Subscribing to topic '{}'...".format(TOPIC))
        subscribe_future, packet_id = mqtt_connection.subscribe(
            topic=TOPIC,
            qos=mqtt.QoS.AT_LEAST_ONCE,
            callback=on_message_received)
        subscribe_result = subscribe_future.result()
        print("Subscribed with {}".format(str(subscribe_result['qos'])))
        print("Listening...")
        while True:
            sleep(10000)

    except Exception as e:
        exit(e)
