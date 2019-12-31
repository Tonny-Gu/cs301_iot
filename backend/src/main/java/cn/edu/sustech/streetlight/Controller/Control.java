package cn.edu.sustech.streetlight.Controller;

import cn.edu.sustech.streetlight.DAO.LightInfoRepository;
import cn.edu.sustech.streetlight.Entity.LightInfoEntity;
import cn.edu.sustech.streetlight.HibernateUtil;
import cn.edu.sustech.streetlight.MQTT.Publish;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.query.Query;
import org.hibernate.query.internal.QueryImpl;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Example;
import org.springframework.web.bind.annotation.*;

import javax.websocket.server.PathParam;
import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

@RestController
@RequestMapping("/api/control")
public class Control {

    @Autowired
    private LightInfoRepository lightInfoRepository;

    @PutMapping("/mode")
    public Map changeMode(@RequestBody Map imode) {
        String mode=imode.get("mode").toString();
        if (mode == null) {
            return Map.of("ok",false);
        }
        if (mode.equals("manual")) {
            try {
                Publish.gao(-1, -1, -1, -1, 0, -1);
            } catch (MqttException e) {
                e.printStackTrace();
            }
        } else if (mode.equals("auto")) {
            try {
                Publish.gao(-1, -1, -1, -1, 1, -1);
            } catch (MqttException e) {
                e.printStackTrace();
            }
        } else {
            return Map.of("ok",false);
        }
        return Map.of("ok",true);
    }

    @GetMapping("mode")
    public Map<String, String> getCurrentMode(){
//        var light=lightInfoRepository.findOne(Example.of())
        var last=lightInfoRepository.findTopByDeviceIdOrderByIdDesc(1);
        return Map.of("mode", Objects.equals(last.getNodeAutoMode(), 1) ?"auto":"manual");
    }

    @PostMapping("/light/{id}")
    public Boolean lightOn(@PathVariable Integer id){
//        return id;
        if(id==1){
            try {
                Publish.gao(1024,1024,1024,-1,-1,-1);
            } catch (MqttException e) {
                e.printStackTrace();
                return false;
            }
            return true;
        }
        return false;
    }

    @PutMapping("/rgb")
    public Map<String,Boolean> changeRGB(@RequestBody Map<String,Integer> map){
        map.putIfAbsent("r",-1);
        map.putIfAbsent("g",-1);
        map.putIfAbsent("b",-1);
        try {
            Publish.gao(map.get("r"),map.get("g"),map.get("b"),-1,-1,-1);
        }catch (Exception e){
            return Map.of("ok",false);
        }
        return Map.of("ok",true);
    }
}
