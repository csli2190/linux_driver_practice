# Replace kernel to linux-6.0.8 (ref : https://phoenixnap.com/kb/build-linux-kernel)

1. download linux source code
  $ wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.0.8.tar.xz

2. install required packages
  $ sudo apt-get install git fakeroot build-essential ncurses-dev xz-utils libssl-dev bc flex libelf-dev bison

3. copy the existing linux config file
  $ cd linux-6.0.8
  $ cp -v /boot/config-$(uname -r) .config

4. to make changes to the configuration file
  $ make menuconfig

5. build the kernel
  $ scripts/config --disable SYSTEM_TRUSTED_KEYS	(if No rule to make target 'debian/canonical-certs.pem)
  $ scripts/config --disable SYSTEM_REVOCATION_KEYS	(if No rule to make target 'debian/canonical-certs.pem)
  $ make

6. install the required modules
  $ sudo make modules_install

7. install the kernel
  $ sudo make install

8. reboot
  $ press "Esc" or "Shift" and select kernel 6.0.8

9. check kernel version
  $ uname -mrs
