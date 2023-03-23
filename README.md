# 74LS382 Function Table

Some 8-bit homebrew computer projects use the [74LS382](https://archive.org/details/74LS382) 4-bit ALU chip.
However, that chip's documentation is a bit incomplete.
This repository contains a complete readout of its function table and a piece of C code that is semantically equivalent.

![SN74LS382 text](74382.jpg?raw=true "Title")

## Summary of the Chip's Behavior

The 74382 has 8 ALU operations:

| s210        | Operation           |
| ----------- | ------------------- |
| 0           | Clear               |
| 1           | B + ~A + carry-in   |
| 2           | A + ~B + carry-in   |
| 3           | A +  B + carry-in   |
| 4           | A xor B             |
| 5           | A or B              |
| 6           | A and B             |
| 7           | Preset              |

- Operation 0 sets the output, the carry-in, and overflow bits to 0
- Operations 1, 2, 3 behave as expected.
- Operations 4, 5, 6 copy the carry-in to the carry-out and overflow outputs **if** the result of the operation is 1111 or set them to 0 otherwise.
- Operation 7 sets the output to 1111 and copies the carry-in to carry-out and overflow.

## Readout File Format

The file `table_sabcf_74382.txt` is a readout of a 74382 with an Arduino.
The columns are s, a, b, c, f.

The value of column `f` is determined in the following way: The low four bits are the result of the ALU operation. Bit 5 is the carry out and bit 6 the value of the overflow bit.
