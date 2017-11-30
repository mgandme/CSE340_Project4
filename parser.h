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

    void parse_program();
	void parse_var_section();
	struct ValueNode* parse_id_list();
	struct StatementNode* parse_body();
	struct StatementNode* parse_stmt_list();
	void parse_stmt();
	void parse_assign_stmt();
	void parse_expr();
	void parse_primary();
	void parse_op();
	void parse_print_stmt();
	void parse_while_stmt();
	void parse_if_stmt();
	void parse_condition();
	void parse_relop();
	void parse_switch_stmt();
	void parse_for_stmt();
	void parse_case_list();
	void parse_case();
	void parse_default_case();
//old stuff
/*
        void parse_scope();
        void parse_scope_list();
        void parse_declaration();
        void parse_type_decl();
        void parse_type_name();
        void parse_var_decl();
        void parse_id_list();
        void parse_stmt_list();
        void parse_stmt();                                                              
        void parse_assign_stmt();
        void parse_while_stmt();
        void parse_expr();
        void parse_term();
        void parse_factor();
        void parse_condition();
        void parse_primary();
        void parse_relop();
*/
    public:
        void ParseInput();
};

#endif

