# SCREEN SHARE
Simple server to share screen over network.

## Introduction
The server continuously records the screen of the host system by taking screenshots, compresses them to JPEG, and serves them over HTTP.

At the moment the application will only work on systems running an X server instance, as Xlib is used to take the actual screenshots.

## Dependencies
 - xlib C bindings

## Run
Run following for a list of command line arguments available:
```sh
$GOPATH/bin/screenserver -usage
```
Without arguments the default port is set to `9002` and the default fps is `25`.

## TODO
* Change so we actually encode the images to a videostream instead.
* Use https://medium.com/stupid-gopher-tricks/streaming-data-in-go-without-buffering-3285ddd2a1e5 as inspiration for solving the streaming.
* Add audio support.
