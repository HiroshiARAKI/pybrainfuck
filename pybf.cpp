#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;

#include <stack>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

constexpr int MEMORY = 1024;  //! the size of memory

constexpr char INCREMENT =  '+';
constexpr char DECREMENT =  '-';
constexpr char RIGHT =  '>';
constexpr char LEFT =  '<';
constexpr char LOOP_START =  '[';
constexpr char LOOP_END =  ']';
constexpr char OUTPUT =  '.';
constexpr char INPUT =  ',';

class Brainfuck{
private:
    unsigned char memory[MEMORY]{};       //! the memory that consists of char, 1Byte=8bit variables (0~255)
    unsigned int ptr = 0;                 //! the pointer of the memory
    unsigned int code_ptr = 0;            //! the pointer of Brainfuck code
    unsigned int code_len = 0;            //! Brainfuck code length (the end of code pointer)
    string code = "";                     //! Brainfuck code
    stack<int> loops;                     //! stacks loops-start "[" pointers

    unsigned int steps = 0;

public:
    Brainfuck();
    Brainfuck(string filename);
    string analyze();

    void set_code(string code){ this->code_len = code.size(); this->code = code; }
    string get_code(){ return this->code; }
    unsigned int get_ptr(){ return this->ptr; }
    unsigned int get_code_ptr(){ return this->code_ptr; }
    vector<unsigned int> get_memory();
    unsigned int get_steps(){ return this->steps; }
};

Brainfuck::Brainfuck() {
    memset(this->memory, 0, sizeof(this->memory));
}
Brainfuck::Brainfuck(string filename) {
    memset(this->memory, 0, sizeof(this->memory));
    ifstream file(filename);
    if (!file){
        cerr << "Error: The file \"" << filename << "\" cannot be opened." << endl;
        return;
    }
    stringstream buffer;
    buffer << file.rdbuf();
    string _code(buffer.str());
    this->code_len = _code.size();
    this->code = _code;
}
string Brainfuck::analyze() {
    string result;
    while (code_ptr < code_len) {
        steps++;
        switch (code[code_ptr]) {
            case INCREMENT:
                memory[ptr]++;
                break;
            case DECREMENT:
                memory[ptr]--;
                break;
            case RIGHT:
                ptr = (ptr >= MEMORY - 1) ? 0 : ptr + 1;
                break;
            case LEFT:
                ptr = (ptr <= 0) ? MEMORY - 1 : ptr - 1;
                break;
            case LOOP_START:
                loops.push(code_ptr);
                if (memory[ptr] == 0) {
                    int depth = 1;
                    while (depth > 0) {
                        code_ptr++;
                        if (code_ptr >= code_len) {
                            cerr << "Error: Cannot find \"]\"." << endl;
                            return "";
                        }
                        if (code[code_ptr] == LOOP_START) depth++;
                        if (code[code_ptr] == LOOP_END)   depth--;
                    }
                    loops.pop();
                }
                break;
            case LOOP_END:
                if (loops.empty()){
                    cerr << "Error: Loop start order [ is not found." << endl;
                    return "";
                }
                code_ptr = loops.top() - 1;
                loops.pop();
                break;
            case OUTPUT:
                result += memory[ptr];
                break;
            case INPUT:
                memory[ptr] = getchar();
                break;
            default:
                break;
        }
        code_ptr++;
    }
    return result;
}
vector<unsigned int> Brainfuck::get_memory() {
    vector<unsigned int> mem;
    for(auto m: this->memory)
        mem.push_back(m);
    return mem;
}

PYBIND11_MODULE(pybrainfuck, bf)
{
    bf.doc() = "You can analyze Brainfuck code quickly, using this module implemented with C++.";
    py::class_<Brainfuck>(bf, "Brainfuck")
            .def(py::init(), "The constructor in the case that you give the BF code later.")
            .def(py::init<string>(), "The constructor in the case that you give the BF code file now.", py::arg("filename"))
            .def("analyze", &Brainfuck::analyze, "analyze BF code and return the result")
            .def("set_code", &Brainfuck::set_code, "set row BF code", py::arg("code"))
            .def("get_code", &Brainfuck::get_code, "get row BF code")
            .def("get_ptr", &Brainfuck::get_ptr, "get a current pointer of memory")
            .def("get_code_ptr", &Brainfuck::get_code_ptr, "get a current pointer of BF code")
            .def("get_memory", &Brainfuck::get_memory, "get a memory status as list")
            .def("get_steps", &Brainfuck::get_steps, "get final analyzing step counts");
}