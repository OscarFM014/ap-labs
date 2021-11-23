// Clock Server is a concurrent TCP server that periodically writes the time.
package main

import (
	"flag"
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"strconv"
	"time"
)

func TimeIn(t time.Time, name string) (time.Time, error) {
	loc, err := time.LoadLocation(name)
	if err == nil {
		t = t.In(loc)
	}
	return t, err
}

func handleConn(c net.Conn, name string) {
	defer c.Close()
	t, err := TimeIn(time.Now(), name)
	if err == nil {
		_, err := io.WriteString(c, name+"	:	"+t.Format("15:04:05\n"))
		if err != nil {
			return // e.g., client disconnected
		}
	} else {
		fmt.Println(name, "<time unknown>")
	}
}

func main() {
	port := flag.Int("port", 999, "an port")

	flag.Parse()
	fmt.Println("port:", *port)
	if *port < 1000 {
		log.Fatal("Port not added")

	}

	time_zone := os.Getenv("TZ")
	if time_zone == "" {
		log.Fatal("TZ not assigned")
	}

	fmt.Println("TZ:", os.Getenv("TZ"))
	string_port := strconv.Itoa(*port)
	listener, err := net.Listen("tcp", "localhost:"+string_port)

	if err != nil {
		log.Fatal(err)
	}
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Print(err) // e.g., connection aborted
			continue
		}
		go handleConn(conn, time_zone) // handle connections concurrently
	}
}

/*

Commands
TZ=US/Eastern go run clockServer.go -port 8010
TZ=Asia/Tokyo go run clockServer.go -port 8020
TZ=Europe/London go run clockServer.go -port 8030
TZ=Local go run clockServer.go -port 8040
TZ=Asia/Shanghai go run clockServer.go -port 8050

go run clockWall.go NewYork=localhost:8010 Tokyo=localhost:8020 London=localhost:8030 Local=localhost:8040 Shangai=localhost:8050 */
