# figure out if I have an unread gmail IM or email by checking the title of chrome
while sleep 1; do
  if wmctrl -l | grep -q 'says...'; then
    echo IM
    echo 'rbh' > /dev/ttyUSB0
  else
    if wmctrl -l | grep -q 'Inbox ('; then
      echo email
      echo 'ybf' > /dev/ttyUSB0
    else
      echo all systems nominal
      echo 'gfh' > /dev/ttyUSB0
    fi
  fi
done
