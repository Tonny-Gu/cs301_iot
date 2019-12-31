package cn.edu.sustech.streetlight;

import cn.edu.sustech.streetlight.MQTT.Publish;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
public class OtherTest {

    @Test
    void gao() throws Exception {
        for(int i=0;i<5;i++){
            Publish.main(null);
        }
    }
}
