#include <string>
#include "Direction.hpp"
#include <map>
using namespace std;

namespace ariel 
{
    bool invalid_characters_in_text(const string &text);
    
    class Notebook 
    {   
            // private:
            // map<int,int> temp;

        public:
            Notebook();
            map<int,map<int,string>> notebook_map;
            bool invalid_location(int page, int row, int column, Direction direction,const string &text);
            void add_new_row(int row, int page);
            void write(int page, int row, int column, Direction direction, string text);
            string read(int page, int row, int column, Direction direction, int length);
            void erase(int page, int row, int column, Direction direction, int length);
            void show(int page);
    };
}