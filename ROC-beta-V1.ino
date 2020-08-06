int PHOTO = 0;
int LED = 8;
int LIMIT = 950;
int DELAY = 5;

int whetherIncomingSignalOn = 0;
int currentBitCount;

int currentCharacter;

void setup() {
    pinMode(2, OUTPUT);
    pinMode(LED, OUTPUT);
    digitalWrite(2, HIGH);
    digitalWrite(LED, LOW);
    Serial.begin(9600);
}

void loop() { 
    if(analogRead(PHOTO) < LIMIT) {
        if(whetherIncomingSignalOn == 1) {
            currentCharacter = (currentCharacter << 1) | 1;
            currentBitCount++;
        }
        else {
            whetherIncomingSignalOn = 1;
            currentBitCount = 0;
            currentCharacter = 0x0;
        }
    }
    else if(whetherIncomingSignalOn == 1){
        currentCharacter = (currentCharacter << 1);
        currentBitCount++;
    }

    if(currentBitCount == 8){
        if(currentCharacter != 0x0)
            Serial.println((char)(currentCharacter/2));
        else{
            Serial.println(0x0);
            whetherIncomingSignalOn = 0;
        }
        currentCharacter = 0x0;
        currentBitCount = 0;
    }

    delay(DELAY);
    digitalWrite(LED, LOW);
    if(Serial.available() > 0){
        switch(Serial.read()){
            case '0':
                digitalWrite(LED, LOW);
            case '1':
                digitalWrite(LED, HIGH);
        }
    }
    delay(DELAY);
}
