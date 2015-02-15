# figure out if I have an unread gmail IM by checking the title of chrome
while sleep 1; do
  if wmctrl -l | grep -q 'says...'; then
    echo 'y' > /dev/ttyUSB0
  else
    echo 'n' > /dev/ttyUSB0
  fi
done