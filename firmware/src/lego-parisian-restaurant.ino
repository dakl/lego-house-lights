/*
 * Project lego-parisian-restaurant
 * Description: Control my LEGO Parisian Restaurant over http
 * Author: Daniel Klevebring
 * Date: 2017-09-17
 */

// ------------
// LEGO Parisian Restaurant Light Automation
// ------------

int outdoor_lights_pin = D6; 
int indoor_lights_pin = D5; 
// int street_light_pin = D4; // not yet added in hw

int outdoor_lights_state = 0;
int indoor_lights_state = 0;
// int street_light_state = 0;

int DELAY_LOOP = 50;

int toggle(int pin, int state) {
    digitalWrite(pin, state);
    return state;
}

int toggle_outdoor_lights(String args) {
    int state = args.toInt();
    outdoor_lights_state = toggle(outdoor_lights_pin, state);
    return outdoor_lights_state;
    
}

int toggle_indoor_lights(String args) {
    int state = args.toInt();
    indoor_lights_state = toggle(indoor_lights_pin, state);
    return indoor_lights_state;
}

void set_indoor_on() {
    toggle(indoor_lights_pin, 1);
}

void set_indoor_off() {
    toggle(indoor_lights_pin, 0);
}

void set_outdoor_on() {
    toggle(outdoor_lights_pin, 1);
}

void set_outdoor_off() {
    toggle(outdoor_lights_pin, 0);
}

void ready() {
    for(int k = 0; k < 5; k++){
        set_indoor_on();
        set_outdoor_off();
        delay(100);
        set_indoor_off();
        set_outdoor_on();
        delay(100);
    }
    set_indoor_on();
    set_outdoor_on();
    // set_streetlight_on();
}


void setup() {

    pinMode(outdoor_lights_pin, OUTPUT);
    pinMode(indoor_lights_pin, OUTPUT);
    // pinMode(street_light_pin, OUTPUT);
    
    Particle.function("indoor_on", set_indoor_on); // POST /v1/devices/{DEVICE_ID}/indoor_on
    Particle.function("indoor_off", set_indoor_off); // POST /v1/devices/{DEVICE_ID}/indoor_off
    Particle.function("outdoor_on", set_outdoor_on); // POST /v1/devices/{DEVICE_ID}/outdoor_on
    Particle.function("outdoor_off", set_outdoor_off); // POST /v1/devices/{DEVICE_ID}/outdoor_off
    // Particle.function("streetlight_on", set_streetlight_on); // POST /v1/devices/{DEVICE_ID}/set_streetlight_on
    // Particle.function("streetlight_off", set_streetlight_off); // POST /v1/devices/{DEVICE_ID}/set_streetlight_off

    // GET /v1/devices/{DEVICE_ID}/get_indoor
    Particle.variable("get_indoor", &indoor_lights_state, INT);

    // GET /v1/devices/{DEVICE_ID}/get_outdoor
    Particle.variable("get_outdoor", &outdoor_lights_state, INT);
    
    // GET /v1/devices/{DEVICE_ID}/get_street
    // Particle.variable("get_street", &street_lights_state, INT);

    ready();
}

void loop() {
    delay(DELAY_LOOP);
}