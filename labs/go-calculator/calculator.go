package main

import (
	"fmt"
	"os"
	"strconv"
)

// adds/subtracts/multiplies all values that are in the *values array.
// nValues is the number of values you're reading from the array
// operator will indicate if it's an addition (1), subtraction (2) or
// multiplication (3)
func calc(operator int, values []int) int {
	result := values[0]
	fmt.Print("", result)
	for i := 1; i < len(values); i++ {
		if operator == 1 {
			result += values[i]
			fmt.Print(" + ", values[i])
		} else if operator == 2 {
			result -= values[i]
			fmt.Print(" - ", values[i])
		} else {
			result *= values[i]
			fmt.Print(" * ", values[i])
		}
	}

	fmt.Print(" = ", result)
	fmt.Print("\n")
	return result
}

// TODO: clean the code
func main() {
	values := os.Args[1:]

	if len(os.Args) < 3 {
		fmt.Printf("You need to write in correct order the input (integers): \n")
		fmt.Printf("./calculator.c add 1 2 3 4 5\n")

		os.Exit(1)
	}

	if values[0] != "add" && values[0] != "sub" && values[0] != "mult" {
		fmt.Printf("You need to write in correct order the input and just this operations:\n")
		fmt.Printf("./calculator.c add 1 2 3 4 5\n")
		fmt.Printf("./calculator.c sub 1 2 3 4 5\n")
		fmt.Printf("./calculator.c mult 1 2 3 4 5\n")
		os.Exit(1)
	}
	var operator int

	arr := make([]int, len(values)-1)

	for i := 1; i < len(values); i++ {
		first, err := strconv.ParseInt(values[i], 10, 0)
		if err == nil {
			arr[i-1] = int(first)
		} else {
			fmt.Printf("You need to write in correct order the input (integers): \n")
			fmt.Printf("./calculator.c add 1 2 3 4 5\n")
			os.Exit(1)
		}
	}

	if values[0] == "add" {
		operator = 1
	} else if values[0] == "sub" {
		operator = 2
	} else {
		operator = 3
	}

	calc(operator, arr)

}
