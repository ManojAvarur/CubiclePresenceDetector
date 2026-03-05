class UltraSonicSensor{
    private:
        const double SOUND_VELOCITY = 0.034;
        const double CM_TO_INCH = 0.393701;

        int TRIGGER_PIN, ECHO_PIN;
        long DURATION;

        unsigned long PREVIOUS_MILLIS = 0;
        const long INTERVAL = 500;  

    public:
        UltraSonicSensor* getCurrentValue(){
            unsigned long currentMillis = millis();

            // Wait for interval before sending out new sound wave
            if (currentMillis - PREVIOUS_MILLIS < INTERVAL) {
                return this;
            }

            PREVIOUS_MILLIS = currentMillis;

            // Clears the trigPin
            digitalWrite(this->TRIGGER_PIN, LOW);
            delayMicroseconds(2);

            // Sets the trigPin on HIGH state for 10 micro seconds
            digitalWrite(this->TRIGGER_PIN, HIGH);
            delayMicroseconds(10);
            digitalWrite(this->TRIGGER_PIN, LOW);

            // Reads the echoPin, returns the sound wave travel time in microseconds
            this->DURATION = pulseIn(this->ECHO_PIN, HIGH);

            // Returns current UltraSonicSensor instance
            return this;
        }

        float inCentimeter(){
            return this->DURATION * SOUND_VELOCITY / 2;
        }

        float inInches(){
            return (this->inCentimeter() * CM_TO_INCH);
        }
    
    UltraSonicSensor(int triggerPin, int echoPin){
        this->TRIGGER_PIN = triggerPin;
        this->ECHO_PIN = echoPin;

        pinMode(this->TRIGGER_PIN, OUTPUT);
        pinMode(this->ECHO_PIN, INPUT);
    }
};