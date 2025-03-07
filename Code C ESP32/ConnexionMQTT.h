#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// Définition d'une classe pour gérer la connexion MQTT via un ESP32
class ConnexionMQTT {
private:
    // Variables pour stocker les informations de connexion WiFi et MQTT
    const char* ssid;
    const char* password;
    const char* mqttBroker;
    const char* mqttUsername;
    const char* mqttPassword;
    int mqttPort;
    const char* mqttTopic;

    // Client sécurisé pour gérer la connexion TLS avec le broker MQTT
    WiFiClientSecure espClient;
    // Client MQTT basé sur le client sécurisé
    PubSubClient mqttClient;

    // Certificat SSL/TLS pour sécuriser la connexion au broker MQTT
    const char *ca_cert = R"EOF(
    -----BEGIN CERTIFICATE-----
    (Certificat SSL/TLS du broker MQTT)
    -----END CERTIFICATE-----
    )EOF";

public:
    // Constructeur de la classe pour initialiser les variables de connexion
    ConnexionMQTT(const char* wifiSsid, const char* wifiPassword,
                const char* broker, int port, const char* topic,
                const char* username = nullptr, const char* password = nullptr)
        : ssid(wifiSsid), password(wifiPassword), mqttBroker(broker),
          mqttPort(port), mqttTopic(topic), mqttUsername(username),
          mqttPassword(password), mqttClient(espClient) {}

    // Méthode d'initialisation de la connexion WiFi et MQTT
    void setup() {
        Serial.begin(115200);  // Initialisation de la communication série
        connectToWiFi();       // Connexion au réseau WiFi

        // Configuration du certificat SSL/TLS pour sécuriser la connexion MQTT
        espClient.setCACert(ca_cert);

        // Configuration du serveur MQTT
        mqttClient.setServer(mqttBroker, mqttPort);
        connectToMQTTBroker(); // Connexion au broker MQTT
    }

    // Méthode à exécuter en boucle pour maintenir la connexion MQTT active
    void loop() {
        if (!mqttClient.connected()) {
            connectToMQTTBroker(); // Reconnexion au broker si déconnecté
        }
        mqttClient.loop(); // Maintien de la communication MQTT
    }

    // Méthode pour publier un message sur le topic MQTT
    void publish(const char* message) {
        if (mqttClient.connected()) {
            mqttClient.publish(mqttTopic, message);
            Serial.printf("Message publié sur le topic %s : %s\n", mqttTopic, message);
        } else {
            Serial.println("Échec de publication, client non connecté.");
        }
    }

private:
    // Méthode pour se connecter au réseau WiFi
    void connectToWiFi() {
        Serial.print("Connexion au réseau WiFi");
        WiFi.begin(ssid, password); // Démarrage de la connexion WiFi

        // Attente de la connexion
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        Serial.println("\nConnecté au réseau WiFi");
    }

    // Méthode pour se connecter au broker MQTT
    void connectToMQTTBroker() {
        while (!mqttClient.connected()) {
            // Génération d'un identifiant client unique pour la connexion
            String clientId = "esp32-" + String(random(0xffff), HEX);
            Serial.printf("Connexion au Broker MQTT avec l'ID client : %s\n", clientId.c_str());

            // Tentative de connexion au broker avec les identifiants
            if (mqttClient.connect(clientId.c_str(), mqttUsername, mqttPassword)) {
                Serial.println("Connecté au Broker MQTT");
            } else {
                Serial.printf("Échec de connexion au Broker MQTT, code d'erreur : %d\n", mqttClient.state());
                delay(5000); // Attente avant une nouvelle tentative de connexion
            }
        }
    }
};
