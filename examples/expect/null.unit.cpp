#include "test.hpp"

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
    }
}