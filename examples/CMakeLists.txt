
add_executable(cbsw-unit-expect-example ${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY}/expect/main.cpp)
target_sources(cbsw-unit-expect-example PRIVATE
    "${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY}/expect/compare.unit.cpp"
    "${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY}/expect/greater-than.unit.cpp"
    "${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY}/expect/greater-than-or-equal.unit.cpp"
    "${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY}/expect/less-than.unit.cpp"
    "${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY}/expect/less-than-or-equal.unit.cpp"
    "${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY}/expect/include.unit.cpp"
    "${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY}/expect/null.unit.cpp"
)
target_link_libraries(cbsw-unit-expect-example cbsw-unit cbsw-unit-expect)