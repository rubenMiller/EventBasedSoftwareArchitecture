# mqtt_framework/base_subscriber.py

import paho.mqtt.client as mqtt
from config import BROKER, PORT, KEEPALIVE
from mqtt_framework.logger import setup_logger

class BaseSubscriber:
    def __init__(self, client_id, topic, on_message_fn):
        self.logger = setup_logger(client_id)
        self.client = mqtt.Client(client_id=client_id, protocol=mqtt.MQTTv5)
        self.client.on_connect = self.on_connect
        self.client.on_message = on_message_fn
        self.topic = topic

        self.client.connect(BROKER, PORT, KEEPALIVE)
        self.client.loop_forever()

    def on_connect(self, client, userdata, flags, reason_code, properties):
        self.logger.info(f"Connected (code={reason_code}), subscribing to '{self.topic}'")
        self.client.subscribe(self.topic)
