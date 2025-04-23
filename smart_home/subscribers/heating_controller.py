# subscribers/heating_controller.py

from mqtt_framework.base_subscriber import BaseSubscriber
from mqtt_framework.logger import setup_logger

logger = setup_logger("heating_controller")

class HeatingControllerSubscriber(BaseSubscriber):
    def __init__(self):
        # Pass the topic and the message handling function to the parent class
        super().__init__(client_id="heating_controller", 
                         topic="home/temperature", 
                         on_message_fn=self.on_message)

    def on_message(self, client, userdata, msg):
        temperature = float(msg.payload.decode())
        logger.info(f"Received temperature: {temperature}°C")
        # Simulate heating control logic
        if temperature < 22.0:
            logger.info("Heating ON")
        else:
            logger.info("Heating OFF")

if __name__ == "__main__":
    logger.info("Starting heating controller subscriber...")
    heating_controller = HeatingControllerSubscriber()
    heating_controller.listen()  # Listen indefinitely
