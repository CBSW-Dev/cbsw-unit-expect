#include "test.hpp"

#include <cstring>

suite() {
    describe("Include") {
        it("demonstrates a passing test with an array and valid value") {
            int array[5] = {1,2,3,4,5};
            expect(array).to.include(2);
        }

        it("demonstrates a failing test with an array and valid value") {
            int array[5] = {1,2,3,4,5};
            expect(array).to.include(6);
        }

        it("demonstrates a passing test with a cstring array and a character") {
            char cstring[6];
            std::memcpy(cstring, "Hello", 6);

            expect(cstring).to.include('e');
        }

        it("demonstrates a failing test with a cstring array and a character") {
            char cstring[6];
            std::memcpy(cstring, "Hello", 6);

            expect(cstring).to.include('x');
        }

        it("demonstrates a passing test with a cstring pointer and a character") {
            char* cstring = (char*)::malloc(6);
            std::memcpy(cstring, "Hello", 6);

            expect(cstring).to.include('e');
            ::free(cstring);
        }

        it("demonstrates a failing test with a cstring pointer and a character") {
            //N.B. these failing tests create leaks, RAII is better here
            char* cstring = (char*)malloc(6);
            std::memcpy(cstring, "Hello", 6);

            expect(cstring).to.include('x');
            ::free(cstring);
        }

        it("demonstrates a passing test with a cstring pointer and a cstring pointer") {
            char* cstring = (char*)::malloc(6);
            std::memcpy(cstring, "Hello", 6);

            expect(cstring).to.include("ell");
            ::free(cstring);
        }

        it("demonstrates a failing test with a cstring pointer and a cstring pointer") {
            //N.B. these failing tests create leaks, RAII is better here
            char* cstring = (char*)malloc(6);
            std::memcpy(cstring, "Hello", 6);

            expect(cstring).to.include("elp");
            ::free(cstring);
        }

        it("demonstrates a passing test with a std::string and a character") {
            std::string string = "Hello";

            expect(string).to.include('l');
        }

        it("demonstrates a failing test with a std::string and a character") {
            std::string string = "Hello";

            expect(string).to.include('p');
        }

        it("demonstrates a passing test with a std::string and a cstring array") {
            std::string string = "Hello";

            expect(string).to.include("el");
        }

        it("demonstrates a failing test with a std::string and a cstring array") {
            std::string string = "Hello";

            expect(string).to.include("elp");
        }

        it("demonstrates a passing test with a std::string and a cstring pointer") {
            std::string string = "Hello";
            char* cstring = (char*)::malloc(3);
            std::memcpy(cstring, "el", 3);

            expect(string).to.include(cstring);

            ::free(cstring);
        }

        it("demonstrates a failing test with a std::string and a cstring pointer") {
            std::string string = "Hello";
            char* cstring = (char*)::malloc(4);
            std::memcpy(cstring, "elp", 4);

            expect(string).to.include(cstring);

            ::free(cstring);
        }

        it("demonstrates a passing test with a std::string and std::string") {
            std::string string = "Hello";
            std::string other = "el";

            expect(string).to.include(other);
        }

        it("demonstrates a failing test with a std::string and std::string") {
            std::string string = "Hello";
            std::string other = "elp";

            expect(string).to.include(other);;
        }

        it("demonstrates a passing test with an iterable stl container(vector) and an element") {
            std::vector<int> vector = {1,2,3,4,5,6};

            expect(vector).to.include(3);
        }

        it("demonstrates a failing test with an iterable stl container(vector) and an element") {
            std::vector<int> vector = {1,2,3,4,5,6};

            expect(vector).to.include(25);
        }

        it("demonstrates a passing test with an iterable stl container(list) and an element") {
            std::list<int> list = {1,2,3,4,5,6};

            expect(list).to.include(3);
        }

        it("demonstrates a failing test with an iterable stl container(list) and an element") {
            std::list<int> list = {1,2,3,4,5,6};

            expect(list).to.include(25);
        }

        it("demonstrates a passing test with an iterable stl container(vector) and another stl container(vector)") {
            std::vector<int> vector = {1,2,3,4,5,6};
            std::vector<int> other = {2,3};

            expect(vector).to.include(other);
        }

        it("demonstrates a failing test with an iterable stl container(vector) and another stl container(vector)") {
            std::vector<int> vector = {1,2,3,4,5,6};
            std::vector<int> other = {2,4};

            expect(vector).to.include(other);
        }

        it("demonstrates a passing test with an iterable stl container(vector) and a different stl container(list)") {
            std::vector<int> vector = {1,2,3,4,5,6};
            std::list<int> other = {2,3};

            expect(vector).to.include(other);
        }

        it("demonstrates a failing test with an iterable stl container(vector) and a different stl container(list)") {
            std::vector<int> vector = {1,2,3,4,5,6};
            std::list<int> other = {2,4};

            expect(vector).to.include(other);
        }
    }
}

//stream operator for an integer array
template <int N> std::ostream& operator << (std::ostream& stream, const int(&array)[N]) {
    if (N == 0) {
        return stream << "[]";
    }
    stream << "[";
    stream << array[0];
    for (int i = 1; i < N; ++i) {
        stream << "," << array[i];
    }
    return stream << "]";
}

//stream operator for an stl vector
template <class T> std::ostream& operator << (std::ostream& stream, const std::vector<T>& vector) {
    if (vector.size() == 0) {
        return stream << "vector[]";
    }
    stream << "vector[";
    auto it = vector.begin();
    stream << *it;
    ++it;
    for (; it != vector.end(); ++it) {
        stream << "," << *it;
    }

    return stream << "]";
}


//stream operator for an stl list
template <class T> std::ostream& operator << (std::ostream& stream, const std::list<T>& list) {
    if (list.size() == 0) {
        return stream << "list[]";
    }
    stream << "list[";
    auto it = list.begin();
    stream << *it;
    ++it;
    for (; it != list.end(); ++it) {
        stream << "," << *it;
    }

    return stream << "]";
}