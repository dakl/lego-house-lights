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

void setup() {

    pinMode(outdoor_lights_pin, OUTPUT);
    pinMode(indoor_lights_pin, OUTPUT);
    // pinMode(street_light_pin, OUTPUT);
    
    Particle.function("set_outdoor", toggle_outdoor_lights);
    Particle.function("set_indoor", toggle_indoor_lights);
    // Particle.function("set_street", toggle_street_lights);

    Particle.variable("outd_state", &outdoor_lights_state, INT);
    Particle.variable("ind_state", &indoor_lights_state, INT);
    // Particle.variable("street_state", &street_lights_state, INT);

    digitalWrite(outdoor_lights_pin, HIGH);
    digitalWrite(indoor_lights_pin, HIGH);
    // digitalWrite(street_lights_pin, HIGH);

}

void loop() {
    
      // We'll leave it on for 1 second...
      delay(1000);
    
      // Then we'll turn it off...
      //digitalWrite(outdoor_lights_pin, LOW);
      //digitalWrite(indoor_lights_pin, HIGH);
    
      // Wait 1 second...
      delay(1000);
    
      // And repeat!
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

