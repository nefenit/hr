/* hr.c - writes horizontal bar to standard output
 * (c) Copyright 2020 Bartosz Mierzynski
 */

package main

import (
	"fmt"
	"os"
	"strconv"
	"golang.org/x/crypto/ssh/terminal"
	"unicode/utf8"
)

func get_columns() uint {
	if columns , err := strconv.Atoi(os.Getenv("COLUMNS")); err == nil {
		return uint(columns)
	} else {
		if width, _, err := terminal.GetSize(int(os.Stdout.Fd())); err == nil {
			return uint(width)
		} else {
			return 80
		}
	}
}

func hr1(n uint) {
	for n > 0 {
		fmt.Print("#")
		n--
	}
	fmt.Print("\n")
}

func hr2(n uint, s string) {
	rlen  := uint(utf8.RuneCountInString(s))
	runes := []rune(s)
	for i := uint(0); i < n; i++ {
		fmt.Printf("%c", runes[i % rlen])
	}
	fmt.Print("\n")
}

func main() {
	n := get_columns()

	if len(os.Args) < 2 {
		hr1(n)
	} else {
		for _, arg := range os.Args[1:] {
			hr2(n, arg)
		}
	}
}
