#include "Pidee.h"

class ofxPidee {
public: 
	// Setup
	// =====
    static void setup() { Pidee::setup(); }

    // Button
    // ======
    static bool getButton() { return Pidee::getButton(); }

    // Dip
    // ===
    static int getDip() { return Pidee::getDip(); }
    static bool getDip( int index ) { return Pidee::getDip( index ); }

    // Led
    // ===
    static void setLedYellow( bool isOn ) { return Pidee::setLedYellow( isOn ); }
    static void setLedRed( bool isOn ) { return Pidee::setLedRed( isOn ); }
    static void setLedGreen( bool isOn ) { return Pidee::setLedGreen( isOn ); }

    // Events
    // ======
    #ifdef PIDEE_EVENTS 
    // Notifications
    static void update() { Pidee::notify(); }
    static void onButton( std::function<void(void)> func ) { Pidee::onButton( func ); }
    static void offButton( std::function<void(void)> func ) { Pidee::offButton( func ); }
    static void onDip( std::function<void(std::string)> func ) { Pidee::onDip( func ); }
    static void offDip( std::function<void(std::string)> func ) { Pidee::offDip( func ); }
    #endif
};