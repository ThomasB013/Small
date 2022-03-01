#include <iostream>
#include <string>

#define DEBUG "debug_helper debugger_info_some_variable_name_that_doesnt_clash"

//Syntax sugar for multiple spaces.
struct SPACES {
    unsigned count;
};

std::ostream& operator<<(std::ostream& os, SPACES p) {
    for(unsigned i = 0; i < p.count; ++i) // < to prevent people from overflowing e.g. by calling SPACES {-1}.
        os << ' ';
    return os;
}

//Function to print everything seperated by comma's.
void print_all(std::ostream&) {}

template<typename T>
void print_all(std::ostream& os, T t) { 
    os << t; 
} 

template<typename T, typename... Args>
void print_all(std::ostream& os, T t, Args... args) { 
    os << t << ", "; 
    print_all(os, args...); 
} 

class debug_helper {
public:
    static std::ostream& debug_out;
    const static unsigned SPACES_PER_LEVEL;

    template<typename... Args>
    debug_helper(const std::string& func_name_, Args... args) :func_name{func_name_}{
        debug_out << SPACES {level * SPACES_PER_LEVEL} << "start - " << func_name << '('; 
        print_all(debug_out, args...);
        debug_out << ")\n";
        ++level;
    }

    ~debug_helper() {
        --level;
        std::cout << SPACES {level * SPACES_PER_LEVEL} << "end - " << func_name << '\n';
    }
private:
    const std::string& func_name;
    static unsigned level;
};

std::ostream& debug_helper::debug_out = std::cout;
const unsigned debug_helper::SPACES_PER_LEVEL = 4;
unsigned debug_helper::level = 0;

void g(int i){
    debug_helper z{"g", i};
}

void g() {
    debug_helper z{"g"};
}

void f(int x) {
    debug_helper d{"f", x};
    int z = 1;
    for (int i = 0; i < x; ++i)
        z*=i;
    g(z);
    g();
}


int main() {
    debug_helper z{"main"};
    f(1);
    f(2);
    return 0;
}

/*
OUTPUT:
start - main()
    start - f(1)
        start - g(0)
        end - g
        start - g()
        end - g
    end - f
    start - f(2)
        start - g(0)
        end - g
        start - g()
        end - g
    end - f
end - main
*/
