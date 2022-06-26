#include <iostream>

struct Coord {
    size_t row, col;
};

struct RowWise_Iterator {
    RowWise_Iterator(size_t crow, size_t ccol, size_t max_col) : cur_row{crow}, cur_col{ccol}, max_cols{max_col} {}

    RowWise_Iterator operator++() {
        cur_col = (cur_col + 1) % max_cols; //Branchless = better ?
        cur_row += (cur_col == 0);
        return *this;
    }

    Coord operator*() const { return Coord{cur_row, cur_col}; }
    bool operator!=(RowWise_Iterator r) const { return r.cur_col != cur_col || r.cur_row != cur_row; }

    size_t cur_row = 0, cur_col = 0;
    const size_t max_cols; 
};

struct RowWise {
    RowWise(size_t max_row, size_t max_col) : max_rows{max_row}, max_cols{max_col} {}

    RowWise_Iterator begin() const { return RowWise_Iterator{0, 0, max_cols}; }
    RowWise_Iterator end() const { return RowWise_Iterator{max_rows, 0, max_cols}; }
    const size_t max_rows, max_cols;
};

int main() {
    for(const auto pos : RowWise{3, 5}) {
        std::cout << "Row: " << pos.row << ", Col: " << pos.col << '\n';
    }
    return 0;
}