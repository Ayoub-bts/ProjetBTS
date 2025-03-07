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
    const char* nomEsp;

    // Client sécurisé pour gérer la connexion TLS avec le broker MQTT
    WiFiClientSecure espClient;
    // Client MQTT basé sur le client sécurisé
    PubSubClient mqttClient;

    // Certificat SSL/TLS pour sécuriser la connexion au broker MQTT
    const char *ca_cert = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh
MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3
d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD
QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT
MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j
b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG
9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB
CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97
nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt
43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P
T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4
gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO
BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR
TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw
DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr
hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg
06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF
PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls
YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk
CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=
-----END CERTIFICATE-----
)EOF";

public:
    // Constructeur de la classe pour initialiser les variables de connexion
    ConnexionMQTT(const char* wifiSsid, const char* wifiPassword,
                  const char* broker, int port, const char* topic,
                  const char* espName, // Ajout du paramètre pour le nom de l'ESP
                  const char* username = nullptr, const char* password = nullptr)
        : ssid(wifiSsid), password(wifiPassword), mqttBroker(broker),
          mqttPort(port), mqttTopic(topic), nomEsp(espName), // Initialisation du nom de l'ESP
          mqttUsername(username), mqttPassword(password), mqttClient(espClient) {}

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
            // Utilisation du nom personnalisé de l'ESP comme identifiant client
            String clientId = String(nomEsp);
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
