# The BrainFuck Interpreter

## Information

This is the free implementation of the BrainFuck programming language written in C. The interpreter support two execution mode:

* source files (*.bf) execution mode;
* interactive execution mode.  

To run the first mode you need to pass the path to source file to the interpreter. For example:

```bush
./BFInterpreter hello_world.bf
```

Or you can run the interactive mode by the command without parameters:

```bash
./BFInterpreter
```

Written by MatrixDeity, 2018.

## Dependencies

This implementation don't has some special dependencies.

## Examples

### HelloWorld

```bush
++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.
```

## Links

* [BrainFuck](https://en.wikipedia.org/wiki/Brainfuck)