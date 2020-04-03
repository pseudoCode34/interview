" Author: John Williams <johnkt12@gmail.com>
" Modified By: John Willams <johnkt12qz@gmail.com>
"
" Created: Sun 15 Sep 2019 21:02:12 +07
" Last Modified: Thu 02 Apr 2020 22:48:45 +07
"

" Plugin {{{

set nocompatible              " be iMproved, required
filetype off                  " required
" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
" call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'
Plugin 'rstacruz/sparkup', {'rtp' : 'vim/'}
Plugin 'majutsushi/tagbar'
Plugin 'dracula/vim'
Plugin 'tpope/vim-commentary'
Plugin 'tpope/vim-fugitive'
Plugin 'kien/ctrlp.vim'
Plugin 'preservim/nerdtree'
Plugin 'preservim/nerdcommenter'
Plugin 'vim-syntastic/syntastic'
Plugin 'edkolev/tmuxline.vim'
Plugin 'mbbill/undotree'
Plugin 'vim-airline/vim-airline'
Plugin 'vim-airline/vim-airline-themes'
Plugin 'honza/vim-snippets'
Plugin 'SirVer/ultisnips'
Plugin 'Vimjas/vim-python-pep8-indent'
Plugin 'octol/vim-cpp-enhanced-highlight'
Plugin 'ycm-core/YouCompleteMe'
Plugin 'jiangmiao/auto-pairs'
Plugin 'jaxbot/semantic-highlight.vim'

call vundle#end() 	" required
filetype plugin indent on " required
" To ignore plugin indent changes, instead use:
" filetype plugin on
"
" Brief help
" :PluginList       - lists configured plugins
" :PluginInstall    - installs plugins; append `!` to update or just :PluginUpdate
" :PluginSearch foo - searches for foo; append `!` to refresh local cache
" :PluginClean      - confirms removal of unused plugins; append `!` to auto-approve removal
"
" see :h vundle for more details or wiki for FAQ
" Put your non-Plugin stuff after this line

" }}}

" Settings {{{
"let g:rainbow_active = 1 "set to 0 if you want to enable it later via :RainbowToggle
" Switch syntax highlighting on, when the terminal has colors
syntax on

" No backup files
set nobackup

" No write backup
set nowritebackup

"No swap file
set noswapfile

" Command history
set history=100

" Always show cursor
set ruler

" Show incomplete commands
set showcmd

" Incremental searching (search as you type)
set incsearch

" Highlight search matches
set hlsearch

" Ignore case in search
set smartcase

" Make sure any searches /searchPhrase doesn't need the \c escape character
set ignorecase

" A buffer is marked as ‘hidden’ if it has unsaved changes, and it is not currently loaded in a window
" if you try and quit Vim while there are hidden buffers, you will raise an error:
" E162: No write since last change for buffer “a.txt”
set hidden

" Turn word wrap off
set nowrap

" Allow backspace to delete end of line, indent and start of line characters
set backspace=indent,eol,start

" Set tab size in spaces (this is for manual indenting)
set tabstop=4

" The number of spaces inserted for a tab (used for auto indenting)
set shiftwidth=4

" Turn on line numbers
set number

" Highlight tailing whitespace
" See issue: https://github.com/Integralist/ProVim/issues/4
set list listchars=tab:\ \ ,trail:·

" Set the status line to something useful
set statusline=%f\%=L:%l/%L\%c\(%p%%)

" Get rid of the delay when pressing O (for example)
" http://stackoverflow.com/questions/2158516/vim-delay-before-o-opens-a-new-line
set timeout timeoutlen=1000 ttimeoutlen=100

" Always show status bar
set laststatus=2

" Hide the toolbar
set guioptions-=T

" UTF encoding
set encoding=utf-8

" Autoload files that have changed outside of vim
set autoread

" Use system clipboard
" http://stackoverflow.com/questions/8134647/copy-and-paste-in-vim-via-keyboard-between-different-mac-terminals
set clipboard+=unnamed

" Don't show intro
set shortmess+=I

" Better splits (new windows appear below and to the right)
set splitbelow
set splitright

" Highlight the current line
set cursorline

" Ensure Vim doesn't beep at you every time you make a mistype
set visualbell

" Visual autocomplete for command menu (e.g. :e ~/path/to/file)
set wildmenu

" redraw only when we need to (i.e. don't redraw when executing a macro)
set lazyredraw

" highlight a matching [{()}] when cursor is placed on start/end character
set showmatch

" Set built-in file system explorer to use layout similar to the NERDTree plugin
let g:netrw_liststyle=3

" Always highlight column 80 so it's easier to see where
" cutoff appears on longer screens
autocmd BufWinEnter * highlight ColorColumn ctermbg=darkred
set colorcolumn=80

colorscheme dracula

" Trigger configuration. Do not use <tab> if you use https://github.com/Valloric/YouCompleteMe.
let g:UltiSnipsExpandTrigger="<c-a>"
let g:UltiSnipsJumpForwardTrigger="<c-z>"
let g:UltiSnipsJumpBackwardTrigger="<c-b>"

" If you want :UltiSnipsEdit to split your window.
let g:UltiSnipsEditSplit="vertical"

" Vim-airline
let g:airline#extensions#tabline#enabled=1
let g:airline#extensions#tabline#formatter='unique_tail'

" Syntastic
let g:syntastic_check_on_open = 1
let g:syntastic_check_on_wq = 0
let g:syntastic_cpp_compiler_options = ' -std=c++2a'

" YCM
"let g:ycm_global_ycm_extra_conf='~/.vim/bundle/YouCompleteMe/third_party/ycmd/.ycm_extra_conf.py'
let g:ycm_autoclose_preview_window_after_completion = 1
let g:ycm_global_ycm_extra_conf = '~/.ycm_extra_conf.py'

" Nerdtree
" Add spaces after comment delimiters by default
let g:NERDSpaceDelims = 1

" Use compact syntax for prettified multi-line comments
let g:NERDCompactSexyComs = 1

" Align line-wise comment delimiters flush left instead of following code indentation
let g:NERDDefaultAlign = 'left'

" Set a language to use its alternate delimiters by default
let g:NERDAltDelims_java = 1

" Add your own custom formats or override the defaults
let g:NERDCustomDelimiters = {'c' : {'left' : '/**', 'right' : '*/'}}

" Allow commenting and inverting empty lines (useful when commenting a region)
let g:NERDCommentEmptyLines = 1

" Enable trimming of trailing whitespace when uncommenting
let g:NERDTrimTrailingWhitespace = 1

" Enable NERDCommenterToggle to check all selected lines is commented or not
let g:NERDToggleCheckAllLines = 1

" How can I close vim if the only window left open is a NERDTree?
autocmd bufenter * if (winnr("$") == 1 && exists("b:NERDTree") && b:NERDTree.isTabTree()) | q | endifendif

" Close all folds when opening a new buffer
autocmd BufRead * set foldmethod=marker
autocmd BufRead *.cpp,*.c setlocal foldmethod=syntax
autocmd BufRead * normal zM

"If you don't want comments to become a fold use:
let c_no_comment_fold = 1
"#if 0" blocks are also folded, unless:
let c_no_if0_fold = 1

" Use a vertical split Termdebug
let g:termdebug_wide = 80

function C_family_highlighing()
  syn keyword Codetags contained BUG HACK UNDONE
  syn cluster cCommentGroup add=Codetags
  hi def link Codetags Todo

  syn region cppDocTags	 contained start="{@\(code\|link\|linkplain\|inherit[Dd]oc\|doc[rR]oot\|value\)" end="}"
  syn match  cppDocTags	 contained "@\(param\|exception\|throws\|since\)\>"
  syn match  cppDocTags	 contained "\(return\|deprecated\|serial\|serialField\|serialData\)\>"
  syn match  cppDocTags	 contained "URL\|References\|Remark\|Last \(modified\|updated\)\|\(Current\|Last\) maintainer\|\(Space\|Time\) complexity\>"
  syn cluster cCommentGroup add=cppDocTags
  hi def link cppDocTags		Special

  syntax match  Symbols      "[-+*?:.<>&|!%=\[\]]"
  hi link Symbols Operator
endfunction
autocmd FileType c,cpp call C_family_highlighing()

" If buffer modified, update any 'Last modified: ' in the first 20 lines.
" 'Last modified: ' can have up to 10 characters before (they are retained).
" Restores cursor and window position using save_cursor variable.
function! UpdateLastModifiedTime()
  if &modified
    let save_cursor = getpos(".")
   let n = min([20, line("$")])
    keepjumps exe '1,' . n . 's#^\(.\{,10}\(Last\)\? [mM]odified: \).*#\1' .
          \ strftime('%c') . '#e'
    call histdel('search', -1)
    call setpos('.', save_cursor)
  endif
endfun
autocmd BufWritePre * call UpdateLastModifiedTime()

function! WriteFileInformation()
  put ='\" Author: John Williams <johnkt12qz@gmail.com>'
  put ='\" Created: ' . strftime('%c')
  put ='\" Last change: ' . strftime('%c')
  "
  "put ='\" Maintainer: John Williams <johnkt12qz@gmail.com>'

  "put ='\" Current maintainer: John Williams <johnkt12qz@gmail.com>'
  "put ='\" Last maintainer: John Williams <johnkt12qz@gmail.com>'

endfunction
"autocmd BufNew call WriteFileInformation()

" }}}

" Key bindings {{{
map <F3> :UndotreeToggle<CR>
map <F4> :NERDTreeToggle<CR>
map <F5> :TagbarToggle<CR>

nnoremap df :YcmCompleter GoToDefinition<CR>
nnoremap dc :YcmCompleter GoToDeclaration<CR>
nnoremap ff :YcmCompleter FixIt<CR>
nnoremap <leader>gd :YcmCompleter GetDoc<CR>
nnoremap <leader>gt :YcmCompleter GoTo<CR>
nnoremap <leader>gi :YcmCompleter GoToInclude<CR>
nnoremap ty :YcmCompleter GetType<CR>

nnoremap <leader>db :packadd termdebug<CR>:Termdebug<CR>

autocmd FileType java nnoremap <F8> :w<CR> :!java "%"<CR>
autocmd FileType c nnoremap <F8> :w<CR> :!clear; time gcc
      \ -Wall -Wextra -pthread -g -std=c11
      \ "%" -o "%<.out" && time ./"%<.out" <CR>
autocmd FileType cpp nnoremap <F8> :w<CR> :!clear; time g++
      \ -Wall -Wextra -pthread -g -std=c++2a
      \ "%" -o "%<.out" && time ./"%<.out" <CR>
autocmd FileType cpp imap <F8> <C-O>:w<CR> <C-O>:!clear; time g++
      \ -Wall -Wextra -pthread -g -std=c++2a
      \ "%" -o "%<.out" && time ./"%<.out" <CR>
autocmd FileType c,cpp,java,javascript map <C-K> :call FormatWholeFile() <CR>
autocmd FileType c,cpp,java,javascript imap <C-K> <C-O>:call FormatWholeFile()<CR>
autocmd FileType python nnoremap <F8> :w<CR> :!clear; python % <CR>

" Type Ngb to jump to buffer number N (from 1 to 99)
let c = 1
while c <= 99
  execute "nnoremap " . c . "gb :" . c . "b\<CR>"
  let c += 1
endwhile

" \b \f \g : go back/forward/last-used
nnoremap <leader>b :bp<CR>
nnoremap <leader>v :bn<CR>
nnoremap <leader>z :e#<CR>
" }}}

" Commands {{{
" jump to last cursor
autocmd BufReadPost *
      \ if line("'\"") > 0 && line("'\"") <= line("$") |
      \   exe "normal g`\"" |
      \ endif

fun! StripTrailingWhitespace()
  " don't strip on these filetypes
  if &ft =~ 'markdown'
    return
  endif
  %s/\s\+$//e
endfun
autocmd BufWritePre	* call StripTrailingWhitespace()

function FormatWholeFile()
  let l:lines = 'all'
  py3f /usr/share/clang/clang-format.py
endfunction

function FormatOnSave()
  let l:formatdiff = 1
  call FormatWholeFile()
endfunction
autocmd BufWritePre *.h,*.cc,*.cpp,*.c call FormatOnSave()

" Special File Format
autocmd FileType sh,cucumber,ruby,yaml,zsh,vim setlocal shiftwidth=2 tabstop=2 expandtab

" }}}
