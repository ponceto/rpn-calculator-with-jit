# RPN CALCULATOR WITH JIT

This is the source code of an RPN calculator with a simple [“Just In Time”](https://en.wikipedia.org/wiki/Just-in-time_compilation) (JIT) compiler.

## PREAMBLE

This project contains the source code for an RPN calculator implementing a virtual machine with bytecode and supporting “Just In Time” compilation at runtime.

The internal JIT compiler currently only supports the [Linux x86-64 ABI](doc/SYSTEM_V_ABI.md).

## DISCLAIMER

This project is for educational purpose only as support for a technical conference about compilers and JIT compilation.

This project comes with absolutely no warranty of any kind. You have been warned!

## LICENCE TERMS

Please read the file [doc/COPYING](doc/COPYING) for full licence terms.

```
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
```

## PROJECT HIERARCHY

```
.
├── bin   [may contain some useful stuff]
├── doc   [may contain some useful documents]
├── etc   [may contain some useful files]
├── lib   [may contain some useful libraries]
└── src   [contains the source code]
```

## HOW TO BUILD

A `Makefile` can be found in the `src` directory in order to `build` / `clean` / `check` the program.

### BUILD

In order to build the program, you must call `make` with the `all` target:

```
make
```

or

```
make all
```

If you are using `GNU Make`, you can run the `Makefile` in parallel to speedup the build:

```
make -j{number-of-parallel-jobs}
```

### CLEAN

In order to clean the build, you must call `make` with the `clean` target:

```
make clean
```

### CHECK

In order to execute some example tests, you must call `make` with the `check` target:

```
make check
```

## HOW TO RUN

### USAGE

```
Usage: rpncalc.bin [OPTIONS...] [EXPR [VERB]]...

Options:

    --help, -h                   display this help and exit

    --verbose, --quiet           enable/disable all log messages
    --debug, --no-debug          enable/disable debug log level
    --trace, --no-trace          enable/disable trace log level
    --print, --no-print          enable/disable print log level
    --alert, --no-alert          enable/disable alert log level
    --error, --no-error          enable/disable error log level

Expr:

    a valid RPN expression

Verb:

    execute                     execute an RPN expression
    compile                     compile an RPN expression
    run                         run the compiled expression
    clear                       clear the stack

```

## THE RPN CALCULATOR

This RPN calculator implements a simple syntax to compute some mathematical or logical operations, manage the stack of operands and manage the array of registers.

### GENERAL KEYWORDS

|      |      |       | Description                                                                      |
|:----:|:----:|:-----:|:---------------------------------------------------------------------------------|
|      |      | `nop` | no operation; do absolutely nothing                                              |
|      |      | `nnn` | push the `nnn` value onto the stack                                              |
|      | `i1` | `top` | get the topmost value from the stack                                             |
|      | `i1` | `pop` | pop the topmost value from the stack                                             |
|      |      | `clr` | clear the stack                                                                  |
|      | `i1` | `dup` | duplicate `i1`                                                                   |
| `i1` | `i2` | `xch` | exchange `i1` and `i2`                                                           |
| `i1` | `i2` | `sto` | store `i1` into `i2` register                                                    |
|      | `i1` | `rcl` | fetch `i2` from `i1` register                                                    |
|      | `i1` | `abs` | compute the absolute value of `i1`                                               |
|      | `i1` | `neg` | compute the negation of `i1`                                                     |
| `i1` | `i2` | `add` | compute the sum of `i1` and `i2`                                                 |
| `i1` | `i2` | `sub` | compute the difference of `i1` and `i2`                                          |
| `i1` | `i2` | `mul` | compute the product of `i1` and `i2`                                             |
| `i1` | `i2` | `div` | compute the division of `i1` and `i2`                                            |
| `i1` | `i2` | `mod` | compute the remainder of `i1` and `i2`                                           |
|      | `i1` | `cpl` | compute the one's complement of `i1`                                             |
| `i1` | `i2` | `and` | compute the logical and between `i1` and `i2`                                    |
| `i1` | `i2` | `ior` | compute the logical inclusive or between `i1` and `i2`                           |
| `i1` | `i2` | `xor` | compute the logical exclusive or between `i1` and `i2`                           |
| `i1` | `i2` | `shl` | shift `i1` `i2` bits to the left                                                 |
| `i1` | `i2` | `shr` | shift `i1` `i2` bits to the right                                                |
|      | `i1` | `inc` | increment `i1`                                                                   |
|      | `i1` | `dec` | decrement `i1`                                                                   |

### GENERAL OPERATORS

|      |      |       | Description                                                                      |
|:----:|:----:|:-----:|:---------------------------------------------------------------------------------|
| `i1` | `i2` | `+`   | same as `<i1> <i2> add`                                                          |
| `i1` | `i2` | `-`   | same as `<i1> <i2> sub`                                                          |
| `i1` | `i2` | `*`   | same as `<i1> <i2> mul`                                                          |
| `i1` | `i2` | `/`   | same as `<i1> <i2> div`                                                          |
| `i1` | `i2` | `%`   | same as `<i1> <i2> mod`                                                          |
| `i1` | `i2` | `~`   | same as `<i1> <i2> cpl`                                                          |
| `i1` | `i2` | `&`   | same as `<i1> <i2> and`                                                          |
| `i1` | `i2` | `\|`  | same as `<i1> <i2> ior`                                                          |
| `i1` | `i2` | `^`   | same as `<i1> <i2> xor`                                                          |
| `i1` | `i2` | `<<`  | same as `<i1> <i2> shl`                                                          |
| `i1` | `i2` | `>>`  | same as `<i1> <i2> shr`                                                          |
|      | `i1` | `++`  | same as `<i1> inc`                                                               |
|      | `i1` | `--`  | same as `<i1> dec`                                                               |

### EXTENDED KEYWORDS

|      |      |       | Description                                                                      |
|:----:|:----:|:-----:|:---------------------------------------------------------------------------------|
|      | `i1` | `st0` | same as `<i1> 0 sto`                                                             |
|      | `i1` | `st1` | same as `<i1> 1 sto`                                                             |
|      | `i1` | `st2` | same as `<i1> 2 sto`                                                             |
|      | `i1` | `st3` | same as `<i1> 3 sto`                                                             |
|      | `i1` | `st4` | same as `<i1> 4 sto`                                                             |
|      | `i1` | `st5` | same as `<i1> 5 sto`                                                             |
|      | `i1` | `st6` | same as `<i1> 6 sto`                                                             |
|      | `i1` | `st7` | same as `<i1> 7 sto`                                                             |
|      | `i1` | `st8` | same as `<i1> 8 sto`                                                             |
|      | `i1` | `st9` | same as `<i1> 9 sto`                                                             |
|      |      | `rc0` | same as `0 rcl`                                                                  |
|      |      | `rc1` | same as `1 rcl`                                                                  |
|      |      | `rc2` | same as `2 rcl`                                                                  |
|      |      | `rc3` | same as `3 rcl`                                                                  |
|      |      | `rc4` | same as `4 rcl`                                                                  |
|      |      | `rc5` | same as `5 rcl`                                                                  |
|      |      | `rc6` | same as `6 rcl`                                                                  |
|      |      | `rc7` | same as `7 rcl`                                                                  |
|      |      | `rc8` | same as `8 rcl`                                                                  |
|      |      | `rc9` | same as `9 rcl`                                                                  |
|      |      | `rnd` | same as `29 rcl`; get a pseudo-random number                                     |
|      |      | `now` | same as `30 rcl`; get the number of milliseconds since epoch                     |
| `i1` | `i2` | `fib` | same as `dup 20 sto add 20 rcl xch`; compute an iteration of the fibonacci suite |
|      |      | `run` | run the compiled expression                                                      |

### THE STACK OF OPERANDS

This RPN calculator has a stack of unlimited integer operands.

|      |      |       | Description                                                                      |
|:----:|:----:|:-----:|:---------------------------------------------------------------------------------|
|      |      | `nnn` | push the value `nnn` onto the stack                                              |
|      | `i1` | `top` | get the topmost value from the stack                                             |
|      | `i1` | `pop` | pop the topmost value from the stack                                             |
|      |      | `clr` | clear the stack                                                                  |
|      | `i1` | `dup` | duplicate `i1`                                                                   |
| `i1` | `i2` | `xch` | exchange `i1` and `i2`                                                           |

### THE ARRAY OF REGISTERS

This RPN calculator has an array of 32 integer registers that can be used to store/fetch temporary or special values.

|      |      |       | Description                                                                      |
|:----:|:----:|:-----:|:---------------------------------------------------------------------------------|
| `i1` | `i2` | `sto` | store `i1` into `i2` register                                                    |
|      | `i1` | `rcl` | fetch `i2` from `i1` register                                                    |
|      |      | `st0` | same as `0 sto`                                                                  |
|      |      | `st1` | same as `1 sto`                                                                  |
|      |      | `st2` | same as `2 sto`                                                                  |
|      |      | `st3` | same as `3 sto`                                                                  |
|      |      | `st4` | same as `4 sto`                                                                  |
|      |      | `st5` | same as `5 sto`                                                                  |
|      |      | `st6` | same as `6 sto`                                                                  |
|      |      | `st7` | same as `7 sto`                                                                  |
|      |      | `st8` | same as `8 sto`                                                                  |
|      |      | `st9` | same as `9 sto`                                                                  |
|      |      | `rc0` | same as `0 rcl`                                                                  |
|      |      | `rc1` | same as `1 rcl`                                                                  |
|      |      | `rc2` | same as `2 rcl`                                                                  |
|      |      | `rc3` | same as `3 rcl`                                                                  |
|      |      | `rc4` | same as `4 rcl`                                                                  |
|      |      | `rc5` | same as `5 rcl`                                                                  |
|      |      | `rc6` | same as `6 rcl`                                                                  |
|      |      | `rc7` | same as `7 rcl`                                                                  |
|      |      | `rc8` | same as `8 rcl`                                                                  |
|      |      | `rc9` | same as `9 rcl`                                                                  |
|      |      | `rnd` | same as `29 rcl`, pseudo-random number generator                                 |
|      |      | `now` | same as `30 rcl`, number of milliseconds since epoch                             |

Some of theses registers are reserved for special purpose like getting the current time or a pseudo-random number.

| Register | Read                           | Write                          |
|:--------:|:-------------------------------|:-------------------------------|
|     0    | user-defined                   | user-defined                   |
|     1    | user-defined                   | user-defined                   |
|     2    | user-defined                   | user-defined                   |
|     3    | user-defined                   | user-defined                   |
|     4    | user-defined                   | user-defined                   |
|     5    | user-defined                   | user-defined                   |
|     6    | user-defined                   | user-defined                   |
|     7    | user-defined                   | user-defined                   |
|     8    | user-defined                   | user-defined                   |
|     9    | user-defined                   | user-defined                   |
|    10    | user-defined                   | user-defined                   |
|    11    | user-defined                   | user-defined                   |
|    12    | user-defined                   | user-defined                   |
|    13    | user-defined                   | user-defined                   |
|    14    | user-defined                   | user-defined                   |
|    15    | user-defined                   | user-defined                   |
|    16    | user-defined                   | user-defined                   |
|    17    | user-defined                   | user-defined                   |
|    18    | user-defined                   | user-defined                   |
|    19    | user-defined                   | user-defined                   |
|    20    | calc-reserved                  | calc-reserved                  |
|    21    | calc-reserved                  | calc-reserved                  |
|    22    | calc-reserved                  | calc-reserved                  |
|    23    | calc-reserved                  | calc-reserved                  |
|    24    | calc-reserved                  | calc-reserved                  |
|    25    | calc-reserved                  | calc-reserved                  |
|    26    | calc-reserved                  | calc-reserved                  |
|    27    | calc-reserved                  | calc-reserved                  |
|    28    | calc-reserved                  | calc-reserved                  |
|    29    | calc-reserved                  | calc-reserved                  |
|    30    | get a new pseudo-random number | set a new pseudo-random seed   |
|    31    | current time in ms since epoch | do nothing                     |

## SOME EXAMPLES

### Example 1

Execute a simple expression.

  - Execute the expression `1 + 2`.

```
rpncalc.bin '1 2 add' execute
```

Results:

```
🟢 executing expression <1 2 add>
🟢 result is 3
```

### Example 2

Compile and execute a simple expression.

  - Compile the expression `3 * 4`.
  - Execute the compiled expression.

```
rpncalc.bin '3 4 mul' compile run
```

Results:

```
🟢 compiling expression <3 4 mul>
🟢 no result <empty stack>
🟢 running the compiled expression...
🔵 the bytecode has never been translated, executing bytecode and translating to machine code...
🟣 emit <function prolog>
🟣 exec <i64>
🟣 emit <i64>
🟣 exec <i64>
🟣 emit <i64>
🟣 exec <mul>
🟣 emit <mul>
🟣 emit <function epilog>
🟢 result is 12
```

### Example 3

Compile an equation then execute it with different parameters.

  - Compile the equation `y = a * x + b`.
  - Execute `clear stack` then the compiled equation with `a = 1`, `x = 2`, `b = 3`.
  - Execute `clear stack` then the compiled equation with `a = 2`, `x = 3`, `b = 4`.

```
rpncalc.bin 'mul add' compile 'clr 3 2 1 run' execute 'clr 4 3 2 run' execute
```

Results:

```
🟢 compiling expression <mul add>
🟢 no result <empty stack>
🟢 executing expression <clr 3 2 1 run>
🔵 the bytecode has never been translated, executing bytecode and translating to machine code...
🟣 emit <function prolog>
🟣 exec <mul>
🟣 emit <mul>
🟣 exec <add>
🟣 emit <add>
🟣 emit <function epilog>
🟢 result is 5
🟢 executing expression <clr 4 3 2 run>
🔵 the bytecode has already been translated, executing the generated machine code...
🟢 result is 10
```

### Example 4

Compile the Fibonacci function then execute some iterations.

  - Compile the function `fib`.
  - Initialize the stack with `0` and `1`.
  - Execute 15 iterations of the Fibonacci function.

```
rpncalc.bin 'fib' compile '0 1' execute run run run run run run run run run run run run run run run
```

Results:

```
🟢 compiling expression <fib>
🟢 no result <empty stack>
🟢 executing expression <0 1>
🟢 result is 1
🟢 running the compiled expression...
🔵 the bytecode has never been translated, executing bytecode and translating to machine code...
🟣 emit <function prolog>
🟣 exec <dup>
🟣 emit <dup>
🟣 exec <i64>
🟣 emit <i64>
🟣 exec <sto>
🟣 emit <sto>
🟣 exec <add>
🟣 emit <add>
🟣 exec <i64>
🟣 emit <i64>
🟣 exec <rcl>
🟣 emit <rcl>
🟣 exec <xch>
🟣 emit <xch>
🟣 emit <function epilog>
🟢 result is 1
🟢 running the compiled expression...
🔵 the bytecode has already been translated, executing the generated machine code...
🟢 result is 2
🟢 running the compiled expression...
🔵 the bytecode has already been translated, executing the generated machine code...
🟢 result is 3
🟢 running the compiled expression...
🔵 the bytecode has already been translated, executing the generated machine code...
🟢 result is 5
🟢 running the compiled expression...
🔵 the bytecode has already been translated, executing the generated machine code...
🟢 result is 8
🟢 running the compiled expression...
🔵 the bytecode has already been translated, executing the generated machine code...
🟢 result is 13
🟢 running the compiled expression...
🔵 the bytecode has already been translated, executing the generated machine code...
🟢 result is 21
🟢 running the compiled expression...
🔵 the bytecode has already been translated, executing the generated machine code...
🟢 result is 34
🟢 running the compiled expression...
🔵 the bytecode has already been translated, executing the generated machine code...
🟢 result is 55
🟢 running the compiled expression...
🔵 the bytecode has already been translated, executing the generated machine code...
🟢 result is 89
🟢 running the compiled expression...
🔵 the bytecode has already been translated, executing the generated machine code...
🟢 result is 144
🟢 running the compiled expression...
🔵 the bytecode has already been translated, executing the generated machine code...
🟢 result is 233
🟢 running the compiled expression...
🔵 the bytecode has already been translated, executing the generated machine code...
🟢 result is 377
🟢 running the compiled expression...
🔵 the bytecode has already been translated, executing the generated machine code...
🟢 result is 610
🟢 running the compiled expression...
🔵 the bytecode has already been translated, executing the generated machine code...
🟢 result is 987
```

### Example 5

Generate a sequence of random numbers.

  - Initialize the pseudo-random number generator with the current time.
  - Compile the expression to obtain a pseudo-random number between 0 and 127.
  - Generate 10 pseudo-random numbers.

```
rpncalc.bin 'now 30 sto' execute 'rnd abs 127 mod' compile run run run run run run run run run run
```

Results:

```
🟢 executing expression <now 30 sto>
🟢 no result <empty stack>
🟢 compiling expression <rnd abs 127 mod>
🟢 no result <empty stack>
🟢 running the compiled expression...
🔵 the bytecode has never been translated, executing bytecode and translating to machine code...
🟣 emit <function prolog>
🟣 exec <i64>
🟣 emit <i64>
🟣 exec <rcl>
🟣 emit <rcl>
🟣 exec <abs>
🟣 emit <abs>
🟣 exec <i64>
🟣 emit <i64>
🟣 exec <mod>
🟣 emit <mod>
🟣 emit <function epilog>
🟢 result is 71
🟢 running the compiled expression...
🔵 the bytecode has already been translated, executing the generated machine code...
🟢 result is 19
🟢 running the compiled expression...
🔵 the bytecode has already been translated, executing the generated machine code...
🟢 result is 95
🟢 running the compiled expression...
🔵 the bytecode has already been translated, executing the generated machine code...
🟢 result is 107
🟢 running the compiled expression...
🔵 the bytecode has already been translated, executing the generated machine code...
🟢 result is 49
🟢 running the compiled expression...
🔵 the bytecode has already been translated, executing the generated machine code...
🟢 result is 9
🟢 running the compiled expression...
🔵 the bytecode has already been translated, executing the generated machine code...
🟢 result is 43
🟢 running the compiled expression...
🔵 the bytecode has already been translated, executing the generated machine code...
🟢 result is 29
🟢 running the compiled expression...
🔵 the bytecode has already been translated, executing the generated machine code...
🟢 result is 21
🟢 running the compiled expression...
🔵 the bytecode has already been translated, executing the generated machine code...
🟢 result is 44
```
