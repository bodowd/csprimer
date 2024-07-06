package main

import "fmt"

func f(n int) int {
	fmt.Printf("&n at n=%d: &%d\n", n, &n)
	return f(n + 1)
}

func main() {
	sum := f(10)
	fmt.Println(sum)
	fmt.Println(&sum)
}
