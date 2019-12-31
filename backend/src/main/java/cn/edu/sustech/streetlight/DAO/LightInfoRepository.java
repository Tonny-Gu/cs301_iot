package cn.edu.sustech.streetlight.DAO;


import cn.edu.sustech.streetlight.Entity.LightInfoEntity;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;

import java.sql.Timestamp;
import java.util.Collection;
import java.util.List;

@Repository
public interface LightInfoRepository extends JpaRepository<LightInfoEntity,Long> {

    LightInfoEntity findTopByDeviceIdOrderByIdDesc(Integer deviceId);

    @Query(
            value = "select t.light from (" +
                    "   select cast(extract(epoch from time) / ?3 as integer) as time_sample," +
                    "          avg(sensor_ambi) as light " +
                    "   from light.light_info " +
                    "   where ?1 < time and time <= ?2 " +
                    "   group by time_sample) as t " +
                    "order by t.time_sample",
            nativeQuery = true
    )
    Collection<Double> findLightSamples(Timestamp from, Timestamp to, long interval);
}
