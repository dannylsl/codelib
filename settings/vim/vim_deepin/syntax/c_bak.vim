"====================================================
" Highlight All Function
" ===================================================
syn match cFunction "\<[a-zA-Z_][a-zA-Z_0-9]*\>[^()]*)("me=e-2
syn match cFunction "\<[a-zA-Z_][a-zA-Z_0-9]*\>\s*("me=e-1
hi cFunction cterm=bold ctermfg=yellow
"===================================================
" Highlight All Class Name
" ==================================================
syn match cClassName "\<[a-zA-Z_][a-zA-Z_0-9]*\>*\:"me=e-1
hi cClassName cterm=bold ctermfg=yellow
"====================================================
" Highlight All Math Operator
" ===================================================
" c math operators
syn match cMathOperator display "[-+\*\%=]"
" c opinter operators
syn match cPointerOperator display "->\|\.\|\:\:"
" c logical operators - boolean results
syn match cLogicalOperator display "[!<>]=\="
syn match cLogicalOperator display "=="
" c bit operators
syn match cBinaryOperator display "\(&\||\|\^\|<<\|>>\)=\="
syn match cBinaryOperator display "\~"
syn match cBinaryOperatorError display "\~="
" More c logical operators - highlight in preference to binary
syn match cLogicalOperator display "&&\|||"
syn match cLogicalOperatorError display "\(&&\|||\)="
" more c priority operators -highlight in preference to binary
syn match cPriorityOpreator display "(\|)\|\[\|\]\|{\|}"
" match operator
hi cMathOperator ctermfg=blue
hi cPointerOperator ctermfg=red
hi cLogicalOperator ctermfg=yellow
hi cBinaryOperator ctermfg=5
hi cBinaryOperatorError ctermfg=red
hi cLogicalOperator ctermfg=yellow
hi cLogicalOperatorError ctermfg=yellow
hi cPriorityOpreator ctermfg=green
