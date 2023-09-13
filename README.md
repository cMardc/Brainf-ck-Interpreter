# Brainf*ck Interpreter in C

This is a simple Brainf*ck interpreter written in C. Brainf*ck is a minimalist and esoteric programming language known for its minimalistic syntax consisting of only eight commands.

## Features

- **Basic Brainf*ck Support:** This interpreter can run Brainf*ck programs that use the standard Brainf*ck commands:
  - `>` Increment the data pointer
  - `<` Decrement the data pointer
  - `+` Increment the byte at the data pointer
  - `-` Decrement the byte at the data pointer
  - `[` Jump past the corresponding `]` if the byte at the data pointer is 0
  - `]` Jump back to the corresponding `[` if the byte at the data pointer is nonzero
  - `.` Output the byte at the data pointer as a character
  - `,` Read a character and store it in the byte at the data pointer

- **Interactive Mode:** Run Brainf*ck programs interactively, allowing you to input and execute code line by line.

- **File Input:** You can also provide a Brainf*ck program stored in a text file as input.

- **Error Handling:** The interpreter includes basic error handling and will report errors such as unmatched brackets, moving the data pointer out of bounds, or attempting to increment/decrement beyond the valid range.

- **Clear Screen:** The interpreter can clear the terminal screen using the `clear` command.

## Usage

### Interactive Mode

To run the interpreter in interactive mode, simply execute the program without any command-line arguments:

```
./brainf
```

You can then enter Brainf*ck code line by line. To exit the interactive mode, type `exit`.

### Run Brainf*ck Program from File

To run a Brainf*ck program stored in a text file, use the following command:

```
./brainf your_program.bf
```

Replace `your_program.bf` with the path to your Brainf*ck program file.

### Clear Screen

To clear the terminal screen when running in interactive mode, type `clear`.

## Example

Here's an example of running a Brainf*ck program in interactive mode:

```
$ ./brainf

Welcome to the Brainf*ck interpreter!
Enter Brainf*ck code (type 'exit' to quit):

>+++++++++[<++++++++>-]<.>+++++++[<++++>-]<+.+++++++..+++.>>>++++++++[<++++>-]
<.>>>++++++++++[<+++++++++>-]<---.<<<<.+++.------.--------.>>+.>++++++++++.
```

This program outputs "Hello, World!".

## Requirements

This interpreter has been developed and tested on various Unix-like systems, including Linux and macOS. It may also work on other platforms with minimal modifications.

## Acknowledgments

This Brainf*ck interpreter was created as a simple educational project and is not optimized for performance or feature completeness.

Feel free to use and modify this code for your own purposes. If you find any issues or have suggestions for improvements, please let me know.

Happy Brainf*ck coding!
