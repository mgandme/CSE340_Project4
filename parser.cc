/*
 * Copyright (C) Rida Bazzi, 2017
 *
 * Do not share this file with anyone
 *
 * Do not post this file or derivatives of 
 * of this file online
 *
 */
#include <iostream>
#include <cstdlib>
#include "parser.h"
#include <string.h>
/*
 *DATE : NOV. 4
 *TIME : 11:57 AM
 *
 *
 *PARSING        : 83 / 83
 *
 *Error Code 1.X : 0 / 12
 *
 *Error Code 2.X : 0 / 7
 *
 *Type Mismatch  : 0 / 20
 *
 *Semantic OK    : 0 / 22
*/




using namespace std;

void Parser::syntax_error()
{
    cout << "Syntax Error\n";
    exit(1);
}

// this function gets a token and checks if it is
// of the expected type. If it is, the token is
// returned, otherwise, synatx_error() is generated
// this function is particularly useful to match
// terminals in a right hand side of a rule.
// Written by Mohsen Zohrevandi
Token Parser::expect(TokenType expected_type)
{
    Token t = lexer.GetToken();
    if (t.token_type != expected_type)
        syntax_error();
    return t;
}

// this function simply checks the next token without
// consuming the input
// Written by Mohsen Zohrevandi
Token Parser::peek()
{
    Token t = lexer.GetToken();
    lexer.UngetToken(t);
    return t;
}
















//old stuff
//
/*
void Parser::parse_program()
{
    // program -> scope
    
    parse_scope();
}

void Parser::parse_scope()
{
    // scope -> { scope_list }
    
    expect(LBRACE);
    parse_scope_list();
    expect(RBRACE);
    
    //ending scope variable?
}


void Parser::parse_scope_list()
{
    // scope_list -> stmt
    // scope_list -> scope
    // scope_list -> declaration
    // scope_list -> stmt scope_list
    // scope_list -> scope scope_list
    // scope_list -> declaration scope_list


    Token t = peek();

    if(t.token_type == ID || t.token_type == WHILE) {
	parse_stmt();
	t = peek();

	if(t.token_type == ID || t.token_type == WHILE
	|| t.token_type == TYPE || t.token_type == VAR
	|| t.token_type == LBRACE) {
	    parse_scope_list();
	}
    }
    else if(t.token_type == TYPE || t.token_type == VAR) {
	parse_declaration();
	t = peek();        

	if(t.token_type == ID || t.token_type == WHILE
        || t.token_type == TYPE || t.token_type == VAR
        || t.token_type == LBRACE) {
            parse_scope_list();
        }
    }
    else if(t.token_type == LBRACE) {
	parse_scope();
	t = peek();
	
        if(t.token_type == ID || t.token_type == WHILE
        || t.token_type == TYPE || t.token_type == VAR
        || t.token_type == LBRACE) {
            parse_scope_list();
        }

    }
    else {
	syntax_error();
    }
}

void Parser::parse_declaration()
{
    // declaration -> type_decl
    // declaration -> var_decl

    Token t = peek();
    if (t.token_type == TYPE)
    	parse_type_decl();
    if (t.token_type == VAR)
    	parse_var_decl();
}

void Parser::parse_type_decl()
{
    // type_decl -> TYPE id_list COLON type_name SEMICOLON

    expect(TYPE);
    parse_id_list();
    expect(COLON);
    parse_type_name();
    expect(SEMICOLON);
}

void Parser::parse_type_name()
{
    // type_name -> REAL
    // type_name -> INT
    // type_name -> BOOLEAN
    // type_name -> STRING
    // type_name -> LONG
    // type_name -> ID

    Token t = lexer.GetToken();
    if(t.token_type != REAL && t.token_type != INT &&
    t.token_type != BOOLEAN && t.token_type != STRING &&
    t.token_type != LONG && t.token_type != ID) {
	syntax_error();
    }
}

void Parser::parse_var_decl()
{
    // var_decl -> VAR id_list COLON type_name SEMICOLON

    expect(VAR);
    currScope->table = parse_id_list();
    expect(COLON);
    parse_type_name();
    expect(SEMICOLON);
}

void Parser::parse_id_list()
{
    // id_list -> ID
    // id_list -> ID COMMA id_list

    Token curr = peek();
    expect(ID);
    Token t = peek();
    if(t.token_type == COMMA) {
	expect(COMMA);
        return var;
    }
    else {
	var->line_no = curr.line_no;
	char *c = curr.lexeme;
	var->name.assign(c, sizeof(curr.lexeme));
	return var;
    }
    
}


void Parser::parse_stmt_list()
{
    // stmt_list -> stmt
    // stmt_list -> stmt stmt_list
    
    parse_stmt();
    Token t = peek();
    if (t.token_type == WHILE || t.token_type == ID)
    {
        // stmt_list -> stmt stmt_list
        parse_stmt_list();
    }
    else if (t.token_type == RBRACE)
    {
        // stmt_list -> stmt
	//parse_stmt();	
    }
    else
    {
        syntax_error();
    }
}

void Parser::parse_stmt()
{
    // stmt -> assign_stmt
    // stmt -> while_stmt
 
    Token t = peek();
    if(t.token_type == ID) {
	parse_assign_stmt();
    }
    else if(t.token_type == WHILE) {
	parse_while_stmt();
    }
    else {
	syntax_error();
    }
    
}

void Parser::parse_assign_stmt()
{
    // assign_stmt -> ID EQUAL expr SEMICOLON

    expect(ID);
    expect(EQUAL);
    parse_expr();
    expect(SEMICOLON);
}

void Parser::parse_while_stmt()
{
   // while_stmt -> WHILE condition LBRACE stmt list RBRACE

    expect(WHILE);
    parse_condition();
    expect(LBRACE);
    parse_stmt_list();
    expect(RBRACE);
}

void Parser::parse_expr()
{
    // expr -> term 
    // expr -> term + expr

    parse_term();
    Token t = peek();
    if(t.token_type == PLUS) {
	lexer.GetToken();
	parse_expr();
    }
}

void Parser::parse_term()
{
    // term -> factor
    // term -> factor MULT term

    parse_factor();
    Token t = peek();
    if(t.token_type == MULT) {
	lexer.GetToken();
	parse_term();
    }
}

void Parser::parse_factor()
{
    // factor -> LPAREN expr RPAREN
    // factor -> NUM
    // factor -> REALNUM
    // factor -> ID

    Token t = peek();
    if(t.token_type == LPAREN) {
	expect(LPAREN);
	parse_expr();
	expect(RPAREN);
    }
    else if(t.token_type == NUM) {
	expect(NUM);
    }
    else if(t.token_type == REALNUM) {
	expect(REALNUM);
    }
    else if(t.token_type == ID) {
	expect(ID);
    }
    else {
	syntax_error();
    }
}

void Parser::parse_condition()
{
    // condition -> ID
    // condition -> primary relop primary
    
    Token t = peek();
    if(t.token_type == NUM || t.token_type == REALNUM) {
	parse_primary();
	parse_relop();
	parse_primary();
    }
    else if(t.token_type == ID) {
	expect(ID);
	t = peek();
	if(t.token_type == GREATER || t.token_type == GTEQ ||
	t.token_type == LESS || t.token_type == NOTEQUAL || 
	t.token_type == LTEQ) {
	    parse_relop();
	    parse_primary();
	} 
    }
    else {
	syntax_error();
    }
}

void Parser::parse_primary()
{
    // primary -> ID
    // primary -> NUM
    // primary -> REALNUM
    Token t = peek();
    if(t.token_type == ID) {
	expect(ID);
    }
    else if(t.token_type == NUM) {
	expect(NUM);
    }
    else if(t.token_type == REALNUM) {
	expect(REALNUM);
    }
    else {
	syntax_error();
    }
}

void Parser::parse_relop()
{
    // relop -> GREATER
    // relop -> GTEQ
    // relop -> LESS
    // relop -> NOTEQ
    // relop -> LTEQ

    Token t = peek();
    if(t.token_type == GREATER) {
	expect(GREATER);
    }
    else if(t.token_type == GTEQ) {
	expect(GTEQ);
    }
    else if(t.token_type == LESS) {
        expect(LESS);
    }
    else if(t.token_type == NOTEQUAL) {
	expect(NOTEQUAL);
    }
    else if(t.token_type == LTEQ) {
	expect(LTEQ);
    }
    else {
	syntax_error();
    }
}

void Parser::ParseInput()
{
    parse_program();
    expect(END_OF_FILE);
}

int main()
{
    Parser parser;

    parser.ParseInput();
    while(s != NULL) {
	cout << s->begOfScope << endl;
	cout << s->endOfScope << endl;
	//cout << (string)s->table->tok->lexeme;
	s = s->next;
    }
}
*/