import paho.mqtt.client as mqtt

broker = "test.mosquitto.org"
topic = "home/temperature"

# Create MQTT v5 client with correct callback API
client = mqtt.Client(
    client_id="heating_controller",
    protocol=mqtt.MQTTv5,
    transport="tcp"
)

def on_connect(client, userdata, flags, reason_code, properties):
    print(f"[Controller] Connected with reason code: {reason_code}")
    client.subscribe(topic)
    print(f"[Controller] Subscribed to topic: {topic}")

def on_message(client, userdata, msg):
    try:
        temp = float(msg.payload.decode())
        print(f"[Controller] Received temperature: {temp:.2f}°C")
        if temp < 20:
            print("🔴 Heating ON")
        elif temp > 24:
            print("🔵 Cooling ON")
        else:
            print("🟢 Temperature is OK")
    except ValueError:
        print("[Controller] Invalid temperature format")

client.on_connect = on_connect
client.on_message = on_message

client.connect(broker)
print("[Controller] Waiting for temperature events...")
client.loop_forever()
