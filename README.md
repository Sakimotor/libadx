# LibADX

A library for decoding [ADX](https://en.wikipedia.org/wiki/ADX_(file_format))
audio files.

## Introduction

**LibADX** is a library for decoding ADX audio files using the KallistiOS
development environment, intended for use only on the Sega Dreamcast game
console.

ADX is a proprietary audio container and compression format developed by
[CRI Middleware](https://www.criware.com/en/index.html) specifically for use
in video games; it is derived from ADPCM but with lossy compression.
[Learn more here](https://en.wikipedia.org/wiki/ADX_(file_format)).

This library features full implementation of the ADX looping function.
The available functions include `play`, `pause`, `stop` and `restart`.

This library is intended to be used as a KallistiOS Port (`kos-ports`) but
it can be used as a KallistiOS add-on as well.

## Installation

This library can be installed using 2 ways:

1. Using the `libADX` KallistiOS Ports (in `kos-ports`);
2. Cloning this repository directly in your `${KOS_BASE}/addons` directory.
   In that case you just have to enter this directory and build the library
   with `make install`.

## Usage

An example using this library is located here:

    $KOS_BASE/examples/dreamcast/sound/hello-adx

To encode ADX files, you can use [radx_encode](https://github.com/Isaac-Lozano/radx).

## Uninstallation

If needed, you can uninstall the library by entering `make clean`.

## Acknowledgments

This library was initially made for the **Dreamcast Media Center** application 
that can be found [here](https://github.com/PH3NOM-PRO/dreamcast-media-center).

* **Josh Pearson** ([PH3NOM](https://github.com/PH3NOM-PRO/)): Decoder algorithm
  optimized for stereo streams; and of course **LibADX** itself.
* [BERO](http://www.geocities.co.jp/Playtown/2004/): Decoder algorithm, written
  for the `adx2wav` utility.
* **Atsushi Yamazaki**: CRI ADX reverse engineering, which is available
  [here](http://web.archive.org/web/20060818165032/http://ku-www.ss.titech.ac.jp/~yatsushi/adx.html).
* [Headshotnoby](https://github.com/headshot2017) and 
  [Ian Micheal](https://github.com/ianmicheal): Small fix for modern KallistiOS.
* [Mickaël Cardoso](http://www.mickael-cardoso.fr/) ([SiZiOUS](http://sizious.com/)):
  Small refactoring.

## License

This library is completely free to modify and or redistribute; see the
[LICENSE](LICENSE) file for details.
