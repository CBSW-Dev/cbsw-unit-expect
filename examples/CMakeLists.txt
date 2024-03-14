
add_executable(cbsw-unit-expect-example ${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY}/expect/main.cpp)
target_sources(cbsw-unit-expect-example PRIVATE
    "${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY}/expect/compare.unit.cpp"
    "${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY}/expect/greater-than.unit.cpp"
    "${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY}/expect/greater-than-or-equal.unit.cpp"
    "${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY}/expect/less-than.unit.cpp"
    "${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY}/expect/less-than-or-equal.unit.cpp"
    "${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY}/expect/include.unit.cpp"
    "${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY}/expect/null.unit.cpp"
    "${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY}/expect/boolean.unit.cpp"
)
target_link_libraries(cbsw-unit-expect-example cbsw-unit cbsw-unit-expect)

add_executable(cbsw-unit-extending-expect-example ${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY}/extending-expect/main.cpp)
target_sources(cbsw-unit-extending-expect-example PRIVATE
    "${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY}/extending-expect/extend-root.unit.cpp"
    "${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY}/extending-expect/extend-to.unit.cpp"
    "${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY}/extending-expect/extend-to-be.unit.cpp"
    "${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY}/extending-expect/extend-to-equal.unit.cpp"
    "${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY}/extending-expect/extend-to-be-null.unit.cpp"
    "${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY}/extending-expect/extend-to-be-boolean.unit.cpp"
    "${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY}/extending-expect/extend-to-include.unit.cpp"
)
target_link_libraries(cbsw-unit-extending-expect-example cbsw-unit cbsw-unit-expect)