# SCREEN SHARE
Simple server to share screen over network.

## Introduction
The server continuously records the screen of the host system by taking screen shots, compresses them to JPEG,
and serves them over HTTP.

At the moment the application will only work on systems running an X server instance, as Xlib is used to take the
actual screenshots.

## Dependencies
 - xlib C bindings

## Run
Run following for a list of command line arguments available:
```sh
$GOPATH/bin/screenserver -usage
```
Without arguments the default port is set to `9002` and the default fps is `25`.

## TODO
 - Share through web sockets
 - Support other window servers than X
