#include <WiFiMulti.h>

class WifiService {
public:
    WifiService();
    void retryConnectUntilSuccess();
    void testConnection(int pin);

private:
    WiFiMulti* wifiMulti;
};