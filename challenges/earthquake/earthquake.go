package main

import (
	"flag"
	"fmt"
	"math/rand"
	"strconv"
	"time"
)

//Stack Libray : https://pkg.go.dev/github.com/golang-collections/collections/stack
type (
	Stack struct {
		top    *node
		length int
	}
	node struct {
		value string
		prev  *node
	}
)

// Create a new stack
func New() *Stack {
	return &Stack{nil, 0}
}

// Return the number of items in the stack
func (this *Stack) Len() int {
	return this.length
}

// View the top item on the stack
func (this *Stack) Peek() string {
	if this.length == 0 {
		return ""
	}
	return this.top.value
}

// Pop the top item of the stack and return it
func (this *Stack) Pop() string {
	if this.length == 0 {
		return ""
	}

	n := this.top
	this.top = n.prev
	this.length--
	return n.value
}

// Push a value onto the top of the stack
func (this *Stack) Push(value string) {
	n := &node{value, this.top}
	this.top = n
	this.length++
}

type person struct {
	speed     int
	path      [][2]int
	current_x int
	current_y int
}

var n_exits int
var n_people int
var floor = [7][7]int{
	{1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1}}
var people_array []person
var people_saved []person
var time_to_exit int
var finish_time bool

func array_gen_path(maze [7][7]int, x_position int, y_position int) [][2]int {
	var h int = len(maze)
	var l int = len(maze[0])

	var visited [7][7]bool
	var pathToExit [][2]int

	stack := New()

	stack.Push(strconv.Itoa(x_position) + "," + strconv.Itoa(y_position))

	for stack.Len() != 0 {
		top_element := stack.Pop()
		var row, col int

		fmt.Sscanf(top_element, "%d,%d", &row, &col)

		if row < 0 || col < 0 || row >= h || col >= l || visited[row][col] {
			continue
		}

		if floor[row][col] == 1 {
			continue
		}
		var values = [2]int{row, col}
		visited[row][col] = true
		pathToExit = append(pathToExit, values)

		if floor[row][col] == -1 {
			break
		}

		stack.Push(strconv.Itoa(row) + "," + strconv.Itoa((col - 1)))
		stack.Push(strconv.Itoa(row) + "," + strconv.Itoa((col + 1)))
		stack.Push(strconv.Itoa((row - 1)) + "," + strconv.Itoa(col))
		stack.Push(strconv.Itoa((row + 1)) + "," + strconv.Itoa(col))
	}
	return pathToExit
}

func setVariables() {
	var random_x, random_y, random_speed int
	for i := 0; i < n_exits; i++ {
		rand.Seed(time.Now().UnixNano())
		if (rand.Intn(6-1)+1)%2 == 0 {
			random_x = rand.Intn(6-1) + 1
			floor[random_x][0] = -1
		} else {
			random_y = rand.Intn(6-1) + 1
			floor[0][random_y] = -1
		}
	}

	p := new(person)

	for i := 0; i < n_people; i++ {
		rand.Seed(time.Now().UnixNano())
		random_x = rand.Intn(6-1) + 1
		random_y = rand.Intn(6-1) + 1
		random_speed = rand.Intn(20-10) + 10
		p = new(person)
		p.path = array_gen_path(floor, random_x, random_y)
		p.speed = random_speed
		p.current_x = random_x
		p.current_y = random_y
		people_array = append(people_array, *p)
	}
}

func walking_out(per person, out_build chan person) {
	for _, cor_cha := range per.path {
		time.Sleep(time.Duration(per.speed) * time.Millisecond)
		if finish_time {
			return
		}
		floor[per.current_x][per.current_y] = 0
		per.current_x = cor_cha[0]
		per.current_y = cor_cha[1]
		if floor[per.current_x][per.current_y] == 8 {
			per.speed = 90
			fmt.Println("\nCollision People, Slow Speed")
			time.Sleep(time.Duration(per.speed) * time.Second)
		}
		floor[per.current_x][per.current_y] = 8
	}
	floor[per.current_x][per.current_y] = -1
	out_build <- per
}

func exit_building() {
	total_time_earth := time.After(time.Duration(time_to_exit) * time.Second)
	out_build := make(chan person)
	for _, curr := range people_array {
		go walking_out(curr, out_build)
	}

	for {
		select {
		case <-total_time_earth:
			fmt.Println("\nEarthquake finish! \n")
			finish_time = true
			close(out_build)
			return
		case pe := <-out_build:
			fmt.Print("\n1+ live saved")
			fmt.Print(", the person take the exit in the [", pe.current_x, ",", pe.current_y, "] position")
			fmt.Println(" and the path that follow was", pe.path, "with a speed of", pe.speed)
			people_saved = append(people_saved, pe)
			break
		}
	}
}

func printFloor() {
	for i := 0; i < 7; i++ {
		fmt.Println(floor[i])
	}
}

func main() {
	var people = flag.Int("p", 1, "people")
	var exits = flag.Int("e", 1, "exits")
	time_to_exit = 20
	flag.Parse()
	n_people = *people
	n_exits = *exits
	if n_people > 13 {
		fmt.Errorf("Too many people on the building")
	}

	if n_exits > 19 {
		fmt.Errorf("Too many exits on the building")
	}

	setVariables()

	fmt.Println(n_people, "People In the Building (represented with 8): ")

	aux_show := floor

	for _, per := range people_array {
		aux_show[per.current_x][per.current_y] = aux_show[per.current_x][per.current_y] + 8
	}

	for _, row := range aux_show {
		fmt.Println(row)
	}

	fmt.Println(" \nStarting Earthquake! Duration:", time_to_exit, "seconds\n")
	fmt.Println("People exiting the building in real time: ")
	exit_building()
	fmt.Println("Safe people:")
	var people_trapped []person
	var finded bool

	for i, pe := range people_saved {
		fmt.Print("\n", i+1, ".-")
		fmt.Print(" the person take the exit in the [", pe.current_x, ",", pe.current_y, "] position")
		fmt.Println(" and the path that follow was", pe.path, "with a initial speed of", pe.speed)
	}

	for _, pe := range people_array {
		for _, sa := range people_saved {
			if sa.path[0][0] == pe.path[0][0] && sa.path[0][1] == pe.path[0][1] {
				finded = true
			}
		}
		if !finded {
			people_trapped = append(people_trapped, pe)
		}
		finded = false
	}

	fmt.Println("\nTrapped people:")
	for i, pe := range people_trapped {
		fmt.Print("\n", i+1, ".-")
		fmt.Print(" The person began in [", pe.current_x, ",", pe.current_y, "] position")
		fmt.Println(" and the path that follow was", pe.path, "with a initial speed of", pe.speed)
	}
	fmt.Println("")

}
