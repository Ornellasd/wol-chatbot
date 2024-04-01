Wake-on-Lan Telegram Bot

I started this project as I currently have a Mac Mini home server/frontend media pc thing that I don't always want on. One day, while killing time at the library, I wanted to work on my docker servers remotely and forgot I had suspended the computer at some point in the day. Thinking of a solution to this quickly led me to my stash of unused esp8266/esp32's and was quickly determined that using a chat bot of sorts would be an easy and safe way to do this remotely.

This is currently a WIP

Todos:
- add suspend functionality
- add esp32 support
- utilize mqtt with mosquitto server on aws in place of telegram altogher(or in tandem perhaps)
- AP mode on initialization so WIFI credentials aren't meccesiated in config for first run(?)
- add OTA support(?)
