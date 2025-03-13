# Create a character device for testing read/write system call

# Test env
VirtualBox 7.1.6 r167084
ubuntu-22.04.5 (linux-6.8.0-52-generic)

# Install virtualBox
install "Guest Additions" for using share folder

# Replace kernel to linux-6.0.8 from ubuntu-22.04.5 default
  $ press "Esc" or "Shift" and select kernel 6.0.8

# Build and install "csli_chrdev"
  $ make
  $ make install
  $ depmod
  $ modprobe csli_chrdev
  $ modprobe -r csli_chrdev

# Check csli_chrdev character device
  $ ls /dev/csli_chrdev -al
  $ cat /sys/class/csli_chrdev/csli_chrdev/dev
  $ dmesg | grep csli

# run "csli_chrdev_test"


