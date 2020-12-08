# A26

**A statically typed esoteric language written in C**

This compiled language consists of 26 registers, each labeled from **a-z**, and a global register **@**.

#

## Documentation

Registers can be declared using their respective symbol followed a pair of braces.

Each register is responsible for a unique purpose.

Additionally, all registers are organized like arrays, so each line inside a register represents a new line

```nasm
d {

}
```

All registers may reference other registers using `$` followed by the register name and the index you want to reference.

```nasm
@ {
  $p[2] ; referencing the second 
}
```

### Comments

Comments are represented using the `;` symbol

```nasm
@ {
  ; this is a comment
}
```

### Global Register

Represented by **@** symbol

The global register is where the program begins to run, so you must include it within your program. 

```nasm
@ {

}
```

### Output register

Represented by **p**

The **p** register displays an output

```nasm
p {
  "Hello World!"
}
```

You may directly use strings and numbers inside this register.

```nasm
p {
  "Hello\n"
  "My age is "
  9
}
```
