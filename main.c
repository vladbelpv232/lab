void test() {
    test_pushBack_emptyVector();
    test_pushBack_fullVector();
}
void test_popBack_notEmptyVector() {
    vector v = createVector(0);
    pushBack(&v, 10);
    assert(v.size == 1);
    popBack(&v);
    assert(v.size == 0);
    assert(v.capacity == 1);
}
void test_atVector_notEmptyVector();
void test_atVector_requestToLastElement()34;
void test_back_oneElementInVector().
void test_front_oneElementInVector().