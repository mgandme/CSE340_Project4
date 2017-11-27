struct ValueNode {
    char *name;
    StatementType type;
    int val;	
}


struct AssignmentStatement {
    struct ValueNode *left_hand_side;
    struct ValueNode *operand1;
    struct ValueNode *operand2;
    ArithmeticOperatorType op;
    //struct AssignmentStatement *next;

}AssignmentStatement;

struct PrintStatement {
    struct ValueNode *id;

}PrintStatement;

struct StatementNode {
    StatementType type;   //Indicates what type of statement it is. ex: NOOP_STMT, GOTO_STMT, ASSIGN_STMT, IF_STMT, PRINT_STMT

    union {
	struct AssignmentStatement *assign_stmt;
	struct PrintStatement *print_stmt;
	struct IfStatement *if_stmt;
	struct GotoStatement *goto_stmt;
    };

    struct StatementNode *next;

}

//IF statement declaration

struct IfStatement {
    ConditionalOperatorType condition_op;
    struct ValueNode *condition_operand1;
    struct ValueNode *condition_operand2;
    
    struct StatementNode *trueBranch;
    struct StatementNOde *falseBranch;

}

//GOTO statement declaration

struct GotoStatement {
    struct StatementNode *target;
}

