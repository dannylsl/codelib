" local syntax file - set colors on a per-machine basis:
" vim: tw=0 ts=4 sw=4
" Vim color file
" Maintainer:	Ron Aaron <ron@ronware.org>
" Last Change:	2003 May 02

set background=dark
hi clear
if exists("syntax_on")
	syntax reset
endif
let g:colors_name = "dannyOathy"
hi Normal		cterm=bold		ctermfg=Green	guifg=Green			guibg=black
hi Comment		term=bold		cterm=bold			ctermfg=Red	guifg=Red
"//  /*
hi Constant		term=underline	ctermfg=white		guifg=white
" \"\" \'\'
hi Special		term=bold		ctermfg=DarkMagenta	guifg=DarkMagenta
hi Identifier	term=underline	cterm=bold			ctermfg=Yellow guifg=Yellow
"var 
hi Statement	term=bold		ctermfg=Yellow		gui=bold	guifg=Yellow
"return
hi PreProc		term=underline	ctermfg=LightBlue	guifg=LightBlue
hi Type			term=underline	ctermfg=Red	guifg=#60ff60 gui=bold
"Number()  Array()
hi Function		term=bold		ctermfg=Blue		guifg=Blue
"function {}
hi Repeat		term=underline	ctermfg=Cyan		guifg=Cyan
" for  if-esle
hi Operator		ctermfg=Red		guifg=Red   
"new
hi Ignore		ctermfg=black	guifg=black
hi Error		term=reverse	ctermbg=Red		ctermfg=White guibg=Red	guifg=Red
hi Number		ctermfg=Magenta	guifg=Magenta
hi Boolean		cterm=bold		ctermfg=Red		ctermfg=Red
"true fasle
hi Todo			term=standout	ctermbg=Yellow	ctermfg=Black guifg=Yellow	guibg=Yellow


" Common groups that link to default highlighting.
" You can specify other highlighting easily.
hi link String			Constant
hi link Character		Constant
"hi link Number			Constant
"hi link Boolean			Constant
hi link Float			Number
hi link Conditional		Repeat
hi link Label			Statement
hi link Keyword			Statement
hi link Exception		Statement
hi link Include			PreProc
hi link Define			PreProc
hi link Macro			PreProc
hi link PreCondit		PreProc
hi link StorageClass	Type
hi link Structure		Type
hi link Typedef			Type
hi link Tag				Special
hi link SpecialChar		Special
hi link Delimiter		Special
hi link SpecialComment	Special
hi link Debug			Special
