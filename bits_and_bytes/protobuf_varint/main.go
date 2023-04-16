package main

import (
	"encoding/binary"
	"fmt"
	"os"
)

func encode(bytes []byte) []byte {

	remaining := binary.BigEndian.Uint64(bytes)

	var result []byte

	for remaining > 0 {
		// isolate the lowest 7 bits
		lowest7bits := remaining & 255

		// we will need to move to the next 7 bits by shifting
		// out the lowest 7 bits for the next loop, but we do it
		// now because we need to check if there is anything else
		// after the 7 bits to know if we should add the header
		remaining >>= 7

		// add header if this is not the last byte
		if remaining > 0 {
			addHeader := lowest7bits | 128
			// store the result
			result = append(result, byte(addHeader))
		} else {
			result = append(result, byte(lowest7bits))
		}

	}

	return result
}

func decode(varint []byte) uint64 {
	accumulator := uint64(0)
	for i := len(varint) - 1; i >= 0; i-- {
		accumulator <<= 7
		accumulator |= uint64(varint[i] & 127)
	}
	return accumulator
}

func main() {

	files := []string{"varint/1.uint64", "varint/150.uint64", "varint/maxint.uint64"}

	for _, s := range files {
		bytes, err := os.ReadFile(s)
		if err != nil {
			panic(err)
		}

		fmt.Println(binary.BigEndian.Uint64(bytes))

		varint := encode(bytes)
		fmt.Printf("In binary: %08b \n", varint)
		fmt.Printf("In hexadecimal: %08x \n", varint)

		fmt.Printf("Decoded to decimal: %d\n\n", decode(varint))

	}

}
