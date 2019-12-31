package cn.edu.sustech.streetlight.Entity

import javax.persistence.*

@Entity
@Table(name = "light_info", schema = "light", catalog = "streetlight")
open class LightInfoEntity {
    @get:Basic
    @get:Column(name = "time", nullable = true)
    var time: java.sql.Timestamp? = null
    @get:Basic
    @get:Column(name = "device_id", nullable = true)
    var deviceId: Int? = null
    @get:Basic
    @get:Column(name = "sensor_humi", nullable = true)
    var sensorHumi: Int? = null
    @get:Basic
    @get:Column(name = "sensor_temp", nullable = true)
    var sensorTemp: Int? = null
    @get:Basic
    @get:Column(name = "sensor_ambi", nullable = true)
    var sensorAmbi: Int? = null
    @get:Basic
    @get:Column(name = "motor_speed", nullable = true)
    var motorSpeed: Int? = null
    @get:Basic
    @get:Column(name = "node_auto_mode", nullable = true)
    var nodeAutoMode: Int? = null
    @get:Basic
    @get:Column(name = "node_ambi_throttle", nullable = true)
    var nodeAmbiThrottle: Int? = null
    @Id
    @Column(name = "id")
    @GeneratedValue(strategy=GenerationType.IDENTITY)
    var id: Int? = null
    @get:Basic
    @get:Column(name = "status_ledb", nullable = true)
    var statusLedb: Int? = null
    @get:Basic
    @get:Column(name = "status_ledg", nullable = true)
    var statusLedg: Int? = null
    @get:Basic
    @get:Column(name = "status_ledr", nullable = true)
    var statusLedr: Int? = null


    override fun toString(): String =
            "Entity of type: ${javaClass.name} ( " +
                    "time = $time " +
                    "deviceId = $deviceId " +
                    "sensorHumi = $sensorHumi " +
                    "sensorTemp = $sensorTemp " +
                    "sensorAmbi = $sensorAmbi " +
                    "motorSpeed = $motorSpeed " +
                    "nodeAutoMode = $nodeAutoMode " +
                    "nodeAmbiThrottle = $nodeAmbiThrottle " +
                    "id = $id " +
                    "statusLedb = $statusLedb " +
                    "statusLedg = $statusLedg " +
                    "statusLedr = $statusLedr " +
                    ")"

    // constant value returned to avoid entity inequality to itself before and after it's update/merge
    override fun hashCode(): Int = 42

    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (javaClass != other?.javaClass) return false
        other as LightInfoEntity

        if (time != other.time) return false
        if (deviceId != other.deviceId) return false
        if (sensorHumi != other.sensorHumi) return false
        if (sensorTemp != other.sensorTemp) return false
        if (sensorAmbi != other.sensorAmbi) return false
        if (motorSpeed != other.motorSpeed) return false
        if (nodeAutoMode != other.nodeAutoMode) return false
        if (nodeAmbiThrottle != other.nodeAmbiThrottle) return false
        if (id != other.id) return false
        if (statusLedb != other.statusLedb) return false
        if (statusLedg != other.statusLedg) return false
        if (statusLedr != other.statusLedr) return false

        return true
    }

}

