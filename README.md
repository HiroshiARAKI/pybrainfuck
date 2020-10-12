# pyBrainfuck
You can analyze Brainfuck code quickly, using this module implemented with C++.  
  
[WEBrainfuck++](https://bf.hirlab.net/) that was implemented by this module and Flask is available.  
Please check it out!

# Usage

```python
from pybrainfuck import Brainfuck

if __name__ == '__main__':
    bf = Brainfuck()  # or ``bf = Brainfuck("sample.bf")`` is ok.
    bf.set_code("+[-->-[>>+>-----<<]<--<---]>-.>>>+.>>..+++[.>]<<<<.+++.------.<<-.>>>>+.")
    res = bf.analyze()
    steps = bf.get_steps()

    print(f"{res}")
    print(f"{steps} steps.")
```
```text
Hello, World!
17896 steps.
```
  

```python
from pybrainfuck import Brainfuck

if __name__ == '__main__':
    bf = Brainfuck() 
    bf.set_code(",[.,]")
    res = bf.analyze("ABCDEF")  # you can pass directly the input string as an argument.
    steps = bf.get_steps()

    print(f"{res}")
    print(f"{steps} steps.")
```
```text
ABCDEF
26 steps.
```
# Installation
1. **pip environment**
    ```shell script
    $ git clone https://github.com/HiroshiARAKI/pybrainfuck.git
    $ pip install ./pybrainfuck
    ```
1. **local environment**  
    After changing the python path in CMakeLists.txt, build the source code as below.
    ```shell script
    $ git clone https://github.com/HiroshiARAKI/pybrainfuck.git
    $ cd pybrainfuck
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    ```

# Environment
pynbind11 >= 2.4.0  
[https://github.com/pybind/pybind11](https://github.com/pybind/pybind11)

# LICENSE
MIT
