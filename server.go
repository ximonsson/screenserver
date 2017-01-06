package main

/*
#cgo pkg-config: x11
#include "xlib.h"
*/
import "C"
import (
	"bytes"
	"flag"
	"fmt"
	"image"
	"image/jpeg"
	"log"
	"net/http"
	"time"
	"unsafe"
)

// default port
var port string = "9002"

// default fps
var fps int = 25

var (
	img      *image.RGBA  // store screen shot
	bufBack  bytes.Buffer // buffer we encode to
	bufFront bytes.Buffer // buffer we server from
)

// Take a screenshot of the screen
func screenshot() {
	if i := C.take_screen_shot(unsafe.Pointer(&img.Pix[0])); i != 0 {
		log.Panicln("Could not get screenshot")
	}
}

// Starts capture of desktop screen at fps.
func capture() {
	for {
		// take a screen shot
		screenshot()
		// encode image
		bufBack.Reset()
		if e := jpeg.Encode(&bufBack, img, nil); e != nil {
			log.Panicln(e)
		}
		bufFront, bufBack = bufBack, bufFront
		// respect FPS
		time.Sleep(time.Second / time.Duration(fps))
	}
}

// Serve screen shot from buffer
func handle(w http.ResponseWriter, req *http.Request) {
	w.Header().Set("Content-Type", "image/jpeg")
	if _, e := w.Write(bufFront.Bytes()); e != nil {
		log.Panicln(e)
	}
}

func init() {
	// init command line arguments
	flag.StringVar(&port, "port", port, "port the server listens on")
	flag.IntVar(&fps, "fps", fps, "frame per second to record screen")

	// init screen grabbing
	C.init_screen_grabbing()
	var w, h C.int
	C.screen_dimensions(&w, &h)
	img = image.NewRGBA(image.Rect(0, 0, int(w), int(h)))
	fmt.Printf("Screen is %dx%d pixels\n", w, h)

	// init routes
	http.HandleFunc("/", handle)
}

func deinit() {
	C.deinit_screen_grabbing()
}

func main() {
	flag.Parse()
	fmt.Printf("%-10s %s\n", "port", port)
	fmt.Printf("%-10s %d\n", "fps", fps)

	// start screen capture
	go capture()

	// start http server
	http.ListenAndServe(":"+port, nil)
}
