package cn.edu.sustech.streetlight.Controller;

import cn.edu.sustech.streetlight.DAO.LightInfoRepository;
import cn.edu.sustech.streetlight.Entity.LightInfoEntity;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Example;
import org.springframework.data.domain.ExampleMatcher;
import org.springframework.web.bind.annotation.*;

import java.sql.Timestamp;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

@RestController
@RequestMapping("/api/query")
public class QueryController {

    @Autowired
    private LightInfoRepository lightInfoRepository;

//    @GetMapping("/illuminance")
//    public String queryLight(@RequestParam("from") long ifrom,
//                             @RequestParam(value = "to", defaultValue = "-1") long to,
//                             @RequestParam(value = "interval", defaultValue = "3600") long interval) {
////        long from= ((Integer) request.get("from")).longValue()*1000;
////        long to= Long.parseLong(request.getOrDefault("to",/1000).toString())*1000;
////        long interval= ((Integer) request.getOrDefault("interval",3600)).longValue()*1000;
//        long from = 0;
////        if(ifrom instanceof Long) {
//        from = (Long) ifrom * 1000;
////        }
//        interval = interval * 1000;
//        if (to == -1) {
//            to = System.currentTimeMillis();
//        }
//        List<LightInfoEntity> list = lightInfoRepository.findAll();
//        long finalFrom = from;
//        long finalTo = to;
//        var tmp = list.stream()
//                .filter(x -> Objects.requireNonNull(x.getTime()).getTime() >= finalFrom && x.getTime().getTime() <= finalTo)
//                .sorted((a, b) -> Integer.compare(b.getId(), a.getId()))
//                .collect(Collectors.toList());
//        if (tmp.size() == 0) {
//            return "[]";
//        }
//        var min_time = tmp.get(0).getTime().getTime();
//        long finalInterval = interval;
//        return tmp.stream().filter(x -> (x.getTime().getTime() - min_time) % finalInterval == 0).flatMap(
//                x -> Stream.of(x.getTime().getTime() / 1000, x.getSensorAmbi())
//        ).collect(Collectors.toList()).toString();
//    }

    @GetMapping("/illuminance")
    public Collection<Double> queryIlluminance(@RequestParam("from") long from,
                             @RequestParam(value = "to", defaultValue = "-1") long to,
                             @RequestParam(value = "interval", defaultValue = "3600") long interval) {
        from *= 1000;
        if (to == -1) {
            to = System.currentTimeMillis();
        } else {
            to *= 1000;
        }
        return lightInfoRepository.findLightSamples(new Timestamp(from), new Timestamp(to), interval);
    }

    @GetMapping("/rgb")
    public Map<String, Integer> queryRGB() {
        var last = lightInfoRepository.findTopByDeviceIdOrderByIdDesc(1);
        HashMap<String, Integer> hashMap = new HashMap<>();
        hashMap.put("r", last.getStatusLedr());
        hashMap.put("g", last.getStatusLedg());
        hashMap.put("b", last.getStatusLedb());
        return hashMap;
    }

    @GetMapping("/latest_lux")
    public Map<String, Long> queryLatestLux() {
        var last = lightInfoRepository.findTopByDeviceIdOrderByIdDesc(1);
        return Map.of(
                "lux", (long) (last.getSensorAmbi() / 1024.0 * 100),
                "timestamp", last.getTime().getTime() / 1000
        );
//        return Map.of("lux",last.getSensorAmbi());
    }
}
