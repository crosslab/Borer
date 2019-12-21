#include "stdafx.h"
#include "CommonDef.h"
#include "Borer.h"

#include "MainFrm.h"
#include "VbhExpression.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ExprParser constructor 
template <class PType> ExprParser<PType>::ExprParser() 
{ 
  
  exp_ptr = NULL; 
} 

// Process an assignment. 
template <class PType> void ExprParser<PType>::eval_exp1(PType &result) 
{ 
  int slot; 
  char ttok_type; 
  char temp_tkn[80]; 
  
  if(tok_type==TT_VARIABLE) { 
    // save old token 
    strcpy(temp_tkn, token); 
    ttok_type = tok_type; 
    
    // compute the index of the variable 
    slot = toupper(*token) - 'A'; 
    
    get_tkn(); 
    if(*token != '=') { 
      putback(); // return current token 
      // restore old token - not assignment 
      strcpy(token, temp_tkn); 
      tok_type = ttok_type; 
    } 
    else { 
      get_tkn(); // get next part of exp 
      eval_exp2(result); 
      return; 
    } 
  } 
  
  eval_exp2(result); 
} 

// Add or subtract two terms. 
template <class PType> void ExprParser<PType>::eval_exp2(PType &result) 
{ 
  register char op; 
  PType temp; 
  
  eval_exp3(result); 
  while((op = *token) == '+' || op == '-') { 
    get_tkn(); 
    eval_exp3(temp); 
    switch(op) { 
    case '-': 
      result = result - temp; 
      break; 
    case '+': 
      result = result + temp; 
      break; 
    } 
  } 
} 

// Multiply or divide two factors. 
template <class PType> void ExprParser<PType>::eval_exp3(PType &result) 
{ 
  register char op; 
  PType temp; 
  
  eval_exp4(result); 
  while((op = *token) == '*' || op == '/' || op == '%') { 
    get_tkn(); 
    eval_exp4(temp); 
    switch(op) { 
    case '*': 
      result = result * temp; 
      break; 
    case '/': 
      result = result / temp; 
      break; 
    case '%': 
      result = (int) result % (int) temp; 
      break; 
    } 
  } 
} 

// Process an exponent 
template <class PType> void ExprParser<PType>::eval_exp4(PType &result) 
{ 
  PType temp, ex; 
  register int t; 
  
  eval_exp5(result); 
  if(*token== '^') { 
    get_tkn(); 
    eval_exp4(temp); 
    ex = result; 
    if(temp==0.0) { 
      result = (PType) 1; 
      return; 
    } 
    for(t=(int)temp-1; t>0; --t) result = result * ex; 
  } 
} 

// Evaluate a unary + or -. 
template <class PType> void ExprParser<PType>::eval_exp5(PType &result) 
{ 
  register char  op; 
  
  op = 0; 
  if((tok_type == TT_DELIMITER) && *token=='+' || *token == '-') { 
    op = *token; 
    get_tkn(); 
  } 
  eval_exp6(result); 
  if(op=='-') result = -result; 
} 

// Process a parenthesized expression. 
template <class PType> void ExprParser<PType>::eval_exp6(PType &result) 
{ 
  if((*token == '(')) { 
    get_tkn(); 
    eval_exp2(result); 
    if(*token != ')') 
      serror(1); 
    get_tkn(); 
  } 
  else atom(result); 
} 

// Get the value of a number or a variable. 
template <class PType> void ExprParser<PType>::atom(PType &result) 
{ 
  switch(tok_type) { 
  case TT_VARIABLE: 
    result = lookup_var(token); 
    get_tkn(); 
    return; 
  case TT_NUMBER: 
    result = (PType) atof(token); 
    get_tkn(); 
    return; 
  default: 
    serror(0); 
  } 
} 

// Return a token to the input stream. 
template <class PType> void ExprParser<PType>::putback() 
{ 
  char *t; 
  
  t = token; 
  for(; *t; t++) exp_ptr--; 
} 

// Display a syntax error. 
template <class PType> void ExprParser<PType>::serror(int error) 
{   
  exp_err=true;
} 

// Obtain the next token. 
template <class PType> void ExprParser<PType>::get_tkn() 
{ 
  register char *temp; 
  
  tok_type = 0; 
  temp = token; 
  *temp = '\0'; 
  
  if(!*exp_ptr) return; // at end of expression 
  
  while(isspace(*exp_ptr)) ++exp_ptr; // skip over white space 
  
  if(strchr("+-*/%^=()", *exp_ptr)){ 
    tok_type = TT_DELIMITER; 
    // advance to next char 
    *temp++ = *exp_ptr++; 
  } 
  else if(isalpha(*exp_ptr)) { 
    if(*exp_ptr!='L') {
      exp_err=true;
    }else {
      while(!isdelim(*exp_ptr)) *temp++ = *exp_ptr++; 
      tok_type = TT_VARIABLE; 
    }
  } 
  else if(isdigit(*exp_ptr)) { 
    while(!isdelim(*exp_ptr)) *temp++ = *exp_ptr++; 
    tok_type = TT_NUMBER; 
  } 
  
  *temp = '\0'; 
} 

// Return true if c is a delimiter. 
template <class PType> int ExprParser<PType>::isdelim(char c) 
{ 
  if(strchr(" +-/*%^=()", c) || c==9 || c=='\r' || c==0) 
    return 1; 
  return 0; 
} 

// Return the value of a variable. 
template <class PType> PType ExprParser<PType>::lookup_var(char *fvs) 
{ 
  if((*fvs!='L') || (strlen(fvs)==1)) { 
    serror(1); 
    return (PType) 0; 
  }else {
    return ptr_vars[atoi(fvs+1)]; 
  }
}

// Parser entry point. 
template <class PType> PType ExprParser<PType>::EvalExprs(char *exp,PType *ptrRef) 
{ 
  PType result; 
  
  exp_err  =false;
  exp_ptr  =exp; 
  ptr_vars =ptrRef;
  
  get_tkn(); 
  if(!*token) { 
    serror(2); // no expression present 
    return (PType) 0; 
  } 
  eval_exp1(result); 
  if(*token) serror(0); // last token must be null 
  return result; 
} 

double DblParser(CString &strExp,double *lpRef)
{
  ExprParser<double> oPsr;
  double dbRet=oPsr.EvalExprs(strExp.GetBuffer(strExp.GetLength()),lpRef);
  strExp.ReleaseBuffer();
  return dbRet;
}
