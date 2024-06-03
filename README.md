# CrackMe problem
My friend sent me a CrackMe problem and I'm writing a complete guide on how to crack it. If you want to try it yourself, don't look any further.
You may either patch the program or exploit an existing vulnerability.

### System
This CrackMe is written in assembly language and can be executed using DosBox.

## Problem Overview
First, let's use Ghidra to disassemble the program.

![Disassemble graph](/disasm_graph.png)

The program starts by checking the TF flag. If it's set, the program terminates immediately.
That makes using debuggers useless, but we can bypass it by nopping this check. 
We can unnop it after we're done.

Than program gets a string input from the user and somehow verifies it.

After that, the output is either 'Access granted' or 'Access denied'

## Method 1. Patching.
We'll start with the easier method. 

We've already noticed that the output depends on the output of the verifier function. 
It's very convenient, we can change one instruction in order for this to work.
```
jnz Success
```
By changing ``jz`` to ``jnz`` we made the program think that the incorrect password is actually correct. Done.

## Method 2. Exploiting.

In order to find an exploit in the program, let's have a look at its input handling function.

![Function that takes the input](/read_string_func.png)

As you can see, it stores data directly on the stack without any limitations - it's a good sign. In the function above, we can see that the program only allocates 0x80 bytes on the stack.

We’re facing a typical stack overflow vulnerability. The main idea of the exploit is in changing the return address. By overwriting it with our own value, we can redirect program execution to a location within the stack that we’ve carefully inputted beforehand.

![Function that takes the input](/example.png)

For example, this input will trick the program into thinking that the return address is "FFB0", but in reality, it zeros out the ax registers and jumps out of the function as if nothing happened.

# Automatisation

In order to make the process of patching even easier, I wrote a simple C application that can do it in two clicks.

## Prerequisites

In order to build the application, you must have GTK3.0 and libvlc installed:

```
sudo apt-get install libgtk-3-dev libvlc-dev
```

## Build and run
```
git clone git@github.com:nniikon/CrackMe.git
cd CrackMe/crack/
make
./crack
```

![](/gif.gif)

Hope you enjoyed this problem!

