// Clock Server is a concurrent TCP server that periodically writes the time.
package main

import (
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"strings"
)

func mustCopy(src io.Reader) string {
	time_buf := make([]byte, 1024)
	buffer_size := 0
	n, err := io.ReadFull(src, time_buf)
	if err != nil {
		if err != io.EOF {
			buffer_size = n
		}
	}
	return string(time_buf[:buffer_size])
}

func get_location_time(port_addr string) net.Conn {
	conn, err := net.Dial("tcp", port_addr)
	if err != nil {
		log.Fatal("The next port not found wasn't found => " + port_addr)
	}
	return conn
}

func main() {
	if len(os.Args) < 2 {
		log.Fatal("Locations not added: go run clockWall.go NewYork=localhost:8010")
	}
	for _, param_locations := range os.Args[1:] {
		s := strings.Split(param_locations, "=")
		fmt.Print(mustCopy(get_location_time(s[1])))
	}
}

/*

Commands
TZ=US/Eastern go run clockServer.go -port 8010
TZ=Asia/Tokyo go run clockServer.go -port 8020
TZ=Europe/London go run clockServer.go -port 8030
TZ=Local go run clockServer.go -port 8040
TZ=Asia/Shanghai go run clockServer.go -port 8050

go run clockWall.go NewYork=localhost:8010 Tokyo=localhost:8020 London=localhost:8030 Local=localhost:8040 Shangai=localhost:8050*/
