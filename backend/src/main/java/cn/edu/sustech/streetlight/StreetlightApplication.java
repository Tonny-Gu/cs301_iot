package cn.edu.sustech.streetlight;

import cn.edu.sustech.streetlight.MQTT.Listen;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.data.jpa.repository.config.EnableJpaAuditing;

@SpringBootApplication
@EnableJpaAuditing
public class StreetlightApplication {

	public static void main(String[] args) {
		SpringApplication.run(StreetlightApplication.class, args);
		Listen.main(null);
	}

}
