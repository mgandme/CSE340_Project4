/*
 *  * Copyright (C) Rida Bazzi, 2017
 *   *
 *    * Do not share this file with anyone
 *     */
#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include "lexer.h"

class Parser {
    private:
	LexicalAnalyzer lexer;

        void syntax_error();
        Token expect(TokenType expected_type);
        Token peek();

        struct StatementNode* parse_program();
	void parse_var_section();
	struct ValueNode* parse_id_list();
	struct StatementNode* parse_body();
	struct StatementNode* parse_stmt_list();
	struct StatementNode* parse_stmt();
	struct AssignmentStatement* parse_assign_stmt();
	void parse_expr();
	struct ValueNode* parse_primary();
	void parse_op();
	void parse_print_stmt();
	void parse_while_stmt();
	struct IfStatement* parse_if_stmt();
	void parse_condition();
	void parse_relop();
	void parse_switch_stmt();
	void parse_for_stmt();
	void parse_case_list();
	void parse_case();
	void parse_default_case();
        struct StatementNode* parse_generate_intermediate_representation();

    public:
        void ParseInput();
};

#endif

