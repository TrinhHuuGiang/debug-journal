#!/bin/bash

echo -e "----------------------\n"
# sudo password before run background `x11vnc`
sudo -v


echo -e "----------------------\n"
# `&` make x11vnc run in background, main terminal continue to end
# `setsid` fork new process
# `nice` with sudo help set priority -2 (higher than normal app (0) and some system service (-1))
#    `nice` can set from -20 -> 19 , more higher more waiting
# `>` stdout to /dev/null
# `2>` stderr send to same end point stdout

sudo setsid nice -n -20 x11vnc -display :0 -forever -viewonly -noremote -multiptr -cursor arrow -scale 800x450 -noipv6 -wireframe red,2,0,128+8+8+8,all,0.15+0.30+5.0+0.125 -nowirecopyrect -noscrollcopyrect -noxdamage -wait 50 -defer 51 -nossl -vencrypt never > /dev/null 2>&1 &





# wait 5s prevent race condition make x11vnc not started
echo -e "---------DONE---------\n"
for ((i=5; i>=1; --i)); do
    echo -ne "\rwait $i   "   #  space to clean old long values
    sleep 0.5
done
echo ""   # endl


