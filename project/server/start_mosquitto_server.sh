#!/bin/bash

# Enable and start Mosquitto
sudo systemctl enable mosquitto
sudo systemctl start mosquitto

# Create default config if not exists
CONFIG_FILE="/etc/mosquitto/conf.d/default.conf"
if [ ! -f "$CONFIG_FILE" ]; then
  echo "Creating default configuration file for Mosquitto"
  echo -e "listener 1883\nallow_anonymous true" | sudo tee "$CONFIG_FILE"
  sudo systemctl restart mosquitto
fi

# Check status
sudo systemctl status mosquitto


# give temporary static ip to my ethernet port
# my system may overwrite this regularly
sudo ip addr add 192.168.1.100/24 dev enp12s0
sudo ip link set enp12s0 up
