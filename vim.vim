syntax enable

"deser ocupero para el dia
"colorscheme desert
"set background=dark

"materialize claro para la noche
"set t_Co=256
"set background=light



function! BuildComposer(info)
  if a:info.status != 'unchanged' || a:info.force
    if has('nvim')
      !cargo build --release
    else
      !cargo build --release --no-default-features --features json-rpc
    endif
  endif
endfunction



call plug#begin('~/.vim/plugged')

"vericiar tiene de inicio
Plug 'tweekmonster/startuptime.vim'


Plug 'scrooloose/nerdtree', { 'on':  'NERDTreeToggle' }

"-> completado
Plug 'autozimu/LanguageClient-neovim', {
    \ 'branch': 'next',
    \ 'do': './install.sh',
	    \ }
Plug 'junegunn/fzf'
	
Plug 'huawenyu/neogdb.vim'



Plug 'roxma/nvim-yarp'
Plug 'ncm2/ncm2'
Plug 'ncm2/ncm2-bufword'
Plug 'ncm2/ncm2-ultisnips'
Plug 'SirVer/ultisnips'
Plug 'honza/vim-snippets'
Plug 'ncm2/ncm2-path'
Plug 'ncm2/ncm2-tagprefix'
Plug 'yuki-ycino/ncm2-dictionary'
Plug 'ncm2/ncm2-neoinclude' | Plug 'Shougo/neoinclude.vim'
Plug 'ncm2/ncm2-gtags'
Plug 'ncm2/ncm2-highprio-pop'
Plug 'jsfaint/gen_tags.vim'
Plug 'ncm2/ncm2-syntax' | Plug 'Shougo/neco-syntax'
Plug 'ncm2/ncm2-match-highlight'
Plug 'ncm2/ncm2-snipmate'
"Plug 'ncm2/ncm2-tern',  {'do': 'npm install'}
"Plug 'ncm2/ncm2-jedi'
"Plug 'ObserverOfTime/ncm2-jc2', {'for': ['java', 'jsp']}
"Plug 'artur-shaik/vim-javacomplete2', {'for': ['java', 'jsp']}
Plug 'ncm2/ncm2-pyclang'

Plug 'tomtom/tlib_vim'
Plug 'marcweber/vim-addon-mw-utils'
Plug 'garbas/vim-snipmate'

Plug 'w0rp/ale'

"Plug 'chiel92/vim-autoformat'
Plug 'sbdchd/neoformat'
Plug 'prettier/vim-prettier', { 'do': 'npm install' }


" -> solo c
"cambia entre h y c
Plug 'vim-scripts/a.vim'




" -> until
"para los colores 
Plug 'chrisbra/colorizer'
Plug 'ap/vim-css-color'
Plug 'Yggdroot/indentLine'
Plug 'enricobacis/vim-airline-clock'

Plug 'euclio/vim-markdown-composer', { 'do': function('BuildComposer') }

Plug 'scrooloose/nerdcommenter'

Plug 'tpope/vim-fugitive'
Plug 'sodapopcan/vim-twiggy'



Plug 'andrewradev/splitjoin.vim'

Plug 'mbbill/undotree'

Plug 'chrisbra/vim-diff-enhanced'

Plug 'vim-scripts/TaskList.vim'
Plug 'gilsondev/searchtasks.vim'
Plug 'samsonw/vim-task'

Plug 'vim-scripts/grep.vim'

Plug 'deris/devdocs.vim'
Plug 'Raimondi/delimitMate'


"moverse con scrool rapido y en smooth  C-f /C-u
Plug 'yuttie/comfortable-motion.vim'



"Plug 'DougBeney/pickachu'

Plug 'majutsushi/tagbar'

Plug 'Valloric/MatchTagAlways'

Plug 'ryanoasis/vim-devicons'

Plug 'airblade/vim-gitgutter'

Plug 'itchyny/calendar.vim'

Plug 'mattn/emmet-vim'

Plug 'gcmt/taboo.vim'

Plug 'MattesGroeger/vim-bookmarks'


Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'

Plug 'kien/ctrlp.vim'

Plug 'schickling/vim-bufonly'

Plug 'LeonelSoriano/vimHttppie'
Plug 'christoomey/vim-conflicted'
Plug 'luochen1990/rainbow'


Plug 'ntpeters/vim-better-whitespace'

Plug 'elzr/vim-json'

Plug 'othree/html5.vim'


Plug 'powerline/powerline'

Plug 'eugen0329/vim-esearch'

"para rezise los split con control mas flecha
Plug 'talek/obvious-resize'




Plug 'huawenyu/neogdb.vim'





"desactiva funciones pesadas para archivos grandes
Plug 'vim-scripts/LargeFile'

"ramas cambiar por el del trabajo
Plug 'idanarye/vim-merginal'
"hisotirial de git
Plug 'cohama/agit.vim'


Plug 'craigemery/vim-autotag'
Plug 'xolox/vim-notes'

Plug 'christoomey/vim-system-copy'
Plug 'xolox/vim-misc'


"buscar y reemplazar
Plug 'brooth/far.vim'

Plug 'thaerkh/vim-indentguides'

Plug 'jistr/vim-nerdtree-tabs'



"abre archivos en la ultima posicion
Plug 'farmergreg/vim-lastplace'


"  TRANFORMA EL TEXT
Plug 'farfanoide/inflector.vim'


"-> temas
Plug 'NLKNguyen/papercolor-theme'



call plug#end()

colorscheme PaperColor

  " enable ncm2 for all buffers
    autocmd BufEnter * call ncm2#enable_for_buffer()

    " IMPORTANTE: :help Ncm2PopupOpen for more information
    set completeopt=noinsert,menuone,noselect





"NERDTree configuracion
map <C-n> :NERDTreeToggle<CR>


" --> LANGUAJE SERVER
let g:LanguageClient_serverCommands = {
    \ 'rust': ['rustup', 'run', 'nightly', 'rls'],
    \ 'javascript': ['javascript-typescript-langserver'],
    \ 'javascript.jsx': ['javascript-typescript-langserver'],
    \ 'html': ['html-languageserver', '--stdio'],
    \ 'cpp': ['clangd'],
    \ 'c': ['clangd'],
    \ 'css': ['css-languageserver', '--stdio'],
    \ 'perl': ['slp.bin'],
    \ 'java': ['java',
    \   '-agentlib:jdwp=transport=dt_socket,server=y,suspend=n,address=1044',
    \   '-Declipse.application=org.eclipse.jdt.ls.core.id1',
    \   '-Dosgi.bundles.defaultStartLevel=4',
    \   '-Declipse.product=org.eclipse.jdt.ls.core.product',
    \   '-Dlog.protocol=true',
    \   '-Dlog.level=ALL',
    \   '-noverify',
    \   '-Xmx1G',
    \   '-jar', '/home/leonel/languaje/plugins/org.eclipse.equinox.launcher_1.4.0.v20161219-1356.jar',
    \   '-configuration', '/home/leonel/languaje/config_linux',
    \   '-data', '/home/leonel/dev/java/skeleton-luis/'],
    \ }


"let g:LanguageClient_loggingFile = '/tmp/lc.log'
"let g:LanguageClient_loggingLevel = 'DEBUG'


nnoremap <F6> :call LanguageClient_contextMenu()<CR>

nnoremap <silent> K :call LanguageClient#textDocument_hover()<CR>
nnoremap <silent> gd :call LanguageClient#textDocument_definition()<CR>
nnoremap <silent> <F2> :call LanguageClient#textDocument_rename()<CR>

" ncm2 settings
autocmd BufEnter * call ncm2#enable_for_buffer()
set completeopt=menuone,noselect,noinsert
set shortmess+=c
inoremap <c-c> 	<ESC>
" make it fast
let ncm2#popup_delay = 6
let ncm2#complete_length = [[4, 4]]
" Use new fuzzy based matches
let g:ncm2#matcher = 'substrfuzzy'


	
"" Map leader to ,
let mapleader='\'

"hi Folded term=NONE cterm=NONE



let g:rainbow_conf = {
\	'guifgs': ['royalblue3', 'darkorange3', 'seagreen3', 'firebrick'],
\	'ctermfgs': ['lightblue', 'lightyellow', 'lightcyan', 'lightmagenta'],
\	'operators': '_,_',
\	'parentheses': ['start=/(/ end=/)/ fold', 'start=/\[/ end=/\]/ fold', 'start=/{/ end=/}/ fold'],
\	'separately': {
\		'*': {},
\		'lisp': {
\			'guifgs': ['royalblue3', 'darkorange3', 'seagreen3', 'firebrick', 'darkorchid3'],
\		},
\		'tex': {
\			'parentheses': ['start=/(/ end=/)/', 'start=/\[/ end=/\]/'],
\		},
\		'vim': {
\			'parentheses': ['start=/(/ end=/)/', 'start=/\[/ end=/\]/', 'start=/{/ end=/}/ fold', 'start=/(/ end=/)/ containedin=vimFuncBody', 'start=/\[/ end=/\]/ containedin=vimFuncBody', 'start=/{/ end=/}/ fold containedin=vimFuncBody'],
\		},
\		'xml': {
\			'parentheses': ['start=/\v\<\z([-_:a-zA-Z0-9]+)(\s+[-_:a-zA-Z0-9]+(\=("[^"]*"|'."'".'[^'."'".']*'."'".'))?)*\>/ end=#</\z1># fold'],
\		},
\		'xhtml': {
\			'parentheses': ['start=/\v\<\z([-_:a-zA-Z0-9]+)(\s+[-_:a-zA-Z0-9]+(\=("[^"]*"|'."'".'[^'."'".']*'."'".'))?)*\>/ end=#</\z1># fold'],
\		},
\		'html': {
\			'parentheses': ['start=/\v\<((area|base|br|col|embed|hr|img|input|keygen|link|menuitem|meta|param|source|track|wbr)[ >])@!\z([-_:a-zA-Z0-9]+)(\s+[-_:a-zA-Z0-9]+(\=("[^"]*"|'."'".'[^'."'".']*'."'".'|[^ '."'".'"><=`]*))?)*\>/ end=#</\z1># fold'],
\		},
\		'php': {
\			'parentheses': ['start=/\v\<((area|base|br|col|embed|hr|img|input|keygen|link|menuitem|meta|param|source|track|wbr)[ >])@!\z([-_:a-zA-Z0-9]+)(\s+[-_:a-zA-Z0-9]+(\=("[^"]*"|'."'".'[^'."'".']*'."'".'|[^ '."'".'"><=`]*))?)*\>/ end=#</\z1># fold', 'start=/(/ end=/)/ containedin=@htmlPreproc contains=@phpClTop', 'start=/\[/ end=/\]/ containedin=@htmlPreproc contains=@phpClTop', 'start=/{/ end=/}/ containedin=@htmlPreproc contains=@phpClTop'],
\		},
\		'css': 0,
\		'sh': {
\			'parentheses': [['\(^\|\s\)\S*()\s*{\?\($\|\s\)','_^{_','}'], ['\(^\|\s\)if\($\|\s\)','_\(^\|\s\)\(then\|else\|elif\)\($\|\s\)_','\(^\|\s\)fi\($\|\s\)'], ['\(^\|\s\)for\($\|\s\)','_\(^\|\s\)\(do\|in\)\($\|\s\)_','\(^\|\s\)done\($\|\s\)'], ['\(^\|\s\)while\($\|\s\)','_\(^\|\s\)\(do\)\($\|\s\)_','\(^\|\s\)done\($\|\s\)'], ['\(^\|\s\)case\($\|\s\)','_\(^\|\s\)\(\S*)\|in\|;;\)\($\|\s\)_','\(^\|\s\)esac\($\|\s\)']],
\		},
\       
\	}
\}



highlight DiffAdd    cterm=NONE ctermfg=0 ctermbg=22
highlight DiffDelete cterm=NONE ctermfg=0 ctermbg=52
highlight DiffChange cterm=NONE ctermfg=0 ctermbg=23
highlight DiffText   cterm=NONE ctermfg=0 ctermbg=23

"para resize de windows
noremap <silent> <C-Up> :<C-U>ObviousResizeUp<CR>
noremap <silent> <C-Down> :<C-U>ObviousResizeDown<CR>
noremap <silent> <C-Left> :<C-U>ObviousResizeLeft<CR>
noremap <silent> <C-Right> :<C-U>ObviousResizeRight<CR>


let g:ale_linters = {'c': ['gcc', 'clang'], 'cpp': ['clang', 'gcc']}

if exists("g:ale_enabled")
	let g:ale_c_clang_options = "-DHAVE_CONFIG_H -Wall -Wextra -std=ansi -pedantic"
	let g:ale_c_gcc_options = "-DHAVE_CONFIG_H -Wall -Wextra -std=ansi -pedantic"

	" Sets or appends pkg-config cflags to g:ale_c_gcc_options and
	" ale_c_clang_options. Takes a list as argument.
	function! SetProjectCflags(pkgDeps)
		let new_list = deepcopy(a:pkgDeps)
		call map(new_list, {_, val -> systemlist('pkg-config --cflags ' . val)[0] })
		let cflags = join(new_list, ' ')
		let g:ale_c_clang_options .= ' ' . cflags
		let g:ale_c_gcc_options .= ' ' . cflags
	endfunction

	call SetProjectCflags(["glib-2.0",
		\ "gtk+-3.0",
		\ "x11",
		\ "alsa",
		\ "libnotify"])
endif

let g:airline#extensions#ale#enabled = 1
let g:ale_echo_msg_error_str = 'E'
let g:ale_echo_msg_warning_str = 'W'
let g:ale_echo_msg_format = '[%linter%] %s [%severity%]'
let g:ale_fixers = {'javascript': ['prettier'], 'scss': ['stylelint'], 'python': ['yapf', 'isort']}
let g:ale_set_highlights = 1
let g:ale_set_signs = 1
let g:ale_sign_column_always = 1



" Set to auto read when a file is changed from the outside
"set autoread

" Sets how many lines of history VIM has to remember
set history=500


set nocompatible
" Enable filetype plugins
filetype plugin on
filetype indent on


augroup lexical
  autocmd!
  autocmd FileType markdown,mkd call lexical#init()
  autocmd FileType textile call lexical#init()
  autocmd FileType text call lexical#init({ 'spell': 0 })
augroup END
let g:lexical#spell = 1 





if has("persistent_undo")
    set undodir=~/.undodir/
    set undofile
endif


autocmd FileType python set omnifunc=pythoncomplete#Complete
autocmd FileType javascript set omnifunc=javascriptcomplete#CompleteJS
autocmd FileType html set omnifunc=htmlcomplete#CompleteTags
autocmd FileType css set omnifunc=csscomplete#CompleteCSS
autocmd FileType xml set omnifunc=xmlcomplete#CompleteTags
autocmd FileType php set omnifunc=phpcomplete#CompletePHP
autocmd FileType c set omnifunc=ccomplete#Complete

"linea 80
if exists('+colorcolumn')
  set colorcolumn=80
else
  au BufWinEnter * let w:m2=matchadd('ErrorMsg', '\%>80.\+', -1)
endif

inoremap <silent> <expr> <CR> ncm2_ultisnips#expand_or("\<CR>", 'n')

" c-j c-k for moving in snippet
" let g:UltiSnipsExpandTrigger		= "<Plug>(ultisnips_expand)"
let g:UltiSnipsJumpForwardTrigger	= "<c-j>"
let g:UltiSnipsJumpBackwardTrigger	= "<c-k>"
let g:UltiSnipsRemoveSelectModeMappings = 0


set nu
" Turn on the WiLd menu
set wildmenu


" Ignore compiled files
set wildignore=*.o,*~,*.pyc

"Always show current position
set ruler

" Height of the command bar
set cmdheight=1

" A buffer becomes hidden when it is abandoned
set hid

" Configure backspace so it acts as it should act
set backspace=eol,start,indent
set whichwrap+=<,>,h,l

" Ignore case when searching
set ignorecase

" When searching try to be smart about cases 
set smartcase

" Highlight search results
set hlsearch

" Makes search act like search in modern browsers
set incsearch

" Don't redraw while executing macros (good performance config)
set lazyredraw

" For regular expressions turn magic on
set magic

" Show matching brackets when text indicator is over them
set showmatch
" How many tenths of a second to blink when matching brackets
set mat=2

" No annoying sound on errors
"set noerrorbells
"set novisualbell
"set t_vb=
"set tm=500


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Colors and Fonts
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Enable syntax highlighting
syntax enable



" Set extra options when running in GUI mode
if has("gui_running")
    set guioptions-=T
    set guioptions+=e
    set t_Co=256
    set guitablabel=%M\ %t
endif

" Set utf8 as standard encoding and en_US as the standard language
set encoding=utf8

" Use Unix as the standard file type
set ffs=unix,dos,mac


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Files, backups and undo
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Turn backup off, since most stuff is in SVN, git et.c anyway...
set nobackup
set nowb
set noswapfile


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Text, tab and indent related
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Use spaces instead of tabs
set expandtab

" Be smart when using tabs ;)
set smarttab

" 1 tab == 4 spaces
set shiftwidth=4
set tabstop=4

" Linebreak on 500 characters
set lbr
set tw=500

set ai "Auto indent
set si "Smart indent
set wrap "Wrap lines



""""""""""""""""""""""""""""""
" => Visual mode related
""""""""""""""""""""""""""""""
" Visual mode pressing * or # searches for the current selection
" Super useful! From an idea by Michael Naumann
vnoremap <silent> * :call VisualSelection('f')<CR>
vnoremap <silent> # :call VisualSelection('b')<CR>


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Moving around, tabs, windows and buffers
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Treat long lines as break lines (useful when moving around in them)
map j gj
map k gk

" Map <Space> to / (search) and Ctrl-<Space> to ? (backwards search)
map <space> /
map <c-space> ?

" Disable highlight when <leader><cr> is pressed
map <silent> <leader><cr> :noh<cr>

" Smart way to move between windows
map <C-j> <C-W>j
map <C-k> <C-W>k
map <C-h> <C-W>h
map <C-l> <C-W>l

" Close the current buffer
map <leader>bd :Bclose<cr>

" Close all the buffers
map <leader>ba :1,1000 bd!<cr>



" Useful mappings for managing tabs
map <leader>tn :tabnew<cr>
map <leader>to :tabonly<cr>
map <leader>tc :tabclose<cr>
map <leader>tm :tabmove

" Opens a new tab with the current buffer's path
" Super useful when editing files in the same directory
map <leader>te :tabedit <c-r>=expand("%:p:h")<cr>/

" Switch CWD to the directory of the open buffer
map <leader>cd :cd %:p:h<cr>:pwd<cr>

" Specify the behavior when switching between buffers 
try
  set switchbuf=useopen,usetab,newtab
  set stal=2
catch
endtry

" Return to last edit position when opening files (You want this!)
autocmd BufReadPost *
     \ if line("'\"") > 0 && line("'\"") <= line("$") |
     \   exe "normal! g`\"" |
     \ endif
" Remember info about open buffers on close
set viminfo^=%

set title                   " Show the filename in the window title bar.

""""""""""""""""""""""""""""""
" => Status line
""""""""""""""""""""""""""""""
" Always show the status line
set laststatus=2

" Format the status line
set statusline=\ %{HasPaste()}%F%m%r%h\ %w\ \ CWD:\ %r%{getcwd()}%h\ \ \ Line:\ %l


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Editing mappings
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Remap VIM 0 to first non-blank character
map 0 ^

" Move a line of text using ALT+[jk] or Comamnd+[jk] on mac
nmap <M-j> mz:m+<cr>`z
nmap <M-k> mz:m-2<cr>`z
vmap <M-j> :m'>+<cr>`<my`>mzgv`yo`z
vmap <M-k> :m'<-2<cr>`>my`<mzgv`yo`z

if has("mac") || has("macunix")
  nmap <D-j> <M-j>
  nmap <D-k> <M-k>
  vmap <D-j> <M-j>
  vmap <D-k> <M-k>
endif

" Delete trailing white space on save, useful for Python and CoffeeScript ;)
func! DeleteTrailingWS()
  exe "normal mz"
  %s/\s\+$//ge
  exe "normal `z"
endfunc
autocmd BufWrite *.py :call DeleteTrailingWS()
autocmd BufWrite *.coffee :call DeleteTrailingWS()


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => vimgrep searching and cope displaying
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" When you press gv you vimgrep after the selected text
vnoremap <silent> gv :call VisualSelection('gv')<CR>

" Open vimgrep and put the cursor in the right position
map <leader>g :vimgrep // **/*.<left><left><left><left><left><left><left>

" Vimgreps in the current file
map <leader><space> :vimgrep // <C-R>%<C-A><right><right><right><right><right><right><right><right><right>

" When you press <leader>r you can search and replace the selected text
vnoremap <silent> <leader>r :call VisualSelection('replace')<CR>

" Do :help cope if you are unsure what cope is. It's super useful!
"
" When you search with vimgrep, display your results in cope by doing:
"   <leader>cc
"
" To go to the next search result do:
"   <leader>n
"
" To go to the previous search results do:
"   <leader>p
"
map <leader>cc :botright cope<cr>
map <leader>co ggVGy:tabnew<cr>:set syntax=qf<cr>pgg
map <leader>n :cn<cr>
map <leader>p :cp<cr>


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Spell checking
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Pressing ,ss will toggle and untoggle spell checking
map <leader>ss :setlocal spell!<cr>

" Shortcuts using <leader>
map <leader>sn ]s
map <leader>sp [s
map <leader>sa zg
map <leader>s? z=



"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Misc
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Remove the Windows ^M - when the encodings gets messed up
noremap <Leader>m mmHmt:%s/<C-V><cr>//ge<cr>'tzt'm

" Quickly open a buffer for scripbble
map <leader>q :e ~/buffer<cr>

" Toggle paste mode on and off
map <leader>pp :setlocal paste!<cr>





"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Helper functions
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
function! CmdLine(str)
    exe "menu Foo.Bar :" . a:str
    emenu Foo.Bar
    unmenu Foo
endfunction

function! VisualSelection(direction) range
    let l:saved_reg = @"
    execute "normal! vgvy"

    let l:pattern = escape(@", '\\/.*$^~[]')
    let l:pattern = substitute(l:pattern, "\n$", "", "")

    if a:direction == 'b'
        execute "normal ?" . l:pattern . "^M"
    elseif a:direction == 'gv'
        call CmdLine("vimgrep " . '/'. l:pattern . '/' . ' **/*.')
    elseif a:direction == 'replace'
        call CmdLine("%s" . '/'. l:pattern . '/')
    elseif a:direction == 'f'
        execute "normal /" . l:pattern . "^M"
    endif

    let @/ = l:pattern
    let @" = l:saved_reg
endfunction


" Returns true if paste mode is enabled
function! HasPaste()
    if &paste
        return 'PASTE MODE  '
    en
    return ''
endfunction
    
" Don't close window, when deleting a buffer
command! Bclose call <SID>BufcloseCloseIt()
function! <SID>BufcloseCloseIt()
   let l:currentBufNum = bufnr("%")
   let l:alternateBufNum = bufnr("#")

   if buflisted(l:alternateBufNum)
     buffer #
   else
     bnext
   endif

   if bufnr("%") == l:currentBufNum
     new
   endif

   if buflisted(l:currentBufNum)
     execute("bdelete! ".l:currentBufNum)
   endif
endfunction


"esto es para el plogin de tagbar
nmap <C-l> :TagbarToggle<CR>


"este es para lo busqueda en archivos
set runtimepath^=~/.vim/bundle/ctrlp.vim


"esto es para los comentarios
" Add spaces after comment delimiters by default
let g:NERDSpaceDelims = 1

" Use compact syntax for prettified multi-line comments
let g:NERDCompactSexyComs = 1

" Align line-wise comment delimiters flush left instead of following code indentation
let g:NERDDefaultAlign = 'left'

" Set a language to use its alternate delimiters by default
let g:NERDAltDelims_java = 1

" Add your own custom formats or override the defaults
let g:NERDCustomDelimiters = { 'c': { 'left': '/**','right': '*/' } }

" Allow commenting and inverting empty lines (useful when commenting a region)
let g:NERDCommentEmptyLines = 1

" Enable trimming of trailing whitespace when uncommenting
let g:NERDTrimTrailingWhitespace = 1
"final delos comentarios


 if has('mouse')
   set mouse=a
 endif

set guioptions-=e


set sessionoptions+=tabpages,globals


noremap <silent> <C-S>          :wa<CR>
vnoremap <silent> <C-S>         <C-C>:wa<CR>
inoremap <silent> <C-S>         <C-O>:wa<CR>

noremap <silent> <A-t>          :tabnew<CR>
vnoremap <silent> <A-t>         <C-C>:tabnew<CR>
inoremap <silent> <A-t>        <C-O>:tabnew<CR>


noremap <silent> <A-a>          :tabp<CR>
vnoremap <silent> <A-a>         <C-C>:tabp<CR>
inoremap <silent> <A-a>        <C-O>:tabp<CR>


noremap <silent> <A-s>          :tabn<CR>
vnoremap <silent> <A-s>         <C-C>:tabn<CR>
inoremap <silent> <A-s>        <C-O>:tabn<CR>





noremap <A-k> :wincmd k<cr>
noremap <A-j> :wincmd j<cr>
noremap <A-h> :wincmd h<cr>
noremap <A-l> :wincmd l<cr>





let g:airline#extensions#tabline#enabled = 1
let g:airline_powerline_fonts=1

" vim-airline
if !exists('g:airline_symbols')
  let g:airline_symbols = {}
endif

if !exists('g:airline_powerline_fonts')
  let g:airline#extensions#tabline#left_sep = ' '
  let g:airline#extensions#tabline#left_alt_sep = '|'
  let g:airline_left_sep          = '▶'
  let g:airline_left_alt_sep      = '»'
  let g:airline_right_sep         = '◀'
  let g:airline_right_alt_sep     = '«'
  let g:airline#extensions#branch#prefix     = '⤴' "➔, ➥, ⎇
  let g:airline#extensions#readonly#symbol   = '⊘'
  let g:airline#extensions#linecolumn#prefix = '¶'
  let g:airline#extensions#paste#symbol      = 'ρ'
  let g:airline_symbols.linenr    = '␊'
  let g:airline_symbols.branch    = '⎇'
  let g:airline_symbols.paste     = 'ρ'
  let g:airline_symbols.paste     = 'Þ'
  let g:airline_symbols.paste     = '∥'
  let g:airline_symbols.whitespace = 'Ξ'
else
  let g:airline#extensions#tabline#left_sep = ''
  let g:airline#extensions#tabline#left_alt_sep = ''

  " powerline symbols
  let g:airline_left_sep = ''
  let g:airline_left_alt_sep = ''
  let g:airline_right_sep = ''
  let g:airline_right_alt_sep = ''
  let g:airline_symbols.branch = ''
  let g:airline_symbols.readonly = ''
  let g:airline_symbols.linenr = ''
endif

set tabline=%!tabber#TabLine()


set shell=bash\ -l
set clipboard=unnamedplus


:au BufEnter * if &buftype == 'terminal' | :startinsert | endif
autocmd BufWinEnter,WinEnter term://* startinsert
tnoremap <ESC> <C-\><C-n>:buffer #<CR>




set encoding=UTF-8
set cursorline 

set wildignore+=*.pyc,*.o,*.obj,*.svn,*.swp,*.class,*.hg,*.DS_Store,*.min.*

let NERDTreeRespectWildIgnore=1


set sessionoptions=buffers,curdir,folds,options,tabpages,winsize
function! Mksession()
	"let path = 'session' . fnamemodify(bufname('%'),':p')
	let l:path =  'session' . fnamemodify(resolve(expand('<sfile>:p')), ':h')
	let l:name_session = substitute(l:path, "/", "-", "g")
	exe  "mksession! " . $HOME . "/.vim/sessions/" . l:name_session . ".vim"
endfunction
command Mksession call Mksession()


function! MksessionLoad()
	let l:path =  'session' . fnamemodify(resolve(expand('<sfile>:p')), ':h')
	let l:name_session = substitute(l:path, "/", "-", "g")
	let l:session_path = $HOME . "/.vim/sessions/" . l:name_session . ".vim"
	if filereadable(l:session_path)
	    exe  "source " . $HOME . "/.vim/sessions/" . l:name_session . ".vim"
	endif
endfunction
command MksessionLoad call MksessionLoad()

augroup mksession_auto
  autocmd!
"  au VimEnter * nested call MksessionLoad()
"  au VimLeavePre * call Mksession()
augroup END


" #########################################################
" # A way to delete 'mkview'
function! MyDeleteView()
	let path = fnamemodify(bufname('%'),':p')
	" vim's odd =~ escaping for /
	let path = substitute(path, '=', '==', 'g')
	if empty($HOME)
	else
		let path = substitute(path, '^'.$HOME, '\~', '')
	endif
	let path = substitute(path, '/', '=+', 'g') . '='
	" view directory
	let path = &viewdir.'/'.path
	call delete(path)
	echo "Deleted: ".path
endfunction
command Delview call MyDeleteView()
" Lower-case user commands: http://vim.wikia.com/wiki/Replace_a_builtin_command_using_cabbrev
cabbrev delview <c-r>=(getcmdtype()==':' && getcmdpos()==1 ? 'Delview' : 'delview')<CR>



