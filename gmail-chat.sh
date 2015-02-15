# figure out if I have an unread gmail IM by checking the title of chrome
while sleep 1; do
  if wmctrl -l | grep -q 'says...'; then
    echo good
    echo 'y' > /dev/ttyUSB1
  else
    echo bad
    echo 'n' > /dev/ttyUSB1
  fi
done
