# _ESP32C3 QEMU boot problems_

This project illustrates the problem where the ESP32C3 QEMU build fails to boot
with only OTA applications and no factory application.
Link to Espressif/QEMU issue: https://github.com/espressif/qemu/issues/83

The application is set to use the custom partition table partitions.csv and the flash size
is set to 4MB.

The dev container is modified to install the QEMU version:
esp-qemu-riscv32-softmmu-develop_8.0.0_20230522
https://github.com/espressif/qemu/releases/tag/esp-develop-8.0.0-20230522

## Reproduce the problem
Open the devcontainer.

Execute commands:
```
idf.py build
cd build/
esptool.py --chip esp32c3 merge_bin --fill-flash-size 4MB -o flash_image.bin @flash_args
qemu-system-riscv32 -nographic -icount 3 -machine esp32c3 -drive file=flash_image.bin,if=mtd,format=raw
```

## "Fix" the problem
In order to "fix" the problem simply remove otadata from the partitions.csv (Remove line 3).
Or use menuconfig to set the partition table to: Factory app, two OTA definitions.

Then rerun the "execute commands".