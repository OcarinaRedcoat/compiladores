/*
generated at Wed May 27 20:45:59 2020
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
#include "tabid.h"
#include "postfix.h"
#include "y.tab.h"
#include "minor.h"

#ifndef U_
#define U_ "_"
#endif

#define TRACE
static void yytrace(NODEPTR_TYPE p, int eruleno, int cost, int bestcost);

extern FILE *yyout;
static int lbl, trash, cnt, stp[10], stpn;
static char *mklbl(int n) {
	static char buf[20];
	sprintf(buf, ".L%d", n);
	return strcpy(malloc(strlen(buf)+1),buf);
}
static char *mkfunc(char *s) {
	static char buf[80];
	strcpy(buf, "_");
	strcat(buf, s);
	return buf;
}
static int mkid(Node *p) {
	Node *addr;
	int type = IDfind(p->value.s, (void**)&addr);
	if (addr->attrib == VOID)
		fprintf(yyout, pfLOCAL, (int)addr->place * pfWORD);
	else
		fprintf(yyout, pfADDR, p->value.s);
	return tTYPE(type);
}
static void mkstr(char *s) {
	int l = ++lbl;
	fprintf(yyout, pfDATA pfLABEL, mklbl(l));
	while (*s)
		fprintf(yyout, pfCHAR, (unsigned char)*s++);
	fprintf(yyout, pfCHAR pfTEXT pfADDR, 0, mklbl(l));
}
static int isFunc(NODEPTR_TYPE p) {
	return (p->info & tFUNC) ? 1 : 1000; }

static int isINT(Node *n) { return (LEFT_CHILD(n)->info & tINT && RIGHT_CHILD(n)->info & tINT) ? 1 : 10000; } 
static int isSTR(Node *n) { return (LEFT_CHILD(n)->info & tSTR && RIGHT_CHILD(n)->info & tSTR) ? 1 : 10000; } 

static int onlyINT(Node *n) { return LEFT_CHILD(n)->info & tINT  ? 1 : 10000;} 

static int onlySTR(Node *n) { return LEFT_CHILD(n)->info & tSTR ? 1 : 10000; }


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
#define yydecls_NT 2
#define yyfunc_NT 3
#define yydecl_NT 4
#define yyfargs_NT 5
#define yyfarg_NT 6
#define yyid_NT 7
#define yyend_NT 8
#define yyeargs_NT 9
#define yyenter_NT 10
#define yystmt_NT 11
#define yyvars_NT 12
#define yycond_NT 13
#define yyexpr_NT 14
#define yyif_NT 15
#define yyelifs_NT 16
#define yystr_NT 17
#define yyuntil_NT 18
#define yystep_NT 19
#define yybegin_NT 20
#define yylv_NT 21
#define yydup_NT 22
#define yyand_NT 23
#define yyor_NT 24
#define yyargs_NT 25

static YYCONST char *yyntname[] = {
	0,
	"file",
	"decls",
	"func",
	"decl",
	"fargs",
	"farg",
	"id",
	"end",
	"eargs",
	"enter",
	"stmt",
	"vars",
	"cond",
	"expr",
	"if",
	"elifs",
	"str",
	"until",
	"step",
	"begin",
	"lv",
	"dup",
	"and",
	"or",
	"args",
	0
};

static YYCONST char *yytermname[] = {
 "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
 "", "", "", "", "", "", "", "", "",
	/* 34 */ "PRINT",
 "", "", "",
	/* 38 */ "MOD",
	/* 39 */ "AND",
 "",
	/* 41 */ "CALL",
 "",
	/* 43 */ "MUL",
	/* 44 */ "ADD",
	/* 45 */ "ARG",
	/* 46 */ "SUB",
 "",
	/* 48 */ "DIV",
 "", "", "", "", "", "", "", "", "", "", "",
	/* 60 */ "STMT",
	/* 61 */ "LT",
	/* 62 */ "EQUAL",
	/* 63 */ "GT",
	/* 64 */ "INPUT",
 "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
 "", "", "", "", "", "",
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
	short cost[26];
	struct {
		unsigned int yyfile:2;
		unsigned int yydecls:2;
		unsigned int yyfunc:1;
		unsigned int yydecl:3;
		unsigned int yyfargs:2;
		unsigned int yyfarg:2;
		unsigned int yyid:1;
		unsigned int yyend:1;
		unsigned int yyeargs:2;
		unsigned int yyenter:1;
		unsigned int yystmt:4;
		unsigned int yyvars:2;
		unsigned int yycond:1;
		unsigned int yyexpr:5;
		unsigned int yyif:1;
		unsigned int yyelifs:2;
		unsigned int yystr:1;
		unsigned int yyuntil:1;
		unsigned int yystep:1;
		unsigned int yybegin:1;
		unsigned int yylv:1;
		unsigned int yydup:1;
		unsigned int yyand:1;
		unsigned int yyor:1;
		unsigned int yyargs:2;
	} rule;
};

static short yynts_0[] = { yydecls_NT, 0 };
static short yynts_1[] = { yydecls_NT, yyfunc_NT, 0 };
static short yynts_2[] = { 0 };
static short yynts_3[] = { yydecls_NT, yydecl_NT, 0 };
static short yynts_4[] = { yyfargs_NT, 0 };
static short yynts_5[] = { yyfargs_NT, yyfarg_NT, 0 };
static short yynts_6[] = { yyfunc_NT, 0 };
static short yynts_7[] = { yydecl_NT, 0 };
static short yynts_8[] = { yyid_NT, 0 };
static short yynts_9[] = { yyend_NT, yyeargs_NT, yyenter_NT, yystmt_NT, 0 };
static short yynts_10[] = { yyeargs_NT, yyfarg_NT, 0 };
static short yynts_11[] = { yyvars_NT, 0 };
static short yynts_12[] = { yyvars_NT, yyfarg_NT, 0 };
static short yynts_13[] = { yycond_NT, yystmt_NT, 0 };
static short yynts_14[] = { yyexpr_NT, 0 };
static short yynts_15[] = { yyif_NT, yystmt_NT, 0 };
static short yynts_16[] = { yyif_NT, yyelifs_NT, 0 };
static short yynts_17[] = { yyif_NT, yyelifs_NT, yystmt_NT, 0 };
static short yynts_18[] = { yyelifs_NT, yyif_NT, 0 };
static short yynts_19[] = { yystmt_NT, yystmt_NT, 0 };
static short yynts_20[] = { yystr_NT, 0 };
static short yynts_21[] = { yyuntil_NT, yystep_NT, 0 };
static short yynts_22[] = { yybegin_NT, yyexpr_NT, 0 };
static short yynts_23[] = { yystmt_NT, yyexpr_NT, 0 };
static short yynts_24[] = { yydup_NT, yylv_NT, 0 };
static short yynts_25[] = { yylv_NT, 0 };
static short yynts_26[] = { yyexpr_NT, yyexpr_NT, 0 };
static short yynts_27[] = { yyand_NT, yyexpr_NT, 0 };
static short yynts_28[] = { yyor_NT, yyexpr_NT, 0 };
static short yynts_29[] = { yyargs_NT, 0 };
static short yynts_30[] = { yyexpr_NT, yyargs_NT, 0 };

static short *yynts[] = {
	0,	/* 0 */
	yynts_0,	/* 1 */
	yynts_1,	/* 2 */
	yynts_2,	/* 3 */
	yynts_3,	/* 4 */
	yynts_2,	/* 5 */
	yynts_4,	/* 6 */
	yynts_5,	/* 7 */
	yynts_2,	/* 8 */
	yynts_2,	/* 9 */
	yynts_2,	/* 10 */
	yynts_6,	/* 11 */
	yynts_7,	/* 12 */
	yynts_8,	/* 13 */
	yynts_8,	/* 14 */
	yynts_2,	/* 15 */
	yynts_9,	/* 16 */
	yynts_2,	/* 17 */
	yynts_10,	/* 18 */
	yynts_2,	/* 19 */
	yynts_11,	/* 20 */
	yynts_12,	/* 21 */
	yynts_2,	/* 22 */
	yynts_13,	/* 23 */
	yynts_14,	/* 24 */
	yynts_15,	/* 25 */
	yynts_13,	/* 26 */
	yynts_16,	/* 27 */
	yynts_17,	/* 28 */
	yynts_2,	/* 29 */
	yynts_18,	/* 30 */
	yynts_19,	/* 31 */
	yynts_2,	/* 32 */
	yynts_2,	/* 33 */
	yynts_14,	/* 34 */
	yynts_2,	/* 35 */
	yynts_14,	/* 36 */
	yynts_14,	/* 37 */
	yynts_20,	/* 38 */
	yynts_2,	/* 39 */
	yynts_14,	/* 40 */
	yynts_21,	/* 41 */
	yynts_22,	/* 42 */
	yynts_14,	/* 43 */
	yynts_23,	/* 44 */
	yynts_2,	/* 45 */
	yynts_24,	/* 46 */
	yynts_14,	/* 47 */
	yynts_25,	/* 48 */
	yynts_2,	/* 49 */
	yynts_2,	/* 50 */
	yynts_2,	/* 51 */
	yynts_25,	/* 52 */
	yynts_26,	/* 53 */
	yynts_26,	/* 54 */
	yynts_26,	/* 55 */
	yynts_26,	/* 56 */
	yynts_26,	/* 57 */
	yynts_26,	/* 58 */
	yynts_26,	/* 59 */
	yynts_26,	/* 60 */
	yynts_26,	/* 61 */
	yynts_26,	/* 62 */
	yynts_26,	/* 63 */
	yynts_26,	/* 64 */
	yynts_27,	/* 65 */
	yynts_14,	/* 66 */
	yynts_28,	/* 67 */
	yynts_14,	/* 68 */
	yynts_14,	/* 69 */
	yynts_14,	/* 70 */
	yynts_26,	/* 71 */
	yynts_26,	/* 72 */
	yynts_29,	/* 73 */
	yynts_30,	/* 74 */
	yynts_2,	/* 75 */
};


static YYCONST char *yystring[] = {
/* 0 */	0,
/* 1 */	"file: MODULE(decls)",
/* 2 */	"file: PROGRAM(decls,func)",
/* 3 */	"decls: NIL",
/* 4 */	"decls: DECL(decls,decl)",
/* 5 */	"decl: NIL",
/* 6 */	"decl: FUNCTION(END,FARGS(fargs,NIL))",
/* 7 */	"fargs: ARGS(fargs,farg)",
/* 8 */	"fargs: NIL",
/* 9 */	"farg: NUMBER(ID,NIL)",
/* 10 */	"farg: STRING(ID,NIL)",
/* 11 */	"decl: func",
/* 12 */	"decl: VAR(decl)",
/* 13 */	"decl: NUMBER(id,NIL)",
/* 14 */	"decl: NUMBER(id,INT)",
/* 15 */	"id: ID",
/* 16 */	"func: FUNCTION(end,FARGS(eargs,START(enter,stmt)))",
/* 17 */	"end: END",
/* 18 */	"eargs: ARGS(eargs,farg)",
/* 19 */	"eargs: NIL",
/* 20 */	"enter: vars",
/* 21 */	"vars: ARGS(vars,farg)",
/* 22 */	"vars: NIL",
/* 23 */	"stmt: FI(THEN(IF(cond,stmt),NIL),NIL)",
/* 24 */	"cond: expr",
/* 25 */	"stmt: FI(THEN(if,NIL),stmt)",
/* 26 */	"if: IF(cond,stmt)",
/* 27 */	"stmt: FI(THEN(if,elifs),NIL)",
/* 28 */	"stmt: FI(THEN(if,elifs),stmt)",
/* 29 */	"elifs: NIL",
/* 30 */	"elifs: ELIF(elifs,if)",
/* 31 */	"stmt: STMT(stmt,stmt)",
/* 32 */	"stmt: NIL",
/* 33 */	"stmt: RETURN(NIL)",
/* 34 */	"stmt: RETURN(expr)",
/* 35 */	"stmt: STOP",
/* 36 */	"stmt: PRINT(expr)",
/* 37 */	"stmt: PRINT(expr)",
/* 38 */	"expr: str",
/* 39 */	"str: CHARS(NIL,STR)",
/* 40 */	"stmt: expr",
/* 41 */	"stmt: FOR(until,step)",
/* 42 */	"until: UNTIL(begin,expr)",
/* 43 */	"begin: expr",
/* 44 */	"step: STEP(stmt,expr)",
/* 45 */	"lv: ID",
/* 46 */	"expr: EQ(dup,lv)",
/* 47 */	"dup: expr",
/* 48 */	"expr: lv",
/* 49 */	"expr: CHARS(NIL,INT)",
/* 50 */	"expr: ID",
/* 51 */	"expr: INPUT",
/* 52 */	"expr: ADDR(lv)",
/* 53 */	"expr: ADD(expr,expr)",
/* 54 */	"expr: SUB(expr,expr)",
/* 55 */	"expr: MUL(expr,expr)",
/* 56 */	"expr: DIV(expr,expr)",
/* 57 */	"expr: MOD(expr,expr)",
/* 58 */	"expr: POW(expr,expr)",
/* 59 */	"expr: NE(expr,expr)",
/* 60 */	"expr: NE(expr,expr)",
/* 61 */	"expr: EQUAL(expr,expr)",
/* 62 */	"expr: EQUAL(expr,expr)",
/* 63 */	"expr: GE(expr,expr)",
/* 64 */	"expr: LE(expr,expr)",
/* 65 */	"expr: AND(and,expr)",
/* 66 */	"and: expr",
/* 67 */	"expr: OR(or,expr)",
/* 68 */	"or: expr",
/* 69 */	"expr: NOT(expr)",
/* 70 */	"expr: uminus(expr)",
/* 71 */	"expr: GT(expr,expr)",
/* 72 */	"expr: LT(expr,expr)",
/* 73 */	"expr: CALL(ID,args)",
/* 74 */	"args: ARG(expr,args)",
/* 75 */	"args: NIL",
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

static short yydecode_decls[] = {
	0,
	3,
	4,
};

static short yydecode_func[] = {
	0,
	16,
};

static short yydecode_decl[] = {
	0,
	5,
	6,
	11,
	12,
	13,
	14,
};

static short yydecode_fargs[] = {
	0,
	7,
	8,
};

static short yydecode_farg[] = {
	0,
	9,
	10,
};

static short yydecode_id[] = {
	0,
	15,
};

static short yydecode_end[] = {
	0,
	17,
};

static short yydecode_eargs[] = {
	0,
	18,
	19,
};

static short yydecode_enter[] = {
	0,
	20,
};

static short yydecode_stmt[] = {
	0,
	23,
	25,
	27,
	28,
	31,
	32,
	33,
	34,
	35,
	36,
	37,
	40,
	41,
};

static short yydecode_vars[] = {
	0,
	21,
	22,
};

static short yydecode_cond[] = {
	0,
	24,
};

static short yydecode_expr[] = {
	0,
	38,
	46,
	48,
	49,
	50,
	51,
	52,
	53,
	54,
	55,
	56,
	57,
	58,
	59,
	60,
	61,
	62,
	63,
	64,
	65,
	67,
	69,
	70,
	71,
	72,
	73,
};

static short yydecode_if[] = {
	0,
	26,
};

static short yydecode_elifs[] = {
	0,
	29,
	30,
};

static short yydecode_str[] = {
	0,
	39,
};

static short yydecode_until[] = {
	0,
	42,
};

static short yydecode_step[] = {
	0,
	44,
};

static short yydecode_begin[] = {
	0,
	43,
};

static short yydecode_lv[] = {
	0,
	45,
};

static short yydecode_dup[] = {
	0,
	47,
};

static short yydecode_and[] = {
	0,
	66,
};

static short yydecode_or[] = {
	0,
	68,
};

static short yydecode_args[] = {
	0,
	74,
	75,
};

static int yyrule(void *state, int goalnt) {
	if (goalnt < 1 || goalnt > 25)
		PANIC("yyrule", "Bad goal nonterminal", goalnt);
	if (!state)
		return 0;
	switch (goalnt) {
	case yyfile_NT:	return yydecode_file[((struct yystate *)state)->rule.yyfile];
	case yydecls_NT:	return yydecode_decls[((struct yystate *)state)->rule.yydecls];
	case yyfunc_NT:	return yydecode_func[((struct yystate *)state)->rule.yyfunc];
	case yydecl_NT:	return yydecode_decl[((struct yystate *)state)->rule.yydecl];
	case yyfargs_NT:	return yydecode_fargs[((struct yystate *)state)->rule.yyfargs];
	case yyfarg_NT:	return yydecode_farg[((struct yystate *)state)->rule.yyfarg];
	case yyid_NT:	return yydecode_id[((struct yystate *)state)->rule.yyid];
	case yyend_NT:	return yydecode_end[((struct yystate *)state)->rule.yyend];
	case yyeargs_NT:	return yydecode_eargs[((struct yystate *)state)->rule.yyeargs];
	case yyenter_NT:	return yydecode_enter[((struct yystate *)state)->rule.yyenter];
	case yystmt_NT:	return yydecode_stmt[((struct yystate *)state)->rule.yystmt];
	case yyvars_NT:	return yydecode_vars[((struct yystate *)state)->rule.yyvars];
	case yycond_NT:	return yydecode_cond[((struct yystate *)state)->rule.yycond];
	case yyexpr_NT:	return yydecode_expr[((struct yystate *)state)->rule.yyexpr];
	case yyif_NT:	return yydecode_if[((struct yystate *)state)->rule.yyif];
	case yyelifs_NT:	return yydecode_elifs[((struct yystate *)state)->rule.yyelifs];
	case yystr_NT:	return yydecode_str[((struct yystate *)state)->rule.yystr];
	case yyuntil_NT:	return yydecode_until[((struct yystate *)state)->rule.yyuntil];
	case yystep_NT:	return yydecode_step[((struct yystate *)state)->rule.yystep];
	case yybegin_NT:	return yydecode_begin[((struct yystate *)state)->rule.yybegin];
	case yylv_NT:	return yydecode_lv[((struct yystate *)state)->rule.yylv];
	case yydup_NT:	return yydecode_dup[((struct yystate *)state)->rule.yydup];
	case yyand_NT:	return yydecode_and[((struct yystate *)state)->rule.yyand];
	case yyor_NT:	return yydecode_or[((struct yystate *)state)->rule.yyor];
	case yyargs_NT:	return yydecode_args[((struct yystate *)state)->rule.yyargs];
	default:
		PANIC("yyrule", "Bad goal nonterminal", goalnt);
		return 0;
	}
}

static void yyclosure_func(NODEPTR_TYPE, int);
static void yyclosure_vars(NODEPTR_TYPE, int);
static void yyclosure_expr(NODEPTR_TYPE, int);
static void yyclosure_str(NODEPTR_TYPE, int);
static void yyclosure_lv(NODEPTR_TYPE, int);

static void yyclosure_func(NODEPTR_TYPE a, int c) {
	struct yystate *p = (struct yystate *)STATE_LABEL(a);
	yytrace(a, 11, c + 0, p->cost[yydecl_NT]);
	if (c + 0 < p->cost[yydecl_NT]) {
		p->cost[yydecl_NT] = c + 0;
		p->rule.yydecl = 3;
	}
}

static void yyclosure_vars(NODEPTR_TYPE a, int c) {
	struct yystate *p = (struct yystate *)STATE_LABEL(a);
	yytrace(a, 20, c + 1, p->cost[yyenter_NT]);
	if (c + 1 < p->cost[yyenter_NT]) {
		p->cost[yyenter_NT] = c + 1;
		p->rule.yyenter = 1;
	}
}

static void yyclosure_expr(NODEPTR_TYPE a, int c) {
	struct yystate *p = (struct yystate *)STATE_LABEL(a);
	yytrace(a, 68, c + 1, p->cost[yyor_NT]);
	if (c + 1 < p->cost[yyor_NT]) {
		p->cost[yyor_NT] = c + 1;
		p->rule.yyor = 1;
	}
	yytrace(a, 66, c + 1, p->cost[yyand_NT]);
	if (c + 1 < p->cost[yyand_NT]) {
		p->cost[yyand_NT] = c + 1;
		p->rule.yyand = 1;
	}
	yytrace(a, 47, c + 1, p->cost[yydup_NT]);
	if (c + 1 < p->cost[yydup_NT]) {
		p->cost[yydup_NT] = c + 1;
		p->rule.yydup = 1;
	}
	yytrace(a, 43, c + 1, p->cost[yybegin_NT]);
	if (c + 1 < p->cost[yybegin_NT]) {
		p->cost[yybegin_NT] = c + 1;
		p->rule.yybegin = 1;
	}
	yytrace(a, 40, c + 1, p->cost[yystmt_NT]);
	if (c + 1 < p->cost[yystmt_NT]) {
		p->cost[yystmt_NT] = c + 1;
		p->rule.yystmt = 12;
	}
	yytrace(a, 24, c + 1, p->cost[yycond_NT]);
	if (c + 1 < p->cost[yycond_NT]) {
		p->cost[yycond_NT] = c + 1;
		p->rule.yycond = 1;
	}
}

static void yyclosure_str(NODEPTR_TYPE a, int c) {
	struct yystate *p = (struct yystate *)STATE_LABEL(a);
	yytrace(a, 38, c + 1000, p->cost[yyexpr_NT]);
	if (c + 1000 < p->cost[yyexpr_NT]) {
		p->cost[yyexpr_NT] = c + 1000;
		p->rule.yyexpr = 1;
		yyclosure_expr(a, c + 1000);
	}
}

static void yyclosure_lv(NODEPTR_TYPE a, int c) {
	struct yystate *p = (struct yystate *)STATE_LABEL(a);
	yytrace(a, 48, c + 1, p->cost[yyexpr_NT]);
	if (c + 1 < p->cost[yyexpr_NT]) {
		p->cost[yyexpr_NT] = c + 1;
		p->rule.yyexpr = 3;
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
		0x7fff;
	switch (OP_LABEL(a)) {
	case 33: /* PRINT */
		yylabel(LEFT_CHILD(a),a);
		/* stmt: PRINT(expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + (onlyINT(a));
		yytrace(a, 36, c + 0, p->cost[yystmt_NT]);
		if (c + 0 < p->cost[yystmt_NT]) {
			p->cost[yystmt_NT] = c + 0;
			p->rule.yystmt = 10;
		}
		/* stmt: PRINT(expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + (onlySTR(a));
		yytrace(a, 37, c + 0, p->cost[yystmt_NT]);
		if (c + 0 < p->cost[yystmt_NT]) {
			p->cost[yystmt_NT] = c + 0;
			p->rule.yystmt = 11;
		}
		break;
	case 37: /* MOD */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: MOD(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + (isINT(a));
		yytrace(a, 57, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 12;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 38: /* AND */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: AND(and,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyand_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + (isINT(a));
		yytrace(a, 65, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 20;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 40: /* CALL */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		if (	/* expr: CALL(ID,args) */
			OP_LABEL(LEFT_CHILD(a)) == 259 /* ID */
		) {
			c = ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyargs_NT] + 3;
			yytrace(a, 73, c + 0, p->cost[yyexpr_NT]);
			if (c + 0 < p->cost[yyexpr_NT]) {
				p->cost[yyexpr_NT] = c + 0;
				p->rule.yyexpr = 26;
				yyclosure_expr(a, c + 0);
			}
		}
		break;
	case 42: /* MUL */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: MUL(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + (isINT(a));
		yytrace(a, 55, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 10;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 43: /* ADD */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: ADD(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 53, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 8;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 44: /* ARG */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* args: ARG(expr,args) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyargs_NT] + 1;
		yytrace(a, 74, c + 0, p->cost[yyargs_NT]);
		if (c + 0 < p->cost[yyargs_NT]) {
			p->cost[yyargs_NT] = c + 0;
			p->rule.yyargs = 1;
		}
		break;
	case 45: /* SUB */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: SUB(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 54, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 9;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 47: /* DIV */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: DIV(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + (isINT(a));
		yytrace(a, 56, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 11;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 59: /* STMT */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* stmt: STMT(stmt,stmt) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yystmt_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yystmt_NT] + 0;
		yytrace(a, 31, c + 0, p->cost[yystmt_NT]);
		if (c + 0 < p->cost[yystmt_NT]) {
			p->cost[yystmt_NT] = c + 0;
			p->rule.yystmt = 5;
		}
		break;
	case 60: /* LT */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: LT(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 72, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 25;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 61: /* EQUAL */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: EQUAL(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + (isINT(a));
		yytrace(a, 61, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 16;
			yyclosure_expr(a, c + 0);
		}
		/* expr: EQUAL(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + (isSTR(a));
		yytrace(a, 62, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 17;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 62: /* GT */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: GT(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 71, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 24;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 63: /* INPUT */
		/* expr: INPUT */
		yytrace(a, 51, 1 + 0, p->cost[yyexpr_NT]);
		if (1 + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = 1 + 0;
			p->rule.yyexpr = 6;
			yyclosure_expr(a, 1 + 0);
		}
		break;
	case 94: /* POW */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: POW(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + (isINT(a));
		yytrace(a, 58, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 13;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 124: /* OR */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: OR(or,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyor_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + (isINT(a));
		yytrace(a, 67, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 21;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 126: /* NOT */
		yylabel(LEFT_CHILD(a),a);
		/* expr: NOT(expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 69, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 22;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 257: /* INT */
		return;
	case 258: /* CHAR */
		return;
	case 259: /* ID */
		/* id: ID */
		yytrace(a, 15, 1 + 0, p->cost[yyid_NT]);
		if (1 + 0 < p->cost[yyid_NT]) {
			p->cost[yyid_NT] = 1 + 0;
			p->rule.yyid = 1;
		}
		/* lv: ID */
		yytrace(a, 45, 1 + 0, p->cost[yylv_NT]);
		if (1 + 0 < p->cost[yylv_NT]) {
			p->cost[yylv_NT] = 1 + 0;
			p->rule.yylv = 1;
			yyclosure_lv(a, 1 + 0);
		}
		/* expr: ID */
		c = (isFunc(a));
		yytrace(a, 50, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 5;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 260: /* STR */
		return;
	case 261: /* PROGRAM */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* file: PROGRAM(decls,func) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yydecls_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyfunc_NT] + 0;
		yytrace(a, 2, c + 0, p->cost[yyfile_NT]);
		if (c + 0 < p->cost[yyfile_NT]) {
			p->cost[yyfile_NT] = c + 0;
			p->rule.yyfile = 2;
		}
		break;
	case 262: /* MODULE */
		yylabel(LEFT_CHILD(a),a);
		/* file: MODULE(decls) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yydecls_NT] + 0;
		yytrace(a, 1, c + 0, p->cost[yyfile_NT]);
		if (c + 0 < p->cost[yyfile_NT]) {
			p->cost[yyfile_NT] = c + 0;
			p->rule.yyfile = 1;
		}
		break;
	case 263: /* END */
		/* end: END */
		yytrace(a, 17, 1 + 0, p->cost[yyend_NT]);
		if (1 + 0 < p->cost[yyend_NT]) {
			p->cost[yyend_NT] = 1 + 0;
			p->rule.yyend = 1;
		}
		break;
	case 264: /* PUBLIC */
		return;
	case 265: /* FORWARD */
		return;
	case 266: /* STRING */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		if (	/* farg: STRING(ID,NIL) */
			OP_LABEL(LEFT_CHILD(a)) == 259 && /* ID */
			OP_LABEL(RIGHT_CHILD(a)) == 293 /* NIL */
		) {
			c = 0;
			yytrace(a, 10, c + 0, p->cost[yyfarg_NT]);
			if (c + 0 < p->cost[yyfarg_NT]) {
				p->cost[yyfarg_NT] = c + 0;
				p->rule.yyfarg = 2;
			}
		}
		break;
	case 267: /* NUMBER */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		if (	/* farg: NUMBER(ID,NIL) */
			OP_LABEL(LEFT_CHILD(a)) == 259 && /* ID */
			OP_LABEL(RIGHT_CHILD(a)) == 293 /* NIL */
		) {
			c = 0;
			yytrace(a, 9, c + 0, p->cost[yyfarg_NT]);
			if (c + 0 < p->cost[yyfarg_NT]) {
				p->cost[yyfarg_NT] = c + 0;
				p->rule.yyfarg = 1;
			}
		}
		if (	/* decl: NUMBER(id,NIL) */
			OP_LABEL(RIGHT_CHILD(a)) == 293 /* NIL */
		) {
			c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyid_NT] + 1;
			yytrace(a, 13, c + 0, p->cost[yydecl_NT]);
			if (c + 0 < p->cost[yydecl_NT]) {
				p->cost[yydecl_NT] = c + 0;
				p->rule.yydecl = 5;
			}
		}
		if (	/* decl: NUMBER(id,INT) */
			OP_LABEL(RIGHT_CHILD(a)) == 257 /* INT */
		) {
			c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyid_NT] + 1;
			yytrace(a, 14, c + 0, p->cost[yydecl_NT]);
			if (c + 0 < p->cost[yydecl_NT]) {
				p->cost[yydecl_NT] = c + 0;
				p->rule.yydecl = 6;
			}
		}
		break;
	case 268: /* ARRAY */
		return;
	case 269: /* FUNCTION */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		if (	/* decl: FUNCTION(END,FARGS(fargs,NIL)) */
			OP_LABEL(LEFT_CHILD(a)) == 263 && /* END */
			OP_LABEL(RIGHT_CHILD(a)) == 286 && /* FARGS */
			OP_LABEL(RIGHT_CHILD(RIGHT_CHILD(a))) == 293 /* NIL */
		) {
			c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(RIGHT_CHILD(a))))->cost[yyfargs_NT] + 1;
			yytrace(a, 6, c + 0, p->cost[yydecl_NT]);
			if (c + 0 < p->cost[yydecl_NT]) {
				p->cost[yydecl_NT] = c + 0;
				p->rule.yydecl = 2;
			}
		}
		if (	/* func: FUNCTION(end,FARGS(eargs,START(enter,stmt))) */
			OP_LABEL(RIGHT_CHILD(a)) == 286 && /* FARGS */
			OP_LABEL(RIGHT_CHILD(RIGHT_CHILD(a))) == 278 /* START */
		) {
			c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyend_NT] + ((struct yystate *)STATE_LABEL(LEFT_CHILD(RIGHT_CHILD(a))))->cost[yyeargs_NT] + ((struct yystate *)STATE_LABEL(LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))))->cost[yyenter_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(RIGHT_CHILD(RIGHT_CHILD(a)))))->cost[yystmt_NT] + 1;
			yytrace(a, 16, c + 0, p->cost[yyfunc_NT]);
			if (c + 0 < p->cost[yyfunc_NT]) {
				p->cost[yyfunc_NT] = c + 0;
				p->rule.yyfunc = 1;
				yyclosure_func(a, c + 0);
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
		/* if: IF(cond,stmt) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yycond_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yystmt_NT] + 1;
		yytrace(a, 26, c + 0, p->cost[yyif_NT]);
		if (c + 0 < p->cost[yyif_NT]) {
			p->cost[yyif_NT] = c + 0;
			p->rule.yyif = 1;
		}
		break;
	case 273: /* THEN */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		return;
	case 274: /* FI */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		if (	/* stmt: FI(THEN(IF(cond,stmt),NIL),NIL) */
			OP_LABEL(LEFT_CHILD(a)) == 273 && /* THEN */
			OP_LABEL(LEFT_CHILD(LEFT_CHILD(a))) == 272 && /* IF */
			OP_LABEL(RIGHT_CHILD(LEFT_CHILD(a))) == 293 && /* NIL */
			OP_LABEL(RIGHT_CHILD(a)) == 293 /* NIL */
		) {
			c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(LEFT_CHILD(LEFT_CHILD(a)))))->cost[yycond_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(LEFT_CHILD(LEFT_CHILD(a)))))->cost[yystmt_NT] + 1;
			yytrace(a, 23, c + 0, p->cost[yystmt_NT]);
			if (c + 0 < p->cost[yystmt_NT]) {
				p->cost[yystmt_NT] = c + 0;
				p->rule.yystmt = 1;
			}
		}
		if (	/* stmt: FI(THEN(if,NIL),stmt) */
			OP_LABEL(LEFT_CHILD(a)) == 273 && /* THEN */
			OP_LABEL(RIGHT_CHILD(LEFT_CHILD(a))) == 293 /* NIL */
		) {
			c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(LEFT_CHILD(a))))->cost[yyif_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yystmt_NT] + 1;
			yytrace(a, 25, c + 0, p->cost[yystmt_NT]);
			if (c + 0 < p->cost[yystmt_NT]) {
				p->cost[yystmt_NT] = c + 0;
				p->rule.yystmt = 2;
			}
		}
		if (	/* stmt: FI(THEN(if,elifs),NIL) */
			OP_LABEL(LEFT_CHILD(a)) == 273 && /* THEN */
			OP_LABEL(RIGHT_CHILD(a)) == 293 /* NIL */
		) {
			c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(LEFT_CHILD(a))))->cost[yyif_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(LEFT_CHILD(a))))->cost[yyelifs_NT] + 1;
			yytrace(a, 27, c + 0, p->cost[yystmt_NT]);
			if (c + 0 < p->cost[yystmt_NT]) {
				p->cost[yystmt_NT] = c + 0;
				p->rule.yystmt = 3;
			}
		}
		if (	/* stmt: FI(THEN(if,elifs),stmt) */
			OP_LABEL(LEFT_CHILD(a)) == 273 /* THEN */
		) {
			c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(LEFT_CHILD(a))))->cost[yyif_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(LEFT_CHILD(a))))->cost[yyelifs_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yystmt_NT] + 1;
			yytrace(a, 28, c + 0, p->cost[yystmt_NT]);
			if (c + 0 < p->cost[yystmt_NT]) {
				p->cost[yystmt_NT] = c + 0;
				p->rule.yystmt = 4;
			}
		}
		break;
	case 275: /* ELIF */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* elifs: ELIF(elifs,if) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyelifs_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyif_NT] + 1;
		yytrace(a, 30, c + 0, p->cost[yyelifs_NT]);
		if (c + 0 < p->cost[yyelifs_NT]) {
			p->cost[yyelifs_NT] = c + 0;
			p->rule.yyelifs = 2;
		}
		break;
	case 276: /* ELSE */
		return;
	case 277: /* RETURN */
		yylabel(LEFT_CHILD(a),a);
		if (	/* stmt: RETURN(NIL) */
			OP_LABEL(LEFT_CHILD(a)) == 293 /* NIL */
		) {
			c = 2;
			yytrace(a, 33, c + 0, p->cost[yystmt_NT]);
			if (c + 0 < p->cost[yystmt_NT]) {
				p->cost[yystmt_NT] = c + 0;
				p->rule.yystmt = 7;
			}
		}
		/* stmt: RETURN(expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + 3;
		yytrace(a, 34, c + 0, p->cost[yystmt_NT]);
		if (c + 0 < p->cost[yystmt_NT]) {
			p->cost[yystmt_NT] = c + 0;
			p->rule.yystmt = 8;
		}
		break;
	case 278: /* START */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		return;
	case 279: /* FOR */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* stmt: FOR(until,step) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyuntil_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yystep_NT] + 1;
		yytrace(a, 41, c + 0, p->cost[yystmt_NT]);
		if (c + 0 < p->cost[yystmt_NT]) {
			p->cost[yystmt_NT] = c + 0;
			p->rule.yystmt = 13;
		}
		break;
	case 280: /* UNTIL */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* until: UNTIL(begin,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yybegin_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + 2;
		yytrace(a, 42, c + 0, p->cost[yyuntil_NT]);
		if (c + 0 < p->cost[yyuntil_NT]) {
			p->cost[yyuntil_NT] = c + 0;
			p->rule.yyuntil = 1;
		}
		break;
	case 281: /* STEP */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* step: STEP(stmt,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yystmt_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 44, c + 0, p->cost[yystep_NT]);
		if (c + 0 < p->cost[yystep_NT]) {
			p->cost[yystep_NT] = c + 0;
			p->rule.yystep = 1;
		}
		break;
	case 282: /* DO */
		return;
	case 283: /* DONE */
		return;
	case 284: /* REPEAT */
		return;
	case 285: /* STOP */
		/* stmt: STOP */
		yytrace(a, 35, 1 + 0, p->cost[yystmt_NT]);
		if (1 + 0 < p->cost[yystmt_NT]) {
			p->cost[yystmt_NT] = 1 + 0;
			p->rule.yystmt = 9;
		}
		break;
	case 286: /* FARGS */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		return;
	case 287: /* CHARS */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		if (	/* str: CHARS(NIL,STR) */
			OP_LABEL(LEFT_CHILD(a)) == 293 && /* NIL */
			OP_LABEL(RIGHT_CHILD(a)) == 260 /* STR */
		) {
			c = 2;
			yytrace(a, 39, c + 0, p->cost[yystr_NT]);
			if (c + 0 < p->cost[yystr_NT]) {
				p->cost[yystr_NT] = c + 0;
				p->rule.yystr = 1;
				yyclosure_str(a, c + 0);
			}
		}
		if (	/* expr: CHARS(NIL,INT) */
			OP_LABEL(LEFT_CHILD(a)) == 293 && /* NIL */
			OP_LABEL(RIGHT_CHILD(a)) == 257 /* INT */
		) {
			c = 1;
			yytrace(a, 49, c + 0, p->cost[yyexpr_NT]);
			if (c + 0 < p->cost[yyexpr_NT]) {
				p->cost[yyexpr_NT] = c + 0;
				p->rule.yyexpr = 4;
				yyclosure_expr(a, c + 0);
			}
		}
		break;
	case 288: /* INTS */
		return;
	case 289: /* ADDR */
		yylabel(LEFT_CHILD(a),a);
		/* expr: ADDR(lv) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yylv_NT] + 0;
		yytrace(a, 52, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 7;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 290: /* VAR */
		yylabel(LEFT_CHILD(a),a);
		/* decl: VAR(decl) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yydecl_NT] + 0;
		yytrace(a, 12, c + 0, p->cost[yydecl_NT]);
		if (c + 0 < p->cost[yydecl_NT]) {
			p->cost[yydecl_NT] = c + 0;
			p->rule.yydecl = 4;
		}
		break;
	case 291: /* ARGS */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* fargs: ARGS(fargs,farg) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyfargs_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyfarg_NT] + 0;
		yytrace(a, 7, c + 0, p->cost[yyfargs_NT]);
		if (c + 0 < p->cost[yyfargs_NT]) {
			p->cost[yyfargs_NT] = c + 0;
			p->rule.yyfargs = 1;
		}
		/* eargs: ARGS(eargs,farg) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyeargs_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyfarg_NT] + 0;
		yytrace(a, 18, c + 0, p->cost[yyeargs_NT]);
		if (c + 0 < p->cost[yyeargs_NT]) {
			p->cost[yyeargs_NT] = c + 0;
			p->rule.yyeargs = 1;
		}
		/* vars: ARGS(vars,farg) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyvars_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyfarg_NT] + 0;
		yytrace(a, 21, c + 0, p->cost[yyvars_NT]);
		if (c + 0 < p->cost[yyvars_NT]) {
			p->cost[yyvars_NT] = c + 0;
			p->rule.yyvars = 1;
			yyclosure_vars(a, c + 0);
		}
		break;
	case 292: /* DECL */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* decls: DECL(decls,decl) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yydecls_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yydecl_NT] + 0;
		yytrace(a, 4, c + 0, p->cost[yydecls_NT]);
		if (c + 0 < p->cost[yydecls_NT]) {
			p->cost[yydecls_NT] = c + 0;
			p->rule.yydecls = 2;
		}
		break;
	case 293: /* NIL */
		/* decls: NIL */
		yytrace(a, 3, 0 + 0, p->cost[yydecls_NT]);
		if (0 + 0 < p->cost[yydecls_NT]) {
			p->cost[yydecls_NT] = 0 + 0;
			p->rule.yydecls = 1;
		}
		/* decl: NIL */
		yytrace(a, 5, 0 + 0, p->cost[yydecl_NT]);
		if (0 + 0 < p->cost[yydecl_NT]) {
			p->cost[yydecl_NT] = 0 + 0;
			p->rule.yydecl = 1;
		}
		/* fargs: NIL */
		yytrace(a, 8, 0 + 0, p->cost[yyfargs_NT]);
		if (0 + 0 < p->cost[yyfargs_NT]) {
			p->cost[yyfargs_NT] = 0 + 0;
			p->rule.yyfargs = 2;
		}
		/* eargs: NIL */
		yytrace(a, 19, 0 + 0, p->cost[yyeargs_NT]);
		if (0 + 0 < p->cost[yyeargs_NT]) {
			p->cost[yyeargs_NT] = 0 + 0;
			p->rule.yyeargs = 2;
		}
		/* vars: NIL */
		yytrace(a, 22, 0 + 0, p->cost[yyvars_NT]);
		if (0 + 0 < p->cost[yyvars_NT]) {
			p->cost[yyvars_NT] = 0 + 0;
			p->rule.yyvars = 2;
			yyclosure_vars(a, 0 + 0);
		}
		/* elifs: NIL */
		yytrace(a, 29, 0 + 0, p->cost[yyelifs_NT]);
		if (0 + 0 < p->cost[yyelifs_NT]) {
			p->cost[yyelifs_NT] = 0 + 0;
			p->rule.yyelifs = 1;
		}
		/* stmt: NIL */
		yytrace(a, 32, 0 + 0, p->cost[yystmt_NT]);
		if (0 + 0 < p->cost[yystmt_NT]) {
			p->cost[yystmt_NT] = 0 + 0;
			p->rule.yystmt = 6;
		}
		/* args: NIL */
		yytrace(a, 75, 1 + 0, p->cost[yyargs_NT]);
		if (1 + 0 < p->cost[yyargs_NT]) {
			p->cost[yyargs_NT] = 1 + 0;
			p->rule.yyargs = 2;
		}
		break;
	case 294: /* EQ */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: EQ(dup,lv) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yydup_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yylv_NT] + 1;
		yytrace(a, 46, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 2;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 295: /* NE */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: NE(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + (isINT(a));
		yytrace(a, 59, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 14;
			yyclosure_expr(a, c + 0);
		}
		/* expr: NE(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + (isSTR(a));
		yytrace(a, 60, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 15;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 296: /* GE */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: GE(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 63, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 18;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 297: /* LE */
		yylabel(LEFT_CHILD(a),a);
		yylabel(RIGHT_CHILD(a),a);
		/* expr: LE(expr,expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + ((struct yystate *)STATE_LABEL(RIGHT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 64, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 19;
			yyclosure_expr(a, c + 0);
		}
		break;
	case 298: /* uminus */
		yylabel(LEFT_CHILD(a),a);
		/* expr: uminus(expr) */
		c = ((struct yystate *)STATE_LABEL(LEFT_CHILD(a)))->cost[yyexpr_NT] + 1;
		yytrace(a, 70, c + 0, p->cost[yyexpr_NT]);
		if (c + 0 < p->cost[yyexpr_NT]) {
			p->cost[yyexpr_NT] = c + 0;
			p->rule.yyexpr = 23;
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
	case 70: /* expr: uminus(expr) */
	case 69: /* expr: NOT(expr) */
	case 52: /* expr: ADDR(lv) */
	case 37: /* stmt: PRINT(expr) */
	case 36: /* stmt: PRINT(expr) */
	case 34: /* stmt: RETURN(expr) */
	case 14: /* decl: NUMBER(id,INT) */
	case 13: /* decl: NUMBER(id,NIL) */
	case 12: /* decl: VAR(decl) */
	case 1: /* file: MODULE(decls) */
		kids[0] = LEFT_CHILD(p);
		break;
	case 74: /* args: ARG(expr,args) */
	case 72: /* expr: LT(expr,expr) */
	case 71: /* expr: GT(expr,expr) */
	case 67: /* expr: OR(or,expr) */
	case 65: /* expr: AND(and,expr) */
	case 64: /* expr: LE(expr,expr) */
	case 63: /* expr: GE(expr,expr) */
	case 62: /* expr: EQUAL(expr,expr) */
	case 61: /* expr: EQUAL(expr,expr) */
	case 60: /* expr: NE(expr,expr) */
	case 59: /* expr: NE(expr,expr) */
	case 58: /* expr: POW(expr,expr) */
	case 57: /* expr: MOD(expr,expr) */
	case 56: /* expr: DIV(expr,expr) */
	case 55: /* expr: MUL(expr,expr) */
	case 54: /* expr: SUB(expr,expr) */
	case 53: /* expr: ADD(expr,expr) */
	case 46: /* expr: EQ(dup,lv) */
	case 44: /* step: STEP(stmt,expr) */
	case 42: /* until: UNTIL(begin,expr) */
	case 41: /* stmt: FOR(until,step) */
	case 31: /* stmt: STMT(stmt,stmt) */
	case 30: /* elifs: ELIF(elifs,if) */
	case 26: /* if: IF(cond,stmt) */
	case 21: /* vars: ARGS(vars,farg) */
	case 18: /* eargs: ARGS(eargs,farg) */
	case 7: /* fargs: ARGS(fargs,farg) */
	case 4: /* decls: DECL(decls,decl) */
	case 2: /* file: PROGRAM(decls,func) */
		kids[0] = LEFT_CHILD(p);
		kids[1] = RIGHT_CHILD(p);
		break;
	case 75: /* args: NIL */
	case 51: /* expr: INPUT */
	case 50: /* expr: ID */
	case 49: /* expr: CHARS(NIL,INT) */
	case 45: /* lv: ID */
	case 39: /* str: CHARS(NIL,STR) */
	case 35: /* stmt: STOP */
	case 33: /* stmt: RETURN(NIL) */
	case 32: /* stmt: NIL */
	case 29: /* elifs: NIL */
	case 22: /* vars: NIL */
	case 19: /* eargs: NIL */
	case 17: /* end: END */
	case 15: /* id: ID */
	case 10: /* farg: STRING(ID,NIL) */
	case 9: /* farg: NUMBER(ID,NIL) */
	case 8: /* fargs: NIL */
	case 5: /* decl: NIL */
	case 3: /* decls: NIL */
		break;
	case 6: /* decl: FUNCTION(END,FARGS(fargs,NIL)) */
		kids[0] = LEFT_CHILD(RIGHT_CHILD(p));
		break;
	case 68: /* or: expr */
	case 66: /* and: expr */
	case 48: /* expr: lv */
	case 47: /* dup: expr */
	case 43: /* begin: expr */
	case 40: /* stmt: expr */
	case 38: /* expr: str */
	case 24: /* cond: expr */
	case 20: /* enter: vars */
	case 11: /* decl: func */
		kids[0] = p;
		break;
	case 16: /* func: FUNCTION(end,FARGS(eargs,START(enter,stmt))) */
		kids[0] = LEFT_CHILD(p);
		kids[1] = LEFT_CHILD(RIGHT_CHILD(p));
		kids[2] = LEFT_CHILD(RIGHT_CHILD(RIGHT_CHILD(p)));
		kids[3] = RIGHT_CHILD(RIGHT_CHILD(RIGHT_CHILD(p)));
		break;
	case 23: /* stmt: FI(THEN(IF(cond,stmt),NIL),NIL) */
		kids[0] = LEFT_CHILD(LEFT_CHILD(LEFT_CHILD(p)));
		kids[1] = RIGHT_CHILD(LEFT_CHILD(LEFT_CHILD(p)));
		break;
	case 25: /* stmt: FI(THEN(if,NIL),stmt) */
		kids[0] = LEFT_CHILD(LEFT_CHILD(p));
		kids[1] = RIGHT_CHILD(p);
		break;
	case 27: /* stmt: FI(THEN(if,elifs),NIL) */
		kids[0] = LEFT_CHILD(LEFT_CHILD(p));
		kids[1] = RIGHT_CHILD(LEFT_CHILD(p));
		break;
	case 28: /* stmt: FI(THEN(if,elifs),stmt) */
		kids[0] = LEFT_CHILD(LEFT_CHILD(p));
		kids[1] = RIGHT_CHILD(LEFT_CHILD(p));
		kids[2] = RIGHT_CHILD(p);
		break;
	case 73: /* expr: CALL(ID,args) */
		kids[0] = RIGHT_CHILD(p);
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
	case 1: /* file: MODULE(decls) */
		fprintf(stderr, "0x%p: line 67: file: MODULE(decls)\n",(void*)p);
#line 67 "minor.brg"

		break;
	case 2: /* file: PROGRAM(decls,func) */
		fprintf(stderr, "0x%p: line 68: file: PROGRAM(decls,func)\n",(void*)p);
#line 68 "minor.brg"

		break;
	case 3: /* decls: NIL */
		fprintf(stderr, "0x%p: line 69: decls: NIL\n",(void*)p);
#line 69 "minor.brg"

		break;
	case 4: /* decls: DECL(decls,decl) */
		fprintf(stderr, "0x%p: line 70: decls: DECL(decls,decl)\n",(void*)p);
#line 70 "minor.brg"

		break;
	case 5: /* decl: NIL */
		fprintf(stderr, "0x%p: line 71: decl: NIL\n",(void*)p);
#line 71 "minor.brg"

		break;
	case 6: /* decl: FUNCTION(END,FARGS(fargs,NIL)) */
		fprintf(stderr, "0x%p: line 72: decl: FUNCTION(END,FARGS(fargs,NIL))\n",(void*)p);
#line 72 "minor.brg"
{ fprintf(yyout, pfEXTRN, mkfunc(LEFT_CHILD(LEFT_CHILD(p))->value.s)); }
		break;
	case 7: /* fargs: ARGS(fargs,farg) */
		fprintf(stderr, "0x%p: line 73: fargs: ARGS(fargs,farg)\n",(void*)p);
#line 73 "minor.brg"

		break;
	case 8: /* fargs: NIL */
		fprintf(stderr, "0x%p: line 74: fargs: NIL\n",(void*)p);
#line 74 "minor.brg"

		break;
	case 9: /* farg: NUMBER(ID,NIL) */
		fprintf(stderr, "0x%p: line 75: farg: NUMBER(ID,NIL)\n",(void*)p);
#line 75 "minor.brg"

		break;
	case 10: /* farg: STRING(ID,NIL) */
		fprintf(stderr, "0x%p: line 76: farg: STRING(ID,NIL)\n",(void*)p);
#line 76 "minor.brg"

		break;
	case 11: /* decl: func */
		fprintf(stderr, "0x%p: line 77: decl: func\n",(void*)p);
#line 77 "minor.brg"

		break;
	case 12: /* decl: VAR(decl) */
		fprintf(stderr, "0x%p: line 78: decl: VAR(decl)\n",(void*)p);
#line 78 "minor.brg"

		break;
	case 13: /* decl: NUMBER(id,NIL) */
		fprintf(stderr, "0x%p: line 79: decl: NUMBER(id,NIL)\n",(void*)p);
#line 79 "minor.brg"
{ fprintf(yyout, pfINTEGER, 0); }
		break;
	case 14: /* decl: NUMBER(id,INT) */
		fprintf(stderr, "0x%p: line 80: decl: NUMBER(id,INT)\n",(void*)p);
#line 80 "minor.brg"
{ fprintf(yyout, pfINTEGER, RIGHT_CHILD(p)->value.i); }
		break;
	case 15: /* id: ID */
		fprintf(stderr, "0x%p: line 81: id: ID\n",(void*)p);
#line 81 "minor.brg"
{ fprintf(yyout, pfDATA pfALIGN pfLABEL, p->value.s); }
		break;
	case 16: /* func: FUNCTION(end,FARGS(eargs,START(enter,stmt))) */
		fprintf(stderr, "0x%p: line 83: func: FUNCTION(end,FARGS(eargs,START(enter,stmt)))\n",(void*)p);
#line 83 "minor.brg"
{ fprintf(yyout, pfIMM pfPOP pfLEAVE pfRET, 0); IDpop(); }
		break;
	case 17: /* end: END */
		fprintf(stderr, "0x%p: line 84: end: END\n",(void*)p);
#line 84 "minor.brg"
{ if (RIGHT_CHILD(p)->value.i & tPUB) fprintf(yyout, pfGLOBL, mkfunc(LEFT_CHILD(p)->value.s), pfFUNC); fprintf(yyout, pfTEXT pfALIGN pfLABEL, mkfunc(LEFT_CHILD(p)->value.s)); IDpush(); }
		break;
	case 18: /* eargs: ARGS(eargs,farg) */
		fprintf(stderr, "0x%p: line 85: eargs: ARGS(eargs,farg)\n",(void*)p);
#line 85 "minor.brg"
{ Node *n = nilNode(VOID); n->place = ++cnt; IDnew(RIGHT_CHILD(p)->info, LEFT_CHILD(RIGHT_CHILD(p))->value.s, n); }
		break;
	case 19: /* eargs: NIL */
		fprintf(stderr, "0x%p: line 86: eargs: NIL\n",(void*)p);
#line 86 "minor.brg"
{ cnt = 1; }
		break;
	case 20: /* enter: vars */
		fprintf(stderr, "0x%p: line 87: enter: vars\n",(void*)p);
#line 87 "minor.brg"
{ fprintf(yyout, pfENTER, -cnt * pfWORD); }
		break;
	case 21: /* vars: ARGS(vars,farg) */
		fprintf(stderr, "0x%p: line 88: vars: ARGS(vars,farg)\n",(void*)p);
#line 88 "minor.brg"
{ Node *n = nilNode(VOID); n->place = --cnt; IDnew(RIGHT_CHILD(p)->info, LEFT_CHILD(RIGHT_CHILD(p))->value.s, n); }
		break;
	case 22: /* vars: NIL */
		fprintf(stderr, "0x%p: line 89: vars: NIL\n",(void*)p);
#line 89 "minor.brg"
{ cnt = 0; }
		break;
	case 23: /* stmt: FI(THEN(IF(cond,stmt),NIL),NIL) */
		fprintf(stderr, "0x%p: line 93: stmt: FI(THEN(IF(cond,stmt),NIL),NIL)\n",(void*)p);
#line 93 "minor.brg"
{ fprintf(yyout, pfLABEL, mklbl(LEFT_CHILD(LEFT_CHILD(LEFT_CHILD(p)))->place)); }
		break;
	case 24: /* cond: expr */
		fprintf(stderr, "0x%p: line 94: cond: expr\n",(void*)p);
#line 94 "minor.brg"
{ p->place = ++lbl; fprintf(yyout, pfJZ, mklbl(p->place)); }
		break;
	case 25: /* stmt: FI(THEN(if,NIL),stmt) */
		fprintf(stderr, "0x%p: line 96: stmt: FI(THEN(if,NIL),stmt)\n",(void*)p);
#line 96 "minor.brg"
{fprintf(yyout, pfLABEL, mklbl(LEFT_CHILD(LEFT_CHILD(p))->place));}
		break;
	case 26: /* if: IF(cond,stmt) */
		fprintf(stderr, "0x%p: line 97: if: IF(cond,stmt)\n",(void*)p);
#line 97 "minor.brg"
{ p->place = ++lbl; fprintf(yyout, pfJMP pfLABEL, mklbl(p->place), mklbl(LEFT_CHILD(p)->place));}
		break;
	case 27: /* stmt: FI(THEN(if,elifs),NIL) */
		fprintf(stderr, "0x%p: line 99: stmt: FI(THEN(if,elifs),NIL)\n",(void*)p);
#line 99 "minor.brg"
{ fprintf(yyout, pfLABEL, mklbl(LEFT_CHILD(LEFT_CHILD(p))->place)); }
		break;
	case 28: /* stmt: FI(THEN(if,elifs),stmt) */
		fprintf(stderr, "0x%p: line 100: stmt: FI(THEN(if,elifs),stmt)\n",(void*)p);
#line 100 "minor.brg"
{ fprintf(yyout, pfLABEL, mklbl(LEFT_CHILD(LEFT_CHILD(p))->place)); }
		break;
	case 29: /* elifs: NIL */
		fprintf(stderr, "0x%p: line 102: elifs: NIL\n",(void*)p);
#line 102 "minor.brg"

		break;
	case 30: /* elifs: ELIF(elifs,if) */
		fprintf(stderr, "0x%p: line 103: elifs: ELIF(elifs,if)\n",(void*)p);
#line 103 "minor.brg"
{ fprintf(yyout, pfLABEL, mklbl(RIGHT_CHILD(p)->place)); }
		break;
	case 31: /* stmt: STMT(stmt,stmt) */
		fprintf(stderr, "0x%p: line 110: stmt: STMT(stmt,stmt)\n",(void*)p);
#line 110 "minor.brg"
{ char s[20]; sprintf(s, "line %d", p->line); fprintf(yyout, pfCOMM, s); }
		break;
	case 32: /* stmt: NIL */
		fprintf(stderr, "0x%p: line 111: stmt: NIL\n",(void*)p);
#line 111 "minor.brg"

		break;
	case 33: /* stmt: RETURN(NIL) */
		fprintf(stderr, "0x%p: line 112: stmt: RETURN(NIL)\n",(void*)p);
#line 112 "minor.brg"
{ fprintf(yyout, pfLEAVE pfRET); }
		break;
	case 34: /* stmt: RETURN(expr) */
		fprintf(stderr, "0x%p: line 113: stmt: RETURN(expr)\n",(void*)p);
#line 113 "minor.brg"
{ fprintf(yyout, pfPOP pfLEAVE pfRET); }
		break;
	case 35: /* stmt: STOP */
		fprintf(stderr, "0x%p: line 114: stmt: STOP\n",(void*)p);
#line 114 "minor.brg"
{ fprintf(yyout, pfJMP, mklbl(stp[stpn-1])); }
		break;
	case 36: /* stmt: PRINT(expr) */
		fprintf(stderr, "0x%p: line 117: stmt: PRINT(expr)\n",(void*)p);
#line 117 "minor.brg"
{ fprintf(yyout, pfEXTRN pfCALL pfTRASH, "_printi", "_printi", 4);}
		break;
	case 37: /* stmt: PRINT(expr) */
		fprintf(stderr, "0x%p: line 118: stmt: PRINT(expr)\n",(void*)p);
#line 118 "minor.brg"
{ fprintf(yyout, pfEXTRN pfCALL pfTRASH, "_prints", "_prints", 4);}
		break;
	case 38: /* expr: str */
		fprintf(stderr, "0x%p: line 126: expr: str\n",(void*)p);
#line 126 "minor.brg"

		break;
	case 39: /* str: CHARS(NIL,STR) */
		fprintf(stderr, "0x%p: line 127: str: CHARS(NIL,STR)\n",(void*)p);
#line 127 "minor.brg"
{ mkstr(RIGHT_CHILD(p)->value.s); }
		break;
	case 40: /* stmt: expr */
		fprintf(stderr, "0x%p: line 128: stmt: expr\n",(void*)p);
#line 128 "minor.brg"
{ fprintf(yyout, pfTRASH, pfWORD); }
		break;
	case 41: /* stmt: FOR(until,step) */
		fprintf(stderr, "0x%p: line 135: stmt: FOR(until,step)\n",(void*)p);
#line 135 "minor.brg"
{ fprintf(yyout, pfTRASH pfJMP pfLABEL, pfWORD, mklbl(LEFT_CHILD(LEFT_CHILD(p))->place), mklbl(LEFT_CHILD(p)->place)); stpn--; }
		break;
	case 42: /* until: UNTIL(begin,expr) */
		fprintf(stderr, "0x%p: line 136: until: UNTIL(begin,expr)\n",(void*)p);
#line 136 "minor.brg"
{ stp[stpn++] = p->place = ++lbl; fprintf(yyout, pfJNZ, mklbl(lbl)); }
		break;
	case 43: /* begin: expr */
		fprintf(stderr, "0x%p: line 137: begin: expr\n",(void*)p);
#line 137 "minor.brg"
{ p->place = ++lbl; fprintf(yyout, pfTRASH pfLABEL, pfWORD, mklbl(lbl)); }
		break;
	case 44: /* step: STEP(stmt,expr) */
		fprintf(stderr, "0x%p: line 138: step: STEP(stmt,expr)\n",(void*)p);
#line 138 "minor.brg"
{/* fprintf(yyout, pfTRASH, pfWORD);*/ }
		break;
	case 45: /* lv: ID */
		fprintf(stderr, "0x%p: line 140: lv: ID\n",(void*)p);
#line 140 "minor.brg"
{ mkid(p); }
		break;
	case 46: /* expr: EQ(dup,lv) */
		fprintf(stderr, "0x%p: line 141: expr: EQ(dup,lv)\n",(void*)p);
#line 141 "minor.brg"
{ fprintf(yyout, pfSTORE); }
		break;
	case 47: /* dup: expr */
		fprintf(stderr, "0x%p: line 142: dup: expr\n",(void*)p);
#line 142 "minor.brg"
{ fprintf(yyout, pfDUP); }
		break;
	case 48: /* expr: lv */
		fprintf(stderr, "0x%p: line 143: expr: lv\n",(void*)p);
#line 143 "minor.brg"
{ fprintf(yyout, pfLOAD); }
		break;
	case 49: /* expr: CHARS(NIL,INT) */
		fprintf(stderr, "0x%p: line 146: expr: CHARS(NIL,INT)\n",(void*)p);
#line 146 "minor.brg"
{ fprintf(yyout, pfIMM, RIGHT_CHILD(p)->value.i); }
		break;
	case 50: /* expr: ID */
		fprintf(stderr, "0x%p: line 147: expr: ID\n",(void*)p);
#line 147 "minor.brg"
{ fprintf(yyout, pfCALL pfPUSH, mkfunc(p->value.s)); }
		break;
	case 51: /* expr: INPUT */
		fprintf(stderr, "0x%p: line 148: expr: INPUT\n",(void*)p);
#line 148 "minor.brg"
{ fprintf(yyout, pfEXTRN pfCALL pfPUSH, U_"readi", U_"readi"); }
		break;
	case 52: /* expr: ADDR(lv) */
		fprintf(stderr, "0x%p: line 149: expr: ADDR(lv)\n",(void*)p);
#line 149 "minor.brg"

		break;
	case 53: /* expr: ADD(expr,expr) */
		fprintf(stderr, "0x%p: line 150: expr: ADD(expr,expr)\n",(void*)p);
#line 150 "minor.brg"
{ fprintf(yyout, pfADD); }
		break;
	case 54: /* expr: SUB(expr,expr) */
		fprintf(stderr, "0x%p: line 151: expr: SUB(expr,expr)\n",(void*)p);
#line 151 "minor.brg"
{ fprintf(yyout, pfSUB); }
		break;
	case 55: /* expr: MUL(expr,expr) */
		fprintf(stderr, "0x%p: line 153: expr: MUL(expr,expr)\n",(void*)p);
#line 153 "minor.brg"
{ fprintf(yyout, pfMUL); }
		break;
	case 56: /* expr: DIV(expr,expr) */
		fprintf(stderr, "0x%p: line 154: expr: DIV(expr,expr)\n",(void*)p);
#line 154 "minor.brg"
{ fprintf(yyout, pfDIV); }
		break;
	case 57: /* expr: MOD(expr,expr) */
		fprintf(stderr, "0x%p: line 155: expr: MOD(expr,expr)\n",(void*)p);
#line 155 "minor.brg"
{ fprintf(yyout, pfMOD); }
		break;
	case 58: /* expr: POW(expr,expr) */
		fprintf(stderr, "0x%p: line 156: expr: POW(expr,expr)\n",(void*)p);
#line 156 "minor.brg"
{ fprintf(yyout, pfEXTRN pfCALL pfTRASH pfPUSH, "_pow", "_pow", 4);}
		break;
	case 59: /* expr: NE(expr,expr) */
		fprintf(stderr, "0x%p: line 158: expr: NE(expr,expr)\n",(void*)p);
#line 158 "minor.brg"
{ fprintf(yyout, pfNE); }
		break;
	case 60: /* expr: NE(expr,expr) */
		fprintf(stderr, "0x%p: line 159: expr: NE(expr,expr)\n",(void*)p);
#line 159 "minor.brg"
{ fprintf(yyout, pfEXTRN pfCALL pfTRASH pfPUSH, "_strncmp", "_strncmp", 4);}
		break;
	case 61: /* expr: EQUAL(expr,expr) */
		fprintf(stderr, "0x%p: line 161: expr: EQUAL(expr,expr)\n",(void*)p);
#line 161 "minor.brg"
{ fprintf(yyout, pfEQ); }
		break;
	case 62: /* expr: EQUAL(expr,expr) */
		fprintf(stderr, "0x%p: line 162: expr: EQUAL(expr,expr)\n",(void*)p);
#line 162 "minor.brg"
{ fprintf(yyout, pfEXTRN pfCALL pfTRASH pfPUSH, "_strcmp", "_strcmp", 4);}
		break;
	case 63: /* expr: GE(expr,expr) */
		fprintf(stderr, "0x%p: line 165: expr: GE(expr,expr)\n",(void*)p);
#line 165 "minor.brg"
{ fprintf(yyout, pfGE); }
		break;
	case 64: /* expr: LE(expr,expr) */
		fprintf(stderr, "0x%p: line 166: expr: LE(expr,expr)\n",(void*)p);
#line 166 "minor.brg"
{ fprintf(yyout, pfLE); }
		break;
	case 65: /* expr: AND(and,expr) */
		fprintf(stderr, "0x%p: line 167: expr: AND(and,expr)\n",(void*)p);
#line 167 "minor.brg"
{ fprintf(yyout, pfLABEL, mklbl(LEFT_CHILD(p)->place)); }
		break;
	case 66: /* and: expr */
		fprintf(stderr, "0x%p: line 168: and: expr\n",(void*)p);
#line 168 "minor.brg"
{ p->place = ++lbl; fprintf(yyout, pfDUP pfJZ pfTRASH, mklbl(p->place), 4); }
		break;
	case 67: /* expr: OR(or,expr) */
		fprintf(stderr, "0x%p: line 169: expr: OR(or,expr)\n",(void*)p);
#line 169 "minor.brg"
{ fprintf(yyout, pfLABEL, mklbl(LEFT_CHILD(p)->place)); }
		break;
	case 68: /* or: expr */
		fprintf(stderr, "0x%p: line 170: or: expr\n",(void*)p);
#line 170 "minor.brg"
{ p->place = ++lbl; fprintf(yyout, pfDUP pfJNZ pfTRASH, mklbl(p->place), 4); }
		break;
	case 69: /* expr: NOT(expr) */
		fprintf(stderr, "0x%p: line 171: expr: NOT(expr)\n",(void*)p);
#line 171 "minor.brg"
{ fprintf(yyout, pfIMM pfEQ, 0); }
		break;
	case 70: /* expr: uminus(expr) */
		fprintf(stderr, "0x%p: line 172: expr: uminus(expr)\n",(void*)p);
#line 172 "minor.brg"
{ fprintf(yyout, pfNEG); }
		break;
	case 71: /* expr: GT(expr,expr) */
		fprintf(stderr, "0x%p: line 175: expr: GT(expr,expr)\n",(void*)p);
#line 175 "minor.brg"
{ fprintf(yyout, pfGT); }
		break;
	case 72: /* expr: LT(expr,expr) */
		fprintf(stderr, "0x%p: line 176: expr: LT(expr,expr)\n",(void*)p);
#line 176 "minor.brg"
{ fprintf(yyout, pfLT); }
		break;
	case 73: /* expr: CALL(ID,args) */
		fprintf(stderr, "0x%p: line 177: expr: CALL(ID,args)\n",(void*)p);
#line 177 "minor.brg"
{ fprintf(yyout, pfCALL pfTRASH pfPUSH, mkfunc(LEFT_CHILD(p)->value.s), trash * pfWORD); }
		break;
	case 74: /* args: ARG(expr,args) */
		fprintf(stderr, "0x%p: line 178: args: ARG(expr,args)\n",(void*)p);
#line 178 "minor.brg"
{ trash += 1; }
		break;
	case 75: /* args: NIL */
		fprintf(stderr, "0x%p: line 179: args: NIL\n",(void*)p);
#line 179 "minor.brg"
{ trash = 0; }
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


#line 180 "minor.brg"

extern char **yynames;
extern int trace, errors, debugNode;
void evaluate(Node *p) {
	if (errors) return;
	if (trace) printNode(p, stdout, yynames);
	if (trace) IDprint(0,0);
	if (!yyselect(p) && trace) fprintf(stderr, "selection successful\n");
}

#ifndef NOTRACE
static void yytrace(NODEPTR_TYPE p, int eruleno, int cost, int bestcost)
{
	int op = OP_LABEL(p);
	YYCONST char *tname = yytermname[op] ? yytermname[op] : "?";
	if (debugNode) fprintf(stderr, "%p:%s matched %s with cost %d vs. %d\n", p, tname, yystring[eruleno], cost, bestcost);
	if (cost >= MAX_COST && bestcost >= MAX_COST) {
		fprintf(stderr, "%p:%s NO MATCH %s with cost %d vs. %d\n", p, tname, yystring[eruleno], cost, bestcost);
		printNode(p, stderr, yynames);
	}
}
#endif
