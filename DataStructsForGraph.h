#include "lexer.h"
#include <string.h>


struct ValueNode {
    char *name;
    int value;
    struct ValueNode *next;
};


struct AssignmentStatement {
    struct ValueNode *left_hand_side;
    struct ValueNode *operand1;
    struct ValueNode *operand2;
    TokenType op;
    //struct AssignmentStatement *next;

};

struct PrintStatement {
    struct ValueNode *id;

};

struct StatementNode {
    TokenType type;   //Indicates what type of statement it is. ex: NOOP_STMT, GOTO_STMT, ASSIGN_STMT, IF_STMT, PRINT_STMT

    union {
	struct AssignmentStatement *assign_stmt;
	struct PrintStatement *print_stmt;
	struct IfStatement *if_stmt;
	struct GotoStatement *goto_stmt;
    };

    struct StatementNode *next;

};

//IF statement declaration

struct IfStatement {
    TokenType condition_op;
    struct ValueNode *condition_operand1;
    struct ValueNode *condition_operand2;
    
    struct StatementNode *trueBranch;
    struct StatementNOde *falseBranch;

};

//GOTO statement declaration

struct GotoStatement {
    struct StatementNode *target;
};

