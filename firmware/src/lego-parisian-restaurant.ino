/*
 * Project lego-parisian-restaurant
 * Description: Control my LEGO Parisian Restaurant over http
 * Author: Daniel Klevebring
 * Date: 2017-09-17
 */

// ------------
// LEGO Modular Building Lights Control
// ------------

#include "MQTT.h"

/* ======================= prototypes =============================== */

void callback(char *topic, byte *payload, unsigned int length);
int setState(int relayNumber, int relayState);

/* ======================= main.ino ======================== */

MQTT client("worker0", 1883, callback);

char *COMMANDS_TOPICS = "commands/lego/#";
char *EVENTS_TOPIC_TEMPLATE = "events/lego/";

int ttl = 16777215;

int PINS[] = {D0, D1, D2, D3};
int STATES[] = {0, 0, 0, 0};

int FAILED_TO_PARSE_PIN = -100;
int FAILED_TO_PARSE_STATE = -200;

void callback(char *_topic, byte *payload, unsigned int length)
{
    char p[length + 1];
    memcpy(p, payload, length);
    p[length] = NULL;

    Particle.publish("event_callback", "handing payload: " + String(p), ttl);

    String topic = String(_topic);
    int relayNumber = topic.charAt(topic.length() - 1) - '0';

    if (String("ON").equals(p))
    {
        setState(relayNumber, HIGH);
        client.publish(String(EVENTS_TOPIC_TEMPLATE) + String(relayNumber), "ON", true);
    }
    else if (String("OFF").equals(p))
    {
        setState(relayNumber, LOW);
        client.publish(String(EVENTS_TOPIC_TEMPLATE) + String(relayNumber), "OFF", true);
    }
}


void reset_handler()
{
    // tell the world what we are doing
    Particle.publish("reset", "going down for reboot NOW!", ttl);
}

int setState(int relayNumber, int relayState)
{
    // write to the appropriate relay
    digitalWrite(PINS[relayNumber - 1], relayState);

    // update states variable
    STATES[relayNumber - 1] = relayState;

    return 0;
}


void ready() {
    Particle.publish("on", "Turning on.", ttl);


    for(int k = 0; k < 5; k++){
        for (int pin : PINS) {
            digitalWrite(pin, HIGH);
        }
        delay(100);
        for (int pin : PINS) {
            digitalWrite(pin, LOW);
        }
        delay(100);
    }
    Particle.publish("booted", "lego-house-lights is ready.", ttl);
}


void setup() {
    Particle.publish("booting", "lego-house-lights is setting up.", ttl);

    // register the reset handler
    System.on(reset, reset_handler);

    for (int pin : PINS)
    {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }

    // // connect to the mqtt broker
    client.connect("lego-house-sparkclient");

    // publish/subscribe
    if (client.isConnected())
    {
        Particle.publish("MQTT: connected", PRIVATE);

        client.publish(String(EVENTS_TOPIC_TEMPLATE) + "general", "Lego Buildings came online.");
        client.subscribe(COMMANDS_TOPICS);
    }

    ready();
}

void loop()
{
    if (client.isConnected())
        client.loop();
}