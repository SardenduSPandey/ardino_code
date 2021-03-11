\\Establish the connectivity between ESP23 and AWS

#include <WiFiClientSecure.h>
#include <PubSubClient.h>

const char* ssid = "iot";      \\WIFI id
const char* password = "12345678";      \\WIFI password
const char* awsEndpoint = "ar3ml2r09xv1s-ats.iot.us-west-2.amazonaws.com";  \\Broker name


const char* certificate_pem_crt = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDWTCCAkGgAwIBAgIUHorlNg66TPjrAHJEQ77+mSgWtQ0wDQYJKoZIhvcNAQEL\n" \
"BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n" \
"SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIxMDEyNTA2MTYw\n" \
"OFoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n" \
"ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALuZGTmBReC0QFznx8rJ\n" \
"3Y9ioe90gdC+3T9Ka2iO0tM7ejOOhfNrkbYp+TwD0dQcncv3VgtDL4gLMBeg8bTk\n" \
"lC84C5Wk4qdjgP5t0Xts+rego4XoZG7bJzXBt3/n+KLj8g7JQ6M8tsw/oiuMV1zK\n" \
"T7EQXZPGC14WAap7Bx1drGBSdYvLG2AgZNsZscoN3ps/zoRxE19prc4YxNX2ApaB\n" \
"HzoZZNCUZ6TcsVhbZzPWo1t4p2hLEy7hGvetfn6HTRgCNpmaMffz8/waUiJUqSEG\n" \
"UrEcqUxWBPdXlxtPNzpxpQyb2/ZJjU2ZzzvZCu0yX4yrY9Iir590EI5Jey1Lb0dc\n" \
"bisCAwEAAaNgMF4wHwYDVR0jBBgwFoAUV7HYOVwdqKO5vq0PO4OXZ+KIDIowHQYD\n" \
"VR0OBBYEFKoQthWymDDySMRIJfK2d6nnDMWJMAwGA1UdEwEB/wQCMAAwDgYDVR0P\n" \
"AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQBcQoJE/+u2diF7BLQM443afrnP\n" \
"t3/OHS0LtAyYbU48rlepVM5A4JOtnnaW1enoy/wTVNWIVFuseOTIh9j796c3M4I+\n" \
"tHpmrJZF6zunCfv7nGFqEMMb+wu4cgvNHHyvDFWGRz8twisAni92O4X3dWMNx+kJ\n" \
"bBLsudbVn1OwgseL+vpbCUoTCRzAEbGZvuEhSez6I1xsY5uzJIgd2cPedLblowlb\n" \
"vgqQuHOCLoCDeze4Ke0KbQyplsjTDn6gjdVlGG8inXHss2j0rCTBSCI1IYWjLfwn\n" \
"UnXw79v4cVIivqkDJ2Aa3JJU6bqvkPQtaYf7h6udJ15vANzxDFzMLgdt9ksF\n" \
"-----END CERTIFICATE-----\n";

const char* private_pem_key = \
"-----BEGIN RSA PRIVATE KEY-----\n" \
"MIIEpAIBAAKCAQEAu5kZOYFF4LRAXOfHysndj2Kh73SB0L7dP0praI7S0zt6M46F\n" \
"82uRtin5PAPR1Bydy/dWC0MviAswF6DxtOSULzgLlaTip2OA/m3Re2z6t6Cjhehk\n" \
"btsnNcG3f+f4ouPyDslDozy2zD+iK4xXXMpPsRBdk8YLXhYBqnsHHV2sYFJ1i8sb\n" \
"YCBk2xmxyg3emz/OhHETX2mtzhjE1fYCloEfOhlk0JRnpNyxWFtnM9ajW3inaEsT\n" \
"LuEa961+fodNGAI2mZox9/Pz/BpSIlSpIQZSsRypTFYE91eXG083OnGlDJvb9kmN\n" \
"TZnPO9kK7TJfjKtj0iKvn3QQjkl7LUtvR1xuKwIDAQABAoIBAQCI1bxTeJq6s1+7\n" \
"JIlTvniwjLYnjmjeFUoWTzcXNg5LazfQgWXtTwoiwGz+PJ8Bw7nJu+h0IJZ7+gUj\n" \
"Rw7m7k+0PYIdrf5xMCA39Wx2ReB+rlp4YzFWtt3b1Sf+0PpH/lJiPKXsXG3Nf6DP\n" \
"ePeEREFqmtBW6H8EKrMeYcynu9rvChX6zckcWG4jOfqrNfhebVPM5Q9ZX24TfOnZ\n" \
"BNhZ7N2qTtob1kfTAkUG3OyK3vSmC3oHh7Ss+aMvId6t/Sp3IUA14DLUbQIQLlWL\n" \
"sqb4I9CZAeGOPyz8C2O0E1onvlT9HoVdbP4fw19yJ8kupFi1PYX+M4t3c912faY3\n" \
"qBMuovHBAoGBAOxuX9AL+Ts2+g2r4wn73uvl37w2mrWso5smdDUk1tKHtBminBEC\n" \
"tJsiwPjYIpEVov6x3MB4poDBawWE8yFBc0bDEFYz4zZGigvnt1umDJahDP9Imt19\n" \
"2Bq4U1D2Y+kzcf3XLqQnMg9jef7R+8/5hrrpDVWbT2dF3tZQbuYWyhTLAoGBAMsg\n" \
"BecPfVfWfrsG36ZKqLb+bFg7xzZdfwJruJy2PoPyWfWoKl6bHoRBRzD4q5izq+Bh\n" \
"jPhvBeOib8pLzLtLbckhEPKilFnAVhndib8w2pLObeSnkU0a7o/QMHBwD51sHw19\n" \
"Ubgr8KQJn3LO5agAqHlmTcWI6QvfTUmo/mM/t0AhAoGAButcBnyzOJZtTwUeyeYD\n" \
"Kig6GgoHERYSW7IOaJfBabvq+20U4DKSEpA70YyRxmk5sfaGnWNqjA4dEbZIX0rJ\n" \
"EuMWkU9HcQkzdRG8/gOoDqh79uSrE5xhPLb0SURMvEBzL5iils9G2chxg5GlqvqE\n" \
"hOfZKg43jrAuy1rjQ/yawW0CgYEAjv/6Z9LV0VLmYVDTfsSsxjeTmwJqmvFziwa/\n" \
"L0R1+npRrso3GedmsoEqV2WZmKVU6WCD2BqBMOKYhPicJ3dQ0PoAbnDas9zeQNNg\n" \
"OENyfUvqvcDiYEAHlyNgFqgttgv6SIrjTx9QCIvlvvO9ZmsgMGc/dUOPnZYVWTgp\n" \
"70FaB0ECgYBheeFzVYHjrnI4qntv+yEKtDaedzFPrUbWagG2GeroXqgRRT3qeqQh\n" \
"0HaiKhOs+uE/favwwrWJpXh2s6DM94vSM/rsTmMuLNrEt7gKbwxXl4PxE4dTCgSh\n" \
"0w0UEzb15VdZfvV6lwqDBS1JAf6m2HnX8OKiqxSMnF2ge6uevjaQFg==\n" \
"-----END RSA PRIVATE KEY-----\n";


const char* rootCA = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n" \
"ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n" \
"b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n" \
"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n" \
"b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n" \
"ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n" \
"9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n" \
"IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n" \
"VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n" \
"93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n" \
"jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n" \
"AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n" \
"A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n" \
"U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n" \
"N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n" \
"o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n" \
"5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n" \
"rqXRfboQnoZsG4q5WTP468SQvvG5\n" \
"-----END CERTIFICATE-----\n";

WiFiClientSecure wiFiClient;
void msgReceived(char* topic, byte* payload, unsigned int len);
PubSubClient pubSubClient(awsEndpoint, 8883, msgReceived, wiFiClient);

void setup() {
  Serial.begin(115200); delay(50); Serial.println();
  Serial.println("ESP32 AWS IoT");
  Serial.print("Connecting to "); Serial.print(ssid);
  WiFi.begin(ssid, password);
  WiFi.waitForConnectResult();
  Serial.print(", WiFi connected, IP address: "); Serial.println(WiFi.localIP());

  wiFiClient.setCACert(rootCA);
  wiFiClient.setCertificate(certificate_pem_crt);
  wiFiClient.setPrivateKey(private_pem_key);
}

unsigned long lastPublish;
int msgCount;

void loop() {

  pubSubCheckConnect();

 
    String msg = String("Hello from Shubham: ")+5;
    boolean rc = pubSubClient.publish("outTopic", msg.c_str());
    Serial.print("Published, msg=");
    Serial.println(msg);
    delay(10000);

}

void msgReceived(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received on "); 
  Serial.print(topic);
  Serial.print(": ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void pubSubCheckConnect() {
  if ( ! pubSubClient.connected()) {
    Serial.print("PubSubClient connecting to: "); Serial.print(awsEndpoint);
    while ( ! pubSubClient.connected()) {
      Serial.print(".");
      pubSubClient.connect("esp32");
      delay(1000);
    }
    Serial.println(" connected");
    pubSubClient.subscribe("inTopic");
  }
  pubSubClient.loop();
}
