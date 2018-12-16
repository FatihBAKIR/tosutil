# tosutil

`tosutil` is a command line tool and libraries that are designed to simplify development with the tos operating system.

## Get information

```
tosutil info board nucleo/f103rb
tosutil info proc esp8266
tosutil info arch avr
tosutil info proc nRF52832
```

## Analyze programs

```
tosutil analyze info blink.elf
tosutil analyze size blink.elf
tosutil analyze safety blink.elf
```

## Downloading firmware to boards

```
tosutil program nucleo/f103rb blink.elf
tosutil program arduino/uno blink.elf
tosutil program nodemcu blink.elf
```

---

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
