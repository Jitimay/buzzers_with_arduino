const int relayPins[] = {0, 1, 2, 3, 4, 5, 6, 7}; // Define the pins for your 8 relays
const int buttonPins[] = {14, 15, 16, 17, 18, 19, 20, 21}; // Define the pins for your 8 pushbuttons
const int debounceDelay = 2000; // 5 seconds (5000 milliseconds)
unsigned long lastButtonPressTime = 0; // To track the time of the last button press
bool isRelayActive = false; // To track whether any relay is currently active
int lastButtonIndex = -1; // To store the index of the last pressed button

void setup() {
  for (int i = 0; i < 8; i++) { // Adjust the loop count to match the number of buttons and relays
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW); // Turn off all relays initially
    pinMode(buttonPins[i], INPUT_PULLUP); // Use the internal pull-up resistors for the buttons
  }
}

void loop() {
  unsigned long currentTime = millis(); // Get the current time

  // Check if the delay has elapsed since the last button press
  if (currentTime - lastButtonPressTime >= debounceDelay && !isRelayActive) {
    // Check each pushbutton for activation
    for (int i = 0; i < 8; i++) { // Adjust the loop count to match the number of buttons and relays
      if (digitalRead(buttonPins[i]) == LOW) { // Button pressed
        if (lastButtonIndex != -1 && lastButtonIndex != i) {
          turnOffAllRelays();
          lastButtonPressTime = currentTime; // Reset the last button press time
          isRelayActive = true; // Indicate that a relay is active
        }
        lastButtonIndex = i;
        activateRelay(i);
        break; // Exit the loop after the first button press
      }
    }
  }

  // Reset the system after 5 seconds of inactivity
  if (isRelayActive && currentTime - lastButtonPressTime >= debounceDelay) {
    turnOffAllRelays();
    isRelayActive = false;
    lastButtonIndex = -1; // Reset the lastButtonIndex after 5 seconds
  }
}

void turnOffAllRelays() {
  for (int i = 0; i < 8; i++) { // Adjust the loop count to match the number of relays
    digitalWrite(relayPins[i], LOW);
  }
}

void activateRelay(int relayIndex) {
  if (relayIndex >= 0 && relayIndex < 8) { // Adjust the limit to match the number of relays
    // Activate the specified relay
    digitalWrite(relayPins[relayIndex], HIGH);
    delay(2000); // Optional: Keep the relay activated for 1 second (adjust as needed)
    digitalWrite(relayPins[relayIndex], LOW);
  }
}
