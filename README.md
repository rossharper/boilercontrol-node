# boilercontrol-node

Node.js wrapper for [boilercontrol](https://github.com/rossharper/boilercontrol) ... that doesn't seem to work.

For some reason the signal isn't generated correctly through the plugin (probably timings off).

# Dependencies

Requires:

- [node-gyp](https://github.com/TooTallNate/node-gyp)

Requires the following installed as dynamic libraries:

- [wiringPi](http://wiringpi.com/download-and-install/)
- [boilercontrol](https://github.com/rossharper/boilercontrol)

# Build

    node-gyp configure
    node-gyp build
