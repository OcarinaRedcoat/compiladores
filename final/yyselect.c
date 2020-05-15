/*
generated at Fri May 15 16:41:19 2020
by $Id: pburg.c,v 2.7 2020/04/06 09:41:42 prs Exp $
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PBURG_PREFIX "yy"
#define PBURG_VERSION "2.7"
#define MAX_COST 0x7fff
#if defined(__STDC__) || defined(__cplusplus)
#define YYCONST const
#else
#define YYCONST
#endif

#line 1 "minor.brg"

/*
 * selecção de instruções com postfix
 */
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "postfix.h"
#include "y.tab.h"
#include "minor.h"

#ifndef U_
#define U_ "_"
#endif

#define TRACE
static void yytrace(NODEPTR_TYPE p, int eruleno, int cost, int bestcost);

extern FILE *yyout;

int lbl;

static char *mklbl(int n) {
	static char buf[20];
	sprintf(buf, "%cL%d", n < 0 ? '.' : '_', n);
	return strcpy(malloc(strlen(buf)+1),buf);
}
static char *mkfunc(char *s) {
	static char buf[80];
	strcpy(buf, "_");
	strcat(buf, s);
	return buf;
}

static void outstr(char *s) {
  while (*s) fprintf(yyout, pfCHAR, (unsigned char)*s++);
  fprintf(yyout, pfCHAR, 0);
}

#ifndef PANIC
#define PANIC yypanic
static void yypanic(YYCONST char *rot, YYCONST char *msg, int val) {
	fprintf(stderr, "Internal Error in %s: %s %d\nexiting...\n",
		rot, msg, val);
	exit(2);
}
#endif
static void yykids(NODEPTR_TYPE, int, NODEPTR_TYPE[]);
#define yyfile_NT 1
#define yyfinaldecls_NT 2
#define yymain_NT 3
#define yydecls_NT 4
#define yygdecls_NT 5
#define yydecl_NT 6
#define yyvardecl_NT 7
#define yyfvars_NT 8
#define yyeqbody_NT 9
#define yyfvar_NT 10
#define yyvdim_NT 11
#define yyeqint_NT 12
#define yyeqstr_NT 13
#define yyeqvec_NT 14
#define yychars_NT 15
#define yychar_NT 16
#define yyints_NT 17
#define yybody_NT 18
#define yyinstrs_NT 19
#define yyret_NT 20
#define yyexpr_NT 21
#define yyloop_NT 22
#define yyblock_NT 23
#define yyinstr_NT 24
#define yyelifs_NT 25
#define yyelse_NT 26
#define yylval_NT 27
#define yyexprs_NT 28

static YYCONST char *yyntname[] = {
	0,
	"file",
	"finaldecls",
	"main",
	"decls",
	"gdecls",
	"decl",
	"vardecl",
	"fvars",
	"eqbody",
	"fvar",
	"vdim",
	"eqint",
	"eqstr",
	"eqvec",
	"chars",
	"char",
	"ints",
	"body",
	"instrs",
	"ret",
	"expr",
	"loop",
	"block",
	"instr",
	"elifs",
	"else",
	"lval",
	"exprs",
	0
};

static YYCONST char *yytermname[] = {
 "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
 "", "", "", "", "", "", "", "", "",
	/* 34 */ "EXCL",
 "",
	/* 36 */ "CARD",
 "",
	/* 38 */ "MOD",
	/* 39 */ "AND",
 "",
	/* 41 */ "CURVE",
 "",
	/* 43 */ "MUL",
	/* 44 */ "ADD",
	/* 45 */ "COMMA",
	/* 46 */ "SUB",
 "",
	/* 48 */ "DIV",
 "", "", "", "", "", "", "", "", "", "", "",
	/* 60 */ "STMT",
	/* 61 */ "MIN",
	/* 62 */ "EQUAL",
	/* 63 */ "MAX",
	/* 64 */ "IN",
 "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
 "", "", "",
	/* 92 */ "PARE",
 "", "",
	/* 95 */ "POW",
 "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
 "", "", "", "", "",
	/* 125 */ "OR",
 "",
	/* 127 */ "NOT",
 "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
 "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
 "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
 "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
 "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
 "", "", "", "", "", "", "", "", "", "",
	/* 258 */ "INT",
	/* 259 */ "CHAR",
	/* 260 */ "ID",
	/* 261 */ "STR",
	/* 262 */ "PROGRAM",
	/* 263 */ "MODULE",
	/* 264 */ "END",
	/* 265 */ "PUBLIC",
	/* 266 */ "FORWARD",
	/* 267 */ "STRING",
	/* 268 */ "NUMBER",
	/* 269 */ "ARRAY",
	/* 270 */ "FUNCTION",
	/* 271 */ "VOID",
	/* 272 */ "CONST",
	/* 273 */ "IF",
	/* 274 */ "THEN",
	/* 275 */ "FI",
	/* 276 */ "ELIF",
	/* 277 */ "ELSE",
	/* 278 */ "RETURN",
	/* 279 */ "START",
	/* 280 */ "FOR",
	/* 281 */ "UNTIL",
	/* 282 */ "STEP",
	/* 283 */ "DO",
	/* 284 */ "DONE",
	/* 285 */ "REPEAT",
	/* 286 */ "STOP",
	/* 287 */ "FARGS",
	/* 288 */ "CHARS",
	/* 289 */ "INTS",
	/* 290 */ "ADDR",
	/* 291 */ "VAR",
	/* 292 */ "ARGS",
	/* 293 */ "DECL",
	/* 294 */ "NIL",
	/* 295 */ "EQ",
	/* 296 */ "NE",
	/* 297 */ "GE",
	/* 298 */ "LE",
	/* 299 */ "uminus",
	""
};

struct yystate {
	short cost[29];
	struct {
		unsigned int yyfile:2;
		unsigned int yyfinaldecls:1;
		unsigned int yymain:2;
		unsigned int yydecls:2;
		unsigned int yygdecls:2;
		unsigned int yydecl:3;
		unsigned int yyvardecl:2;
		unsigned int yyfvars:2;
		unsigned int yyeqbody:2;
		unsigned int yyfvar:2;
		unsigned int yyvdim:2;
		unsigned int yyeqint:2;
		unsigned int yyeqstr:2;
		unsigned int yyeqvec:2;
		unsigned int yychars:2;
		unsigned int yychar:2;
		unsigned int yyints:2;
		unsigned int yybody:2;
		unsigned int yyinstrs:2;
		unsigned int yyret:2;
		unsigned int yyexpr:5;
		unsigned int yyloop:2;
		unsigned int yyblock:1;
		unsigned int yyinstr:3;
		unsigned int yyelifs:2;
		unsigned int yyelse:2;
		unsigned int yylval:2;
		unsigned int yyexprs:2;
	} rule;
};

static short yynts_0[] = { yyfinaldecls_NT, yymain_NT, 0 };
static short yynts_1[] = { yyfinaldecls_NT, 0 };
static short yynts_2[] = { yydecls_NT, 0 };
static short yynts_3[] = { 0 };
static short yynts_4[] = { yygdecls_NT, 0 };
static short yynts_5[] = { yygdecls_NT, yydecl_NT, 0 };
static short yynts_6[] = { yydecl_NT, 0 };
static short yynts_7[] = { yyvardecl_NT, 0 };
static short yynts_8[] = { yyfvars_NT, yyeqbody_NT, 0 };
static short yynts_9[] = { yyeqbody_NT, 0 };
static short yynts_10[] = { yyvdim_NT, 0 };
static short yynts_11[] = { yyfvar_NT, 0 };
static short yynts_12[] = { yyfvars_NT, yyfvar_NT, 0 };
static short yynts_13[] = { yyeqint_NT, 0 };
static short yynts_14[] = { yyeqstr_NT, 0 };
static short yynts_15[] = { yyvdim_NT, yyeqvec_NT, 0 };
static short yynts_16[] = { yychars_NT, 0 };
static short yynts_17[] = { yychar_NT, 0 };
static short yynts_18[] = { yychars_NT, yychar_NT, 0 };
static short yynts_19[] = { yyints_NT, 0 };
static short yynts_20[] = { yybody_NT, 0 };
static short yynts_21[] = { yyfvars_NT, yyinstrs_NT, 0 };
static short yynts_22[] = { yyinstrs_NT, 0 };
static short yynts_23[] = { yyfvars_NT, yyinstrs_NT, yyret_NT, 0 };
static short yynts_24[] = { yyinstrs_NT, yyret_NT, 0 };
static short yynts_25[] = { yyexpr_NT, 0 };
static short yynts_26[] = { yyret_NT, 0 };
static short yynts_27[] = { yyinstrs_NT, yyloop_NT, 0 };
static short yynts_28[] = { yyinstrs_NT, yyinstr_NT, 0 };
static short yynts_29[] = { yyexpr_NT, yyblock_NT, yyelifs_NT, yyelse_NT, 0 };
static short yynts_30[] = { yyexpr_NT, yyexpr_NT, yyblock_NT, yyexpr_NT, 0 };
static short yynts_31[] = { yyexpr_NT, yylval_NT, 0 };
static short yynts_32[] = { yyelifs_NT, yyexpr_NT, yyblock_NT, 0 };
static short yynts_33[] = { yyblock_NT, 0 };
static short yynts_34[] = { yylval_NT, 0 };
static short yynts_35[] = { yyexpr_NT, yyexpr_NT, 0 };
static short yynts_36[] = { yyexprs_NT, 0 };
static short yynts_37[] = { yyexpr_NT, yyexprs_NT, 0 };

static short *yynts[] = {
	0,	/* 0 */
	yynts_0,	/* 1 */
	yynts_1,	/* 2 */
	yynts_2,	/* 3 */
	yynts_3,	/* 4 */
	yynts_4,	/* 5 */
	yynts_5,	/* 6 */
	yynts_6,	/* 7 */
	yynts_7,	/* 8 */
	yynts_8,	/* 9 */
	yynts_9,	/* 10 */
	yynts_3,	/* 11 */
	yynts_3,	/* 12 */
	yynts_3,	/* 13 */
	yynts_10,	/* 14 */
	yynts_11,	/* 15 */
	yynts_12,	/* 16 */
	yynts_13,	/* 17 */
	yynts_14,	/* 18 */
	yynts_15,	/* 19 */
	yynts_3,	/* 20 */
	yynts_3,	/* 21 */
	yynts_3,	/* 22 */
	yynts_3,	/* 23 */
	yynts_3,	/* 24 */
	yynts_3,	/* 25 */
	yynts_16,	/* 26 */
	yynts_17,	/* 27 */
	yynts_18,	/* 28 */
	yynts_3,	/* 29 */
	yynts_3,	/* 30 */
	yynts_3,	/* 31 */
	yynts_3,	/* 32 */
	yynts_19,	/* 33 */
	yynts_3,	/* 34 */
	yynts_19,	/* 35 */
	yynts_3,	/* 36 */
	yynts_20,	/* 37 */
	yynts_21,	/* 38 */
	yynts_22,	/* 39 */
	yynts_23,	/* 40 */
	yynts_24,	/* 41 */
	yynts_3,	/* 42 */
	yynts_25,	/* 43 */
	yynts_3,	/* 44 */
	yynts_26,	/* 45 */
	yynts_3,	/* 46 */
	yynts_3,	/* 47 */
	yynts_27,	/* 48 */
	yynts_3,	/* 49 */
	yynts_28,	/* 50 */
	yynts_29,	/* 51 */
	yynts_30,	/* 52 */
	yynts_25,	/* 53 */
	yynts_25,	/* 54 */
	yynts_31,	/* 55 */
	yynts_3,	/* 56 */
	yynts_32,	/* 57 */
	yynts_3,	/* 58 */
	yynts_33,	/* 59 */
	yynts_3,	/* 60 */
	yynts_25,	/* 61 */
	yynts_16,	/* 62 */
	yynts_34,	/* 63 */
	yynts_3,	/* 64 */
	yynts_34,	/* 65 */
	yynts_25,	/* 66 */
	yynts_35,	/* 67 */
	yynts_35,	/* 68 */
	yynts_35,	/* 69 */
	yynts_35,	/* 70 */
	yynts_35,	/* 71 */
	yynts_35,	/* 72 */
	yynts_35,	/* 73 */
	yynts_35,	/* 74 */
	yynts_35,	/* 75 */
	yynts_35,	/* 76 */
	yynts_35,	/* 77 */
	yynts_35,	/* 78 */
	yynts_35,	/* 79 */
	yynts_35,	/* 80 */
	yynts_25,	/* 81 */
	yynts_25,	/* 82 */
	yynts_31,	/* 83 */
	yynts_36,	/* 84 */
	yynts_25,	/* 85 */
	yynts_37,	/* 86 */
};


static YYCONST char *yystring[] = {
/* 0 */	0,
/* 1 */	"file: PROGRAM(finaldecls,FUNCTION(END(ID,INT),FARGS(NIL,main)))",
/* 2 */	"file: MODULE(finaldecls)",
/* 3 */	"finaldecls: decls",
/* 4 */	"decls: NIL",
/* 5 */	"decls: gdecls",
/* 6 */	"gdecls: DECL(gdecls,decl)",
/* 7 */	"gdecls: DECL(NIL,decl)",
/* 8 */	"decl: VAR(vardecl)",
/* 9 */	"decl: FUNCTION(END(ID,INT),FARGS(fvars,eqbody))",
/* 10 */	"decl: FUNCTION(END(ID,INT),FARGS(NIL,eqbody))",
/* 11 */	"decl: NIL",
/* 12 */	"fvar: NUMBER(ID,NIL)",
/* 13 */	"fvar: STRING(ID,NIL)",
/* 14 */	"fvar: ARRAY(ID,INTS(vdim,NIL))",
/* 15 */	"fvars: ARGS(NIL,fvar)",
/* 16 */	"fvars: ARGS(fvars,fvar)",
/* 17 */	"vardecl: NUMBER(ID,eqint)",
/* 18 */	"vardecl: STRING(ID,eqstr)",
/* 19 */	"vardecl: ARRAY(ID,INTS(vdim,eqvec))",
/* 20 */	"vdim: INT",
/* 21 */	"vdim: NIL",
/* 22 */	"eqint: NIL",
/* 23 */	"eqint: INT",
/* 24 */	"eqint: INT",
/* 25 */	"eqstr: NIL",
/* 26 */	"eqstr: chars",
/* 27 */	"chars: CHARS(NIL,char)",
/* 28 */	"chars: CHARS(chars,char)",
/* 29 */	"char: INT",
/* 30 */	"char: CHAR",
/* 31 */	"char: STR",
/* 32 */	"eqvec: NIL",
/* 33 */	"eqvec: ints",
/* 34 */	"ints: INT",
/* 35 */	"ints: INTS(ints,INT)",
/* 36 */	"eqbody: NIL",
/* 37 */	"eqbody: body",
/* 38 */	"main: START(fvars,instrs)",
/* 39 */	"main: START(NIL,instrs)",
/* 40 */	"body: START(fvars,STMT(instrs,ret))",
/* 41 */	"body: START(NIL,STMT(instrs,ret))",
/* 42 */	"ret: RETURN(NIL)",
/* 43 */	"ret: RETURN(expr)",
/* 44 */	"ret: NIL",
/* 45 */	"loop: ret",
/* 46 */	"loop: REPEAT",
/* 47 */	"loop: STOP",
/* 48 */	"block: STMT(instrs,loop)",
/* 49 */	"instrs: NIL",
/* 50 */	"instrs: STMT(instrs,instr)",
/* 51 */	"instr: FI(THEN(IF(expr,block),elifs),else)",
/* 52 */	"instr: FOR(UNTIL(expr,expr),STEP(block,expr))",
/* 53 */	"instr: EXCL(expr)",
/* 54 */	"instr: expr",
/* 55 */	"instr: CARD(expr,lval)",
/* 56 */	"elifs: NIL",
/* 57 */	"elifs: ELIF(elifs,IF(expr,block))",
/* 58 */	"else: NIL",
/* 59 */	"else: block",
/* 60 */	"lval: ID",
/* 61 */	"lval: PARE(expr,ID)",
/* 62 */	"expr: chars",
/* 63 */	"expr: lval",
/* 64 */	"expr: IN",
/* 65 */	"expr: ADDR(lval)",
/* 66 */	"expr: expr",
/* 67 */	"expr: ADD(expr,expr)",
/* 68 */	"expr: SUB(expr,expr)",
/* 69 */	"expr: MUL(expr,expr)",
/* 70 */	"expr: DIV(expr,expr)",
/* 71 */	"expr: MOD(expr,expr)",
/* 72 */	"expr: POW(expr,expr)",
/* 73 */	"expr: EQUAL(expr,expr)",
/* 74 */	"expr: NE(expr,expr)",
/* 75 */	"expr: GE(expr,expr)",
/* 76 */	"expr: LE(expr,expr)",
/* 77 */	"expr: MIN(expr,expr)",
/* 78 */	"expr: MAX(expr,expr)",
/* 79 */	"expr: AND(expr,expr)",
/* 80 */	"expr: OR(expr,expr)",
/* 81 */	"expr: NOT(expr)",
/* 82 */	"expr: uminus(expr)",
/* 83 */	"expr: EQ(expr,lval)",
/* 84 */	"expr: CURVE(ID,exprs)",
/* 85 */	"exprs: COMMA(expr,NIL)",
/* 86 */	"exprs: COMMA(expr,exprs)",
};

#ifndef TRACE
static void yytrace(NODEPTR_TYPE p, int eruleno, int cost, int bestcost)
{
	int op = OP_LABEL(p);
	YYCONST char *tname = yytermname[op] ? yytermname[op] : "?";
	fprintf(stderr, "0x%p:%s matched %s with cost %d vs. %d\n", (void*)p, tname, yystring[eruleno], cost, bestcost);
}
#endif

static short yydecode_file[] = {
	0,
	1,
	2,
};

static short yydecode_finaldecls[] = {
	0,
	3,
};

static short yydecode_main[] = {
	0,
	38,
	39,
};

static short yydecode_decls[] = {
	0,
	4,
	5,
};

static short yydecode_gdecls[] = {
	0,
	6,
	7,
};

static short yydecode_decl[] = {
	0,
	8,
	9,
	10,
	11,
};

static short yydecode_vardecl[] = {
	0,
	17,
	18,
	19,
};

static short yydecode_fvars[] = {
	0,
	15,
	16,
};

static short yydecode_eqbody[] = {
	0,
	36,
	37,
};

static short yydecode_fvar[] = {
	0,
	12,
	13,
	14,
};

static short yydecode_vdim[] = {
	0,
	20,
	21,
};

static short yydecode_eqint[] = {
	0,
	22,
	23,
	24,
};

static short yydecode_eqstr[] = {
	0,
	25,
	26,
};

static short yydecode_eqvec[] = {
	0,
	32,
	33,
};

static short yydecode_chars[] = {
	0,
	27,
	28,
};

static short yydecode_char[] = {
	0,
	29,
	30,
	31,
};

static short yydecode_ints[] = {
	0,
	34,
	35,
};

static short yydecode_body[] = {
	0,
	40,
	41,
};

static short yydecode_instrs[] = {
	0,
	49,
	50,
};

static short yydecode_ret[] = {
	0,
	42,
	43,
	44,
};

static short yydecode_expr[] = {
	0,
	62,
	63,
	64,
	65,
	66,
	67,
	68,
	69,
	70,
	71,
	72,
	73,
	74,
	75,
	76,
	77,
	78,
	79,
	80,
	81,
	82,
	83,
	84,
};

static short yydecode_loop[] = {
	0,
	45,
	46,
	47,
};

static short yydecode_block[] = {
	0,
	48,
};

static short yydecode_instr[] = {
	0,
	51,
	52,
	53,
	54,
	55,
};

static short yydecode_elifs[] = {
	0,
	56,
	57,
};

static short yydecode_else[] = {
	0,
	58,
	59,
};

static short yydecode_lval[] = {
	0,
	60,
	61,
};

static short yydecode_exprs[] = {
	0,
	85,
	86,
};

static int yyrule(void *state, int goalnt) {
	if (goalnt < 1 || goalnt > 28)
		PANIC("yyrule", "Bad goal nonterminal", goalnt);
	if (!state)
		return 0;
	switch (goalnt) {
	case yyfile_NT:	return yydecode_file[((struct yystate *)state)->rule.yyfile];
	case yyfinaldecls_NT:	return yydecode_finaldecls[((struct yystate *)state)->rule.yyfinaldecls];
	case yymain_NT:	return yydecode_main[((struct yystate *)state)->rule.yymain];
	case yydecls_NT:	return yydecode_decls[((struct yystate *)state)->rule.yydecls];
	case yygdecls_NT:	return yydecode_gdecls[((struct yystate *)state)->rule.yygdecls];
	case yydecl_NT:	return yydecode_decl[((struct yystate *)state)->rule.yydecl];
	case yyvardecl_NT:	return yydecode_vardecl[((struct yystate *)state)->rule.yyvardecl];
	case yyfvars_NT:	return yydecode_fvars[((struct yystate *)state)->rule.yyfvars];
	case yyeqbody_NT:	return yydecode_eqbody[((struct yystate *)state)->rule.yyeqbody];
	case yyfvar_NT:	return yydecode_fvar[((struct yystate *)state)->rule.yyfvar];
	case yyvdim_NT:	return yydecode_vdim[((struct yystate *)state)->rule.yyvdim];
	case yyeqint_NT:	return yydecode_eqint[((struct yystate *)state)->rule.yyeqint];
	case yyeqstr_NT:	return yydecode_eqstr[((struct yystate *)state)->rule.yyeqstr];
	case yyeqvec_NT:	return yydecode_eqvec[((struct yystate *)state)->rule.yyeqvec];
	case yychars_NT:	return yydecode_chars[((struct yystate *)state)->rule.yychars];
	case yychar_NT:	return yydecode_char[((struct yystate *)state)->rule.yychar];
	case yyints_NT:	return yydecode_ints[((struct yystate *)state)->rule.yyints];
	case yybody_NT:	return yydecode_body[((struct yystate *)state)->rule.yybody];
	case yyinstrs_NT:	return yydecode_instrs[((struct yystate *)state)->rule.yyinstrs];
	case yyret_NT:	return yydecode_ret[((struct yystate *)state)->rule.yyret];
	case yyexpr_NT:	return yydecode_expr[((struct yystate *)state)->rule.yyexpr];
	case yyloop_NT:	return yydecode_loop[((struct yystate *)state)->rule.yyloop];
	case yyblock_NT:	return yydecode_block[((struct yystate *)state)->rule.yyblock];
	case yyinstr_NT:	return yydecode_instr[((struct yystate *)state)->rule.yyinstr];
	case yyelifs_NT:	return yydecode_elifs[((struct yystate *)state)->rule.yyelifs];
	case yyelse_NT:	return yydecode_else[((struct yystate *)state)->rule.yyelse];
	case yylval_NT:	return yydecode_lval[((struct yystate *)state)->rule.yylval];
	case yyexprs_NT:	return yydecode_exprs[((struct yystate *)state)->rule.yyexprs];
	default:
		PANIC("yyrule", "Bad goal nonterminal", goalnt);
		return 0;
	}
}

static void yyclosure_decls(NODEPTR_TYPE, int);
static void yyclosure_gdecls(NODEPTR_TYPE, int);
static void yyclosure_chars(NODEPTR_TYPE, int);
static void yyclosure_ints(NODEPTR_TYPE, int);
static void yyclosure_body(NODEPTR_TYPE, int);
static void yyclosure_ret(NODEPTR_TYPE, int);
static void yyclosure_expr(NODEPTR_TYPE, int);
static void yyclosure_block(NODEPTR_TYPE, int);
static void yyclosure_lval(NODEPTR_TYPE, int);

static void yyclosure_decls(NODEPTR_TYPE a, int c) {
	struct yystate *p = (struct yystate *)STATE_LABEL(a);
	yytrace(a, 3, c + 0, p->cost[yyfinaldecls_NT]);
	if (c + 0 < p->cost[yyfinaldecls_NT]) {
		p->cost[yyfinaldecls_NT] = c + 0;
		p->rule.yyfinaldecls = 1;
	}
}

static void yyclosure_gdecls(NODEPTR_TYPE a, int c) {
	struct yystate *p = (struct yystate *)STATE_LABEL(a);
	yytrace(a, 5, c + 1, p->cost[yydecls_NT]);
	if (c + 1 < p->cost[yydecls_NT]) {
		p->cost[yydecls_NT] = c + 1;
		p->rule.yydecls = 2;
		yyclosure_decls(a, c + 1);
	}
}

static void yyclosure_chars(NODEPTR_TYPE a, int c) {
	struct yystate *p = (struct yystate *)STATE_LABEL(a);
	yytrace(a, 62, c + 1, p->cost[yyexpr_NT]);
	if (c + 1 < p->cost[yyexpr_NT]) {
		p->cost[yyexpr_NT] = c + 1;
		p->rule.yyexpr = 1;
		yyclosure_expr(a, c + 1);
	}
	yytrace(a, 26, c + 1, p->cost[yyeqstr_NT]);
	if (c + 1 < p->cost[yyeqstr_NT]) {
		p->cost[yyeqstr_NT] = c + 1;
		p->rule.yyeqstr = 2;
	}
}

static void yyclosure_ints(NODEPTR_TYPE a, int c) {
	struct yystate *p = (struct yystate *)STATE_LABEL(a);
	yytrace(a, 33, c + 1, p->cost[yyeqvec_NT]);
	if (c + 1 < p->cost[yyeqvec_NT]) {
		p->cost[yyeqvec_NT] = c + 1;
		p->rule.yyeqvec = 2;
	}
}

static void yyclosure_body(NODEPTR_TYPE a, int c) {
	struct yystate *p = (struct yystate *)STATE_LABEL(a);
	yytrace(a, 37, c + 1, p->cost[yyeqbody_NT]);
	if (c + 1 < p->cost[yyeqbody_NT]) {
		p->cost[yyeqbody_NT] = c + 1;
		p->rule.yyeqbody = 2;
	}
}

static void yyclosure_ret(NODEPTR_TYPE a, int c) {
	struct yystate *p = (struct yystate *)STATE_LABEL(a);
	yytrace(a, 45, c + 1, p->cost[yyloop_NT]);
	if (c + 1 < p->cost[yyloop_NT]) {
		p->cost[yyloop_NT] = c + 1;
		p->rule.yyloop = 1;
	}
}

static void yyclosure_expr(NODEPTR_TYPE a, int c) {
	struct yystate *p = (struct yystate *)STATE_LABEL(a);
	yytrace(a, 66, c + 1, p->cost[yyexpr_NT]);
	if (c + 1 < p->cost[yyexpr_NT]) {
		p->cost[yyexpr_NT] = c + 1;
		p->rule.yyexpr = 5;
		yyclosure_expr(a, c + 1);
	}
	yytrace(a, 54, c + 1, p->cost[yyinstr_NT]);
	if (c + 1 < p->cost[yyinstr_NT]) {
		p->cost[yyinstr_NT] = c + 1;
		p->rule.yyinstr = 4;
	}
}

static void yyclosure_block(NODEPTR_TYPE a, int c) {
	struct yystate *p = (struct yystate *)STATE_LABEL(a);
	yytrace(a, 59, c + 1, p->cost[yyelse_NT]);
	if (c + 1 < p->cost[yyelse_NT]) {
		p->cost[yyelse_NT] = c + 1;
		p->rule.yyelse = 2;
	}
}

static void yyclosure_lval(NODEPTR_TYPE a, int c) {
	struct yystate *p = (struct yystate *)STATE_LABEL(a);
	yytrace(a, 63, c + 1, p->cost[yyexpr_NT]);
	if (c + 1 < p->cost[yyexpr_NT]) {
		p->cost[yyexpr_NT] = c + 1;
		p->rule.yyexpr = 2;
		yyclosure_expr(a, c + 1);
	}
}

static void yylabel(NODEPTR_TYPE a, NODEPTR_TYPE u) {
	int c;
	struct yystate *p;

	if (!a)
		PANIC("yylabel", "Null tree in", OP_LABEL(u));
	STATE_LABEL(a) = p = (struct yystate *)malloc(sizeof *p);
	memset(p, 0, sizeof *p);
	p->cost[1] =
	p->cost[2] =
	p->cost[3] =
	p->cost[4] =
	p->cost[5] =
	p->cost[6] =
	p->cost[7] =
	p->cost[8] =
	p->cost[9] =
	p->cost[10] =
	p->cost[11] =
	p->cost[12] =
	p->cost[13] =
	p->cost[14] =
	p->cost[15] =
	p->cost[16] =
	p->cost[17] =
	p->cost[18] =
	p->cost[19] =
	p->cost[20] =
	p->cost[21] =
	p->cost[22] =
	p->cost[23] =
	p->cost[24] =
	p->cost[25] =
	p->cost[26] =
	p->cost[27] =
	p->cost[28] =
		0x7fff;
	switch (OP_LABEL(a)) {
	case 33: /* EXCL */
		yylabel(LEFT_CHILD(a),a);
		/* instr: EXCL(expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 53, c + 0, p->cost[yyinstr_NT]);
		if (c + 0 < p->cost[yyinstr_NT]) {
			p->cost[yyinstr_NT] = c + 0;
			p->rule.yyinstr = 3;
		}
		break;
	case 35: /* CARD */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* instr: CARD(expr,lval) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yylval_NT] + 1;
		yytrace(a, 55, c + 0, p->cost[yyinstr_NT]);
		if (c + 0 < p->cost[yyinstr_NT]) {
			p->cost[yyinstr_NT] = c + 0;
			p->rule.yyinstr = 5;
		}
		break;
	case 37: /* MOD */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: MOD(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 71, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 10;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 38: /* AND */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: AND(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 79, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 18;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 40: /* CURVE */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		if (	/* expr: CURVE(ID,exprs) */
			OP_LABEL(LEFT_CHILD(a)) == 259 /* ID */
		) {
			c = ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexprs_NT] + 1;
			yytrace(a, 84, c + 0, p->cost[yyexpr_NT]);
			if (c + 0 < p->cost[yyexpr_NT]) {
				p->cost[yyexpr_NT] = c + 0;
				p->rule.yyexpr = 23;
				yyclosure_expr(a, c + 0);
			}
		}
		break;
	case 42: /* MUL */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: MUL(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 69, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 8;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 43: /* ADD */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: ADD(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 67, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 6;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 44: /* COMMA */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		if (	/* exprs: COMMA(expr,NIL) */
			OP_LABEL(RIGHT_CHILD(a)) == 293 /* NIL */
		) {
			c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + 1;
			yytrace(a, 85, c + 0, p->cost[yyexprs_NT]);
			if (c + 0 < p->cost[yyexprs_NT]) {
				p->cost[yyexprs_NT] = c + 0;
				p->rule.yyexprs = 1;
			}
		}
		/* exprs: COMMA(expr,exprs) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexprs_NT] + 1;
		yytrace(a, 86, c + 0, p->cost[yyexprs_NT]);
		if (c + 0 < p->cost[yyexprs_NT]) {
			p->cost[yyexprs_NT] = c + 0;
			p->rule.yyexprs = 2;
		}
		break;
	case 45: /* SUB */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: SUB(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 68, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 7;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 47: /* DIV */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: DIV(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 70, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 9;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 59: /* STMT */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* block: STMT(instrs,loop) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyinstrs_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyloop_NT] + 1;
		yytrace(a, 48, c + 0, p->cost[yyblock_NT]);
		if (c + 0 < p->cost[yyblock_NT]) {
			p->cost[yyblock_NT] = c + 0;
			p->rule.yyblock = 1;
			yyclosure_block(a, c + 0);
		}
		/* instrs: STMT(instrs,instr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyinstrs_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyinstr_NT] + 1;
		yytrace(a, 50, c + 0, p->cost[yyinstrs_NT]);
		if (c + 0 < p->cost[yyinstrs_NT]) {
			p->cost[yyinstrs_NT] = c + 0;
			p->rule.yyinstrs = 2;
		}
		break;
	case 60: /* MIN */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: MIN(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 77, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 16;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 61: /* EQUAL */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: EQUAL(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 73, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 12;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 62: /* MAX */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: MAX(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 78, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 17;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 63: /* IN */
		/* expr: IN */
		yytrace(a, 64, 1 + 0, p->cost[yyexpr_NT]);
		if (1 + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = 1 + 0;
			p->rule.yyexpr = 3;
			yyclosure_expr(a, 1 + 0);
		}
		break;
	case 91: /* PARE */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		if (	/* lval: PARE(expr,ID) */
			OP_LABEL(RIGHT_CHILD(a)) == 259 /* ID */
		) {
			c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + 1;
			yytrace(a, 61, c + 0, p->cost[yylval_NT]);
			if (c + 0 < p->cost[yylval_NT]) {
				p->cost[yylval_NT] = c + 0;
				p->rule.yylval = 2;
				yyclosure_lval(a, c + 0);
			}
		}
		break;
	case 94: /* POW */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: POW(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 72, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 11;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 124: /* OR */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: OR(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 80, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 19;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 126: /* NOT */
		yylabel(LEFT_CHILD(a),a);
		/* expr: NOT(expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 81, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 20;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 257: /* INT */
		/* vdim: INT */
		yytrace(a, 20, 1 + 0, p->cost[yyvdim_NT]);
		if (1 + 0 < p->cost[yyvdim_NT]) {
			p->cost[yyvdim_NT] = 1 + 0;
			p->rule.yyvdim = 1;
		}
		/* eqint: INT */
		yytrace(a, 23, 1 + 0, p->cost[yyeqint_NT]);
		if (1 + 0 < p->cost[yyeqint_NT]) {
			p->cost[yyeqint_NT] = 1 + 0;
			p->rule.yyeqint = 2;
		}
		/* eqint: INT */
		yytrace(a, 24, 1 + 0, p->cost[yyeqint_NT]);
		if (1 + 0 < p->cost[yyeqint_NT]) {
			p->cost[yyeqint_NT] = 1 + 0;
			p->rule.yyeqint = 3;
		}
		/* char: INT */
		yytrace(a, 29, 1 + 0, p->cost[yychar_NT]);
		if (1 + 0 < p->cost[yychar_NT]) {
			p->cost[yychar_NT] = 1 + 0;
			p->rule.yychar = 1;
		}
		/* ints: INT */
		yytrace(a, 34, 1 + 0, p->cost[yyints_NT]);
		if (1 + 0 < p->cost[yyints_NT]) {
			p->cost[yyints_NT] = 1 + 0;
			p->rule.yyints = 1;
			yyclosure_ints(a, 1 + 0);
		}
		break;
	case 258: /* CHAR */
		/* char: CHAR */
		yytrace(a, 30, 1 + 0, p->cost[yychar_NT]);
		if (1 + 0 < p->cost[yychar_NT]) {
			p->cost[yychar_NT] = 1 + 0;
			p->rule.yychar = 2;
		}
		break;
	case 259: /* ID */
		/* lval: ID */
		yytrace(a, 60, 1 + 0, p->cost[yylval_NT]);
		if (1 + 0 < p->cost[yylval_NT]) {
			p->cost[yylval_NT] = 1 + 0;
			p->rule.yylval = 1;
			yyclosure_lval(a, 1 + 0);
		}
		break;
	case 260: /* STR */
		/* char: STR */
		yytrace(a, 31, 1 + 0, p->cost[yychar_NT]);
		if (1 + 0 < p->cost[yychar_NT]) {
			p->cost[yychar_NT] = 1 + 0;
			p->rule.yychar = 3;
		}
		break;
	case 261: /* PROGRAM */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		if (	/* file: PROGRAM(finaldecls,FUNCTION(END(ID,INT),FARGS(NIL,main))) */
			OP_LABEL(RIGHT_CHILD(a)) == 269 && /* FUNCTION */
			OP_LABEL(LEFT_CHILD(RIGHT_CHILD(a))) == 263 && /* END */
			OP_LABEL(LEFT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))) == 259 && /* ID */
			OP_LABEL(RIGHT_CHILD(LEFT_CHILD(RIGHT_CHILD(a)))) == 257 && /* INT */
			OP_LABEL(RIGHT_CHILD(RIGHT_CHILD(a))) == 286 && /* FARGS */
			OP_LABEL(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))) == 293 /* NIL */
		) {
			c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyfinaldecls_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))))->cost[yymain_NT] + 1;
			yytrace(a, 1, c + 0, p->cost[yyfile_NT]);
			if (c + 0 < p->cost[yyfile_NT]) {
				p->cost[yyfile_NT] = c + 0;
				p->rule.yyfile = 1;
			}
		}
		break;
	case 262: /* MODULE */
		yylabel(LEFT_CHILD(a),a);
		/* file: MODULE(finaldecls) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyfinaldecls_NT] + 1;
		yytrace(a, 2, c + 0, p->cost[yyfile_NT]);
		if (c + 0 < p->cost[yyfile_NT]) {
			p->cost[yyfile_NT] = c + 0;
			p->rule.yyfile = 2;
		}
		break;
	case 263: /* END */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		return;
	case 264: /* PUBLIC */
		return;
	case 265: /* FORWARD */
		return;
	case 266: /* STRING */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		if (	/* fvar: STRING(ID,NIL) */
			OP_LABEL(LEFT_CHILD(a)) == 259 && /* ID */
			OP_LABEL(RIGHT_CHILD(a)) == 293 /* NIL */
		) {
			c = 1;
			yytrace(a, 13, c + 0, p->cost[yyfvar_NT]);
			if (c + 0 < p->cost[yyfvar_NT]) {
				p->cost[yyfvar_NT] = c + 0;
				p->rule.yyfvar = 2;
			}
		}
		if (	/* vardecl: STRING(ID,eqstr) */
			OP_LABEL(LEFT_CHILD(a)) == 259 /* ID */
		) {
			c = ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyeqstr_NT] + 1;
			yytrace(a, 18, c + 0, p->cost[yyvardecl_NT]);
			if (c + 0 < p->cost[yyvardecl_NT]) {
				p->cost[yyvardecl_NT] = c + 0;
				p->rule.yyvardecl = 2;
			}
		}
		break;
	case 267: /* NUMBER */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		if (	/* fvar: NUMBER(ID,NIL) */
			OP_LABEL(LEFT_CHILD(a)) == 259 && /* ID */
			OP_LABEL(RIGHT_CHILD(a)) == 293 /* NIL */
		) {
			c = 1;
			yytrace(a, 12, c + 0, p->cost[yyfvar_NT]);
			if (c + 0 < p->cost[yyfvar_NT]) {
				p->cost[yyfvar_NT] = c + 0;
				p->rule.yyfvar = 1;
			}
		}
		if (	/* vardecl: NUMBER(ID,eqint) */
			OP_LABEL(LEFT_CHILD(a)) == 259 /* ID */
		) {
			c = ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyeqint_NT] + 1;
			yytrace(a, 17, c + 0, p->cost[yyvardecl_NT]);
			if (c + 0 < p->cost[yyvardecl_NT]) {
				p->cost[yyvardecl_NT] = c + 0;
				p->rule.yyvardecl = 1;
			}
		}
		break;
	case 268: /* ARRAY */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		if (	/* fvar: ARRAY(ID,INTS(vdim,NIL)) */
			OP_LABEL(LEFT_CHILD(a)) == 259 && /* ID */
			OP_LABEL(RIGHT_CHILD(a)) == 288 && /* INTS */
			OP_LABEL(RIGHT_CHILD(RIGHT_CHILD(a))) == 293 /* NIL */
		) {
			c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(RIGHT_CHILD(a))))->cost[yyvdim_NT] + 1;
			yytrace(a, 14, c + 0, p->cost[yyfvar_NT]);
			if (c + 0 < p->cost[yyfvar_NT]) {
				p->cost[yyfvar_NT] = c + 0;
				p->rule.yyfvar = 3;
			}
		}
		if (	/* vardecl: ARRAY(ID,INTS(vdim,eqvec)) */
			OP_LABEL(LEFT_CHILD(a)) == 259 && /* ID */
			OP_LABEL(RIGHT_CHILD(a)) == 288 /* INTS */
		) {
			c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(RIGHT_CHILD(a))))->cost[yyvdim_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(RIGHT_CHILD(a))))->cost[yyeqvec_NT] + 1;
			yytrace(a, 19, c + 0, p->cost[yyvardecl_NT]);
			if (c + 0 < p->cost[yyvardecl_NT]) {
				p->cost[yyvardecl_NT] = c + 0;
				p->rule.yyvardecl = 3;
			}
		}
		break;
	case 269: /* FUNCTION */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		if (	/* decl: FUNCTION(END(ID,INT),FARGS(fvars,eqbody)) */
			OP_LABEL(LEFT_CHILD(a)) == 263 && /* END */
			OP_LABEL(LEFT_CHILD(LEFT_CHILD(a))) == 259 && /* ID */
			OP_LABEL(RIGHT_CHILD(LEFT_CHILD(a))) == 257 && /* INT */
			OP_LABEL(RIGHT_CHILD(a)) == 286 /* FARGS */
		) {
			c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(RIGHT_CHILD(a))))->cost[yyfvars_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(RIGHT_CHILD(a))))->cost[yyeqbody_NT] + 1;
			yytrace(a, 9, c + 0, p->cost[yydecl_NT]);
			if (c + 0 < p->cost[yydecl_NT]) {
				p->cost[yydecl_NT] = c + 0;
				p->rule.yydecl = 2;
			}
		}
		if (	/* decl: FUNCTION(END(ID,INT),FARGS(NIL,eqbody)) */
			OP_LABEL(LEFT_CHILD(a)) == 263 && /* END */
			OP_LABEL(LEFT_CHILD(LEFT_CHILD(a))) == 259 && /* ID */
			OP_LABEL(RIGHT_CHILD(LEFT_CHILD(a))) == 257 && /* INT */
			OP_LABEL(RIGHT_CHILD(a)) == 286 && /* FARGS */
			OP_LABEL(LEFT_CHILD(RIGHT_CHILD(a))) == 293 /* NIL */
		) {
			c = ((struct yystate *)STATE_LABEL(RIGHT_CHILD(RIGHT_CHILD(a))))->cost[yyeqbody_NT] + 1;
			yytrace(a, 10, c + 0, p->cost[yydecl_NT]);
			if (c + 0 < p->cost[yydecl_NT]) {
				p->cost[yydecl_NT] = c + 0;
				p->rule.yydecl = 3;
			}
		}
		break;
	case 270: /* VOID */
		return;
	case 271: /* CONST */
		return;
	case 272: /* IF */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		return;
	case 273: /* THEN */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		return;
	case 274: /* FI */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		if (	/* instr: FI(THEN(IF(expr,block),elifs),else) */
			OP_LABEL(LEFT_CHILD(a)) == 273 && /* THEN */
			OP_LABEL(LEFT_CHILD(LEFT_CHILD(a))) == 272 /* IF */
		) {
			c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(LEFT_CHILD(LEFT_CHILD(a)))))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(LEFT_CHILD(LEFT_CHILD(a)))))->cost[yyblock_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(LEFT_CHILD(a))))->cost[yyelifs_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyelse_NT] + 1;
			yytrace(a, 51, c + 0, p->cost[yyinstr_NT]);
			if (c + 0 < p->cost[yyinstr_NT]) {
				p->cost[yyinstr_NT] = c + 0;
				p->rule.yyinstr = 1;
			}
		}
		break;
	case 275: /* ELIF */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		if (	/* elifs: ELIF(elifs,IF(expr,block)) */
			OP_LABEL(RIGHT_CHILD(a)) == 272 /* IF */
		) {
			c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyelifs_NT] + ((struct yystate *)STATE_LABEL(LEFT_CHILD(RIGHT_CHILD(a))))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(RIGHT_CHILD(a))))->cost[yyblock_NT] + 1;
			yytrace(a, 57, c + 0, p->cost[yyelifs_NT]);
			if (c + 0 < p->cost[yyelifs_NT]) {
				p->cost[yyelifs_NT] = c + 0;
				p->rule.yyelifs = 2;
			}
		}
		break;
	case 276: /* ELSE */
		return;
	case 277: /* RETURN */
		yylabel(LEFT_CHILD(a),a);
		if (	/* ret: RETURN(NIL) */
			OP_LABEL(LEFT_CHILD(a)) == 293 /* NIL */
		) {
			c = 1;
			yytrace(a, 42, c + 0, p->cost[yyret_NT]);
			if (c + 0 < p->cost[yyret_NT]) {
				p->cost[yyret_NT] = c + 0;
				p->rule.yyret = 1;
				yyclosure_ret(a, c + 0);
			}
		}
		/* ret: RETURN(expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 43, c + 0, p->cost[yyret_NT]);
		if (c + 0 < p->cost[yyret_NT]) {
			p->cost[yyret_NT] = c + 0;
			p->rule.yyret = 2;
			yyclosure_ret(a, c + 0);
		}
		break;
	case 278: /* START */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* main: START(fvars,instrs) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyfvars_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyinstrs_NT] + 1;
		yytrace(a, 38, c + 0, p->cost[yymain_NT]);
		if (c + 0 < p->cost[yymain_NT]) {
			p->cost[yymain_NT] = c + 0;
			p->rule.yymain = 1;
		}
		if (	/* main: START(NIL,instrs) */
			OP_LABEL(LEFT_CHILD(a)) == 293 /* NIL */
		) {
			c = ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyinstrs_NT] + 1;
			yytrace(a, 39, c + 0, p->cost[yymain_NT]);
			if (c + 0 < p->cost[yymain_NT]) {
				p->cost[yymain_NT] = c + 0;
				p->rule.yymain = 2;
			}
		}
		if (	/* body: START(fvars,STMT(instrs,ret)) */
			OP_LABEL(RIGHT_CHILD(a)) == 59 /* STMT */
		) {
			c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyfvars_NT] + ((struct yystate *)STATE_LABEL(LEFT_CHILD(RIGHT_CHILD(a))))->cost[yyinstrs_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(RIGHT_CHILD(a))))->cost[yyret_NT] + 1;
			yytrace(a, 40, c + 0, p->cost[yybody_NT]);
			if (c + 0 < p->cost[yybody_NT]) {
				p->cost[yybody_NT] = c + 0;
				p->rule.yybody = 1;
				yyclosure_body(a, c + 0);
			}
		}
		if (	/* body: START(NIL,STMT(instrs,ret)) */
			OP_LABEL(LEFT_CHILD(a)) == 293 && /* NIL */
			OP_LABEL(RIGHT_CHILD(a)) == 59 /* STMT */
		) {
			c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(RIGHT_CHILD(a))))->cost[yyinstrs_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(RIGHT_CHILD(a))))->cost[yyret_NT] + 1;
			yytrace(a, 41, c + 0, p->cost[yybody_NT]);
			if (c + 0 < p->cost[yybody_NT]) {
				p->cost[yybody_NT] = c + 0;
				p->rule.yybody = 2;
				yyclosure_body(a, c + 0);
			}
		}
		break;
	case 279: /* FOR */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		if (	/* instr: FOR(UNTIL(expr,expr),STEP(block,expr)) */
			OP_LABEL(LEFT_CHILD(a)) == 280 && /* UNTIL */
			OP_LABEL(RIGHT_CHILD(a)) == 281 /* STEP */
		) {
			c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(LEFT_CHILD(a))))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(LEFT_CHILD(a))))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(LEFT_CHILD(RIGHT_CHILD(a))))->cost[yyblock_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(RIGHT_CHILD(a))))->cost[yyexpr_NT] + 1;
			yytrace(a, 52, c + 0, p->cost[yyinstr_NT]);
			if (c + 0 < p->cost[yyinstr_NT]) {
				p->cost[yyinstr_NT] = c + 0;
				p->rule.yyinstr = 2;
			}
		}
		break;
	case 280: /* UNTIL */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		return;
	case 281: /* STEP */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		return;
	case 282: /* DO */
		return;
	case 283: /* DONE */
		return;
	case 284: /* REPEAT */
		/* loop: REPEAT */
		yytrace(a, 46, 1 + 0, p->cost[yyloop_NT]);
		if (1 + 0 < p->cost[yyloop_NT]) {
			p->cost[yyloop_NT] = 1 + 0;
			p->rule.yyloop = 2;
		}
		break;
	case 285: /* STOP */
		/* loop: STOP */
		yytrace(a, 47, 1 + 0, p->cost[yyloop_NT]);
		if (1 + 0 < p->cost[yyloop_NT]) {
			p->cost[yyloop_NT] = 1 + 0;
			p->rule.yyloop = 3;
		}
		break;
	case 286: /* FARGS */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		return;
	case 287: /* CHARS */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		if (	/* chars: CHARS(NIL,char) */
			OP_LABEL(LEFT_CHILD(a)) == 293 /* NIL */
		) {
			c = ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yychar_NT] + 1;
			yytrace(a, 27, c + 0, p->cost[yychars_NT]);
			if (c + 0 < p->cost[yychars_NT]) {
				p->cost[yychars_NT] = c + 0;
				p->rule.yychars = 1;
				yyclosure_chars(a, c + 0);
			}
		}
		/* chars: CHARS(chars,char) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yychars_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yychar_NT] + 1;
		yytrace(a, 28, c + 0, p->cost[yychars_NT]);
		if (c + 0 < p->cost[yychars_NT]) {
			p->cost[yychars_NT] = c + 0;
			p->rule.yychars = 2;
			yyclosure_chars(a, c + 0);
		}
		break;
	case 288: /* INTS */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		if (	/* ints: INTS(ints,INT) */
			OP_LABEL(RIGHT_CHILD(a)) == 257 /* INT */
		) {
			c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyints_NT] + 1;
			yytrace(a, 35, c + 0, p->cost[yyints_NT]);
			if (c + 0 < p->cost[yyints_NT]) {
				p->cost[yyints_NT] = c + 0;
				p->rule.yyints = 2;
				yyclosure_ints(a, c + 0);
			}
		}
		break;
	case 289: /* ADDR */
		yylabel(LEFT_CHILD(a),a);
		/* expr: ADDR(lval) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yylval_NT] + 1;
		yytrace(a, 65, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 4;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 290: /* VAR */
		yylabel(LEFT_CHILD(a),a);
		/* decl: VAR(vardecl) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyvardecl_NT] + 1;
		yytrace(a, 8, c + 0, p->cost[yydecl_NT]);
		if (c + 0 < p->cost[yydecl_NT]) {
			p->cost[yydecl_NT] = c + 0;
			p->rule.yydecl = 1;
		}
		break;
	case 291: /* ARGS */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		if (	/* fvars: ARGS(NIL,fvar) */
			OP_LABEL(LEFT_CHILD(a)) == 293 /* NIL */
		) {
			c = ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyfvar_NT] + 1;
			yytrace(a, 15, c + 0, p->cost[yyfvars_NT]);
			if (c + 0 < p->cost[yyfvars_NT]) {
				p->cost[yyfvars_NT] = c + 0;
				p->rule.yyfvars = 1;
			}
		}
		/* fvars: ARGS(fvars,fvar) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyfvars_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyfvar_NT] + 1;
		yytrace(a, 16, c + 0, p->cost[yyfvars_NT]);
		if (c + 0 < p->cost[yyfvars_NT]) {
			p->cost[yyfvars_NT] = c + 0;
			p->rule.yyfvars = 2;
		}
		break;
	case 292: /* DECL */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* gdecls: DECL(gdecls,decl) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yygdecls_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yydecl_NT] + 1;
		yytrace(a, 6, c + 0, p->cost[yygdecls_NT]);
		if (c + 0 < p->cost[yygdecls_NT]) {
			p->cost[yygdecls_NT] = c + 0;
			p->rule.yygdecls = 1;
			yyclosure_gdecls(a, c + 0);
		}
		if (	/* gdecls: DECL(NIL,decl) */
			OP_LABEL(LEFT_CHILD(a)) == 293 /* NIL */
		) {
			c = ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yydecl_NT] + 1;
			yytrace(a, 7, c + 0, p->cost[yygdecls_NT]);
			if (c + 0 < p->cost[yygdecls_NT]) {
				p->cost[yygdecls_NT] = c + 0;
				p->rule.yygdecls = 2;
				yyclosure_gdecls(a, c + 0);
			}
		}
		break;
	case 293: /* NIL */
		/* decls: NIL */
		yytrace(a, 4, 0 + 0, p->cost[yydecls_NT]);
		if (0 + 0 < p->cost[yydecls_NT]) {
			p->cost[yydecls_NT] = 0 + 0;
			p->rule.yydecls = 1;
			yyclosure_decls(a, 0 + 0);
		}
		/* decl: NIL */
		yytrace(a, 11, 0 + 0, p->cost[yydecl_NT]);
		if (0 + 0 < p->cost[yydecl_NT]) {
			p->cost[yydecl_NT] = 0 + 0;
			p->rule.yydecl = 4;
		}
		/* vdim: NIL */
		yytrace(a, 21, 0 + 0, p->cost[yyvdim_NT]);
		if (0 + 0 < p->cost[yyvdim_NT]) {
			p->cost[yyvdim_NT] = 0 + 0;
			p->rule.yyvdim = 2;
		}
		/* eqint: NIL */
		yytrace(a, 22, 0 + 0, p->cost[yyeqint_NT]);
		if (0 + 0 < p->cost[yyeqint_NT]) {
			p->cost[yyeqint_NT] = 0 + 0;
			p->rule.yyeqint = 1;
		}
		/* eqstr: NIL */
		yytrace(a, 25, 0 + 0, p->cost[yyeqstr_NT]);
		if (0 + 0 < p->cost[yyeqstr_NT]) {
			p->cost[yyeqstr_NT] = 0 + 0;
			p->rule.yyeqstr = 1;
		}
		/* eqvec: NIL */
		yytrace(a, 32, 0 + 0, p->cost[yyeqvec_NT]);
		if (0 + 0 < p->cost[yyeqvec_NT]) {
			p->cost[yyeqvec_NT] = 0 + 0;
			p->rule.yyeqvec = 1;
		}
		/* eqbody: NIL */
		yytrace(a, 36, 0 + 0, p->cost[yyeqbody_NT]);
		if (0 + 0 < p->cost[yyeqbody_NT]) {
			p->cost[yyeqbody_NT] = 0 + 0;
			p->rule.yyeqbody = 1;
		}
		/* ret: NIL */
		yytrace(a, 44, 0 + 0, p->cost[yyret_NT]);
		if (0 + 0 < p->cost[yyret_NT]) {
			p->cost[yyret_NT] = 0 + 0;
			p->rule.yyret = 3;
			yyclosure_ret(a, 0 + 0);
		}
		/* instrs: NIL */
		yytrace(a, 49, 0 + 0, p->cost[yyinstrs_NT]);
		if (0 + 0 < p->cost[yyinstrs_NT]) {
			p->cost[yyinstrs_NT] = 0 + 0;
			p->rule.yyinstrs = 1;
		}
		/* elifs: NIL */
		yytrace(a, 56, 0 + 0, p->cost[yyelifs_NT]);
		if (0 + 0 < p->cost[yyelifs_NT]) {
			p->cost[yyelifs_NT] = 0 + 0;
			p->rule.yyelifs = 1;
		}
		/* else: NIL */
		yytrace(a, 58, 0 + 0, p->cost[yyelse_NT]);
		if (0 + 0 < p->cost[yyelse_NT]) {
			p->cost[yyelse_NT] = 0 + 0;
			p->rule.yyelse = 1;
		}
		break;
	case 294: /* EQ */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: EQ(expr,lval) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yylval_NT] + 1;
		yytrace(a, 83, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 22;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 295: /* NE */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: NE(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 74, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 13;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 296: /* GE */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: GE(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 75, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 14;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 297: /* LE */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: LE(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 76, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 15;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 298: /* uminus */
		yylabel(LEFT_CHILD(a),a);
		/* expr: uminus(expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 82, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 21;
			yyclosure_expr(a, c + 0);
		}
		break;
	default:
		PANIC("yylabel", "Bad terminal", OP_LABEL(a));
	}
}

static void yykids(NODEPTR_TYPE p, int eruleno, NODEPTR_TYPE kids[]) {
	if (!p)
		PANIC("yykids", "Null tree in rule", eruleno);
	if (!kids)
		PANIC("yykids", "Null kids in", OP_LABEL(p));
	switch (eruleno) {
	case 1: /* file: PROGRAM(finaldecls,FUNCTION(END(ID,INT),FARGS(NIL,main))) */
		kids[0] = LEFT_CHILD(p);
		kids[1] = RIGHT_CHILD(RIGHT_CHILD(RIGHT_CHILD(p)));
		break;
	case 85: /* exprs: COMMA(expr,NIL) */
	case 82: /* expr: uminus(expr) */
	case 81: /* expr: NOT(expr) */
	case 65: /* expr: ADDR(lval) */
	case 61: /* lval: PARE(expr,ID) */
	case 53: /* instr: EXCL(expr) */
	case 43: /* ret: RETURN(expr) */
	case 35: /* ints: INTS(ints,INT) */
	case 8: /* decl: VAR(vardecl) */
	case 2: /* file: MODULE(finaldecls) */
		kids[0] = LEFT_CHILD(p);
		break;
	case 66: /* expr: expr */
	case 63: /* expr: lval */
	case 62: /* expr: chars */
	case 59: /* else: block */
	case 54: /* instr: expr */
	case 45: /* loop: ret */
	case 37: /* eqbody: body */
	case 33: /* eqvec: ints */
	case 26: /* eqstr: chars */
	case 5: /* decls: gdecls */
	case 3: /* finaldecls: decls */
		kids[0] = p;
		break;
	case 64: /* expr: IN */
	case 60: /* lval: ID */
	case 58: /* else: NIL */
	case 56: /* elifs: NIL */
	case 49: /* instrs: NIL */
	case 47: /* loop: STOP */
	case 46: /* loop: REPEAT */
	case 44: /* ret: NIL */
	case 42: /* ret: RETURN(NIL) */
	case 36: /* eqbody: NIL */
	case 34: /* ints: INT */
	case 32: /* eqvec: NIL */
	case 31: /* char: STR */
	case 30: /* char: CHAR */
	case 29: /* char: INT */
	case 25: /* eqstr: NIL */
	case 24: /* eqint: INT */
	case 23: /* eqint: INT */
	case 22: /* eqint: NIL */
	case 21: /* vdim: NIL */
	case 20: /* vdim: INT */
	case 13: /* fvar: STRING(ID,NIL) */
	case 12: /* fvar: NUMBER(ID,NIL) */
	case 11: /* decl: NIL */
	case 4: /* decls: NIL */
		break;
	case 86: /* exprs: COMMA(expr,exprs) */
	case 83: /* expr: EQ(expr,lval) */
	case 80: /* expr: OR(expr,expr) */
	case 79: /* expr: AND(expr,expr) */
	case 78: /* expr: MAX(expr,expr) */
	case 77: /* expr: MIN(expr,expr) */
	case 76: /* expr: LE(expr,expr) */
	case 75: /* expr: GE(expr,expr) */
	case 74: /* expr: NE(expr,expr) */
	case 73: /* expr: EQUAL(expr,expr) */
	case 72: /* expr: POW(expr,expr) */
	case 71: /* expr: MOD(expr,expr) */
	case 70: /* expr: DIV(expr,expr) */
	case 69: /* expr: MUL(expr,expr) */
	case 68: /* expr: SUB(expr,expr) */
	case 67: /* expr: ADD(expr,expr) */
	case 55: /* instr: CARD(expr,lval) */
	case 50: /* instrs: STMT(instrs,instr) */
	case 48: /* block: STMT(instrs,loop) */
	case 38: /* main: START(fvars,instrs) */
	case 28: /* chars: CHARS(chars,char) */
	case 16: /* fvars: ARGS(fvars,fvar) */
	case 6: /* gdecls: DECL(gdecls,decl) */
		kids[0] = LEFT_CHILD(p);
		kids[1] = RIGHT_CHILD(p);
		break;
	case 84: /* expr: CURVE(ID,exprs) */
	case 39: /* main: START(NIL,instrs) */
	case 27: /* chars: CHARS(NIL,char) */
	case 18: /* vardecl: STRING(ID,eqstr) */
	case 17: /* vardecl: NUMBER(ID,eqint) */
	case 15: /* fvars: ARGS(NIL,fvar) */
	case 7: /* gdecls: DECL(NIL,decl) */
		kids[0] = RIGHT_CHILD(p);
		break;
	case 41: /* body: START(NIL,STMT(instrs,ret)) */
	case 19: /* vardecl: ARRAY(ID,INTS(vdim,eqvec)) */
	case 9: /* decl: FUNCTION(END(ID,INT),FARGS(fvars,eqbody)) */
		kids[0] = LEFT_CHILD(RIGHT_CHILD(p));
		kids[1] = RIGHT_CHILD(RIGHT_CHILD(p));
		break;
	case 10: /* decl: FUNCTION(END(ID,INT),FARGS(NIL,eqbody)) */
		kids[0] = RIGHT_CHILD(RIGHT_CHILD(p));
		break;
	case 14: /* fvar: ARRAY(ID,INTS(vdim,NIL)) */
		kids[0] = LEFT_CHILD(RIGHT_CHILD(p));
		break;
	case 57: /* elifs: ELIF(elifs,IF(expr,block)) */
	case 40: /* body: START(fvars,STMT(instrs,ret)) */
		kids[0] = LEFT_CHILD(p);
		kids[1] = LEFT_CHILD(RIGHT_CHILD(p));
		kids[2] = RIGHT_CHILD(RIGHT_CHILD(p));
		break;
	case 51: /* instr: FI(THEN(IF(expr,block),elifs),else) */
		kids[0] = LEFT_CHILD(LEFT_CHILD(LEFT_CHILD(p)));
		kids[1] = RIGHT_CHILD(LEFT_CHILD(LEFT_CHILD(p)));
		kids[2] = RIGHT_CHILD(LEFT_CHILD(p));
		kids[3] = RIGHT_CHILD(p);
		break;
	case 52: /* instr: FOR(UNTIL(expr,expr),STEP(block,expr)) */
		kids[0] = LEFT_CHILD(LEFT_CHILD(p));
		kids[1] = RIGHT_CHILD(LEFT_CHILD(p));
		kids[2] = LEFT_CHILD(RIGHT_CHILD(p));
		kids[3] = RIGHT_CHILD(RIGHT_CHILD(p));
		break;
	default:
		PANIC("yykids", "Bad rule number", eruleno);
	}
}

static void yyreduce(NODEPTR_TYPE p, int goalnt)
{
  int eruleno = yyrule(STATE_LABEL(p), goalnt);
  short *nts = yynts[eruleno];
  NODEPTR_TYPE kids[4];
  int i;

  for (yykids(p, eruleno, kids), i = 0; nts[i]; i++)
    yyreduce(kids[i], nts[i]);

  switch(eruleno) {
	case 1: /* file: PROGRAM(finaldecls,FUNCTION(END(ID,INT),FARGS(NIL,main))) */
		fprintf(stderr, "0x%p: line 46: file: PROGRAM(finaldecls,FUNCTION(END(ID,INT),FARGS(NIL,main)))\n",(void*)p);
#line 46 "minor.brg"
{ fprintf(yyout, pfIMM pfPOP pfLEAVE pfRET, 0); }
		break;
	case 2: /* file: MODULE(finaldecls) */
		fprintf(stderr, "0x%p: line 47: file: MODULE(finaldecls)\n",(void*)p);
#line 47 "minor.brg"
{}
		break;
	case 3: /* finaldecls: decls */
		fprintf(stderr, "0x%p: line 49: finaldecls: decls\n",(void*)p);
#line 49 "minor.brg"
{ fprintf(yyout, pfGLOBL pfTEXT pfALIGN pfLABEL pfENTER , "_main", pfFUNC, "_main", 0); }
		break;
	case 4: /* decls: NIL */
		fprintf(stderr, "0x%p: line 51: decls: NIL\n",(void*)p);
#line 51 "minor.brg"

		break;
	case 5: /* decls: gdecls */
		fprintf(stderr, "0x%p: line 52: decls: gdecls\n",(void*)p);
#line 52 "minor.brg"
{}
		break;
	case 6: /* gdecls: DECL(gdecls,decl) */
		fprintf(stderr, "0x%p: line 54: gdecls: DECL(gdecls,decl)\n",(void*)p);
#line 54 "minor.brg"
{}
		break;
	case 7: /* gdecls: DECL(NIL,decl) */
		fprintf(stderr, "0x%p: line 55: gdecls: DECL(NIL,decl)\n",(void*)p);
#line 55 "minor.brg"
{}
		break;
	case 8: /* decl: VAR(vardecl) */
		fprintf(stderr, "0x%p: line 57: decl: VAR(vardecl)\n",(void*)p);
#line 57 "minor.brg"
{}
		break;
	case 9: /* decl: FUNCTION(END(ID,INT),FARGS(fvars,eqbody)) */
		fprintf(stderr, "0x%p: line 58: decl: FUNCTION(END(ID,INT),FARGS(fvars,eqbody))\n",(void*)p);
#line 58 "minor.brg"
{}
		break;
	case 10: /* decl: FUNCTION(END(ID,INT),FARGS(NIL,eqbody)) */
		fprintf(stderr, "0x%p: line 59: decl: FUNCTION(END(ID,INT),FARGS(NIL,eqbody))\n",(void*)p);
#line 59 "minor.brg"
{}
		break;
	case 11: /* decl: NIL */
		fprintf(stderr, "0x%p: line 60: decl: NIL\n",(void*)p);
#line 60 "minor.brg"

		break;
	case 12: /* fvar: NUMBER(ID,NIL) */
		fprintf(stderr, "0x%p: line 62: fvar: NUMBER(ID,NIL)\n",(void*)p);
#line 62 "minor.brg"
{}
		break;
	case 13: /* fvar: STRING(ID,NIL) */
		fprintf(stderr, "0x%p: line 63: fvar: STRING(ID,NIL)\n",(void*)p);
#line 63 "minor.brg"
{}
		break;
	case 14: /* fvar: ARRAY(ID,INTS(vdim,NIL)) */
		fprintf(stderr, "0x%p: line 64: fvar: ARRAY(ID,INTS(vdim,NIL))\n",(void*)p);
#line 64 "minor.brg"
{}
		break;
	case 15: /* fvars: ARGS(NIL,fvar) */
		fprintf(stderr, "0x%p: line 66: fvars: ARGS(NIL,fvar)\n",(void*)p);
#line 66 "minor.brg"
{}
		break;
	case 16: /* fvars: ARGS(fvars,fvar) */
		fprintf(stderr, "0x%p: line 67: fvars: ARGS(fvars,fvar)\n",(void*)p);
#line 67 "minor.brg"
{}
		break;
	case 17: /* vardecl: NUMBER(ID,eqint) */
		fprintf(stderr, "0x%p: line 69: vardecl: NUMBER(ID,eqint)\n",(void*)p);
#line 69 "minor.brg"
{}
		break;
	case 18: /* vardecl: STRING(ID,eqstr) */
		fprintf(stderr, "0x%p: line 70: vardecl: STRING(ID,eqstr)\n",(void*)p);
#line 70 "minor.brg"
{}
		break;
	case 19: /* vardecl: ARRAY(ID,INTS(vdim,eqvec)) */
		fprintf(stderr, "0x%p: line 71: vardecl: ARRAY(ID,INTS(vdim,eqvec))\n",(void*)p);
#line 71 "minor.brg"
{}
		break;
	case 20: /* vdim: INT */
		fprintf(stderr, "0x%p: line 73: vdim: INT\n",(void*)p);
#line 73 "minor.brg"
{}
		break;
	case 21: /* vdim: NIL */
		fprintf(stderr, "0x%p: line 74: vdim: NIL\n",(void*)p);
#line 74 "minor.brg"

		break;
	case 22: /* eqint: NIL */
		fprintf(stderr, "0x%p: line 76: eqint: NIL\n",(void*)p);
#line 76 "minor.brg"

		break;
	case 23: /* eqint: INT */
		fprintf(stderr, "0x%p: line 77: eqint: INT\n",(void*)p);
#line 77 "minor.brg"
{}
		break;
	case 24: /* eqint: INT */
		fprintf(stderr, "0x%p: line 78: eqint: INT\n",(void*)p);
#line 78 "minor.brg"
{}
		break;
	case 25: /* eqstr: NIL */
		fprintf(stderr, "0x%p: line 80: eqstr: NIL\n",(void*)p);
#line 80 "minor.brg"

		break;
	case 26: /* eqstr: chars */
		fprintf(stderr, "0x%p: line 81: eqstr: chars\n",(void*)p);
#line 81 "minor.brg"
{}
		break;
	case 27: /* chars: CHARS(NIL,char) */
		fprintf(stderr, "0x%p: line 83: chars: CHARS(NIL,char)\n",(void*)p);
#line 83 "minor.brg"
{  }
		break;
	case 28: /* chars: CHARS(chars,char) */
		fprintf(stderr, "0x%p: line 84: chars: CHARS(chars,char)\n",(void*)p);
#line 84 "minor.brg"
{}
		break;
	case 29: /* char: INT */
		fprintf(stderr, "0x%p: line 86: char: INT\n",(void*)p);
#line 86 "minor.brg"
{}
		break;
	case 30: /* char: CHAR */
		fprintf(stderr, "0x%p: line 87: char: CHAR\n",(void*)p);
#line 87 "minor.brg"
{}
		break;
	case 31: /* char: STR */
		fprintf(stderr, "0x%p: line 88: char: STR\n",(void*)p);
#line 88 "minor.brg"
{ char *lb = mklbl(++lbl); fprintf(yyout, pfRODATA pfALIGN pfLABEL pfCHAR, lb , p->value.s); }
		break;
	case 32: /* eqvec: NIL */
		fprintf(stderr, "0x%p: line 90: eqvec: NIL\n",(void*)p);
#line 90 "minor.brg"

		break;
	case 33: /* eqvec: ints */
		fprintf(stderr, "0x%p: line 91: eqvec: ints\n",(void*)p);
#line 91 "minor.brg"
{}
		break;
	case 34: /* ints: INT */
		fprintf(stderr, "0x%p: line 93: ints: INT\n",(void*)p);
#line 93 "minor.brg"
{}
		break;
	case 35: /* ints: INTS(ints,INT) */
		fprintf(stderr, "0x%p: line 94: ints: INTS(ints,INT)\n",(void*)p);
#line 94 "minor.brg"
{}
		break;
	case 36: /* eqbody: NIL */
		fprintf(stderr, "0x%p: line 96: eqbody: NIL\n",(void*)p);
#line 96 "minor.brg"

		break;
	case 37: /* eqbody: body */
		fprintf(stderr, "0x%p: line 97: eqbody: body\n",(void*)p);
#line 97 "minor.brg"
{}
		break;
	case 38: /* main: START(fvars,instrs) */
		fprintf(stderr, "0x%p: line 99: main: START(fvars,instrs)\n",(void*)p);
#line 99 "minor.brg"
{}
		break;
	case 39: /* main: START(NIL,instrs) */
		fprintf(stderr, "0x%p: line 100: main: START(NIL,instrs)\n",(void*)p);
#line 100 "minor.brg"
{}
		break;
	case 40: /* body: START(fvars,STMT(instrs,ret)) */
		fprintf(stderr, "0x%p: line 102: body: START(fvars,STMT(instrs,ret))\n",(void*)p);
#line 102 "minor.brg"
{}
		break;
	case 41: /* body: START(NIL,STMT(instrs,ret)) */
		fprintf(stderr, "0x%p: line 103: body: START(NIL,STMT(instrs,ret))\n",(void*)p);
#line 103 "minor.brg"
{}
		break;
	case 42: /* ret: RETURN(NIL) */
		fprintf(stderr, "0x%p: line 105: ret: RETURN(NIL)\n",(void*)p);
#line 105 "minor.brg"
{}
		break;
	case 43: /* ret: RETURN(expr) */
		fprintf(stderr, "0x%p: line 106: ret: RETURN(expr)\n",(void*)p);
#line 106 "minor.brg"
{}
		break;
	case 44: /* ret: NIL */
		fprintf(stderr, "0x%p: line 107: ret: NIL\n",(void*)p);
#line 107 "minor.brg"

		break;
	case 45: /* loop: ret */
		fprintf(stderr, "0x%p: line 109: loop: ret\n",(void*)p);
#line 109 "minor.brg"
{}
		break;
	case 46: /* loop: REPEAT */
		fprintf(stderr, "0x%p: line 110: loop: REPEAT\n",(void*)p);
#line 110 "minor.brg"
{}
		break;
	case 47: /* loop: STOP */
		fprintf(stderr, "0x%p: line 111: loop: STOP\n",(void*)p);
#line 111 "minor.brg"
{}
		break;
	case 48: /* block: STMT(instrs,loop) */
		fprintf(stderr, "0x%p: line 113: block: STMT(instrs,loop)\n",(void*)p);
#line 113 "minor.brg"
{}
		break;
	case 49: /* instrs: NIL */
		fprintf(stderr, "0x%p: line 115: instrs: NIL\n",(void*)p);
#line 115 "minor.brg"

		break;
	case 50: /* instrs: STMT(instrs,instr) */
		fprintf(stderr, "0x%p: line 116: instrs: STMT(instrs,instr)\n",(void*)p);
#line 116 "minor.brg"
{ /*fprintf(yyout, );*/ }
		break;
	case 51: /* instr: FI(THEN(IF(expr,block),elifs),else) */
		fprintf(stderr, "0x%p: line 118: instr: FI(THEN(IF(expr,block),elifs),else)\n",(void*)p);
#line 118 "minor.brg"
{}
		break;
	case 52: /* instr: FOR(UNTIL(expr,expr),STEP(block,expr)) */
		fprintf(stderr, "0x%p: line 119: instr: FOR(UNTIL(expr,expr),STEP(block,expr))\n",(void*)p);
#line 119 "minor.brg"
{}
		break;
	case 53: /* instr: EXCL(expr) */
		fprintf(stderr, "0x%p: line 120: instr: EXCL(expr)\n",(void*)p);
#line 120 "minor.brg"
{ fprintf(yyout, pfEXTRN pfCALL pfTRASH, "_prints", "_prints", 3);}
		break;
	case 54: /* instr: expr */
		fprintf(stderr, "0x%p: line 121: instr: expr\n",(void*)p);
#line 121 "minor.brg"
{}
		break;
	case 55: /* instr: CARD(expr,lval) */
		fprintf(stderr, "0x%p: line 122: instr: CARD(expr,lval)\n",(void*)p);
#line 122 "minor.brg"
{}
		break;
	case 56: /* elifs: NIL */
		fprintf(stderr, "0x%p: line 124: elifs: NIL\n",(void*)p);
#line 124 "minor.brg"

		break;
	case 57: /* elifs: ELIF(elifs,IF(expr,block)) */
		fprintf(stderr, "0x%p: line 125: elifs: ELIF(elifs,IF(expr,block))\n",(void*)p);
#line 125 "minor.brg"
{}
		break;
	case 58: /* else: NIL */
		fprintf(stderr, "0x%p: line 127: else: NIL\n",(void*)p);
#line 127 "minor.brg"

		break;
	case 59: /* else: block */
		fprintf(stderr, "0x%p: line 128: else: block\n",(void*)p);
#line 128 "minor.brg"
{}
		break;
	case 60: /* lval: ID */
		fprintf(stderr, "0x%p: line 130: lval: ID\n",(void*)p);
#line 130 "minor.brg"
{}
		break;
	case 61: /* lval: PARE(expr,ID) */
		fprintf(stderr, "0x%p: line 131: lval: PARE(expr,ID)\n",(void*)p);
#line 131 "minor.brg"
{}
		break;
	case 62: /* expr: chars */
		fprintf(stderr, "0x%p: line 133: expr: chars\n",(void*)p);
#line 133 "minor.brg"
{ /*fprintf(yyout, pfADDR);*/ }
		break;
	case 63: /* expr: lval */
		fprintf(stderr, "0x%p: line 134: expr: lval\n",(void*)p);
#line 134 "minor.brg"
{}
		break;
	case 64: /* expr: IN */
		fprintf(stderr, "0x%p: line 135: expr: IN\n",(void*)p);
#line 135 "minor.brg"
{}
		break;
	case 65: /* expr: ADDR(lval) */
		fprintf(stderr, "0x%p: line 136: expr: ADDR(lval)\n",(void*)p);
#line 136 "minor.brg"
{}
		break;
	case 66: /* expr: expr */
		fprintf(stderr, "0x%p: line 137: expr: expr\n",(void*)p);
#line 137 "minor.brg"
{}
		break;
	case 67: /* expr: ADD(expr,expr) */
		fprintf(stderr, "0x%p: line 138: expr: ADD(expr,expr)\n",(void*)p);
#line 138 "minor.brg"
{}
		break;
	case 68: /* expr: SUB(expr,expr) */
		fprintf(stderr, "0x%p: line 139: expr: SUB(expr,expr)\n",(void*)p);
#line 139 "minor.brg"
{}
		break;
	case 69: /* expr: MUL(expr,expr) */
		fprintf(stderr, "0x%p: line 140: expr: MUL(expr,expr)\n",(void*)p);
#line 140 "minor.brg"
{}
		break;
	case 70: /* expr: DIV(expr,expr) */
		fprintf(stderr, "0x%p: line 141: expr: DIV(expr,expr)\n",(void*)p);
#line 141 "minor.brg"
{}
		break;
	case 71: /* expr: MOD(expr,expr) */
		fprintf(stderr, "0x%p: line 142: expr: MOD(expr,expr)\n",(void*)p);
#line 142 "minor.brg"
{}
		break;
	case 72: /* expr: POW(expr,expr) */
		fprintf(stderr, "0x%p: line 143: expr: POW(expr,expr)\n",(void*)p);
#line 143 "minor.brg"
{}
		break;
	case 73: /* expr: EQUAL(expr,expr) */
		fprintf(stderr, "0x%p: line 144: expr: EQUAL(expr,expr)\n",(void*)p);
#line 144 "minor.brg"
{}
		break;
	case 74: /* expr: NE(expr,expr) */
		fprintf(stderr, "0x%p: line 145: expr: NE(expr,expr)\n",(void*)p);
#line 145 "minor.brg"
{}
		break;
	case 75: /* expr: GE(expr,expr) */
		fprintf(stderr, "0x%p: line 146: expr: GE(expr,expr)\n",(void*)p);
#line 146 "minor.brg"
{}
		break;
	case 76: /* expr: LE(expr,expr) */
		fprintf(stderr, "0x%p: line 147: expr: LE(expr,expr)\n",(void*)p);
#line 147 "minor.brg"
{}
		break;
	case 77: /* expr: MIN(expr,expr) */
		fprintf(stderr, "0x%p: line 148: expr: MIN(expr,expr)\n",(void*)p);
#line 148 "minor.brg"
{}
		break;
	case 78: /* expr: MAX(expr,expr) */
		fprintf(stderr, "0x%p: line 149: expr: MAX(expr,expr)\n",(void*)p);
#line 149 "minor.brg"
{}
		break;
	case 79: /* expr: AND(expr,expr) */
		fprintf(stderr, "0x%p: line 150: expr: AND(expr,expr)\n",(void*)p);
#line 150 "minor.brg"
{}
		break;
	case 80: /* expr: OR(expr,expr) */
		fprintf(stderr, "0x%p: line 151: expr: OR(expr,expr)\n",(void*)p);
#line 151 "minor.brg"
{}
		break;
	case 81: /* expr: NOT(expr) */
		fprintf(stderr, "0x%p: line 152: expr: NOT(expr)\n",(void*)p);
#line 152 "minor.brg"
{}
		break;
	case 82: /* expr: uminus(expr) */
		fprintf(stderr, "0x%p: line 153: expr: uminus(expr)\n",(void*)p);
#line 153 "minor.brg"
{}
		break;
	case 83: /* expr: EQ(expr,lval) */
		fprintf(stderr, "0x%p: line 154: expr: EQ(expr,lval)\n",(void*)p);
#line 154 "minor.brg"
{}
		break;
	case 84: /* expr: CURVE(ID,exprs) */
		fprintf(stderr, "0x%p: line 155: expr: CURVE(ID,exprs)\n",(void*)p);
#line 155 "minor.brg"
{}
		break;
	case 85: /* exprs: COMMA(expr,NIL) */
		fprintf(stderr, "0x%p: line 157: exprs: COMMA(expr,NIL)\n",(void*)p);
#line 157 "minor.brg"
{}
		break;
	case 86: /* exprs: COMMA(expr,exprs) */
		fprintf(stderr, "0x%p: line 158: exprs: COMMA(expr,exprs)\n",(void*)p);
#line 158 "minor.brg"
{}
		break;
	default: break;
  }
}

int yyselect(NODEPTR_TYPE p)
{
	yylabel(p,p);
	if (((struct yystate *)STATE_LABEL(p))->rule.yyfile == 0) {
		fprintf(stderr, "No match for start symbol (%s).\n", yyntname[1]);
		return 1;
	}
	yyreduce(p, 1);
	return 0;
}


#line 159 "minor.brg"

extern char **yynames;
extern int trace, errors, debugNode;
void evaluate(Node *p) {
	if (errors) return;
	if (trace)  printNode(p, stdout, yynames);
	if (!yyselect(p) && trace) printf("selection successful\n");
}

#ifndef NOTRACE
static void yytrace(NODEPTR_TYPE p, int eruleno, int cost, int bestcost)
{
	int op = OP_LABEL(p);
	YYCONST char *tname = yytermname[op] ? yytermname[op] : "?";
	if (debugNode) fprintf(stderr, "0x%p:%s matched %s with cost %d vs. %d\n", p, tname, yystring[eruleno], cost, bestcost);
	if (cost >= MAX_COST && bestcost >= MAX_COST) {
		fprintf(stderr, "0x%p:%s NO MATCH %s with cost %d vs. %d\n", p, tname, yystring[eruleno], cost, bestcost);
		/*printNode(p, stderr, yynames);*/
	}
}
#endif
