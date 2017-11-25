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



