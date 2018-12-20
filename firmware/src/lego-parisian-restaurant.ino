/*
 * Project lego-parisian-restaurant
 * Description: Control my LEGO Parisian Restaurant over http
 * Author: Daniel Klevebring
 * Date: 2017-09-17
 */

// ------------
// LEGO Parisian Restaurant Light Automation
// ------------

int time_to_live = 16777215;

int PINS[] = {D0, D1, D2, D3};
int PINCOUNT = sizeof(PINS)/sizeof(PINS[0]);
int INITIAL_STATES[] = {0, 0, 0, 0};

int FAILED_TO_PARSE_PIN = -100;
int FAILED_TO_PARSE_STATE = -200;

void reset_handler()
{
    // tell the world what we are doing
    Particle.publish("reset", "going down for reboot NOW!", time_to_live);
}

int getPinIndex(String args)
{
    Particle.publish("get_pin_index", "Getting pin index from args " + args, time_to_live);
    // parse the relay number
    int pinIndex = args.charAt(0) - '0';
    Particle.publish("get_pin_index", "Pin index was " + String(pinIndex) , time_to_live);    
    // do a sanity check
    if (pinIndex < 0 || pinIndex > 3) return -1;
    else return pinIndex;
}

int getValue(String args)
{
    unsigned int pinIndex, value;    
    int n = sscanf(args, "%u,%u", &pinIndex, &value);

    Particle.publish("got_value", "value is " + String(value), time_to_live);    
    // do a sanity check
    if (value < 0 || value > 1) return -1;
    else return value;
}

/*
command format: pinIndex,state
examples: `0,HIGH`, `3,LOW`
POST /v1/devices/{DEVICE_ID}/pin
# EXAMPLE REQUEST
curl https://api.particle.io/v1/devices/0123456789abcdef/pin \
-d access_token=123412341234 -d params=1,HIGH
*/
int pinControl(String args)
{
    Particle.publish("set_state", "Setting state using args " + args, time_to_live);
    // parse the relay number
    int pinIndex = getPinIndex(args);
    if (pinIndex == -1) return FAILED_TO_PARSE_PIN;
    int pin = PINS[pinIndex];

    // find out the state of the relay
    int value = getValue(args);
    if (value == -1) return FAILED_TO_PARSE_STATE;

    digitalWrite(pin, value);
    return 1;
}

/*
command format: 1 (range 0 to 3)
POST /v1/devices/{DEVICE_ID}/state
# EXAMPLE REQUEST
curl https://api.particle.io/v1/devices/0123456789abcdef/state \
-d access_token=123412341234 -d params=1
*/
int pinState(String args)
{
    Particle.publish("get_state", "Reading pin " + args +  " state.", time_to_live);
    // parse the relay number
    int pinIndex = getPinIndex(args);
    if (pinIndex == -1) return FAILED_TO_PARSE_PIN;

    return digitalRead(PINS[pinIndex]);
}

void ready() {
    Particle.publish("on", "Turning on.", time_to_live);
    for(int k = 0; k < 5; k++){
        for (int i = 0; i < PINCOUNT; i++) {
            digitalWrite(PINS[i], HIGH);
        }
        delay(100);
        for (int i = 0; i < PINCOUNT; i++) {
            digitalWrite(PINS[i], LOW);
        }
        delay(100);
    }
    Particle.publish("booted", "lego-house-lights is ready.", time_to_live);
}


void setup() {
    Particle.publish("booting", "lego-house-lights is setting up.", time_to_live);

    // register the reset handler
    System.on(reset, reset_handler);

    for (int i=0; i<PINCOUNT; i++) {
        pinMode(PINS[i], OUTPUT);
    }

    // register control function
    Particle.function("pin", pinControl);

    // register state function
    Particle.function("state", pinState);

    ready();
}

void loop() {}
