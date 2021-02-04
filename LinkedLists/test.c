#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "llist.h"

// Precondition: len > 0
Node *list_from_array(const int *values, size_t len) {
    Node *head = newNode(values[0]);

    Node *cur_Node = head;
    for (size_t i = 1; i < len; i++) {
        cur_Node = linsert(cur_Node, values[i]);
    }

    return head;
}

#define list_from_imm(...) ({ \
    int vals[] = {__VA_ARGS__}; \
    size_t len = sizeof(vals) / sizeof(int); \
    list_from_array(vals, len); })

bool Node_sanity_check(const Node *n) {
    bool sane = true;

    if(n->prev && n->prev->next != n) {
        printf("[Node @ %p (value: %d)] is not its prev Node's next!\n", n, n->val);
        sane = false;
    }

    if(n->next && n->next->prev != n) {
        printf("[Node @ %p (value %d)] is not its next Node's prev!\n", n, n->val);
        sane = false;
    }

    return sane;
}

bool list_sanity_check(const Node *head) {
    bool sane = true;

    if(head->prev != NULL) {
        printf("[Node @ %p (value %d)] purports to be the head, but has a prev!\n", head, head->val);
        sane = false;
    }

    const Node *n = head->next;
    while(n != NULL) {
        sane = sane && Node_sanity_check(n);
        n = n->next;
    }

    return sane;
}


#define assert_msg(expr, msg) do { \
        typeof(expr) res = (expr); \
        if(!res) { \
            puts("💥 Test failed: " msg "\n"); \
            puts("The expression that failed is:\n" #expr); \
            printf("(line %d in %s in %s)\n", __LINE__, __FUNCTION__, __FILE__); \
            exit(1); \
        } \
    } while(0)

#define assert_sane(head, ctx) assert_msg(list_sanity_check(head), "list is not linked correctly after " ctx " - see details above")

#define pass(msg) puts("👍 " msg " looks good!")


void test_newNode() {
    Node *head = newNode(5);
    assert_msg(
        head != NULL && head->val == 5 && head->next == NULL && head->prev == NULL,
        "newNode should make a standalone Node with the given value");
    
    free(head);

    pass("newNode");
}

void test_insert_at_end() {
    Node *head = newNode(1);
    Node *new_Node = linsert(head, 2);

    assert_msg(new_Node != NULL && new_Node->val == 2,
        "linsert should return the newly created Node");
    
    assert_msg(head->next == new_Node && new_Node->prev == head && new_Node->next == NULL,
        "linsert should correctly insert a Node at the end of the list");
    
    assert_sane(head, "linsert at end");

    free(head);
    free(new_Node);

    pass("linsert at the end of the list");
}

void test_insert_in_middle() {
    Node *head = newNode(1);

    // We've already tested this use of linsert, so we know it works
    Node *three = linsert(head, 3);

    // This the new use case we want to test, since head is now followed by something
    Node *two = linsert(head, 2);

    assert_msg(head->next == two && two->next == three,
        "linsert should correctly insert a Node in the middle of the list");
    
    assert_sane(head, "linsert in middle");

    free(head);
    free(two);
    free(three);

    pass("linsert in the middle of the list");
}

void test_find() {
    // Since we've tested linsert now, we can use things that
    // rely on list_from_array, like this macro:
    Node *head = list_from_imm(1, 2, 3, 3, 4);
    Node *two = head->next;
    Node *three = two->next;
    Node *second_three = three->next;
    Node *four = second_three->next;

    assert_msg(lfind(head, 1) == head,
        "lfind should return the head Node if it matches");
    
    assert_msg(lfind(head, 2) == two,
        "lfind should return a matching Node in the list");
    
    assert_msg(lfind(head, 3) == three,
        "lfind should return the *first* Node with a matching value");

    assert_msg(lfind(head, 4) == four,
        "lfind should return the tail Node if it matches");
    
    assert_msg(lfind(head, 5) == NULL,
        "lfind should return NULL if no matching Node is found");
    
    assert_sane(head, "lfind");

    free(head);
    free(two);
    free(three);
    free(second_three);
    free(four);

    pass("lfind");
}

void test_remove_head() {
    Node *head = list_from_imm(1, 2);
    Node *two = head->next;

    ldelete(head);
    assert_msg(two->prev == NULL,
        "calling ldelete on the head should set the next Node's prev to NULL");
    
    assert_sane(two, "ldelete of head Node");

    // ldelete should also have freed head,
    // but we have no portable way to check that

    free(two);

    pass("ldelete on the head of a list");
}

void test_remove_tail() {
    Node *head = list_from_imm(1, 2);
    Node *two = head->next;

    ldelete(two);
    assert_msg(head->next == NULL,
        "calling ldelete on the final Node should behave appropriately");
    
    assert_sane(head, "ldelete of final Node");

    free(head);

    pass("ldelete on the final Node of a list");
}

void test_remove_in_middle() {
    Node *head = list_from_imm(1, 2, 0, 3);
    Node *two = head->next;
    Node *outlier = two->next;
    Node *three = outlier->next;

    ldelete(outlier);
    assert_msg(two->next == three && three->prev == two,
        "ldelete should correctly remove a Node in the middle of a list");
    
    assert_sane(head, "ldelete in middle");

    free(head);
    free(two);
    free(three);

    pass("ldelete in the middle of a list");
}


int main(int argc, char *argv[]) {
    test_newNode();
    puts("Test newNode Passed!");
    test_insert_at_end();
    puts("Test test_insert_at_end Passed!");
    test_insert_in_middle();
    puts("Test  test_insert_in_middle Passed!");
    test_find();
    puts("Test test_find Passed!");
    test_remove_head();
    puts("Test test_remove_head Passed!");
    test_remove_tail();
    puts("Test test_remove_tail Passed!");
    test_remove_in_middle();
    puts("Test test_remove_in_middle Passed!");

    puts("\n🎉 YOU DID IT 🎉\n");

    puts("... Well, probably!");
    puts("It's hard to test that you freed things appropriately.");
    puts("Make sure your ldelete and lfree do the right");
    puts("thing before you submit.");

    return 0;
}