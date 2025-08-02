#!/bin/bash

echo "Stopping services..."

# Stop services
sudo systemctl stop ccpd
sudo pkill -9 ccpd # kill ccpd, it sometime hanging and waste CPU
sudo systemctl stop cups

# Force kill stuck captmon2 if needed
# Some time `captmon2` process exist and no auto terminate and waste CPU
if pgrep captmon2 > /dev/null
then
    echo "Force killing captmon2..."
    sudo pkill -9 captmon2
fi

# Print status
echo -e "\n\ncups: "
sudo systemctl status cups --no-pager

echo -e  "\n\nccpd: "
sudo systemctl status ccpd --no-pager

# Enable old USB scheme
echo "\n\nold Usb scheme:"
echo Y | sudo tee /sys/module/usbcore/parameters/old_scheme_first

# Restart services
echo "\n\nStarting services..."
sudo systemctl start cups
sudo systemctl start ccpd

# Check status again
echo -e "\n\ncups: "
sudo systemctl status cups --no-pager

echo -e "\n\nccpd: "
sudo systemctl status ccpd --no-pager

