set nu
syntax on
set shiftwidth=4
set cin
set mouse=a
set tabstop=4
set ruler
set cursorline
set cursorcolumn
set cindent
set autoindent
inoremap { {}<LEFT>
inoremap ( ()<LEFT>
inoremap [ []<LEFT>
inoremap " ""<ESC>i
inoremap ' ''<ESC>i
set background=dark
autocmd BufNewFile *.[ch],*.hpp,*.cpp,Makefile,*.mk,*.sh exec ":call SetTitle()"
func SetTitle()
	if &filetype == 'make'
		call setline(1,"")
		call setline(2,"")
		call SetComment_sh()

	elseif &filetype == 'sh'
		call setline(1,"#!/system/bin/sh")
		call setline(2,"")
"		call SetComment_sh()

	else
	     call SetComment()
	     if expand("%:e") == 'hpp'
		  call append(line(".")+10, "#ifndef _".toupper(expand("%:t:r"))."_H")
		  call append(line(".")+11, "#define _".toupper(expand("%:t:r"))."_H")
		  call append(line(".")+12, "#ifdef __cplusplus")
		  call append(line(".")+13, "extern \"C\"")
		  call append(line(".")+14, "{")
		  call append(line(".")+15, "#endif")
		  call append(line(".")+16, "")
		  call append(line(".")+17, "#ifdef __cplusplus")
		  call append(line(".")+18, "}")
		  call append(line(".")+19, "#endif")
		  call append(line(".")+20, "#endif //".toupper(expand("%:t:r"))."_H")

	     elseif expand("%:e") == 'h'
	  	  call append(line(".")+10, "#pragma once")
	     endif
	endif
endfunc

func SetComment()
	call setline(1,"#include<bits/stdc++.h>")
	call append(line("."),  "using namespace std;") 
	call append(line(".") + 1, "typedef long long ll;")
	call append(line(".")+2, "#ifndef ONLINE_JUDGE")
	call append(line(".")+3, '#define dbg(x...) do{cout << "\033[33;1m" << #x << "->" ; err(x);} while (0)')
	call append(line(".")+4, 'void err(){cout << "\033[39;0m" << endl;}')
	call append(line(".")+5, "template<template<typename...> class T, typename t, typename... A>")
	call append(line(".")+6, "void err(T<t> a, A... x){for (auto v: a) cout << v << ' '; err(x...);}")
	call append(line(".")+7, "template<typename T, typename... A>")
	call append(line(".")+8, "void err(T a, A... x){cout << a << ' '; err(x...);}")
	call append(line(".")+9, "#else")
	call append(line(".")+10, "#define dbg(...)")
	call append(line(".") + 11, "#endif")
	call append(line(".") + 12, "#define inf 1ll << 50")
endfunc
