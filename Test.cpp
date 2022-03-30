#include "doctest.h"
#include "Notebook.hpp"
#include "Direction.hpp"
#include <stdexcept>

using namespace ariel;
using namespace std;

Notebook notebook;

    TEST_CASE("write to written or deleted position"){
    //Trying to write on writen pos: horizontal and vertical
    notebook.write(7,0,0,Direction::Horizontal,"lior");
    CHECK_THROWS(notebook.write(7,0,0,Direction::Horizontal,"lior"));
    CHECK_THROWS(notebook.write(7,0,0,Direction::Vertical,"lior"));
    CHECK_THROWS(notebook.write(7,0,2,Direction::Vertical,"lior"));
    CHECK_THROWS(notebook.write(7,0,3,Direction::Vertical,"lior"));
    CHECK_THROWS(notebook.write(7,0,2,Direction::Horizontal,"lior"));
    CHECK_THROWS(notebook.write(7,0,3,Direction::Horizontal,"lior"));

    //Trying to write on erased pos: horizontal and vertical
    notebook.erase(7,0,0,Direction::Horizontal,5);
    CHECK_THROWS(notebook.write(7,0,0,Direction::Horizontal,"lior"));
    CHECK_THROWS(notebook.write(7,0,0,Direction::Vertical,"lior"));
    CHECK_THROWS(notebook.write(7,0,2,Direction::Vertical,"lior"));
    CHECK_THROWS(notebook.write(7,0,3,Direction::Vertical,"lior"));
    CHECK_THROWS(notebook.write(7,0,2,Direction::Horizontal,"lior"));
    CHECK_THROWS(notebook.write(7,0,3,Direction::Horizontal,"lior"));
}

TEST_CASE("valid position") {
    //write function
    CHECK_THROWS(notebook.write(-100, 100, 50, Direction::Horizontal, "lior"));
    CHECK_THROWS(notebook.write(65, -100, 51, Direction::Horizontal, "lior"));
    CHECK_THROWS(notebook.write(100, 99, 52, Direction::Horizontal, "lior"));
    CHECK_THROWS(notebook.write(100, 99, 51, Direction::Horizontal, "lior"));
    CHECK_THROWS(notebook.write(100, 99, 50, Direction::Horizontal, "lior"));
    CHECK_THROWS(notebook.write(-55, 85, -30, Direction::Horizontal, "lior"));
    CHECK_THROWS(notebook.write(100, -99, -50, Direction::Horizontal, "lior"));
    CHECK_NOTHROW(notebook.write(50, 50, 51, Direction::Horizontal, "abramovichh"));
    CHECK_THROWS(notebook.write(50, 50, 101, Direction::Horizontal, "lior"));

    //read function
    CHECK_THROWS(notebook.read(-55, 85, -30, Direction::Horizontal, 3));
    CHECK_THROWS(notebook.read(65, -100, 51, Direction::Horizontal, -3));
    CHECK_THROWS(notebook.read(100, -99, -50, Direction::Horizontal, 3));
    CHECK_THROWS(notebook.read(-100, 100, 50, Direction::Horizontal, 3));
    CHECK_THROWS(notebook.read(50, 50, -1, Direction::Horizontal, 5));
    CHECK_THROWS(notebook.read(50, 50, 101, Direction::Horizontal, 5));
    CHECK_THROWS(notebook.read(50, 50, 101, Direction::Horizontal, 101));

    //erase function
    CHECK_THROWS(notebook.erase(100, -99, -50, Direction::Horizontal, 3));
    CHECK_THROWS(notebook.erase(-55, 85, -30, Direction::Horizontal, 3));
    CHECK_THROWS(notebook.erase(100, 99, 50, Direction::Horizontal, 3));
    CHECK_THROWS(notebook.erase(65, -100, 51, Direction::Horizontal, -3));
    CHECK_THROWS(notebook.erase(100, 99, 51, Direction::Horizontal, 3));
    CHECK_THROWS(notebook.erase(-100, 100, 50, Direction::Horizontal, 3));
    CHECK_THROWS(notebook.erase(50, 50, 101, Direction::Horizontal, 101));
    CHECK_THROWS(notebook.erase(50, 50, 101, Direction::Horizontal, 5));
    
    Notebook notebook2;
    notebook2.write(0,0,0,Direction::Horizontal,"lior");
    CHECK(notebook2.read(0,0,0,Direction::Horizontal,4)=="lior");
    CHECK(notebook2.read(0,0,0,Direction::Horizontal,5)=="lior_");
    CHECK(notebook2.read(0,0,1,Direction::Horizontal,3)=="ior");
    CHECK(notebook2.read(0,0,1,Direction::Horizontal,5)=="_ior_");
    CHECK(notebook2.read(2,2,2,Direction::Horizontal,4)=="____");
   }