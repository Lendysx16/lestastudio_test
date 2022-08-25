#pragma once

class nothing_to_pop_exepction: public std::exception{
    virtual const char* what() const noexcept{
        return "The buffer is empty";
    }
};