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
<script src="https://gist.github.com/maitesin/05afafa443c41042078448efe9c42367.js"></script>
Assembly generated:
<script src="https://gist.github.com/maitesin/e2a261eefda5862da26f8e7402a3109d.js"></script>
