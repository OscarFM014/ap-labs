# Multithreaded Earthquake Simulator 🌎
This project is a multithreaded earthquake simulator where every person in a building floor must walk out of the building by the emergency exits.

## Introduction 
This document provides a comprehensive architectural overview of the system, using a number of different architectural views to depict different aspects of the system. It is intended to capture and convey the significant architectural decisions which have been made on the system.

### Scope 
This Software Architecture Document provides an architectural overview of the Multithreaded Earthquake Simulator.

### References
Applicable references are:
[Stack Libray](https://pkg.go.dev/github.com/golang-collections/collections/stack)

## Architectural Representation 
This document presents the architecture as a series of views; logical view and process view . There is no separate implementation view described in this document.

## Architectural Goals and Constraints
There are some key requirements and system constraints that have a significant bearing on the architecture. They are:

- The building's map can be static or automatically generated.
- We're considering a 1-floor building.
- Each person's behaviour must be implemented in a separated thread.
- Building map is a shared resource across all people threads.
- Number of people and emergency exits in the building is defined in the simulation's start.
- Emergency exits are randomly located.
- Every person emergency walk out route is randomply generated to the first found exit.
- Each person will have his/her own walking speed.
- If a person finds another person on his/her path, he/she must slow down in case that the front person's walk is slower.
- Define a timeout for walking out of the building.
- Display safe people and trapped people after earthquake timeout.

##Logical View
A description of the logical view of the architecture. Describes the most important classes and the organization of the system. Class diagrams may be included to illustrate the relationships between architecturally.

### Architecture Overview


##Process View
A description of the logical view of the architecture. Describes the most important classes and the organization of the system. Class diagrams may be included to illustrate the relationships between architecturally.

###Processes



## Getting Started 🚀
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites 🔧
You need to have a web navigator, preferably the most updated versions:
> + [Go](https://go.dev/learn/)

To visualize functionallity:
```
make build
```
And then
```
make test
```

### Explanation  ⚙️


Test 1
- The command -p represent the number of people
- The command -e represent the number of exits
- By default the program always set 1 person and 1 exit

```
$ ./earthquake.o -p 5 -e 2 || true
```
- First you will see the building:
- The number 1 represent the wall
- The number -1 represent the exits
- The number 8 the people
```
5 People In the Building (represented with 8): 
[1 1 1 -1 -1 1 1]
[1 0 0 0 0 0 1]
[1 0 0 0 0 0 1]
[1 0 8 0 0 8 1]
[1 0 0 0 8 0 1]
[1 0 8 0 8 0 1]
[1 1 1 1 1 1 1]
```
- The earthquake start
```
Starting Earthquake! Duration: 20 seconds
```

- Here is a info about the people (threads) during the earthquake in real time
- The collision message represent the collision in the floor between the people (threads)

```
People exiting the building in real time:

Collision People, Slow Speed

Collision People, Slow Speed

Collision People, Slow Speed

1+ live saved, the person take the exit in the [0,3] position and the path that follow was [[3 2] [4 2] [5 2] [5 3] [4 3] [3 3] [2 3] [1 3] [0 3]] with a speed of 12

1+ live saved, the person take the exit in the [0,3] position and the path that follow was [[4 4] [5 4] [5 5] [4 5] [3 5] [2 5] [1 5] [1 4] [2 4] [3 4] [3 3] [4 3] [5 3] [5 2] [4 2] [3 2] [2 2] [1 2] [1 3] [2 3] [0 3]] with a speed of 15
```

- Once the main time of the earthquake finish, the info of the total people saved and trapped is displayed

```
Earthquake finish! 

Safe people:

1.- the person take the exit in the [0,3] position and the path that follow was [[3 2] [4 2] [5 2] [5 3] [4 3] [3 3] [2 3] [1 3] [0 3]] with a initial speed of 12

2.- the person take the exit in the [0,3] position and the path that follow was [[4 4] [5 4] [5 5] [4 5] [3 5] [2 5] [1 5] [1 4] [2 4] [3 4] [3 3] [4 3] [5 3] [5 2] [4 2] [3 2] [2 2] [1 2] [1 3] [2 3] [0 3]] with a initial speed of 15

Trapped people:

1.- The person began in [5,4] position and the path that follow was [[5 4] [4 4] [3 4] [2 4] [1 4] [0 4]] with a initial speed of 12

2.- The person began in [5,2] position and the path that follow was [[5 2] [4 2] [3 2] [2 2] [1 2] [1 3] [2 3] [3 3] [4 3] [5 3] [5 4] [4 4] [3 4] [2 4] [1 4] [0 4]] with a initial speed of 16

3.- The person began in [3,5] position and the path that follow was [[3 5] [4 5] [5 5] [5 4] [4 4] [3 4] [2 4] [1 4] [0 4]] with a initial speed of 10
```

## Build With 🛠
+ Go

## Authors 🖋
+ **Linda Abundis** *-  Developer -*  [Linda Abundis](https://github.com/LindaNayeli104)
+ **Oscar Fernandez** *- Developer-* [OscarFM014](https://github.com/OscarFM014)

See also the list of [**contributors**](https://github.com/OscarFM014/diversify/graphs/contributors) who participated in this project.

## License 📄
This project is licensed under the [MIT](https://choosealicense.com/licenses/mit/) License
