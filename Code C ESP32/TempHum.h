#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <DHT_U.h>

// Classe pour gérer le capteur DHT
class DHTSensor {
private:
    int pin;        // Broche connectée au capteur
    DHT dht;        // Instance de la bibliothèque DHT

public:
    // Constructeur
    DHTSensor(int sensorPin, int sensorType) : pin(sensorPin), dht(sensorPin, sensorType) {}

    // Méthode pour initialiser le capteur
    void begin() {
        dht.begin();
        Serial.println("DHT : Initialisation terminée");
    }

    // Méthode pour lire l'humidité
    float getHumidity() {
        float humidity = dht.readHumidity();
        if (isnan(humidity)) {
            Serial.println("Erreur de lecture de l'humidité !");
            return -1.0; // Retourne une valeur négative en cas d'erreur
        }
        return humidity;
    }

    // Méthode pour lire la température
    float getTemperature() {
        float temperature = dht.readTemperature();
        if (isnan(temperature)) {
            Serial.println("Erreur de lecture de la température !");
            return -1.0; // Retourne une valeur négative en cas d'erreur
        }
        return temperature;
    }
};

#endif // DHT_SENSOR_H
