
# FreeRTOS on a Raspberry Pico with Multicore support

Layout:

```sh
~/pico/pico-sdk/
~/pico/FreeRTOS-Kernel/
~/pico/PicoFreertosBlink/
```

To download the pico-sdk do the following:

```sh
cd ~/pico/
git clone https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk/
git submodule update --init
cd ..
```

To download the FreeRTOS-Kernel do the following:

```sh
cd ~/pico/
git clone https://github.com/FreeRTOS/FreeRTOS-Kernel.git
cd FreeRTOS-Kernel/
git checkout smp
```

# Building

```sh
cd ~/pico/
git clone https://github.com/ghubcoder/PicoFreertosBlink.git
cd PicoFreertosBlink/
mkdir build && cd build/
export PICO_SDK_PATH=~/pico/pico-sdk
export FREERTOS_KERNEL_PATH=~/pico/FreeRTOS-Kernel
cmake ..
make
```

Blink code is a modified version of the code available in [this](https://github.com/yunkya2/pico-freertos-sample) repository.

More [here](https://ghubcoder.github.io/posts/using-multiple-cores-pico-freertos/)
