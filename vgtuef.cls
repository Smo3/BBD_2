% VGTU EF class
%
% Maksim Norkin, 2012

\ProvidesClass{vgtuef}


\LoadClass[12pt,a4paper,twoside,openright]{article}


% Table of contents
% \RequirePackage{tocloft}
\RequirePackage{graphicx}
\RequirePackage[utf8x]{inputenc}
%\RequirePackage[L7x]{fontenc}
\RequirePackage[T1]{fontenc}
\RequirePackage[lithuanian]{babel}
\RequirePackage{fancyhdr}
\RequirePackage{layout}
\RequirePackage{color}
\RequirePackage[hmarginratio=1:1]{geometry}
\RequirePackage[toc,page]{appendix}

%% Table
\RequirePackage{multirow}

\RequirePackage{epstopdf}
\RequirePackage{listings}

%% Math
\RequirePackage[sc]{mathpazo}
\RequirePackage{amsmath,amssymb}
\RequirePackage{upgreek}

%% Custom spaces
\RequirePackage{setspace}

%% Fonts
\RequirePackage{winfonts}

%% Graphics
\RequirePackage{pgfplots}
\RequirePackage{tikz}

%% Custom captions
\RequirePackage[skip=5pt,labelfont=bf,justification=centering,labelsep=space]{caption}
\RequirePackage{chngcntr}
\counterwithin{figure}{section}
\counterwithin{equation}{section}
\counterwithin{table}{section}
\RequirePackage{newfloat}

%% Source code float environment
%\RequirePackage{float}
\RequirePackage{floatrow}
%\floatname{cfigure}{programinis kodas}
%\floatplacement{cfigure}{tp}
\newfloat{cfigure}{tbp}{lop}[section]
\DeclareFloatStyle{cfigure-fs}{
	capposition=top,
	heightadjust=all
}
\floatsetup[cfigure]{style=cfigure-fs}
\DeclareCaptionLabelFormat{cfigure-st}{#2 programinis kodas.}
\floatsetup[table]{style=cfigure-fs}
\captionsetup[cfigure]{position=above,labelformat=cfigure-st,justification=justified,singlelinecheck=false}
\counterwithin{cfigure}{section}

%% Source code style
\lstset{
  language=Matlab,
  basicstyle=\footnotesize,
  numbers=left
}

% COLORS
\definecolor{b1}{cmyk}{0.68,0.15,0.0, 0.59}

\renewcommand{\sfdefault}{phv}
\renewcommand{\rmdefault}{ptm}
\renewcommand{\ttdefault}{pcr}

\def\@IEEEstringptm{ptm} % Times Roman family
\def\@IEEEstringppl{ppl} % Palatino Roman family
\def\@IEEEstringphv{phv} % Helvetica Sans Serif family
\def\@IEEEstringpcr{pcr} % Courier typewriter family
\def\@IEEEstringcmtt{cmtt} % Computer Modern typewriter family

\pagestyle{fancy}

\fancypagestyle{plain}{

}

\fancyhead{} % clear all the headers
\renewcommand{\headrulewidth}{0pt} % and lines
%\fancyhead[LE]{LEFT EVEN} % 
%\fancyhead{} % Clear all the headers
\fancyhead[CO]{\includegraphics[width=483pt]{img/CE_HEADER}} % 
\fancyhead[CE]{\includegraphics[width=483pt]{img/CO_HEADER}}
\fancyheadoffset[E]{0pt}
%\fancyhead[CE]{Labas}
%\fancyhead[L]{\includegraphics[height=10pt]{img/CO_HEADER}} % 
%\fancyhead[R]{TT}
%\fancyhead[RO,LE]{RIGHT ODD}
%\fancyhead[LE]{LEFT EVEN}
\fancyfoot{} % Clear all the footer stuff
\fancyfoot[C]{\color{b1}\thepage}

\setlength{\hoffset}{-1in}
%\setlength{\voffset}{-46pt}
\setlength{\textwidth}{483pt}
\setlength{\marginparwidth}{0pt}
\setlength{\oddsidemargin}{70pt}
\setlength{\evensidemargin}{40pt}
\setlength{\marginparsep}{0pt}
%\setlength{\topmargin}{0pt}
\setlength{\textheight}{680pt}
\setlength{\footskip}{20pt}

%\setlength{\headheight}{}

%% Enable font
\normalfont\selectfont

% Table of contents
\renewcommand\thesection{\arabic{section}.}
\renewcommand\thesubsection{\thesection\arabic{subsection}.}
\renewcommand\thesubsubsection{\thesubsection\arabic{subsubsection}.}

\RequirePackage{tocloft}

\renewcommand{\cftsecleader}{\cftdotfill{\cftdotsep}}

\renewcommand{\cfttoctitlefont}{\hfill\bfseries\color{b1}\MakeUppercase}
\renewcommand{\cftaftertoctitle}{\hfill}

%\renewcommand{\contentsname}{\centering Turinys}

% Section style
\def\section{\@startsection{section}{1}{\z@}{1.5ex plus 1.5ex minus 0.5ex}{0.7ex plus 1ex minus 0ex}{\normalfont\normalsize\scshape\bfseries\color{b1}\centering\Large}}
\def\subsection{\@startsection{subsection}{2}{\z@}{1.5ex plus 1.5ex minus 0.5ex}{0.7ex plus .5ex minus 0ex}{\normalfont\normalsize\scshape\bfseries\color{b1}\large}}
\def\subsubsection{\@startsection{subsubsection}{3}{\z@}{1.5ex plus 1.5ex minus 0.5ex}{0.7ex plus .2ex minus 0ex}{\normalfont\normalsize\scshape\bfseries\color{b1}\large}}

\let\stdsection\section
\renewcommand\section{\newpage\stdsection}

%% APPENDIX
\renewcommand\appendixname{PRIEDAI}

