# RPN Calculator

This is a calculator that takes in RPN.

## Usage

```
make
./calc-rpn
```

At the prompt, enter values and operations, space separated. Press enter to run.
```
: 1 2 +
stack: 3
```

You can enter input one at a time or all at once (up to some arbitrary maximum number of tokens per line, like 256 or so).

If you enter numeric values, they'll be pushed to the stack.
If you enter an operation or function, it'll pop its args off the stack and push it's results back on.

## Functions

* +, -, *, /
These all work as expected

* drop - pops and discards from the stack
* swap - pops two values and pushes them back on in reversed order
* dup - pops from the stack and pushes two of the value it popped
* clear - drop from the stack until empty (might not work yet)

