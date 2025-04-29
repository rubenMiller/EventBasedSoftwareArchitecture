systemctl enable mosquitto
systemctl start mosquitto
systemctl status mosquitto

# do this only, if the file does not exist
if [ ! -f /etc/mosquitto/conf.d/default.conf ]; then
  echo "Creating default configuration file for Mosquitto"
  echo "listener 1883 \n allow_anonymous true" | touch /etc/mosquitto/conf.d/default.conf
fi

