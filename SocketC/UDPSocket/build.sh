
#!/bin/sh

gcc -c server.c client.c

if [ -f server ]; then
  rm server
fi
gcc -o server server.c

if [ -f client ]; then
  rm client
fi
gcc -o client client.c
