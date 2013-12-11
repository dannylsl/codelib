"====================================================
" Highlight All Function
" ===================================================
syn match cFunction "\<[a-zA-Z_][a-zA-Z_0-9]*\>[^()]*)("me=e-2
syn match cFunction "\<[a-zA-Z_][a-zA-Z_0-9]*\>\s*("me=e-1
hi cFunction cterm=bold ctermfg=blue
"===================================================
" Highlight All Class Name
" ==================================================
syn match cClassName "\<[a-zA-Z_][a-zA-Z_0-9]*\>*\:"me=e-1
hi cClassName cterm=bold ctermfg=yellow
