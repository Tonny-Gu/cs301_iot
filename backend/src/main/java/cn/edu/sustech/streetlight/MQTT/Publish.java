package cn.edu.sustech.streetlight.MQTT;

import org.eclipse.paho.client.mqttv3.*;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

import java.util.UUID;
import java.util.concurrent.CountDownLatch;

public class Publish {
    public static void main(String[] args) throws Exception {
        gao(1024,0,0,-1,-1,-1);
    }

    public static void gao(int r, int g, int b, int motor_speed, int node_auto_mode, int node_ambi_throttle) throws MqttException {
        String str = "{\n" +
                "    \"cmd\": {\n" +
                "        \"led\": {\n" +
                "            \"r\":" + r + ",\n" +
                "            \"g\": " + g + ",\n" +
                "            \"b\": " + b + "\n" +
                "        },\n" +
                "        \"motor\": {\n" +
                "            \"speed\": " + motor_speed + "\n" +
                "        },\n" +
                "        \"node\": {\n" +
                "            \"auto_mode\": " + node_auto_mode + ",\n" +
                "            \"ambi_throttle\": " + node_ambi_throttle + "\n" +
                "        }\n" +
                "    }\n" +
                "}";

        String publisherId = UUID.randomUUID().toString();
        String topic = "/node0/sub";
        int qos = 2;
        String broker = "tcp://47.106.254.82:10010";
        MemoryPersistence persistence = new MemoryPersistence();
        MqttClient publisher = null;
        publisher = new MqttClient(broker, publisherId, persistence);
        MqttConnectOptions connOpts = new MqttConnectOptions();
        connOpts.setCleanSession(true);
        MqttMessage mqttMessage = new MqttMessage();
        mqttMessage.setQos(qos);
        mqttMessage.setPayload(str.getBytes());
        publisher.connect();
        publisher.publish(topic, mqttMessage);
        publisher.disconnect();
    }
}
