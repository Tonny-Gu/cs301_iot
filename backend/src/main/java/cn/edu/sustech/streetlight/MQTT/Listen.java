package cn.edu.sustech.streetlight.MQTT;

import cn.edu.sustech.streetlight.DAO.LightInfoRepository;
import cn.edu.sustech.streetlight.Entity.LightInfoEntity;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import javax.annotation.PostConstruct;
import java.sql.Time;
import java.sql.Timestamp;
import java.util.HashMap;
import java.util.Map;

@Component
public class Listen {

    @Autowired
    private LightInfoRepository repository;

    private static LightInfoRepository lightInfoRepository;

    @PostConstruct
    public void init(){
        lightInfoRepository=repository;
    }

    public static void main(String[] args) {
        String topic        = "/node0/pub";
//        String content      = "Message from MqttPublishSample";
        int qos             = 2;
        String broker       = "tcp://47.106.254.82:10010";
        String clientId     = "JavaServer";
        MemoryPersistence persistence = new MemoryPersistence();
//        MqttClient client=new MqttClient();
        MqttClient sampleClient=null;
        try{
            sampleClient = new MqttClient(broker, clientId, persistence);
            MqttConnectOptions connOpts = new MqttConnectOptions();
            connOpts.setCleanSession(true);
            System.out.println("Connecting to broker: "+broker);
            sampleClient.connect(connOpts);
            System.out.println("Connected");
//            System.out.println("Publishing message: "+content);
//            MqttMessage message = new MqttMessage(content.getBytes());
//            message.setQos(qos);
//            sampleClient.publish(topic, message);
//            System.out.println("Message published")
            sampleClient.subscribe(topic,(t, msg) -> {
                byte[] payload = msg.getPayload();
                // ... payload handling omitted
//                System.out.print("topic: " + t);

                HashMap<String,Object> result = new ObjectMapper().readValue(msg.toString(), HashMap.class);
                System.out.println(result);
                LightInfoEntity lightInfo=new LightInfoEntity();
                lightInfo.setSensorHumi((Integer) ((Map) result.get("sensor")).get("humi"));
                lightInfo.setSensorAmbi((Integer) ((Map) result.get("sensor")).get("ambi"));
                lightInfo.setSensorTemp((Integer) ((Map) result.get("sensor")).get("temp"));
                lightInfo.setStatusLedb((Integer) ((Map) ((Map) result.get("status")).get("led")).get("b"));
                lightInfo.setStatusLedg((Integer) ((Map) ((Map) result.get("status")).get("led")).get("g"));
                lightInfo.setStatusLedr((Integer) ((Map) ((Map) result.get("status")).get("led")).get("r"));
                lightInfo.setMotorSpeed((Integer) ((Map) ((Map) result.get("status")).get("motor")).get("speed"));
                lightInfo.setDeviceId(1);
                lightInfo.setNodeAutoMode(((Integer) ((Map) ((Map) result.get("status")).get("node")).get("auto_mode")));
                lightInfo.setNodeAmbiThrottle(((Integer) ((Map) ((Map) result.get("status")).get("node")).get("ambi_throttle")));
                Integer seconds= (Integer) result.get("timestamp");
                lightInfo.setTime(new Timestamp((long) seconds * 1000));
                System.out.println(lightInfo);
                lightInfoRepository.save(lightInfo);
//                System.out.println();
            });
        }catch (Exception e){
            e.printStackTrace();
        }
    }
}
