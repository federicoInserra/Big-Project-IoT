#define MQTTCLIENT_QOS1 0
#define MQTTCLIENT_QOS2 0

#include "M24SR.h"
#include "MQTTClientMbedOs.h"
#include "MQTT_server_setting.h"
#include "ReadCallbacks.h"
#include "TLSSocket.h"
#include "mbed-trace/mbed_trace.h"
#include "mbed.h"
#include "mbed_events.h"
#include "mbedtls/error.h"

// Netowrk
#define LED_ON MBED_CONF_APP_LED_ON
#define LED_OFF MBED_CONF_APP_LED_OFF

// NFC
#ifdef TARGET_DISCO_L475VG_IOT01A
// Pins definition for the DISCO_L475VG_IOT01A board
#define NFC_I2C_SDA_PIN PB_11
#define NFC_I2C_SCL_PIN PB_10
#define NFC_GPO_PIN PE_4
#define NFC_RF_DISABLE_PIN PE_2
#endif // DISCO_L475VG_IOT01A
#define M24SR_ADDR 0xAC

// Enable button 1
InterruptIn btn1(USER_BUTTON);

// Led
DigitalOut sessionOpenLed(LED1);      // tag session is open
DigitalOut ongoingOperationLed(LED2); // ongoing read/write operation
DigitalOut sessionClosedLed(LED3);    // tag session is closed
DigitalOut led(MBED_CONF_APP_LED_PIN, LED_ON);

/* Flag to be set when received a message from the server. */
static volatile bool isMessageArrived = false;
/* Variable set to true when we receive an interrupt from the NFC component */
static volatile bool nfcInterruptFlag = false;
/* Buffer size for a receiving message. */
const int MESSAGE_BUFFER_SIZE = 128;
/* Buffer for a receiving message. */
char messageBuffer[MESSAGE_BUFFER_SIZE];
/* Flag to be set when the button is pressed */
static volatile bool isPublish = false;

/*
 * Callback function called when a message arrived from server.
 */
void messageArrived(MQTT::MessageData &md) {
  // Copy payload to the buffer.
  MQTT::Message &message = md.message;
  if (message.payloadlen >= MESSAGE_BUFFER_SIZE) {
    // TODO: handling error
  } else {
    memcpy(messageBuffer, message.payload, message.payloadlen);
  }
  messageBuffer[message.payloadlen] = '\0';

  isMessageArrived = true;
}

/*
 * Callback function called when the button1 is clicked.
 */
void btn1_rise_handler() { isPublish = true; }

/** NFC ISR called when the NFC component has a message ready */
static void nfc_interrupt_callback() { nfcInterruptFlag = true; }

int main(int argc, char *argv[]) {
  thread_sleep_for(200);
  mbed_trace_init();
  btn1.rise(btn1_rise_handler);

  printf("\r\nAWS IoT + NFC\r\n");
  bool isSubscribed = false;

  WiFiInterface *network;
  TLSSocket *socket =
      new TLSSocket; // Allocate on heap to avoid stack overflow.
  MQTTClient *mqttClient = NULL;

  printf("Opening network interface...\r\n");
  {
    network = WiFiInterface::get_default_instance();
    if (!network) {
      printf("Error! No network inteface found.\n");
      return -1;
    }

    printf("Connecting to network\n");
    nsapi_size_or_error_t ret = network->connect(MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA_WPA2);
    if (ret) {
      printf("Unable to connect! returned %d\n", ret);
      return -1;
    }
    printf("Network interface opened successfully.\r\n");
    printf("MAC: %s\n", network->get_mac_address());
    SocketAddress a;
    network->get_ip_address(&a);
    printf("IP: %s\n", a.get_ip_address());
    network->get_netmask(&a);
    printf("Netmask: %s\n", a.get_ip_address());
    network->get_gateway(&a);
    printf("Gateway: %s\n", a.get_ip_address());
    printf("RSSI: %d\n\n", network->get_rssi());
    printf("\r\n");
  }
  printf("Connecting to host %s:%d ...\r\n", MQTT_SERVER_HOST_NAME,
         MQTT_SERVER_PORT);
  {
    SocketAddress addr;
    nsapi_error_t ret = network->gethostbyname(MQTT_SERVER_HOST_NAME, &addr);
    if (ret != NSAPI_ERROR_OK) {
      printf("Error! DNS resolution for ifconfig.io failed with %d\n", ret);
      return -1;
    }
    addr.set_port(MQTT_SERVER_PORT);
    ret = socket->open(network);
    if (ret != NSAPI_ERROR_OK) {
      printf("Error! socket->open() returned: %d\n", ret);
      return ret;
    }

    socket->set_hostname(MQTT_SERVER_HOST_NAME);

    ret = socket->set_root_ca_cert(SSL_CA_PEM);
    if (ret != NSAPI_ERROR_OK) {
      printf("Could not set ca cert! Returned %d\n", ret);
      return -1;
    }
    ret = socket->set_client_cert_key(SSL_CLIENT_CERT_PEM,
                                      SSL_CLIENT_PRIVATE_KEY_PEM);
    if (ret != NSAPI_ERROR_OK) {
      printf("Could not set keys! Returned %d\n", ret);
      return -1;
    }
    if (ret != NSAPI_ERROR_OK) {
      printf("Could not connect! Returned %d\n", ret);
      return -1;
    }
    ret = socket->connect(addr);
    if (ret != NSAPI_ERROR_OK) {
      printf("Error! socket->connect() returned: %d\n", ret);
      return -1;
    }
  }
  printf("Connection established.\r\n");
  printf("\r\n");

  printf("MQTT client is trying to connect the server ...\r\n");
  {
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.cleansession = true;
    data.MQTTVersion = 4; // Version 3.1.1
    data.clientID.cstring = (char *)MQTT_CLIENT_ID;

    mqttClient = new MQTTClient(socket);
    int rc = mqttClient->connect(data);
    if (rc != MQTT::SUCCESS) {
      printf("ERROR: rc from MQTT connect is %d\r\n", rc);
      return -1;
    }
  }
  printf("Client connected.\r\n");
  printf("\r\n");

  printf("Client is trying to subscribe a topic \"%s\".\r\n", MQTT_TOPIC_SUB);
  {
    int rc = mqttClient->subscribe(MQTT_TOPIC_SUB, MQTT::QOS0, messageArrived);
    if (rc != MQTT::SUCCESS) {
      printf("ERROR: rc from MQTT subscribe is %d\r\n", rc);
      return -1;
    }
    isSubscribed = true;
  }
  printf("Client has subscribed a topic \"%s\".\r\n", MQTT_TOPIC_SUB);
  printf("\r\n");

  // Turn off the LED to let users know connection process done.
  led = LED_OFF;

  // Create the NFC component
  I2C i2cChannel(NFC_I2C_SDA_PIN, NFC_I2C_SCL_PIN);

  M24SR nfcTag(M24SR_ADDR, i2cChannel, &nfc_interrupt_callback, NFC_GPO_PIN,
               NFC_RF_DISABLE_PIN);

  // init needed to enable the component
  nfcTag.init(NULL);
  // No call back needed since default behavior is sync
  nfcTag.get_session();

  NDefLib::NDefNfcTag &tag = nfcTag.get_NDef_tag();

  printf("NFC Init done\n\r");
  ReadCallbacks NDefReadCallback(sessionOpenLed, ongoingOperationLed,
                                 sessionClosedLed);
  tag.set_callback(&NDefReadCallback); // Set the callback
  tag.open_session();

  while (true) {
    /* Check connection */
    if (!mqttClient->isConnected()) {
      break;
    }
    if (nfcInterruptFlag) {
      nfcInterruptFlag = false;
      // Manage an async event from the NFC component
      nfcTag.manage_event();
    }
    /* Pass control to other thread. */
    if (mqttClient->yield() != MQTT::SUCCESS) {
      break;
    }
    /* Received a control message. */
    if (isMessageArrived) {
      isMessageArrived = false;
      // Just print it out here.
      printf("\r\nMessage arrived:\r\n%s\r\n\r\n", messageBuffer);
    }
    /* Publish data */
    if (isPublish) {
      isPublish = false;
      static unsigned short id = 0;
      tag.open_session(); // Start the callback chain
      const char *strMessage = NDefReadCallback.get_string();

      // When sending a message, LED lights blue.
      led = LED_ON;

      MQTT::Message message;
      message.retained = false;
      message.dup = false;

      const size_t buf_size = 128;
      char *buf = new char[buf_size];
      message.payload = (void *)buf;

      message.qos = MQTT::QOS0;
      message.id = id++;
      int ret = snprintf(buf, buf_size, "%s", strMessage);
      if (ret < 0) {
        printf("ERROR: snprintf() returns %d.", ret);
        continue;
      }
      message.payloadlen = ret;
      // Publish a message.
      printf("Publishing MQTT message.\r\n");
      int rc = mqttClient->publish(MQTT_TOPIC_SUB, message);
      if (rc != MQTT::SUCCESS) {
        printf("ERROR: rc from MQTT publish is %d\r\n", rc);
      }
      printf("MQTT message published.\r\n");
      delete[] buf;
      led = LED_OFF;
    }
  } // While

  printf("The client has disconnected.\r\n");

  if (mqttClient) {
    if (isSubscribed) {
      mqttClient->unsubscribe(MQTT_TOPIC_SUB);
    }
    if (mqttClient->isConnected())
      mqttClient->disconnect();
    delete mqttClient;
  }
  if (socket) {
    socket->close();
  }
  if (network) {
    network->disconnect();
  }
}
