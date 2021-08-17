package main

import (
	"fmt"
	"os"
)

func main() {
	names := os.Args[1:]
	if(len(os.Args) == 0){
		fmt.Errorf("No name")
	}else{
		for _, name := range names {
			fmt.Printf("Hello %v, Welcome to the jungle \n", name)
		}
	}

}
