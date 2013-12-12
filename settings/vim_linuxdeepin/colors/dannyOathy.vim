" local syntax file - set colors on a per-machine basis:
" vim: tw=0 ts=4 sw=4
" Vim color file
" Maintainer:   Ron Aaron <ron@ronware.org>
" Modified by danny Lee
" Last Change:  2003 May 02

set background=dark
hi clear
if exists("syntax_on")
  syntax reset
endif
let g:colors_name = "dannyOathy"
hi Normal       cterm=bold      ctermfg=Green   guifg=cyan          guibg=black
hi Comment      term=bold       cterm=bold          ctermfg=DarkGray    guifg=#80a0ff
"//  /*
hi Constant     term=underline  ctermfg=white       guifg=Magenta
" \"\" \'\'
hi Special      term=bold       ctermfg=DarkMagenta guifg=Red
hi Identifier   term=underline  cterm=bold          ctermfg=Yellow guifg=#40ffff
"var
hi Statement    term=bold       ctermfg=Yellow      gui=bold    guifg=#aa4444
"return
hi PreProc      term=underline  ctermfg=LightBlue   guifg=#ff80ff
hi Type         term=underline  ctermfg=Red guifg=#60ff60 gui=bold
"Number()  Array()
hi Function     term=bold       ctermfg=Blue        guifg=White
"function {}
hi Repeat       term=underline  ctermfg=Cyan        guifg=white
" for  if-esle
hi Operator     ctermfg=Red     guifg=Red
"new
hi Ignore       ctermfg=black   guifg=bg
hi Error        term=reverse    ctermbg=Red     ctermfg=White guibg=Red     guifg=White
hi Number       ctermfg=Magenta
hi Boolean      cterm=bold      ctermfg=Red
"true fasle
hi Todo         term=standout   ctermbg=Yellow  ctermfg=Black guifg=Blue    guibg=Yellow

hi CursorColumn term=reverse ctermbg=Black guibg=grey40
hi CursorLine term=underline cterm=underline guibg=grey40
hi SpecialKey term=bold ctermfg=Red ctermbg=white guifg=Cyan

" Common groups that link to default highlighting.
" You can specify other highlighting easily.
hi link String          Constant
hi link Character       Constant
"hi link Number         Constant
"hi link Boolean            Constant
hi link Float           Number
hi link Conditional     Repeat
hi link Label           Statement
hi link Keyword         Statement
hi link Exception       Statement
hi link Include         PreProc
hi link Define          PreProc
hi link Macro           PreProc
hi link PreCondit       PreProc
hi link StorageClass    Type
hi link Structure       Type
hi link Typedef         Type
hi link Tag             Special
hi link SpecialChar     Special
hi link Delimiter       Special
hi link SpecialComment  Special
hi link Debug           Special
