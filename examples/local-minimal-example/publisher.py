import time
import random
import paho.mqtt.client as mqtt

broker = "test.mosquitto.org"
topic = "home/temperature"

# Use MQTT version 5 and new callback API
client = mqtt.Client(
    client_id="temp_sensor",
    protocol=mqtt.MQTTv5,
    transport="tcp"
)

def on_connect(client, userdata, flags, reason_code, properties):
    print(f"[Sensor] Connected with reason code: {reason_code}")

client.on_connect = on_connect

client.connect(broker)
client.loop_start()

try:
    while True:
        temp = random.uniform(18.0, 26.0)
        message = f"{temp:.2f}"
        result = client.publish(topic, message)
        status = result.rc
        if status == mqtt.MQTT_ERR_SUCCESS:
            print(f"[Sensor] Published temperature: {message}°C")
        else:
            print("[Sensor] Failed to publish message")
        time.sleep(5)
except KeyboardInterrupt:
    print("\n[Sensor] Stopping...")
    client.loop_stop()
    client.disconnect()
