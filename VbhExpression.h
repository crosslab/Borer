#if !defined(_VBH_INC_)
#define _VBH_INC_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VbhExpression.h : header file

enum tt_types { TT_DELIMITER = 1, TT_VARIABLE, TT_NUMBER}; 

const int NUMVARS = 256; 

template <class PType> class ExprParser { 
  char *exp_ptr;  // points to the expression 
  char token[80]; // holds current token 
  char tok_type;  // holds token's type 
  
  void eval_exp1(PType &result); 
  void eval_exp2(PType &result); 
  void eval_exp3(PType &result); 
  void eval_exp4(PType &result); 
  void eval_exp5(PType &result); 
  void eval_exp6(PType &result); 
  void atom(PType &result); 
  void get_tkn(), putback(); 
  void serror(int error); 
  PType lookup_var(char *fvs); 
  int isdelim(char c); 
  
public: 
  ExprParser(); 
  PType EvalExprs(char *exp,PType *ptrRef); 
  
  PType *ptr_vars;
  bool   exp_err;  // points to the expression 
}; 

double DblParser(CString &strExp,double *lpRef);

#endif // !defined(_VBH_INC_)
