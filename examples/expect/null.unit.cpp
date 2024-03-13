#include "test.hpp"

namespace {
    class TestNull {
    public:
        TestNull(void* pointer):
            _pointer(pointer)
        {}

        operator void*() const {
            return _pointer;
        }

        void* _pointer;
    };
}

suite() {
    describe("Null") {
        it("demonstrates a passing test with a nullable pointer") {
            int* pointer = nullptr;
            expect(pointer).to.be.null();
        }

        it("demonstrates a failing test with a nullable pointer") {
            int valid = 5;
            int* pointer = &valid;
            expect(pointer).to.be.null();
        }

        it("demonstrates a failing test with a non nullable object") {
            int notAPointer = 5;
            expect(notAPointer).to.be.null();
        }

        it("demonstrates a passing test with a nullable object") {
            TestNull testNull(nullptr);
            expect(testNull).to.be.null();
        }
    }
}