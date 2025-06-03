# mqtt_framework/base_publisher.py

import time
import paho.mqtt.client as mqtt
from config import BROKER, PORT, KEEPALIVE
from mqtt_framework.logger import setup_logger

class BasePublisher:
    def __init__(self, client_id):
        self.logger = setup_logger(client_id)
        self.client = mqtt.Client(client_id=client_id, protocol=mqtt.MQTTv5)
        self.client.on_connect = self.on_connect
        self.client.connect(BROKER, PORT, KEEPALIVE)
        self.client.loop_start()

    def on_connect(self, client, userdata, flags, reason_code, properties):
        self.logger.info(f"Connected (code={reason_code})")

    def publish(self, topic, get_message_fn, delay=5, retain=False):
        try:
            while True:
                message = get_message_fn()
                result = self.client.publish(topic, message, qos=1, retain=retain)
                if result.rc == mqtt.MQTT_ERR_SUCCESS:
                    self.logger.info(f"Published to '{topic}': {message}")
                else:
                    self.logger.warning("Failed to publish")
                time.sleep(delay)
        except KeyboardInterrupt:
            self.logger.info("Stopping publisher...")
            self.client.loop_stop()
            self.client.disconnect()
