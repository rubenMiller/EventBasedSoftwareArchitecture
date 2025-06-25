Ip Address stuff


Set them permanently:

```bash
nmcli con add type ethernet ifname enp12s0 con-name static-enp12s0 ip4 192.168.1.100/24
nmcli con up static-enp12s0

```

Delete later to have a working LAN Port
```bash
nmcli con delete static-enp12s0

```