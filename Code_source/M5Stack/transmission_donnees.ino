#include <lmic.h>

#include <hal/hal.h>

#include <SPI.h>



// Clés OTAA (obtenues depuis l'interface ChirpStack)

static const u1_t APPEUI[8] = { 0x00, 0x00, 0x00, 0xD0, 0x7E, 0xD5, 0xB3, 0x70 };

static const u1_t DEVEUI[8] = { 0x01, 0x03, 0x02, 0x06, 0x08, 0x09, 0x0A, 0x0B };

static const u1_t APPKEY[16] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x03, 0x01 };



// Variables pour LMIC

void os_getArtEui(u1_t *buf) { memcpy(buf, APPEUI, 8); }

void os_getDevEui(u1_t *buf) { memcpy(buf, DEVEUI, 8); }

void os_getDevKey(u1_t *buf) { memcpy(buf, APPKEY, 16); }



// Pin mapping pour LoRa

const lmic_pinmap lmic_pins = {

    .nss = 5,          // Pin NSS (Chip Select)

    .rxtx = LMIC_UNUSED_PIN,

    .rst = 4,          // Pin Reset

    .dio = {26, 27, 25} // Pins DIO0, DIO1, DIO2

};



osjob_t sendjob;



void configureLoRa() {

    LMIC.freq = 868100000;  

    LMIC_setDrTxpow(DR_SF7, 14);  

}



void do_send(osjob_t *j) {

    if (LMIC.opmode & OP_TXRXPEND) {

        Serial.println("Envoi en attente...");

    } else {

        float temperature = random(0, 40);

        int luminosite = random(10, 1000);



        uint8_t payload[6];

        payload[0] = (uint8_t)temperature;

        payload[1] = (uint8_t)((temperature - payload[0]) * 100);

        payload[2] = (luminosite >> 8) & 0xFF;

        payload[3] = luminosite & 0xFF;



        LMIC_setTxData2(1, payload, sizeof(payload), 0);

        Serial.printf("Données envoyées : Temperature=%.2f, Luminosite=%d\n", temperature, luminosite);

    }

}



void onEvent(ev_t ev) {

    Serial.print("Événement LoRaWAN : ");

    switch (ev) {

        case EV_TXCOMPLETE:

            Serial.println("Transmission terminée !");

            if (LMIC.txrxFlags & TXRX_ACK) Serial.println("ACK reçu");

            if (LMIC.dataLen) {

                Serial.print("Données reçues : ");

                Serial.write(LMIC.frame + LMIC.dataBeg, LMIC.dataLen);

                Serial.println();

            }

            os_setTimedCallback(&sendjob, os_getTime() + sec2osticks(10), do_send);

            break;

        case EV_JOINING:

            Serial.println("Tentative de rejoindre le réseau...");

            break;

        case EV_JOINED:

            Serial.println("Connecté au réseau !");

            LMIC_setLinkCheckMode(0);

            break;

        case EV_JOIN_FAILED:

            Serial.println("Échec de connexion !");

            break;

        default:

            Serial.println("Événement inconnu");

            break;

    }

}



void setup() {

    Serial.begin(115200);

    Serial.println("Initialisation du programme...");

    delay(1000);



    os_init();

    LMIC_reset();

    configureLoRa();

    Serial.println("Tentative de connexion au réseau LoRaWAN...");

    LMIC_startJoining();

}



void loop() {

    Serial.println("Boucle principale en cours...");

    os_runloop_once();

    delay(1000);

}