#/bin/bash

echo "-[sudo apt update && apt upgrade -y]-"
sudo apt update && apt upgrade -y

echo "-[sudo apt install -y g++ bison flex make]-"
sudo apt install g++ bison flex make

echo "-[setup completed]-"
