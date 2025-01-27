#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

class ConnexionMQTT {
private:
    const char* ssid;
    const char* password;
    const char* mqttBroker;
    const char* mqttUsername;
    const char* mqttPassword;
    int mqttPort;
    const char* mqttTopic;

    WiFiClientSecure espClient;
    PubSubClient mqttClient;

    // Certificat intégré dans la classe
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
    ConnexionMQTT(const char* wifiSsid, const char* wifiPassword,
                const char* broker, int port, const char* topic,
                const char* username = nullptr, const char* password = nullptr)
        : ssid(wifiSsid), password(wifiPassword), mqttBroker(broker),
          mqttPort(port), mqttTopic(topic), mqttUsername(username),
          mqttPassword(password), mqttClient(espClient) {}

    void setup() {
        Serial.begin(115200);
        connectToWiFi();

        // Configuration du certificat SSL/TLS
        espClient.setCACert(caCert);

        mqttClient.setServer(mqttBroker, mqttPort);
        connectToMQTTBroker();
    }

    void loop() {
        if (!mqttClient.connected()) {
            connectToMQTTBroker();
        }
        mqttClient.loop();
    }

    void publish(const char* message) {
        if (mqttClient.connected()) {
            mqttClient.publish(mqttTopic, message);
            Serial.printf("Message publié sur le topic %s : %s\n", mqttTopic, message);
        } else {
            Serial.println("Échec de publication, client non connecté.");
        }
    }

private:
    void connectToWiFi() {
        Serial.print("Connexion au réseau WiFi");
        WiFi.begin(ssid, password);

        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        Serial.println("\nConnecté au réseau WiFi");
    }

    void connectToMQTTBroker() {
        while (!mqttClient.connected()) {
            String clientId = "esp32-" + String(random(0xffff), HEX);
            Serial.printf("Connexion au Broker MQTT avec l'ID client : %s\n", clientId.c_str());

            if (mqttClient.connect(clientId.c_str(), mqttUsername, mqttPassword)) {
                Serial.println("Connecté au Broker MQTT");
            } else {
                Serial.printf("Échec de connexion au Broker MQTT, code d'erreur : %d\n", mqttClient.state());
                delay(5000);
            }
        }
    }
};
