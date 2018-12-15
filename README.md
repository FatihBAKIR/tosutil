# tosutil

`tosutil` is a command line tool and libraries that are designed to simplify development with the tos operating system.

## Install required components

For a board:

```
tosutil prepare board nucleo/f103rb
```

For a processor:

```
tosutil prepare proc esp8266
tosutil prepare proc STM32/F103RB
```

For a target:

```
tosutil prepare proc cortex-m3
```

## Install specific components

SDKs:
```
tosutil install sdk esp-open-sdk
tosutil install sdk nRF5
tosutil install sdk libopencm3
```