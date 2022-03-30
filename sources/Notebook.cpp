#include "Direction.hpp"
#include "Notebook.hpp"
#include <string>
#include <iostream>
using namespace std;
const int ROWLEN = 100;
const int MAX = 126;
const int MIN = 32;

namespace ariel 
{
        Notebook::Notebook() { }

        bool Notebook::invalid_location(int page, int row, int column, Direction direction,const string &text) {
            int text_length = text.length();

            if (direction == Direction::Vertical) 
            {
                for (int j = row; j < row + text_length; j++) 
                {
                    unsigned int position = (unsigned int)(column);
                    string temp = this->notebook_map.at(page).at(j);
                    if (temp.at(position) != '_') 
                    {
                        return true;
                    }
                }
            }
            else 
            {
                string string_temp = this->notebook_map.at(page).at(row);
                for (int j = column; j < column + text_length; j++) 
                {
                    unsigned int position = (unsigned int)(j);
                    if (string_temp[position] != '_') 
                    {
                        return true;
                    }
                }
            }
            return false;
        }

        void Notebook::add_new_row(int row, int page) {
            if (this->notebook_map.find(page) != this->notebook_map.end()) {
                if (this->notebook_map[page].find(row) == this->notebook_map[page].end()) 
                {
                    string newLine(ROWLEN, '_');
                    this->notebook_map[page][row] = newLine;
                }
            }

            if (this->notebook_map.find(page) == this->notebook_map.end()) {
                if (this->notebook_map[page].find(row) == this->notebook_map[page].end()) 
                {
                    string newLine(ROWLEN, '_');
                    this->notebook_map[page][row] = newLine;
                }
            }
        }

         bool invalid_characters_in_text(const string &text)
        {
            int text_length = text.length();
            for (unsigned int position = 0; position < text_length; position++)
            {
                if (text.at(position) < MIN || text.at(position) > MAX) 
                {
                    return true;
                }
            }
            return false;
        }

         void Notebook::write(int page, int row, int column, Direction direction, string text)
         {
            for(unsigned int i = 0 ; i < text.size();i++){
                if(text[i]=='~'){
                    throw std::invalid_argument(" ");
                }
            }

             int text_length = text.length();

             if (row < 0 || column < 0 || page < 0 || column > ROWLEN)
             {
                 throw std::invalid_argument{ "Negative row,column or page value!" };
             }
             if (text_length == 0)
             {
                 throw std::invalid_argument{ "Current Text is empty!" };
             }
             if (invalid_characters_in_text(text))
             {
                 throw std::invalid_argument{ "Current Text have invalid characters!" };
             }
             if (text_length > ROWLEN && direction == ariel::Direction::Horizontal)
             {
                 throw std::invalid_argument{ "Cant read more than 100 in one line!" };
             }


             if (direction == Direction::Vertical)
             {
                 for (int curr_row = row; curr_row < row + text_length; curr_row++)
                 {
                     add_new_row(curr_row, page);
                 }
             }
             else 
             {
                 add_new_row(row,page);
             }

             if (invalid_location(page, row, column, direction, text)) 
             {
                 throw std::invalid_argument{ "This position is already taken!" };
             }

             if (direction == Direction::Vertical) 
             {
                 for (int j = row; j < row + text_length; j++)
                 {
                     unsigned int Column = (unsigned int)(column);
                     unsigned int text_position = (unsigned int)(j - row);
                     this->notebook_map.at(page).at(j)[Column] = text[text_position];
                 }
             }
             else 
             {
                 for (int j = column; j < column + text_length; j++)
                 {
                     unsigned int position = (unsigned int)(j);
                     unsigned int text_position = (unsigned int)(j - column);
                     this->notebook_map.at(page).at(row)[position] = text[text_position];
                 }
             }
         }
         string Notebook::read(int page, int row, int column, Direction direction, int length)
         {
             string val;

             if (row < 0 || column < 0 || page < 0 || column > ROWLEN) 
             {
                 throw std::invalid_argument{ "Negative row,column or page value!" };
             }
             if (column + length > ROWLEN + 1) 
             {
                 throw std::invalid_argument{ "Column value is more than max!" };
             }
             if (length <= 0) 
             {
                 throw std::invalid_argument{ "Cant read 0 characters or less!" };
             }
             if (length > ROWLEN && direction == ariel::Direction::Horizontal) 
             {
                 throw std::invalid_argument{ "Cant read more than 100 in one line!" };
             }

             if (direction == Direction::Vertical)
             {
                 for (int curr_row = row; curr_row < row + length; curr_row++)
                 {
                     add_new_row(curr_row, page);
                 }

                 for (int j = 0; j < length; j++) //delete values from notebook_map
                 {
                     unsigned int Delete_Column = (unsigned int)(column);
                     val += this->notebook_map.at(page).at(row + j)[Delete_Column];
                 }
             }
             else 
             {
                 add_new_row(row, page);

                 for (int j = 0; j < length; j++) //delete values from notebook_map
                 {
                     unsigned int curr_position = (unsigned int)(column + j);
                     val += this->notebook_map.at(page).at(row)[curr_position];
                 }
             }

             return val;
         }
         void Notebook::erase(int page, int row, int column, Direction direction, int length)
         {


             if (row < 0 || column < 0 || page < 0 || column > ROWLEN)
             {
                 throw std::invalid_argument{ "Negative row,column or page value!" };
             }
             if (column + length > ROWLEN + 1)
             {
                 throw std::invalid_argument{ "Column value is more than max!" };
             }
             if (length <= 0)
             {
                 throw std::invalid_argument{ "Cant read 0 characters or less!" };
             }
             if (length > ROWLEN && direction == ariel::Direction::Horizontal)
             {
                 throw std::invalid_argument{ "Cant read more than 100 in one line!" };
             }

             if (direction == Direction::Vertical)
             {
                 for (int j = row; j < row + length; j++) 
                 {
                     add_new_row(j,page);
                 }

                 for (int curr_row = row; curr_row < row + length; curr_row++)
                 {
                     unsigned int delete_column = (unsigned int)(column);
                     this->notebook_map.at(page).at(curr_row)[delete_column] = '~';
                 }
             }
             else
             {
                 if(column+length>ROWLEN){
                     throw std::invalid_argument("error");
                 }
                 add_new_row(row,page); 

                 for (int j = column; j < column + length; j++) //delete values from notebook_map
                 {
                     unsigned int curr_position = (unsigned int)(j);
                     this->notebook_map.at(page).at(row)[curr_position] = '~';
                 }
             }
         }
         void Notebook::show(int page) 
         {
             string empty(ROWLEN, '_');
             string answer;
             if (page < 0) 
             {
                 throw std::invalid_argument{ "Page value cant be negative!" };
             }
             std::map<int, string> ::iterator itr;
             try 
             {
                 for (itr = this->notebook_map.at(page).begin(); itr != this->notebook_map.at(page).end(); itr++)
                 {
                     answer += itr->second;
                     answer += '\n';
                 }
             }
             catch (exception ex) 
             {
                 answer = ' ';
             }
         }   
}