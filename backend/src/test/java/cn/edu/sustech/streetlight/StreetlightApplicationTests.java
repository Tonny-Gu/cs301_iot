package cn.edu.sustech.streetlight;

import cn.edu.sustech.streetlight.DAO.LightInfoRepository;
import cn.edu.sustech.streetlight.Entity.LightInfoEntity;
import org.junit.jupiter.api.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;


@RunWith(SpringRunner.class)
@SpringBootTest
class StreetlightApplicationTests {

	@Autowired
	private LightInfoRepository lightInfoRepository;
	@Test
	void contextLoads() {
		System.out.println(lightInfoRepository.findAll());
	}

	@Test
	void saveTest(){
//		LightInfoEntity lightInfoEntity=new LightInfoEntity();
//		lightInfoEntity.setDeviceId(0);
////		lightInfoEntity.setId(0);
//		lightInfoRepository.save(lightInfoEntity);
		System.out.println(lightInfoRepository.findTopByDeviceIdOrderByIdDesc(1));
	}
}
