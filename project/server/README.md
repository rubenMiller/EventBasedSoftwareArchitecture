# Set up for ip address

Just running the bash script and using a LAN-cable is not sufficient, the ip set-up of the 'server' needs to be done as well.
In the bash script there is already a (very) temporary solution which worked for 1-5 minutes for me.

Below is a permanent solution and how to undo it.


Set permanently:

```bash
nmcli con add type ethernet ifname enp12s0 con-name static-enp12s0 ip4 192.168.1.100/24
nmcli con up static-enp12s0

```

Delete later to have a working LAN Port
```bash
nmcli con delete static-enp12s0

```