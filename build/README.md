# INSTALLATION
## Debian/Ubuntu
1. Update package dependencies `sudo apt-get update`
1. Install passivedns `sudo dpkg -i passivedns-*.deb`
1. Install dependencies `sudo apt-get install -f`
1. Set interface variable in `/etc/passivedns/passivedns.conf`
1. Reload **systemd** `sudo systemctl daemon-reload`
1. Add passivedns to autorun `sudo systemctl enable passivedns`
1. Start/Stop/Reload/Status of passivedns `sudo systemctl {start/stop/restart/status} passivedns`

## Centos/RHEL/Fedora
:TODO Add installation