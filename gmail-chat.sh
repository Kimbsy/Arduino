# figure out if I have an unread gmail IM or email by checking the title of chrome

# define colors
RED='\033[0;31m'
GRE='\033[0;32m'
YEL='\033[0;33m'
NC='\033[0m'

while sleep 1; do
  if wmctrl -l | grep -q 'says...'; then
    printf "${RED}IM${NC}\n"
    echo 'rbh' > /dev/ttyUSB0
  else
    if wmctrl -l | grep -q 'Inbox ('; then
      printf "${YEL}email${NC}\n"
      echo 'ybf' > /dev/ttyUSB0
    else
      printf "${GRE}all systems nominal${NC}\n"
      echo 'gfh' > /dev/ttyUSB0
    fi
  fi
done
