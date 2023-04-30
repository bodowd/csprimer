package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strconv"
	"strings"
)

var hex2dec = map[string]int{
	"0": 0,
	"1": 1,
	"2": 2,
	"3": 3,
	"4": 4,
	"5": 5,
	"6": 6,
	"7": 7,
	"8": 8,
	"9": 9,
	"a": 10,
	"b": 11,
	"c": 12,
	"d": 13,
	"e": 14,
	"f": 15,
}

func _convert(s string) string {
	return strconv.Itoa((hex2dec[string(s[0])] << 4) + hex2dec[string(s[1])])
}

func convert(re *regexp.Regexp, s string) string {
	match := re.FindStringSubmatch(s)
	var sb strings.Builder
	sb.WriteString("rgb(")
	if len(match) > 0 {
		m := match[1]
		_r := m[:2]
		_g := m[2:4]
		_b := m[4:6]

		r := _convert(_r)
		g := _convert(_g)
		b := _convert(_b)

		rgb := fmt.Sprintf("%s %s %s", r, g, b)

		sb.WriteString(rgb)

	}

	sb.WriteString(")")
	return sb.String()
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		s := scanner.Text()
		re := regexp.MustCompile("#([0-9a-fA-F]+)")
		fmt.Println(re.ReplaceAllString(s, convert(re, s)))
		// fmt.Println(replace)
	}

}
