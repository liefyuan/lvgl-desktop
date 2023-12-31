# LVGL for frame buffer device

LVGL configured to work with `/dev/fb0` on Linux, however it can be changed in [`lv_drv_conf.h`](https://github.com/lvgl/lv_port_linux_frame_buffer/blob/master/lv_drv_conf.h) by `FBDEV_PATH`.

When cloning this repository, also make sure to download submodules (`git submodule update --init --recursive`) otherwise you will be missing key components.

Check out this blog post for a step by step tutorial:
https://blog.lvgl.io/2018-01-03/linux_fb

## Clone the project

Clone the LVGL Framebuffer Demo project and its related sub modules:

```
git clone https://github.com/lvgl/lv_port_linux_frame_buffer.git
cd lv_port_linux_frame_buffer/
git submodule update --init --recursive
```

## Build the project

```
make
sudo make install
```

## Run the demo application

```
demo
```
# lvgl-desktop
