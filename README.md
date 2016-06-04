# ARM C Compiler (ACC)
[![Build Status](https://travis-ci.org/maitesin/acc.svg?branch=master)](https://travis-ci.org/maitesin/acc)
<a href="https://scan.coverity.com/projects/arm-c-compiler">
  <img alt="Coverity Scan Build Status" src="https://scan.coverity.com/projects/7891/badge.svg"/>
</a>
[![codecov](https://codecov.io/gh/maitesin/acc/branch/master/graph/badge.svg)](https://codecov.io/gh/maitesin/acc)


**ACC** is a project that its only aim is to improve my knowledge of two topics, C language and ARM assembly. I think this is a good exercise to go deep into both topics.

# Parser
The **ACC** is a **LALR(1) parser**, that means it is a [**Look-Ahead Left-to-Right parser**](https://en.wikipedia.org/wiki/LALR_parser).

# Grammar
```
S -> int main "(" ")" "{" E "}"
E -> return I;
     | if "(" B ")" "{" E "}"
     | if "(" B ")" "{" E "}" else "{" E "}"
I -> [0-9]+
B -> I < I
     | I <= I
     | I == I
     | I >= I
     | I > I
     | ! B
     | "(" B ")"
```

# Example
C code:
```c
int main()
{
    if (1 < 2)
    {
	    if (4 > 10)
	    {
		    return 1;
	    }
	    else {
		    return 2;
	    }
    }
    return 0;
}
```
Assembly generated:
```asm
	.text
	.global main
main:
	mov r0, #1
	mov r1, #2
	cmp r0, r1
	bge if_else_0
	mov r0, #4
	mov r1, #10
	cmp r0, r1
	ble if_else_1
	mov r0, #1
	bx lr
if_else_1:
	mov r0, #2
	bx lr
if_else_0:
	mov r0, #0
	bx lr
```
