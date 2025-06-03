# publishers/temp_sensor.py

import random
from mqtt_framework.base_publisher import BasePublisher
from mqtt_framework.logger import setup_logger

logger = setup_logger("temp_sensor")

class TempSensorPublisher(BasePublisher):
    def __init__(self):
        super().__init__(client_id="temp_sensor")
    
    def get_message(self):
        # Simulate a random temperature between 18.0 and 26.0
        temperature = random.uniform(18.0, 26.0)
        logger.info(f"Publishing temperature: {temperature:.2f}°C")
        return f"{temperature:.2f}"

if __name__ == "__main__":
    logger.info("Starting temperature sensor publisher...")
    temp_sensor = TempSensorPublisher()
    temp_sensor.publish("home/temperature", temp_sensor.get_message, delay=5)  # Publish every 5 seconds
