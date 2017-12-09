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

void setup() {

    pinMode(outdoor_lights_pin, OUTPUT);
    pinMode(indoor_lights_pin, OUTPUT);
    // pinMode(street_light_pin, OUTPUT);
    
    Particle.function("set_indoor_on", set_indoor_on); // POST /v1/devices/{DEVICE_ID}/set_indoor_on
    Particle.function("set_indoor_off", set_indoor_off); // POST /v1/devices/{DEVICE_ID}/set_indoor_off
    Particle.function("set_outdoor_on", set_outdoor_on); // POST /v1/devices/{DEVICE_ID}/set_outdoor_on
    Particle.function("set_outdoor_off", set_outdoor_off); // POST /v1/devices/{DEVICE_ID}/set_outdoor_off
    // Particle.function("set_streetlight_on", set_streetlight_on); // POST /v1/devices/{DEVICE_ID}/set_streetlight_on
    // Particle.function("set_streetlight_off", set_streetlight_off); // POST /v1/devices/{DEVICE_ID}/set_streetlight_off

    // GET /v1/devices/{DEVICE_ID}/get_indoor_state
    Particle.variable("get_indoor_state", &indoor_lights_state, INT);

    // GET /v1/devices/{DEVICE_ID}/get_outdoor_state
    Particle.variable("get_outdoor_state", &outdoor_lights_state, INT);
    
    // GET /v1/devices/{DEVICE_ID}/get_streetlight_state
    // Particle.variable("get_streetlight_state", &street_lights_state, INT);

    digitalWrite(outdoor_lights_pin, HIGH);
    digitalWrite(indoor_lights_pin, HIGH);
    // digitalWrite(street_lights_pin, HIGH);

}

void loop() {
    delay(DELAY_LOOP);
}

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