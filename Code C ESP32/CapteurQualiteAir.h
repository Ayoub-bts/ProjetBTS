#ifndef CAPTEUR_QUALITE_AIR_H
#define CAPTEUR_QUALITE_AIR_H

#include "Air_Quality_Sensor.h"
#include <Arduino.h>

class CapteurQualiteAir {
private:
    AirQualitySensor capteur;
    int broche;

public:
    // Constructeur
    CapteurQualiteAir(int brocheCapteur) : capteur(brocheCapteur), broche(brocheCapteur) {}

    // Méthode d'initialisation
    bool initialiser() {
        Serial.println("Attente de l'initialisation du capteur...");
        delay(20000); // Attente pour stabilisation du capteur
        if (capteur.init()) {
            Serial.println("Capteur prêt.");
            return true;
        } else {
            Serial.println("Erreur du capteur !");
            return false;
        }
    }

    // Méthode pour obtenir la qualité de l'air sous forme de texte
    String obtenirQualiteAir() {
        int qualite = capteur.slope();
        if (qualite == AirQualitySensor::FORCE_SIGNAL) {
            return "Pollution très élevée !";
        } else if (qualite == AirQualitySensor::HIGH_POLLUTION) {
            return "Pollution élevée !";
        } else if (qualite == AirQualitySensor::LOW_POLLUTION) {
            return "Faible pollution !";
        } else if (qualite == AirQualitySensor::FRESH_AIR) {
            return "Air frais.";
        } else {
            return "Qualité inconnue.";
        }
    }

    // Méthode pour obtenir la valeur brute du capteur
    int obtenirValeur() {
        return capteur.getValue();
    }
};

#endif // CAPTEUR_QUALITE_AIR_H
