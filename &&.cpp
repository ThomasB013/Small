struct S {
    ~S() {
        cout << "Destructed\n";
    }
};

struct S10 {
    S* p = new S[10];
    ~S10() {
       delete[] p;
    }
};

void f(S&& s, const S& x) {
    cout << "f1(S&& s, const S& x)\n";
}

void f(const S& x, S&& s) {
    cout << "f2(const S& x, S&& s)\n";
    f(move(s), x);
}

void f(const S& x, const S& y) {
    cout << "f3(const S& x, const S& y)\n";
}

S x() {
    return S();
}

int main()
{
    S s1, s2, s3;
    f(s2, x());
}
