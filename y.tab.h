#define INT 257
#define ID 258
#define STRING 259
#define CHR 260
#define PROGRAM 261
#define MODULE 262
#define START 263
#define END 264
#define VOID 265
#define CONST 266
#define NUMBER 267
#define ARRAY 268
#define FUNCTION 269
#define PUBLIC 270
#define FOWARD 271
#define IF 272
#define THEN 273
#define ELSE 274
#define ELIF 275
#define FI 276
#define FOR 277
#define UNTIL 278
#define STEP 279
#define DO 280
#define DONE 281
#define REPEAT 282
#define STOP 283
#define RETURN 284
#define IFX 285
#define ATR 286
#define NE 287
#define GE 288
#define LE 289
#define UMINUS 290
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
	int i;			/* integer value                 */
	char *s;		/* symbol name or string literal */
	/*Node *n;*/
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
