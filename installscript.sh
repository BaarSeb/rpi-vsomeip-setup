#boost setup
sudo apt-get install libboost-all-dev
	
# vsomeip setup
cd ~
git clone https://github.com/GENIVI/vsomeip.git
cd vsomeip
wget -O 0001-Support-boost-v1.66.patch.zip https://github.com/GENIVI/vsomeip/files/2244890/0001-Support-boost-v1.66.patch.zip
unzip 0001-Support-boost-v1.66.patch.zip
git apply 0001-Support-boost-v1.66.patch
mkdir build
cd build
cmake -DENABLE_SIGNAL_HANDLING=1 ..
make

# scapy download
cd ~
git clone https://github.com/secdev/scapy

# add user with reduced rights
sudo useradd student
