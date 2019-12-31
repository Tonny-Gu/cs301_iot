package cn.edu.sustech.streetlight;



import org.eclipse.paho.client.mqttv3.IMqttClient;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;

import java.net.URISyntaxException;
import java.util.ConcurrentModificationException;
import java.util.UUID;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.SubmissionPublisher;
import java.util.concurrent.TimeUnit;

public class MqttPublishSample {

    public static void main(String[] args) throws Exception {
        String publisherId = UUID.randomUUID().toString();
        IMqttClient publisher = new MqttClient("tcp://10.20.71.60:1883",publisherId);

        MqttConnectOptions options = new MqttConnectOptions();
        options.setAutomaticReconnect(true);
        options.setCleanSession(true);
        options.setConnectionTimeout(10);
        publisher.connect();

        CountDownLatch receivedSignal = new CountDownLatch(10);

        publisher.subscribe("foo", (topic, msg) -> {
            byte[] payload = msg.getPayload();
            // ... payload handling omitted
            System.out.print("topic: "+topic);
            System.out.print(" message: "+msg);
            System.out.println();
            receivedSignal.countDown();
        });
        receivedSignal.await(10,TimeUnit.SECONDS);
        publisher.disconnect();
        System.out.println("do other things");

//        publisher.subscribe("foo2", (topic, msg) -> {
//            byte[] payload = msg.getPayload();
//            // ... payload handling omitted
//            System.out.print("topic: "+topic);
//            System.out.print("message: "+msg);
//            System.out.println();
//            receivedSignal.countDown();
//        });
    }
}
